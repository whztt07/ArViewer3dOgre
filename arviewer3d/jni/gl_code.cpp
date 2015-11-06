/*
 Copyright (C) 2015, Peter Graf

 This file is part of Arvos-App - AR Viewer Open Source App for Android.
 Arvos-App is free software.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 For more information on the AR Viewer Open Source - App,
 please see: http://www.arvos-app.com/.
 */

/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define OGRE_STATIC_GLES
#define OGRE_STATIC_ParticleFX
#define OGRE_STATIC_OctreeSceneManager
#include <Ogre/include/Build/OgreStaticPluginLoader.h>

#include <Ogre/include/OgreMain/Ogre.h>
#include <Ogre/include/OgreMain/OgreRenderWindow.h>
#include <Ogre/include/OgreMain/OgreStringConverter.h>
#include <Ogre/include/RenderSystems/GLES/EGL/Android/OgreAndroidEGLWindow.h>
#include <OgreAPKFileSystemArchive.h>
#include <Ogre/include/OgreMain/Android/OgreAPKFileSystemArchive.h>
#include <Ogre/include/OgreMain/Android/OgreAPKZipArchive.h>

#include <EGL/egl.h>

#include "gl_code.h"

#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer
#include <android/asset_manager.h>

static AAssetManager* gAssetManager;

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static ANativeWindow *mRendereWindow = 0;

static Ogre::RenderWindow* gRenderWnd = NULL;
static Ogre::Root* gRoot = NULL;
static Ogre::StaticPluginLoader* gStaticPluginLoader = NULL;
static Ogre::SceneManager* gSceneMgr = NULL;

static Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName)
{
	Ogre::DataStreamPtr stream;
	AAsset* asset = AAssetManager_open(gAssetManager, fileName.c_str(), AASSET_MODE_BUFFER);
	if (asset)
	{
		off_t length = AAsset_getLength(asset);
		void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
		memcpy(membuf, AAsset_getBuffer(asset), length);
		AAsset_close(asset);

		stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
	}
	return stream;
}

static void setupScene()
{
	LOGI("------->setupScene()");

	Ogre::ConfigFile cf;
	cf.load(openAPKFile("resources.cfg"));

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	while (seci.hasMoreElements())
	{
		Ogre::String sec, type, arch;
		sec = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	gSceneMgr = gRoot->createSceneManager(Ogre::ST_GENERIC);
	Ogre::Camera* camera = gSceneMgr->createCamera("MyCam");

	Ogre::Entity* pEntity = gSceneMgr->createEntity("SinbadInstance", "Sinbad.mesh");
	Ogre::SceneNode* pNode = gSceneMgr->getRootSceneNode()->createChildSceneNode();
	pNode->attachObject(pEntity);

	Ogre::Light* pDirLight = gSceneMgr->createLight();
	pDirLight->setDirection(Ogre::Vector3(0, -1, 0));
	pDirLight->setType(Ogre::Light::LT_DIRECTIONAL);
	pNode->attachObject(pDirLight);

	camera->setNearClipDistance(1.0f);
	camera->setFarClipDistance(100000.0f);
	camera->setPosition(0, 0, 20.0f);
	camera->lookAt(0, 0, 0);
	camera->setAutoAspectRatio(true);

	Ogre::Viewport* vp = gRenderWnd->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(1, 0, 0));

	LOGI("<-------setupScene()");
}


static void initWindow()
{
	LOGI("------->initWindow() >>>>>>>>");

	LOGI("Calling AConfiguration_new()");

	AConfiguration* config = AConfiguration_new();

	LOGI("AConfiguration_new() %p", config);

	AConfiguration_fromAssetManager(config, gAssetManager);

	LOGI("AConfiguration_fromAssetManager(config, gAssetManager) %p", config);

	if (!gRenderWnd)
	{
		Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(gAssetManager) );
		Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(gAssetManager) );

		Ogre::NameValuePairList opt;

		LOGI("Ogre::StringConverter::toString((int)mRendereWindow) %s",
				Ogre::StringConverter::toString((int )mRendereWindow).c_str());
		LOGI("Ogre::StringConverter::toString((int)config) %s", Ogre::StringConverter::toString((int )config).c_str());

		opt["externalWindowHandle"] = Ogre::StringConverter::toString((int) mRendereWindow);
		opt["androidConfig"] = Ogre::StringConverter::toString((int) config);

		gRenderWnd = gRoot->createRenderWindow("OgreWindow", 0, 0, false, &opt);

		setupScene();
	}
	else
	{
		static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(mRendereWindow, config);
	}
	AConfiguration_delete(config);

	LOGI("<-------initWindow()");
}

static void initOgre()
{
	LOGI("------->initOgre()");

	if (gRoot == NULL)
	{
		gRoot = new Ogre::Root();

		LOGI("new Ogre::Root() %p", gRoot);

#ifdef OGRE_STATIC_LIB
		gStaticPluginLoader = new Ogre::StaticPluginLoader();
		gStaticPluginLoader->load();
#endif
		LOGI("gRoot->getAvailableRenderers().at(0) %p", gRoot->getAvailableRenderers().at(0));

		gRoot->setRenderSystem(gRoot->getAvailableRenderers().at(0));
		gRoot->initialise(false);
	}

	LOGI("<-------initOgre()");
}

extern "C"
{
JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_init(JNIEnv * env, jobject obj, jint width, jint height,
		jobject assetManager, jstring externalFilesDir, jobject surface);
JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_step(JNIEnv * env, jobject obj);

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnStart(JNIEnv* jenv, jobject obj, jobject assetManager,
		jstring externalFilesDir);
JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnResume(JNIEnv* jenv, jobject obj);
JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnPause(JNIEnv* jenv, jobject obj);
JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnStop(JNIEnv* jenv, jobject obj);
JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeSetSurface(JNIEnv* jenv, jobject obj, jobject surface);

}
;

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_init(JNIEnv * env, jobject obj, jint width, jint height,
		jobject assetManager, jstring externalFilesDir, jobject surface)
{
	LOGI("------->native init()");

	AAssetManager *aAssetManager = AAssetManager_fromJava(env, assetManager);
	if (aAssetManager == NULL)
	{
		LOGI("error loading asset manager");
	}
	else
	{
		LOGI("loaded asset manager");
	}
	const char * activityExternalFilesDir = env->GetStringUTFChars(externalFilesDir, NULL);

	LOGI("<-------native init");
}

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_step(JNIEnv * env, jobject obj)
{
	LOGI("------->native step ()");

	if (gRenderWnd != NULL && gRenderWnd->isActive())
	{
		gRenderWnd->windowMovedOrResized();
		gRoot->renderOneFrame();
	}

	LOGI("<-------native step");
}

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnStart(JNIEnv* jenv, jobject obj, jobject assetManager,
		jstring externalFilesDir)
{
	LOGI("------->nativeOnStart");

	AAssetManager *aAssetManager = AAssetManager_fromJava(jenv, assetManager);
	if (aAssetManager == NULL)
	{
		LOGI("error loading asset manager");
	}
	else
	{
		LOGI("loaded asset manager %p", aAssetManager);
	}
	const char * activityExternalFilesDir = jenv->GetStringUTFChars(externalFilesDir, NULL);

	LOGI("<-------nativeOnStart");
	return;
}

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnResume(JNIEnv* jenv, jobject obj)
{
	LOGI("------->nativeOnResume");

	LOGI("<-------nativeOnResume");
	return;
}

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnPause(JNIEnv* jenv, jobject obj)
{
	LOGI("------->nativeOnPause");

	LOGI("<-------nativeOnPause");
	return;
}

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeOnStop(JNIEnv* jenv, jobject obj)
{
	LOGI("------->nativeOnStop");

	LOGI("<-------nativeOnStop");
	return;
}

JNIEXPORT void JNICALL Java_com_arvos_arviewer_GL2JNILib_nativeSetSurface(JNIEnv* jenv, jobject obj, jobject surface)
{
	LOGI("------->nativeSetSurface");
	if (surface != 0)
	{
		mRendereWindow = ANativeWindow_fromSurface(jenv, surface);
		LOGI("Got mRendereWindow %p", mRendereWindow);

		initOgre();
		initWindow();
	}
	else
	{
		LOGI("Releasing mRendereWindow");
		ANativeWindow_release(mRendereWindow);
	}
	LOGI("<-------nativeSetSurface");
	return;
}


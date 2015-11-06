SAMPLE_PATH := $(call my-dir)

LOCAL_PATH := $(SAMPLE_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE    := gl2jni
LOCAL_SRC_FILES := gl_code.cpp

LOCAL_CPPFLAGS += -std=c++11 -frtti -Wno-switch-enum -Wno-switch
LOCAL_ARM_MODE := arm

LOCAL_LDLIBS	:= -landroid -lc -lm -ldl -llog -lEGL -lGLESv1_CM -L$(LOCAL_PATH)/Ogre/lib/armeabi-v7a -L$(LOCAL_PATH)/Dependencies/lib/armeabi-v7a
LOCAL_LDLIBS	+= -lPlugin_ParticleFXStatic -lPlugin_OctreeSceneManagerStatic -lRenderSystem_GLESStatic -lOgreOverlayStatic -lOgreMainStatic
LOCAL_LDLIBS	+= -landroid -lc -lm -ldl -llog -lEGL -lGLESv1_CM -lzzip -lz -lFreeImage -lfreetype -lOIS  $(LOCAL_PATH)/Dependencies/lib/armeabi-v7a/libsupc++.a $(LOCAL_PATH)/Dependencies/lib/armeabi-v7a/libstdc++.a ./obj/local/armeabi-v7a/libcpufeatures.a

LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES=1 -I$(LOCAL_PATH)/Ogre/include/Build -I$(LOCAL_PATH)/Ogre/include/OgreMain -I$(LOCAL_PATH)/Ogre/include/OgreMain/Android -I$(LOCAL_PATH)/Ogre/include/RenderSystems/GLES
LOCAL_CFLAGS += -I$(LOCAL_PATH)/Ogre/include/RenderSystems/GLES/EGL -I$(ANDROID_NDK)/sources/cpufeatures -I$(LOCAL_PATH)/Ogre/include/Components/Overlay 
LOCAL_CFLAGS += -I$(LOCAL_PATH)/Ogre/include/PlugIns/ParticleFX -I$(LOCAL_PATH)/Ogre/include/PlugIns/OctreeSceneManager 
LOCAL_CFLAGS += -I$(LOCAL_PATH)/Dependencies/include -I$(LOCAL_PATH)/Dependencies/include/OIS 
LOCAL_CFLAGS += -fexceptions -frtti -x c++ -D___ANDROID___ -DANDROID -DZZIP_OMIT_CONFIG_H 

LOCAL_STATIC_LIBRARIES := cpufeatures
LOCAL_SHARED_LIBRARIES := 
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
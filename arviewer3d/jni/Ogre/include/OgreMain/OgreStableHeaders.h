/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2013 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

/* Stable headers which will be used for precompilation if the compiler
   supports it. Add entries here when headers are unlikely to change.
   NB: a change to any of these headers will result in a full rebuild,
   so don't add things to this lightly.
*/

#ifndef __OgreStableHeaders__
#define __OgreStableHeaders__

#include <Ogre/include/OgreMain/OgrePlatform.h>

#if (OGRE_PLATFORM == OGRE_PLATFORM_WIN32 && !defined(__MINGW32__)) || OGRE_PLATFORM == OGRE_PLATFORM_WINRT || OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include <Ogre/include/OgreMain/OgreArchive.h>
#include <Ogre/include/OgreMain/OgreAxisAlignedBox.h>
#include <Ogre/include/OgreMain/OgreBitwise.h>
#include <Ogre/include/OgreMain/OgreCamera.h>
#include <Ogre/include/OgreMain/OgreColourValue.h>
#include <Ogre/include/OgreMain/OgreCommon.h>
#include <Ogre/include/OgreMain/OgreDataStream.h>
#include <Ogre/include/OgreMain/OgreException.h>
#include <Ogre/include/OgreMain/OgreFileSystem.h>
#include <Ogre/include/OgreMain/OgreLog.h>
#include <Ogre/include/OgreMain/OgreMath.h>
#include <Ogre/include/OgreMain/OgreMatrix3.h>
#include <Ogre/include/OgreMain/OgreMatrix4.h>
#include <Ogre/include/OgreMain/OgreMovableObject.h>
#include <Ogre/include/OgreMain/OgreNode.h>
#include <Ogre/include/OgreMain/OgrePlane.h>
#include <Ogre/include/OgreMain/OgrePrerequisites.h>
#include <Ogre/include/OgreMain/OgreQuaternion.h>
#include <Ogre/include/OgreMain/OgreResource.h>
#include <Ogre/include/OgreMain/OgreSerializer.h>
#include <Ogre/include/OgreMain/OgreSharedPtr.h>
#include <Ogre/include/OgreMain/OgreSimpleRenderable.h>
#include <Ogre/include/OgreMain/OgreSimpleSpline.h>
#include <Ogre/include/OgreMain/OgreSingleton.h>
#include <Ogre/include/OgreMain/OgreSphere.h>
#include <Ogre/include/OgreMain/OgreStdHeaders.h>
#include <Ogre/include/OgreMain/OgreString.h>
#include <Ogre/include/OgreMain/OgreStringConverter.h>
#include <Ogre/include/OgreMain/OgreStringInterface.h>
#include <Ogre/include/OgreMain/OgreStringVector.h>
#include <Ogre/include/OgreMain/OgreUserObjectBindings.h>
#include <Ogre/include/OgreMain/OgreVector2.h>
#include <Ogre/include/OgreMain/OgreVector3.h>
#include <Ogre/include/OgreMain/OgreVector4.h>
#include <Ogre/include/OgreMain/OgreWireBoundingBox.h>
#if OGRE_NO_ZIP_ARCHIVE == 0
#	include <Ogre/include/OgreMain/OgreZip.h>
#endif

#endif

#endif 

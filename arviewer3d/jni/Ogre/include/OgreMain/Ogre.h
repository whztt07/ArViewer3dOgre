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
#ifndef _Ogre_H__
#define _Ogre_H__
// This file includes all the other files which you will need to build a client application
#include "OgreAnimation.h"
#include <Ogre/include/OgreMain/OgreAnimation.h>
#include <Ogre/include/OgreMain/OgreAnimationState.h>
#include <Ogre/include/OgreMain/OgreAnimationTrack.h>
#include <Ogre/include/OgreMain/OgreAny.h>
#include <Ogre/include/OgreMain/OgreArchive.h>
#include <Ogre/include/OgreMain/OgreArchiveManager.h>
#include <Ogre/include/OgreMain/OgreAxisAlignedBox.h>
#include <Ogre/include/OgreMain/OgreBillboardChain.h>
#include <Ogre/include/OgreMain/OgreBillboardSet.h>
#include <Ogre/include/OgreMain/OgreBone.h>
#include <Ogre/include/OgreMain/OgreCamera.h>
#include <Ogre/include/OgreMain/OgreCompositionPass.h>
#include <Ogre/include/OgreMain/OgreCompositionTargetPass.h>
#include <Ogre/include/OgreMain/OgreCompositionTechnique.h>
#include <Ogre/include/OgreMain/OgreCompositor.h>
#include <Ogre/include/OgreMain/OgreCompositorChain.h>
#include <Ogre/include/OgreMain/OgreCompositorInstance.h>
#include <Ogre/include/OgreMain/OgreCompositorManager.h>
#include <Ogre/include/OgreMain/OgreConfigFile.h>
#include <Ogre/include/OgreMain/OgreControllerManager.h>
#include <Ogre/include/OgreMain/OgreDataStream.h>
#include <Ogre/include/OgreMain/OgreEntity.h>
#include <Ogre/include/OgreMain/OgreException.h>
#include <Ogre/include/OgreMain/OgreFrustum.h>
#include <Ogre/include/OgreMain/OgreGpuProgram.h>
#include <Ogre/include/OgreMain/OgreGpuProgramManager.h>
#include <Ogre/include/OgreMain/OgreHardwareBufferManager.h>
#include <Ogre/include/OgreMain/OgreHardwareIndexBuffer.h>
#include <Ogre/include/OgreMain/OgreHardwareOcclusionQuery.h>
#include <Ogre/include/OgreMain/OgreHardwarePixelBuffer.h>
#include <Ogre/include/OgreMain/OgreHardwarePixelBuffer.h>
#include <Ogre/include/OgreMain/OgreHardwareVertexBuffer.h>
#include <Ogre/include/OgreMain/OgreHighLevelGpuProgram.h>
#include <Ogre/include/OgreMain/OgreHighLevelGpuProgramManager.h>
#include <Ogre/include/OgreMain/OgreInstanceBatch.h>
#include <Ogre/include/OgreMain/OgreInstancedEntity.h>
#include <Ogre/include/OgreMain/OgreInstanceManager.h>
#include <Ogre/include/OgreMain/OgreKeyFrame.h>
#include <Ogre/include/OgreMain/OgreLight.h>
#include <Ogre/include/OgreMain/OgreLogManager.h>
#include <Ogre/include/OgreMain/OgreManualObject.h>
#include <Ogre/include/OgreMain/OgreMaterial.h>
#include <Ogre/include/OgreMain/OgreMaterialManager.h>
#include <Ogre/include/OgreMain/OgreMaterialSerializer.h>
#include <Ogre/include/OgreMain/OgreMath.h>
#include <Ogre/include/OgreMain/OgreMatrix3.h>
#include <Ogre/include/OgreMain/OgreMatrix4.h>
#include <Ogre/include/OgreMain/OgreMesh.h>
#include <Ogre/include/OgreMain/OgreMeshManager.h>
#include <Ogre/include/OgreMain/OgreMeshSerializer.h>
#include <Ogre/include/OgreMain/OgreParticleAffector.h>
#include <Ogre/include/OgreMain/OgreParticleEmitter.h>
#include <Ogre/include/OgreMain/OgreParticleSystemManager.h>
#include <Ogre/include/OgreMain/OgrePass.h>
#include <Ogre/include/OgreMain/OgrePatchMesh.h>
#include <Ogre/include/OgreMain/OgrePatchSurface.h>
#include <Ogre/include/OgreMain/OgrePrerequisites.h>
#include <Ogre/include/OgreMain/OgreProfiler.h>
#include <Ogre/include/OgreMain/OgreRadixSort.h>
#include <Ogre/include/OgreMain/OgreRenderObjectListener.h>
#include <Ogre/include/OgreMain/OgreRenderQueueInvocation.h>
#include <Ogre/include/OgreMain/OgreRenderQueueListener.h>
#include <Ogre/include/OgreMain/OgreRenderSystem.h>
#include <Ogre/include/OgreMain/OgreRenderTargetListener.h>
#include <Ogre/include/OgreMain/OgreRenderTexture.h>
#include <Ogre/include/OgreMain/OgreRenderWindow.h>
#include <Ogre/include/OgreMain/OgreResourceBackgroundQueue.h>
#include <Ogre/include/OgreMain/OgreResourceGroupManager.h>
#include <Ogre/include/OgreMain/OgreRibbonTrail.h>
#include <Ogre/include/OgreMain/OgreRoot.h>
#include <Ogre/include/OgreMain/OgreSceneManager.h>
#include <Ogre/include/OgreMain/OgreSceneManagerEnumerator.h>
#include <Ogre/include/OgreMain/OgreSceneNode.h>
#include <Ogre/include/OgreMain/OgreShadowCameraSetup.h>
#include <Ogre/include/OgreMain/OgreShadowCameraSetupFocused.h>
#include <Ogre/include/OgreMain/OgreShadowCameraSetupLiSPSM.h>
#include <Ogre/include/OgreMain/OgreShadowCameraSetupPlaneOptimal.h>
#include <Ogre/include/OgreMain/OgreShadowCameraSetupPSSM.h>
#include <Ogre/include/OgreMain/OgreSimpleRenderable.h>
#include <Ogre/include/OgreMain/OgreSkeleton.h>
#include <Ogre/include/OgreMain/OgreSkeletonInstance.h>
#include <Ogre/include/OgreMain/OgreSkeletonManager.h>
#include <Ogre/include/OgreMain/OgreSkeletonSerializer.h>
#include <Ogre/include/OgreMain/OgreStaticGeometry.h>
#include <Ogre/include/OgreMain/OgreString.h>
#include <Ogre/include/OgreMain/OgreStringConverter.h>
#include <Ogre/include/OgreMain/OgreStringVector.h>
#include <Ogre/include/OgreMain/OgreSubEntity.h>
#include <Ogre/include/OgreMain/OgreSubMesh.h>
#include <Ogre/include/OgreMain/OgreTechnique.h>
#include <Ogre/include/OgreMain/OgreTextureManager.h>
#include <Ogre/include/OgreMain/OgreTextureUnitState.h>
#include <Ogre/include/OgreMain/OgreVector2.h>
#include <Ogre/include/OgreMain/OgreViewport.h>
#include <Ogre/include/OgreMain/OgreWindowEventUtilities.h>
// .... more to come

#endif

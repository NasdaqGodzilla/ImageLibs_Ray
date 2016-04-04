// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_RENDER_TYPES_H_
#define _H_RENDER_TYPES_H_

#include <ray/graphics_types.h>

_NAME_BEGIN

typedef std::shared_ptr<class Material> MaterialPtr;
typedef std::shared_ptr<class MaterialPass> MaterialPassPtr;
typedef std::shared_ptr<class MaterialTech> MaterialTechPtr;
typedef std::shared_ptr<class MaterialParam> MaterialParamPtr;
typedef std::shared_ptr<class MaterialVariant> MaterialVariantPtr;
typedef std::shared_ptr<class MaterialLoader> MaterialLoaderPtr;
typedef std::shared_ptr<class MaterialManager> MaterialManagerPtr;
typedef std::shared_ptr<class RenderObject> RenderObjectPtr;
typedef std::shared_ptr<class RenderPostProcess> RenderPostProcessPtr;
typedef std::shared_ptr<class RenderPipelineController> RenderPipelineControllerPtr;
typedef std::shared_ptr<class RenderPipeline> RenderPipelinePtr;
typedef std::shared_ptr<class RenderPipelineManager> RenderPipelineManagerPtr;
typedef std::shared_ptr<class RenderDataManager> RenderDataManagerPtr;
typedef std::shared_ptr<class RenderMesh> RenderMeshPtr;
typedef std::shared_ptr<class RenderSystem> RenderSystemPtr;
typedef std::shared_ptr<class RenderBuffer> RenderBufferPtr;
typedef std::shared_ptr<class RenderScene> RenderScenePtr;
typedef std::shared_ptr<class Camera> CameraPtr;
typedef std::shared_ptr<class Light> LightPtr;

typedef std::weak_ptr<class Material> MaterialWeakPtr;
typedef std::weak_ptr<class MaterialPass> MaterialPassWeakPtr;
typedef std::weak_ptr<class MaterialTech> MaterialTechWeakPtr;
typedef std::weak_ptr<class MaterialParam> MaterialParamWeakPtr;
typedef std::weak_ptr<class MaterialVariant> MaterialVariantWeakPtr;
typedef std::weak_ptr<class MaterialLoader> MaterialLoaderWeakPtr;
typedef std::weak_ptr<class MaterialManager> MaterialManagerWeakPtr;
typedef std::weak_ptr<class RenderObject> RenderObjectWeakPtr;
typedef std::weak_ptr<class RenderPostProcess> RenderPostProcessWeakPtr;
typedef std::weak_ptr<class RenderPipelineController> RenderPipelineControllerWeakPtr;
typedef std::weak_ptr<class RenderPipeline> RenderPipelineWeakPtr;
typedef std::weak_ptr<class RenderPipelineManager> RenderPipelineManagerWeakPtr;
typedef std::weak_ptr<class RenderDataManager> RenderDataManagerWeakPtr;
typedef std::weak_ptr<class RenderMesh> RenderMeshWeakPtr;
typedef std::weak_ptr<class RenderSystem> RenderSystemWeakPtr;
typedef std::weak_ptr<class RenderBuffer> RenderBufferWeakPtr;
typedef std::weak_ptr<class RenderScene> RenderSceneWeakPtr;
typedef std::weak_ptr<class Camera> CameraWeakPtr;
typedef std::weak_ptr<class Light> LightWeakPtr;

typedef std::vector<RenderBufferPtr> RenderBuffers;
typedef std::vector<RenderMeshPtr> RenderMeshes;
typedef std::vector<RenderObjectPtr> RenderObjects;
typedef std::vector<RenderScenePtr> RenderScenes;
typedef std::vector<RenderPostProcessPtr> RenderPostProcessor;
typedef std::vector<MaterialPtr> Materials;
typedef std::vector<MaterialPassPtr> MaterialPassList;
typedef std::vector<MaterialTechPtr> MaterialTechniques;
typedef std::vector<MaterialParamPtr> MaterialParams;
typedef std::vector<MaterialVariantPtr> MaterialVariants;
typedef std::vector<CameraPtr> Cameras;
typedef std::vector<LightPtr> Lights;

enum CameraType
{
	CameraTypeOrtho,
	CameraTypePerspective,
	CameraTypeBeginRange = CameraTypeOrtho,
	CameraTypeEndRange = CameraTypePerspective,
	CameraTypeRangeSize = (CameraTypeEndRange - CameraTypeBeginRange + 1),
	CameraTypeMaxEnum = 0x7FFFFFFF
};

enum CameraOrder
{
	CameraOrderShadow,
	CameraOrderColor,
	CameraOrderNormal,
	CameraOrderLight,
	CameraOrderShading,
	CameraOrderCustom,
	CameraOrderCubeMap,
	CameraOrderMain,
	CameraOrderBeginRange = CameraOrderShadow,
	CameraOrderEndRange = CameraOrderMain,
	CameraOrderRangeSize = (CameraOrderEndRange - CameraOrderBeginRange + 1),
	CameraOrderMaxEnum = 0x7FFFFFFF
};

enum CameraRender
{
	CameraRenderScreen,
	CameraRenderTexture,
	CameraRenderCubeMap,
	CameraRenderBeginRange = CameraRenderScreen,
	CameraRenderEndRange = CameraRenderCubeMap,
	CameraRenderRangeSize = (CameraRenderEndRange - CameraRenderBeginRange + 1),
	CameraRenderMaxEnum = 0x7FFFFFFF
};

enum LightType
{
	LightTypeSun,
	LightTypeDirectional,
	LightTypeAmbient,
	LightTypePoint,
	LightTypeSpot,
	LightTypeArea,
	LightTypeHemiSphere,
	LightTypeBeginRange = LightTypeSun,
	LightTypeEndRange = LightTypeHemiSphere,
	LightTypeRangeSize = (LightTypeEndRange - LightTypeBeginRange + 1),
	LightTypeMaxEnum = 0x7FFFFFFF
};

enum RenderQueue
{
	RenderQueueCustom,
	RenderQueueOpaque,
	RenderQueueTransparent,
	RenderQueueLighting,
	RenderQueuePostprocess,
	RenderQueueBeginRange = RenderQueueCustom,
	RenderQueueEndRange = RenderQueuePostprocess,
	RenderQueueRangeSize = (RenderQueueEndRange - RenderQueueBeginRange + 1),
	RenderQueueMaxEnum = 0x7FFFFFFF
};

enum RenderPass
{
	RenderPassCustom,
	RenderPassDepth,
	RenderPassShadow,
	RenderPassOpaques,
	RenderPassTransparent,
	RenderPassSpecific,
	RenderPassLights,
	RenderPassPostprocess,
	RenderPassBeginRange = RenderPassCustom,
	RenderPassEndRange = RenderPassPostprocess,
	RenderPassRangeSize = (RenderPassEndRange - RenderPassBeginRange + 1),
	RenderPassMaxEnum = 0x7FFFFFFF
};

_NAME_END

#endif
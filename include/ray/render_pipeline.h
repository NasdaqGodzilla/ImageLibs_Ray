// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
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
#ifndef _H_RENDER_PIPELINE_H_
#define _H_RENDER_PIPELINE_H_

#include <ray/render_types.h>

_NAME_BEGIN

class EXPORT RenderPipeline : public rtti::Interface
{
	__DeclareSubClass(RenderPipeline, rtti::Interface)
public:
	RenderPipeline() noexcept;
	~RenderPipeline() noexcept;

	bool setup(RenderPipelineDevicePtr pipelineDevice, WindHandle window, std::uint32_t w, std::uint32_t h, std::uint32_t dpi_w, std::uint32_t dpi_h, GraphicsSwapInterval interval) noexcept;
	void close() noexcept;

	void renderBegin() noexcept;
	void renderEnd() noexcept;

	void setWindowResolution(std::uint32_t w, std::uint32_t h) noexcept;
	void getWindowResolution(std::uint32_t& w, std::uint32_t& h) const noexcept;

	void setFramebufferSize(std::uint32_t w, std::uint32_t h) noexcept;
	void getFramebufferSize(std::uint32_t& w, std::uint32_t& h) const noexcept;

	GraphicsDeviceType getDeviceType() const noexcept;

	void setSwapInterval(GraphicsSwapInterval interval) noexcept;
	GraphicsSwapInterval getSwapInterval() const noexcept;

	void setCamera(const Camera* camera, bool forceUpdate = false) noexcept;
	const Camera* getCamera() const noexcept;

	void setViewport(std::uint32_t i, const Viewport& view) noexcept;
	const Viewport& getViewport(std::uint32_t i) const noexcept;

	void setScissor(std::uint32_t i, const Scissor& scissor) noexcept;
	const Scissor& getScissor(std::uint32_t i) const noexcept;

	void setFramebuffer(const GraphicsFramebufferPtr& target) noexcept;
	void clearFramebuffer(std::uint32_t i, GraphicsClearFlags flags, const float4& color, float depth = 1.0f, std::int32_t stencil = 0) noexcept;
	void readFramebuffer(std::uint32_t i, const GraphicsTexturePtr& texture, std::uint32_t miplevel, std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) noexcept;
	void readFramebufferToCube(std::uint32_t i, std::uint32_t face, const GraphicsTexturePtr& texture, std::uint32_t miplevel, std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) noexcept;
	void discardFramebuffer(std::uint32_t i) noexcept;

	void setMaterialPass(const MaterialPassPtr& pass) noexcept;
	void setVertexBuffer(std::uint32_t i, const GraphicsDataPtr& vbo, std::intptr_t offset) noexcept;
	void setIndexBuffer(const GraphicsDataPtr& ibo, std::intptr_t offset, GraphicsIndexType indexType) noexcept;

	void generateMipmap(const GraphicsTexturePtr& texture);

	void drawCone(const MaterialTech& tech, std::uint32_t layer = 0) noexcept;
	void drawSphere(const MaterialTech& tech, std::uint32_t layer = 0) noexcept;
	void drawScreenQuad(const MaterialTech& tech, std::uint32_t instanceCount = 1) noexcept;
	void drawScreenQuadLayer(const MaterialTech& tech, std::uint32_t layer, std::uint32_t instanceCount = 1) noexcept;

	void draw(std::uint32_t numVertices, std::uint32_t numInstances, std::uint32_t startVertice, std::uint32_t startInstances) noexcept;
	void drawIndexed(std::uint32_t numIndices, std::uint32_t numInstances, std::uint32_t startIndice, std::uint32_t startVertice, std::uint32_t startInstances) noexcept;

	void drawLayer(std::uint32_t numVertices, std::uint32_t numInstances, std::uint32_t startVertice, std::uint32_t startInstances, std::uint32_t layer) noexcept;
	void drawIndexedLayer(std::uint32_t numIndices, std::uint32_t numInstances, std::uint32_t startIndice, std::uint32_t startVertice, std::uint32_t startInstances, std::uint32_t layer) noexcept;

	void drawRenderQueue(RenderQueue queue) noexcept;
	void drawRenderQueue(RenderQueue queue, const MaterialTechPtr& tech) noexcept;

	void addPostProcess(RenderPostProcessPtr& postprocess) noexcept;
	void removePostProcess(RenderPostProcessPtr& postprocess) noexcept;
	bool drawPostProcess(RenderQueue queue, const GraphicsFramebufferPtr& source, const GraphicsFramebufferPtr& swap) noexcept;
	void destroyPostProcess() noexcept;

	void present() noexcept;

	bool isTextureSupport(GraphicsFormat format) noexcept;
	bool isTextureDimSupport(GraphicsTextureDim dimension) noexcept;
	bool isVertexSupport(GraphicsFormat format) noexcept;
	bool isShaderSupport(GraphicsShaderStageFlagBits stage) noexcept;

	void setTransform(const float4x4& transform) noexcept;
	void setTransformInverse(const float4x4& transform) noexcept;

	const MaterialSemanticPtr& getSemanticParam(GlobalSemanticType type) const noexcept;

	GraphicsDataPtr createGraphicsData(const GraphicsDataDesc& desc) noexcept;
	GraphicsInputLayoutPtr createInputLayout(const GraphicsInputLayoutDesc& desc) noexcept;
	GraphicsTexturePtr createTexture(const GraphicsTextureDesc& desc) noexcept;
	GraphicsTexturePtr createTexture(std::uint32_t w, std::uint32_t h, GraphicsTextureDim dim, GraphicsFormat format, GraphicsSamplerFilter filter = GraphicsSamplerFilter::GraphicsSamplerFilterLinear, GraphicsSamplerWrap wrap = GraphicsSamplerWrap::GraphicsSamplerWrapRepeat) noexcept;
	GraphicsFramebufferPtr createFramebuffer(const GraphicsFramebufferDesc& desc) noexcept;
	GraphicsFramebufferLayoutPtr createFramebufferLayout(const GraphicsFramebufferLayoutDesc& desc) noexcept;

	MaterialPtr createMaterial(const std::string& name) noexcept;
	void destroyMaterial(MaterialPtr material) noexcept;

private:
	bool setupDeviceContext(WindHandle window, std::uint32_t w, std::uint32_t h, GraphicsSwapInterval interval) noexcept;
	bool setupMaterialSemantic() noexcept;
	bool setupBaseMeshes() noexcept;

	void destroyDeviceContext() noexcept;
	void destroyMaterialSemantic() noexcept;
	void destroyBaseMeshes() noexcept;
	void destroyDataManager() noexcept;

	void makePlane(float width, float height, std::uint32_t widthSegments, std::uint32_t heightSegments) noexcept;
	void makeCone(float radius, float height, std::uint32_t segments, float thetaStart = 0, float thetaLength = M_TWO_PI) noexcept;
	void makeSphere(float radius, std::uint32_t widthSegments = 8, std::uint32_t heightSegments = 6, float phiStart = 0.0, float phiLength = M_TWO_PI, float thetaStart = 0, float thetaLength = M_PI) noexcept;

private:
	RenderPipeline(const RenderPipeline&) = delete;
	RenderPipeline& operator=(const RenderPipeline&) = delete;

private:
	std::uint32_t _width;
	std::uint32_t _height;

	std::uint32_t _dpi_w;
	std::uint32_t _dpi_h;

	RenderPipelineDevicePtr _pipelineDevice;
	RenderPipelineManagerPtr _pipelineManager;

	GraphicsSwapchainPtr _graphicsSwapchain;
	GraphicsContextPtr _graphicsContext;

	const Camera* _camera;

	GraphicsDataPtr _planeVbo;
	GraphicsDataPtr _planeIbo;
	GraphicsIndexType _planeIndexType;
	std::uint32_t _planeIndices;

	GraphicsDataPtr _sphereVbo;
	GraphicsDataPtr _sphereIbo;
	GraphicsIndexType _sphereIndexType;
	std::uint32_t _sphereIndices;

	GraphicsDataPtr _coneVbo;
	GraphicsDataPtr _coneIbo;
	GraphicsIndexType _coneIndexType;
	std::uint32_t _coneIndices;

	MaterialSemanticManagerPtr _semanticsManager;

	RenderDataManagerPtr _dataManager;

	RenderPostProcessor _postprocessors;
};

_NAME_END

#endif
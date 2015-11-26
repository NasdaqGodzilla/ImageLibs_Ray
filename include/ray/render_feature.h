// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
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
#ifndef _H_RENDERER_FEATURE_H_
#define _H_RENDERER_FEATURE_H_

#include <ray/game_features.h>
#include <ray/render_system.h>

_NAME_BEGIN

class EXPORT RenderFeature final : public GameFeature
{
	__DeclareSubClass(RenderFeature, GameFeature)
public:
	RenderFeature() noexcept;
	RenderFeature(WindHandle hwnd, std::uint32_t w, std::uint32_t h) noexcept;
	virtual ~RenderFeature() noexcept;

	void setRenderWindow(WindHandle hwnd, std::uint32_t w, std::uint32_t h) noexcept;
	WindHandle getRenderWindow() const noexcept;

	void setRenderPipeline(RenderPipelinePtr pipeline) noexcept;
	RenderPipelinePtr getRenderPipeline() const noexcept;

	void setRenderSetting(const RenderSetting& setting) noexcept;
	const RenderSetting& getRenderSetting() const noexcept;

	RenderScenePtr getRenderScene(GameScene* scene) noexcept;
	RenderScenePtr getRenderScene(GameScenePtr scene) noexcept;

	GameFeaturePtr clone() const noexcept;

private:

	void onActivate() except;
	void onDeactivate() except;

	void onOpenScene(GameScenePtr scene) except;
	void onCloseScene(GameScenePtr scene) except;

	void onFrameBegin() except;
	void onFrame() except;
	void onFrameEnd() except;

private:
	RenderFeature(const RenderFeature&) = delete;
	RenderFeature& operator=(const RenderFeature&) = delete;

private:

	typedef std::map<std::uint32_t, RenderScenePtr> RenderScenes;

	WindHandle _hwnd;
	std::uint32_t _width;
	std::uint32_t _height;

	RenderSetting _renderSetting;
	RenderScenes _renderScenes;
};

_NAME_END

#endif
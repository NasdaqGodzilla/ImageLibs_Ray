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
#ifndef _H_SSSS_H_
#define _H_SSSS_H_

#include <ray/render_post_process.h>

_NAME_BEGIN

class SSSS final : public RenderPostProcess
{
public:
	SSSS() noexcept;
	~SSSS() noexcept;

	void setStrength(float strength) noexcept;
	void setCorrection(float correction) noexcept;

	float getStrength() const noexcept;
	float getCorrection() const noexcept;

	void applyGuassBlur(RenderPipeline& pipeline, GraphicsFramebufferPtr source, const GraphicsFramebufferPtr& swap) noexcept;

private:
	virtual void onActivate(RenderPipeline& pipeline) noexcept;
	virtual void onDeactivate(RenderPipeline& pipeline) noexcept;

	virtual bool onRender(RenderPipeline& pipeline, RenderQueue queue, const GraphicsFramebufferPtr& source, const GraphicsFramebufferPtr& swap) noexcept;

private:
	float _sssStrength;
	float _sssCorrection;

	MaterialPtr _ssss;
	MaterialTechPtr _sssGuassBlur;

	MaterialParamPtr _sssFactor;
	MaterialParamPtr _sssSource;
};

_NAME_END

#endif
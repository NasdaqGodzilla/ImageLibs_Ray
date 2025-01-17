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
#ifndef _H_LIGHT_COMPONENT_H_
#define _H_LIGHT_COMPONENT_H_

#include <ray/render_component.h>
#include <ray/light.h>

_NAME_BEGIN

class EXPORT LightComponent final : public RenderComponent
{
	__DeclareSubClass(LightComponent, RenderComponent)
public:
	LightComponent() noexcept;
	LightComponent(const archivebuf& reader) noexcept;
	~LightComponent() noexcept;

	void setVisible(bool enable) noexcept;
	bool getVisible() const noexcept;

	void setLightType(LightType type) noexcept;
	LightType getLightType() const noexcept;

	void setLightRange(float range) noexcept;
	void setLightIntensity(float intensity) noexcept;
	void setLightAttenuation(const float3& atten) noexcept;
	void setSpotInnerCone(float value) noexcept;
	void setSpotOuterCone(float value) noexcept;
	void setLightColor(const float3& color) noexcept;

	float getLightRange() const noexcept;
	float getLightIntensity() const noexcept;
	const float3& getLightAttenuation() const noexcept;
	const float2& getSpotInnerCone() const noexcept;
	const float2& getSpotOuterCone() const noexcept;
	const float3& getLightColor() const noexcept;

	void setShadowMode(ShadowMode shadowMode) noexcept;
	ShadowMode getShadowMode() const noexcept;

	void setShadowBias(float bias) noexcept;
	float getShadowBias() const noexcept;

	void setGlobalIllumination(bool enable) noexcept;
	bool getGlobalIllumination() const noexcept;

	void load(const archivebuf& reader) noexcept;
	void save(archivebuf& write) noexcept;

	GameComponentPtr clone() const noexcept;

private:
	virtual void onActivate() noexcept;
	virtual void onDeactivate() noexcept;

	virtual void onAttachComponent(const GameComponentPtr& component) noexcept;
	virtual void onDetachComponent(const GameComponentPtr& component) noexcept;

	virtual void onMoveAfter() noexcept;

	virtual void onEnableSkyBox(bool enable) noexcept;
	virtual void onEnableSkyLighting(bool enable) noexcept;

	virtual void onSkyBoxChange() noexcept;
	virtual void onSkyLightingDiffuseChange() noexcept;
	virtual void onSkyLightingSpecularChange() noexcept;

private:
	LightComponent(const LightComponent&) = delete;
	LightComponent& operator=(const LightComponent&) = delete;

private:
	LightPtr _light;

	std::function<void()> _onSkyBoxChange;
	std::function<void()> _onSkyLightingDiffuseChange;
	std::function<void()> _onSkyLightingSpecularChange;
	std::function<void(bool)> _onEnableSkyBox;
	std::function<void(bool)> _onEnableSkyLighting;
};

_NAME_END

#endif
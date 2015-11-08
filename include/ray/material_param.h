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
#ifndef _H_MATERIAL_PARAM_H_
#define _H_MATERIAL_PARAM_H_

#include <ray/material_fwd.h>

_NAME_BEGIN

class EXPORT MaterialParam final : public ShaderVariant
{
public:
	MaterialParam() noexcept;
	MaterialParam(const std::string& name, float value) noexcept;
	MaterialParam(const std::string& name, const float3& value) noexcept;
	MaterialParam(const std::string& name, const Vector4& value) noexcept;
	MaterialParam(const std::string& name, const Matrix4x4& value) noexcept;
	MaterialParam(const std::string& name, ShaderVariantType type) noexcept;
	~MaterialParam() noexcept;

	void addShaderUniform(ShaderUniformPtr uniform) noexcept;
	void removeShaderUniform(ShaderUniformPtr uniform) noexcept;

private:
	virtual void onChangeBefore() noexcept;
	virtual void onChangeAfter() noexcept;

private:
	MaterialParam(const MaterialParam&) = delete;
	MaterialParam& operator=(const MaterialParam&) = delete;

private:

	ShaderUniforms _uniforms;
};

_NAME_END

#endif
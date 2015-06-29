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
#ifndef _H_RENDER_STATE_H_
#define _H_RENDER_STATE_H_

#include <ray/render_types.h>

_NAME_BEGIN

struct EXPORT RenderBlendState
{
    bool           blendEnable;
    bool           blendSeparateEnable;

    BlendOperation blendOp;
    BlendFactor    blendSrc;
    BlendFactor    blendDest;

    BlendOperation blendAlphaOp;
    BlendFactor    blendAlphaSrc;
    BlendFactor    blendAlphaDest;

    ColorMask      colorWriteMask;

    RenderBlendState() noexcept;
};

struct EXPORT RenderRasterState
{
    CullMode            cullMode;
    FillMode            fillMode;
    bool                scissorTestEnable;
    bool                srgbEnable;
    bool                multisampleEnable;
    bool                pointSizeEnable;

    RenderRasterState() noexcept;
};

struct EXPORT RenderDepthState
{
    bool                depthEnable;
    bool                depthWriteMask;
    CompareFunction     depthFunc;

    bool                depthBiasEnable;
    float               depthBias;
    float               depthSlopScaleBias;

    RenderDepthState() noexcept;
};

struct EXPORT RenderStencilState
{
    bool                stencilEnable;
    int                 stencilRef;
    CompareFunction     stencilFunc;
    unsigned int        stencilReadMask;
    unsigned int        stencilWriteMask;
    StencilOperation    stencilFail;
    StencilOperation    stencilZFail;
    StencilOperation    stencilPass;

    bool                stencilTwoEnable;
    CompareFunction     stencilTwoFunc;
    unsigned int        stencilTwoReadMask;
    unsigned int        stencilTwoWriteMask;
    StencilOperation    stencilTwoFail;
    StencilOperation    stencilTwoZFail;
    StencilOperation    stencilTwoPass;

    RenderStencilState() noexcept;
};

struct EXPORT RenderClearState
{
    ClearFlags    clearFlags;
    Vector4       clearColor;
    float         clearDepth;
    std::uint32_t clearStencil;

    RenderClearState() noexcept;
};

class EXPORT RenderState : public Instance<RenderState>
{
public:
    RenderState() noexcept;
    virtual ~RenderState() noexcept;

    void setup() noexcept;
    void close() noexcept;

    void setBlendState(const RenderBlendState& state) noexcept;
    void setRasterState(const RenderRasterState& state) noexcept;
    void setDepthState(const RenderDepthState& state) noexcept;
    void setStencilState(const RenderStencilState& state) noexcept;
    void setClearState(const RenderClearState& state) noexcept;

    RenderBlendState& getBlendState() noexcept;
    RenderRasterState& getRasterState() noexcept;
    RenderDepthState& getDepthState() noexcept;
    RenderStencilState& getStencilState() noexcept;
    RenderClearState& getClearState() noexcept;

    const RenderBlendState& getBlendState() const noexcept;
    const RenderRasterState& getRasterState() const noexcept;
    const RenderDepthState& getDepthState() const noexcept;
    const RenderStencilState& getStencilState() const noexcept;
    const RenderClearState& getClearState() const noexcept;

    static CullMode stringToCullMode(const std::string& cullmode) noexcept;
    static FillMode stringToFillMode(const std::string& fillmode) noexcept;
    static BlendOperation stringToBlendOperation(const std::string& blendop) noexcept;
    static BlendFactor stringToBlendFactor(const std::string& factor) noexcept;
    static ColorMask stringToColorMask(const std::string& mask) noexcept;
    static CompareFunction stringToCompareFunc(const std::string& func) noexcept;
    static StencilOperation stringToStencilOp(const std::string& stencilop) noexcept;
    static ClearFlags stringToClearFlags(const std::string& flags) noexcept;

public:

    RenderBlendState _blendState;
    RenderRasterState _rasterState;
    RenderDepthState _depthState;
    RenderStencilState _stencilState;
    RenderClearState _clearState;
};

_NAME_END

#endif
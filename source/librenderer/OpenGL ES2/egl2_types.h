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
#ifndef _H_EGL2_TYPES_H_
#define _H_EGL2_TYPES_H_

#include <ray/render_device.h>
#include <ray/render_buffer.h>
#include <ray/render_texture.h>
#include <ray/render_state.h>
#include <ray/render_window.h>
#include <ray/render_command.h>
#include <ray/shader.h>

#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <GLES2\gl2ext.h>

_NAME_BEGIN

#if defined(EGLAPI)
#	define GL_DEBUG_OUTPUT_SYNCHRONOUS   GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR
#   define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR
#   define GL_DEBUG_CALLBACK_FUNCTION    GL_DEBUG_CALLBACK_FUNCTION_KHR
#   define GL_DEBUG_CALLBACK_USER_PARAM  GL_DEBUG_CALLBACK_USER_PARAM_KHR
#   define GL_DEBUG_SOURCE_API           GL_DEBUG_SOURCE_API_KHR
#   define GL_DEBUG_SOURCE_WINDOW_SYSTEM GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR
#   define GL_DEBUG_SOURCE_SHADER_COMPILER GL_DEBUG_SOURCE_SHADER_COMPILER_KHR
#   define GL_DEBUG_SOURCE_THIRD_PARTY   GL_DEBUG_SOURCE_THIRD_PARTY_KHR
#   define GL_DEBUG_SOURCE_APPLICATION   GL_DEBUG_SOURCE_APPLICATION_KHR
#   define GL_DEBUG_SOURCE_OTHER         GL_DEBUG_SOURCE_OTHER_KHR
#   define GL_DEBUG_TYPE_ERROR           GL_DEBUG_TYPE_ERROR_KHR
#   define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR
#   define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR
#   define GL_DEBUG_TYPE_PORTABILITY     GL_DEBUG_TYPE_PORTABILITY_KHR
#   define GL_DEBUG_TYPE_PERFORMANCE     GL_DEBUG_TYPE_PERFORMANCE_KHR
#   define GL_DEBUG_TYPE_OTHER           GL_DEBUG_TYPE_OTHER_KHR
#   define GL_DEBUG_TYPE_MARKER          GL_DEBUG_TYPE_MARKER_KHR
#   define GL_DEBUG_TYPE_PUSH_GROUP      GL_DEBUG_TYPE_PUSH_GROUP_KHR
#   define GL_DEBUG_TYPE_POP_GROUP       GL_DEBUG_TYPE_POP_GROUP_KHR
#   define GL_DEBUG_SEVERITY_NOTIFICATION GL_DEBUG_SEVERITY_NOTIFICATION_KHR
#   define GL_MAX_DEBUG_GROUP_STACK_DEPTH GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR
#   define GL_DEBUG_GROUP_STACK_DEPTH    GL_DEBUG_GROUP_STACK_DEPTH_KHR
#   define GL_BUFFER                     GL_BUFFER_KHR
#   define GL_SHADER                     GL_SHADER_KHR
#   define GL_PROGRAM                    GL_PROGRAM_KHR
#   define GL_VERTEX_ARRAY               GL_VERTEX_ARRAY_KHR
#   define GL_QUERY                      GL_QUERY_KHR
#   define GL_MAX_LABEL_LENGTH           GL_MAX_LABEL_LENGTH_KHR
#   define GL_MAX_DEBUG_MESSAGE_LENGTH   GL_MAX_DEBUG_MESSAGE_LENGTH_KHR
#   define GL_MAX_DEBUG_LOGGED_MESSAGES  GL_MAX_DEBUG_LOGGED_MESSAGES_KHR
#   define GL_DEBUG_LOGGED_MESSAGES      GL_DEBUG_LOGGED_MESSAGES_KHR
#   define GL_DEBUG_SEVERITY_HIGH        GL_DEBUG_SEVERITY_HIGH_KHR
#   define GL_DEBUG_SEVERITY_MEDIUM      GL_DEBUG_SEVERITY_MEDIUM_KHR
#   define GL_DEBUG_SEVERITY_LOW         GL_DEBUG_SEVERITY_LOW_KHR
#   define GL_DEBUG_OUTPUT               GL_DEBUG_OUTPUT_KHR
#   define GL_CONTEXT_FLAG_DEBUG_BIT     GL_CONTEXT_FLAG_DEBUG_BIT_KHR
#   define GL_STACK_OVERFLOW             GL_STACK_OVERFLOW_KHR
#   define GL_STACK_UNDERFLOW            GL_STACK_UNDERFLOW_KHR
#   define GL_FRAMEBUFFER_SRGB           GL_FRAMEBUFFER_SRGB_EXT

#   define GLAPIENTRY GL_APIENTRY

#   define glDebugMessageCallback glDebugMessageCallbackKHR
#   define glDebugMessageControl glDebugMessageControlKHR
#endif

#if GL_DEBUG
#	if defined(_VISUAL_STUDIO_)
#		pragma warning(disable : 4127)
#	endif
#	define GL_CHECK(x) do { x; EGL2Check::checkError(); } while (false)
#else
#	define GL_CHECK(x) x
#endif

struct GPUfbconfig
{
	int redSize;
	int greenSize;
	int blueSize;
	int alphaSize;

	int bufferSize;
	int depthSize;
	int stencilSize;

	int accumSize;
	int accumRedSize;
	int accumGreenSize;
	int accumBlueSize;
	int accumAlphaSize;

	int samples;
};

struct GPUctxconfig
{
	int api;
	int major;
	int minor;
	int forward;
	int profile;
	int robustness;
	int release;
	int multithread;

	EGLContext share;
};

typedef std::shared_ptr<class EGL2Canvas> EGL2CanvasPtr;
typedef std::shared_ptr<class EGL2Framebuffer> EGL2RenderTexturePtr;
typedef std::shared_ptr<class EGL2Shader> EGL2ShaderPtr;
typedef std::shared_ptr<class EGL2ShaderObject> EGL2ShaderObjectPtr;
typedef std::shared_ptr<class EGL2VertexBuffer> EGL2VertexBufferPtr;
typedef std::shared_ptr<class EGL2IndexBuffer> EGL2IndexBufferPtr;

class EGL2Types
{
public:

	static GLenum asEGL2VertexType(VertexType type) noexcept;
	static GLenum asEGL2VertexFormat(VertexFormat format) noexcept;
	static GLenum asEGL2IndexType(IndexType type) noexcept;
	static GLenum asEGL2ShaderType(ShaderType type) noexcept;
	static GLenum asEGL2Target(TextureDim mapping) noexcept;
	static GLenum asEGL2Format(TextureFormat format) noexcept;
	static GLenum asEGL2Type(TextureFormat format) noexcept;
	static GLint  asEGL2Internalformat(TextureFormat format) noexcept;
	static GLenum asCompareFunction(CompareFunction func) noexcept;
	static GLenum asBlendFactor(BlendFactor func) noexcept;
	static GLenum asBlendOperation(BlendOperation op) noexcept;
	static GLenum asCullMode(CullMode mode) noexcept;
	static GLenum asFillMode(FillMode mode) noexcept;
	static GLenum asStencilOperation(StencilOperation stencilop) noexcept;
};

class EGL2Check
{
public:
	static void checkError() noexcept;
};

_NAME_END

#endif
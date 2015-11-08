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
#ifdef _BUILD_PLATFORM_WINDOWS
#include <ray/ogl_extenstion.h>

_NAME_BEGIN

#ifdef GLEW_MX
GLEWContext _glewctx;
#endif

PFNGLCREATESTATESNVPROC __glewCreateStatesNV;
PFNGLDELETESTATESNVPROC __glewDeleteStatesNV;
PFNGLISSTATENVPROC __glewIsStateNV;
PFNGLSTATECAPTURENVPROC __glewStateCaptureNV;
PFNGLDRAWCOMMANDSNVPROC __glewDrawCommandsNV;
PFNGLDRAWCOMMANDSADDRESSNVPROC __glewDrawCommandsAddressNV;
PFNGLDRAWCOMMANDSSTATESNVPROC __glewDrawCommandsStatesNV;
PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC __glewDrawCommandsStatesAddressNV;
PFNGLCREATECOMMANDLISTSNVPROC __glewCreateCommandListsNV;
PFNGLDELETECOMMANDLISTSNVPROC __glewDeleteCommandListsNV;
PFNGLISCOMMANDLISTNVPROC __glewIsCommandListNV;
PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC __glewListDrawCommandsStatesClientNV;
PFNGLCOMMANDLISTSEGMENTSNVPROC __glewCommandListSegmentsNV;
PFNGLCOMPILECOMMANDLISTNVPROC __glewCompileCommandListNV;
PFNGLCALLCOMMANDLISTNVPROC __glewCallCommandListNV;
PFNGLGETCOMMANDHEADERNVPROC __glewGetCommandHeaderNV;
PFNGLGETSTAGEINDEXNVPROC __glewGetStageIndexNV;

int OGLExtenstion::initExtention = 0;
int OGLExtenstion::initedNVcommandList = 0;

bool OGLFeatures::ARB_bindless_texture = 0;
bool OGLFeatures::ARB_vertex_array_object = 0;
bool OGLFeatures::ARB_vertex_attrib_binding = 0;
bool OGLFeatures::ARB_provoking_vertex = 0;
bool OGLFeatures::ARB_direct_state_access = 0;
bool OGLFeatures::ARB_viewport_array = 0;
bool OGLFeatures::KHR_debug = 0;
bool OGLFeatures::NV_command_list = 0;
bool OGLFeatures::NV_shader_buffer_load = 0;
bool OGLFeatures::NV_vertex_buffer_unified_memory = 0;

OGLExtenstion::OGLExtenstion() noexcept
{
}

OGLExtenstion::~OGLExtenstion() noexcept
{
}

bool
OGLExtenstion::initExtensions() except
{
	if (initExtention) return 0;

	auto result = glewInit();

	OGLFeatures::ARB_bindless_texture = GLEW_ARB_bindless_texture ? true : false;
	OGLFeatures::ARB_vertex_array_object = GLEW_ARB_vertex_array_object ? true : false;
	OGLFeatures::ARB_vertex_attrib_binding = false; //GLEW_ARB_vertex_attrib_binding ? true : false;
	OGLFeatures::ARB_provoking_vertex = GLEW_ARB_provoking_vertex ? true : false;
	OGLFeatures::ARB_direct_state_access = GLEW_ARB_direct_state_access ? true : false;
	OGLFeatures::ARB_viewport_array = GLEW_ARB_viewport_array ? true : false;
	OGLFeatures::KHR_debug = GLEW_KHR_debug;
	OGLFeatures::NV_shader_buffer_load = false; //GLEW_NV_shader_buffer_load ? true : false;
	OGLFeatures::NV_vertex_buffer_unified_memory = false;//GLEW_NV_vertex_buffer_unified_memory ? true : false;

	initExtention = true;

	return result == GLEW_OK;
}

bool
OGLExtenstion::initCommandListNV() noexcept
{
	if (initedNVcommandList)
		return __glewCreateStatesNV != NULL;

	initedNVcommandList = 1;

	__glewCreateStatesNV = (PFNGLCREATESTATESNVPROC)wglGetProcAddress("glCreateStatesNV");
	__glewDeleteStatesNV = (PFNGLDELETESTATESNVPROC)wglGetProcAddress("glDeleteStatesNV");
	__glewIsStateNV = (PFNGLISSTATENVPROC)wglGetProcAddress("glIsStateNV");
	__glewStateCaptureNV = (PFNGLSTATECAPTURENVPROC)wglGetProcAddress("glStateCaptureNV");
	__glewDrawCommandsNV = (PFNGLDRAWCOMMANDSNVPROC)wglGetProcAddress("glDrawCommandsNV");
	__glewDrawCommandsAddressNV = (PFNGLDRAWCOMMANDSADDRESSNVPROC)wglGetProcAddress("glDrawCommandsAddressNV");
	__glewDrawCommandsStatesNV = (PFNGLDRAWCOMMANDSSTATESNVPROC)wglGetProcAddress("glDrawCommandsStatesNV");
	__glewDrawCommandsStatesAddressNV = (PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC)wglGetProcAddress("glDrawCommandsStatesAddressNV");
	__glewCreateCommandListsNV = (PFNGLCREATECOMMANDLISTSNVPROC)wglGetProcAddress("glCreateCommandListsNV");
	__glewDeleteCommandListsNV = (PFNGLDELETECOMMANDLISTSNVPROC)wglGetProcAddress("glDeleteCommandListsNV");
	__glewIsCommandListNV = (PFNGLISCOMMANDLISTNVPROC)wglGetProcAddress("glIsCommandListNV");
	__glewListDrawCommandsStatesClientNV = (PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC)wglGetProcAddress("glListDrawCommandsStatesClientNV");
	__glewCommandListSegmentsNV = (PFNGLCOMMANDLISTSEGMENTSNVPROC)wglGetProcAddress("glCommandListSegmentsNV");
	__glewCompileCommandListNV = (PFNGLCOMPILECOMMANDLISTNVPROC)wglGetProcAddress("glCompileCommandListNV");
	__glewCallCommandListNV = (PFNGLCALLCOMMANDLISTNVPROC)wglGetProcAddress("glCallCommandListNV");
	__glewGetCommandHeaderNV = (PFNGLGETCOMMANDHEADERNVPROC)wglGetProcAddress("glGetCommandHeaderNV");
	__glewGetStageIndexNV = (PFNGLGETSTAGEINDEXNVPROC)wglGetProcAddress("glGetStageIndexNV");

	OGLFeatures::NV_command_list = __glewCreateStatesNV != NULL;

	return __glewCreateStatesNV != NULL;
}

_NAME_END

#endif
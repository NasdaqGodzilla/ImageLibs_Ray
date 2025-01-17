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
#include "ogl_types.h"

#if defined(_BUILD_PLATFORM_LINUX) || defined(_BUILD_PLATFORM_APPLE) && defined(_BUILD_OPENGL_ES)
#	include <dlfcn.h>
#endif

_NAME_BEGIN

#ifdef GLEW_MX
#	ifdef _WIN32
WGLEWContext _wglewctx;
#		define wglewGetContext() (&_wglewctx)
#	elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
GLXEWContext _glxewctx;
#	define glxewGetContext() (&_glxewctx)
#	endif
#endif

#if defined(_BUILD_OPENGL_ES)

PFNGLACCUM __glAccum;
PFNGLALPHAFUNC __glAlphaFunc;
PFNGLARETEXTURESRESIDENT __glAreTexturesResident;
PFNGLARRAYELEMENT __glArrayElement;
PFNGLBEGIN __glBegin;
PFNGLBINDTEXTURE __glBindTexture;
PFNGLBITMAP __glBitmap;
PFNGLBLENDFUNC __glBlendFunc;
PFNGLCALLLIST __glCallList;
PFNGLCALLLISTS __glCallLists;
PFNGLCLEAR __glClear;
PFNGLCLEARACCUM __glClearAccum;
PFNGLCLEARCOLOR __glClearColor;
PFNGLCLEARDEPTH __glClearDepth;
PFNGLCLEARINDEX __glClearIndex;
PFNGLCLEARSTENCIL __glClearStencil;
PFNGLCLIPPLANE __glClipPlane;
PFNGLCOLOR3B __glColor3b;
PFNGLCOLOR3BV __glColor3bv;
PFNGLCOLOR3D __glColor3d;
PFNGLCOLOR3DV __glColor3dv;
PFNGLCOLOR3F __glColor3f;
PFNGLCOLOR3FV __glColor3fv;
PFNGLCOLOR3I __glColor3i;
PFNGLCOLOR3IV __glColor3iv;
PFNGLCOLOR3S __glColor3s;
PFNGLCOLOR3SV __glColor3sv;
PFNGLCOLOR3UB __glColor3ub;
PFNGLCOLOR3UBV __glColor3ubv;
PFNGLCOLOR3UI __glColor3ui;
PFNGLCOLOR3UIV __glColor3uiv;
PFNGLCOLOR3US __glColor3us;
PFNGLCOLOR3USV __glColor3usv;
PFNGLCOLOR4B __glColor4b;
PFNGLCOLOR4BV __glColor4bv;
PFNGLCOLOR4D __glColor4d;
PFNGLCOLOR4DV __glColor4dv;
PFNGLCOLOR4F __glColor4f;
PFNGLCOLOR4FV __glColor4fv;
PFNGLCOLOR4I __glColor4i;
PFNGLCOLOR4IV __glColor4iv;
PFNGLCOLOR4S __glColor4s;
PFNGLCOLOR4SV __glColor4sv;
PFNGLCOLOR4UB __glColor4ub;
PFNGLCOLOR4UBV __glColor4ubv;
PFNGLCOLOR4UI __glColor4ui;
PFNGLCOLOR4UIV __glColor4uiv;
PFNGLCOLOR4US __glColor4us;
PFNGLCOLOR4USV __glColor4usv;
PFNGLCOLORMASK __glColorMask;
PFNGLCOLORMATERIAL __glColorMaterial;
PFNGLCOLORPOINTER __glColorPointer;
PFNGLCOPYPIXELS __glCopyPixels;
PFNGLCOPYTEXIMAGE1D __glCopyTexImage1D;
PFNGLCOPYTEXIMAGE2D __glCopyTexImage2D;
PFNGLCOPYTEXSUBIMAGE1D __glCopyTexSubImage1D;
PFNGLCOPYTEXSUBIMAGE2D __glCopyTexSubImage2D;
PFNGLCULLFACE __glCullFace;
PFNGLDELETELISTS __glDeleteLists;
PFNGLDELETETEXTURES __glDeleteTextures;
PFNGLDEPTHFUNC __glDepthFunc;
PFNGLDEPTHMASK __glDepthMask;
PFNGLDEPTHRANGE __glDepthRange;
PFNGLDISABLE __glDisable;
PFNGLDISABLECLIENTSTATE __glDisableClientState;
PFNGLDRAWARRAYS __glDrawArrays;
PFNGLDRAWBUFFER __glDrawBuffer;
PFNGLDRAWELEMENTS __glDrawElements;
PFNGLDRAWPIXELS __glDrawPixels;
PFNGLEDGEFLAG __glEdgeFlag;
PFNGLEDGEFLAGPOINTER __glEdgeFlagPointer;
PFNGLEDGEFLAGV __glEdgeFlagv;
PFNGLENABLE __glEnable;
PFNGLENABLECLIENTSTATE __glEnableClientState;
PFNGLEND __glEnd;
PFNGLENDLIST __glEndList;
PFNGLEVALCOORD1D __glEvalCoord1d;
PFNGLEVALCOORD1DV __glEvalCoord1dv;
PFNGLEVALCOORD1F __glEvalCoord1f;
PFNGLEVALCOORD1FV __glEvalCoord1fv;
PFNGLEVALCOORD2D __glEvalCoord2d;
PFNGLEVALCOORD2DV __glEvalCoord2dv;
PFNGLEVALCOORD2F __glEvalCoord2f;
PFNGLEVALCOORD2FV __glEvalCoord2fv;
PFNGLEVALMESH1 __glEvalMesh1;
PFNGLEVALMESH2 __glEvalMesh2;
PFNGLEVALPOINT1 __glEvalPoint1;
PFNGLEVALPOINT2 __glEvalPoint2;
PFNGLFEEDBACKBUFFER __glFeedbackBuffer;
PFNGLFINISH __glFinish;
PFNGLFLUSH __glFlush;
PFNGLFOGF __glFogf;
PFNGLFOGFV __glFogfv;
PFNGLFOGI __glFogi;
PFNGLFOGIV __glFogiv;
PFNGLFRONTFACE __glFrontFace;
PFNGLFRUSTUM __glFrustum;
PFNGLGENLISTS __glGenLists;
PFNGLGENTEXTURES __glGenTextures;
PFNGLGETBOOLEANV __glGetBooleanv;
PFNGLGETCLIPPLANE __glGetClipPlane;
PFNGLGETDOUBLEV __glGetDoublev;
PFNGLGETERROR __glGetError;
PFNGLGETFLOATV __glGetFloatv;
PFNGLGETINTEGERV __glGetIntegerv;
PFNGLGETLIGHTFV __glGetLightfv;
PFNGLGETLIGHTIV __glGetLightiv;
PFNGLGETMAPDV __glGetMapdv;
PFNGLGETMAPFV __glGetMapfv;
PFNGLGETMAPIV __glGetMapiv;
PFNGLGETMATERIALFV __glGetMaterialfv;
PFNGLGETMATERIALIV __glGetMaterialiv;
PFNGLGETPIXELMAPFV __glGetPixelMapfv;
PFNGLGETPIXELMAPUIV __glGetPixelMapuiv;
PFNGLGETPIXELMAPUSV __glGetPixelMapusv;
PFNGLGETPOINTERV __glGetPointerv;
PFNGLGETPOLYGONSTIPPLE __glGetPolygonStipple;
PFNGLGETSTRING __glGetString;
PFNGLGETTEXENVFV __glGetTexEnvfv;
PFNGLGETTEXENVIV __glGetTexEnviv;
PFNGLGETTEXGENDV __glGetTexGendv;
PFNGLGETTEXGENFV __glGetTexGenfv;
PFNGLGETTEXGENIV __glGetTexGeniv;
PFNGLGETTEXIMAGE __glGetTexImage;
PFNGLGETTEXLEVELPARAMETERFV __glGetTexLevelParameterfv;
PFNGLGETTEXLEVELPARAMETERIV __glGetTexLevelParameteriv;
PFNGLGETTEXPARAMETERFV __glGetTexParameterfv;
PFNGLGETTEXPARAMETERIV __glGetTexParameteriv;
PFNGLHINT __glHint;
PFNGLINDEXMASK __glIndexMask;
PFNGLINDEXPOINTER __glIndexPointer;
PFNGLINDEXD __glIndexd;
PFNGLINDEXDV __glIndexdv;
PFNGLINDEXF __glIndexf;
PFNGLINDEXFV __glIndexfv;
PFNGLINDEXI __glIndexi;
PFNGLINDEXIV __glIndexiv;
PFNGLINDEXS __glIndexs;
PFNGLINDEXSV __glIndexsv;
PFNGLINDEXUB __glIndexub;
PFNGLINDEXUBV __glIndexubv;
PFNGLINITNAMES __glInitNames;
PFNGLINTERLEAVEDARRAYS __glInterleavedArrays;
PFNGLISENABLED __glIsEnabled;
PFNGLISLIST __glIsList;
PFNGLISTEXTURE __glIsTexture;
PFNGLLIGHTMODELF __glLightModelf;
PFNGLLIGHTMODELFV __glLightModelfv;
PFNGLLIGHTMODELI __glLightModeli;
PFNGLLIGHTMODELIV __glLightModeliv;
PFNGLLIGHTF __glLightf;
PFNGLLIGHTFV __glLightfv;
PFNGLLIGHTI __glLighti;
PFNGLLIGHTIV __glLightiv;
PFNGLLINESTIPPLE __glLineStipple;
PFNGLLINEWIDTH __glLineWidth;
PFNGLLISTBASE __glListBase;
PFNGLLOADIDENTITY __glLoadIdentity;
PFNGLLOADMATRIXD __glLoadMatrixd;
PFNGLLOADMATRIXF __glLoadMatrixf;
PFNGLLOADNAME __glLoadName;
PFNGLLOGICOP __glLogicOp;
PFNGLMAP1D __glMap1d;
PFNGLMAP1F __glMap1f;
PFNGLMAP2D __glMap2d;
PFNGLMAP2F __glMap2f;
PFNGLMAPGRID1D __glMapGrid1d;
PFNGLMAPGRID1F __glMapGrid1f;
PFNGLMAPGRID2D __glMapGrid2d;
PFNGLMAPGRID2F __glMapGrid2f;
PFNGLMATERIALF __glMaterialf;
PFNGLMATERIALFV __glMaterialfv;
PFNGLMATERIALI __glMateriali;
PFNGLMATERIALIV __glMaterialiv;
PFNGLMATRIXMODE __glMatrixMode;
PFNGLMULTMATRIXD __glMultMatrixd;
PFNGLMULTMATRIXF __glMultMatrixf;
PFNGLNEWLIST __glNewList;
PFNGLNORMAL3B __glNormal3b;
PFNGLNORMAL3BV __glNormal3bv;
PFNGLNORMAL3D __glNormal3d;
PFNGLNORMAL3DV __glNormal3dv;
PFNGLNORMAL3F __glNormal3f;
PFNGLNORMAL3FV __glNormal3fv;
PFNGLNORMAL3I __glNormal3i;
PFNGLNORMAL3IV __glNormal3iv;
PFNGLNORMAL3S __glNormal3s;
PFNGLNORMAL3SV __glNormal3sv;
PFNGLNORMALPOINTER __glNormalPointer;
PFNGLORTHO __glOrtho;
PFNGLPASSTHROUGH __glPassThrough;
PFNGLPIXELMAPFV __glPixelMapfv;
PFNGLPIXELMAPUIV __glPixelMapuiv;
PFNGLPIXELMAPUSV __glPixelMapusv;
PFNGLPIXELSTOREF __glPixelStoref;
PFNGLPIXELSTOREI __glPixelStorei;
PFNGLPIXELTRANSFERF __glPixelTransferf;
PFNGLPIXELTRANSFERI __glPixelTransferi;
PFNGLPIXELZOOM __glPixelZoom;
PFNGLPOINTSIZE __glPointSize;
PFNGLPOLYGONMODE __glPolygonMode;
PFNGLPOLYGONOFFSET __glPolygonOffset;
PFNGLPOLYGONSTIPPLE __glPolygonStipple;
PFNGLPOPATTRIB __glPopAttrib;
PFNGLPOPCLIENTATTRIB __glPopClientAttrib;
PFNGLPOPMATRIX __glPopMatrix;
PFNGLPOPNAME __glPopName;
PFNGLPRIORITIZETEXTURES __glPrioritizeTextures;
PFNGLPUSHATTRIB __glPushAttrib;
PFNGLPUSHCLIENTATTRIB __glPushClientAttrib;
PFNGLPUSHMATRIX __glPushMatrix;
PFNGLPUSHNAME __glPushName;
PFNGLRASTERPOS2D __glRasterPos2d;
PFNGLRASTERPOS2DV __glRasterPos2dv;
PFNGLRASTERPOS2F __glRasterPos2f;
PFNGLRASTERPOS2FV __glRasterPos2fv;
PFNGLRASTERPOS2I __glRasterPos2i;
PFNGLRASTERPOS2IV __glRasterPos2iv;
PFNGLRASTERPOS2S __glRasterPos2s;
PFNGLRASTERPOS2SV __glRasterPos2sv;
PFNGLRASTERPOS3D __glRasterPos3d;
PFNGLRASTERPOS3DV __glRasterPos3dv;
PFNGLRASTERPOS3F __glRasterPos3f;
PFNGLRASTERPOS3FV __glRasterPos3fv;
PFNGLRASTERPOS3I __glRasterPos3i;
PFNGLRASTERPOS3IV __glRasterPos3iv;
PFNGLRASTERPOS3S __glRasterPos3s;
PFNGLRASTERPOS3SV __glRasterPos3sv;
PFNGLRASTERPOS4D __glRasterPos4d;
PFNGLRASTERPOS4DV __glRasterPos4dv;
PFNGLRASTERPOS4F __glRasterPos4f;
PFNGLRASTERPOS4FV __glRasterPos4fv;
PFNGLRASTERPOS4I __glRasterPos4i;
PFNGLRASTERPOS4IV __glRasterPos4iv;
PFNGLRASTERPOS4S __glRasterPos4s;
PFNGLRASTERPOS4SV __glRasterPos4sv;
PFNGLREADBUFFER __glReadBuffer;
PFNGLREADPIXELS __glReadPixels;
PFNGLRECTD __glRectd;
PFNGLRECTDV __glRectdv;
PFNGLRECTF __glRectf;
PFNGLRECTFV __glRectfv;
PFNGLRECTI __glRecti;
PFNGLRECTIV __glRectiv;
PFNGLRECTS __glRects;
PFNGLRECTSV __glRectsv;
PFNGLRENDERMODE __glRenderMode;
PFNGLROTATED __glRotated;
PFNGLROTATEF __glRotatef;
PFNGLSCALED __glScaled;
PFNGLSCALEF __glScalef;
PFNGLSCISSOR __glScissor;
PFNGLSELECTBUFFER __glSelectBuffer;
PFNGLSHADEMODEL __glShadeModel;
PFNGLSTENCILFUNC __glStencilFunc;
PFNGLSTENCILMASK __glStencilMask;
PFNGLSTENCILOP __glStencilOp;
PFNGLTEXCOORD1D __glTexCoord1d;
PFNGLTEXCOORD1DV __glTexCoord1dv;
PFNGLTEXCOORD1F __glTexCoord1f;
PFNGLTEXCOORD1FV __glTexCoord1fv;
PFNGLTEXCOORD1I __glTexCoord1i;
PFNGLTEXCOORD1IV __glTexCoord1iv;
PFNGLTEXCOORD1S __glTexCoord1s;
PFNGLTEXCOORD1SV __glTexCoord1sv;
PFNGLTEXCOORD2D __glTexCoord2d;
PFNGLTEXCOORD2DV __glTexCoord2dv;
PFNGLTEXCOORD2F __glTexCoord2f;
PFNGLTEXCOORD2FV __glTexCoord2fv;
PFNGLTEXCOORD2I __glTexCoord2i;
PFNGLTEXCOORD2IV __glTexCoord2iv;
PFNGLTEXCOORD2S __glTexCoord2s;
PFNGLTEXCOORD2SV __glTexCoord2sv;
PFNGLTEXCOORD3D __glTexCoord3d;
PFNGLTEXCOORD3DV __glTexCoord3dv;
PFNGLTEXCOORD3F __glTexCoord3f;
PFNGLTEXCOORD3FV __glTexCoord3fv;
PFNGLTEXCOORD3I __glTexCoord3i;
PFNGLTEXCOORD3IV __glTexCoord3iv;
PFNGLTEXCOORD3S __glTexCoord3s;
PFNGLTEXCOORD3SV __glTexCoord3sv;
PFNGLTEXCOORD4D __glTexCoord4d;
PFNGLTEXCOORD4DV __glTexCoord4dv;
PFNGLTEXCOORD4F __glTexCoord4f;
PFNGLTEXCOORD4FV __glTexCoord4fv;
PFNGLTEXCOORD4I __glTexCoord4i;
PFNGLTEXCOORD4IV __glTexCoord4iv;
PFNGLTEXCOORD4S __glTexCoord4s;
PFNGLTEXCOORD4SV __glTexCoord4sv;
PFNGLTEXCOORDPOINTER __glTexCoordPointer;
PFNGLTEXENVF __glTexEnvf;
PFNGLTEXENVFV __glTexEnvfv;
PFNGLTEXENVI __glTexEnvi;
PFNGLTEXENVIV __glTexEnviv;
PFNGLTEXGEND __glTexGend;
PFNGLTEXGENDV __glTexGendv;
PFNGLTEXGENF __glTexGenf;
PFNGLTEXGENFV __glTexGenfv;
PFNGLTEXGENI __glTexGeni;
PFNGLTEXGENIV __glTexGeniv;
PFNGLTEXIMAGE1D __glTexImage1D;
PFNGLTEXIMAGE2D __glTexImage2D;
PFNGLTEXPARAMETERF __glTexParameterf;
PFNGLTEXPARAMETERFV __glTexParameterfv;
PFNGLTEXPARAMETERI __glTexParameteri;
PFNGLTEXPARAMETERIV __glTexParameteriv;
PFNGLTEXSUBIMAGE1D __glTexSubImage1D;
PFNGLTEXSUBIMAGE2D __glTexSubImage2D;
PFNGLTRANSLATED __glTranslated;
PFNGLTRANSLATEF __glTranslatef;
PFNGLVERTEX2D __glVertex2d;
PFNGLVERTEX2DV __glVertex2dv;
PFNGLVERTEX2F __glVertex2f;
PFNGLVERTEX2FV __glVertex2fv;
PFNGLVERTEX2I __glVertex2i;
PFNGLVERTEX2IV __glVertex2iv;
PFNGLVERTEX2S __glVertex2s;
PFNGLVERTEX2SV __glVertex2sv;
PFNGLVERTEX3D __glVertex3d;
PFNGLVERTEX3DV __glVertex3dv;
PFNGLVERTEX3F __glVertex3f;
PFNGLVERTEX3FV __glVertex3fv;
PFNGLVERTEX3I __glVertex3i;
PFNGLVERTEX3IV __glVertex3iv;
PFNGLVERTEX3S __glVertex3s;
PFNGLVERTEX3SV __glVertex3sv;
PFNGLVERTEX4D __glVertex4d;
PFNGLVERTEX4DV __glVertex4dv;
PFNGLVERTEX4F __glVertex4f;
PFNGLVERTEX4FV __glVertex4fv;
PFNGLVERTEX4I __glVertex4i;
PFNGLVERTEX4IV __glVertex4iv;
PFNGLVERTEX4S __glVertex4s;
PFNGLVERTEX4SV __glVertex4sv;
PFNGLVERTEXPOINTER __glVertexPointer;
PFNGLVIEWPORT __glViewport;

#endif

#if defined(_BUILD_PLATFORM_WINDOWS)
PFNWGLSWAPINTERVALEXTPROC __wglSwapIntervalEXT;
PFNWGLCREATECONTEXTATTRIBSARBPROC   __wglCreateContextAttribsARB;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC __wglGetPixelFormatAttribivARB;
#elif defined(_BUILD_OPENGL_ES)
#	define GetProcAddress dlsym
#endif

bool initGLExtenstion() noexcept
{
	static thread_local bool initGLExtention = false;
	if (initGLExtention)
		return true;

	if (::glewInit() != GLEW_OK)
		return false;

#if defined(GLEW_MX)
#	if	defined(_BUILD_PLATFORM_WINDOWS)
	if (wglewInit() != GLEW_OK)
		return false;
#	elif defined(_BUILD_PLATFORM_LINUX)
	if (glxewInit() != GLEW_OK)
		return false;
#	endif
#endif

#if defined(_BUILD_PLATFORM_WINDOWS) && defined(_BUILD_OPENGL_ES)
	HMODULE opengl32 = ::LoadLibrary("OpenGL32");
	if (!opengl32)
	{
		this->getDevice()->downcast<OGLDevice>()->message("OpenGL dynamic library is not found.");
		return false;
	}
#elif defined(_BUILD_PLATFORM_LINUX) && defined(_BUILD_OPENGL_ES)
	void* opengl32 = ::dlopen("/usr/lib/x86_64-linux-gnu/libGL.so.1", RTLD_NOW);
	if (!opengl32)
	{
		this->getDevice()->downcast<OGLDevice>()->message("OpenGL dynamic library is not found.");
		return false;
	}
#elif defined(_BUILD_PLATFORM_APPLE) && defined(_BUILD_OPENGL_ES)
	void* opengl32 = ::dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_NOW);
	if (!opengl32)
	{
		this->getDevice()->downcast<OGLDevice>()->message("OpenGL dynamic library is not found.");
		return false;
	}
#endif

#if defined(_BUILD_OPENGL_ES)
	__glAccum = (PFNGLACCUM)::GetProcAddress(opengl32, "glAccum");
	__glAlphaFunc = (PFNGLALPHAFUNC)::GetProcAddress(opengl32, "glAlphaFunc");
	__glAreTexturesResident = (PFNGLARETEXTURESRESIDENT)::GetProcAddress(opengl32, "glAreTexturesResident");
	__glArrayElement = (PFNGLARRAYELEMENT)::GetProcAddress(opengl32, "glArrayElement");
	__glBegin = (PFNGLBEGIN)::GetProcAddress(opengl32, "glBegin");
	__glBindTexture = (PFNGLBINDTEXTURE)::GetProcAddress(opengl32, "glBindTexture");
	__glBitmap = (PFNGLBITMAP)::GetProcAddress(opengl32, "glBitmap");
	__glBlendFunc = (PFNGLBLENDFUNC)::GetProcAddress(opengl32, "glBlendFunc");
	__glCallList = (PFNGLCALLLIST)::GetProcAddress(opengl32, "glCallList");
	__glCallLists = (PFNGLCALLLISTS)::GetProcAddress(opengl32, "glCallLists");
	__glClear = (PFNGLCLEAR)::GetProcAddress(opengl32, "glClear");
	__glClearAccum = (PFNGLCLEARACCUM)::GetProcAddress(opengl32, "glClearAccum");
	__glClearColor = (PFNGLCLEARCOLOR)::GetProcAddress(opengl32, "glClearColor");
	__glClearDepth = (PFNGLCLEARDEPTH)::GetProcAddress(opengl32, "glClearDepth");
	__glClearIndex = (PFNGLCLEARINDEX)::GetProcAddress(opengl32, "glClearIndex");
	__glClearStencil = (PFNGLCLEARSTENCIL)::GetProcAddress(opengl32, "glClearStencil");
	__glClipPlane = (PFNGLCLIPPLANE)::GetProcAddress(opengl32, "glClipPlane");
	__glColor3b = (PFNGLCOLOR3B)::GetProcAddress(opengl32, "glColor3b");
	__glColor3bv = (PFNGLCOLOR3BV)::GetProcAddress(opengl32, "glColor3bv");
	__glColor3d = (PFNGLCOLOR3D)::GetProcAddress(opengl32, "glColor3d");
	__glColor3dv = (PFNGLCOLOR3DV)::GetProcAddress(opengl32, "glColor3dv");
	__glColor3f = (PFNGLCOLOR3F)::GetProcAddress(opengl32, "glColor3f");
	__glColor3fv = (PFNGLCOLOR3FV)::GetProcAddress(opengl32, "glColor3fv");
	__glColor3i = (PFNGLCOLOR3I)::GetProcAddress(opengl32, "glColor3i");
	__glColor3iv = (PFNGLCOLOR3IV)::GetProcAddress(opengl32, "glColor3iv");
	__glColor3s = (PFNGLCOLOR3S)::GetProcAddress(opengl32, "glColor3s");
	__glColor3sv = (PFNGLCOLOR3SV)::GetProcAddress(opengl32, "glColor3sv");
	__glColor3ub = (PFNGLCOLOR3UB)::GetProcAddress(opengl32, "glColor3ub");
	__glColor3ubv = (PFNGLCOLOR3UBV)::GetProcAddress(opengl32, "glColor3ubv");
	__glColor3ui = (PFNGLCOLOR3UI)::GetProcAddress(opengl32, "glColor3ui");
	__glColor3uiv = (PFNGLCOLOR3UIV)::GetProcAddress(opengl32, "glColor3uiv");
	__glColor3us = (PFNGLCOLOR3US)::GetProcAddress(opengl32, "glColor3us");
	__glColor3usv = (PFNGLCOLOR3USV)::GetProcAddress(opengl32, "glColor3usv");
	__glColor4b = (PFNGLCOLOR4B)::GetProcAddress(opengl32, "glColor4b");
	__glColor4bv = (PFNGLCOLOR4BV)::GetProcAddress(opengl32, "glColor4bv");
	__glColor4d = (PFNGLCOLOR4D)::GetProcAddress(opengl32, "glColor4d");
	__glColor4dv = (PFNGLCOLOR4DV)::GetProcAddress(opengl32, "glColor4dv");
	__glColor4f = (PFNGLCOLOR4F)::GetProcAddress(opengl32, "glColor4f");
	__glColor4fv = (PFNGLCOLOR4FV)::GetProcAddress(opengl32, "glColor4fv");
	__glColor4i = (PFNGLCOLOR4I)::GetProcAddress(opengl32, "glColor4i");
	__glColor4iv = (PFNGLCOLOR4IV)::GetProcAddress(opengl32, "glColor4iv");
	__glColor4s = (PFNGLCOLOR4S)::GetProcAddress(opengl32, "glColor4s");
	__glColor4sv = (PFNGLCOLOR4SV)::GetProcAddress(opengl32, "glColor4sv");
	__glColor4ub = (PFNGLCOLOR4UB)::GetProcAddress(opengl32, "glColor4ub");
	__glColor4ubv = (PFNGLCOLOR4UBV)::GetProcAddress(opengl32, "glColor4ubv");
	__glColor4ui = (PFNGLCOLOR4UI)::GetProcAddress(opengl32, "glColor4ui");
	__glColor4uiv = (PFNGLCOLOR4UIV)::GetProcAddress(opengl32, "glColor4uiv");
	__glColor4us = (PFNGLCOLOR4US)::GetProcAddress(opengl32, "glColor4us");
	__glColor4usv = (PFNGLCOLOR4USV)::GetProcAddress(opengl32, "glColor4usv");
	__glColorMask = (PFNGLCOLORMASK)::GetProcAddress(opengl32, "glColorMask");
	__glColorMaterial = (PFNGLCOLORMATERIAL)::GetProcAddress(opengl32, "glColorMaterial");
	__glColorPointer = (PFNGLCOLORPOINTER)::GetProcAddress(opengl32, "glColorPointer");
	__glCopyPixels = (PFNGLCOPYPIXELS)::GetProcAddress(opengl32, "glCopyPixels");
	__glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1D)::GetProcAddress(opengl32, "glCopyTexImage1D");
	__glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2D)::GetProcAddress(opengl32, "glCopyTexImage2D");
	__glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1D)::GetProcAddress(opengl32, "glCopyTexSubImage1D");
	__glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2D)::GetProcAddress(opengl32, "glCopyTexSubImage2D");
	__glCullFace = (PFNGLCULLFACE)::GetProcAddress(opengl32, "glCullFace");
	__glDeleteLists = (PFNGLDELETELISTS)::GetProcAddress(opengl32, "glDeleteLists");
	__glDeleteTextures = (PFNGLDELETETEXTURES)::GetProcAddress(opengl32, "glDeleteTextures");
	__glDepthFunc = (PFNGLDEPTHFUNC)::GetProcAddress(opengl32, "glDepthFunc");
	__glDepthMask = (PFNGLDEPTHMASK)::GetProcAddress(opengl32, "glDepthMask");
	__glDepthRange = (PFNGLDEPTHRANGE)::GetProcAddress(opengl32, "glDepthRange");
	__glDisable = (PFNGLDISABLE)::GetProcAddress(opengl32, "glDisable");
	__glDisableClientState = (PFNGLDISABLECLIENTSTATE)::GetProcAddress(opengl32, "glDisableClientState");
	__glDrawArrays = (PFNGLDRAWARRAYS)::GetProcAddress(opengl32, "glDrawArrays");
	__glDrawBuffer = (PFNGLDRAWBUFFER)::GetProcAddress(opengl32, "glDrawBuffer");
	__glDrawElements = (PFNGLDRAWELEMENTS)::GetProcAddress(opengl32, "glDrawElements");
	__glDrawPixels = (PFNGLDRAWPIXELS)::GetProcAddress(opengl32, "glDrawPixels");
	__glEdgeFlag = (PFNGLEDGEFLAG)::GetProcAddress(opengl32, "glEdgeFlag");
	__glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTER)::GetProcAddress(opengl32, "glEdgeFlagPointer");
	__glEdgeFlagv = (PFNGLEDGEFLAGV)::GetProcAddress(opengl32, "glEdgeFlagv");
	__glEnable = (PFNGLENABLE)::GetProcAddress(opengl32, "glEnable");
	__glEnableClientState = (PFNGLENABLECLIENTSTATE)::GetProcAddress(opengl32, "glEnableClientState");
	__glEnd = (PFNGLEND)::GetProcAddress(opengl32, "glEnd");
	__glEndList = (PFNGLENDLIST)::GetProcAddress(opengl32, "glEndList");
	__glEvalCoord1d = (PFNGLEVALCOORD1D)::GetProcAddress(opengl32, "glEvalCoord1d");
	__glEvalCoord1dv = (PFNGLEVALCOORD1DV)::GetProcAddress(opengl32, "glEvalCoord1dv");
	__glEvalCoord1f = (PFNGLEVALCOORD1F)::GetProcAddress(opengl32, "glEvalCoord1f");
	__glEvalCoord1fv = (PFNGLEVALCOORD1FV)::GetProcAddress(opengl32, "glEvalCoord1fv");
	__glEvalCoord2d = (PFNGLEVALCOORD2D)::GetProcAddress(opengl32, "glEvalCoord2d");
	__glEvalCoord2dv = (PFNGLEVALCOORD2DV)::GetProcAddress(opengl32, "glEvalCoord2dv");
	__glEvalCoord2f = (PFNGLEVALCOORD2F)::GetProcAddress(opengl32, "glEvalCoord2f");
	__glEvalCoord2fv = (PFNGLEVALCOORD2FV)::GetProcAddress(opengl32, "glEvalCoord2fv");
	__glEvalMesh1 = (PFNGLEVALMESH1)::GetProcAddress(opengl32, "glEvalMesh1");
	__glEvalMesh2 = (PFNGLEVALMESH2)::GetProcAddress(opengl32, "glEvalMesh2");
	__glEvalPoint1 = (PFNGLEVALPOINT1)::GetProcAddress(opengl32, "glEvalPoint1");
	__glEvalPoint2 = (PFNGLEVALPOINT2)::GetProcAddress(opengl32, "glEvalPoint2");
	__glFeedbackBuffer = (PFNGLFEEDBACKBUFFER)::GetProcAddress(opengl32, "glFeedbackBuffer");
	__glFinish = (PFNGLFINISH)::GetProcAddress(opengl32, "glFinish");
	__glFlush = (PFNGLFLUSH)::GetProcAddress(opengl32, "glFlush");
	__glFogf = (PFNGLFOGF)::GetProcAddress(opengl32, "glFogf");
	__glFogfv = (PFNGLFOGFV)::GetProcAddress(opengl32, "glFogfv");
	__glFogi = (PFNGLFOGI)::GetProcAddress(opengl32, "glFogi");
	__glFogiv = (PFNGLFOGIV)::GetProcAddress(opengl32, "glFogiv");
	__glFrontFace = (PFNGLFRONTFACE)::GetProcAddress(opengl32, "glFrontFace");
	__glFrustum = (PFNGLFRUSTUM)::GetProcAddress(opengl32, "glFrustum");
	__glGenLists = (PFNGLGENLISTS)::GetProcAddress(opengl32, "glGenLists");
	__glGenTextures = (PFNGLGENTEXTURES)::GetProcAddress(opengl32, "glGenTextures");
	__glGetBooleanv = (PFNGLGETBOOLEANV)::GetProcAddress(opengl32, "glGetBooleanv");
	__glGetClipPlane = (PFNGLGETCLIPPLANE)::GetProcAddress(opengl32, "glGetClipPlane");
	__glGetDoublev = (PFNGLGETDOUBLEV)::GetProcAddress(opengl32, "glGetDoublev");
	__glGetError = (PFNGLGETERROR)::GetProcAddress(opengl32, "glGetError");
	__glGetFloatv = (PFNGLGETFLOATV)::GetProcAddress(opengl32, "glGetFloatv");
	__glGetIntegerv = (PFNGLGETINTEGERV)::GetProcAddress(opengl32, "glGetIntegerv");
	__glGetLightfv = (PFNGLGETLIGHTFV)::GetProcAddress(opengl32, "glGetLightfv");
	__glGetLightiv = (PFNGLGETLIGHTIV)::GetProcAddress(opengl32, "glGetLightiv");
	__glGetMapdv = (PFNGLGETMAPDV)::GetProcAddress(opengl32, "glGetMapdv");
	__glGetMapfv = (PFNGLGETMAPFV)::GetProcAddress(opengl32, "glGetMapfv");
	__glGetMapiv = (PFNGLGETMAPIV)::GetProcAddress(opengl32, "glGetMapiv");
	__glGetMaterialfv = (PFNGLGETMATERIALFV)::GetProcAddress(opengl32, "glGetMaterialfv");
	__glGetMaterialiv = (PFNGLGETMATERIALIV)::GetProcAddress(opengl32, "glGetMaterialiv");
	__glGetPixelMapfv = (PFNGLGETPIXELMAPFV)::GetProcAddress(opengl32, "glGetPixelMapfv");
	__glGetPixelMapuiv = (PFNGLGETPIXELMAPUIV)::GetProcAddress(opengl32, "glGetPixelMapuiv");
	__glGetPixelMapusv = (PFNGLGETPIXELMAPUSV)::GetProcAddress(opengl32, "glGetPixelMapusv");
	__glGetPointerv = (PFNGLGETPOINTERV)::GetProcAddress(opengl32, "glGetPointerv");
	__glGetPolygonStipple = (PFNGLGETPOLYGONSTIPPLE)::GetProcAddress(opengl32, "glGetPolygonStipple");
	__glGetString = (PFNGLGETSTRING)::GetProcAddress(opengl32, "glGetString");
	__glGetTexEnvfv = (PFNGLGETTEXENVFV)::GetProcAddress(opengl32, "glGetTexEnvfv");
	__glGetTexEnviv = (PFNGLGETTEXENVIV)::GetProcAddress(opengl32, "glGetTexEnviv");
	__glGetTexGendv = (PFNGLGETTEXGENDV)::GetProcAddress(opengl32, "glGetTexGendv");
	__glGetTexGenfv = (PFNGLGETTEXGENFV)::GetProcAddress(opengl32, "glGetTexGenfv");
	__glGetTexGeniv = (PFNGLGETTEXGENIV)::GetProcAddress(opengl32, "glGetTexGeniv");
	__glGetTexImage = (PFNGLGETTEXIMAGE)::GetProcAddress(opengl32, "glGetTexImage");
	__glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFV)::GetProcAddress(opengl32, "glGetTexLevelParameterfv");
	__glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIV)::GetProcAddress(opengl32, "glGetTexLevelParameteriv");
	__glGetTexParameterfv = (PFNGLGETTEXPARAMETERFV)::GetProcAddress(opengl32, "glGetTexParameterfv");
	__glGetTexParameteriv = (PFNGLGETTEXPARAMETERIV)::GetProcAddress(opengl32, "glGetTexParameteriv");
	__glHint = (PFNGLHINT)::GetProcAddress(opengl32, "glHint");
	__glIndexMask = (PFNGLINDEXMASK)::GetProcAddress(opengl32, "glIndexMask");
	__glIndexPointer = (PFNGLINDEXPOINTER)::GetProcAddress(opengl32, "glIndexPointer");
	__glIndexd = (PFNGLINDEXD)::GetProcAddress(opengl32, "glIndexd");
	__glIndexdv = (PFNGLINDEXDV)::GetProcAddress(opengl32, "glIndexdv");
	__glIndexf = (PFNGLINDEXF)::GetProcAddress(opengl32, "glIndexf");
	__glIndexfv = (PFNGLINDEXFV)::GetProcAddress(opengl32, "glIndexfv");
	__glIndexi = (PFNGLINDEXI)::GetProcAddress(opengl32, "glIndexi");
	__glIndexiv = (PFNGLINDEXIV)::GetProcAddress(opengl32, "glIndexiv");
	__glIndexs = (PFNGLINDEXS)::GetProcAddress(opengl32, "glIndexs");
	__glIndexsv = (PFNGLINDEXSV)::GetProcAddress(opengl32, "glIndexsv");
	__glIndexub = (PFNGLINDEXUB)::GetProcAddress(opengl32, "glIndexub");
	__glIndexubv = (PFNGLINDEXUBV)::GetProcAddress(opengl32, "glIndexubv");
	__glInitNames = (PFNGLINITNAMES)::GetProcAddress(opengl32, "glInitNames");
	__glInterleavedArrays = (PFNGLINTERLEAVEDARRAYS)::GetProcAddress(opengl32, "glInterleavedArrays");
	__glIsEnabled = (PFNGLISENABLED)::GetProcAddress(opengl32, "glIsEnabled");
	__glIsList = (PFNGLISLIST)::GetProcAddress(opengl32, "glIsList");
	__glIsTexture = (PFNGLISTEXTURE)::GetProcAddress(opengl32, "glIsTexture");
	__glLightModelf = (PFNGLLIGHTMODELF)::GetProcAddress(opengl32, "glLightModelf");
	__glLightModelfv = (PFNGLLIGHTMODELFV)::GetProcAddress(opengl32, "glLightModelfv");
	__glLightModeli = (PFNGLLIGHTMODELI)::GetProcAddress(opengl32, "glLightModeli");
	__glLightModeliv = (PFNGLLIGHTMODELIV)::GetProcAddress(opengl32, "glLightModeliv");
	__glLightf = (PFNGLLIGHTF)::GetProcAddress(opengl32, "glLightf");
	__glLightfv = (PFNGLLIGHTFV)::GetProcAddress(opengl32, "glLightfv");
	__glLighti = (PFNGLLIGHTI)::GetProcAddress(opengl32, "glLighti");
	__glLightiv = (PFNGLLIGHTIV)::GetProcAddress(opengl32, "glLightiv");
	__glLineStipple = (PFNGLLINESTIPPLE)::GetProcAddress(opengl32, "glLineStipple");
	__glLineWidth = (PFNGLLINEWIDTH)::GetProcAddress(opengl32, "glLineWidth");
	__glListBase = (PFNGLLISTBASE)::GetProcAddress(opengl32, "glListBase");
	__glLoadIdentity = (PFNGLLOADIDENTITY)::GetProcAddress(opengl32, "glLoadIdentity");
	__glLoadMatrixd = (PFNGLLOADMATRIXD)::GetProcAddress(opengl32, "glLoadMatrixd");
	__glLoadMatrixf = (PFNGLLOADMATRIXF)::GetProcAddress(opengl32, "glLoadMatrixf");
	__glLoadName = (PFNGLLOADNAME)::GetProcAddress(opengl32, "glLoadName");
	__glLogicOp = (PFNGLLOGICOP)::GetProcAddress(opengl32, "glLogicOp");
	__glMap1d = (PFNGLMAP1D)::GetProcAddress(opengl32, "glMap1d");
	__glMap1f = (PFNGLMAP1F)::GetProcAddress(opengl32, "glMap1f");
	__glMap2d = (PFNGLMAP2D)::GetProcAddress(opengl32, "glMap2d");
	__glMap2f = (PFNGLMAP2F)::GetProcAddress(opengl32, "glMap2f");
	__glMapGrid1d = (PFNGLMAPGRID1D)::GetProcAddress(opengl32, "glMapGrid1d");
	__glMapGrid1f = (PFNGLMAPGRID1F)::GetProcAddress(opengl32, "glMapGrid1f");
	__glMapGrid2d = (PFNGLMAPGRID2D)::GetProcAddress(opengl32, "glMapGrid2d");
	__glMapGrid2f = (PFNGLMAPGRID2F)::GetProcAddress(opengl32, "glMapGrid2f");
	__glMaterialf = (PFNGLMATERIALF)::GetProcAddress(opengl32, "glMaterialf");
	__glMaterialfv = (PFNGLMATERIALFV)::GetProcAddress(opengl32, "glMaterialfv");
	__glMateriali = (PFNGLMATERIALI)::GetProcAddress(opengl32, "glMateriali");
	__glMaterialiv = (PFNGLMATERIALIV)::GetProcAddress(opengl32, "glMaterialiv");
	__glMatrixMode = (PFNGLMATRIXMODE)::GetProcAddress(opengl32, "glMatrixMode");
	__glMultMatrixd = (PFNGLMULTMATRIXD)::GetProcAddress(opengl32, "glMultMatrixd");
	__glMultMatrixf = (PFNGLMULTMATRIXF)::GetProcAddress(opengl32, "glMultMatrixf");
	__glNewList = (PFNGLNEWLIST)::GetProcAddress(opengl32, "glNewList");
	__glNormal3b = (PFNGLNORMAL3B)::GetProcAddress(opengl32, "glNormal3b");
	__glNormal3bv = (PFNGLNORMAL3BV)::GetProcAddress(opengl32, "glNormal3bv");
	__glNormal3d = (PFNGLNORMAL3D)::GetProcAddress(opengl32, "glNormal3d");
	__glNormal3dv = (PFNGLNORMAL3DV)::GetProcAddress(opengl32, "glNormal3dv");
	__glNormal3f = (PFNGLNORMAL3F)::GetProcAddress(opengl32, "glNormal3f");
	__glNormal3fv = (PFNGLNORMAL3FV)::GetProcAddress(opengl32, "glNormal3fv");
	__glNormal3i = (PFNGLNORMAL3I)::GetProcAddress(opengl32, "glNormal3i");
	__glNormal3iv = (PFNGLNORMAL3IV)::GetProcAddress(opengl32, "glNormal3iv");
	__glNormal3s = (PFNGLNORMAL3S)::GetProcAddress(opengl32, "glNormal3s");
	__glNormal3sv = (PFNGLNORMAL3SV)::GetProcAddress(opengl32, "glNormal3sv");
	__glNormalPointer = (PFNGLNORMALPOINTER)::GetProcAddress(opengl32, "glNormalPointer");
	__glOrtho = (PFNGLORTHO)::GetProcAddress(opengl32, "glOrtho");
	__glPassThrough = (PFNGLPASSTHROUGH)::GetProcAddress(opengl32, "glPassThrough");
	__glPixelMapfv = (PFNGLPIXELMAPFV)::GetProcAddress(opengl32, "glPixelMapfv");
	__glPixelMapuiv = (PFNGLPIXELMAPUIV)::GetProcAddress(opengl32, "glPixelMapuiv");
	__glPixelMapusv = (PFNGLPIXELMAPUSV)::GetProcAddress(opengl32, "glPixelMapusv");
	__glPixelStoref = (PFNGLPIXELSTOREF)::GetProcAddress(opengl32, "glPixelStoref");
	__glPixelStorei = (PFNGLPIXELSTOREI)::GetProcAddress(opengl32, "glPixelStorei");
	__glPixelTransferf = (PFNGLPIXELTRANSFERF)::GetProcAddress(opengl32, "glPixelTransferf");
	__glPixelTransferi = (PFNGLPIXELTRANSFERI)::GetProcAddress(opengl32, "glPixelTransferi");
	__glPixelZoom = (PFNGLPIXELZOOM)::GetProcAddress(opengl32, "glPixelZoom");
	__glPointSize = (PFNGLPOINTSIZE)::GetProcAddress(opengl32, "glPointSize");
	__glPolygonMode = (PFNGLPOLYGONMODE)::GetProcAddress(opengl32, "glPolygonMode");
	__glPolygonOffset = (PFNGLPOLYGONOFFSET)::GetProcAddress(opengl32, "glPolygonOffset");
	__glPolygonStipple = (PFNGLPOLYGONSTIPPLE)::GetProcAddress(opengl32, "glPolygonStipple");
	__glPopAttrib = (PFNGLPOPATTRIB)::GetProcAddress(opengl32, "glPopAttrib");
	__glPopClientAttrib = (PFNGLPOPCLIENTATTRIB)::GetProcAddress(opengl32, "glPopClientAttrib");
	__glPopMatrix = (PFNGLPOPMATRIX)::GetProcAddress(opengl32, "glPopMatrix");
	__glPopName = (PFNGLPOPNAME)::GetProcAddress(opengl32, "glPopName");
	__glPrioritizeTextures = (PFNGLPRIORITIZETEXTURES)::GetProcAddress(opengl32, "glPrioritizeTextures");
	__glPushAttrib = (PFNGLPUSHATTRIB)::GetProcAddress(opengl32, "glPushAttrib");
	__glPushClientAttrib = (PFNGLPUSHCLIENTATTRIB)::GetProcAddress(opengl32, "glPushClientAttrib");
	__glPushMatrix = (PFNGLPUSHMATRIX)::GetProcAddress(opengl32, "glPushMatrix");
	__glPushName = (PFNGLPUSHNAME)::GetProcAddress(opengl32, "glPushName");
	__glRasterPos2d = (PFNGLRASTERPOS2D)::GetProcAddress(opengl32, "glRasterPos2d");
	__glRasterPos2dv = (PFNGLRASTERPOS2DV)::GetProcAddress(opengl32, "glRasterPos2dv");
	__glRasterPos2f = (PFNGLRASTERPOS2F)::GetProcAddress(opengl32, "glRasterPos2f");
	__glRasterPos2fv = (PFNGLRASTERPOS2FV)::GetProcAddress(opengl32, "glRasterPos2fv");
	__glRasterPos2i = (PFNGLRASTERPOS2I)::GetProcAddress(opengl32, "glRasterPos2i");
	__glRasterPos2iv = (PFNGLRASTERPOS2IV)::GetProcAddress(opengl32, "glRasterPos2iv");
	__glRasterPos2s = (PFNGLRASTERPOS2S)::GetProcAddress(opengl32, "glRasterPos2s");
	__glRasterPos2sv = (PFNGLRASTERPOS2SV)::GetProcAddress(opengl32, "glRasterPos2sv");
	__glRasterPos3d = (PFNGLRASTERPOS3D)::GetProcAddress(opengl32, "glRasterPos3d");
	__glRasterPos3dv = (PFNGLRASTERPOS3DV)::GetProcAddress(opengl32, "glRasterPos3dv");
	__glRasterPos3f = (PFNGLRASTERPOS3F)::GetProcAddress(opengl32, "glRasterPos3f");
	__glRasterPos3fv = (PFNGLRASTERPOS3FV)::GetProcAddress(opengl32, "glRasterPos3fv");
	__glRasterPos3i = (PFNGLRASTERPOS3I)::GetProcAddress(opengl32, "glRasterPos3i");
	__glRasterPos3iv = (PFNGLRASTERPOS3IV)::GetProcAddress(opengl32, "glRasterPos3iv");
	__glRasterPos3s = (PFNGLRASTERPOS3S)::GetProcAddress(opengl32, "glRasterPos3s");
	__glRasterPos3sv = (PFNGLRASTERPOS3SV)::GetProcAddress(opengl32, "glRasterPos3sv");
	__glRasterPos4d = (PFNGLRASTERPOS4D)::GetProcAddress(opengl32, "glRasterPos4d");
	__glRasterPos4dv = (PFNGLRASTERPOS4DV)::GetProcAddress(opengl32, "glRasterPos4dv");
	__glRasterPos4f = (PFNGLRASTERPOS4F)::GetProcAddress(opengl32, "glRasterPos4f");
	__glRasterPos4fv = (PFNGLRASTERPOS4FV)::GetProcAddress(opengl32, "glRasterPos4fv");
	__glRasterPos4i = (PFNGLRASTERPOS4I)::GetProcAddress(opengl32, "glRasterPos4i");
	__glRasterPos4iv = (PFNGLRASTERPOS4IV)::GetProcAddress(opengl32, "glRasterPos4iv");
	__glRasterPos4s = (PFNGLRASTERPOS4S)::GetProcAddress(opengl32, "glRasterPos4s");
	__glRasterPos4sv = (PFNGLRASTERPOS4SV)::GetProcAddress(opengl32, "glRasterPos4sv");
	__glReadBuffer = (PFNGLREADBUFFER)::GetProcAddress(opengl32, "glReadBuffer");
	__glReadPixels = (PFNGLREADPIXELS)::GetProcAddress(opengl32, "glReadPixels");
	__glRectd = (PFNGLRECTD)::GetProcAddress(opengl32, "glRectd");
	__glRectdv = (PFNGLRECTDV)::GetProcAddress(opengl32, "glRectdv");
	__glRectf = (PFNGLRECTF)::GetProcAddress(opengl32, "glRectf");
	__glRectfv = (PFNGLRECTFV)::GetProcAddress(opengl32, "glRectfv");
	__glRecti = (PFNGLRECTI)::GetProcAddress(opengl32, "glRecti");
	__glRectiv = (PFNGLRECTIV)::GetProcAddress(opengl32, "glRectiv");
	__glRects = (PFNGLRECTS)::GetProcAddress(opengl32, "glRects");
	__glRectsv = (PFNGLRECTSV)::GetProcAddress(opengl32, "glRectsv");
	__glRenderMode = (PFNGLRENDERMODE)::GetProcAddress(opengl32, "glRenderMode");
	__glRotated = (PFNGLROTATED)::GetProcAddress(opengl32, "glRotated");
	__glRotatef = (PFNGLROTATEF)::GetProcAddress(opengl32, "glRotatef");
	__glScaled = (PFNGLSCALED)::GetProcAddress(opengl32, "glScaled");
	__glScalef = (PFNGLSCALEF)::GetProcAddress(opengl32, "glScalef");
	__glScissor = (PFNGLSCISSOR)::GetProcAddress(opengl32, "glScissor");
	__glSelectBuffer = (PFNGLSELECTBUFFER)::GetProcAddress(opengl32, "glSelectBuffer");
	__glShadeModel = (PFNGLSHADEMODEL)::GetProcAddress(opengl32, "glShadeModel");
	__glStencilFunc = (PFNGLSTENCILFUNC)::GetProcAddress(opengl32, "glStencilFunc");
	__glStencilMask = (PFNGLSTENCILMASK)::GetProcAddress(opengl32, "glStencilMask");
	__glStencilOp = (PFNGLSTENCILOP)::GetProcAddress(opengl32, "glStencilOp");
	__glTexCoord1d = (PFNGLTEXCOORD1D)::GetProcAddress(opengl32, "glTexCoord1d");
	__glTexCoord1dv = (PFNGLTEXCOORD1DV)::GetProcAddress(opengl32, "glTexCoord1dv");
	__glTexCoord1f = (PFNGLTEXCOORD1F)::GetProcAddress(opengl32, "glTexCoord1f");
	__glTexCoord1fv = (PFNGLTEXCOORD1FV)::GetProcAddress(opengl32, "glTexCoord1fv");
	__glTexCoord1i = (PFNGLTEXCOORD1I)::GetProcAddress(opengl32, "glTexCoord1i");
	__glTexCoord1iv = (PFNGLTEXCOORD1IV)::GetProcAddress(opengl32, "glTexCoord1iv");
	__glTexCoord1s = (PFNGLTEXCOORD1S)::GetProcAddress(opengl32, "glTexCoord1s");
	__glTexCoord1sv = (PFNGLTEXCOORD1SV)::GetProcAddress(opengl32, "glTexCoord1sv");
	__glTexCoord2d = (PFNGLTEXCOORD2D)::GetProcAddress(opengl32, "glTexCoord2d");
	__glTexCoord2dv = (PFNGLTEXCOORD2DV)::GetProcAddress(opengl32, "glTexCoord2dv");
	__glTexCoord2f = (PFNGLTEXCOORD2F)::GetProcAddress(opengl32, "glTexCoord2f");
	__glTexCoord2fv = (PFNGLTEXCOORD2FV)::GetProcAddress(opengl32, "glTexCoord2fv");
	__glTexCoord2i = (PFNGLTEXCOORD2I)::GetProcAddress(opengl32, "glTexCoord2i");
	__glTexCoord2iv = (PFNGLTEXCOORD2IV)::GetProcAddress(opengl32, "glTexCoord2iv");
	__glTexCoord2s = (PFNGLTEXCOORD2S)::GetProcAddress(opengl32, "glTexCoord2s");
	__glTexCoord2sv = (PFNGLTEXCOORD2SV)::GetProcAddress(opengl32, "glTexCoord2sv");
	__glTexCoord3d = (PFNGLTEXCOORD3D)::GetProcAddress(opengl32, "glTexCoord3d");
	__glTexCoord3dv = (PFNGLTEXCOORD3DV)::GetProcAddress(opengl32, "glTexCoord3dv");
	__glTexCoord3f = (PFNGLTEXCOORD3F)::GetProcAddress(opengl32, "glTexCoord3f");
	__glTexCoord3fv = (PFNGLTEXCOORD3FV)::GetProcAddress(opengl32, "glTexCoord3fv");
	__glTexCoord3i = (PFNGLTEXCOORD3I)::GetProcAddress(opengl32, "glTexCoord3i");
	__glTexCoord3iv = (PFNGLTEXCOORD3IV)::GetProcAddress(opengl32, "glTexCoord3iv");
	__glTexCoord3s = (PFNGLTEXCOORD3S)::GetProcAddress(opengl32, "glTexCoord3s");
	__glTexCoord3sv = (PFNGLTEXCOORD3SV)::GetProcAddress(opengl32, "glTexCoord3sv");
	__glTexCoord4d = (PFNGLTEXCOORD4D)::GetProcAddress(opengl32, "glTexCoord4d");
	__glTexCoord4dv = (PFNGLTEXCOORD4DV)::GetProcAddress(opengl32, "glTexCoord4dv");
	__glTexCoord4f = (PFNGLTEXCOORD4F)::GetProcAddress(opengl32, "glTexCoord4f");
	__glTexCoord4fv = (PFNGLTEXCOORD4FV)::GetProcAddress(opengl32, "glTexCoord4fv");
	__glTexCoord4i = (PFNGLTEXCOORD4I)::GetProcAddress(opengl32, "glTexCoord4i");
	__glTexCoord4iv = (PFNGLTEXCOORD4IV)::GetProcAddress(opengl32, "glTexCoord4iv");
	__glTexCoord4s = (PFNGLTEXCOORD4S)::GetProcAddress(opengl32, "glTexCoord4s");
	__glTexCoord4sv = (PFNGLTEXCOORD4SV)::GetProcAddress(opengl32, "glTexCoord4sv");
	__glTexCoordPointer = (PFNGLTEXCOORDPOINTER)::GetProcAddress(opengl32, "glTexCoordPointer");
	__glTexEnvf = (PFNGLTEXENVF)::GetProcAddress(opengl32, "glTexEnvf");
	__glTexEnvfv = (PFNGLTEXENVFV)::GetProcAddress(opengl32, "glTexEnvfv");
	__glTexEnvi = (PFNGLTEXENVI)::GetProcAddress(opengl32, "glTexEnvi");
	__glTexEnviv = (PFNGLTEXENVIV)::GetProcAddress(opengl32, "glTexEnviv");
	__glTexGend = (PFNGLTEXGEND)::GetProcAddress(opengl32, "glTexGend");
	__glTexGendv = (PFNGLTEXGENDV)::GetProcAddress(opengl32, "glTexGendv");
	__glTexGenf = (PFNGLTEXGENF)::GetProcAddress(opengl32, "glTexGenf");
	__glTexGenfv = (PFNGLTEXGENFV)::GetProcAddress(opengl32, "glTexGenfv");
	__glTexGeni = (PFNGLTEXGENI)::GetProcAddress(opengl32, "glTexGeni");
	__glTexGeniv = (PFNGLTEXGENIV)::GetProcAddress(opengl32, "glTexGeniv");
	__glTexImage1D = (PFNGLTEXIMAGE1D)::GetProcAddress(opengl32, "glTexImage1D");
	__glTexImage2D = (PFNGLTEXIMAGE2D)::GetProcAddress(opengl32, "glTexImage2D");
	__glTexParameterf = (PFNGLTEXPARAMETERF)::GetProcAddress(opengl32, "glTexParameterf");
	__glTexParameterfv = (PFNGLTEXPARAMETERFV)::GetProcAddress(opengl32, "glTexParameterfv");
	__glTexParameteri = (PFNGLTEXPARAMETERI)::GetProcAddress(opengl32, "glTexParameteri");
	__glTexParameteriv = (PFNGLTEXPARAMETERIV)::GetProcAddress(opengl32, "glTexParameteriv");
	__glTexSubImage1D = (PFNGLTEXSUBIMAGE1D)::GetProcAddress(opengl32, "glTexSubImage1D");
	__glTexSubImage2D = (PFNGLTEXSUBIMAGE2D)::GetProcAddress(opengl32, "glTexSubImage2D");
	__glTranslated = (PFNGLTRANSLATED)::GetProcAddress(opengl32, "glTranslated");
	__glTranslatef = (PFNGLTRANSLATEF)::GetProcAddress(opengl32, "glTranslatef");
	__glVertex2d = (PFNGLVERTEX2D)::GetProcAddress(opengl32, "glVertex2d");
	__glVertex2dv = (PFNGLVERTEX2DV)::GetProcAddress(opengl32, "glVertex2dv");
	__glVertex2f = (PFNGLVERTEX2F)::GetProcAddress(opengl32, "glVertex2f");
	__glVertex2fv = (PFNGLVERTEX2FV)::GetProcAddress(opengl32, "glVertex2fv");
	__glVertex2i = (PFNGLVERTEX2I)::GetProcAddress(opengl32, "glVertex2i");
	__glVertex2iv = (PFNGLVERTEX2IV)::GetProcAddress(opengl32, "glVertex2iv");
	__glVertex2s = (PFNGLVERTEX2S)::GetProcAddress(opengl32, "glVertex2s");
	__glVertex2sv = (PFNGLVERTEX2SV)::GetProcAddress(opengl32, "glVertex2sv");
	__glVertex3d = (PFNGLVERTEX3D)::GetProcAddress(opengl32, "glVertex3d");
	__glVertex3dv = (PFNGLVERTEX3DV)::GetProcAddress(opengl32, "glVertex3dv");
	__glVertex3f = (PFNGLVERTEX3F)::GetProcAddress(opengl32, "glVertex3f");
	__glVertex3fv = (PFNGLVERTEX3FV)::GetProcAddress(opengl32, "glVertex3fv");
	__glVertex3i = (PFNGLVERTEX3I)::GetProcAddress(opengl32, "glVertex3i");
	__glVertex3iv = (PFNGLVERTEX3IV)::GetProcAddress(opengl32, "glVertex3iv");
	__glVertex3s = (PFNGLVERTEX3S)::GetProcAddress(opengl32, "glVertex3s");
	__glVertex3sv = (PFNGLVERTEX3SV)::GetProcAddress(opengl32, "glVertex3sv");
	__glVertex4d = (PFNGLVERTEX4D)::GetProcAddress(opengl32, "glVertex4d");
	__glVertex4dv = (PFNGLVERTEX4DV)::GetProcAddress(opengl32, "glVertex4dv");
	__glVertex4f = (PFNGLVERTEX4F)::GetProcAddress(opengl32, "glVertex4f");
	__glVertex4fv = (PFNGLVERTEX4FV)::GetProcAddress(opengl32, "glVertex4fv");
	__glVertex4i = (PFNGLVERTEX4I)::GetProcAddress(opengl32, "glVertex4i");
	__glVertex4iv = (PFNGLVERTEX4IV)::GetProcAddress(opengl32, "glVertex4iv");
	__glVertex4s = (PFNGLVERTEX4S)::GetProcAddress(opengl32, "glVertex4s");
	__glVertex4sv = (PFNGLVERTEX4SV)::GetProcAddress(opengl32, "glVertex4sv");
	__glVertexPointer = (PFNGLVERTEXPOINTER)::GetProcAddress(opengl32, "glVertexPointer");
	__glViewport = (PFNGLVIEWPORT)::GetProcAddress(opengl32, "glViewport");
#endif

#if defined(_BUILD_PLATFORM_WINDOWS)
	__wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)::wglGetProcAddress("wglSwapIntervalEXT");
	__wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)::wglGetProcAddress("wglGetPixelFormatAttribivARB");
	__wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)::wglGetProcAddress("wglCreateContextAttribsARB");

	initGLExtention = __wglCreateContextAttribsARB ? true : false;
#else
	initGLExtention = true;
#endif

	return initGLExtention;
}

_NAME_END
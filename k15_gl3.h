#ifndef _K15_GL3_h_
#define _K15_GL3_h_

//EGL_KHR_create_context
#define EGL_CONTEXT_MAJOR_VERSION_KHR						0x3098
#define EGL_CONTEXT_MINOR_VERSION_KHR						0x30FB
#define EGL_CONTEXT_FLAGS_KHR								0x30FC
#define EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR					0x30FD
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR  0x31BD
#define EGL_NO_RESET_NOTIFICATION_KHR						0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_KHR						0x31BF
#define EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR					0x00000001
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR		0x00000002
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR			0x00000004
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR				0x00000001
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR	0x00000002

//GL_AMD_debug_output
#define GL_MAX_DEBUG_MESSAGE_LENGTH_AMD				0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_AMD			0x9144
#define GL_DEBUG_LOGGED_MESSAGES_AMD				0x9145
#define GL_DEBUG_SEVERITY_HIGH_AMD					0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_AMD				0x9147
#define GL_DEBUG_SEVERITY_LOW_AMD					0x9148
#define GL_DEBUG_CATEGORY_API_ERROR_AMD				0x9149
#define GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD			0x914A
#define GL_DEBUG_CATEGORY_DEPRECATION_AMD			0x914B
#define GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD	0x914C
#define GL_DEBUG_CATEGORY_PERFORMANCE_AMD			0x914D
#define GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD		0x914E
#define GL_DEBUG_CATEGORY_APPLICATION_AMD			0x914F
#define GL_DEBUG_CATEGORY_OTHER_AMD					0x9150

//GL_EXT_texture_filter_anisotropic
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE 

//GL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3

#define K15_GL3_CHECK_ASSIGNMENT(variable, value) {if (value) variable = (void*)value; else printf( "Could not assign to variable \'%s\'.", #variable);}

void K15_GL3RegisterGLFunctions();

#ifdef _WIN32
	typedef BOOL(WINAPI *PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
	typedef HGLRC(WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
# include "glcorearb.h"
# include "wglext.h"
# ifndef APIENTRY
#  define APIENTRY
# endif //APIENTRY
#endif // _WIN32

void APIENTRY K15_DebugProcARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	const char* sourceName = 0;
	const char* typeName = 0;

	switch (source)
	{
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourceName = "Window System";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourceName = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourceName = "Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		sourceName = "Application";
		break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		typeName = "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typeName = "Deprecated";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typeName = "Undefined Behavior";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		typeName = "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		typeName = "Performance";
	}

	if (typeName == 0 || sourceName == 0)
		return;

	char buffer[512];
	sprintf(buffer, "OpenGL %s Warning. Category: %s Message: %s\n", typeName, sourceName, (const char*)message);

	OutputDebugStringA(buffer);
}


#ifdef K15_OPENGL_ENABLE_ERROR_CHECK_CALLS
	const char* K15_GLConvertErrorCode(GLenum p_ErrorCode)
	{
		const char* errorMessage = 0;
		switch (p_ErrorCode)
		{
		case GL_INVALID_ENUM:
		{
			errorMessage = "GL_INVALID_ENUM";
			break;
		}

		case GL_INVALID_VALUE:
		{
			errorMessage = "GL_INVALID_VALUE";
			break;
		}

		case GL_INVALID_OPERATION:
		{
			errorMessage = "GL_INVALID_OPERATION";
			break;
		}

		case GL_STACK_OVERFLOW:
		{
			errorMessage = "GL_STACK_OVERFLOW";
			break;
		}

		case GL_STACK_UNDERFLOW:
		{
			errorMessage = "GL_STACK_UNDERFLOW";
			break;
		}

		case GL_OUT_OF_MEMORY:
		{
			errorMessage = "GL_OUT_OF_MEMORY";
			break;
		}

		case GL_INVALID_FRAMEBUFFER_OPERATION:
		{
			errorMessage = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		}

		case GL_CONTEXT_LOST:
		{
			errorMessage = "GL_CONTEXT_LOST";
			break;
		}
		}
		return errorMessage;
}
# define K15_OPENGL_CALL(x) \
	{ \
		x; \
		GLenum errorEnum = kglGetError(); \
		if(errorEnum != GL_NO_ERROR){\
			char buffer[512]; \
			sprintf(buffer, "OpenGL Error on calling '%s' (Error: %s)\n", #x, K15_GLConvertErrorCode(errorEnum)); \
			OutputDebugStringA(buffer);\
		}\
	}
#else
	#define K15_OPENGL_CALL(x) x;
#endif //K15_OPENGL_ENABLE_ERROR_CHECK_CALLS

typedef char GLchar;

// default gl functions
typedef GLvoid (APIENTRY *PFNGLBINDTEXTUREPROC)(GLenum, GLuint);
typedef GLvoid (APIENTRY *PFNGLDELETETEXTURESPROC)(GLsizei, const GLuint*);
typedef GLvoid (APIENTRY *PFNGLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const GLvoid*);
typedef GLvoid (APIENTRY *PFNGLGENTEXTURESPROC)(GLsizei, GLuint*);
typedef GLvoid (APIENTRY *PFNGLDRAWARRAYSPROC)(GLenum, GLint, GLsizei);

//windows gl
typedef GLvoid* (WINAPI *PFNWGLGETPROCADDRESSPROC)(const char*);
typedef HGLRC	(WINAPI *PFNWGLCREATECONTEXTPROC)(HDC);
typedef BOOL	(WINAPI *PFNWGLDELETECONTEXTPROC)(HGLRC);
typedef BOOL	(WINAPI *PFNWGLMAKECURRENTPROC)(HDC, HGLRC);
typedef HGLRC	(WINAPI *PFNWGLGETCURRENTCONTEXTPROC)(void);
typedef HDC		(WINAPI* PFNWGLGETCURRENTDCPROC)(void);

//GL_KHR_debug
typedef GLvoid (APIENTRY* GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef GLvoid (APIENTRY* PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);

PFNGLBINDTEXTUREPROC	kglBindTexture;
PFNGLCLEARPROC			kglClear;
PFNGLCLEARCOLORPROC		kglClearColor;
PFNGLCULLFACEPROC		kglCullFace;
PFNGLDELETETEXTURESPROC	kglDeleteTextures;
PFNGLDEPTHFUNCPROC		kglDepthFunc;
PFNGLDISABLEPROC		kglDisable;
PFNGLDRAWELEMENTSPROC	kglDrawElements;
PFNGLENABLEPROC			kglEnable;
PFNGLFRONTFACEPROC		kglFrontFace;
PFNGLGENTEXTURESPROC	kglGenTextures;
PFNGLGETERRORPROC		kglGetError;
PFNGLPOLYGONMODEPROC	kglPolygonMode;
PFNGLVIEWPORTPROC		kglViewport;
PFNGLGETFLOATVPROC		kglGetFloatv;
PFNGLGETINTEGERVPROC	kglGetIntegerv;
PFNGLGETSTRINGIPROC		kglGetStringi;
PFNGLGETSTRINGPROC		kglGetString;
PFNGLTEXIMAGE1DPROC		kglTexImage1D;
PFNGLTEXIMAGE2DPROC		kglTexImage2D;
PFNGLTEXPARAMETERIPROC	kglTexParameteri;
PFNGLDRAWARRAYSPROC		kglDrawArrays;

#ifdef _WIN32
#define kglGetProcAddress kwglGetProcAddress

//wgl
PFNWGLCHOOSEPIXELFORMATARBPROC			kwglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC		kwglCreateContextAttribsARB;
PFNWGLGETPROCADDRESSPROC				kwglGetProcAddress;
PFNWGLCREATECONTEXTPROC					kwglCreateContext;
PFNWGLDELETECONTEXTPROC					kwglDeleteContext;
PFNWGLMAKECURRENTPROC					kwglMakeCurrent;
PFNWGLGETCURRENTCONTEXTPROC				kwglGetCurrentContext;
PFNWGLGETCURRENTDCPROC					kwglGetCurrentDC;

void K15_GL3RegisterWGLFunctions(HWND p_HWND)
{
	HMODULE openglModule = GetModuleHandleA("opengl32.dll");

	if (!openglModule)
		openglModule = LoadLibraryA("opengl32.dll");

	K15_GL3_CHECK_ASSIGNMENT(kwglGetProcAddress, GetProcAddress(openglModule, "wglGetProcAddress"));

	K15_GL3_CHECK_ASSIGNMENT(kwglCreateContext, GetProcAddress(openglModule, "wglCreateContext"));
	K15_GL3_CHECK_ASSIGNMENT(kwglDeleteContext, GetProcAddress(openglModule, "wglDeleteContext"));
	K15_GL3_CHECK_ASSIGNMENT(kwglMakeCurrent, GetProcAddress(openglModule, "wglMakeCurrent"));
	K15_GL3_CHECK_ASSIGNMENT(kwglGetCurrentContext, GetProcAddress(openglModule, "wglGetCurrentContext"));
	K15_GL3_CHECK_ASSIGNMENT(kwglGetCurrentDC, GetProcAddress(openglModule, "wglGetCurrentDC"));

	K15_GL3_CHECK_ASSIGNMENT(kglBindTexture, GetProcAddress(openglModule, "glBindTexture"));
	K15_GL3_CHECK_ASSIGNMENT(kglClear, GetProcAddress(openglModule, "glClear"));
	K15_GL3_CHECK_ASSIGNMENT(kglClearColor, GetProcAddress(openglModule, "glClearColor"));
	K15_GL3_CHECK_ASSIGNMENT(kglCullFace, GetProcAddress(openglModule, "glCullFace"));
	K15_GL3_CHECK_ASSIGNMENT(kglDeleteTextures, GetProcAddress(openglModule, "glDeleteTextures"));
	K15_GL3_CHECK_ASSIGNMENT(kglDepthFunc, GetProcAddress(openglModule, "glDepthFunc"));
	K15_GL3_CHECK_ASSIGNMENT(kglDisable, GetProcAddress(openglModule, "glDisable"));
	K15_GL3_CHECK_ASSIGNMENT(kglDrawElements, GetProcAddress(openglModule, "glDrawElements"));
	K15_GL3_CHECK_ASSIGNMENT(kglEnable, GetProcAddress(openglModule, "glEnable"));
	K15_GL3_CHECK_ASSIGNMENT(kglFrontFace, GetProcAddress(openglModule, "glFrontFace"));
	K15_GL3_CHECK_ASSIGNMENT(kglGenTextures, GetProcAddress(openglModule, "glGenTextures"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetError, GetProcAddress(openglModule, "glGetError"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetFloatv, GetProcAddress(openglModule, "glGetFloatv"));
	K15_GL3_CHECK_ASSIGNMENT(kglPolygonMode, GetProcAddress(openglModule, "glPolygonMode"));
	K15_GL3_CHECK_ASSIGNMENT(kglViewport, GetProcAddress(openglModule, "glViewport"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetIntegerv, GetProcAddress(openglModule, "glGetIntegerv"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetString, GetProcAddress(openglModule, "glGetString"));

	K15_GL3_CHECK_ASSIGNMENT(kglTexImage1D, GetProcAddress(openglModule, "glTexImage1D"));
	K15_GL3_CHECK_ASSIGNMENT(kglTexImage2D, GetProcAddress(openglModule, "glTexImage2D"));
	K15_GL3_CHECK_ASSIGNMENT(kglTexParameteri, GetProcAddress(openglModule, "glTexParameteri"));
	K15_GL3_CHECK_ASSIGNMENT(kglDrawArrays, GetProcAddress(openglModule, "glDrawArrays"));

	HDC deviceContext = GetDC(p_HWND);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
	SetPixelFormat(deviceContext, pixelFormat, &pfd);

	HGLRC glContext = kwglCreateContext(deviceContext);
	kwglMakeCurrent(deviceContext, glContext);

	K15_GL3_CHECK_ASSIGNMENT(kwglChoosePixelFormatARB, kwglGetProcAddress("wglChoosePixelFormatARB"));
	K15_GL3_CHECK_ASSIGNMENT(kwglCreateContextAttribsARB, kwglGetProcAddress("wglCreateContextAttribsARB"));

	//create real context
	const int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB,				GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,				GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,				GL_TRUE,
		WGL_ACCELERATION_ARB,				WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,					WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,					24,
		WGL_DEPTH_BITS_ARB,					24,
		WGL_STENCIL_BITS_ARB,				8,
		0
	};

	int pixelFormatIndex = 0;
	unsigned int formatCount = 1;

	K15_OPENGL_CALL(kwglChoosePixelFormatARB(deviceContext, pixelFormatAttributes, 0, 1, &pixelFormatIndex, &formatCount));
	SetPixelFormat(deviceContext, pixelFormatIndex, 0);

	//int contextFlags = WGL_CONTEXT_CORE_PROFILE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB;
	int majorVersion = 3;
	int minorVersion = 3;

	const int contextAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
		WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0 //END
	};

	HGLRC context = 0;
	K15_OPENGL_CALL(context = kwglCreateContextAttribsARB(deviceContext, 0, contextAttributes));
	K15_OPENGL_CALL(kwglMakeCurrent(deviceContext, context));

	K15_GL3RegisterGLFunctions();
}

#endif //_WIN32

//default gl functions
PFNGLCREATESHADERPROC					kglCreateShader;
PFNGLSHADERSOURCEPROC					kglShaderSource;
PFNGLCOMPILESHADERPROC					kglCompileShader;
PFNGLCREATEPROGRAMPROC					kglCreateProgram;
PFNGLGETSHADERIVPROC					kglGetShaderiv;
PFNGLATTACHSHADERPROC					kglAttachShader;
PFNGLLINKPROGRAMPROC					kglLinkProgram;
PFNGLUSEPROGRAMPROC						kglUseProgram;
PFNGLDETACHSHADERPROC					kglDetachShader;
PFNGLGETSHADERINFOLOGPROC				kglGetShaderInfoLog;
PFNGLGENBUFFERSPROC						kglGenBuffers;
PFNGLBINDBUFFERPROC						kglBindBuffer;
PFNGLBUFFERDATAPROC						kglBufferData;
PFNGLBUFFERSUBDATAPROC					kglBufferSubData;
PFNGLBINDFRAGDATALOCATIONPROC			kglBindFragDataLocation;
PFNGLVERTEXATTRIBPOINTERPROC			kglVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC		kglEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC		kglDisableVertexAttribArray;
PFNGLDELETEBUFFERSPROC					kglDeleteBuffers;
PFNGLGETPROGRAMIVPROC					kglGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC				kglGetProgramInfoLog;
PFNGLDELETEPROGRAMPROC					kglDeleteProgram;
PFNGLGETACTIVEUNIFORMPROC				kglGetActiveUniform;
PFNGLGETACTIVEATTRIBPROC				kglGetActiveAttrib;
PFNGLGETUNIFORMLOCATIONPROC				kglGetUniformLocation;
PFNGLGETATTRIBLOCATIONPROC				kglGetAttribLocation;
PFNGLBLENDEQUATIONSEPARATEPROC			kglBlendEquationSeparate;
PFNGLBLENDFUNCSEPARATEPROC				kglBlendFuncSeparate;
PFNGLGENFRAMEBUFFERSPROC				kglGenFramebuffers;
PFNGLBINDFRAMEBUFFERPROC				kglBindFramebuffer;
PFNGLDELETEFRAMEBUFFERSPROC				kglDeleteFramebuffers;
PFNGLGENRENDERBUFFERSPROC				kglGenRenderbuffers;
PFNGLBINDRENDERBUFFERPROC				kglBindRenderbuffer;
PFNGLDELETERENDERBUFFERSPROC			kglDeleteRenderbuffers;
PFNGLRENDERBUFFERSTORAGEPROC			kglRenderbufferStorage;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC	kglRenderbufferStorageMultisample;
PFNGLFRAMEBUFFERRENDERBUFFERPROC		kglFramebufferRenderbuffer;
PFNGLFRAMEBUFFERTEXTUREPROC				kglFramebufferTexture;
PFNGLCHECKFRAMEBUFFERSTATUSPROC			kglCheckFramebufferStatus;
PFNGLDRAWBUFFERSPROC					kglDrawBuffers;
PFNGLDRAWRANGEELEMENTSPROC				kglDrawRangeElements;
PFNGLDRAWELEMENTSBASEVERTEXPROC			kglDrawElementsBaseVertex;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC	kglDrawRangeElementsBaseVertex;
PFNGLCOMPRESSEDTEXIMAGE1DPROC			kglCompressedTexImage1D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC			kglCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE3DPROC			kglCompressedTexImage3D;
PFNGLTEXIMAGE3DPROC						kglTexImage3D;
PFNGLGENERATEMIPMAPPROC					kglGenerateMipmap;
PFNGLACTIVETEXTUREPROC					kglActiveTexture;

PFNGLUNIFORM1FPROC						kglUniform1f;
PFNGLUNIFORM2FPROC						kglUniform2f;
PFNGLUNIFORM3FPROC						kglUniform3f;
PFNGLUNIFORM4FPROC						kglUniform4f;
PFNGLUNIFORM1FVPROC						kglUniform1fv;
PFNGLUNIFORM2FVPROC						kglUniform2fv;
PFNGLUNIFORM3FVPROC						kglUniform3fv;
PFNGLUNIFORM4FVPROC						kglUniform4fv;

PFNGLUNIFORM1IPROC						kglUniform1i;
PFNGLUNIFORM2IPROC						kglUniform2i;
PFNGLUNIFORM3IPROC						kglUniform3i;
PFNGLUNIFORM4IPROC						kglUniform4i;
PFNGLUNIFORM1IVPROC						kglUniform1iv;
PFNGLUNIFORM2IVPROC						kglUniform2iv;
PFNGLUNIFORM3IVPROC						kglUniform3iv;
PFNGLUNIFORM4IVPROC						kglUniform4iv;

PFNGLUNIFORMMATRIX2FVPROC				kglUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC				kglUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC				kglUniformMatrix4fv;

//GL_ARB_vertex_array_object//
PFNGLGENVERTEXARRAYSPROC		kglGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC		kglBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC		kglDeleteVertexArrays;

//GL_ARB_sampler_objects
PFNGLGENSAMPLERSPROC				kglGenSamplers;
PFNGLDELETESAMPLERSPROC				kglDeleteSamplers;
PFNGLBINDSAMPLERPROC				kglBindSampler;
PFNGLSAMPLERPARAMETERIPROC			kglSamplerParameteri;
PFNGLSAMPLERPARAMETERFPROC			kglSamplerParameterf;
PFNGLSAMPLERPARAMETERIVPROC			kglSamplerParameteriv;
PFNGLSAMPLERPARAMETERFVPROC			kglSamplerParameterfv;
PFNGLSAMPLERPARAMETERIIVPROC		kglSamplerParameterIiv;
PFNGLSAMPLERPARAMETERIUIVPROC		kglSamplerParameterIuiv;
PFNGLGETSAMPLERPARAMETERIIVPROC		kglGetSamplerParameterIiv;
PFNGLGETSAMPLERPARAMETERIVPROC		kglGetSamplerParameteriv;
PFNGLGETSAMPLERPARAMETERFVPROC		kglGetSamplerParameterfv;
PFNGLGETSAMPLERPARAMETERIUIVPROC	kglGetSamplerParameterIuiv;

//GL_ARB_separate_shader_objects//
PFNGLGENPROGRAMPIPELINESPROC	kglGenProgramPipelines;
PFNGLBINDPROGRAMPIPELINEPROC	kglBindProgramPipeline;
PFNGLDELETEPROGRAMPIPELINESPROC	kglDeleteProgramPipelines;
PFNGLUSEPROGRAMSTAGESPROC		kglUseProgramStages;
PFNGLACTIVESHADERPROGRAMPROC	kglActiveShaderProgram;
PFNGLCREATESHADERPROGRAMVPROC	kglCreateShaderProgramv;
PFNGLPROGRAMPARAMETERIPROC		kglProgramParameteri;

PFNGLPROGRAMUNIFORM1IPROC kglProgramUniform1i;
PFNGLPROGRAMUNIFORM2IPROC kglProgramUniform2i;
PFNGLPROGRAMUNIFORM3IPROC kglProgramUniform3i;
PFNGLPROGRAMUNIFORM4IPROC kglProgramUniform4i;

PFNGLPROGRAMUNIFORM1UIPROC kglProgramUniform1ui;
PFNGLPROGRAMUNIFORM2UIPROC kglProgramUniform2ui;
PFNGLPROGRAMUNIFORM3UIPROC kglProgramUniform3ui;
PFNGLPROGRAMUNIFORM4UIPROC kglProgramUniform4ui;

PFNGLPROGRAMUNIFORM1FPROC kglProgramUniform1f;
PFNGLPROGRAMUNIFORM2FPROC kglProgramUniform2f;
PFNGLPROGRAMUNIFORM3FPROC kglProgramUniform3f;
PFNGLPROGRAMUNIFORM4FPROC kglProgramUniform4f;

PFNGLPROGRAMUNIFORM1DPROC kglProgramUniform1d;
PFNGLPROGRAMUNIFORM2DPROC kglProgramUniform2d;
PFNGLPROGRAMUNIFORM3DPROC kglProgramUniform3d;
PFNGLPROGRAMUNIFORM4DPROC kglProgramUniform4d;

PFNGLPROGRAMUNIFORM1IVPROC kglProgramUniform1iv;
PFNGLPROGRAMUNIFORM2IVPROC kglProgramUniform2iv;
PFNGLPROGRAMUNIFORM3IVPROC kglProgramUniform3iv;
PFNGLPROGRAMUNIFORM4IVPROC kglProgramUniform4iv;

PFNGLPROGRAMUNIFORM1UIVPROC kglProgramUniform1uiv;
PFNGLPROGRAMUNIFORM2UIVPROC kglProgramUniform2uiv;
PFNGLPROGRAMUNIFORM3UIVPROC kglProgramUniform3uiv;
PFNGLPROGRAMUNIFORM4UIVPROC kglProgramUniform4uiv;

PFNGLPROGRAMUNIFORM1FVPROC kglProgramUniform1fv;
PFNGLPROGRAMUNIFORM2FVPROC kglProgramUniform2fv;
PFNGLPROGRAMUNIFORM3FVPROC kglProgramUniform3fv;
PFNGLPROGRAMUNIFORM4FVPROC kglProgramUniform4fv;

PFNGLPROGRAMUNIFORM1DVPROC kglProgramUniform1dv;
PFNGLPROGRAMUNIFORM2DVPROC kglProgramUniform2dv;
PFNGLPROGRAMUNIFORM3DVPROC kglProgramUniform3dv;
PFNGLPROGRAMUNIFORM4DVPROC kglProgramUniform4dv;

PFNGLPROGRAMUNIFORMMATRIX2FVPROC	kglProgramUniformMatrix2fv;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC	kglProgramUniformMatrix3fv;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC	kglProgramUniformMatrix4fv;

PFNGLPROGRAMUNIFORMMATRIX2DVPROC	kglProgramUniformMatrix2dv;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC	kglProgramUniformMatrix3dv;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC	kglProgramUniformMatrix4dv;

PFNGLVALIDATEPROGRAMPIPELINEPROC		kglValidateProgramPipeline;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC	kglGetProgramPipelineInfoLog;

//GL_ARB_sampler_objects
PFNGLGENSAMPLERSPROC				kglGenSamplers;
PFNGLDELETESAMPLERSPROC				kglDeleteSamplers;
PFNGLBINDSAMPLERPROC				kglBindSampler;
PFNGLSAMPLERPARAMETERIPROC			kglSamplerParameteri;
PFNGLSAMPLERPARAMETERFPROC			kglSamplerParameterf;
PFNGLSAMPLERPARAMETERIVPROC			kglSamplerParameteriv;
PFNGLSAMPLERPARAMETERFVPROC			kglSamplerParameterfv;
PFNGLSAMPLERPARAMETERIIVPROC		kglSamplerParameterIiv;
PFNGLSAMPLERPARAMETERIUIVPROC		kglSamplerParameterIuiv;
PFNGLGETSAMPLERPARAMETERIIVPROC		kglGetSamplerParameterIiv;
PFNGLGETSAMPLERPARAMETERIVPROC		kglGetSamplerParameteriv;
PFNGLGETSAMPLERPARAMETERFVPROC		kglGetSamplerParameterfv;
PFNGLGETSAMPLERPARAMETERIUIVPROC	kglGetSamplerParameterIuiv;

//GL_KHR_debug
PFNGLDEBUGMESSAGECALLBACKPROC kglDebugMessageCallback;

//GL_ARB_direct_state_access
PFNGLTEXTURESTORAGE1DPROC				kglTextureStorage1D;
PFNGLTEXTURESTORAGE2DPROC				kglTextureStorage2D;
PFNGLTEXTURESTORAGE3DPROC				kglTextureStorage3D;
PFNGLTEXTURESUBIMAGE1DPROC				kglTextureSubImage1D;
PFNGLTEXTURESUBIMAGE2DPROC				kglTextureSubImage2D;
PFNGLTEXTURESUBIMAGE3DPROC				kglTextureSubImage3D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC	kglCompressedTextureSubImage1D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC	kglCompressedTextureSubImage2D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC	kglCompressedTextureSubImage3D;
PFNGLGENERATETEXTUREMIPMAPPROC			kglGenerateTextureMipmap;
PFNGLNAMEDBUFFERDATAPROC				kglNamedBufferData;
PFNGLNAMEDBUFFERSUBDATAPROC				kglNamedBufferSubData;
PFNGLMAPNAMEDBUFFERPROC					kglMapNamedBuffer;
PFNGLMAPNAMEDBUFFERRANGEPROC			kglMapNamedBufferRange;
PFNGLUNMAPNAMEDBUFFERPROC				kglUnmapNamedBuffer;
/*********************************************************************************/

void K15_GL3RegisterGLFunctions()
{
	K15_GL3_CHECK_ASSIGNMENT(kglGetStringi, kglGetProcAddress("glGetStringi"));
	K15_GL3_CHECK_ASSIGNMENT(kglCreateShader, kglGetProcAddress("glCreateShader"));
	K15_GL3_CHECK_ASSIGNMENT(kglShaderSource, kglGetProcAddress("glShaderSource"));
	K15_GL3_CHECK_ASSIGNMENT(kglCompileShader, kglGetProcAddress("glCompileShader"));
	K15_GL3_CHECK_ASSIGNMENT(kglCreateProgram, kglGetProcAddress("glCreateProgram"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetShaderiv, kglGetProcAddress("glGetShaderiv"));
	K15_GL3_CHECK_ASSIGNMENT(kglAttachShader, kglGetProcAddress("glAttachShader"));
	K15_GL3_CHECK_ASSIGNMENT(kglLinkProgram, kglGetProcAddress("glLinkProgram"));
	K15_GL3_CHECK_ASSIGNMENT(kglUseProgram, kglGetProcAddress("glUseProgram"));
	K15_GL3_CHECK_ASSIGNMENT(kglDetachShader, kglGetProcAddress("glDetachShader"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetShaderInfoLog, kglGetProcAddress("glGetShaderInfoLog"));
	K15_GL3_CHECK_ASSIGNMENT(kglGenBuffers, kglGetProcAddress("glGenBuffers"));
	K15_GL3_CHECK_ASSIGNMENT(kglVertexAttribPointer, kglGetProcAddress("glVertexAttribPointer"));
	K15_GL3_CHECK_ASSIGNMENT(kglEnableVertexAttribArray, kglGetProcAddress("glEnableVertexAttribArray"));
	K15_GL3_CHECK_ASSIGNMENT(kglDisableVertexAttribArray, kglGetProcAddress("glDisableVertexAttribArray"));
	K15_GL3_CHECK_ASSIGNMENT(kglDrawElementsBaseVertex, kglGetProcAddress("glDrawElementsBaseVertex"));
	K15_GL3_CHECK_ASSIGNMENT(kglBindBuffer, kglGetProcAddress("glBindBuffer"));
	K15_GL3_CHECK_ASSIGNMENT(kglBufferData, kglGetProcAddress("glBufferData"));
	K15_GL3_CHECK_ASSIGNMENT(kglBufferSubData, kglGetProcAddress("glBufferSubData"));
	K15_GL3_CHECK_ASSIGNMENT(kglDeleteBuffers, kglGetProcAddress("glDeleteBuffers"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetProgramiv, kglGetProcAddress("glGetProgramiv"));
	K15_GL3_CHECK_ASSIGNMENT(kglDeleteProgram, kglGetProcAddress("glDeleteProgram"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetActiveUniform, kglGetProcAddress("glGetActiveUniform"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetActiveAttrib, kglGetProcAddress("glGetActiveAttrib"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetUniformLocation, kglGetProcAddress("glGetUniformLocation"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetAttribLocation, kglGetProcAddress("glGetAttribLocation"));
	K15_GL3_CHECK_ASSIGNMENT(kglBlendEquationSeparate, kglGetProcAddress("glBlendEquationSeparate"));
	K15_GL3_CHECK_ASSIGNMENT(kglBindFragDataLocation, kglGetProcAddress("glBindFragDataLocation"));
	K15_GL3_CHECK_ASSIGNMENT(kglGetProgramInfoLog, kglGetProcAddress("glGetProgramInfoLog"));
	K15_GL3_CHECK_ASSIGNMENT(kglBlendFuncSeparate, kglGetProcAddress("glBlendFuncSeparate"));
	K15_GL3_CHECK_ASSIGNMENT(kglGenFramebuffers, kglGetProcAddress("glGenFramebuffers"));
	K15_GL3_CHECK_ASSIGNMENT(kglBindFramebuffer, kglGetProcAddress("glBindFramebuffer"));
	K15_GL3_CHECK_ASSIGNMENT(kglDeleteFramebuffers, kglGetProcAddress("glDeleteFramebuffers"));
	K15_GL3_CHECK_ASSIGNMENT(kglGenRenderbuffers, kglGetProcAddress("glGenRenderbuffers"));
	K15_GL3_CHECK_ASSIGNMENT(kglBindRenderbuffer, kglGetProcAddress("glBindRenderbuffer"));
	K15_GL3_CHECK_ASSIGNMENT(kglDeleteRenderbuffers, kglGetProcAddress("glDeleteRenderbuffers"));
	K15_GL3_CHECK_ASSIGNMENT(kglRenderbufferStorage, kglGetProcAddress("glRenderbufferStorage"));
	K15_GL3_CHECK_ASSIGNMENT(kglFramebufferRenderbuffer, kglGetProcAddress("glFramebufferRenderbuffer"));
	K15_GL3_CHECK_ASSIGNMENT(kglFramebufferTexture, kglGetProcAddress("glFramebufferTexture"));
	K15_GL3_CHECK_ASSIGNMENT(kglCheckFramebufferStatus, kglGetProcAddress("glCheckFramebufferStatus"));
	K15_GL3_CHECK_ASSIGNMENT(kglRenderbufferStorageMultisample, kglGetProcAddress("glRenderbufferStorageMultisample"));
	K15_GL3_CHECK_ASSIGNMENT(kglTexImage3D, kglGetProcAddress("glTexImage3D"));
	K15_GL3_CHECK_ASSIGNMENT(kglCompressedTexImage1D, kglGetProcAddress("glCompressedTexImage1D"));
	K15_GL3_CHECK_ASSIGNMENT(kglCompressedTexImage2D, kglGetProcAddress("glCompressedTexImage2D"));
	K15_GL3_CHECK_ASSIGNMENT(kglCompressedTexImage3D, kglGetProcAddress("glCompressedTexImage3D"));
	K15_GL3_CHECK_ASSIGNMENT(kglGenerateMipmap, kglGetProcAddress("glGenerateMipmap"));
	K15_GL3_CHECK_ASSIGNMENT(kglActiveTexture, kglGetProcAddress("glActiveTexture"));
	K15_GL3_CHECK_ASSIGNMENT(kglDebugMessageCallback, kglGetProcAddress("glDebugMessageCallbackARB"));
	K15_GL3_CHECK_ASSIGNMENT(kglGenVertexArrays, kglGetProcAddress("glGenVertexArrays"));
	K15_GL3_CHECK_ASSIGNMENT(kglBindVertexArray, kglGetProcAddress("glBindVertexArray"));
	K15_GL3_CHECK_ASSIGNMENT(kglDeleteVertexArrays, kglGetProcAddress("glDeleteVertexArrays"));
	K15_GL3_CHECK_ASSIGNMENT(kglUniform1f, kglGetProcAddress("glUniform1f"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform2f, kglGetProcAddress("glUniform2f"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform3f, kglGetProcAddress("glUniform3f"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform4f, kglGetProcAddress("glUniform4f"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform1fv,	kglGetProcAddress("glUniform1fv"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform2fv,	kglGetProcAddress("glUniform2fv"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform3fv,	kglGetProcAddress("glUniform3fv"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform4fv,	kglGetProcAddress("glUniform4fv"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform1i, kglGetProcAddress("glUniform1i"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform2i, kglGetProcAddress("glUniform2i"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform3i, kglGetProcAddress("glUniform3i"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform4i, kglGetProcAddress("glUniform4i"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform1iv,	kglGetProcAddress("glUniform1iv"));		
	K15_GL3_CHECK_ASSIGNMENT(kglUniform2iv,	kglGetProcAddress("glUniform2iv"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform3iv,	kglGetProcAddress("glUniform3iv"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniform4iv,	kglGetProcAddress("glUniform4iv"));			
	K15_GL3_CHECK_ASSIGNMENT(kglUniformMatrix2fv, kglGetProcAddress("glUniformMatrix2fv"));
	K15_GL3_CHECK_ASSIGNMENT(kglUniformMatrix3fv, kglGetProcAddress("glUniformMatrix3fv"));
	K15_GL3_CHECK_ASSIGNMENT(kglUniformMatrix4fv, kglGetProcAddress("glUniformMatrix4fv"));

	kglDebugMessageCallback(K15_DebugProcARB, 0);
}

#endif //_K15_GL3_h_
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>

#define K15_OPENGL_ENABLE_ERROR_CHECK_CALLS
#include "k15_gl3.h"

#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define K15_FALSE 0
#define K15_TRUE 1

typedef unsigned char bool8;
typedef unsigned char byte;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
void resizeBackbuffer(HWND p_HWND, uint32 p_Width, uint32 p_Height);

uint32 screenWidth = 1024;
uint32 screenHeight = 768;

GLint vbo = 0;
GLint ibo = 0;
GLint vao = 0;
GLint shaderProgram = 0;
GLint projUniform = 0;
GLint textureUniform = 0;
K15_GUIContext guiContext;

uint32 convertColor(kg_color32 p_Color)
{
	int r = (uint8)(p_Color >> 0);
	int g = (uint8)(p_Color >> 8);
	int b = (uint8)(p_Color >> 16);
	int a = (uint8)(p_Color >> 24);

	float fR = (float)r / 255.f;
	float fG = (float)g / 255.f;
	float fB = (float)b / 255.f;

	fR = powf(fR, 1.f / 2.2f);
	fG = powf(fG, 1.f / 2.2f);
	fB = powf(fB, 1.f / 2.2f);

	r = (int)(fR * 255.f);
	g = (int)(fG * 255.f);
	b = (int)(fB * 255.f);

	return RGB(r, g, b);
}

GLuint iconTextureHandle;
GLuint fontTextureHandle;

void setupResources(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "accept.png", "load");
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "add.png", "load2");
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "anchor.png", "load3");

	K15_GUIIconSet* icons = 0;
	K15_GUIBakeIconResources(p_GUIResourceDatabase, &icons, "default_iconset");

	K15_GUIFont* font = 0;
	K15_GUIGetFontResource(p_GUIResourceDatabase, &font, "default_font");
	
	uint32 fontPixelBufferSize = K15_GUICalculateFontPixelBufferSizeInBytes(font, K15_GUI_PIXEL_FORMAT_R8G8B8);
	void* fontPixelBuffer = malloc(fontPixelBufferSize);

	uint32 iconPixelBufferSize = K15_GUICalculateIconSetPixelBufferSizeInBytes(icons, K15_GUI_PIXEL_FORMAT_R8G8B8);
	void* iconPixelBuffer= malloc(fontPixelBufferSize);

	int iconTextureWidth = 0;
	int iconTextureHeight = 0;
	int fontTextureWidth = 0;
	int fontTextureHeight = 0;

	K15_GUICopyIconSetTextureIntoPixelBuffer(icons, iconPixelBuffer, K15_GUI_PIXEL_FORMAT_R8G8B8, &iconTextureWidth, &iconTextureHeight);
	K15_GUICopyFontTextureIntoPixelBuffer(font, fontPixelBuffer, K15_GUI_PIXEL_FORMAT_R8G8B8, &fontTextureWidth, &fontTextureHeight);

	K15_OPENGL_CALL(kglGenTextures(1, &iconTextureHandle));
	K15_OPENGL_CALL(kglGenTextures(1, &fontTextureHandle));

	K15_OPENGL_CALL(kglBindTexture(GL_TEXTURE_2D, iconTextureHandle));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
	K15_OPENGL_CALL(kglTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, iconTextureWidth, iconTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, iconPixelBuffer));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	
	K15_OPENGL_CALL(kglBindTexture(GL_TEXTURE_2D, fontTextureHandle));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
	K15_OPENGL_CALL(kglTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, fontTextureWidth, fontTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, fontPixelBuffer));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	K15_OPENGL_CALL(kglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	K15_GUISetIconSetTextureUserData(icons, iconTextureHandle);
	K15_GUISetFontTextureUserData(font, fontTextureHandle);
}

void updateGUI(K15_GUIContext* p_GUIContext)
{
	static kg_b8 showWindow = 0;
	static kg_s16 windowPosX = 0;
	static kg_s16 windowPosY = 0;
	static kg_u16 windowWidth = 200;
	static kg_u16 windowHeight = 100;
	static float sliderValue = 0.f;
	char* message = (char*)alloca(512);

	K15_GUIBeginFrame(p_GUIContext);
	K15_GUIBeginToolBar(p_GUIContext, "toolbar_1");

	if (K15_GUIBeginMenu(p_GUIContext, "File", "file"))
	{
		if (K15_GUIMenuItem(p_GUIContext, "Open...", "open_1"))
		{
			printf("Open pressed...\n");
		}

		if (K15_GUIMenuItem(p_GUIContext, "Close", "close_1"))
		{
			exit(0);
		}

		K15_GUISeparator(p_GUIContext);

		if (K15_GUIBeginMenu(p_GUIContext, "Even More", "more_1"))
		{
			if (K15_GUIMenuItem(p_GUIContext, "Open Window", "open_window_1"))
			{
				showWindow = !showWindow;
			}

			K15_GUIEndMenu(p_GUIContext);
		}
		K15_GUIEndMenu(p_GUIContext);
	}

	K15_GUIBeginMenu(p_GUIContext, "Edit", "edit");
	K15_GUIBeginMenu(p_GUIContext, "View", "view");

	K15_GUIEndToolBar(p_GUIContext);

	if (showWindow)
	{
		if (K15_GUIBeginWindow(p_GUIContext, &windowPosY, &windowPosY, &windowHeight, &windowHeight,
			"Test Window", "test_window_1"))
		{
			K15_GUILabel(p_GUIContext, "Print float:", "label_1");
			//				K15_GUINextLine(p_GUIContext);
			//				K15_GUIFloatSlider(p_GUIContext, &sliderValue, 0.f, 10.f, "slider_1");
			if (K15_GUIButton(p_GUIContext, "Print float", "print_1"))
			{
				printf("Float: %.3f\n", sliderValue);
			}
			K15_GUIEndWindow(p_GUIContext);
		}
	}

	kg_result lastResult = K15_GUIGetLastResult(p_GUIContext);
	if (lastResult != K15_GUI_RESULT_SUCCESS)
	{
		kg_u32 bytesWritten = K15_GUIConvertResultToMessage(lastResult, &message, 512);
		message[bytesWritten] = 0;
		printf("Error: %s\n", message);
	}
	K15_GUIFinishFrame(p_GUIContext);
}

void drawGUI(K15_GUIContext* p_GUIContext)
{
	K15_GUIDrawInformation* drawInformation = &p_GUIContext->drawInformation;
	int indexSizeInBytes = drawInformation->indexSizeInBytes;

	if (drawInformation->numDrawCommands > 0)
	{
		K15_OPENGL_CALL(kglBufferData(GL_ARRAY_BUFFER, drawInformation->vertexBufferDataSizeInBytes, drawInformation->vertexBufferData, GL_DYNAMIC_DRAW));
		K15_OPENGL_CALL(kglBufferData(GL_ELEMENT_ARRAY_BUFFER, drawInformation->indexBufferDataSizeInBytes, drawInformation->indexBufferData, GL_DYNAMIC_DRAW));

		for (uint32 drawCommandIndex = 0;
			drawCommandIndex < drawInformation->numDrawCommands;
			++drawCommandIndex)
		{
			K15_GUIDrawCommand* drawCommand = drawInformation->drawCommands + drawCommandIndex;
			kg_u64 textureUserData = drawCommand->textureUserData;
			kg_u32 numTriangles = drawCommand->numTriangles;
			kg_u32 vertexOffset = drawCommand->vertexOffset;
			kg_u32 indexOffset = drawCommand->indexOffset;

			K15_OPENGL_CALL(kglBindTexture(GL_TEXTURE_2D, (GLuint)textureUserData));
			K15_OPENGL_CALL(kglDrawElements(GL_TRIANGLES, numTriangles * 3, indexSizeInBytes == 4 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT, (const void*)(indexOffset * indexSizeInBytes)));
		}
	}
}

void K15_WindowCreated(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	
}

void K15_WindowClosed(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_WindowResized(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	WORD newWidth = (WORD)(p_lParam);
	WORD newHeight = (WORD)(p_lParam >> 16);

	resizeBackbuffer(p_HWND, newWidth, newHeight);

	K15_GUISystemEvent systemEvent;
	systemEvent.type = K15_GUI_WINDOW_RESIZED;
	systemEvent.params.size.height = newHeight;
	systemEvent.params.size.width = newWidth;

	float projMatrix[16];
	K15_GUICalculateColumnMajorProjectionMatrix(projMatrix, 
		newWidth, newHeight, K15_GUI_INVERT_Y_AXIS);

	K15_OPENGL_CALL(kglUniformMatrix4fv(projUniform, 1, GL_FALSE, projMatrix));

	K15_GUIAddSystemEvent(&guiContext.events, systemEvent);
}

void K15_KeyInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_MouseButtonInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	K15_GUIMouseInput mouseInput = { 0 };
	mouseInput.data.mouseButton = K15_GUI_MOUSE_BUTTON_LEFT;
	mouseInput.type = K15_GUI_MOUSE_BUTTON_PRESSED;

	K15_GUIAddMouseInput(&guiContext.events, mouseInput);
}

void K15_MouseMove(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	WORD posX = (WORD)(p_lParam);
	WORD posY = (WORD)(p_lParam >> 16);

	K15_GUIMouseInput mouseInput = { 0 };
	mouseInput.data.mousePos.x = posX;
	mouseInput.data.mousePos.y = posY;
	mouseInput.type = K15_GUI_MOUSE_MOVED;

	K15_GUIAddMouseInput(&guiContext.events, mouseInput);
}

void K15_MouseWheel(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

LRESULT CALLBACK K15_WNDPROC(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	bool8 messageHandled = K15_FALSE;

	switch (p_Message)
	{
	case WM_CREATE:
		K15_WindowCreated(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_CLOSE:
		K15_WindowClosed(p_HWND, p_Message, p_wParam, p_lParam);
		PostQuitMessage(0);
		messageHandled = K15_TRUE;
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		K15_KeyInput(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_XBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_XBUTTONDOWN:
		K15_MouseButtonInput(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_SIZE:
		K15_WindowResized(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_MOUSEMOVE:
		K15_MouseMove(p_HWND, p_Message, p_wParam, p_lParam);
		break;

	case WM_MOUSEWHEEL:
		K15_MouseWheel(p_HWND, p_Message, p_wParam, p_lParam);
		break;
	}

	if (messageHandled == K15_FALSE)
	{
		return DefWindowProc(p_HWND, p_Message, p_wParam, p_lParam);
	}

	return 0;
}

HWND setupWindow(HINSTANCE p_Instance, int p_Width, int p_Height)
{
	WNDCLASS wndClass = {0};
	wndClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
	wndClass.hInstance = p_Instance;
	wndClass.lpszClassName = "K15_Win32Template";
	wndClass.lpfnWndProc = K15_WNDPROC;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&wndClass);

	HWND hwnd = CreateWindowA("K15_Win32Template", "Win32 Template",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		p_Width, p_Height, 0, 0, p_Instance, 0);

	K15_GL3RegisterWGLFunctions(hwnd);

	if (hwnd == INVALID_HANDLE_VALUE)
		MessageBox(0, "Error creating Window.\n", "Error!", 0);
	else
		ShowWindow(hwnd, SW_SHOW);
	return hwnd;
}

uint32 getTimeInMilliseconds(LARGE_INTEGER p_PerformanceFrequency)
{
	LARGE_INTEGER appTime = {0};
	QueryPerformanceCounter(&appTime);

	appTime.QuadPart *= 1000; //to milliseconds

	return (uint32)(appTime.QuadPart / p_PerformanceFrequency.QuadPart);
}

void resizeBackbuffer(HWND p_HWND, uint32 p_Width, uint32 p_Height)
{
	screenWidth = p_Width;
	screenHeight = p_Height;
	kglViewport(0, 0, p_Width, p_Height);
}

char* getInfoLogForShader(GLuint p_Shader)
{
	GLint infoLogLength = 0;
	K15_OPENGL_CALL(kglGetShaderiv(p_Shader, GL_INFO_LOG_LENGTH, &infoLogLength));
	char* infoLog = 0;

	if (infoLogLength > 0)
	{
		infoLog = (char*)malloc(infoLogLength);
		kglGetShaderInfoLog(p_Shader, infoLogLength, 0, infoLog);
	}
	return infoLog;
}

void setup(HWND p_HWND)
{
	const char* vertexShaderSource = ""
		"#version 330\n"
		"uniform mat4 projMatrix;"
		"in vec2 position;\n"
		"in vec2 uv;\n"
		"in vec4 color;\n"
		"out vec4 fragColor;\n"
		"out vec2 fragUV;\n"
		"out gl_PerVertex{\n"
		"vec4 gl_Position;\n"
		"float gl_PointSize;\n"
		"float gl_ClipDistance[];\n"
		"};\n"
		"void main()\n"
		"{\n"
		"	fragColor = color;\n"
		"	fragUV = uv;\n"
		"	vec4 pos = vec4(position.x, position.y, 1.f, 1.f);"
		"	gl_Position = projMatrix * pos;\n"
		"}";

	const char* fragmentShaderSource = ""
		"#version 330\n"
		"in vec4 fragColor;\n"
		"in vec2 fragUV;\n"
		"uniform sampler2D textureSampler;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = texture(textureSampler, fragUV);\n"
		"}";

	kg_u32 vertexShaderSourceLength = strlen(vertexShaderSource);
	kg_u32 fragmentShaderSourceLenght = strlen(fragmentShaderSource);

	K15_OPENGL_CALL(kglGenBuffers(1, &vbo));
	K15_OPENGL_CALL(kglGenBuffers(1, &ibo));
	K15_OPENGL_CALL(kglGenVertexArrays(1, &vao));

	K15_OPENGL_CALL(kglFrontFace(GL_CW));
	K15_OPENGL_CALL(kglCullFace(GL_FRONT));

	K15_OPENGL_CALL(kglBindVertexArray(vao));
	K15_OPENGL_CALL(kglBindBuffer(GL_ARRAY_BUFFER, vbo));
	K15_OPENGL_CALL(kglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

	kg_u32 sizeVertexStrideInBytes = K15_GUI_VERTEX_SIZE_IN_BYTES;

	K15_OPENGL_CALL(shaderProgram = kglCreateProgram());

	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;

	K15_OPENGL_CALL(vertexShader = kglCreateShader(GL_VERTEX_SHADER));
	K15_OPENGL_CALL(fragmentShader = kglCreateShader(GL_FRAGMENT_SHADER));

	K15_OPENGL_CALL(kglShaderSource(vertexShader, 1, &vertexShaderSource, &vertexShaderSourceLength));
	K15_OPENGL_CALL(kglShaderSource(fragmentShader, 1, &fragmentShaderSource, &fragmentShaderSourceLenght));

	K15_OPENGL_CALL(kglCompileShader(vertexShader));
	K15_OPENGL_CALL(kglCompileShader(fragmentShader));

	GLint vertexShaderCompileStatus = 0;
	GLint fragmentShaderCompileStatus = 0;
	K15_OPENGL_CALL(kglGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus));
	K15_OPENGL_CALL(kglGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus));

	if (vertexShaderCompileStatus == GL_FALSE)
	{
		const char* error = getInfoLogForShader(vertexShader);
		MessageBoxA(p_HWND, error, "Vertex Shader Error!", 0);
	}

	if (fragmentShaderCompileStatus == GL_FALSE)
	{
		const char* error = getInfoLogForShader(fragmentShader);
		MessageBoxA(p_HWND, error, "Fragment Shader Error!", 0);
	}

	K15_OPENGL_CALL(kglAttachShader(shaderProgram, vertexShader));
	K15_OPENGL_CALL(kglAttachShader(shaderProgram, fragmentShader));
	K15_OPENGL_CALL(kglLinkProgram(shaderProgram));

	GLint linkStatus = 0;
	K15_OPENGL_CALL(kglGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus));

	if (linkStatus == GL_FALSE)
	{
		GLint programLogLength = 0;
		K15_OPENGL_CALL(kglGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &programLogLength));

		if (programLogLength > 0)
		{
			char* programLog = (char*)malloc(programLogLength);
			K15_OPENGL_CALL(kglGetProgramInfoLog(shaderProgram, programLogLength, 0, programLog));
			MessageBoxA(p_HWND, programLog, "Shader Linker Error!", 0);
		}
	}

	GLint posAttribLocation = 0;
	GLint uvAttribLocation = 0;
	GLint colorAttribLocation = 0;

	//get register location using attribute name
	K15_OPENGL_CALL(posAttribLocation = kglGetAttribLocation(shaderProgram, "position"));
 	K15_OPENGL_CALL(uvAttribLocation = kglGetAttribLocation(shaderProgram, "uv"));
 	K15_OPENGL_CALL(colorAttribLocation = kglGetAttribLocation(shaderProgram, "color"));

	int attribArrayIndex = 0;

	if (posAttribLocation >= 0)
	{
		K15_OPENGL_CALL(kglEnableVertexAttribArray(attribArrayIndex++));
		K15_OPENGL_CALL(kglVertexAttribPointer(posAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeVertexStrideInBytes, 0));
	}

	if (uvAttribLocation >= 0)
	{
		K15_OPENGL_CALL(kglEnableVertexAttribArray(attribArrayIndex++));
		K15_OPENGL_CALL(kglVertexAttribPointer(uvAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeVertexStrideInBytes, (const void*)(sizeof(float) * 2)));
	}

	if (colorAttribLocation >= 0)
	{
		K15_OPENGL_CALL(kglEnableVertexAttribArray(attribArrayIndex));
		K15_OPENGL_CALL(kglVertexAttribPointer(colorAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeVertexStrideInBytes, (const void*)(sizeof(float) * 4)));
	}

	K15_OPENGL_CALL(projUniform = kglGetUniformLocation(shaderProgram, "projMatrix"));
	K15_OPENGL_CALL(textureUniform = kglGetUniformLocation(shaderProgram, "textureSampler"));

	K15_OPENGL_CALL(kglUseProgram(shaderProgram));

	K15_OPENGL_CALL(kglUniform1i(textureUniform, 0));
	K15_OPENGL_CALL(kglActiveTexture(GL_TEXTURE0));

	K15_WindowResized(p_HWND, 0, 0, (LPARAM)(screenWidth | (screenHeight << 16)));
}

void swapBuffers(HWND p_HWND)
{
	HDC deviceContext = GetDC(p_HWND);
	SwapBuffers(deviceContext);
	kglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawDeltaTime(uint32 p_DeltaTimeInMS)
{

}

void doFrame(K15_GUIContext* p_GUIContext, uint32 p_DeltaTimeInMS, HWND p_HWND)
{
	drawDeltaTime(p_DeltaTimeInMS);
	updateGUI(p_GUIContext);
	drawGUI(p_GUIContext);

	swapBuffers(p_HWND);
}

int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	const uint32 msPerFrame = 16;

	LARGE_INTEGER performanceFrequency;
	QueryPerformanceFrequency(&performanceFrequency);

	HWND hwnd = setupWindow(hInstance, screenWidth, screenHeight);

	if (hwnd == INVALID_HANDLE_VALUE)
		return -1;

	setup(hwnd);

	K15_GUIResourceDatabase guiResourceDatabase = { 0 };
	kg_result result = K15_GUICreateResourceDatabase(&guiResourceDatabase);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		char* errorMsg = (char*)alloca(256);
		K15_GUIConvertResultToMessage(result, &errorMsg, 256);

		printf("Error during resource database creation: '%s'\n", errorMsg);
	}

	result = K15_CreateGUIContext(&guiContext, &guiResourceDatabase, 0, 0, screenWidth, screenHeight);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		char* errorMsg = (char*)alloca(256);
		K15_GUIConvertResultToMessage(result, &errorMsg, 256);

		printf("Error during context creation: '%s'\n", errorMsg);
	}

	setupResources(&guiResourceDatabase);

	uint32 timeFrameStarted = 0;
	uint32 timeFrameEnded = 0;
	uint32 deltaMs = 0;

	bool8 loopRunning = K15_TRUE;
	MSG msg = {0};

	while (loopRunning)
	{
		timeFrameStarted = getTimeInMilliseconds(performanceFrequency);

		while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				loopRunning = K15_FALSE;
		}

		doFrame(&guiContext, deltaMs, hwnd);

// 		StretchBlt(backbufferDC, 0, 0, iW, iH, iconDC, 0, 0, iW, iH, SRCCOPY);
// 		swapBuffers(hwnd);

		timeFrameEnded = getTimeInMilliseconds(performanceFrequency);
		deltaMs = timeFrameEnded - timeFrameStarted;

		//60FPS
		if (deltaMs < msPerFrame)
			Sleep(msPerFrame - deltaMs);
	}

	return 0;
}
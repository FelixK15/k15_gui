#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <GL/GL.h>

#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"

#define GL_CALL(x) x; {GLenum _err; while(_err = glGetError() != 0){__debugbreak();}}

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "opengl32.lib")

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

	GL_CALL(glGenTextures(1, &iconTextureHandle));
	GL_CALL(glGenTextures(1, &fontTextureHandle));

	GL_CALL(glBindTexture(GL_TEXTURE_2D, iconTextureHandle));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, 3, iconTextureWidth, iconTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, iconPixelBuffer));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	
	GL_CALL(glBindTexture(GL_TEXTURE_2D, fontTextureHandle));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, 3, fontTextureWidth, fontTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, fontPixelBuffer));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

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

	if (K15_GUIBeginMenu(p_GUIContext, "File0123456789.,!", "file_1"))
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
		}
		K15_GUIEndMenu(p_GUIContext);
	}

	K15_GUIBeginMenu(p_GUIContext, "File", "file_2");
	K15_GUIBeginMenu(p_GUIContext, "File", "file_3");

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
	K15_GUIDrawCommandBuffer drawCommandBuffer = { 0 };
	K15_GUICopyDrawCommandBuffer(p_GUIContext, &drawCommandBuffer);

	//updateVertexBuffer(guiVertexBuffer, drawCommandBuffer.vertexData, drawCommandBuffer.vertexDataSize);

	for (uint32 drawCommandIndex = 0;
		drawCommandIndex < drawCommandBuffer.numDrawCommands;
		++drawCommandIndex)
	{
		K15_GUIDrawCommand* drawCommand = drawCommandBuffer.drawCommands + drawCommandIndex;
		
		drawCommand->textureUserData;
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
	glViewport(0, 0, p_Width, p_Height);
}

void setup(HWND p_HWND)
{
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

	HGLRC glContext = wglCreateContext(deviceContext);

	wglMakeCurrent(deviceContext, glContext);

	//set default gl state
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0.f, 0.f, 0.f, 1.f);

	glEnable(GL_TEXTURE_2D);
}

void swapBuffers(HWND p_HWND)
{
	HDC deviceContext = GetDC(p_HWND);
	SwapBuffers(deviceContext);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <math.h>

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
kg_context guiContext;

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


void updateGUI()
{
	kg_context* pContext = &guiContext;
	kg_begin_frame(pContext);

	if (kg_begin_window(pContext, "TestWindow", "window_0"))
	{
		kg_end_window(pContext);
	}

	kg_end_frame(pContext);

	kg_error* pError = 0;
	while( kg_pop_error(pContext, &pError) )
	{
		printf("Error occured: %s\n", pError->pErrorString);
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

}

void K15_KeyInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_MouseButtonInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_MouseMove(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

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

void allocateDebugConsole()
{
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
}

HWND setupWindow(HINSTANCE p_Instance, int p_Width, int p_Height)
{
	WNDCLASS wndClass = {0};
	HWND hwnd = INVALID_HANDLE_VALUE;

	wndClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
	wndClass.hInstance = p_Instance;
	wndClass.lpszClassName = "K15_Win32Template";
	wndClass.lpfnWndProc = K15_WNDPROC;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&wndClass);

	hwnd = CreateWindowA("K15_Win32Template", "Win32 Template",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		p_Width, p_Height, 0, 0, p_Instance, 0);

	K15_GL3RegisterWGLFunctions(hwnd);

	if (hwnd == INVALID_HANDLE_VALUE)
		MessageBox(0, "Error creating Window.\n", "Error!", 0);
	else
	{
		allocateDebugConsole();
		ShowWindow(hwnd, SW_SHOW);
	}
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
	char* infoLog = 0;

	K15_OPENGL_CALL(kglGetShaderiv(p_Shader, GL_INFO_LOG_LENGTH, &infoLogLength));

	if (infoLogLength > 0)
	{
		infoLog = (char*)malloc(infoLogLength);
		kglGetShaderInfoLog(p_Shader, infoLogLength, 0, infoLog);
	}
	return infoLog;
}

void setup(HWND p_HWND)
{
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

void doFrame(uint32 p_DeltaTimeInMS, HWND p_HWND)
{
	drawDeltaTime(p_DeltaTimeInMS);

	swapBuffers(p_HWND);
}

int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	const uint32 msPerFrame = 16;
	HWND hwnd = INVALID_HANDLE_VALUE;
	LARGE_INTEGER performanceFrequency;

	QueryPerformanceFrequency(&performanceFrequency);

	hwnd = setupWindow(hInstance, screenWidth, screenHeight);

	if (hwnd == INVALID_HANDLE_VALUE)
		return -1;

	setup(hwnd);

	{
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

			doFrame(deltaMs, hwnd);

	// 		StretchBlt(backbufferDC, 0, 0, iW, iH, iconDC, 0, 0, iW, iH, SRCCOPY);
	// 		swapBuffers(hwnd);

			timeFrameEnded = getTimeInMilliseconds(performanceFrequency);
			deltaMs = timeFrameEnded - timeFrameStarted;

			//60FPS
			if (deltaMs < msPerFrame)
				Sleep(msPerFrame - deltaMs);
		}
	}
	

	return 0;
}
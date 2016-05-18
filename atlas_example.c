#include <windows.h>
#include <stdio.h>

#define K15_IA_IMPLEMENTATION
#include "K15_ImageAtlas.h"

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

HDC textDC = 0;
HDC backbufferDC = 0;
HBITMAP backbufferBitmap = 0;
uint32 screenWidth = 1024;
uint32 screenHeight = 768;

struct pos
{
	int x;
	int y;
};
K15_ImageAtlas atlas = {};
uint32 numNodes = 20;
uint32 insertedNodes = 0;
pos positions[20];

bool8 pressedLastFrame = K15_FALSE;

void K15_WindowCreated(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_WindowClosed(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_KeyInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	bool8 wasDown = ((p_lParam & (1 << 30)) != 0);
	bool8 isDown = ((p_lParam & (1 << 31)) == 0);

	if (isDown != wasDown)
	{
		if (isDown)
			pressedLastFrame = K15_TRUE;
	}
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
	WNDCLASS wndClass = {};
	wndClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
	wndClass.hInstance = p_Instance;
	wndClass.lpszClassName = "K15_Win32Template";
	wndClass.lpfnWndProc = K15_WNDPROC;
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
	LARGE_INTEGER appTime = {};
	QueryPerformanceCounter(&appTime);

	appTime.QuadPart *= 1000; //to milliseconds

	return (uint32)(appTime.QuadPart / p_PerformanceFrequency.QuadPart);
}

void setup(HWND p_HWND)
{
	HDC originalDC = GetDC(p_HWND);
	textDC = CreateCompatibleDC(originalDC);
	backbufferDC = CreateCompatibleDC(originalDC);
	backbufferBitmap = CreateCompatibleBitmap(originalDC, screenWidth, screenHeight);

	SetTextColor(backbufferDC, RGB(255, 255, 255));
	SetBkColor(backbufferDC, RGB(0, 0, 0));

	SelectObject(backbufferDC, backbufferBitmap);

	if (K15_IACreateAtlas(&atlas, KIA_PIXEL_FORMAT_R8G8B8A8, numNodes) != K15_IA_RESULT_SUCCESS)
		MessageBox(0, "Error creating atlas!", "Error", 0);
}

void swapBuffers(HWND p_HWND)
{
	HDC originalDC = GetDC(p_HWND);
	
	//blit to front buffer
	BitBlt(originalDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, SRCCOPY);

	//clear backbuffer
	BitBlt(backbufferDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, BLACKNESS);
}

void doFrame(uint32 p_DeltaTimeInMS, HWND p_HWND)
{
	char messageBuffer[256] = { 0 };
	sprintf_s(messageBuffer, 256, "MS: %d", p_DeltaTimeInMS);

	RECT textRect = {};
	textRect.left = 0;
	textRect.top = 0;
	textRect.bottom = screenHeight;
	textRect.right = screenWidth;

	DrawTextA(backbufferDC, messageBuffer, -1, &textRect, DT_LEFT | DT_TOP);
	swapBuffers(p_HWND);

	for (uint32 nodeIndex = 0;
		nodeIndex < insertedNodes;
		++nodeIndex)
	{
		HBRUSH tempBrush = CreateSolidBrush(RGB((24 * nodeIndex) % 255, 200, 200));
		SelectObject(backbufferDC, tempBrush);
		Rectangle(backbufferDC, positions[nodeIndex].x, positions[nodeIndex].y, positions[nodeIndex].x + 40, positions[nodeIndex].y + 60);
		DeleteObject(tempBrush);
	}

	if (pressedLastFrame)
	{
		K15_IAAddImageToAtlas(&atlas, KIA_PIXEL_FORMAT_R8G8B8A8, (kia_byte*)2, 40, 60, &positions[insertedNodes].x, &positions[insertedNodes].y);
		++insertedNodes;
	}

	pressedLastFrame = K15_FALSE;
}

int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	LARGE_INTEGER performanceFrequency;
	QueryPerformanceFrequency(&performanceFrequency);

	HWND hwnd = setupWindow(hInstance, screenWidth, screenHeight);

	if (hwnd == INVALID_HANDLE_VALUE)
		return -1;

	setup(hwnd);

	uint32 timeFrameStarted = 0;
	uint32 timeFrameEnded = 0;
	uint32 deltaMs = 0;

	bool8 loopRunning = K15_TRUE;
	MSG msg = {};

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

		timeFrameEnded = getTimeInMilliseconds(performanceFrequency);
		deltaMs = timeFrameEnded - timeFrameStarted;
	}

	return 0;
}
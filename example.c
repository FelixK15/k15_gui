#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>

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

HDC backbufferDC = 0;
HBITMAP backbufferBitmap = 0;
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

void setupResources(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "accept.png", "load");
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "add.png", "load2");
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "anchor.png", "load3");

	K15_GUIIconSet* icons = 0;
	K15_GUIBakeIconResources(p_GUIResourceDatabase, &icons, "default_iconset");

	stbi_write_png("test1.png", icons->texture.pixelWidth, icons->texture.pixelHeight,
		icons->texture.numColorComponents, icons->texture.pixelData,
		icons->texture.numColorComponents * icons->texture.pixelWidth);

	// 	kg_u32 fontTextureDataSizeInBytes = K15_GUIGetFontTextureDataSizeInBytes(arial12);
	// 	kg_byte* fontTextureData = (kg_byte*)malloc(fontTextureDataSizeInBytes);
	// 
	// 	K15_GUIGetFontTextureData(arial12, &fontTextureData, fontTextureDataSizeInBytes);
	// 	arial12->texture.userData = 1;
	// 
	// 	kg_u32 iconTextureDataSizeInBytes = K15_GUIGetIconSetTextureSizeInBytes(icons);
	// 	kg_byte* iconsTextureData = (kg_byte*)malloc(iconTextureDataSizeInBytes);
	// 
	// 	K15_GUIGetIconSetTextureData(icons, &iconsTextureData, iconTextureDataSizeInBytes);
	// 	icons->texture.userData = 2;
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

	if (K15_GUIBeginMenu(p_GUIContext, "File", "file_1"))
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

void drawRect(K15_GUIRectShapeData* p_RectShapeData)
{
	uint32 height = p_RectShapeData->rect.bottom - p_RectShapeData->rect.top;

	for (uint32 y = 0;
		y < height;
		++y)
	{
		float p = (float)y / (float)height;
		kg_color32 color = K15_GUISampleColorGradient(&p_RectShapeData->colorGradient, p);
		COLORREF c = convertColor(color);
		HPEN pen = CreatePen(PS_SOLID, 1, c);

		SelectObject(backbufferDC, pen);

		Rectangle(backbufferDC, p_RectShapeData->rect.left,
			y + p_RectShapeData->rect.top,
			p_RectShapeData->rect.right ,
			y + p_RectShapeData->rect.top + 1);

		DeleteObject(pen);
	}
}

void drawGUI(K15_GUIContext* p_GUIContext)
{
	kg_u32 sizeDrawCommandBuffer = K15_GUICalculateDrawCommandBufferSizeInBytes(p_GUIContext);
	K15_GUIDrawCommandBuffer drawCommandBuffer = { 0 };

	K15_GUICopyDrawCommandBuffer(p_GUIContext, &drawCommandBuffer);

	while (K15_GUIHasDrawCommand(&drawCommandBuffer))
	{
		K15_GUIDrawCommand* drawCommand = 0;
		K15_GUIGetDrawCommand(&drawCommandBuffer, &drawCommand);

		switch (drawCommand->type)
		{
		case K15_GUI_DRAW_RECT_COMMAND:
		{
			K15_GUIRectShapeData rectShapeData = { 0 };
			K15_GUIGetDrawCommandData(&drawCommandBuffer, drawCommand, &rectShapeData, sizeof(rectShapeData), 0);
			drawRect(&rectShapeData);
			break;
		}

		case K15_GUI_DRAW_TEXT_COMMAND:
		{
			K15_GUITextShapeData textShapeData = { 0 };
			K15_GUIGetDrawCommandData(&drawCommandBuffer, drawCommand, &textShapeData, sizeof(textShapeData), 0);
			char* text = 0;
			K15_GUIGetDrawCommandDataRaw(&drawCommandBuffer, drawCommand, (void**)&text, sizeof(textShapeData));
			int bla = 0;
			bla = bla;
			//drawText(&textShapeData);
			break;
		}

		default:
			break;
		}

		K15_GUINextDrawCommand(&drawCommandBuffer);
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

HWND setupWindow(HINSTANCE p_Instance, int p_Width, int p_Height)
{
	WNDCLASS wndClass = {0};
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
	LARGE_INTEGER appTime = {0};
	QueryPerformanceCounter(&appTime);

	appTime.QuadPart *= 1000; //to milliseconds

	return (uint32)(appTime.QuadPart / p_PerformanceFrequency.QuadPart);
}

void resizeBackbuffer(HWND p_HWND, uint32 p_Width, uint32 p_Height)
{
	DeleteObject(backbufferBitmap);

	HDC originalDC = GetDC(p_HWND);
	backbufferBitmap = CreateCompatibleBitmap(originalDC, p_Width, p_Height);
	screenWidth = p_Width;
	screenHeight = p_Height;

	SelectObject(backbufferDC, backbufferBitmap);
}

void setup(HWND p_HWND)
{
	HDC originalDC = GetDC(p_HWND);
	backbufferDC = CreateCompatibleDC(originalDC);
	backbufferBitmap = CreateCompatibleBitmap(originalDC, screenWidth, screenHeight);

	SelectObject(backbufferDC, backbufferBitmap);
}

void swapBuffers(HWND p_HWND)
{
	HDC originalDC = GetDC(p_HWND);

	//blit to front buffer
	BitBlt(originalDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, SRCCOPY);

	//clear backbuffer
	BitBlt(backbufferDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, BLACKNESS);
}

void drawDeltaTime(uint32 p_DeltaTimeInMS)
{
	RECT textRect;
	textRect.left = 70;
	textRect.top = 70;
	textRect.bottom = screenHeight;
	textRect.right = screenWidth;

	char messageBuffer[64];
	SetTextColor(backbufferDC, RGB(255, 255, 255));
	SetBkColor(backbufferDC, RGB(0, 0, 0));

	sprintf_s(messageBuffer, 64, "MS: %d", p_DeltaTimeInMS);
	DrawTextA(backbufferDC, messageBuffer, -1, &textRect, DT_LEFT | DT_TOP);
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

		timeFrameEnded = getTimeInMilliseconds(performanceFrequency);
		deltaMs = timeFrameEnded - timeFrameStarted;

		//60FPS
		if (deltaMs < msPerFrame)
			Sleep(msPerFrame - deltaMs);
	}

	return 0;
}
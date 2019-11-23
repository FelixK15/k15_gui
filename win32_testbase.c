#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <shellscalingapi.h>
#include <stdio.h>
#include <wingdi.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "Shcore.lib")

#define K15_FALSE 0
#define K15_TRUE 1

typedef unsigned char 	bool8;
typedef unsigned char 	byte;
typedef unsigned int 	uint32;
typedef unsigned short 	uint16;
typedef unsigned char 	uint8;

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

kg_float2* pPoints = kg_nullptr;
kg_line_float_2d* pLines = kg_nullptr;

float scaleFactor = 0.3f;
kg_float2 offset = {0.0f, 50.0f};
size_t normalCount;
int codePoint = 'I';
size_t pointCount;
size_t lineCount;
const size_t maxPointCount = 20u;
float error = 0.98f;
int s_drawLinePoints = 1;

void resizeBackbuffer(HWND p_HWND, uint32 p_Width, uint32 p_Height);

BITMAPINFO glyphInfo;
HDC backbufferDC = 0;
HBITMAP backbufferBitmap = 0;
uint32 screenWidth = 1024;
uint32 screenHeight = 768;
uint32 timePerFrameInMS = 16;

kg_linear_allocator allocator;
kg_texture_atlas atlas;

void generateCurvePoints()
{
#if 1
	kg_float2 p0 = {30.0f, 30.0f};
	kg_float2 p1 = {(float)screenWidth - 30.f, 30.0f};
	kg_float2 cp = {(float)screenWidth*0.5f, (float)screenHeight};
#else
	kg_float2 p0 = {0.0f, 0.0f};
	kg_float2 p1 = {(float)screenWidth, (float)screenHeight};
	kg_float2 cp = {(float)screenWidth, 0.0f};
#endif

	pointCount = kg_generate_line_points_on_quadratic_curve(pPoints, maxPointCount, p0, p1, cp, error);
}

void generateGlyphPoints()
{
	kg_clear_texture_atlas(&atlas);
	HANDLE arialFontHandle = CreateFile("C:/Windows/Fonts/arial.ttf", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, INVALID_HANDLE_VALUE);
	assert(arialFontHandle != INVALID_HANDLE_VALUE);

	HANDLE arialFontMapHandle = CreateFileMapping(arialFontHandle, NULL, PAGE_READONLY, 0, 0, NULL);
	assert(arialFontMapHandle != INVALID_HANDLE_VALUE);

	void* pArialFontMapData = MapViewOfFile(arialFontMapHandle, FILE_MAP_READ, 0, 0, 0);
	kg_buffer fontBuffer = kg_create_buffer(pArialFontMapData, GetFileSize(arialFontHandle, NULL));
	
	kg_true_type_font font;
	kg_init_true_type_font(&font, &fontBuffer, NULL);
	kg_glyph_id glyphId;
	kg_result result = kg_parse_true_type_code_point_glyph_id(&font, &glyphId, codePoint);
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		lineCount = 0u;
		return;
	}
	kg_u32 offset = font.tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] + 18;
	kg_u16 unitsPerEm = 0u;
	kg_read_data(&unitsPerEm, &font.data, &offset );

	kg_rasterize_true_type_glyph(&allocator, NULL, &atlas, &font, glyphId, unitsPerEm, 96, 24 );
	stbi_write_png("test.png", atlas.size.x, atlas.size.y, atlas.pixelFormat, atlas.pImageData, atlas.size.x);

	UnmapViewOfFile(pArialFontMapData);
	CloseHandle(arialFontMapHandle);
	CloseHandle(arialFontHandle);
}

void printErrorToFile(const char* p_FileName)
{
	DWORD errorId = GetLastError();
	char* textBuffer = 0;
	DWORD writtenChars = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, errorId, 
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPSTR)&textBuffer, 512, 0);

	if (writtenChars > 0)
	{
		FILE* file = fopen(p_FileName, "w");

		if (file)
		{
			fwrite(textBuffer, writtenChars, 1, file);			
			fflush(file);
			fclose(file);
		}
	}
}

void allocateDebugConsole()
{
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
}

void K15_WindowCreated(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_WindowClosed(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{

}

void K15_KeyInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	if (p_Message == WM_KEYDOWN)
	{
		if (p_wParam == VK_DOWN)
		{
			if (error > 0.f)
			{
				error -= 0.01f;
				if (error < 0.f)
				{
					error = 0.f;
				}

				generateGlyphPoints();
			}
		}
		else if (p_wParam == VK_UP)
		{
			if (error < 1.f)
			{
				error += 0.01f;
				if (error > 1.f)
				{
					error = 1.f;
				}
				
				generateGlyphPoints();
			}
		}
		else if (p_wParam == VK_LEFT)
		{
			codePoint--;
			generateGlyphPoints();
		}
		else if (p_wParam == VK_RIGHT)
		{
			codePoint++;
			generateGlyphPoints();
		}
		else if (p_wParam == VK_F5)
		{
			generateGlyphPoints();
		}
		else if (p_wParam == VK_SPACE)
		{
			s_drawLinePoints = !s_drawLinePoints;
		}
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

void K15_WindowResized(HWND p_HWND, UINT p_Messaeg, WPARAM p_wParam, LPARAM p_lParam)
{
	WORD newWidth = (WORD)(p_lParam);
	WORD newHeight = (WORD)(p_lParam >> 16);

	resizeBackbuffer(p_HWND, newWidth, newHeight);
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

	case WM_SIZE:
		K15_WindowResized(p_HWND, p_Message, p_wParam, p_lParam);
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
	DeleteObject(backbufferBitmap);

	HDC originalDC = GetDC(p_HWND);
	backbufferBitmap = CreateCompatibleBitmap(originalDC, p_Width, p_Height);
	screenWidth = p_Width;
	screenHeight = p_Height;
	
	SelectObject(backbufferDC, backbufferBitmap);
}

void setup(HWND p_HWND)
{
	const uint32 atlasWidth = 256;
	const uint32 atlasHeight = 256;
	const kg_pixel_format atlasFormat = K15_GUI_PIXEL_FORMAT_R8;
	const uint32 atlasSizeInBytes = atlasWidth * atlasHeight * atlasFormat;
	HDC originalDC = GetDC(p_HWND);
	backbufferDC = CreateCompatibleDC(originalDC);

	kg_buffer allocatorBuffer = kg_create_buffer(malloc(1024*1024*5), 1024*1024*5);
	kg_create_linear_allocator(&allocator, allocatorBuffer.pMemory, allocatorBuffer.memorySizeInBytes);
	kg_create_texture_atlas(&atlas, &allocator, atlasWidth, atlasHeight, atlasFormat);

	kg_allocate_from_linear_allocator(&pPoints, &allocator, sizeof(kg_float2) * maxPointCount);

	//generateCurvePoints();
	generateGlyphPoints();
	resizeBackbuffer(p_HWND, screenWidth, screenHeight);
}

void swapBuffers(HWND p_HWND)
{
	HDC originalDC = GetDC(p_HWND);
	
	//blit to front buffer
	BitBlt(originalDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, SRCCOPY);

	//clear backbuffer
	BitBlt(backbufferDC, 0, 0, screenWidth, screenHeight, backbufferDC, 0, 0, BLACKNESS);
}

void drawLinePoints()
{
	const float width = 10.f;
	const float height = 10.f;

	kg_float2 v[2];
	v[0] = kg_float2_zero();
	v[1] = kg_float2_zero();
	
	int i = 0u;

	static char text[20];

	if (pointCount > 0)
	{
		for (size_t pointIndex = 0u; pointIndex < pointCount; ++pointIndex)
		{
			Rectangle(backbufferDC, 
				(int)(pPoints[pointIndex].x - width  * 0.5f),
				(int)(pPoints[pointIndex].y - height * 0.5f),
				(int)(pPoints[pointIndex].x + width  * 0.5f),
				(int)(pPoints[pointIndex].y + height * 0.5f));
		
			if (pointIndex != 0u)
			{
				if (pointIndex == 1)
				{
					v[0] = kg_float2_init(pPoints[pointIndex].x - pPoints[pointIndex - 1u].x,
										pPoints[pointIndex].y - pPoints[pointIndex - 1].y);
				}
				else 
				{
					v[1] = kg_float2_init(pPoints[pointIndex].x - pPoints[pointIndex - 1u].x,
										pPoints[pointIndex].y - pPoints[pointIndex - 1].y);
				
					v[0] = kg_float2_normalize(v[0]);
					v[1] = kg_float2_normalize(v[1]);

					const float d = kg_float2_dot(v[0], v[1]);
					sprintf(text, "d:%.3f", d);

					RECT textRect;
					textRect.left 	= (LONG)(pPoints[pointIndex - 1].x + 0.f);
					textRect.top 	= (LONG)(pPoints[pointIndex - 1].y + 0.f);
					textRect.right 	= (LONG)(pPoints[pointIndex - 1].x + 80.f);
					textRect.bottom = (LONG)(pPoints[pointIndex - 1].y + 80.f);

					DrawTextA(backbufferDC, text, -1, &textRect, DT_LEFT | DT_TOP);
				
					v[0] = v[1];
				}
			}
		}
	}
	else if (lineCount > 0)
	{
		for (size_t lineIndex = 0u; lineIndex < lineCount; ++lineIndex)
		{
			Rectangle(backbufferDC, 
				(int)(pLines[lineIndex].p0.x * scaleFactor - width  * 0.5f + offset.x),
				(int)(pLines[lineIndex].p0.y * scaleFactor - height * 0.5f + offset.y),
				(int)(pLines[lineIndex].p0.x * scaleFactor + width  * 0.5f + offset.x),
				(int)(pLines[lineIndex].p0.y * scaleFactor + height * 0.5f + offset.y));
			
			Rectangle(backbufferDC, 
				(int)(pLines[lineIndex].p1.x * scaleFactor - width  * 0.5f + offset.x),
				(int)(pLines[lineIndex].p1.y * scaleFactor - height * 0.5f + offset.y),
				(int)(pLines[lineIndex].p1.x * scaleFactor + width  * 0.5f + offset.x),
				(int)(pLines[lineIndex].p1.y * scaleFactor + height * 0.5f + offset.y));
		}
	}
}

void drawLines()
{
	if(pointCount > 0 || lineCount > 0)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		HPEN oldPen = (HPEN)SelectObject(backbufferDC, pen);

		if(pointCount > 0)
		{
			for(size_t pointIndex = 0u; pointIndex < pointCount - 1; ++pointIndex)
			{
				MoveToEx(backbufferDC, (int)pPoints[pointIndex].x, (int)pPoints[pointIndex].y, 0u);
				LineTo(backbufferDC, (int)pPoints[pointIndex + 1].x, (int)pPoints[pointIndex + 1].y);
			}
		}
		else
		{
			for(size_t lineIndex = 0u; lineIndex < lineCount; ++lineIndex)
			{
				MoveToEx(backbufferDC, (int)(pLines[lineIndex].p0.x * scaleFactor + offset.x), (int)(pLines[lineIndex].p0.y * scaleFactor + offset.y), 0u);
				LineTo(backbufferDC, (int)(pLines[lineIndex].p1.x * scaleFactor + offset.x), (int)(pLines[lineIndex].p1.y * scaleFactor + offset.y));	
			}
		}

		SelectObject(backbufferDC, oldPen);
		DeleteObject(pen);
	}
}

void drawDeltaTime(uint32 p_DeltaTimeInMS)
{
	RECT textRect;
	textRect.left = 200;
	textRect.top = 20;
	textRect.bottom = screenHeight;
	textRect.right = screenWidth;

	char messageBuffer[64];
	SetTextColor(backbufferDC, RGB(255, 255, 255));
	SetBkColor(backbufferDC, RGB(0, 0, 0));

	sprintf_s(messageBuffer, 64, "error: %.3f\ncodepoint: %d\nlinecount: %d\npointcount: %d", error, codePoint, lineCount, pointCount);
	DrawTextA(backbufferDC, messageBuffer, -1, &textRect, DT_RIGHT | DT_TOP);
}

void doFrame(uint32 p_DeltaTimeInMS, HWND p_HWND)
{
	if (s_drawLinePoints)
	{
		drawLinePoints();
	}

	drawLines();
	drawDeltaTime(p_DeltaTimeInMS);
	swapBuffers(p_HWND);
}

int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	LARGE_INTEGER performanceFrequency;
	QueryPerformanceFrequency(&performanceFrequency);

	allocateDebugConsole();

	HWND hwnd = setupWindow(hInstance, screenWidth, screenHeight);

	if (hwnd == INVALID_HANDLE_VALUE)
		return -1;

	setup(hwnd);

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

		timeFrameEnded = getTimeInMilliseconds(performanceFrequency);
		deltaMs = timeFrameEnded - timeFrameStarted;

		Sleep(100);
	}

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <malloc.h>
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

const size_t vertexMemorySize 	= kg_size_kilo_bytes(512);
const size_t indexMemorySize	= kg_size_kilo_bytes(512);
const size_t dataMemorySize 	= kg_size_mega_bytes(5);

GLuint vertexBuffer 	= 0u;
GLuint indexBuffer 		= 0u;
GLuint vertexArray 		= 0u;
GLuint shaderProgram 	= 0u;

void* pVertexMemory; 	
void* pIndexMemory;
void* pDataMemory;

kg_context_handle contextHandle;

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

void updateGUI()
{
	kg_begin_frame(contextHandle);

	if (kg_begin_window(contextHandle, "TestWindow"))
	{
		kg_end_window(contextHandle);
	}

	kg_end_frame(contextHandle);

	kg_error* pError = 0;
	while( kg_pop_error(contextHandle, &pError) )
	{
		printf("Error occured: '%s'\n", pError->pDescription );
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
	kg_keyboard_key_type buttonType = K15_GUI_KEY_NORMAL;

	switch (p_wParam)
	{
		case VK_RETURN:
			buttonType = K15_GUI_KEY_RETURN;
			break;

		case VK_BACK:
			buttonType = K15_GUI_KEY_BACK;
			break;

		case VK_TAB:
			buttonType = K15_GUI_KEY_TAB;
			break;

		case VK_DELETE:
			buttonType = K15_GUI_KEY_DEL;
			break;

		case VK_PRIOR:
			buttonType = K15_GUI_KEY_PGUP;
			break;

		case VK_NEXT:
			buttonType = K15_GUI_KEY_PGDOWN;
			break;

		case VK_HOME:
			buttonType = K15_GUI_KEY_HOME;
			break;

		case VK_END:
			buttonType = K15_GUI_KEY_END;
			break;

		case VK_INSERT:
			buttonType = K15_GUI_KEY_INS;
			break;

		case VK_ESCAPE:
			buttonType = K15_GUI_KEY_ESC;
			break;

		case VK_MENU:
			buttonType = K15_GUI_KEY_ALT;
			break;

		case VK_SHIFT:
			buttonType = K15_GUI_KEY_SHIFT;
			break;

		case VK_CONTROL:
			buttonType = K15_GUI_KEY_CTRL;
			break;

		case VK_F1:
			buttonType = K15_GUI_KEY_F1;
			break;

		case VK_F2:
			buttonType = K15_GUI_KEY_F2;
			break;
			
		case VK_F3:
			buttonType = K15_GUI_KEY_F3;
			break;
			
		case VK_F4:
			buttonType = K15_GUI_KEY_F4;
			break;
			
		case VK_F5:
			buttonType = K15_GUI_KEY_F5;
			break;
			
		case VK_F6:
			buttonType = K15_GUI_KEY_F6;
			break;
		
		case VK_F7:
			buttonType = K15_GUI_KEY_F7;
			break;
			
		case VK_F8:
			buttonType = K15_GUI_KEY_F8;
			break;
			
		case VK_F9:
			buttonType = K15_GUI_KEY_F9;
			break;
			
		case VK_F10:
			buttonType = K15_GUI_KEY_F10;
			break;
			
		case VK_F11:
			buttonType = K15_GUI_KEY_F11;
			break;
			
		case VK_F12:
			buttonType = K15_GUI_KEY_F12;
			break;
			
		case VK_LEFT:
			buttonType = K15_GUI_KEY_LEFT;
			break;

		case VK_RIGHT:
			buttonType = K15_GUI_KEY_LEFT;
			break;

		case VK_UP:
			buttonType = K15_GUI_KEY_LEFT;
			break;

		case VK_DOWN:
			buttonType = K15_GUI_KEY_LEFT;
			break;

		default:
			break;
	}

	if (p_Message == WM_KEYDOWN || p_Message == WM_SYSKEYDOWN)
	{
		kg_add_input_key_button_down(contextHandle, buttonType);
	}
	else
	{
		kg_add_input_key_button_up(contextHandle, buttonType);
	}
}

void K15_MouseButtonInput(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	uint16 x = (uint16)p_lParam;
	uint16 y = (uint16)(p_lParam >> 16u);

	kg_mouse_button_type buttonType = K15_GUI_MOUSE_BUTTON_LEFT;

	switch(p_wParam)
	{
		case VK_LBUTTON:
			buttonType = K15_GUI_MOUSE_BUTTON_LEFT;
			break;

		case VK_RBUTTON:
			buttonType = K15_GUI_MOUSE_BUTTON_RIGHT;
			break;

		case VK_MBUTTON:
			buttonType = K15_GUI_MOUSE_BUTTON_MIDDLE;
			break;

		default:
			buttonType = K15_GUI_MOUSE_BUTTON_LEFT;
			break;
	}

	if (p_Message == WM_MBUTTONDOWN || p_Message == WM_LBUTTONDOWN || p_Message == WM_RBUTTONDOWN)
	{
		kg_add_input_mouse_button_down(contextHandle, x, y, buttonType);
	}
	else if (p_Message == WM_MBUTTONUP || p_Message == WM_LBUTTONUP || p_Message == WM_RBUTTONUP)
	{
		kg_add_input_mouse_button_up(contextHandle, x, y, buttonType);
	}
}	

void K15_MouseMove(HWND p_HWND, UINT p_Message, WPARAM p_wParam, LPARAM p_lParam)
{
	uint16 x = (uint16)p_lParam;
	uint16 y = (uint16)(p_lParam >> 16u);

	kg_add_input_mouse_move(contextHandle, x, y);
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

uint8 shaderCompilationFailed(GLuint shader)
{
	GLint success = 0u;
	K15_GL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

	if (success == kg_true)
	{
		return kg_false;
	}

	GLint logSize = 0;
	K15_GL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize));

	GLint size = 0;
	char* pLog = (char*)malloc(logSize);
	K15_GL(glGetShaderInfoLog(shader, logSize, &size, pLog));

	printf("Could not compile shader:\n%s\n\n", pLog);
	free(pLog);

	return kg_true;
}

uint8 shaderLinkingFailed(GLuint program)
{
	GLint isLinked = 0;
	K15_GL(glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked));

	if (isLinked == GL_TRUE)
	{
		return kg_false;
	}

	GLint maxLength = 0;
	K15_GL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

	char* pLog = (char*)malloc(maxLength);
	K15_GL(glGetProgramInfoLog(program, maxLength, &maxLength, pLog));
	
	printf("Could not link shader:\n%s\n\n", pLog);


	free(pLog);

	return kg_true;
}

void setup(HWND p_HWND)
{
	pVertexMemory 	= malloc(vertexMemorySize);
	pIndexMemory 	= malloc(indexMemorySize);
	pDataMemory		= malloc(dataMemorySize);

	memset(pDataMemory, 0, dataMemorySize);

	char fcc[4] = {'F', 'U', 'C', 'K'};
	char* bla = (char*)pDataMemory;
	memcpy(bla + dataMemorySize - 4, fcc, 4);

	kg_context_parameter parameter = kg_create_context_parameter();
	parameter.scratchBuffer = kg_create_buffer(pDataMemory, dataMemorySize);

	kg_render_context_parameter renderParameter = kg_create_render_context_parameter();
	renderParameter.vertexBufferCount 	= 1u;
	renderParameter.indexBufferCount	= 1u;
	renderParameter.vertexBuffer[0] 	= kg_create_buffer(pVertexMemory, vertexMemorySize);
	renderParameter.indexBuffer[0] 		= kg_create_buffer(pIndexMemory, indexMemorySize);
	renderParameter.indexDataType		= K15_GUI_INDEX_DATA_TYPE_SHORT;

	K15_GL(glGenBuffers(1, &vertexBuffer));
	K15_GL(glGenBuffers(1, &indexBuffer));

	K15_GL(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	K15_GL(glBufferStorage(GL_ARRAY_BUFFER, vertexMemorySize, kg_nullptr, GL_DYNAMIC_STORAGE_BIT));
	
	K15_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
	K15_GL(glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, indexMemorySize, kg_nullptr, GL_DYNAMIC_STORAGE_BIT));

	K15_GL(glGenVertexArrays(1, &vertexArray));
	K15_GL(glBindVertexArray(vertexArray));

	K15_GL(glEnableVertexAttribArray(0));
	K15_GL(glEnableVertexAttribArray(1));
	K15_GL(glEnableVertexAttribArray(2));

	const kg_vertex_definition* pVertexDefinition = kg_get_vertex_definition();

	for (int attributeIndex = 0; attributeIndex < pVertexDefinition->attributeCount; ++attributeIndex)
	{
		const kg_vertex_attribute_definition* pAttribute = pVertexDefinition->attributes + attributeIndex;
		K15_GL(glVertexAttribPointer(attributeIndex, pAttribute->size, GL_FLOAT, GL_FALSE, pVertexDefinition->stride, (const GLvoid*)pAttribute->offset));
	}

	const char* pVertexShader = ""
	"#version 410\n"
	"layout(location=0) in vec4 positionIn;\n"
	"layout(location=1) in vec4 colorIn;\n"
	"layout(location=2) in vec2 texCoordsIn;\n"
	""
	"out vec2 texCoords;\n"
	"out vec4 color;\n"
	""
	"uniform mat4 projection;\n"
	""
	"void main()\n"
	"{\n"
	"	texCoords 	= texCoordsIn;\n"
	"	color 		= colorIn;\n"
	"	gl_Position = positionIn * projection;\n"
	"}\n";

	const char* pFragmentShader = ""
	"#version 410\n"
	"in vec2 texCoords;\n"
	"in vec4 color;\n"
	""
	"void main()\n"
	"{\n"
	"	gl_FragColor = color;\n"
	"}\n";

	const int vertexShaderLength = strlen(pVertexShader);
	const int fragmentShaderLength = strlen(pFragmentShader);

	shaderProgram = kglCreateProgram();

	GLuint vertexShader 	= kglCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader	= kglCreateShader(GL_FRAGMENT_SHADER);

	K15_GL(glShaderSource(vertexShader, 1, &pVertexShader, &vertexShaderLength));
	K15_GL(glShaderSource(fragmentShader, 1, &pFragmentShader, &fragmentShaderLength));

	K15_GL(glCompileShader(vertexShader));
	K15_GL(glCompileShader(fragmentShader));

	if (shaderCompilationFailed(vertexShader))
	{
		return;
	}

	if (shaderCompilationFailed(fragmentShader))
	{
		return;
	}

	K15_GL(glAttachShader(shaderProgram, vertexShader));
	K15_GL(glAttachShader(shaderProgram, fragmentShader));

	K15_GL(glLinkProgram(shaderProgram));

	if (shaderLinkingFailed(shaderProgram))
	{
		return;
	}

	K15_GL(glDetachShader(shaderProgram, vertexShader));
	K15_GL(glDetachShader(shaderProgram, fragmentShader));

	K15_GL(glUseProgram(shaderProgram));

	const char* pError = NULL;
	kg_result result = kg_create_context_with_custom_parameter(&contextHandle, &parameter, &renderParameter, &pError);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		printf("could not create gui context. error = %s\n", kg_result_to_string(result));
	}
}

void swapBuffers(HWND p_HWND)
{
	HDC deviceContext = GetDC(p_HWND);
	SwapBuffers(deviceContext);
	kglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawGUI()
{
	kg_render_data renderData;
	kg_result result = kg_get_render_data(contextHandle, &renderData);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return;	
	}

	float mat[16];
	kg_calculate_row_major_projection_matrix(mat, screenWidth, screenHeight, K15_GUI_MATRIX_INVERT_Y_AXIS_FLAG);

	GLint projectionLocation = kglGetUniformLocation(shaderProgram, "projection");
	K15_GL(glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, mat));

	K15_GL(glBufferSubData(GL_ARRAY_BUFFER, 0, renderData.vertexDataSizeInBytes, renderData.pVertexData));
	K15_GL(glDrawArrays(GL_TRIANGLES, 0, renderData.vertexCount));
}

void drawDeltaTime(uint32 p_DeltaTimeInMS)
{

}

void doFrame(uint32 p_DeltaTimeInMS, HWND p_HWND)
{
	drawDeltaTime(p_DeltaTimeInMS);
	updateGUI();
	drawGUI();
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
#define _GNU_SOURCE 1

#include "stdio.h"
#include "time.h"
#include "string.h"
#include "unistd.h"
#include "X11/Xlib.h"
#include "GL/gl.h"
#include "GL/glx.h"

#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"

#define K15_OPENGL_CALL(x) {x; {GLenum glerr = glGetError(); while(glerr != 0){ printf("GLError during call of '%s' : '%d'\n", #x, glerr); glerr = glGetError();}}}

#define K15_FALSE 0
#define K15_TRUE 1

#define	GLX_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB           0x2092
#define GLX_CONTEXT_FLAGS_ARB                   0x2094
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB        0x00000001

typedef unsigned char bool8;
typedef unsigned char byte;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

Display* mainDisplay = 0;
GC mainGC;
int mainScreen = 0;
Atom deleteMessage = 0;
int nanoSecondsPerFrame = 16000000;

K15_GUIContext guiContext = {0};

uint32 screenWidth = 1024;
uint32 screenHeight = 768;

GLint vbo = 0;
GLint ibo = 0;
GLint vao = 0;
GLint shaderProgram = 0;
GLint projUniform = 0;
GLint textureUniform = 0;
K15_GUIContext guiContext;

GLuint iconTextureHandle;
GLuint fontTextureHandle;

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

void resizeWindow(int p_Width, int p_Height)
{
	screenWidth = p_Width;
	screenHeight = p_Height;

	K15_GUISystemEvent systemEvent;
	systemEvent.type = K15_GUI_WINDOW_RESIZED;
	systemEvent.params.size.height = p_Height;
	systemEvent.params.size.width = p_Width;

	float projMatrix[16];
	K15_GUICalculateColumnMajorProjectionMatrix(projMatrix, 
		p_Width, p_Height, K15_GUI_INVERT_Y_AXIS);

	K15_OPENGL_CALL(glUniformMatrix4fv(projUniform, 1, GL_FALSE, projMatrix));
	K15_OPENGL_CALL(glViewport(0, 0, p_Width, p_Height));

	K15_GUIAddSystemEvent(&guiContext.events, systemEvent);
}

void handleKeyPress(XEvent* p_Event)
{
}

void handleKeyRelease(XEvent* p_Event)
{
	K15_GUIMouseInput mouseInput = { 0 };
	mouseInput.data.mouseButton = K15_GUI_MOUSE_BUTTON_LEFT;
	mouseInput.type = K15_GUI_MOUSE_BUTTON_RELEASED;

	K15_GUIAddMouseInput(&guiContext.events, mouseInput);
}

void handleButtonPress(XEvent* p_Event)
{
	K15_GUIMouseInput mouseInput = { 0 };
	mouseInput.data.mouseButton = K15_GUI_MOUSE_BUTTON_LEFT;
	mouseInput.type = K15_GUI_MOUSE_BUTTON_PRESSED;

	K15_GUIAddMouseInput(&guiContext.events, mouseInput);
}

void handleButtonRelease(XEvent* p_Event)
{
}

void handleMouseMotion(XEvent* p_Event)
{
	int posX = p_Event->xmotion.x;
	int posY = p_Event->xmotion.y;
	K15_GUIMouseInput mouseInput = { 0 };
	mouseInput.data.mousePos.x = posX;
	mouseInput.data.mousePos.y = posY;
	mouseInput.type = K15_GUI_MOUSE_MOVED;

	K15_GUIAddMouseInput(&guiContext.events, mouseInput);
}

void handleWindowResize(XEvent* p_Event)
{
	int width = p_Event->xconfigure.width;
	int height = p_Event->xconfigure.height;

	resizeWindow(width, height);
}

bool8 filterEvent(XEvent* p_Event)
{
	if (p_Event->type == KeyRelease)
	{
		if (XEventsQueued(mainDisplay, QueuedAfterReading))
		{
			XEvent tempEvent;
			XPeekEvent(mainDisplay, &tempEvent);

			if (tempEvent.type == KeyPress && tempEvent.xkey.time == p_Event->xkey.time &&
				tempEvent.xkey.keycode == p_Event->xkey.keycode)
			{
				XNextEvent(mainDisplay, &tempEvent);
				return K15_TRUE;
			}
		}
	}


	return K15_FALSE;
}

#define RGB(r, g, b) (r | (g << 8) | (b << 16))

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

	K15_OPENGL_CALL(glGenTextures(1, &iconTextureHandle));
	K15_OPENGL_CALL(glGenTextures(1, &fontTextureHandle));

	K15_OPENGL_CALL(glBindTexture(GL_TEXTURE_2D, iconTextureHandle));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
	K15_OPENGL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, iconTextureWidth, iconTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, iconPixelBuffer));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	
	K15_OPENGL_CALL(glBindTexture(GL_TEXTURE_2D, fontTextureHandle));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
	K15_OPENGL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, fontTextureWidth, fontTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, fontPixelBuffer));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	K15_OPENGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

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

	if (K15_GUIBeginMenu(p_GUIContext, "Edit", "edit"))
	{
		if (K15_GUIMenuItem(p_GUIContext, "Whales", "open_2"))
		{
			printf("Open pressed...\n");
		}

		K15_GUIEndMenu(p_GUIContext);
	}

	if (K15_GUIBeginMenu(p_GUIContext, "View", "view"))
	{
		if (K15_GUIMenuItem(p_GUIContext, "Cambridge", "open_3"))
		{
			printf("Open pressed...\n");
		}

		K15_GUIEndMenu(p_GUIContext);
	}

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
		K15_OPENGL_CALL(glBufferData(GL_ARRAY_BUFFER, drawInformation->vertexBufferDataSizeInBytes, drawInformation->vertexBufferData, GL_DYNAMIC_DRAW));
		K15_OPENGL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawInformation->indexBufferDataSizeInBytes, drawInformation->indexBufferData, GL_DYNAMIC_DRAW));

		uint32 drawCommandIndex = 0;
		for (drawCommandIndex = 0;
			drawCommandIndex < drawInformation->numDrawCommands;
			++drawCommandIndex)
		{
			K15_GUIDrawCommand* drawCommand = drawInformation->drawCommands + drawCommandIndex;
			kg_u64 textureUserData = drawCommand->textureUserData;
			kg_u32 numTriangles = drawCommand->numTriangles;
			kg_u32 vertexOffset = drawCommand->vertexOffset;
			kg_u32 indexOffset = drawCommand->indexOffset;

			K15_OPENGL_CALL(glBindTexture(GL_TEXTURE_2D, (GLuint)textureUserData));
			K15_OPENGL_CALL(glDrawElements(GL_TRIANGLES, numTriangles * 3, indexSizeInBytes == 4 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT, (const void*)(indexOffset * indexSizeInBytes)));
		}
	}
}

void handleEvent(XEvent* p_Event)
{
	if (filterEvent(p_Event))
		return;

	if (p_Event->type == KeyPress)
		handleKeyPress(p_Event);
	else if (p_Event->type == KeyRelease)
		handleKeyRelease(p_Event);
	else if (p_Event->type == ButtonPress)
		handleButtonPress(p_Event);
	else if (p_Event->type == ButtonRelease)
		handleButtonRelease(p_Event);
	else if (p_Event->type == MotionNotify)
		handleMouseMotion(p_Event);
	else if (p_Event->type == ConfigureNotify)
		handleWindowResize(p_Event);
}

char* getInfoLogForShader(GLuint p_Shader)
{
	GLint infoLogLength = 0;
	K15_OPENGL_CALL(glGetShaderiv(p_Shader, GL_INFO_LOG_LENGTH, &infoLogLength));
	char* infoLog = 0;

	if (infoLogLength > 0)
	{
		infoLog = (char*)malloc(infoLogLength);
		glGetShaderInfoLog(p_Shader, infoLogLength, 0, infoLog);
	}
	return infoLog;
}

int errorHandler(Display* p_Display, XErrorEvent* p_Event)
{
	uint32 errorCode = p_Event->error_code;
	char errorMessage[256];
	XGetErrorText(p_Display, errorCode, errorMessage, 256);

	printf("Error (%d): '%s'", errorCode, errorMessage);

	return 0;
}

void setupGL()
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

	K15_OPENGL_CALL(glGenBuffers(1, &vbo));
	K15_OPENGL_CALL(glGenBuffers(1, &ibo));
	K15_OPENGL_CALL(glGenVertexArrays(1, &vao));

	K15_OPENGL_CALL(glFrontFace(GL_CW));
	K15_OPENGL_CALL(glCullFace(GL_FRONT));

	K15_OPENGL_CALL(glBindVertexArray(vao));
	K15_OPENGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	K15_OPENGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

	kg_u32 sizeVertexStrideInBytes = K15_GUI_VERTEX_SIZE_IN_BYTES;

	K15_OPENGL_CALL(shaderProgram = glCreateProgram());

	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;

	K15_OPENGL_CALL(vertexShader = glCreateShader(GL_VERTEX_SHADER));
	K15_OPENGL_CALL(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

	K15_OPENGL_CALL(glShaderSource(vertexShader, 1, &vertexShaderSource, &vertexShaderSourceLength));
	K15_OPENGL_CALL(glShaderSource(fragmentShader, 1, &fragmentShaderSource, &fragmentShaderSourceLenght));

	K15_OPENGL_CALL(glCompileShader(vertexShader));
	K15_OPENGL_CALL(glCompileShader(fragmentShader));

	GLint vertexShaderCompileStatus = 0;
	GLint fragmentShaderCompileStatus = 0;
	K15_OPENGL_CALL(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus));
	K15_OPENGL_CALL(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus));

	if (vertexShaderCompileStatus == GL_FALSE)
	{
		const char* error = getInfoLogForShader(vertexShader);
		printf("Vertex Shader Error: '%s'\n", error);
	}

	if (fragmentShaderCompileStatus == GL_FALSE)
	{
		const char* error = getInfoLogForShader(fragmentShader);
		printf("Fragment Shader Error: '%s'\n", error);
	}

	K15_OPENGL_CALL(glAttachShader(shaderProgram, vertexShader));
	K15_OPENGL_CALL(glAttachShader(shaderProgram, fragmentShader));
	K15_OPENGL_CALL(glLinkProgram(shaderProgram));

	GLint linkStatus = 0;
	K15_OPENGL_CALL(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus));

	if (linkStatus == GL_FALSE)
	{
		GLint programLogLength = 0;
		K15_OPENGL_CALL(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &programLogLength));

		if (programLogLength > 0)
		{
			char* programLog = (char*)malloc(programLogLength);
			K15_OPENGL_CALL(glGetProgramInfoLog(shaderProgram, programLogLength, 0, programLog));
			printf("Shader Linker Error: '%s'\n", programLog);
			free(programLog);
		}
	}

	GLint posAttribLocation = 0;
	GLint uvAttribLocation = 0;
	GLint colorAttribLocation = 0;

	//get register location using attribute name
	K15_OPENGL_CALL(posAttribLocation = glGetAttribLocation(shaderProgram, "position"));
 	K15_OPENGL_CALL(uvAttribLocation = glGetAttribLocation(shaderProgram, "uv"));
 	K15_OPENGL_CALL(colorAttribLocation = glGetAttribLocation(shaderProgram, "color"));

	int attribArrayIndex = 0;

	if (posAttribLocation >= 0)
	{
		K15_OPENGL_CALL(glEnableVertexAttribArray(attribArrayIndex++));
		K15_OPENGL_CALL(glVertexAttribPointer(posAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeVertexStrideInBytes, 0));
	}

	if (uvAttribLocation >= 0)
	{
		K15_OPENGL_CALL(glEnableVertexAttribArray(attribArrayIndex++));
		K15_OPENGL_CALL(glVertexAttribPointer(uvAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeVertexStrideInBytes, (const void*)(sizeof(float) * 2)));
	}

	if (colorAttribLocation >= 0)
	{
		K15_OPENGL_CALL(glEnableVertexAttribArray(attribArrayIndex));
		K15_OPENGL_CALL(glVertexAttribPointer(colorAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeVertexStrideInBytes, (const void*)(sizeof(float) * 4)));
	}

	K15_OPENGL_CALL(projUniform = glGetUniformLocation(shaderProgram, "projMatrix"));
	K15_OPENGL_CALL(textureUniform = glGetUniformLocation(shaderProgram, "textureSampler"));

	K15_OPENGL_CALL(glUseProgram(shaderProgram));

	K15_OPENGL_CALL(glUniform1i(textureUniform, 0));
	K15_OPENGL_CALL(glActiveTexture(GL_TEXTURE0));
	
}

void setupWindow(Window* p_WindowOut, int p_Width, int p_Height)
{
	int borderWidth = 1;
	int eventMask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | 
		KeyPressMask | KeyReleaseMask | StructureNotifyMask;

	static int visualAttributes[] = {
			GLX_X_RENDERABLE, True,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
			GLX_RED_SIZE, 8,
			GLX_GREEN_SIZE, 8,
			GLX_BLUE_SIZE, 8,
			GLX_ALPHA_SIZE, 8,
			GLX_DEPTH_SIZE, 24,
			GLX_STENCIL_SIZE, 8,
			GLX_DOUBLEBUFFER, True,
			None
	};

	int fbCount = 0;
	GLXFBConfig* fbc = glXChooseFBConfig(mainDisplay, XDefaultScreen(mainDisplay), visualAttributes, &fbCount);

	if (!fbc)
	{
		printf("Failed to retrieve framebuffer config through glXChooseFBConfig.\n");
	}

	GLXFBConfig frameBufferConfig = fbc[0];
	XFree(fbc);

	XVisualInfo* vi = glXGetVisualFromFBConfig(mainDisplay, frameBufferConfig);

	XSetWindowAttributes setWindowAttributes = {0};
	setWindowAttributes.colormap = XCreateColormap(mainDisplay, XRootWindow(mainDisplay, vi->screen), vi->visual, AllocNone);
	setWindowAttributes.background_pixmap = None;
	setWindowAttributes.border_pixel = 0;
	setWindowAttributes.event_mask = StructureNotifyMask;

	Window window = XCreateSimpleWindow(mainDisplay, XRootWindow(mainDisplay, vi->screen),
		0, 0, p_Width, p_Height, 0, 0, 0);

	XFree(vi);

	*p_WindowOut = window;

	mainGC = XCreateGC(mainDisplay, window, 0, 0);
	XSetForeground(mainDisplay, mainGC, (~0));
	XStoreName(mainDisplay, window, "Test Window!");
	XSelectInput(mainDisplay, window, eventMask);
	XSetWMProtocols(mainDisplay, window, &deleteMessage, 1);

	glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
	glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB("glXCreateContextAttribsARB");

	GLXContext ctx = 0;

	int contextAttributes[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 3,
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		None
	};

	ctx = glXCreateContextAttribsARB(mainDisplay, frameBufferConfig, 0, True, contextAttributes);
	XSync(mainDisplay, False);

	glXMakeCurrent(mainDisplay, window, ctx);
	glViewport(0, 0, p_Width, p_Height);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	printf("OpenGL intialized!\nGL_VERSION: '%s'\nGL_RENDERER: '%s'\nGL_VENDOR: '%s'.\n", 
		glGetString(GL_VERSION), glGetString(GL_RENDERER), glGetString(GL_VENDOR));

	XMapWindow(mainDisplay, window);
}

bool8 setup(Window* p_WindowOut)
{
	XSetErrorHandler(errorHandler);
	mainDisplay = XOpenDisplay(0);

	if (mainDisplay)
	{
		mainScreen = XDefaultScreen(mainDisplay);
		deleteMessage = XInternAtom(mainDisplay, "WM_DELETE_WINDOW", False);
		setupWindow(p_WindowOut, 800, 600);
		setupGL();
		return K15_TRUE;
	}

	return K15_FALSE;
}

void drawDeltaTime(Window* p_MainWindow, long p_DeltaTimeInNs)
{
	char buffer[256];
	sprintf(buffer, "Milliseconds:%ld", p_DeltaTimeInNs / 1000000);

	XDrawString(mainDisplay, *p_MainWindow, mainGC, 20, screenHeight - 20, buffer, strlen(buffer));
}

void doFrame(Window* p_MainWindow, K15_GUIContext* p_GUIContext, long p_DeltaTimeInNs)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawDeltaTime(p_MainWindow, p_DeltaTimeInNs);
	updateGUI(p_GUIContext);
	drawGUI(p_GUIContext);
	glXSwapBuffers(mainDisplay, *p_MainWindow);

	XFlush(mainDisplay);
	XSync(mainDisplay, *p_MainWindow);
}

int main(int argc, char** argv)
{
	Window mainWindow;
	if (!setup(&mainWindow))
	{
		printf("Could not initialize window!\n");
		return -1;
	}

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

	struct timespec timeFrameStarted = {0};
	struct timespec timeFrameEnded = {0};
	long deltaNs = 0;

	bool8 loopRunning = K15_TRUE;
	XEvent event = {0};
	while (loopRunning)
	{
		clock_gettime(CLOCK_MONOTONIC, &timeFrameStarted);
		while (XPending(mainDisplay))
		{
			XNextEvent(mainDisplay, &event);

			if (event.type == ClientMessage && 
				event.xclient.data.l[0] == deleteMessage)
			{
				loopRunning = K15_FALSE;
			} 

			handleEvent(&event);
		}

		doFrame(&mainWindow, &guiContext, deltaNs);

		clock_gettime(CLOCK_MONOTONIC, &timeFrameEnded);

		deltaNs = timeFrameEnded.tv_nsec - timeFrameStarted.tv_nsec;

		if (deltaNs < nanoSecondsPerFrame)
		{
			struct timespec sleepTime = {0, nanoSecondsPerFrame - deltaNs};
			nanosleep(&sleepTime, 0);
		}
	}

	return 0;
}
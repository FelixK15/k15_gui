#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"

void setupResources(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "accept.png", "load");
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "add.png", "load2");
	K15_GUICreateIconResourceFromFile(p_GUIResourceDatabase, "anchor.png", "load3");

	K15_GUIIconSet* icons = 0;
	K15_GUIBakeIconResources(p_GUIResourceDatabase, &icons, "default_iconset");
	
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
	kg_u32 sizeDrawCommandBuffer = K15_GUICalculateDrawCommandBufferSizeInBytes(p_GUIContext);
	K15_GUIDrawCommandBuffer* drawCommandBuffer = (K15_GUIDrawCommandBuffer*)malloc(sizeDrawCommandBuffer);

	K15_GUICopyDrawCommandBuffer(p_GUIContext, drawCommandBuffer);

	while (K15_GUIHasDrawCommand(drawCommandBuffer))
	{
		K15_GUIDrawCommandType type = K15_GUIGetDrawCommandType(drawCommandBuffer);

		switch (type)
		{
		case K15_GUI_DRAW_RECT_COMMAND:
			K15_GUIRectShapeData rectShapeData = { 0 };
			K15_GUIGetDrawCommandData(drawCommandBuffer, &rectShapeData, sizeof(rectShapeData));
			drawRect(&rectShapeData);
			break;

		default:
			break;
		}

		K15_GUINextDrawCommand(drawCommandBuffer);
	}
}

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main(int argc, char** argv)
{
	K15_GUIResourceDatabase guiResourceDatabase = {0};
	kg_result result = K15_GUICreateResourceDatabase(&guiResourceDatabase);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		char* errorMsg = (char*)alloca(256);
		K15_GUIConvertResultToMessage(result, &errorMsg, 256);

		printf("Error during resource database creation: '%s'\n", errorMsg);
	}

	K15_GUIContext guiContext = {0};
	result = K15_CreateGUIContext(&guiContext, &guiResourceDatabase, 0, 0, 800, 600);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		char* errorMsg = (char*)alloca(256);
		K15_GUIConvertResultToMessage(result, &errorMsg, 256);

		printf("Error during context creation: '%s'\n", errorMsg);
	}

	setupResources(&guiResourceDatabase);

	for (;;)
	{
		updateGUI(&guiContext);
		drawGUI(&guiContext);
		Sleep(20);
	}
	
	return 0;
}
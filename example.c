#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"

void setupResources(K15_GUIResourceContext* p_GUIResourceContext)
{
	K15_GUIFont* arial12 = K15_GUICreateFontResource(p_GUIResourceContext, "arial.ttf", 12, "default");
	K15_GUIIcon* load = K15_GUICreateIconResource(p_GUIResourceContext, "load.png", "load");
	K15_GUIIconSet* icons = K15_GUIBakeIconResources(p_GUIResourceContext);

	kg_u32 fontTextureDataSizeInBytes = K15_GUIGetFontTextureDataSizeInBytes(arial12);
	kg_byte* fontTextureData = (kg_byte*)malloc(fontTextureDataSizeInBytes);

	K15_GUIGetFontTextureData(arial12, &fontTextureData, fontTextureDataSizeInBytes);
	arial12->texture.userData = 1;

	kg_u32 iconTextureDataSizeInBytes = K15_GUIGetIconSetTextureSizeInBytes(icons);
	kg_byte* iconsTextureData = (kg_byte*)malloc(iconTextureDataSizeInBytes);

	K15_GUIGetIconSetTextureData(icons, &iconsTextureData, iconTextureDataSizeInBytes);
	icons->texture.userData = 2;
}

void updateGUI(K15_GUIContext* p_GUIContext)
{
	static kg_b8 showWindow = 0;
	static kg_s16 windowPosX = 0;
	static kg_s16 windowPosY = 0;
	static kg_u16 windowWidth = 200;
	static kg_u16 windowHeight = 100;
	static float sliderValue = 0.f;

	for (;;)
	{
		K15_GUIBeginToolBar(&guiContext, "toolbar_1");

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

		K15_GUIEndToolBar(&guiContext);

		if (showWindow)
		{
			if (K15_GUIBeginWindow(p_GUIContext, &windowPosY, &windowPosY, &windowHeight, &windowHeight, "Test Window", "test_window_1"))
			{
				K15_GUILabel(p_GUIContext, "Print float:", "label_1");
				K15_GUINextLine(p_GUIContext);
				K15_GUIFloatSlider(p_GUIContext, &sliderValue, 0.f, 10.f, "slider_1");
				if (K15_GUIButton(p_GUIContext, "Print float", "print_1"))
				{
					printf("Float: %.3f\n", sliderValue);
				}
				K15_GUIEndWindow(p_GUIContext);
			}
		}

		K15_GUIFinishFrame(p_GUIContext);
	}
}

void drawGUI(K15_GUIContext* p_GUIContext)
{
	K15_GUIDrawCommandBuffer guiDrawCommandBuffer = {};

	kg_result result = K15_GUICreateDrawCommandBuffer(p_GUIContext, &guiDrawCommandBuffer);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		char errorMsg[256];
		K15_GUIConvertResultToMessage(result, errorMsg, 256);

		printf("Error during command buffer creation: '%s'\n", errorMsg);
	}

	K15_GUIDrawCommand drawCmd = {};

	for (kg_u32 cmdIndex = 0;
		cmdIndex < guiDrawCommandBuffer.numCommands;
		++cmdIndex)
	{
		kg_result result = K15_GUIGetNextDrawCommand(&guiDrawCommandBuffer, &drawCmd);

		if (result == K15_GUI_RESULT_NO_MORE_DRAW_COMMANDS)
		{
			break;
		}

		if (drawCmd.type == K15_GUI_DRAW_VERTICES_COMMAND)
		{
			K15_GUIDrawVerticesCommand cmd = {};
			kg_result result = K15_GUIGetDrawVerticesCommand(&guiDrawCommandBuffer, &drawCmd, &cmd);

			if (result != K15_GUI_RESULT_SUCCESS)
			{
				char errorMsg[256];
				K15_GUIConvertResultToString(result, errorMsg, 256);
				printf("Error during 'DrawVerticesCommand' retrieval: '%s'\n", errorMsg);
				break;
			}

			
		}

		kg_u32 triCount = drawCmd->numTriangles;
		kg_u32 indexCount = primCount * 3;

		float* vertexData = drawCmd->vertexData;

		//upload to vertex buffer

		if ((drawCmd->attributeFlags & K15_GUI_UV_ATTRIBUTE_FLAG) > 0)
		{
			kg_u64 textureUserData = drawCmd->textureUserData;

		}

		if ((drawCmd->attributeFlags & K15_GUI_COLOR_ATTRIBUTE_FLAG) > 0)
		{

		}
	}
}

int main(int argc, char** argv)
{
	K15_GUIContext guiContext = {};
	kg_result result = K15_CreateGUIContext(&guiContext);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		char errorMsg[256];
		K15_GUIConvertResultToMessage(result, errorMsg, 256);

		printf("Error during context creation: '%s'\n", errorMsg);
	}

	setup(&guiContext);
	updateGUI(&guiContext);
	drawGUI(&guiContext);
	
	return 0;
}

#include "k15_gui.h"

void setup()
{
	K15_GUIFont* arial12 = K15_GUIGetFont(&guiContext, "arial.ttf", 12);
	kg_u32 fontTextureDataSizeInBytes = K15_GUIGetFontTextureDataSizeInBytes(arial12);
	kg_byte* fontTextureData = (kg_byte*)malloc(fontTextureDataSizeInBytes);

	K15_GUIGetFontTextureData(arial12, &fontTextureData, fontTextureDataSizeInBytes);
	arial12->texture.userData = 1;
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

		if (K15_GUIBeginMenu(p_GUIContext, "&File", "file_1"))
		{
			if (K15_GUIMenuItem(p_GUIContext, "&Open...", "open_1"))
			{
				printf("Open pressed...\n");
			}

			if (K15_GUIMenuItem(p_GUIContext, "&Close", "close_1"))
			{
				exit(0);
			}

			K15_GUISeparator(p_GUIContext);

			if (K15_GUIBeginMenu(p_GUIContext, "Even &More", "more_1"))
			{
				if (K15_GUIMenuItem(p_GUIContext, "Open &Window", "open_window_1"))
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
		
		K15_GUIDrawCommandBuffer guiDrawCommandBuffer = {};
		
		kg_result result = K15_GUICreateDrawCommandBuffer(p_GUIContext &guiDrawCommandBuffer);

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			char errorMsg[256];
			K15_GUIConvertResultToMessage(result, errorMsg, 256);

			printf("Error during command buffer creation: '%s'\n", errorMsg);
		}

		for (kg_u32 cmdIndex = 0;
			cmdIndex < guiDrawCommandBuffer.numCommands;
			++cmdIndex)
		{
			K15_GUIDrawCommand* drawCmd = guiDrawCommandBuffer.drawCommands + cmdIndex;
			
			if ((drawCmd->attributeFlags & K15_GUI_TEXTURE_USERDATA_ATTRIBUTE_FLAG) > 0)
			{
				kg_u64 textureUserData = drawCmd->textureUserData;
				//bindTexture(textureUserData);
			}
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

	return 0;
}
#ifndef _K15_GUILayer_Context_h_
#define _K15_GUILayer_Context_h_

#ifndef K15_GUI_MALLOC
	#define K15_GUI_MALLOC(bytes) malloc(bytes)
#endif //K15_GUI_MALLOC

#ifndef K15_GUI_FREE
	#define K15_GUI_FREE(ptr) free(ptr)
#endif //K15_GUI_FREE

#ifndef K15_GUI_STRLEN
	#define K15_GUI_STRLEN(str) kg_strlen(str)
#endif //K15_GUI_STRLEN

#define K15_GUI_COLOR_RGBA(r,g,b,a) ((a << 24) | (b << 16) | (g << 8) | (r << 0))
#define K15_GUI_COLOR_RGB(r,g,b) K15_GUI_COLOR_RGBA(r,g,b,255)
#define K15_GUI_COLOR_BLACK K15_GUI_COLOR_RGB(0, 0, 0)
#define K15_GUI_COLOR_WHITE K15_GUI_COLOR_RGB(255, 255, 255)

#define K15_GUI_MAX_LAYOUTS 20
#define K15_GUI_MAX_ELEMENT_PTR_PER_LAYOUT 128
#define K15_GUI_MEMORY_BUFFER_COUNT 2
#define K15_GUI_MEMORY_FRONT_BUFFER 0
#define K15_GUI_MEMORY_BACK_BUFFER 1

#define K15_GUI_MAX_BUFFERED_MOUSE_INPUTS 16
#define K15_GUI_MAX_BUFFERED_KEYBOARD_INPUTS 16
#define K15_GUI_MAX_BUFFERED_SYSTEM_EVENTS 16

#define K15_GUI_RESULT_SUCCESS 0
#define K15_GUI_RESULT_OUT_OF_MEMORY 1
#define K15_GUI_RESULT_NOT_ENOUGH_MEMORY 2
#define K15_GUI_RESULT_FONT_DATA_ERROR 3
#define K15_GUI_RESULT_NOT_SUPPORTED 4
#define K15_GUI_RESULT_FILE_NOT_FOUND 5

#define kg_size_kilo_bytes(n) (n*1024)

#define K15_GUI_MIN_MEMORY_SIZE_IN_BYTES sizeof(K15_GUIContext) + kg_size_kilo_bytes(10)

typedef unsigned long long kg_u64;
typedef unsigned int kg_u32;
typedef unsigned short kg_u16;
typedef unsigned char kg_u8;

typedef unsigned int kg_color32;

typedef long long kg_s64;
typedef int kg_s32;
typedef short kg_s16;
typedef char kg_s8;

typedef unsigned char kg_byte;
typedef unsigned char kg_b8;
typedef unsigned int kg_result;

struct K15_GUIContext;

/*********************************************************************************/
enum _K15_GUIContextInitFlags
{
	K15_GUI_SHAPE_BASED_DRAW_COMMANDS = 0x001,
	K15_GUI_VERTEX_BASED_DRAW_COMMANDS = 0x002,

	K15_GUI_DEFAULT_INIT_FLAGS = K15_GUI_VERTEX_BASED_DRAW_COMMANDS
} K15_GUIContextInitFlags;
/*********************************************************************************/
typedef enum _K15_GUIDrawCommandCreationFlags
{
	K15_GUI_CONVERT_TO_NDC = 0x01
} K15_GUIDrawCommandCreationFlags;
/*********************************************************************************/
typedef enum _K15_GUIMouseInputType
{
	K15_GUI_MOUSE_BUTTON_PRESSED = 0,
	K15_GUI_MOUSE_BUTTON_RELEASED,
	K15_GUI_MOUSE_WHEEL_UP,
	K15_GUI_MOUSE_WHEEL_DOWN,
	K15_GUI_MOUSE_MOVED
} K15_GUIMouseInputType;
/*********************************************************************************/
typedef enum _K15_GUIMouseButtonType
{
	K15_GUI_MOUSE_BUTTON_LEFT = 0,
	K15_GUI_MOUSE_BUTTON_RIGHT,
	K15_GUI_MOUSE_BUTTON_MIDDLE,
	K15_GUI_MOUSE_BUTTON_SPECIAL1,
	K15_GUI_MOUSE_BUTTON_SPECIAL2
} K15_GUIMouseButtonType;
/*********************************************************************************/
typedef enum _K15_GUIKeyboardModifierType
{
	K15_GUI_CTRL_MODIFIER = 0x01,
	K15_GUI_L_ALT_MODIFIER = 0x02,
	K15_GIU_R_ALT_MODIFIER = 0x04,
	K15_GUI_SHIFT_MODIFIER = 0x08
} K15_GUIKeyboardModifierType;
/*********************************************************************************/
typedef enum _K15_GUIKeyboardInputType
{
	K15_GUI_KEY_PRESSED = 0,
	K15_GUI_KEY_RELEASED,
	K15_GUI_TEXT_INPUT
} K15_GUIKeyboardInputType;
/*********************************************************************************/
typedef enum _K15_GUIKeyboardKeyType
{
	K15_GUI_KEY_RETURN = 0,
	K15_GUI_KEY_BACK,
	K15_GUI_KEY_TAB,
	K15_GUI_KEY_DEL,
	K15_GUI_KEY_PGDWN,
	K15_GUI_KEY_PGUP,
	K15_GUI_KEY_HOME,
	K15_GUI_KEY_END,
	K15_GUI_KEY_INS,
	K15_GUI_KEY_ESC,

	K15_GUI_KEY_F1,
	K15_GUI_KEY_F2,
	K15_GUI_KEY_F3,
	K15_GUI_KEY_F4,
	K15_GUI_KEY_F5,
	K15_GUI_KEY_F6,
	K15_GUI_KEY_F7,
	K15_GUI_KEY_F8,
	K15_GUI_KEY_F9,
	K15_GUI_KEY_F10,
	K15_GUI_KEY_F11,
	K15_GUI_KEY_F12,

	K15_GUI_KEY_LEFT,
	K15_GUI_KEY_RIGHT,
	K15_GUI_KEY_UP,
	K15_GUI_KEY_DOWN,

	//all other keys.
	K15_GUI_KEY_NORMAL
} K15_GUIKeyboardKeyType;
/*********************************************************************************/
typedef enum _K15_GUISystemEventType
{
	K15_GUI_WINDOW_RESIZED = 0,
	K15_GUI_SYSTEM_EVENT_COUNT
} K15_GUISystemEventType;
/*********************************************************************************/
typedef struct _K15_GUIMouseInput
{
	union
	{
		struct
		{
			kg_u16 mousePosX;
			kg_u16 mousePosY;
		};

		kg_u32 mouseButton;
	};

	K15_GUIMouseInputType type;
} K15_GUIMouseInput;
/*********************************************************************************/
typedef struct _K15_GUIKeyboardInput
{
	struct
	{
		kg_u16 key;
		kg_u16 modifierMask;
	} keyInput;

	K15_GUIKeyboardInputType type;
	K15_GUIKeyboardKeyType keyType;
	K15_GUIKeyboardModifierType modifier;
} K15_GUIKeyboardInput;
/*********************************************************************************/
typedef struct _K15_GUISystemEvent
{
	K15_GUISystemEventType type;

	union
	{
		struct
		{
			kg_u16 width;
			kg_u16 height;
		} size;
	} params;
} K15_GUISystemEvent;
/*********************************************************************************/
typedef struct _K15_GUIContextEvents
{
	K15_GUISystemEvent bufferedSystemEvents[K15_GUI_MAX_BUFFERED_SYSTEM_EVENTS];
	K15_GUIMouseInput bufferedMouseInput[K15_GUI_MAX_BUFFERED_MOUSE_INPUTS];
	K15_GUIKeyboardInput bufferedKeyboardInput[K15_GUI_MAX_BUFFERED_KEYBOARD_INPUTS];
	kg_u16 mousePosX;
	kg_u16 mousePosY;
	kg_s16 mouseDeltaX;
	kg_s16 mouseDeltaY;
	kg_u16 numBufferedSystemEvents;
	kg_u16 numBufferedMouseInputs;
	kg_u16 numBufferedKeyboardInputs;
} K15_GUIContextEvents;
/*********************************************************************************/
typedef struct _K15_GUIRectangle
{
	kg_s16 pixelPosLeft;
	kg_s16 pixelPosTop;
	kg_s16 pixelPosRight;
	kg_s16 pixelPosBottom;
} K15_GUIRectangle;
/*********************************************************************************/
typedef struct _K15_GUITexture
{
	kg_u16 pixelWidth;
	kg_u16 pixelHeight;
	kg_u64 userData;
} K15_GUITexture;
/*********************************************************************************/
typedef struct _K15_GUIFont
{
	K15_GUITexture texture;
} K15_GUIFont;
/*********************************************************************************/
typedef struct _K15_GUIButtonStyle
{
	kg_color32 borderUpperColor;
	kg_color32 borderLowerColor;
	kg_color32 upperBackgroundColor;
	kg_color32 lowerBackgroundColor;
	kg_color32 textColor;
	kg_u16 borderPixelThickness;
	kg_u16 verticalPixelPadding;
	kg_u16 horizontalPixelPadding;
	K15_GUIFont* font;
} K15_GUIButtonStyle;
/*********************************************************************************/
typedef struct _K15_GUILabelStyle
{
	kg_color32 textColor;
	K15_GUIFont* font;
} K15_GUILabelStyle;
/*********************************************************************************/
typedef struct _K15_GUIMenuStyle
{
	kg_color32 textColor;
	kg_color32 upperBackgroundColor;
	kg_color32 lowerBackgroundColor;
	kg_color32 upperHoveredBackgroundColor;
	kg_color32 lowerHoveredBackgroundColor;
	kg_color32 upperFocusedBackgroundColor;
	kg_color32 lowerFocusedBackgroundColor;
	kg_u32 verticalPixelPadding;
	kg_u32 horizontalPixelPadding;
	K15_GUIFont* font;
} K15_GUIMenuStyle;
/*********************************************************************************/
typedef struct _K15_GUIToolBarStyle
{
	kg_color32 lowerBackgroundColor;
	kg_color32 upperBackgroundColor;
	kg_u32 pixelHeight;
} K15_GUIToolBarStyle;
/*********************************************************************************/
typedef struct _K15_GUIMenuItemStyle
{
	kg_color32 lowerBackgroundColor;
	kg_color32 upperBackgroundColor;
	kg_color32 lowerHoveredBackgroundColor;
	kg_color32 upperHoveredBackgroundColor;
	kg_color32 lowerMouseDownBackgroundColor;
	kg_color32 upperMouseDownBackgroundColor;
	kg_color32 textColor;
	kg_u32 verticalPixelPadding;
	kg_u32 horizontalPixelPadding;
	K15_GUIFont* font;
} K15_GUIMenuItemStyle;
/*********************************************************************************/
typedef struct _K15_GUIContextStyle
{
	K15_GUIButtonStyle buttonStyle;
	K15_GUILabelStyle labelStyle;
	K15_GUIMenuStyle menuStyle;
	K15_GUIToolBarStyle toolBarStyle;
	K15_GUIMenuItemStyle menuItemStyle;
} K15_GUIContextStyle;

/*********************************************************************************/
typedef struct _K15_GUIResourceDatabase
{
	int placeholder;
} K15_GUIResourceDatabase;
/*********************************************************************************/
typedef struct _K15_GUIClipRect
{
	kg_s16 left;
	kg_s16 top;
	kg_s16 right;
	kg_s16 bottom;
} K15_GUIClipRect;
/*********************************************************************************/
typedef struct _K15_GUIContext
{
	kg_byte* memoryBuffer;
	K15_GUIResourceDatabase* resourceDatabase;
	K15_GUIContextStyle style;
	K15_GUIContextEvents events;
	K15_GUIClipRect clipRect;
	kg_u32 focusedElementIdHash;
	kg_u32 clickedElementIdHash;
	kg_u32 activatedElementIdHash;
	kg_u32 hoveredElementIdHash;
	kg_u32 mouseDownElementIdHash;
	kg_u32 memoryBufferCapacityInBytes;
	kg_u32 memoryBufferSizeInBytes;
	kg_u32 flagMask;
	kg_u8 numMenus;
	kg_u8 numLayouts;
	kg_u8 layoutIndex;
} K15_GUIContext;
/*********************************************************************************/

//how this should work:
// - Call gui logic (K15_GUIButton, K15_GUIBeginWindow, K15_GUIPushHorizontalLayout etc.)
// - Store elements internally in the gui context (just rects?) <-- headache
// - iterate over elements (layouting)
// - iterate over elements (input)
// - iterate over elements (rendering)
// - Call gui logic (next frame - retrieve results from last frame. Mainly results of the input)

kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext, kg_s16 p_ClipRect[4],
	kg_u32 p_InitFlag);

kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext, kg_s16 p_ClipRect[4],
	kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes, kg_u32 p_InitFlags);

void K15_GUIBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier);
kg_b8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY,
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier);
kg_b8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier);
kg_b8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier);
kg_b8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier);

void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier);



void K15_GUIEndWindow(K15_GUIContext* p_GUIContext);
void K15_GUIEndMenu(K15_GUIContext* p_GUIContext);
void K15_GUIEndToolBar(K15_GUIContext* p_GUIContext);

void K15_GUIFinishGUIFrame(K15_GUIContext* p_GUIContext);

void K15_GUIAddMouseInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIMouseInput* p_MouseInput);
void K15_GUIAddKeyboardInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIKeyboardInput* p_KeyboardInput);
void K15_GUIAddSystemEvent(K15_GUIContextEvents* p_GUIContextEvents, K15_GUISystemEvent* p_SystemEvent);

#ifdef K15_GUI_IMPLEMENTATION
#define internal 
#define K15_GUI_SWAP(a, b) {a ^= b; b ^= a; a ^= b;}

#ifndef K15_GUI_STRIP_STANDARD_IO
# include "stdio.h"
#endif //!K15_GUI_STRIP_STANDARD_IO

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

typedef enum _K15_GUIFontInitFlags
{
	K15_GUI_FONT_INCLUDE_LATIN_GLYPHS = 0x01,
	K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS = 0x02,
	K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS = 0x04,
	K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS = 0x08,

	K15_GUI_FONT_INCLUDE_ALL_GPYPS = K15_GUI_FONT_INCLUDE_LATIN_GLYPHS | K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS | K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS | K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS
} K15_GUIFontInitFlags;

/*********************************************************************************/
#ifndef K15_GUI_STRIP_STANDARD_IO
static kg_result K15_GUIOpenFileForReading(const char* p_FilePath,
	FILE** p_FileHandlePtr, kg_u32* p_FileSizePtr)
{
	kg_result result = K15_GUI_RESULT_SUCCESS;
	FILE* fileHandle = fopen(p_FontFilePath, "rb");

	if (!fileHandle)
		result = K15_GUI_RESULT_FILE_NOT_FOUND;

	if (fileHandle)
	{
		fseek(fileHandle, 0, SEEK_END);
		*p_FileSizePtr = (kg_u32)ftell(fileHandle);
		fseek(fileHandle, 0, SEEK_SET);

		*p_FileHandlePtr = fileHandle;
	}

	return result;
}
#endif //!K15_GUI_STRIP_STANDARD_IO
/*********************************************************************************/
static kg_u32 K15_GUIGetGlyphCountForGlyphRanges(kg_u8 p_GlyphRangeFlags)
{
	kg_u32 numGlyphes = 0;
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_LATIN_GLYPHS) > 0)
		numGlyphes += 223; //32-255
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS) > 0)
		numGlyphes += 255 + 15 + 239 + 20911; //12288-12543 & 12784-12799 & 65280-65519 & 19968-40879
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS) > 0)
		numGlyphes += 303 + 31 + 105; //1024-1327 & 11744-11775 & 42560-42665
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS) > 0)
		numGlyphes += 50 + 11165; //12593-12643 & 44032-55197

	return numGlyphes;
}
/*********************************************************************************/
static void K15_GUICalculateTextureDimensionForGlyphRange(stbtt_fontinfo* p_FontInfo, float p_ScaleFactor,
	kg_u8 p_GlyphRangeFlags, kg_u32* p_OutTextureWidth, kg_u32* p_OutTextureHeight)
{
	kg_u32 textureWidth = 0;
	kg_u32 textureHeight = 0;
	kg_u32 numGlyphs = K15_GUIGetGlyphCountForGlyphRanges(p_GlyphRangeFlags);

	K15_GUIRect* glyphRects 
}
/*********************************************************************************/
static kg_result K15_GUICreateFontResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont* p_OutFont, kg_byte* p_TrueTypeFontBuffer, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags = K15_GUI_FONT_INCLUDE_LATIN_GLYPHS)
{
	stbtt_fontinfo fontInfo = {};
	int result = stbtt_InitFont(&fontInfo, p_TrueTypeFontBuffer, 0);

	if (result == 0)
		return K15_GUI_RESULT_FONT_DATA_ERROR;

	float scaleFac = stbtt_ScaleForPixelHeight(&fontInfo, (float)p_FontSize);
	kg_u32 textureWidth = 0;
	kg_u32 textureHeight = 0;
	K15_GUICalculateTextureDimensionForGlyphRange(&fontInfo, scaleFac, p_GlyphRangeFlags, &textureWidth, &textureHeight);
}
/*********************************************************************************/
static kg_result K15_GUICreateFontResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont* p_OutFont, const char* p_FontFilePath, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags = K15_GUI_FONT_INCLUDE_LATIN_GLYPHS)
{
	kg_result result = K15_GUI_RESULT_NOT_SUPPORTED;
#ifndef K15_GUI_STRIP_STANDARD_IO
	FILE* fileHandle = 0;
	kg_u32 fileSizeInBytes = 0;

	result = K15_GUIOpenFileForReading(p_FontFilePath, &fileHandle, &fileSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS &&
		fileSizeInBytes > 0)
	{
		kg_byte* tempFontBuffer = (kg_byte*)malloc(fileSizeInBytes);

		if (!tempFontBuffer)
			result = K15_GUI_RESULT_OUT_OF_MEMORY;

		if (tempFontBuffer)
		{ 
			fread(tempFontBuffer, 1, fileSizeInBytes, fileHandle);
			fclose(fileHandle);

			result = K15_GUICreateFontResourceFromMemory(p_GUIResourceDatabase, p_OutFont,
				tempFontBuffer, p_FontSize, p_FontName, p_GlyphRangeFlags);
		}

		free(tempFontBuffer);
	}

#endif //K15_GUI_STRIP_STANDARD_IO
	return result;
}
/*********************************************************************************/
static K15_GUIContextStyle K15_GUICreateDefaultStyle(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	K15_GUIContextStyle defaultStyle;

	K15_GUIFont defaultFont = {};
	K15_GUICreateFontResourceFromFile(p_GUIResourceDatabase, &defaultFont, "Cousine-Regular.ttf", 12, "default_font");

	//Button Style
	defaultStyle.buttonStyle.borderLowerColor = K15_GUI_COLOR_RGB(16, 16, 16);
	defaultStyle.buttonStyle.borderUpperColor = K15_GUI_COLOR_RGB(96, 96, 96);
	defaultStyle.buttonStyle.lowerBackgroundColor = K15_GUI_COLOR_RGB(80, 80, 80);
	defaultStyle.buttonStyle.upperBackgroundColor = K15_GUI_COLOR_RGB(48, 48, 48);
	defaultStyle.buttonStyle.textColor = K15_GUI_COLOR_BLACK;
	defaultStyle.buttonStyle.borderPixelThickness = 2;
	defaultStyle.buttonStyle.horizontalPixelPadding = 4;
	defaultStyle.buttonStyle.verticalPixelPadding = 2;
	defaultStyle.buttonStyle.font = defaultFont;

	//Window Style
	defaultStyle.windowStyle.borderLowerColor = K15_GUI_COLOR_BLACK;
	defaultStyle.windowStyle.borderUpperColor = K15_GUI_COLOR_RGB(5, 5, 69);
	defaultStyle.windowStyle.lowerBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.windowStyle.upperBackgroundColor = K15_GUI_COLOR_RGB(16, 16, 16);
	defaultStyle.windowStyle.upperTitleBackgroundColor = K15_GUI_COLOR_BLACK;
	defaultStyle.windowStyle.lowerTitleBackgroundColor = K15_GUI_COLOR_BLACK;
	defaultStyle.windowStyle.titleTextColor = K15_GUI_COLOR_RGB(238, 238, 238);
	defaultStyle.windowStyle.borderPixelThickness = 2;
	defaultStyle.windowStyle.titlePixelPadding = 2;
	defaultStyle.windowStyle.font = defaultFont;

	//Label Style
	defaultStyle.labelStyle.textColor = K15_GUI_COLOR_BLACK;
	defaultStyle.labelStyle.font = defaultFont;

	//Toolbar Style
	defaultStyle.toolBarStyle.upperBackgroundColor = K15_GUI_COLOR_RGB(16, 16, 16);
	defaultStyle.toolBarStyle.lowerBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.toolBarStyle.pixelHeight = 22;

	//Menu Style
	defaultStyle.menuStyle.font = defaultFont;
	defaultStyle.menuStyle.menuColors.lowerBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuStyle.menuColors.upperBackgroundColor = K15_GUI_COLOR_RGB(16, 16, 16);
	defaultStyle.menuStyle.menuColors.lowerFocusedBackgroundColor = K15_GUI_COLOR_RGB(48, 48, 48);
	defaultStyle.menuStyle.menuColors.upperFocusedBackgroundColor = K15_GUI_COLOR_RGB(96, 96, 96);
	defaultStyle.menuStyle.menuColors.lowerHoveredBackgroundColor = K15_GUI_COLOR_RGB(16, 16, 16);
	defaultStyle.menuStyle.menuColors.upperHoveredBackgroundColor = K15_GUI_COLOR_RGB(64, 64, 64);
	defaultStyle.menuStyle.subMenuColors.lowerBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuStyle.subMenuColors.upperBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuStyle.subMenuColors.lowerFocusedBackgroundColor = K15_GUI_COLOR_RGB(64, 64, 64);
	defaultStyle.menuStyle.subMenuColors.upperFocusedBackgroundColor = K15_GUI_COLOR_RGB(64, 64, 64);
	defaultStyle.menuStyle.subMenuColors.lowerHoveredBackgroundColor = K15_GUI_COLOR_RGB(101, 101, 101);
	defaultStyle.menuStyle.subMenuColors.upperHoveredBackgroundColor = K15_GUI_COLOR_RGB(101, 101, 101);
	defaultStyle.menuStyle.textColor = K15_GUI_COLOR_BLACK;
	defaultStyle.menuStyle.verticalPixelPadding = 2;
	defaultStyle.menuStyle.horizontalPixelPadding = 8;

	//Menu Item Style
	defaultStyle.menuItemStyle.font = defaultFont;
	defaultStyle.menuItemStyle.lowerBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuItemStyle.upperBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuItemStyle.lowerHoveredBackgroundColor = K15_GUI_COLOR_RGB(101, 101, 101);
	defaultStyle.menuItemStyle.upperHoveredBackgroundColor = K15_GUI_COLOR_RGB(101, 101, 101);
	defaultStyle.menuItemStyle.lowerMouseDownBackgroundColor = K15_GUI_COLOR_RGB(64, 64, 64);
	defaultStyle.menuItemStyle.upperMouseDownBackgroundColor = K15_GUI_COLOR_RGB(64, 64, 64);
	defaultStyle.menuItemStyle.textColor = K15_GUI_COLOR_BLACK;
	defaultStyle.menuItemStyle.verticalPixelPadding = 2;
	defaultStyle.menuItemStyle.horizontalPixelPadding = 8;

	return defaultStyle;
}
/*********************************************************************************/
static void K15_InternalGUIHandleMouseInput(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	
}
/*********************************************************************************/
static void K15_InternalGUIHandleKeyboardInput(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	
}
/*********************************************************************************/
static void K15_InternalGUIHandleSystemEvents(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	
}
/*********************************************************************************/
static void K15_InternalGUIHandleInput(K15_GUIContextEvents* p_GUIContextEvents)
{
	
}
/*********************************************************************************/


/*********************************************************************************/
static kg_result K15_GUIValidateClipRect(K15_GUIClipRect* p_ClipRect)
{
	if ((p_ClipRect->right - p_ClipRect->left) == 0 || (p_ClipRect->bottom - p_ClipRect->top) == 0)
		return K15_GUI_RESULT_EMPTY_CLIP_RECT;

	if (p_ClipRect->left > p_ClipRect->right)
		K15_GUI_SWAP(p_ClipRect->left, p_ClipRect->right);
	
	if (p_ClipRect->top > p_ClipRect->bottom)
		K15_GUI_SWAP(p_ClipRect->top, p_ClipRect->bottom);
}
/*********************************************************************************/
kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext, K15_GUIResourceDatabase* p_ContextResources,
	kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop, kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom, 
	kg_u32 p_InitFlags = K15_GUI_DEFAULT_INIT_FLAGS)
{
	kg_byte* guiMemory = (kg_byte*)malloc(K15_GUI_MIN_MEMORY_SIZE_IN_BYTES);

	if (!guiMemory)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	return K15_CreateGUIContextWithCustomAllocator(p_OutGUIContext, p_ClipRect, 
		guiMemory, K15_GUI_MIN_MEMORY_SIZE_IN_BYTES, p_InitFlags);
}
/*********************************************************************************/
kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext, 
	K15_GUIResourceDatabase* p_ContextResources, kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop,
	kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom, kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes, 
	kg_u32 p_InitFlags = K15_GUI_DEFAULT_INIT_FLAGS)
{
	if (!p_Memory)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	if (p_MemorySizeInBytes < K15_GUI_MIN_MEMORY_SIZE_IN_BYTES)
		return K15_GUI_RESULT_NOT_ENOUGH_MEMORY;

	K15_GUIClipRect clipRect = {};
	clipRect.left = p_ClipPosLeft;
	clipRect.top = p_ClipPosTop;
	clipRect.right = p_ClipPosRight;
	clipRect.bottom = p_ClipPosBottom;

	kg_result clipRectValidationResult = K15_GUIValidateClipRect(&clipRect);

	if (clipRectValidationResult != K15_GUI_RESULT_SUCCESS)
		return clipRectValidationResult;

	kg_byte* guiMemory = p_Memory;
	kg_u32 guiMemorySizeInBytes = p_MemorySizeInBytes;

	K15_GUIContext* guiContext = (K15_GUIContext*)guiMemory;
	guiMemory += sizeof(K15_GUIContext);
	guiMemorySizeInBytes -= sizeof(K15_GUIContext);

	//nullify the rest of the memory
	memset(guiMemory, 0, guiMemorySizeInBytes);

	guiContext->memoryBuffer = guiMemory;
	guiContext->memoryBufferSizeInBytes = guiMemorySizeInBytes;
	guiContext->memoryBufferCapacityInBytes = guiMemorySizeInBytes;
	guiContext->focusedElementIdHash = 0;
	guiContext->hoveredElementIdHash = 0;
	guiContext->clickedElementIdHash = 0;
	guiContext->mouseDownElementIdHash = 0;
	guiContext->layoutIndex = 0;
	guiContext->numLayouts = 0;
	guiContext->numMenus = 0;
	guiContext->style = K15_InternalCreateDefaultStyle(p_ContextResources);
	guiContext->resourceDatabase = p_ContextResources;
	guiContext->activatedElementIdHash = 0;
	guiContext->events.numBufferedKeyboardInputs = 0;
	guiContext->events.numBufferedMouseInputs = 0;
	guiContext->flagMask = 0;
	guiContext->clipRect = clipRect;

	//assign newly created gui context
	*p_OutGUIContext = *guiContext;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
void K15_GUIBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier)
{
	
}
/*********************************************************************************/
kg_b8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY,
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier)
{
	K15_GUIContextStyle* style = &p_GUIContext->style;
	return K15_GUIBeginWindowEX(p_GUIContext, p_PosX, p_PosY, p_Width, p_Height, p_Title,
		p_Identifier, &style->windowStyle);
}
/*********************************************************************************/
kg_b8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier)
{
	return K15_GUIBeginMenuEX(p_GUIContext, p_MenuText, p_Identifier, &p_GUIContext->style.menuStyle);
}
/*********************************************************************************/
kg_b8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier)
{
	return K15_GUIMenuItemEX(p_GUIContext, p_ItemText, p_Identifier, &p_GUIContext->style.menuItemStyle);
}
/*********************************************************************************/
kg_b8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier)
{
	K15_GUIButtonStyle* defaultButtonStyle = &p_GUIContext->style.buttonStyle;
	return K15_GUIButtonEX(p_GUIContext, p_ButtonText, p_Identifier, defaultButtonStyle);
}
/*********************************************************************************/
void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier)
{
	K15_GUILabelEX(p_GUIContext, p_LabelText, p_Identifier, &p_GUIContext->style.labelStyle);
}
/*********************************************************************************/
void K15_GUIEndMenu(K15_GUIContext* p_GUIContext)
{
	p_GUIContext->numMenus -= 1;

	if (p_GUIContext->numMenus == 0)
		p_GUIContext->flagMask &= ~K15_GUI_CONTEXT_INSIDE_MENU_FLAG;

	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
void K15_GUIEndSubMenu(K15_GUIContext* p_GUIContext)
{
	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
void K15_GUIEndWindow(K15_GUIContext* p_GUIContext)
{
	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
void K15_GUIEndToolBar(K15_GUIContext* p_GUIContext)
{
	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
void K15_GUIFinishGUIFrame(K15_GUIContext* p_GUIContext)
{

}
/*********************************************************************************/
void K15_GUIAddMouseInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIMouseInput* p_MouseInput)
{
	K15_ASSERT(p_GUIContextEvents);
	K15_ASSERT(p_MouseInput);

	uint32 mouseInputIndex = p_GUIContextEvents->numBufferedMouseInputs++;
	K15_ASSERT(mouseInputIndex != K15_GUI_MAX_BUFFERED_MOUSE_INPUTS);

	p_GUIContextEvents->bufferedMouseInput[mouseInputIndex] = *p_MouseInput;
}
/*********************************************************************************/
void K15_GUIAddKeyboardInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIKeyboardInput* p_KeyboardInput)
{
	K15_ASSERT(p_GUIContextEvents);
	K15_ASSERT(p_KeyboardInput);

	uint32 keyInputIndex = p_GUIContextEvents->numBufferedKeyboardInputs++;
	K15_ASSERT(keyInputIndex != K15_GUI_MAX_BUFFERED_KEYBOARD_INPUTS);

	p_GUIContextEvents->bufferedKeyboardInput[keyInputIndex] = *p_KeyboardInput;
}
/*********************************************************************************/
void K15_GUIAddSystemEvent(K15_GUIContextEvents* p_GUIContextEvents, K15_GUISystemEvent* p_SystemEvent)
{
	K15_ASSERT(p_GUIContextEvents);
	K15_ASSERT(p_SystemEvent);

	uint32 systemEventIndex = p_GUIContextEvents->numBufferedSystemEvents++;
	K15_ASSERT(systemEventIndex != K15_GUI_MAX_BUFFERED_SYSTEM_EVENTS);

	p_GUIContextEvents->bufferedSystemEvents[systemEventIndex] = *p_SystemEvent;
}
/*********************************************************************************/

#endif //K15_GUI_IMPLEMENTATION

#endif //_K15_GUILayer_Context_h_
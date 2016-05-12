#ifndef _K15_GUILayer_Context_h_
#define _K15_GUILayer_Context_h_

#define K15_GUI_MAX_LAYOUTS 20
#define K15_GUI_MAX_RESOURCE_NAME_LENGTH 64
#define K15_GUI_MAX_ICONS_PER_ICON_SET 64
#define K15_GUI_MAX_ELEMENT_PTR_PER_LAYOUT 128

#define K15_GUI_MAX_BUFFERED_MOUSE_INPUTS 16
#define K15_GUI_MAX_BUFFERED_KEYBOARD_INPUTS 16
#define K15_GUI_MAX_BUFFERED_SYSTEM_EVENTS 16

#define K15_GUI_TRUE 1
#define K15_GUI_FALSE 0

#define kg_size_kilo_bytes(n) (n*1024)

#define K15_GUI_MIN_MEMORY_SIZE_IN_BYTES sizeof(K15_GUIContext) + kg_size_kilo_bytes(10)
#define K15_GUI_DEFAULT_RESOURCE_DATABASE_MEMORY_SIZE kg_size_kilo_bytes(256)

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

struct _K15_GUIContext;
/*********************************************************************************/
typedef enum _K15_GUIResults
{
	K15_GUI_RESULT_SUCCESS = 0,
	K15_GUI_RESULT_OUT_OF_MEMORY = 1,
	K15_GUI_RESULT_FONT_DATA_ERROR = 2,
	K15_GUI_RESULT_NOT_SUPPORTED = 3,
	K15_GUI_RESULT_FILE_NOT_FOUND = 4,
	K15_GUI_RESULT_EMPTY_CLIP_RECT = 5,
	K15_GUI_RESULT_INVALID_ARGUMENTS = 6,
	K15_GUI_RESULT_OUT_OF_RANGE = 7,
	K15_GUI_RESULT_NAME_ALREADY_IN_USE = 8,
	K15_GUI_RESULT_RESOURCE_NOT_FOUND = 9,
	K15_GUI_RESULT_IMAGE_DATA_ERROR = 10,
	K15_GUI_RESULT_FILE_FORMAT_NOT_SUPPORTED = 11,
	K15_GUI_RESULT_TOO_MANY_ICONS = 12,
	K15_GUI_RESULT_NO_ICONS = 13
} kg_result;
/*********************************************************************************/
enum _K15_GUIContextInitFlags
{
	K15_GUI_SHAPE_BASED_DRAW_COMMANDS = 0x001,
	K15_GUI_VERTEX_BASED_DRAW_COMMANDS = 0x002,

	K15_GUI_DEFAULT_INIT_FLAGS = K15_GUI_VERTEX_BASED_DRAW_COMMANDS
} K15_GUIContextInitFlags;
/*********************************************************************************/
typedef enum _K15_GUIFontInitFlags
{
	K15_GUI_FONT_INCLUDE_LATIN_GLYPHS = 0x01,
	K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS = 0x02,
	K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS = 0x04,
	K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS = 0x08,

	K15_GUI_FONT_INCLUDE_ALL_GPYPS = K15_GUI_FONT_INCLUDE_LATIN_GLYPHS | K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS | K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS | K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS
} K15_GUIFontInitFlags;
/*********************************************************************************/
typedef enum _K15_GUIDrawCommandCreationFlags
{
	K15_GUI_CONVERT_TO_NDC = 0x01
} K15_GUIDrawCommandCreationFlags;
/*********************************************************************************/
typedef enum _K15_GUIContextFlags
{
	K15_GUI_CONTEXT_INSIDE_MENU_FLAG = 0x01
} K15_GUIContextFlags;
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
typedef enum _K15_GUIResourceType
{
	K15_GUI_FONT_RESOURCE_TYPE = 0,
	K15_GUI_ICON_RESOURCE_TYPE,
	K15_GUI_ICONSET_RESOURCE_TYPE
} K15_GUIResourceType;
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
	kg_s32 pixelPosLeft;
	kg_s32 pixelPosTop;
	kg_s32 pixelPosRight;
	kg_s32 pixelPosBottom;
} K15_GUIRectangle;
/*********************************************************************************/
typedef struct _K15_GUITexture
{
	kg_u16 numColorComponents;
	kg_u16 pixelWidth;
	kg_u16 pixelHeight;
	kg_byte* pixelData;
	kg_u64 userData;
} K15_GUITexture;
/*********************************************************************************/
typedef struct _K15_GUIFont
{
	float scaleFactor;
	kg_u32 glyphRangeMask;
	kg_s32 fontSize;
	kg_s32 lineGap;
	kg_s32 ascent;
	kg_s32 descent;
	kg_u32 numGlyphs;
	K15_GUITexture texture;
} K15_GUIFont;
/*********************************************************************************/
typedef struct _K15_GUIFontGlyph
{
	K15_GUIRectangle glyphRect;
	kg_u32 codepoint;
	kg_s32 leftSideBearing;
	kg_s32 advancewidth;
} K15_GUIFontGlyph;
/*********************************************************************************/
typedef struct _K15_GUIIcon
{
	kg_byte* pixelData;
	kg_u32 pixelHeight;
	kg_u32 pixelWidth;
	kg_u32 numColorComponents;
} K15_GUIIcon;
/*********************************************************************************/
typedef struct _K15_GUIIconMarker
{
	K15_GUIRectangle atlasClipRect;
	char name[K15_GUI_MAX_RESOURCE_NAME_LENGTH];
} K15_GUIIconMarker;
/*********************************************************************************/
typedef struct _K15_GUIIconSet
{
	K15_GUIIconMarker iconMarker[K15_GUI_MAX_ICONS_PER_ICON_SET];
	K15_GUITexture texture;
	kg_u32 numIconMarker;
} K15_GUIIconSet;
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
typedef struct _K15_GUIWindowStyle
{
	kg_color32 borderLowerColor;
	kg_color32 borderUpperColor;
	kg_color32 lowerBackgroundColor;
	kg_color32 upperBackgroundColor;
	kg_color32 upperTitleBackgroundColor;
	kg_color32 lowerTitleBackgroundColor;
	kg_color32 titleTextColor;
	kg_u8 borderPixelThickness;
	kg_u8 titlePixelPadding;
	K15_GUIFont* font;
} K15_GUIWindowStyle;
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
	K15_GUIWindowStyle windowStyle;
	K15_GUIButtonStyle buttonStyle;
	K15_GUILabelStyle labelStyle;
	K15_GUIMenuStyle menuStyle;
	K15_GUIToolBarStyle toolBarStyle;
	K15_GUIMenuItemStyle menuItemStyle;
} K15_GUIContextStyle;
/*********************************************************************************/
typedef struct _K15_GUIResourceTableEntry
{
	char name[K15_GUI_MAX_RESOURCE_NAME_LENGTH];
	kg_u32 sizeInBytes;
	K15_GUIResourceType type;
} K15_GUIResourceTableEntry;
/*********************************************************************************/
typedef struct _K15_GUIResourceDatabase
{	
	K15_GUIResourceTableEntry* resourceTable;
	kg_byte* resourceMemory;
	kg_u32 resourceMemoryCapacityInBytes;
	kg_u32 resourceMemorySizeInBytes;
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
typedef struct _K15_GUIGlyphRange
{
	kg_u32 from;
	kg_u32 to;
} K15_GUIGlyphRange;
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

kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext, K15_GUIResourceDatabase* p_ContextResources,
	kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop, kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom,
	kg_u32 p_InitFlags = K15_GUI_DEFAULT_INIT_FLAGS);

kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext,
	K15_GUIResourceDatabase* p_ContextResources, kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop,
	kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom, kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes,
	kg_u32 p_InitFlags = K15_GUI_DEFAULT_INIT_FLAGS);

//*****************RESOURCES******************//
kg_result K15_GUICreateResourceDatabase(K15_GUIResourceDatabase* p_GUIResourceDatabase);
kg_result K15_GUICreateResourceDatabaseWithCustomMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_DatabaseMemory, kg_u32 p_DatabaseMemorySizeInBytes);

kg_result K15_GUICreateFontResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, const char* p_FontFilePath, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags = K15_GUI_FONT_INCLUDE_LATIN_GLYPHS);

kg_result K15_GUICreateFontResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, kg_byte* p_TrueTypeFontBuffer, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags = K15_GUI_FONT_INCLUDE_LATIN_GLYPHS);

kg_result K15_GUICreateIconResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	const char* p_IconFilePath, const char* p_IconName);

kg_result K15_GUICreateIconResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_IconFileMemory, kg_u32 p_IconFileDataBufferSizeInBytes, const char* p_IconName);

kg_result K15_GUICreateIconResourceFromMemoryRaw(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_IconPixelDataBuffer, kg_u32 p_PixelWidth, kg_u32 p_PixelHeight, 
	kg_u8 p_ColorComponents, const char* p_IconName);

kg_result K15_GUIBakeIconResources(K15_GUIResourceDatabase* p_GUIResourceDatabase, 
	K15_GUIIconSet** p_OutIconSet, const char* p_IconSetName);

void K15_GUIBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier);
void K15_GUICustomBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier, K15_GUIToolBarStyle* p_Style);

kg_b8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY, kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier);
kg_b8 K15_GUICustomBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY, kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier, K15_GUIWindowStyle* p_Style);

kg_b8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier);
kg_b8 K15_GUICustomBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier, K15_GUIMenuStyle* p_Style);

kg_b8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier);
kg_b8 K15_GUICustomMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier, K15_GUIMenuItemStyle* p_Style);

kg_b8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier);
kg_b8 K15_GUICustomButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier, K15_GUIButtonStyle* p_Style);

void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier);
void K15_GUICustomLabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier, K15_GUILabelStyle* p_Style);

void K15_GUISeparator(K15_GUIContext* p_GUIContext);

void K15_GUIEndWindow(K15_GUIContext* p_GUIContext);
void K15_GUIEndMenu(K15_GUIContext* p_GUIContext);
void K15_GUIEndToolBar(K15_GUIContext* p_GUIContext);

void K15_GUIFinishFrame(K15_GUIContext* p_GUIContext);

void K15_GUIPopLayout(K15_GUIContext* p_GUIContext);

void K15_GUIConvertResultToMessage(kg_result p_Result, char** p_OutMessage, kg_u32 p_OutMessageBufferSizeInBytes);

kg_result K15_GUIAddMouseInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIMouseInput p_MouseInput);
kg_result K15_GUIAddKeyboardInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIKeyboardInput p_KeyboardInput);
kg_result K15_GUIAddSystemEvent(K15_GUIContextEvents* p_GUIContextEvents, K15_GUISystemEvent p_SystemEvent);

#ifdef K15_GUI_IMPLEMENTATION
#define internal static
#define K15_GUI_SWAP(a, b) {a ^= b; b ^= a; a ^= b;}

#ifndef K15_GUI_STRIP_STANDARD_IO
# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
#endif //!K15_GUI_STRIP_STANDARD_IO

#ifndef K15_GUI_MALLOC
# include <malloc.h>
# define K15_GUI_MALLOC malloc
# define K15_GUI_FREE free
#endif //K15_GUI_MALLOC

#ifndef K15_GUI_MEMCPY
# include <string.h>
# define K15_GUI_MEMCPY memcpy
#endif //K15_GUI_MEMCPY

#ifndef K15_GUI_MEMMOVE
# include <string.h>
# define K15_GUI_MEMMOVE memmove
#endif //K15_GUI_MEMMOVE

#ifndef K15_GUI_STRLEN
# include <string.h>
# define K15_GUI_STRLEN strlen
#endif //K15_GUI_STRLEN

#ifndef K15_GUI_STRCMP
# include <string.h>
# define K15_GUI_STRCMP strcmp
#endif //K15_GUI_STRCMP

#ifndef K15_GUI_MIN
# define K15_GUI_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif //K15_GUI_MIN

#ifndef K15_GUI_MAX
# define K15_GUI_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif //K15_GUI_MAX

#define K15_GUI_COLOR_RGBA(r,g,b,a) ((a << 24) | (b << 16) | (g << 8) | (r << 0))
#define K15_GUI_COLOR_RGB(r,g,b) K15_GUI_COLOR_RGBA(r,g,b,255)
#define K15_GUI_COLOR_BLACK K15_GUI_COLOR_RGB(0, 0, 0)
#define K15_GUI_COLOR_WHITE K15_GUI_COLOR_RGB(255, 255, 255)

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define K15_IA_IMPLEMENTATION
#include "K15_ImageAtlas.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_GIF
#define STBI_FAILURE_USERMSG
#define STBI_MALLOC K15_GUI_MALLOC
#define STBI_FREE K15_GUI_FREE
#define STBI_REALLOC realloc
#include "stb_image.h"

/*********************************************************************************/
#ifndef K15_GUI_STRIP_STANDARD_IO
static kg_result K15_GUIOpenFileForReading(const char* p_FilePath,
	FILE** p_FileHandlePtr, kg_u32* p_FileSizePtr)
{
	kg_result result = K15_GUI_RESULT_SUCCESS;
	FILE* fileHandle = fopen(p_FilePath, "rb");

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
static kg_u32 K15_GUIGetGlyphRanges(kg_u8 p_GlyphRangeFlags, K15_GUIGlyphRange** p_OutGlyphRangeArray,
	kg_u32 p_GlyphRangeArraySize)
{
	kg_u32 glyphRangeIndex = 0;

#define K15_GUI_SET_GLYPH_RANGE(f, t) \
	if (glyphRangeIndex < p_GlyphRangeArraySize) \
	{ \
		p_OutGlyphRangeArray[glyphRangeIndex]->from = f;\
		p_OutGlyphRangeArray[glyphRangeIndex++]->to = t;\
	}
	
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_LATIN_GLYPHS) > 0) 
	{
		K15_GUI_SET_GLYPH_RANGE(33, 255);
	}
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS) > 0)
	{
		K15_GUI_SET_GLYPH_RANGE(12288, 12543);
		K15_GUI_SET_GLYPH_RANGE(12784, 12799);
		K15_GUI_SET_GLYPH_RANGE(65280, 65519);
		K15_GUI_SET_GLYPH_RANGE(19968, 40879);
	}
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS) > 0)
	{
		K15_GUI_SET_GLYPH_RANGE(1024, 1327);
		K15_GUI_SET_GLYPH_RANGE(11744, 11775);
		K15_GUI_SET_GLYPH_RANGE(42560, 42665);
	}
	if ((p_GlyphRangeFlags & K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS) > 0)
	{
		K15_GUI_SET_GLYPH_RANGE(12593, 12643);
		K15_GUI_SET_GLYPH_RANGE(44032, 55197);
	}
#undef K15_GUI_SET_GLYPH_RANGE

	return glyphRangeIndex;
}
/*********************************************************************************/
static kg_result K15_GUIConvertIAResult(kia_result p_ResultIA)
{
	if (p_ResultIA == K15_IA_RESULT_OUT_OF_MEMORY)
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	else if (p_ResultIA == K15_IA_RESULT_OUT_OF_RANGE)
		return K15_GUI_RESULT_OUT_OF_RANGE;
	else if (p_ResultIA == K15_IA_RESULT_INVALID_ARGUMENTS)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
static kg_result K15_GUIConvertSTBIResult(const char* p_ResultSTBI)
{
	if (K15_GUI_STRCMP(p_ResultSTBI, "Corrupt JPEG") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "Corrupt PNG") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "Very large image (corrupt?)") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "Image not of any known type, or corrupt") == 0)
		return K15_GUI_RESULT_IMAGE_DATA_ERROR;

	if (K15_GUI_STRCMP(p_ResultSTBI, "JPEG format not supported: 8-bit only") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "JPEG format not supported: delayed height") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "Image too large to decode") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "Not a PNG") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "PNG not supported: 1/2/4/8-bit only") == 0 ||
		K15_GUI_STRCMP(p_ResultSTBI, "PNG not supported: unknown PNG chunk type") == 0)
		return K15_GUI_RESULT_FILE_FORMAT_NOT_SUPPORTED;

	if (K15_GUI_STRCMP(p_ResultSTBI, "Out of memory"))
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	if (K15_GUI_STRCMP(p_ResultSTBI, "Unable to open file"))
		return K15_GUI_RESULT_FILE_NOT_FOUND;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
static kg_result K15_GUICreateResourceDatabase(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	if (!p_GUIResourceDatabase)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	kg_byte* resourceDatabaseMemory = (kg_byte*)K15_GUI_MALLOC(K15_GUI_DEFAULT_RESOURCE_DATABASE_MEMORY_SIZE);

	if (!resourceDatabaseMemory)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	return K15_GUICreateResourceDatabaseWithCustomMemory(p_GUIResourceDatabase, 
		resourceDatabaseMemory, K15_GUI_DEFAULT_RESOURCE_DATABASE_MEMORY_SIZE);
}
/*********************************************************************************/
static kg_result K15_GUICreateResourceDatabaseWithCustomMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_DatabaseMemory, kg_u32 p_DatabaseMemorySizeInBytes)
{
	if (!p_DatabaseMemory || p_DatabaseMemorySizeInBytes == 0)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	p_GUIResourceDatabase->resourceMemory = p_DatabaseMemory;
	p_GUIResourceDatabase->resourceMemoryCapacityInBytes = p_DatabaseMemorySizeInBytes;
	p_GUIResourceDatabase->resourceMemorySizeInBytes = 0;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
static kg_result K15_GUICreateFontResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, const char* p_FontFilePath, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags)
{
	kg_result result = K15_GUI_RESULT_NOT_SUPPORTED;
#ifndef K15_GUI_STRIP_STANDARD_IO
	FILE* fileHandle = 0;
	kg_u32 fileSizeInBytes = 0;

	result = K15_GUIOpenFileForReading(p_FontFilePath, &fileHandle, &fileSizeInBytes);

	if (result == K15_GUI_RESULT_SUCCESS &&
		fileSizeInBytes > 0)
	{
		kg_byte* tempFontBuffer = (kg_byte*)K15_GUI_MALLOC(fileSizeInBytes);

		if (!tempFontBuffer)
		{
			fclose(fileHandle);
			result = K15_GUI_RESULT_OUT_OF_MEMORY;
		}

		if (tempFontBuffer)
		{ 
			fread(tempFontBuffer, 1, fileSizeInBytes, fileHandle);
			fclose(fileHandle);

			result = K15_GUICreateFontResourceFromMemory(p_GUIResourceDatabase, p_OutFont,
				tempFontBuffer, p_FontSize, p_FontName, p_GlyphRangeFlags);
		}

		K15_GUI_FREE(tempFontBuffer);
	}

#endif //K15_GUI_STRIP_STANDARD_IO
	return result;
}
/*********************************************************************************/
static kg_result K15_GUIGrowResourceTable(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	kg_u32 resourceMemoryGrowSizeInBytes= kg_size_kilo_bytes(256);
	kg_u32 sizeMemoryBufferInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;
	kg_u32 capacityMemoryBufferInBytes = p_GUIResourceDatabase->resourceMemoryCapacityInBytes;

	kg_u32 newResourceMemoryBufferSizeInBytes = capacityMemoryBufferInBytes + resourceMemoryGrowSizeInBytes;

	K15_GUIResourceTableEntry* newResourceTable = 
		(K15_GUIResourceTableEntry*)K15_GUI_MALLOC(newResourceMemoryBufferSizeInBytes);

	K15_GUIResourceTableEntry* currentResourceTable = p_GUIResourceDatabase->resourceTable;

	if (!newResourceTable)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	K15_GUI_MEMCPY(newResourceTable, currentResourceTable, sizeMemoryBufferInBytes);

	K15_GUI_FREE(currentResourceTable);

	p_GUIResourceDatabase->resourceMemoryCapacityInBytes = newResourceMemoryBufferSizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
static kg_b8 K15_GUIFitsIntoResourceTableMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_u32 p_SizeInBytes)
{
	kg_u32 capacityResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemoryCapacityInBytes;
	kg_u32 sizeResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;

	return (capacityResourceMemoryInBytes >= sizeResourceMemoryInBytes + p_SizeInBytes);
}
/*********************************************************************************/
static kg_b8 K15_GUISearchResourceTableEntry(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	const char* p_ResourceName, K15_GUIResourceTableEntry** p_OutResourceTableEntryPtr)
{
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 resourceMemorySizeInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;
	kg_u32 resourceMemoryPosition = 0;

	K15_GUIResourceTableEntry* tableEntry = 0;
	
	while (resourceMemoryPosition < resourceMemorySizeInBytes)
	{
		tableEntry = (K15_GUIResourceTableEntry*)(resourceMemory + resourceMemoryPosition);

		if (K15_GUI_STRCMP(tableEntry->name, p_ResourceName) == 0)
		{
			if (p_OutResourceTableEntryPtr)
				*p_OutResourceTableEntryPtr = tableEntry;

			return K15_GUI_TRUE;
		}

		resourceMemoryPosition += tableEntry->sizeInBytes;
	}

	return K15_GUI_FALSE;
}
/*********************************************************************************/
static kg_result K15_GUICreateResourceTableEntry(K15_GUIResourceDatabase* p_GUIResourceDatabase, 
	K15_GUIResourceTableEntry** p_TableEntryPtr, const char* p_Name, K15_GUIResourceType p_ResourceType)
{
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 sizeResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;

	if (!K15_GUIFitsIntoResourceTableMemory(p_GUIResourceDatabase, sizeof(K15_GUIResourceTableEntry)))
	{
		kg_result growResult = K15_GUIGrowResourceTable(p_GUIResourceDatabase);
		if (growResult != K15_GUI_RESULT_SUCCESS)
			return growResult;
	}

	kg_u32 nameLength = K15_GUI_MIN(K15_GUI_STRLEN(p_Name), K15_GUI_MAX_RESOURCE_NAME_LENGTH);

	K15_GUIResourceTableEntry* tableEntry = 
		(K15_GUIResourceTableEntry*)(resourceMemory + sizeResourceMemoryInBytes);

	K15_GUI_MEMCPY(tableEntry->name, p_Name, nameLength);
	tableEntry->name[nameLength] = 0;
	tableEntry->type = p_ResourceType;
	tableEntry->sizeInBytes = sizeof(K15_GUIResourceTableEntry);

	*p_TableEntryPtr = tableEntry;

	p_GUIResourceDatabase->resourceMemorySizeInBytes += sizeof(K15_GUIResourceTableEntry);

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
static kg_result K15_GUIGetResourceTableEntryMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIResourceTableEntry* p_TableEntry, void** p_MemoryPtr, kg_u32 p_SizeInBytes)
{
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 sizeResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;

	while (!K15_GUIFitsIntoResourceTableMemory(p_GUIResourceDatabase, p_SizeInBytes))
	{
		kg_result growResult = K15_GUIGrowResourceTable(p_GUIResourceDatabase);
		if (growResult != K15_GUI_RESULT_SUCCESS)
			return growResult;
	}

	p_TableEntry->sizeInBytes += p_SizeInBytes;

	*p_MemoryPtr = (resourceMemory + sizeResourceMemoryInBytes);
	p_GUIResourceDatabase->resourceMemorySizeInBytes += p_SizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
static kg_result K15_GUIRemoveResourceTableEntryByName(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	const char* p_ResourceName)
{
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 resourceMemorySizeInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;
	kg_u32 resourceMemoryPosition = 0;

	while (resourceMemoryPosition < resourceMemorySizeInBytes)
	{
		K15_GUIResourceTableEntry* tableEntry =
			(K15_GUIResourceTableEntry*)(resourceMemory + resourceMemoryPosition);

		if (K15_GUI_STRCMP(tableEntry->name, p_ResourceName) == 0)
		{
			kg_u32 resourceSizeInBytes = tableEntry->sizeInBytes;
			kg_u32 bytesToMove = resourceMemorySizeInBytes - resourceMemoryPosition + resourceSizeInBytes;

			if (bytesToMove > 0)
			{
				K15_GUI_MEMMOVE(resourceMemory + resourceMemoryPosition,
					resourceMemory + resourceMemoryPosition + resourceSizeInBytes,
					resourceSizeInBytes);
			}

			p_GUIResourceDatabase->resourceMemorySizeInBytes -= resourceSizeInBytes;
			return K15_GUI_RESULT_SUCCESS;
		}
	}

	return K15_GUI_RESULT_RESOURCE_NOT_FOUND;
}
/*********************************************************************************/
static kg_result K15_GUICreateFontResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, kg_byte* p_TrueTypeFontBuffer, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags)
{
	K15_GUIRectangle* glyphRects = 0;
	K15_GUIGlyphRange* glyphRanges = 0;
	K15_GUIResourceTableEntry* tableEntry = 0;
	kg_s32 ascent = 0;
	kg_s32 descent = 0;
	kg_s32 lineGap = 0;
	kg_result result = K15_GUI_RESULT_SUCCESS;

	if (K15_GUISearchResourceTableEntry(p_GUIResourceDatabase, p_FontName, 0))
		return K15_GUI_RESULT_NAME_ALREADY_IN_USE;

	stbtt_fontinfo fontInfo = {};
	int resultSTBTT = stbtt_InitFont(&fontInfo, p_TrueTypeFontBuffer, 0);

	if (resultSTBTT == 0)
		return K15_GUI_RESULT_FONT_DATA_ERROR;

	float scaleFac = stbtt_ScaleForPixelHeight(&fontInfo, (float)p_FontSize);

	stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);

	kg_u32 numGlyphs = K15_GUIGetGlyphCountForGlyphRanges(p_GlyphRangeFlags);

	kg_u32 numComponents = 1;
	K15_ImageAtlas textureAtlas = {};
	kia_result taResult = K15_IACreateAtlas(&textureAtlas, numComponents);

	if (taResult != K15_IA_RESULT_SUCCESS)
	{
		result = K15_GUIConvertIAResult(taResult);
		goto freeResources;
	}
	
	result = K15_GUICreateResourceTableEntry(p_GUIResourceDatabase, &tableEntry,
		p_FontName, K15_GUI_FONT_RESOURCE_TYPE);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto freeResources;

	K15_GUIFont* guiFont = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&guiFont, sizeof(K15_GUIFont));

	if (result != K15_GUI_RESULT_SUCCESS)
		goto freeResources;

	K15_GUIFontGlyph* guiFontGlyphs = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&guiFontGlyphs, sizeof(K15_GUIFontGlyph) * numGlyphs);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto freeResources;


	kg_u32 glyphRangeArraySize = 10;

	glyphRects = (K15_GUIRectangle*)K15_GUI_MALLOC(numGlyphs * sizeof(K15_GUIRectangle));
	glyphRanges = (K15_GUIGlyphRange*)K15_GUI_MALLOC(sizeof(K15_GUIGlyphRange) * glyphRangeArraySize);

	if (!glyphRects || !glyphRanges)
	{
		result = K15_GUI_RESULT_OUT_OF_MEMORY;
		goto freeResources;
	}

	glyphRangeArraySize = K15_GUIGetGlyphRanges(p_GlyphRangeFlags, &glyphRanges, glyphRangeArraySize);

	kg_u32 glyphIndex = 0;

	for (kg_u32 glyphRangeIndex = 0;
		glyphRangeIndex < glyphRangeArraySize;
		++glyphRangeIndex)
	{
		K15_GUIGlyphRange* glyphRange = glyphRanges + glyphRangeIndex;

		kg_u32 codepoint = glyphRange->from;
		kg_u32 endCodepoint = glyphRange->to;
		kg_u32 glyphArrayIndex = 0;
		while (codepoint < endCodepoint)
		{
			K15_GUIRectangle* glyphRect = glyphRects + glyphArrayIndex;
			
			kg_s32 glyphIndex = stbtt_FindGlyphIndex(&fontInfo, codepoint);
			codepoint += 1;

			kg_s32 glyphBitmapWidth = 0;
			kg_s32 glyphBitmapHeight = 0;

			kg_byte* glyphBitmap = stbtt_GetGlyphBitmap(&fontInfo, scaleFac, scaleFac, glyphIndex, 
				&glyphBitmapWidth, &glyphBitmapHeight, 0, 0);

			if (glyphBitmap && 
				glyphBitmapHeight > 0 && 
				glyphBitmapWidth > 0)
			{
				kia_u32 glyphBitmapPosX = 0;
				kia_u32 glyphBitmapPosY = 0;

				taResult = K15_IAAddImageToAtlas(&textureAtlas, glyphBitmap,
					numComponents, glyphBitmapWidth, glyphBitmapHeight, 
					&glyphBitmapPosX, &glyphBitmapPosY);

				kg_s32 leftSideBearing = 0;
				kg_s32 advanceWidth = 0;

				stbtt_GetGlyphHMetrics(&fontInfo, glyphIndex, &advanceWidth, &leftSideBearing);

				glyphRect->pixelPosLeft = glyphBitmapPosX;
				glyphRect->pixelPosTop = glyphBitmapPosY;
				glyphRect->pixelPosRight = glyphBitmapPosX + glyphBitmapWidth;
				glyphRect->pixelPosBottom = glyphBitmapPosY + glyphBitmapHeight;

				if (taResult != K15_IA_RESULT_SUCCESS)
				{
					result = K15_GUIConvertIAResult(taResult);
					goto freeResources;
				}

				K15_GUIFontGlyph* fontGlyph = guiFontGlyphs + glyphArrayIndex;
				fontGlyph->codepoint = codepoint;
				fontGlyph->glyphRect = *glyphRect;
				fontGlyph->leftSideBearing = leftSideBearing;
				fontGlyph->advancewidth = advanceWidth;
				
				glyphArrayIndex += 1;
			}
		}
	}

	kia_u32 textureWidth = 0;
	kia_u32 textureHeight = 0;
	kia_byte* texturePixelData = K15_IAGetAtlasPixelData(&textureAtlas, &textureWidth, &textureHeight);
	kia_u32 texturePixelDataSizeInBytes = K15_IAGetAtlasPixelDataSizeInBytes(&textureAtlas);

	kg_byte* copyTexturePixelDataMemory = (kia_byte*)K15_GUI_MALLOC(texturePixelDataSizeInBytes);

	if (!copyTexturePixelDataMemory)
	{
		result = K15_GUI_RESULT_OUT_OF_MEMORY;
		goto freeResources;
	}

	K15_GUI_MEMCPY(copyTexturePixelDataMemory, texturePixelData, texturePixelDataSizeInBytes);

	guiFont->texture.pixelHeight = textureHeight;
	guiFont->texture.pixelWidth = textureWidth;
	guiFont->texture.pixelData = copyTexturePixelDataMemory;
	guiFont->texture.numColorComponents = numComponents;
	guiFont->texture.userData = 0;

freeResources:
	if (result == K15_IA_RESULT_SUCCESS)
	{
		guiFont->glyphRangeMask = p_GlyphRangeFlags;
		guiFont->fontSize = p_FontSize;
		guiFont->lineGap = lineGap;
		guiFont->ascent = ascent;
		guiFont->descent = descent;
		guiFont->scaleFactor = scaleFac;
		guiFont->numGlyphs = numGlyphs;

		*p_OutFont = guiFont;
	}
	else
	{
		K15_GUIRemoveResourceTableEntryByName(p_GUIResourceDatabase, tableEntry->name);
	}

	K15_IAFreeAtlas(&textureAtlas);
	K15_GUI_FREE(glyphRanges);
	K15_GUI_FREE(glyphRects);

	return result;
}
/*********************************************************************************/
kg_result K15_GUICreateIconResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	const char* p_IconFilePath, const char* p_IconName)
{
	kg_result result = K15_GUI_RESULT_NOT_SUPPORTED;
#ifndef K15_GUI_STRIP_STANDARD_IO
	FILE* fileHandle = 0;
	kg_u32 fileSizeInBytes = 0;

	result = K15_GUIOpenFileForReading(p_IconFilePath, &fileHandle, &fileSizeInBytes);

	if (result == K15_GUI_RESULT_SUCCESS &&
		fileSizeInBytes > 0)
	{
		kg_byte* tempIconBuffer = (kg_byte*)K15_GUI_MALLOC(fileSizeInBytes);

		if (!tempIconBuffer)
		{
			result = K15_GUI_RESULT_OUT_OF_MEMORY;
			fclose(fileHandle);
		}

		if (tempIconBuffer)
		{
			fread(tempIconBuffer, 1, fileSizeInBytes, fileHandle);
			fclose(fileHandle);

			result = K15_GUICreateIconResourceFromMemory(p_GUIResourceDatabase,	tempIconBuffer, 
				fileSizeInBytes, p_IconName);
		}

		K15_GUI_FREE(tempIconBuffer);
	}
#endif //K15_GUI_STRIP_STANDARD_IO

	return result;
}
/*********************************************************************************/
kg_result K15_GUICreateIconResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_IconFileDataBuffer, kg_u32 p_IconFileDataBufferSizeInBytes, const char* p_IconName)
{
	if (!p_GUIResourceDatabase || !p_IconFileDataBuffer || !p_IconName)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	kg_s32 pixelWidth = 0;
	kg_s32 pixelHeight = 0;
	kg_s32 numColorComponents = 0;
	kg_result result = K15_GUI_RESULT_SUCCESS;

	kg_byte* pixelDataMemory = stbi_load_from_memory((const kg_byte*)p_IconFileDataBuffer, 
		p_IconFileDataBufferSizeInBytes, &pixelWidth, &pixelHeight, &numColorComponents, 0);

	if (!pixelDataMemory)
		return K15_GUIConvertSTBIResult(stbi_failure_reason());

	result = K15_GUICreateIconResourceFromMemoryRaw(p_GUIResourceDatabase, pixelDataMemory, 
		pixelWidth, pixelHeight, numColorComponents, p_IconName);

	if (result != K15_GUI_RESULT_SUCCESS)
		K15_GUI_FREE(pixelDataMemory);

	return result;
}
/*********************************************************************************/
kg_result K15_GUICreateIconResourceFromMemoryRaw(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_IconPixelDataBuffer, kg_u32 p_PixelWidth, kg_u32 p_PixelHeight, 
	kg_u8 p_ColorComponents, const char* p_IconName)
{
	if (!p_GUIResourceDatabase || !p_IconPixelDataBuffer || p_PixelHeight == 0 ||
		p_PixelWidth == 0 || p_ColorComponents == 0 || p_ColorComponents > 4 ||
		!p_IconName)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	K15_GUIResourceTableEntry* tableEntry = 0;

	kg_result result = K15_GUICreateResourceTableEntry(p_GUIResourceDatabase, &tableEntry,
		p_IconName, K15_GUI_ICON_RESOURCE_TYPE);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto freeResources;

	K15_GUIIcon* guiIcon = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&guiIcon, sizeof(K15_GUIIcon));

	if (result != K15_GUI_RESULT_SUCCESS)
		goto freeResources;

	guiIcon->numColorComponents = p_ColorComponents;
	guiIcon->pixelData = p_IconPixelDataBuffer;
	guiIcon->pixelHeight = p_PixelHeight;
	guiIcon->pixelWidth = p_PixelWidth;

freeResources:
	if (result != K15_GUI_RESULT_SUCCESS)
		K15_GUIRemoveResourceTableEntryByName(p_GUIResourceDatabase, tableEntry->name);

	return result;
}
/*********************************************************************************/
kg_result K15_GUIBakeIconResources(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIIconSet** p_OutIconSet, const char* p_IconSetName)
{
	if (!p_GUIResourceDatabase || !p_OutIconSet || !p_IconSetName)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	kg_result result = K15_GUI_RESULT_SUCCESS;
	K15_ImageAtlas iconTextureAtlas = {};

	kia_u8 numColorComponents = 4;
	kia_result resultTA = K15_IACreateAtlas(&iconTextureAtlas, numColorComponents);

	if (resultTA != K15_IA_RESULT_SUCCESS)
	{
		result = K15_GUIConvertIAResult(resultTA);
		goto freeResources;
	}

	K15_GUIResourceTableEntry* tableEntry = 0;

	result = K15_GUICreateResourceTableEntry(p_GUIResourceDatabase, &tableEntry,
		p_IconSetName, K15_GUI_ICONSET_RESOURCE_TYPE);

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	K15_GUIIconSet* iconSet = 0;

	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&iconSet, sizeof(K15_GUIIconSet));

	if (result != K15_GUI_RESULT_SUCCESS)
		goto freeResources;

	K15_GUIResourceTableEntry* currentTableEntry = 0;
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 resourceMemorySize = p_GUIResourceDatabase->resourceMemorySizeInBytes;
	kg_u32 resourceMemoryPosition = 0;
	kg_u32 iconIndex = 0;

	while (resourceMemoryPosition < resourceMemorySize)
	{
		if (iconIndex >= K15_GUI_MAX_ICONS_PER_ICON_SET)
			break;

		currentTableEntry = (K15_GUIResourceTableEntry*)(resourceMemory + resourceMemoryPosition);

		if (currentTableEntry->type == K15_GUI_ICON_RESOURCE_TYPE)
		{
			K15_GUIIcon* icon =
				(K15_GUIIcon*)(resourceMemory + resourceMemoryPosition + sizeof(K15_GUIResourceTableEntry));
			
			kg_byte* pixelData = icon->pixelData;
			kg_u32 pixelHeight = icon->pixelHeight;
			kg_u32 pixelWidth = icon->pixelWidth;
			kg_u8 iconNumColorComponents = icon->numColorComponents;

			kg_u32 iconAtlasPosX = 0;
			kg_u32 iconAtlasPosY = 0;

			resultTA = K15_IAAddImageToAtlas(&iconTextureAtlas, pixelData, iconNumColorComponents,
				pixelWidth, pixelHeight, &iconAtlasPosX, &iconAtlasPosY);

			if (resultTA != K15_IA_RESULT_SUCCESS)
			{
				result = K15_GUIConvertIAResult(resultTA);
				goto freeResources;
			}

			K15_GUIIconMarker* iconMarker = iconSet->iconMarker + iconIndex;
			iconMarker->atlasClipRect.pixelPosLeft = iconAtlasPosX;
			iconMarker->atlasClipRect.pixelPosTop = iconAtlasPosY;
			iconMarker->atlasClipRect.pixelPosRight = iconAtlasPosX + pixelWidth;
			iconMarker->atlasClipRect.pixelPosBottom = iconAtlasPosY + pixelHeight;
			
			K15_GUI_MEMCPY(iconMarker->name, currentTableEntry->name, K15_GUI_MAX_RESOURCE_NAME_LENGTH);

			++iconIndex;
		}

		resourceMemoryPosition += currentTableEntry->sizeInBytes;
	}

	if (iconIndex == 0)
	{
		result = K15_GUI_RESULT_NO_ICONS;
		goto freeResources;
	}

	iconSet->numIconMarker = iconIndex;
	
	kg_u32 atlasPixelHeight = 0;
	kg_u32 atlasPixelWidth = 0;
	kg_u32 atlasPixelDataSizeInBytes = K15_IAGetAtlasPixelDataSizeInBytes(&iconTextureAtlas);
	kg_byte* atlasPixelData = K15_IAGetAtlasPixelData(&iconTextureAtlas, &atlasPixelWidth, &atlasPixelHeight);

	kg_byte* copyAtlasPixelData = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&copyAtlasPixelData, atlasPixelDataSizeInBytes);
	
	if (result != K15_GUI_RESULT_SUCCESS)
		goto freeResources;

	K15_GUI_MEMCPY(copyAtlasPixelData, atlasPixelData, atlasPixelDataSizeInBytes);

	iconSet->texture.numColorComponents = 4;
	iconSet->texture.pixelData = copyAtlasPixelData;
	iconSet->texture.pixelHeight = atlasPixelHeight;
	iconSet->texture.pixelWidth = atlasPixelWidth;

	*p_OutIconSet = iconSet;

freeResources:
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		K15_GUIRemoveResourceTableEntryByName(p_GUIResourceDatabase, tableEntry->name);
	}

	K15_IAFreeAtlas(&iconTextureAtlas);

	return result;
}
/*********************************************************************************/
static K15_GUIContextStyle K15_GUICreateDefaultStyle(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	K15_GUIContextStyle defaultStyle = {};

	K15_GUIFont* defaultFont = 0;
	kg_result result = K15_GUICreateFontResourceFromFile(p_GUIResourceDatabase, &defaultFont, 
		"Cousine-Regular.ttf", 12, "default_font");

// 	stbi_write_tga("bla.tga", defaultFont->texture.pixelWidth, defaultFont->texture.pixelHeight,
// 		defaultFont->texture.numColorComponents, defaultFont->texture.pixelData);

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
	defaultStyle.menuStyle.lowerBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuStyle.upperBackgroundColor = K15_GUI_COLOR_RGB(16, 16, 16);
	defaultStyle.menuStyle.lowerFocusedBackgroundColor = K15_GUI_COLOR_RGB(48, 48, 48);
	defaultStyle.menuStyle.upperFocusedBackgroundColor = K15_GUI_COLOR_RGB(96, 96, 96);
	defaultStyle.menuStyle.lowerHoveredBackgroundColor = K15_GUI_COLOR_RGB(16, 16, 16);
	defaultStyle.menuStyle.upperHoveredBackgroundColor = K15_GUI_COLOR_RGB(64, 64, 64);
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

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext, K15_GUIResourceDatabase* p_ContextResources,
	kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop, kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom, 
	kg_u32 p_InitFlags)
{
	kg_byte* guiMemory = (kg_byte*)malloc(K15_GUI_MIN_MEMORY_SIZE_IN_BYTES);

	if (!guiMemory)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	return K15_CreateGUIContextWithCustomMemory(p_OutGUIContext, p_ContextResources, 
		p_ClipPosLeft, p_ClipPosTop, p_ClipPosRight, p_ClipPosBottom, 
		guiMemory, K15_GUI_MIN_MEMORY_SIZE_IN_BYTES, p_InitFlags);
}
/*********************************************************************************/
kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext, 
	K15_GUIResourceDatabase* p_ContextResources, kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop,
	kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom, kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes, 
	kg_u32 p_InitFlags)
{
	if (!p_Memory || p_MemorySizeInBytes < K15_GUI_MIN_MEMORY_SIZE_IN_BYTES)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

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
	guiContext->style = K15_GUICreateDefaultStyle(p_ContextResources);
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
	K15_GUIContextStyle* style = &p_GUIContext->style;
	K15_GUICustomBeginToolBar(p_GUIContext, p_Identifier, &style->toolBarStyle);
}
/*********************************************************************************/
void K15_GUICustomBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier, 
	K15_GUIToolBarStyle* p_Style)
{

}
/*********************************************************************************/
kg_b8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY,
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier)
{
	K15_GUIContextStyle* style = &p_GUIContext->style;
	return K15_GUICustomBeginWindow(p_GUIContext, p_PosX, p_PosY, p_Width, p_Height, p_Title,
		p_Identifier, &style->windowStyle);
}
/*********************************************************************************/
kg_b8 K15_GUICustomBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY, 
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier, 
	K15_GUIWindowStyle* p_Style)
{
	return 0;
}
/*********************************************************************************/
kg_b8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier)
{
	return K15_GUICustomBeginMenu(p_GUIContext, p_MenuText, p_Identifier, &p_GUIContext->style.menuStyle);
}
/*********************************************************************************/
kg_b8 K15_GUICustomBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier,
	K15_GUIMenuStyle* p_Style)
{
	return 0;
}
/*********************************************************************************/
kg_b8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier)
{
	return K15_GUICustomMenuItem(p_GUIContext, p_ItemText, p_Identifier, &p_GUIContext->style.menuItemStyle);
}
/*********************************************************************************/
kg_b8 K15_GUICustomMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier,
	K15_GUIMenuItemStyle* p_Style)
{
	return 0;
}
/*********************************************************************************/
kg_b8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier)
{
	K15_GUIButtonStyle* defaultButtonStyle = &p_GUIContext->style.buttonStyle;
	return K15_GUICustomButton(p_GUIContext, p_ButtonText, p_Identifier, defaultButtonStyle);
}
/*********************************************************************************/
kg_b8 K15_GUICustomButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier,
	K15_GUIButtonStyle* p_Style)
{
	return 0;
}
/*********************************************************************************/
void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier)
{
	K15_GUICustomLabel(p_GUIContext, p_LabelText, p_Identifier, &p_GUIContext->style.labelStyle);
}
/*********************************************************************************/
void K15_GUICustomLabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier,
	K15_GUILabelStyle* p_Style)
{
	
}
/*********************************************************************************/
void K15_GUISeparator(K15_GUIContext* p_GUIContext)
{

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
void K15_GUIFinishFrame(K15_GUIContext* p_GUIContext)
{

}
/*********************************************************************************/
void K15_GUIPopLayout(K15_GUIContext* p_GUIContext)
{

}
/*********************************************************************************/
void K15_GUIConvertResultToMessage(kg_result p_Result, char** p_OutMessage, kg_u32 p_OutMessageBufferSizeInBytes)
{
	const char* errorMsg = 0;

	if (p_Result == K15_GUI_RESULT_SUCCESS)
		errorMsg = "Success";
	else if (p_Result == K15_GUI_RESULT_OUT_OF_MEMORY)
		errorMsg = "Out of memory";
	else if (p_Result == K15_GUI_RESULT_FONT_DATA_ERROR)
		errorMsg = "Font data error";
	else if (p_Result == K15_GUI_RESULT_NOT_SUPPORTED)
		errorMsg = "No supported";
	else if (p_Result == K15_GUI_RESULT_FILE_NOT_FOUND)
		errorMsg = "File not found";
	else if (p_Result == K15_GUI_RESULT_EMPTY_CLIP_RECT)
		errorMsg = "Empty clip rect";
	else if (p_Result == K15_GUI_RESULT_INVALID_ARGUMENTS)
		errorMsg = "Invalid arguments";
	else if (p_Result == K15_GUI_RESULT_OUT_OF_RANGE)
		errorMsg = "Out of range";
	else if (p_Result == K15_GUI_RESULT_NAME_ALREADY_IN_USE)
		errorMsg = "Name already in use";
	else if (p_Result == K15_GUI_RESULT_RESOURCE_NOT_FOUND)
		errorMsg = "Resource not found";
	else if (p_Result == K15_GUI_RESULT_IMAGE_DATA_ERROR)
		errorMsg = "Image data error";
	else if (p_Result == K15_GUI_RESULT_FILE_FORMAT_NOT_SUPPORTED)
		errorMsg = "File format not supported";
	else if (p_Result == K15_GUI_RESULT_TOO_MANY_ICONS)
		errorMsg = "Too many icons";

	if (errorMsg)
	{
		kg_u32 bytesToFill = K15_GUI_MIN(K15_GUI_STRLEN(errorMsg), p_OutMessageBufferSizeInBytes);
		K15_GUI_MEMCPY(*p_OutMessage, errorMsg, bytesToFill);
	}
}
/*********************************************************************************/
kg_result K15_GUIAddMouseInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIMouseInput p_MouseInput)
{
	if (!p_GUIContextEvents)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	
	if (p_GUIContextEvents->numBufferedMouseInputs == K15_GUI_MAX_BUFFERED_MOUSE_INPUTS)
		return K15_GUI_RESULT_OUT_OF_RANGE;

	kg_u32 mouseInputIndex = p_GUIContextEvents->numBufferedMouseInputs++;
	p_GUIContextEvents->bufferedMouseInput[mouseInputIndex] = p_MouseInput;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_result K15_GUIAddKeyboardInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIKeyboardInput p_KeyboardInput)
{
	if (!p_GUIContextEvents)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	if (p_GUIContextEvents->numBufferedKeyboardInputs == K15_GUI_MAX_BUFFERED_KEYBOARD_INPUTS)
		return K15_GUI_RESULT_OUT_OF_RANGE;

	kg_u32 keyInputIndex = p_GUIContextEvents->numBufferedKeyboardInputs++;
	p_GUIContextEvents->bufferedKeyboardInput[keyInputIndex] = p_KeyboardInput;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_result K15_GUIAddSystemEvent(K15_GUIContextEvents* p_GUIContextEvents, K15_GUISystemEvent p_SystemEvent)
{
	if (!p_GUIContextEvents)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	if (p_GUIContextEvents->numBufferedSystemEvents == K15_GUI_MAX_BUFFERED_SYSTEM_EVENTS)
		return K15_GUI_RESULT_OUT_OF_RANGE;

	kg_u32 systemEventIndex = p_GUIContextEvents->numBufferedSystemEvents++;
	p_GUIContextEvents->bufferedSystemEvents[systemEventIndex] = p_SystemEvent;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/

#endif //K15_GUI_IMPLEMENTATION
#endif //_K15_GUILayer_Context_h_
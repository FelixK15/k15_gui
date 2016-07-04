#ifndef _K15_GUILayer_Context_h_
#define _K15_GUILayer_Context_h_

#ifndef K15_GUI_STATIC
# define kg_def static
#else
# define kg_def extern
#endif //K15_GUI_STATIC

#define K15_GUI_MAX_LAYOUTS 20
#define K15_GUI_MAX_RESOURCE_NAME_LENGTH 64
#define K15_GUI_MAX_ICONS_PER_ICON_SET 64
#define K15_GUI_MAX_ELEMENT_PTR_PER_LAYOUT 128

#define K15_GUI_MAX_BUFFERED_MOUSE_INPUTS 16
#define K15_GUI_MAX_BUFFERED_KEYBOARD_INPUTS 16
#define K15_GUI_MAX_BUFFERED_SYSTEM_EVENTS 16
#define K15_GUI_ELEMENT_HASH_TABLE_SIZE 4096
#define K15_GUI_MAX_LAYOUTED_ELEMENTS 256
#define K15_GUI_MAX_GLYPH_RANGES 10

#define K15_GUI_TRUE 1
#define K15_GUI_FALSE 0

#define kg_size_kilo_bytes(n) (n*1024)
#define kg_size_mega_bytes(n) (n*1024*1024)
#define K15_GUI_DRAW_COMMAND_BUFFER_SIZE kg_size_kilo_bytes(5)
#define K15_GUI_MIN_MEMORY_SIZE_IN_BYTES sizeof(K15_GUIContext) + kg_size_kilo_bytes(10)
#define K15_GUI_DEFAULT_RESOURCE_DATABASE_MEMORY_SIZE kg_size_mega_bytes(5)

typedef unsigned long long kg_u64;
typedef unsigned int kg_u32;
typedef unsigned short kg_u16;
typedef unsigned char kg_u8;
typedef float kg_f32;

typedef unsigned int kg_color32;

typedef long long kg_s64;
typedef int kg_s32;
typedef short kg_s16;
typedef char kg_s8;

typedef unsigned char kg_byte;
typedef unsigned char kg_b8;

/*********************************************************************************/
typedef enum 
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
	K15_GUI_RESULT_NO_ICONS = 13,
	K15_GUI_RESULT_HASH_CONFLICT = 14,
	K15_GUI_RESULT_FRAME_NOT_FINISHED = 15,
	K15_GUI_RESULT_FRAME_NOT_STARTED = 16,
	K15_GUI_RESULT_ELEMENT_NOT_STARTED = 17,
	K15_GUI_RESULT_ELEMENT_NOT_FINISHED = 18,
	K15_GUI_RESULT_DRAW_COMMAND_FINISHED = 19,
	K15_GUI_RESULT_UNKNOWN_ERROR = 20
} kg_result;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_ELEMENT_CLIPPED = 0x001
} K15_GUIElementFlags;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_FONT_INCLUDE_LATIN_GLYPHS = 0x01,
	K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS = 0x02,
	K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS = 0x04,
	K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS = 0x08,

	K15_GUI_FONT_INCLUDE_ALL_GPYPS = K15_GUI_FONT_INCLUDE_LATIN_GLYPHS | K15_GUI_FONT_INCLUDE_CHINESE_GLYPHS | K15_GUI_FONT_INCLUDE_CYRILLIC_GLYPHS | K15_GUI_FONT_INCLUDE_KOREAN_GLYPHS
} K15_GUIFontInitFlags;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_CONVERT_TO_NDC = 0x01
} K15_GUIDrawCommandCreationFlags;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_CONTEXT_INSIDE_FRAME_FLAG = 0x01,
	K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG = 0x02,
	K15_GUI_CONTEXT_INSIDE_MENU_FLAG = 0x04
} K15_GUIContextFlags;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_MOUSE_BUTTON_PRESSED = 0,
	K15_GUI_MOUSE_BUTTON_RELEASED,
	K15_GUI_MOUSE_WHEEL_UP,
	K15_GUI_MOUSE_WHEEL_DOWN,
	K15_GUI_MOUSE_MOVED
} K15_GUIMouseInputType;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_MOUSE_BUTTON_LEFT = 0,
	K15_GUI_MOUSE_BUTTON_RIGHT,
	K15_GUI_MOUSE_BUTTON_MIDDLE,
	K15_GUI_MOUSE_BUTTON_SPECIAL1,
	K15_GUI_MOUSE_BUTTON_SPECIAL2
} K15_GUIMouseButtonType;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_CTRL_MODIFIER = 0x01,
	K15_GUI_L_ALT_MODIFIER = 0x02,
	K15_GIU_R_ALT_MODIFIER = 0x04,
	K15_GUI_SHIFT_MODIFIER = 0x08
} K15_GUIKeyboardModifierType;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_KEY_PRESSED = 0,
	K15_GUI_KEY_RELEASED,
	K15_GUI_TEXT_INPUT
} K15_GUIKeyboardInputType;
/*********************************************************************************/
typedef enum 
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
typedef enum 
{
	K15_GUI_WINDOW_RESIZED = 0,
	K15_GUI_SYSTEM_EVENT_COUNT
} K15_GUISystemEventType;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_FONT_RESOURCE_TYPE = 0,
	K15_GUI_ICON_RESOURCE_TYPE,
	K15_GUI_ICONSET_RESOURCE_TYPE
} K15_GUIResourceType;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_HORIZONTAL_LAYOUT_TYPE = 0,
	K15_GUI_VERTICAL_LAYOUT_TYPE,
	K15_GUI_STACKED_LAYOUT_TYPE
} K15_GUILayoutType;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_TOOLBAR_ELEMENT_TYPE = 0,
	K15_GUI_MENU_ELEMENT_TYPE,
	K15_GUI_MENU_ITEM_ELEMENT_TYPE,
	K15_GUI_BUTTON_ELEMENT_TYPE,
	K15_GUI_LAYOUT_ELEMENT_TYPE
} K15_GUIElementType;
/*********************************************************************************/
typedef struct 
{
	union
	{
		struct
		{
			kg_u16 x;
			kg_u16 y;
		} mousePos;

		kg_u32 mouseButton;
	} data;

	K15_GUIMouseInputType type;
} K15_GUIMouseInput;
/*********************************************************************************/
typedef struct 
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
typedef struct 
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
typedef struct 
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
typedef struct
{
	kg_s16 left;
	kg_s16 top;
	kg_s16 right;
	kg_s16 bottom;
} K15_GUIRect;
/*********************************************************************************/
typedef struct 
{
	kg_u16 numColorComponents;
	kg_u16 pixelWidth;
	kg_u16 pixelHeight;
	kg_byte* pixelData;
	kg_u64 userData;
} K15_GUITexture;
/*********************************************************************************/
typedef struct
{
	K15_GUIRect glyphRect;
	kg_u32 codepoint;
	kg_s32 leftSideBearing;
	kg_s32 advanceWidth;
} K15_GUIFontGlyph;
/*********************************************************************************/
typedef struct 
{
	K15_GUITexture texture;
	K15_GUIFontGlyph* glyphs;
	float scaleFactor;
	kg_u32 glyphRangeMask;
	kg_s32 fontSize;
	kg_s32 lineGap;
	kg_s32 ascent;
	kg_s32 descent;
	kg_u32 numGlyphs;
} K15_GUIFont;
/*********************************************************************************/
typedef struct 
{
	kg_byte* pixelData;
	kg_u32 pixelHeight;
	kg_u32 pixelWidth;
	kg_u32 numColorComponents;
} K15_GUIIcon;
/*********************************************************************************/
typedef struct 
{
	K15_GUIRect atlasClipRect;
	char name[K15_GUI_MAX_RESOURCE_NAME_LENGTH];
} K15_GUIIconMarker;
/*********************************************************************************/
typedef struct 
{
	K15_GUIIconMarker iconMarker[K15_GUI_MAX_ICONS_PER_ICON_SET];
	K15_GUITexture texture;
	kg_u32 numIconMarker;
} K15_GUIIconSet;
/*********************************************************************************/
typedef struct 
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
typedef struct 
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
/*******************a**************************************************************/
typedef struct 
{
	kg_color32 textColor;
	K15_GUIFont* font;
} K15_GUILabelStyle;
/*********************************************************************************/
typedef struct 
{
	kg_color32 lowerBackgroundColor;
	kg_color32 upperBackgroundColor;
	kg_u32 pixelHeight;
} K15_GUIToolBarStyle;
/*********************************************************************************/
typedef struct 
{
	K15_GUIWindowStyle windowStyle;
	K15_GUIButtonStyle buttonStyle;
	K15_GUIButtonStyle menuStyle;
	K15_GUIButtonStyle menuItemStyle;
	K15_GUILabelStyle labelStyle;
	K15_GUIToolBarStyle toolBarStyle;
} K15_GUIContextStyle;
/*********************************************************************************/
typedef struct 
{
	char name[K15_GUI_MAX_RESOURCE_NAME_LENGTH];
	kg_u32 sizeInBytes;
	K15_GUIResourceType type;
} K15_GUIResourceTableEntry;
/*********************************************************************************/
typedef struct 
{	
	K15_GUIResourceTableEntry* resourceTable;
	kg_byte* resourceMemory;
	kg_u32 resourceMemoryCapacityInBytes;
	kg_u32 resourceMemorySizeInBytes;
} K15_GUIResourceDatabase;
/*********************************************************************************/
typedef struct 
{
	kg_u32 from;
	kg_u32 to;
} K15_GUIGlyphRange;
/*********************************************************************************/
typedef enum
{
	K15_GUI_SOLID_COLOR = 0,
	K15_GUI_LINEAR_GRADIENT
} K15_GUIColorGradientType;
/*********************************************************************************/
typedef enum
{
	K15_GUI_DRAW_RECT_COMMAND = 0,
	K15_GUI_DRAW_CIRCLE_COMMAND,
	K15_GUI_DRAW_TEXT_COMMAND
} K15_GUIDrawCommandType;
/*********************************************************************************/
typedef struct
{
	K15_GUIColorGradientType type;
	kg_color32 from;
	kg_color32 to;
} K15_GUIColorGradient;
/*********************************************************************************/
typedef struct 
{
	K15_GUIDrawCommandType type;
	kg_u32 sizeInBytes;
} K15_GUIDrawCommand;
/*********************************************************************************/
typedef struct 
{
	kg_byte drawCommandBuffer[K15_GUI_DRAW_COMMAND_BUFFER_SIZE];
	kg_u32 bufferPosition;
	kg_u32 bufferCapacityInBytes;
	kg_u32 bufferSizeInBytes;
} K15_GUIDrawCommandBuffer;
/*********************************************************************************/
typedef struct 
{
	K15_GUIRect clipRect;
	K15_GUIElementType type;
	kg_u32 identifierHash;
	kg_u32 offsetNextElementInBytes;
	kg_u32 layoutIndex;
	kg_u8 flags;
} K15_GUIElement;
/*********************************************************************************/
typedef struct 
{
	K15_GUIElement* layoutedElements[K15_GUI_MAX_LAYOUTED_ELEMENTS];
	K15_GUILayoutType type;
	kg_u32 numElements;
} K15_GUILayoutData;
/*********************************************************************************/
typedef struct
{
	K15_GUIButtonStyle* buttonStyle;
	kg_u32 textLength;
} K15_GUIButtonData;
/*********************************************************************************/
typedef struct
{
	K15_GUIRect rect;
	K15_GUIColorGradient colorGradient;
} K15_GUIRectShapeData;
/*********************************************************************************/
typedef struct 
{
	kg_byte* memoryBuffer;
	kg_u32 memoryBufferSizeInBytes;
	kg_u32 memoryBufferCapacityInBytes;
} K15_GUIContextMemory;
/*********************************************************************************/
typedef struct 
{
	K15_GUIElement* elementHashTable[K15_GUI_ELEMENT_HASH_TABLE_SIZE];
	K15_GUIElement* layoutTable[K15_GUI_MAX_LAYOUTS];
	K15_GUIContextStyle style;
	K15_GUIContextEvents events;
	K15_GUIContextMemory memory;
	K15_GUIDrawCommandBuffer drawCmdBuffer;
	K15_GUIRect clipRect;
	K15_GUIResourceDatabase* resourceDatabase;
	kg_result lastResult;
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

kg_def kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext, K15_GUIResourceDatabase* p_ContextResources,
	kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop, kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom);

kg_def kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext,
	K15_GUIResourceDatabase* p_ContextResources, kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop,
	kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom, kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes);

//*****************RESOURCES******************//
kg_def kg_result K15_GUICreateResourceDatabase(K15_GUIResourceDatabase* p_GUIResourceDatabase);
kg_def kg_result K15_GUICreateResourceDatabaseWithCustomMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_DatabaseMemory, kg_u32 p_DatabaseMemorySizeInBytes);

kg_def kg_result K15_GUICreateFontResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, const char* p_FontFilePath, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags);

kg_def kg_result K15_GUICreateFontResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, kg_byte* p_TrueTypeFontBuffer, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags);

kg_def kg_result K15_GUICreateIconResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	const char* p_IconFilePath, const char* p_IconName);

kg_def kg_result K15_GUICreateIconResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_IconFileMemory, kg_u32 p_IconFileDataBufferSizeInBytes, const char* p_IconName);

kg_def kg_result K15_GUICreateIconResourceFromMemoryRaw(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_byte* p_IconPixelDataBuffer, kg_u32 p_PixelWidth, kg_u32 p_PixelHeight, 
	kg_u8 p_ColorComponents, const char* p_IconName);

kg_def kg_result K15_GUIBakeIconResources(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIIconSet** p_OutIconSet, const char* p_IconSetName);

kg_def kg_result K15_GUIGetFontResource(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, const char* p_FontName);

kg_def kg_result K15_GUIGetIconSetResource(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIIconSet** p_OutIconSet, const char* p_IconSetName);

//*****************CONTROLS******************//
kg_def void K15_GUIBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier);
kg_def void K15_GUICustomBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier, 
	K15_GUIToolBarStyle* p_Style);

kg_def kg_b8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY, 
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier);
kg_def kg_b8 K15_GUICustomBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY, 
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier, 
	K15_GUIWindowStyle* p_Style);

kg_def kg_b8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier);
kg_def kg_b8 K15_GUICustomBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier, 
	K15_GUIButtonStyle* p_Style);

kg_def kg_b8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier);
kg_def kg_b8 K15_GUICustomMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier, 
	K15_GUIButtonStyle* p_Style);

kg_def kg_b8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier);
kg_def kg_b8 K15_GUICustomButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier, 
	K15_GUIButtonStyle* p_Style);

kg_def void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier);
kg_def void K15_GUICustomLabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier, 
	K15_GUILabelStyle* p_Style);

kg_def void K15_GUISeparator(K15_GUIContext* p_GUIContext);

kg_def void K15_GUIEndWindow(K15_GUIContext* p_GUIContext);
kg_def void K15_GUIEndMenu(K15_GUIContext* p_GUIContext);
kg_def void K15_GUIEndToolBar(K15_GUIContext* p_GUIContext);

kg_def kg_result K15_GUIBeginFrame(K15_GUIContext* p_GUIContext);
kg_def kg_result K15_GUIFinishFrame(K15_GUIContext* p_GUIContext);

kg_def void K15_GUIPopLayout(K15_GUIContext* p_GUIContext);

kg_def kg_result K15_GUIGetLastResult(K15_GUIContext* p_GUIContext);
kg_def kg_u32 K15_GUIConvertResultToMessage(kg_result p_Result, char** p_OutMessage, kg_u32 p_OutMessageBufferSizeInBytes);

//*****************INPUT******************//
kg_def kg_result K15_GUIAddMouseInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIMouseInput p_MouseInput);
kg_def kg_result K15_GUIAddKeyboardInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIKeyboardInput p_KeyboardInput);
kg_def kg_result K15_GUIAddSystemEvent(K15_GUIContextEvents* p_GUIContextEvents, K15_GUISystemEvent p_SystemEvent);

//*****************RENDERING******************//
kg_def kg_u32 K15_GUICalculateDrawCommandBufferSizeInBytes(K15_GUIContext* p_GUIContext);
kg_def kg_b8 K15_GUIHasDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer);
kg_def void K15_GUINextDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer);
kg_def void K15_GUICopyDrawCommandBuffer(K15_GUIContext* p_GUIContext,
	K15_GUIDrawCommandBuffer* p_GUIDrawCommandBuffer);
kg_def kg_result K15_GUIGetDrawCommandData(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer, 
	K15_GUIDrawCommand* p_DrawCommand, void* p_Data, kg_u32 p_DataSize, kg_u32 p_OffsetInBytes);
kg_def kg_result K15_GUIGetDrawCommandDataRaw(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer,
	K15_GUIDrawCommand* p_DrawCommand, void** p_DataPtr, kg_u32 p_OffsetInBytes);

#ifdef K15_GUI_IMPLEMENTATION

void K15_GUICalculateTextRect(const char* p_Text, K15_GUIFont* p_Font, K15_GUIRect* p_OutRect);

#ifndef kg_internal
# define kg_internal static
#endif //kg_internal

#ifndef K15_GUI_SWAP
# define K15_GUI_SWAP(a, b) {a ^= b; b ^= a; a ^= b;}
#endif //K15_GUI_SWAP

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

#ifndef K15_GUI_MEMSET
# include <string.h>
# define K15_GUI_MEMSET memset
#endif //K15_GUI_MEMSEt

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

#ifndef K15_GUI_CLAMP
# define K15_GUI_CLAMP(v, min, max) ((v) < (min) ? (min) : (v) > (max) ? (max) : (v))
#endif //K15_GUI_CLAMP

#define K15_GUI_COLOR_RGBA(r,g,b,a) (((a)<< 24) | ((b) << 16) | ((g) << 8) | ((r) << 0))
#define K15_GUI_COLOR_RGB(r,g,b) K15_GUI_COLOR_RGBA(r,g,b,255)
#define K15_GUI_COLOR_BLACK K15_GUI_COLOR_RGB(0, 0, 0)
#define K15_GUI_COLOR_WHITE K15_GUI_COLOR_RGB(255, 255, 255)

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

//TEMP
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
kg_internal kg_result K15_GUIOpenFileForReading(const char* p_FilePath,
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
kg_internal kg_u32 K15_GUIGetGlyphCountForGlyphRanges(kg_u8 p_GlyphRangeFlags)
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
kg_internal kg_u32 K15_GUIGetGlyphRanges(kg_u8 p_GlyphRangeFlags, K15_GUIGlyphRange** p_OutGlyphRangeArray,
	kg_u32 p_GlyphRangeArraySize)
{
	kg_u32 glyphRangeIndex = 0;

#define K15_GUI_SET_GLYPH_RANGE(f, t) \
	if (glyphRangeIndex < p_GlyphRangeArraySize) \
	{ \
		(*p_OutGlyphRangeArray + glyphRangeIndex)->from = f; \
		(*p_OutGlyphRangeArray + glyphRangeIndex)->to = t; \
		glyphRangeIndex += 1; \
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
kg_internal kg_result K15_GUIConvertIAResult(kia_result p_ResultIA)
{
	if (p_ResultIA == K15_IA_RESULT_OUT_OF_MEMORY)
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	else if (p_ResultIA == K15_IA_RESULT_OUT_OF_RANGE)
		return K15_GUI_RESULT_OUT_OF_RANGE;
	else if (p_ResultIA == K15_IA_RESULT_INVALID_ARGUMENTS)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	return K15_GUI_RESULT_UNKNOWN_ERROR;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIConvertSTBIResult(const char* p_ResultSTBI)
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

	return K15_GUI_RESULT_UNKNOWN_ERROR;
}
/*********************************************************************************/
kg_def kg_result K15_GUICreateResourceDatabase(K15_GUIResourceDatabase* p_GUIResourceDatabase)
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
kg_def kg_result K15_GUICreateResourceDatabaseWithCustomMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
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
kg_def kg_result K15_GUICreateFontResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
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
kg_internal kg_b8 K15_GUIFitsIntoResourceTableMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	kg_u32 p_SizeInBytes)
{
	kg_u32 capacityResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemoryCapacityInBytes;
	kg_u32 sizeResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;

	return (capacityResourceMemoryInBytes >= sizeResourceMemoryInBytes + p_SizeInBytes);
}
/*********************************************************************************/
kg_internal kg_b8 K15_GUISearchResourceTableEntry(K15_GUIResourceDatabase* p_GUIResourceDatabase,
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
kg_internal kg_result K15_GUICreateResourceTableEntry(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIResourceTableEntry** p_TableEntryPtr, const char* p_Name, K15_GUIResourceType p_ResourceType)
{
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 sizeResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;

	if (!K15_GUIFitsIntoResourceTableMemory(p_GUIResourceDatabase, sizeof(K15_GUIResourceTableEntry)))
		return K15_GUI_RESULT_OUT_OF_MEMORY;

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
kg_internal kg_result K15_GUIGetResourceTableEntryMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIResourceTableEntry* p_TableEntry, void** p_MemoryPtr, kg_u32 p_SizeInBytes)
{
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 sizeResourceMemoryInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;

	if (!K15_GUIFitsIntoResourceTableMemory(p_GUIResourceDatabase, p_SizeInBytes))
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	p_TableEntry->sizeInBytes += p_SizeInBytes;

	*p_MemoryPtr = (resourceMemory + sizeResourceMemoryInBytes);
	p_GUIResourceDatabase->resourceMemorySizeInBytes += p_SizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIRemoveResourceTableEntryByName(K15_GUIResourceDatabase* p_GUIResourceDatabase,
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
				K15_GUI_MEMCPY(resourceMemory + resourceMemoryPosition,
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
kg_def kg_result K15_GUICreateFontResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, kg_byte* p_TrueTypeFontBuffer, kg_u8 p_FontSize, const char* p_FontName,
	kg_u8 p_GlyphRangeFlags)
{
	K15_GUIResourceTableEntry* tableEntry = 0;
	kg_s32 ascent = 0;
	kg_s32 descent = 0;
	kg_s32 lineGap = 0;
	kg_result result = K15_GUI_RESULT_SUCCESS;

	if (K15_GUISearchResourceTableEntry(p_GUIResourceDatabase, p_FontName, 0))
		return K15_GUI_RESULT_NAME_ALREADY_IN_USE;

	stbtt_fontinfo fontInfo = {0};
	int resultSTBTT = stbtt_InitFont(&fontInfo, p_TrueTypeFontBuffer, 0);

	if (resultSTBTT == 0)
		return K15_GUI_RESULT_FONT_DATA_ERROR;

	float scaleFac = stbtt_ScaleForPixelHeight(&fontInfo, (float)p_FontSize);

	stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);

	kg_u32 numGlyphs = K15_GUIGetGlyphCountForGlyphRanges(p_GlyphRangeFlags);

	K15_ImageAtlas textureAtlas = {0};
	kia_result taResult = K15_IACreateAtlas(&textureAtlas, numGlyphs);

	if (taResult != K15_IA_RESULT_SUCCESS)
	{
		result = K15_GUIConvertIAResult(taResult);
		goto functionEnd;
	}
	
	result = K15_GUICreateResourceTableEntry(p_GUIResourceDatabase, &tableEntry,
		p_FontName, K15_GUI_FONT_RESOURCE_TYPE);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_GUIFont* guiFont = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&guiFont, sizeof(K15_GUIFont));

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_GUIFontGlyph* guiFontGlyphs = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&guiFontGlyphs, sizeof(K15_GUIFontGlyph) * numGlyphs);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_GUIGlyphRange glyphRanges[K15_GUI_MAX_GLYPH_RANGES] = { 0 };
	K15_GUIGlyphRange* glyphRangesPtr = glyphRanges;

	kg_u32 glyphRangeArraySize = K15_GUIGetGlyphRanges(p_GlyphRangeFlags, &glyphRangesPtr, 
		K15_GUI_MAX_GLYPH_RANGES);

	kg_u32 glyphIndex = 0;

	for (kg_u32 glyphRangeIndex = 0;
		glyphRangeIndex < glyphRangeArraySize;
		++glyphRangeIndex)
	{
		K15_GUIGlyphRange* glyphRange = glyphRanges + glyphRangeIndex;

		kg_u32 startCodePoint = glyphRange->from;
		kg_u32 codepoint = glyphRange->from;
		kg_u32 endCodepoint = glyphRange->to;
		kg_u32 glyphArrayIndex = 0;

		while (codepoint < endCodepoint)
		{
			K15_GUIRect glyphRect = {0};
			
			kg_s32 glyphIndex = stbtt_FindGlyphIndex(&fontInfo, codepoint);

			kg_s32 glyphBitmapWidth = 0;
			kg_s32 glyphBitmapHeight = 0;

			kg_byte* glyphBitmap = stbtt_GetGlyphBitmap(&fontInfo, scaleFac, scaleFac, glyphIndex, 
				&glyphBitmapWidth, &glyphBitmapHeight, 0, 0);

			if (glyphBitmap && 
				glyphBitmapHeight > 0 && 
				glyphBitmapWidth > 0)
			{
				int glyphBitmapPosX = 0;
				int glyphBitmapPosY = 0;

				taResult = K15_IAAddImageToAtlas(&textureAtlas, KIA_PIXEL_FORMAT_R8, 
					glyphBitmap, glyphBitmapWidth, glyphBitmapHeight, 
					&glyphBitmapPosX, &glyphBitmapPosY);

				kg_s32 leftSideBearing = 0;
				kg_s32 advanceWidth = 0;

				stbtt_GetGlyphHMetrics(&fontInfo, glyphIndex, &advanceWidth, &leftSideBearing);

				glyphRect.left = glyphBitmapPosX;
				glyphRect.top = glyphBitmapPosY;
				glyphRect.right = glyphBitmapPosX + glyphBitmapWidth;
				glyphRect.bottom = glyphBitmapPosY + glyphBitmapHeight;

				if (taResult != K15_IA_RESULT_SUCCESS)
				{
					result = K15_GUIConvertIAResult(taResult);
					goto functionEnd;
				}

				K15_GUIFontGlyph* fontGlyph = guiFontGlyphs + (codepoint - startCodePoint);
				fontGlyph->codepoint = codepoint;
				fontGlyph->glyphRect = glyphRect;
				fontGlyph->leftSideBearing = (kg_s32)((float)leftSideBearing * scaleFac);
				fontGlyph->advanceWidth = (kg_s32)((float)advanceWidth * scaleFac);
				
				glyphArrayIndex += 1;
			}

			codepoint += 1;
		}
	}

	int textureWidth = 0;
	int textureHeight = 0;
	unsigned char* texturePixelData = 0;

	kg_u32 texturePixelDataSizeInBytes = K15_IACalculateAtlasPixelDataSizeInBytes(&textureAtlas, 
		KIA_PIXEL_FORMAT_R8);

	void* copyTexturePixelDataMemory = 0;

	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry, &copyTexturePixelDataMemory,
		texturePixelDataSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_IABakeImageAtlasIntoPixelBuffer(&textureAtlas, KIA_PIXEL_FORMAT_R8, copyTexturePixelDataMemory,
		&textureWidth, &textureHeight);

	guiFont->texture.pixelHeight = textureHeight;
	guiFont->texture.pixelWidth = textureWidth;
	guiFont->texture.pixelData = (kg_byte*)copyTexturePixelDataMemory;
	guiFont->texture.numColorComponents = 1;
	guiFont->texture.userData = 0;

functionEnd:
	if (result == K15_IA_RESULT_SUCCESS)
	{
		guiFont->glyphRangeMask = p_GlyphRangeFlags;
		guiFont->fontSize = p_FontSize;
		guiFont->lineGap = lineGap;
		guiFont->ascent = ascent;
		guiFont->descent = descent;
		guiFont->scaleFactor = scaleFac;
		guiFont->numGlyphs = numGlyphs;
		guiFont->glyphs = guiFontGlyphs;

		*p_OutFont = guiFont;
	}
	else
	{
		K15_GUIRemoveResourceTableEntryByName(p_GUIResourceDatabase, tableEntry->name);
	}

	K15_IAFreeAtlas(&textureAtlas);

	return result;
}
/*********************************************************************************/
kg_def kg_result K15_GUICreateIconResourceFromFile(K15_GUIResourceDatabase* p_GUIResourceDatabase,
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
kg_def kg_result K15_GUICreateIconResourceFromMemory(K15_GUIResourceDatabase* p_GUIResourceDatabase,
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
kg_def kg_result K15_GUICreateIconResourceFromMemoryRaw(K15_GUIResourceDatabase* p_GUIResourceDatabase,
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
		goto functionEnd;

	K15_GUIIcon* guiIcon = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&guiIcon, sizeof(K15_GUIIcon));

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	guiIcon->numColorComponents = p_ColorComponents;
	guiIcon->pixelData = p_IconPixelDataBuffer;
	guiIcon->pixelHeight = p_PixelHeight;
	guiIcon->pixelWidth = p_PixelWidth;

functionEnd:
	if (result != K15_GUI_RESULT_SUCCESS)
		K15_GUIRemoveResourceTableEntryByName(p_GUIResourceDatabase, tableEntry->name);

	return result;
}
/*********************************************************************************/
kg_internal kg_u32 K15_GUIGetNumIconResources(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	K15_GUIResourceTableEntry* currentTableEntry = 0;
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 resourceMemorySize = p_GUIResourceDatabase->resourceMemorySizeInBytes;
	kg_u32 resourceMemoryPosition = 0;
	kg_u32 numIcons = 0;

	while (resourceMemoryPosition < resourceMemorySize)
	{
		if (numIcons >= K15_GUI_MAX_ICONS_PER_ICON_SET)
			break;

		currentTableEntry = (K15_GUIResourceTableEntry*)(resourceMemory + resourceMemoryPosition);

		if (currentTableEntry->type == K15_GUI_ICON_RESOURCE_TYPE)
			++numIcons;

		resourceMemoryPosition += currentTableEntry->sizeInBytes;
	}

	return numIcons;
}
/*********************************************************************************/
kg_def kg_result K15_GUIBakeIconResources(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIIconSet** p_OutIconSet, const char* p_IconSetName)
{
	if (!p_GUIResourceDatabase || !p_OutIconSet || !p_IconSetName)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	kg_u32 numIcons = K15_GUIGetNumIconResources(p_GUIResourceDatabase);

	if (numIcons == 0)
		return K15_GUI_RESULT_NO_ICONS;

	K15_ImageAtlas iconTextureAtlas = {0};
	kg_result result = K15_GUI_RESULT_SUCCESS;
	kia_result resultTA = K15_IACreateAtlas(&iconTextureAtlas, numIcons);

	if (resultTA != K15_IA_RESULT_SUCCESS)
	{
		result = K15_GUIConvertIAResult(resultTA);
		goto functionEnd;
	}

	K15_GUIResourceTableEntry* tableEntry = 0;

	result = K15_GUICreateResourceTableEntry(p_GUIResourceDatabase, &tableEntry,
		p_IconSetName, K15_GUI_ICONSET_RESOURCE_TYPE);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_GUIIconSet* iconSet = 0;

	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&iconSet, sizeof(K15_GUIIconSet));

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

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

			int iconAtlasPosX = 0;
			int iconAtlasPosY = 0;

			resultTA = K15_IAAddImageToAtlas(&iconTextureAtlas, (K15_IAPixelFormat)iconNumColorComponents,
				pixelData, pixelWidth, pixelHeight, &iconAtlasPosX, &iconAtlasPosY);

			if (resultTA != K15_IA_RESULT_SUCCESS)
			{
				result = K15_GUIConvertIAResult(resultTA);
				goto functionEnd;
			}

			K15_GUIIconMarker* iconMarker = iconSet->iconMarker + iconIndex;
			iconMarker->atlasClipRect.left = iconAtlasPosX;
			iconMarker->atlasClipRect.top = iconAtlasPosY;
			iconMarker->atlasClipRect.right = iconAtlasPosX + pixelWidth;
			iconMarker->atlasClipRect.bottom = iconAtlasPosY + pixelHeight;
			
			K15_GUI_MEMCPY(iconMarker->name, currentTableEntry->name, K15_GUI_MAX_RESOURCE_NAME_LENGTH);

			++iconIndex;
		}

		resourceMemoryPosition += currentTableEntry->sizeInBytes;
	}

	if (iconIndex == 0)
	{
		result = K15_GUI_RESULT_NO_ICONS;
		goto functionEnd;
	}

	iconSet->numIconMarker = iconIndex;
	
	int atlasPixelHeight = 0;
	int atlasPixelWidth = 0;
	kg_u32 atlasPixelDataSizeInBytes = K15_IACalculateAtlasPixelDataSizeInBytes(&iconTextureAtlas, 
		KIA_PIXEL_FORMAT_R8G8B8A8);
	
	kg_byte* copyAtlasPixelData = 0;
	result = K15_GUIGetResourceTableEntryMemory(p_GUIResourceDatabase, tableEntry,
		(void**)&copyAtlasPixelData, atlasPixelDataSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_IABakeImageAtlasIntoPixelBuffer(&iconTextureAtlas, KIA_PIXEL_FORMAT_R8G8B8A8, copyAtlasPixelData,
		&atlasPixelHeight, &atlasPixelWidth);

	iconSet->texture.numColorComponents = 4;
	iconSet->texture.pixelData = copyAtlasPixelData;
	iconSet->texture.pixelHeight = atlasPixelHeight;
	iconSet->texture.pixelWidth = atlasPixelWidth;

	*p_OutIconSet = iconSet;

functionEnd:
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		K15_GUIRemoveResourceTableEntryByName(p_GUIResourceDatabase, tableEntry->name);
	}

	K15_IAFreeAtlas(&iconTextureAtlas);

	return result;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIFindResourceTableEntry(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	void** p_OutMemory, const char* p_ResourceName, K15_GUIResourceType p_ResourceType)
{
	if (!p_GUIResourceDatabase || !p_OutMemory || !p_ResourceName)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	K15_GUIResourceTableEntry* tableEntry = 0;
	kg_byte* resourceMemory = p_GUIResourceDatabase->resourceMemory;
	kg_u32 resourceMemorySizeInBytes = p_GUIResourceDatabase->resourceMemorySizeInBytes;
	kg_u32 resourceMemoryPosition = 0;

	while (resourceMemoryPosition < resourceMemorySizeInBytes)
	{
		tableEntry = (K15_GUIResourceTableEntry*)(resourceMemory + resourceMemoryPosition);

		if (tableEntry->type == p_ResourceType &&
			K15_GUI_STRCMP(p_ResourceName, tableEntry->name) == 0)
		{
			*p_OutMemory = (void*)(resourceMemory + resourceMemoryPosition + sizeof(K15_GUIResourceTableEntry));
			return K15_GUI_RESULT_SUCCESS;
		}
	}	

	return K15_GUI_RESULT_RESOURCE_NOT_FOUND;
}
/*********************************************************************************/
kg_def kg_result K15_GUIGetFontResource(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIFont** p_OutFont, const char* p_FontName)
{
	return K15_GUIFindResourceTableEntry(p_GUIResourceDatabase, (void**)p_OutFont,
		p_FontName, K15_GUI_FONT_RESOURCE_TYPE);
}
/*********************************************************************************/
kg_def kg_result K15_GUIGetIconSetResource(K15_GUIResourceDatabase* p_GUIResourceDatabase,
	K15_GUIIconSet** p_OutIconSet, const char* p_IconSetName)
{
	return K15_GUIFindResourceTableEntry(p_GUIResourceDatabase, (void**)p_OutIconSet,
		p_IconSetName, K15_GUI_ICONSET_RESOURCE_TYPE);
}
/*********************************************************************************/
kg_internal K15_GUIContextStyle K15_GUICreateDefaultStyle(K15_GUIResourceDatabase* p_GUIResourceDatabase)
{
	K15_GUIContextStyle defaultStyle = {0};

	K15_GUIFont* defaultFont = 0;
	kg_result result = K15_GUICreateFontResourceFromFile(p_GUIResourceDatabase, &defaultFont, 
		"Cousine-Regular.ttf", 24, "default_font", K15_GUI_FONT_INCLUDE_LATIN_GLYPHS);

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
	defaultStyle.menuStyle.textColor = K15_GUI_COLOR_BLACK;
	defaultStyle.menuStyle.verticalPixelPadding = 2;
	defaultStyle.menuStyle.horizontalPixelPadding = 8;

	//Menu Item Style
	defaultStyle.menuItemStyle.font = defaultFont;
	defaultStyle.menuItemStyle.lowerBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuItemStyle.upperBackgroundColor = K15_GUI_COLOR_RGB(128, 128, 128);
	defaultStyle.menuItemStyle.textColor = K15_GUI_COLOR_BLACK;
	defaultStyle.menuItemStyle.verticalPixelPadding = 2;
	defaultStyle.menuItemStyle.horizontalPixelPadding = 8;

	return defaultStyle;
}
/*********************************************************************************/
kg_internal void K15_GUIHandleMouseInput(K15_GUIContextMemory* p_ContextMemory, kg_u32 p_NumMouseEvents,
	K15_GUIMouseInput* p_MouseEvents, kg_u16* p_MousePosInOutX, kg_u16* p_MousePosInOutY)
{
	kg_u32 memorySize = p_ContextMemory->memoryBufferSizeInBytes;
	kg_byte* memory = p_ContextMemory->memoryBuffer;

	kg_u32 memoryPosition = 0;

	K15_GUIElement* element = 0;

	while (memoryPosition < memorySize)
	{
		element = (K15_GUIElement*)(memory + memoryPosition);
		memoryPosition += element->offsetNextElementInBytes;
	}

}
/*********************************************************************************/
kg_internal void K15_GUIHandleKeyboardInput(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	
}
/*********************************************************************************/
kg_internal void K15_GUIHandleSystemEvents(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	
}
/*********************************************************************************/
kg_internal void K15_GUIHandleInput(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_GUIContextEvents)
{
	kg_u16 mousePosX = p_GUIContextEvents->mousePosX;
	kg_u16 mousePosY = p_GUIContextEvents->mousePosY;

// 	K15_GUIHandleMouseInput(p_Memory, p_GUIContextEvents->numBufferedMouseInputs,
// 		p_GUIContextEvents->bufferedMouseInput, &p_GUIContextEvents->mousePosX,
// 		&p_GUIContextEvents->mousePosY);
// 
// 	K15_GUIHandleKeyboardInput(p_Memory, p_GUIContextEvents->numBufferedKeyboardInputs,
// 		p_GUIContextEvents->bufferedKeyboardInput);
// 
// 	K15_GUIHandleSystemEvents(p_Memory, p_GUIContextEvents->numBufferedSystemEvents,
// 		p_GUIContextEvents->numBufferedSystemEvents);
}
/*********************************************************************************/


/*********************************************************************************/
kg_internal kg_result K15_GUIValidateClipRect(K15_GUIRect* p_ClipRect)
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
kg_internal kg_result K15_GUIReserveMemoryChunk(K15_GUIContextMemory* p_GUIContextMemory,
	void** p_MemoryChunkPtr, kg_u32 p_MemoryChunkSizeInBytes)
{
	kg_u32 memorySize = p_GUIContextMemory->memoryBufferSizeInBytes;
	kg_u32 memoryCapacity = p_GUIContextMemory->memoryBufferCapacityInBytes;
	kg_byte* memoryBuffer = p_GUIContextMemory->memoryBuffer;

	if (memorySize + p_MemoryChunkSizeInBytes > memoryCapacity)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	*p_MemoryChunkPtr = (memoryBuffer + memorySize);
	p_GUIContextMemory->memoryBufferSizeInBytes = memorySize + p_MemoryChunkSizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIAddElementData(K15_GUIContextMemory* p_GUIContextMemory,
	K15_GUIElement* p_GUIElement, void* p_Data, kg_u32 p_DataSizeInBytes)
{
	void* memoryBuffer = 0;
	kg_result result = K15_GUIReserveMemoryChunk(p_GUIContextMemory, &memoryBuffer, p_DataSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	K15_GUI_MEMCPY(memoryBuffer, p_Data, p_DataSizeInBytes);

	p_GUIElement->offsetNextElementInBytes += p_DataSizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIGetElementDataRaw(K15_GUIContextMemory* p_GUIContextMemory,
	K15_GUIElement* p_GUIElement, void** p_OutData, kg_u32 p_OffsetInBytes)
{
	kg_u32 ptrDiff = (kg_u32)((kg_u64)p_GUIElement - (kg_u64)p_GUIContextMemory->memoryBuffer);
	kg_u32 totalOffsetInBytes = p_OffsetInBytes + ptrDiff + sizeof(K15_GUIElement);

	if (p_GUIContextMemory->memoryBufferSizeInBytes < totalOffsetInBytes)
		return K15_GUI_RESULT_OUT_OF_RANGE;

	*p_OutData = p_GUIContextMemory->memoryBuffer + totalOffsetInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIGetElementData(K15_GUIContextMemory* p_GUIContextMemory,
	K15_GUIElement* p_GUIElement, void* p_OutData, kg_u32 p_DataSizeInBytes, kg_u32 p_OffsetInBytes)
{
	kg_u32 ptrDiff = (kg_u32)((kg_u64)p_GUIElement - (kg_u64)p_GUIContextMemory->memoryBuffer);
	kg_u32 totalOffsetInBytes = p_OffsetInBytes + ptrDiff + sizeof(K15_GUIElement);

	if (p_GUIContextMemory->memoryBufferSizeInBytes < totalOffsetInBytes + p_DataSizeInBytes)
		return K15_GUI_RESULT_OUT_OF_RANGE;

	K15_GUI_MEMCPY(p_OutData, p_GUIContextMemory->memoryBuffer + totalOffsetInBytes, p_DataSizeInBytes);

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_def kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext, K15_GUIResourceDatabase* p_ContextResources,
	kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop, kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom)
{
	kg_byte* guiMemory = (kg_byte*)malloc(K15_GUI_MIN_MEMORY_SIZE_IN_BYTES);

	if (!guiMemory)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	return K15_CreateGUIContextWithCustomMemory(p_OutGUIContext, p_ContextResources, 
		p_ClipPosLeft, p_ClipPosTop, p_ClipPosRight, p_ClipPosBottom, 
		guiMemory, K15_GUI_MIN_MEMORY_SIZE_IN_BYTES);
}
/*********************************************************************************/
kg_def kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext, 
	K15_GUIResourceDatabase* p_ContextResources, kg_s16 p_ClipPosLeft, kg_s16 p_ClipPosTop,
	kg_s16 p_ClipPosRight, kg_s16 p_ClipPosBottom, kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes)
{
	if (!p_Memory || p_MemorySizeInBytes < K15_GUI_MIN_MEMORY_SIZE_IN_BYTES)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	K15_GUIRect clipRect = {0};
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
	K15_GUI_MEMSET(guiMemory, 0, guiMemorySizeInBytes);

	guiContext->memory.memoryBuffer = guiMemory;
	guiContext->memory.memoryBufferCapacityInBytes = p_MemorySizeInBytes;
	guiContext->memory.memoryBufferSizeInBytes = 0;
	guiContext->memoryBufferSizeInBytes = guiMemorySizeInBytes;
	guiContext->memoryBufferCapacityInBytes = guiMemorySizeInBytes;
	guiContext->drawCmdBuffer.bufferCapacityInBytes = K15_GUI_DRAW_COMMAND_BUFFER_SIZE;
	guiContext->drawCmdBuffer.bufferSizeInBytes = 0;
	guiContext->focusedElementIdHash = 0;
	guiContext->hoveredElementIdHash = 0;
	guiContext->clickedElementIdHash = 0;
	guiContext->mouseDownElementIdHash = 0;
	guiContext->layoutIndex = 0;
	guiContext->numLayouts = 0;
	guiContext->numMenus = 0;
	guiContext->lastResult = K15_GUI_RESULT_SUCCESS;
	guiContext->style = K15_GUICreateDefaultStyle(p_ContextResources);
	guiContext->resourceDatabase = p_ContextResources;
	guiContext->activatedElementIdHash = 0;
	guiContext->events.numBufferedKeyboardInputs = 0;
	guiContext->events.numBufferedMouseInputs = 0;
	guiContext->flagMask = 0;
	guiContext->clipRect = clipRect;

	K15_GUI_MEMSET(guiContext->elementHashTable, 0, sizeof(guiContext->elementHashTable));

	//assign newly created gui context
	*p_OutGUIContext = *guiContext;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_def void K15_GUIBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier)
{
	K15_GUIContextStyle* style = &p_GUIContext->style;
	K15_GUICustomBeginToolBar(p_GUIContext, p_Identifier, &style->toolBarStyle);
}
/*********************************************************************************/
kg_internal kg_u32 K15_GUICreateHash(const char* p_String, kg_u32 p_StringLength)
{
	kg_u32 hash = 0;

	for (kg_u32 i = 0; i < p_StringLength; i++)
		hash = 33 * hash + 720 + p_String[i];

	return hash;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIPerformClipping(K15_GUIRect* p_ClipRectToClip, K15_GUIRect* p_ClipRect)
{
	p_ClipRectToClip->left = K15_GUI_MIN(p_ClipRectToClip->left, p_ClipRect->left);
	p_ClipRectToClip->top = K15_GUI_MIN(p_ClipRectToClip->top, p_ClipRect->top);
	p_ClipRectToClip->right = K15_GUI_MIN(p_ClipRectToClip->right, p_ClipRect->right);
	p_ClipRectToClip->bottom = K15_GUI_MIN(p_ClipRectToClip->bottom, p_ClipRect->bottom);

	return K15_GUIValidateClipRect(p_ClipRectToClip);
}
/*********************************************************************************/
kg_internal K15_GUIRect K15_GUIGetTopMostClipRect(K15_GUIContext* p_GUIContext)
{
	if (p_GUIContext->numLayouts == 0)
		return p_GUIContext->clipRect;

	kg_u32 layoutIndex = p_GUIContext->numLayouts - 1;
	K15_GUIElement* layoutElement = p_GUIContext->layoutTable[layoutIndex];

	return layoutElement->clipRect;
}
/*********************************************************************************/
kg_internal K15_GUIElement* K15_GUIGetTopLayoutElement(K15_GUIContext* p_GUIContext)
{
	if (!p_GUIContext)
		return 0;

	kg_u32 layoutIndex = p_GUIContext->numLayouts;

	if (layoutIndex == 0)
		return 0;

	return p_GUIContext->layoutTable[layoutIndex - 1];
}
/*********************************************************************************/
kg_internal kg_result K15_GUIRegisterUnidentifiedElement(K15_GUIContext* p_GUIContext,
	K15_GUIElement** p_GUIElementPtr, K15_GUIElementType p_ElementType, K15_GUIRect* p_ClipRect)
{
	if ((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_FRAME_FLAG) == 0)
		return K15_GUI_RESULT_FRAME_NOT_STARTED;

	K15_GUIContextMemory* guiContextMemory = &p_GUIContext->memory;

	K15_GUIElement* element = 0;
	kg_result result = K15_GUIReserveMemoryChunk(guiContextMemory, (void**)&element, sizeof(K15_GUIElement));

	element->type = p_ElementType;
	element->identifierHash = (~0);
	element->clipRect = *p_ClipRect;
	element->layoutIndex = p_GUIContext->layoutIndex;
	element->offsetNextElementInBytes = sizeof(K15_GUIElement);

	K15_GUIElement* topLayout = K15_GUIGetTopLayoutElement(p_GUIContext);

	if (topLayout)
	{
		K15_GUILayoutData* layoutData = 0;
		result = K15_GUIGetElementDataRaw(guiContextMemory, topLayout, &layoutData, 0);
	
		if (result != K15_GUI_RESULT_SUCCESS)
			return result;

		if (layoutData->numElements == K15_GUI_MAX_ELEMENT_PTR_PER_LAYOUT)
			return K15_GUI_RESULT_OUT_OF_MEMORY;

		kg_u32 elementIndex = layoutData->numElements++;
		layoutData->layoutedElements[elementIndex] = element;
	}

	if (p_GUIElementPtr)
		*p_GUIElementPtr = element;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIRegisterIdentifiedElement(K15_GUIContext* p_GUIContext, 
	K15_GUIElement** p_GUIElementPtr, K15_GUIElementType p_ElementType, const char* p_Identifier, 
	K15_GUIRect* p_ClipRect)
{
	if ((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_FRAME_FLAG) == 0)
		return K15_GUI_RESULT_FRAME_NOT_STARTED;

	K15_GUIElement** guiElementHashTable = p_GUIContext->elementHashTable;

	kg_u32 identifierLength = (kg_u32)K15_GUI_STRLEN(p_Identifier);
	kg_u32 identiferHash = K15_GUICreateHash(p_Identifier, identifierLength);
	identiferHash %= K15_GUI_ELEMENT_HASH_TABLE_SIZE;

	if (guiElementHashTable[identiferHash])
		return K15_GUI_RESULT_HASH_CONFLICT;

	K15_GUIElement* element = 0;
	kg_result result = K15_GUIRegisterUnidentifiedElement(p_GUIContext, &element, p_ElementType, p_ClipRect);

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	element->type = p_ElementType;
	element->identifierHash = identiferHash;
	element->clipRect = *p_ClipRect;
	element->layoutIndex = p_GUIContext->layoutIndex;
	element->offsetNextElementInBytes = sizeof(K15_GUIElement);

	guiElementHashTable[identiferHash] = element;

	*p_GUIElementPtr = element;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIAddDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer,
	K15_GUIDrawCommand** p_OutDrawCommand, K15_GUIDrawCommandType p_DrawCommandType)
{
	K15_GUIDrawCommand drawCmd;
	drawCmd.type = p_DrawCommandType;
	drawCmd.sizeInBytes = 0;

	kg_result result = K15_GUI_RESULT_SUCCESS;
	kg_u32 drawCmdSizeInBytes = sizeof(drawCmd);

	kg_u32 drawCmdBufferSizeInBytes = p_DrawCommandBuffer->bufferSizeInBytes;
	kg_u32 drawCmdBufferCapacityInBytes = p_DrawCommandBuffer->bufferCapacityInBytes;
	kg_u32 drawCmdBufferNewSizeInBytes = drawCmdBufferSizeInBytes + drawCmdSizeInBytes;
	kg_byte* drawCmdBuffer = p_DrawCommandBuffer->drawCommandBuffer;

	if (drawCmdBufferNewSizeInBytes > drawCmdBufferCapacityInBytes)
	{
		result = K15_GUI_RESULT_OUT_OF_MEMORY;
		goto functionEnd;
	}

	p_DrawCommandBuffer->bufferSizeInBytes = drawCmdBufferNewSizeInBytes;
	
	K15_GUI_MEMCPY(drawCmdBuffer + drawCmdBufferSizeInBytes, &drawCmd, sizeof(drawCmd));
	
	if (p_OutDrawCommand)
		*p_OutDrawCommand = (K15_GUIDrawCommand*)(drawCmdBuffer + drawCmdBufferSizeInBytes);

functionEnd:
	return result;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIAddDrawCommandData(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer,
	K15_GUIDrawCommand* p_DrawCommand, void* p_Data, kg_u32 p_DataSizeInBytes)
{
	if (!p_DrawCommandBuffer || !p_DrawCommand || !p_Data || p_DataSizeInBytes == 0)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	kg_result result = K15_GUI_RESULT_SUCCESS;

	if ((p_DrawCommandBuffer->bufferCapacityInBytes - p_DrawCommandBuffer->bufferSizeInBytes) < p_DataSizeInBytes)
	{
		result = K15_GUI_RESULT_OUT_OF_MEMORY;
		goto functionEnd;
	}

	kg_u32 drawCommandSizeInBytes = sizeof(K15_GUIDrawCommand) + p_DrawCommand->sizeInBytes;
	kg_u64 drawCommandAddress = (kg_u64)p_DrawCommand;
	kg_u64 drawCommandBufferEndAddress = (kg_u64)p_DrawCommandBuffer->drawCommandBuffer + p_DrawCommandBuffer->bufferSizeInBytes;

	if (drawCommandBufferEndAddress - drawCommandAddress > drawCommandSizeInBytes)
	{
		result = K15_GUI_RESULT_DRAW_COMMAND_FINISHED;
		goto functionEnd;
	}

	kg_byte* bufferPosition = p_DrawCommandBuffer->drawCommandBuffer + p_DrawCommandBuffer->bufferSizeInBytes;

	K15_GUI_MEMCPY(bufferPosition, p_Data, p_DataSizeInBytes);

	p_DrawCommandBuffer->bufferSizeInBytes += p_DataSizeInBytes;
	p_DrawCommand->sizeInBytes += p_DataSizeInBytes;

functionEnd:
	return result;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIAddRectShapeDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer,
	K15_GUIRect* p_ClipRect, K15_GUIColorGradient p_Gradient)
{
	K15_GUIRectShapeData shapeData = { 0 };
	shapeData.rect = *p_ClipRect;
	shapeData.colorGradient = p_Gradient;

	K15_GUIDrawCommand* drawCommand = 0;
	kg_result result = K15_GUIAddDrawCommand(p_DrawCommandBuffer, &drawCommand, K15_GUI_DRAW_RECT_COMMAND);

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	return K15_GUIAddDrawCommandData(p_DrawCommandBuffer, drawCommand, &shapeData, sizeof(shapeData));
}
/*********************************************************************************/
kg_internal K15_GUIColorGradient K15_GUICreateLinearColorGradiant(kg_color32 p_From, kg_color32 p_To)
{
	K15_GUIColorGradient lerpGradient;
	lerpGradient.type = K15_GUI_LINEAR_GRADIENT;
	lerpGradient.from = p_From;
	lerpGradient.to = p_To;

	return lerpGradient;
}
/*********************************************************************************/
kg_internal void K15_GUISetLastResult(kg_result* p_ResultOut, kg_result p_Result)
{
	if (*p_ResultOut == K15_GUI_RESULT_SUCCESS)
		*p_ResultOut = p_Result;
}
/*********************************************************************************/
kg_internal kg_result K15_GUIPushLayout(K15_GUIContext* p_GUIContext, K15_GUILayoutType p_LayoutType,
	K15_GUIRect* p_ClipRect)
{
	if (!p_GUIContext || !p_ClipRect)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	if (p_GUIContext->numLayouts == K15_GUI_MAX_LAYOUTS)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	K15_GUIContextMemory* contextMemory = &p_GUIContext->memory;

	K15_GUIElement* layoutElement = 0;
	kg_result result = K15_GUIRegisterUnidentifiedElement(p_GUIContext, &layoutElement,
		K15_GUI_LAYOUT_ELEMENT_TYPE, p_ClipRect);

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	K15_GUILayoutData layoutData = { 0 };
	layoutData.type = p_LayoutType;

	result = K15_GUIAddElementData(contextMemory, layoutElement, &layoutData, sizeof(layoutData));

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	K15_GUILayoutData* elementLayoutData = 0;
	result = K15_GUIGetElementDataRaw(contextMemory, layoutElement, &elementLayoutData, 0);

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	kg_u32 layoutIndex = p_GUIContext->numLayouts;

	p_GUIContext->layoutTable[layoutIndex] = layoutElement;
	++p_GUIContext->numLayouts;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_def void K15_GUICustomBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier,
	K15_GUIToolBarStyle* p_Style)
{
	kg_result result;

	if ((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG) == 1)
	{
		result = K15_GUI_RESULT_ELEMENT_NOT_FINISHED;
		goto functionEnd;
	}

	p_GUIContext->flagMask |= K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG;

	K15_GUIDrawCommandBuffer* drawCmdBuffer = &p_GUIContext->drawCmdBuffer;

	kg_s16 toolbarHeight = p_Style->pixelHeight;
	kg_color32 upperBackgroundColor = p_Style->upperBackgroundColor;
	kg_color32 lowerBackgroundColor = p_Style->lowerBackgroundColor;

	K15_GUIContextMemory* guiContextMemory = &p_GUIContext->memory;
	toolbarHeight = K15_GUI_MIN(p_GUIContext->clipRect.bottom, toolbarHeight);

	K15_GUIRect clipRect;
	clipRect.left = p_GUIContext->clipRect.left;
	clipRect.top = p_GUIContext->clipRect.top;
	clipRect.right = p_GUIContext->clipRect.right;
	clipRect.bottom = toolbarHeight;

	K15_GUIElement* guiElement = 0;
	result = K15_GUIRegisterIdentifiedElement(p_GUIContext, &guiElement, K15_GUI_TOOLBAR_ELEMENT_TYPE, 
		p_Identifier, &clipRect);

	if (!guiElement || result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	result = K15_GUIAddElementData(guiContextMemory, guiElement, &upperBackgroundColor, sizeof(kg_color32));
	result = K15_GUIAddElementData(guiContextMemory, guiElement, &lowerBackgroundColor, sizeof(kg_color32));

	if (result == K15_GUI_RESULT_SUCCESS)
		K15_GUIPushLayout(p_GUIContext, K15_GUI_HORIZONTAL_LAYOUT_TYPE, &clipRect);

functionEnd:
	K15_GUISetLastResult(&p_GUIContext->lastResult, result);
}
/*********************************************************************************/
kg_def kg_b8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY,
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier)
{
	K15_GUIContextStyle* style = &p_GUIContext->style;
	return K15_GUICustomBeginWindow(p_GUIContext, p_PosX, p_PosY, p_Width, p_Height, p_Title,
		p_Identifier, &style->windowStyle);
}
/*********************************************************************************/
kg_def kg_b8 K15_GUICustomBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY,
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier, 
	K15_GUIWindowStyle* p_Style)
{
	return 0;
}
/*********************************************************************************/
kg_def kg_b8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier)
{
	return K15_GUICustomBeginMenu(p_GUIContext, p_MenuText, p_Identifier, &p_GUIContext->style.menuStyle);
}
/*********************************************************************************/
kg_internal kg_result K15_GUIDefaultButtonBehavior(K15_GUIContext* p_GUIContext, const char* p_MenuText,
	const char* p_Identifier, K15_GUIButtonStyle* p_Style)
{
	kg_result result = K15_GUI_RESULT_SUCCESS;
	K15_GUIDrawCommandBuffer* drawCmdBuffer = &p_GUIContext->drawCmdBuffer;

	kg_color32 upperBackgroundColor = p_Style->upperBackgroundColor;
	kg_color32 lowerBackgroundColor = p_Style->lowerBackgroundColor;

	K15_GUIFont* font = p_Style->font;
	K15_GUIRect textRect = { 0 };

	K15_GUICalculateTextRect(p_MenuText, font, &textRect);

	kg_u32 textLength = K15_GUI_STRLEN(p_MenuText);
	K15_GUIContextMemory* guiContextMemory = &p_GUIContext->memory;

	K15_GUIElement* guiElement = 0;
	result = K15_GUIRegisterIdentifiedElement(p_GUIContext, &guiElement, K15_GUI_BUTTON_ELEMENT_TYPE, 
		p_Identifier, &textRect);

	if (!guiElement || result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_GUIButtonData buttonData = { 0 };
	buttonData.textLength = textLength;
	buttonData.buttonStyle = p_Style;

	result = K15_GUIAddElementData(guiContextMemory, guiElement, &buttonData, sizeof(buttonData));
	result = K15_GUIAddElementData(guiContextMemory, guiElement, (void*)p_MenuText, textLength);

functionEnd:
	return result;
}
/*********************************************************************************/
kg_def kg_b8 K15_GUICustomBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier,
	K15_GUIButtonStyle* p_Style)
{
	kg_result result;

	if ((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_MENU_FLAG) == 1)
	{
		result = K15_GUI_RESULT_ELEMENT_NOT_FINISHED;
		goto functionEnd;
	}

	p_GUIContext->flagMask |= K15_GUI_CONTEXT_INSIDE_MENU_FLAG;

	result = K15_GUIDefaultButtonBehavior(p_GUIContext, p_MenuText, p_Identifier, p_Style);

functionEnd:
	K15_GUISetLastResult(&p_GUIContext->lastResult, result);
	return 0;
}
/*********************************************************************************/
kg_def kg_b8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier)
{
	return K15_GUICustomMenuItem(p_GUIContext, p_ItemText, p_Identifier, &p_GUIContext->style.menuItemStyle);
}
/*********************************************************************************/
kg_def kg_b8 K15_GUICustomMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier,
	K15_GUIButtonStyle* p_Style)
{
	return 0;
}
/*********************************************************************************/
kg_def kg_b8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier)
{
	K15_GUIButtonStyle* defaultButtonStyle = &p_GUIContext->style.buttonStyle;
	return K15_GUICustomButton(p_GUIContext, p_ButtonText, p_Identifier, defaultButtonStyle);
}
/*********************************************************************************/
kg_def kg_b8 K15_GUICustomButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier,
	K15_GUIButtonStyle* p_Style)
{
	return 0;
}
/*********************************************************************************/
kg_def void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier)
{
	K15_GUICustomLabel(p_GUIContext, p_LabelText, p_Identifier, &p_GUIContext->style.labelStyle);
}
/*********************************************************************************/
kg_def void K15_GUICustomLabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier,
	K15_GUILabelStyle* p_Style)
{
	
}
/*********************************************************************************/
kg_def void K15_GUISeparator(K15_GUIContext* p_GUIContext)
{

}
/*********************************************************************************/
kg_def void K15_GUIEndMenu(K15_GUIContext* p_GUIContext)
{
	p_GUIContext->numMenus -= 1;

	if (p_GUIContext->numMenus == 0)
		p_GUIContext->flagMask &= ~K15_GUI_CONTEXT_INSIDE_MENU_FLAG;

	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
kg_def void K15_GUIEndSubMenu(K15_GUIContext* p_GUIContext)
{
	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
kg_def void K15_GUIEndWindow(K15_GUIContext* p_GUIContext)
{
	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
kg_def void K15_GUIEndToolBar(K15_GUIContext* p_GUIContext)
{
	if ((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG) == 0)
	{
		K15_GUISetLastResult(&p_GUIContext->lastResult, K15_GUI_RESULT_ELEMENT_NOT_STARTED);
		return;
	}

	p_GUIContext->flagMask &= ~K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG;
	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
kg_internal void K15_GUIArrangeElementsHorizontally(K15_GUILayoutData* p_LayoutData,
	K15_GUIRect* p_LayoutClipRect)
{
	K15_GUIElement** layoutedElements = p_LayoutData->layoutedElements;
	K15_GUIElement* guiElement = 0;

	kg_u32 layoutWidth = p_LayoutClipRect->right - p_LayoutClipRect->left;
	kg_u32 numElements = p_LayoutData->numElements;

	//Thinks about size hints per element
	kg_u32 widthPerElement = layoutWidth / numElements;
	kg_u32 posX = p_LayoutClipRect->left;

	for (kg_u32 elementIndex = 0;
		elementIndex < numElements;
		++elementIndex)
	{
		guiElement = layoutedElements[elementIndex];

		guiElement->clipRect.left = posX;
		guiElement->clipRect.right = posX + widthPerElement;

		posX += widthPerElement;
	}
}
/*********************************************************************************/
kg_internal void K15_GUIArrangeElementsVertically(K15_GUILayoutData* p_LayoutData,
	K15_GUIRect* p_LayoutClipRect)
{
	K15_GUIElement** layoutedElements = p_LayoutData->layoutedElements;
	K15_GUIElement* guiElement = 0;

	kg_u32 layoutHeight = p_LayoutClipRect->bottom - p_LayoutClipRect->top;
	kg_u32 numElements = p_LayoutData->numElements;

	//Thinks about size hints per element
	kg_u32 heightPerElement = layoutHeight / numElements;
	kg_u32 posY = p_LayoutClipRect->top;

	for (kg_u32 elementIndex = 0;
		elementIndex < numElements;
		++elementIndex)
	{
		guiElement = layoutedElements[elementIndex];

		guiElement->clipRect.top = posY;
		guiElement->clipRect.bottom = posY + heightPerElement;

		posY += heightPerElement;
	}
}
/*********************************************************************************/
kg_internal void K15_GUIArrangeElementsStacked(K15_GUILayoutData* p_LayoutData,
	K15_GUIRect* p_LayoutClipRect)
{
	K15_GUIElement** layoutedElements = p_LayoutData->layoutedElements;
	K15_GUIElement* guiElement = 0;

	kg_u32 layoutWidth = p_LayoutClipRect->right - p_LayoutClipRect->left;
	kg_u32 layoutHeight = p_LayoutClipRect->bottom - p_LayoutClipRect->top;
	kg_u32 numElements = p_LayoutData->numElements;
	kg_u32 elementWidth = 0;
	kg_u32 elementHeight = 0;
	kg_u32 posX = p_LayoutClipRect->left;
	kg_u32 posY = p_LayoutClipRect->top;

	for (kg_u32 elementIndex = 0;
		elementIndex < numElements;
		++elementIndex)
	{
		guiElement = layoutedElements[elementIndex];

		elementWidth = guiElement->clipRect.right - guiElement->clipRect.left;
		elementHeight = guiElement->clipRect.bottom - guiElement->clipRect.top;

		guiElement->clipRect.left = posX;
		guiElement->clipRect.right = posX + elementWidth;
		guiElement->clipRect.top = posY;
		guiElement->clipRect.bottom = posY + elementHeight;

		posY += elementHeight;
	}
}
/*********************************************************************************/
kg_internal void K15_GUIArrangeLayoutElements(K15_GUIElement* p_GUIElement)
{
	//layout data should follow right after the actual gui element
	K15_GUILayoutData* layoutData = (K15_GUILayoutData*)(p_GUIElement + 1);
	kg_u32 numElements = layoutData->numElements;

	if (numElements == 0)
		return;

	if (layoutData->type == K15_GUI_HORIZONTAL_LAYOUT_TYPE)
		K15_GUIArrangeElementsHorizontally(layoutData, &p_GUIElement->clipRect);
	else if (layoutData->type == K15_GUI_VERTICAL_LAYOUT_TYPE)
		K15_GUIArrangeElementsVertically(layoutData, &p_GUIElement->clipRect);
	else if (layoutData->type == K15_GUI_STACKED_LAYOUT_TYPE)
		K15_GUIArrangeElementsStacked(layoutData, &p_GUIElement->clipRect);
}
/*********************************************************************************/
kg_internal kg_color32 K15_GUISampleColorGradient(K15_GUIColorGradient* p_ColorGradient, float p_SampleValue)
{
	p_SampleValue = K15_GUI_CLAMP(p_SampleValue, 0.f, 1.f);

	kg_color32 output = 0;
	K15_GUIColorGradientType colorGradientType = p_ColorGradient->type;
	kg_color32 fromColor = p_ColorGradient->from;
	kg_color32 toColor = p_ColorGradient->to;

	float fR = (float)((kg_u8)(fromColor >> 0) / 255);
	float fG = (float)((kg_u8)(fromColor >> 8) / 255);
	float fB = (float)((kg_u8)(fromColor >> 16) / 255);
	float fA = (float)((kg_u8)(fromColor >> 24) / 255);

	float tR = (float)((kg_u8)(toColor >> 0) / 255);
	float tG = (float)((kg_u8)(toColor >> 8) / 255);
	float tB = (float)((kg_u8)(toColor >> 16) / 255);
	float tA = (float)((kg_u8)(toColor >> 24) / 255);

	float oR = 0.f;
	float oG = 0.f;
	float oB = 0.f;
	float oA = 0.f;

	switch (colorGradientType)
	{
	case K15_GUI_SOLID_COLOR:
		output = p_SampleValue > 0.5f ? toColor : fromColor;
		break;

	case K15_GUI_LINEAR_GRADIENT:
		oR = fR * 1.f - p_SampleValue + tR * p_SampleValue;
		oG = fG * 1.f - p_SampleValue + tG * p_SampleValue;
		oB = fB * 1.f - p_SampleValue + tB * p_SampleValue;
		oA = fA * 1.f - p_SampleValue + tA * p_SampleValue;
		output = ((kg_u8)(oR * 255.f) << 0 |
			(kg_u8)(oG * 255.f) << 8 |
			(kg_u8)(oB * 255.f) << 16 |
			(kg_u8)(oA * 255.f) << 24);
		break;
	}

	return output;
}
/*********************************************************************************/
kg_internal void K15_GUICalculateTextRect(const char* p_Text, K15_GUIFont* p_Font, K15_GUIRect* p_OutRect)
{
	if (!p_Text || !p_Font || !p_OutRect)
		return;

	kg_s32 ascent = p_Font->ascent;
	kg_s32 descent = p_Font->descent;
	kg_s32 lineGap = p_Font->lineGap;
	kg_u32 verticalOffset = (kg_u32)(ascent - descent + lineGap);

	kg_s16 posX = 0;
	kg_s16 posY = 0;
	kg_s32 leftSideBearing = 0;
	kg_s32 advanceWidth = 0;
	K15_GUIFontGlyph* glyphs = p_Font->glyphs;
	K15_GUIFontGlyph* glyph = 0;

	K15_GUIGlyphRange glyphRanges[10];
	K15_GUIGlyphRange* glyphRangesPtr = glyphRanges;

	kg_u32 numGlyphRanges = K15_GUIGetGlyphRanges(p_Font->glyphRangeMask, &glyphRangesPtr, 10);
	K15_GUIGlyphRange* glyphRange = 0;

	while (1)
	{
		if (*p_Text == 0)
			break;

		kg_u32 codePoint = (int)(*p_Text++);
		kg_u32 glyphIndex = -1;

		if (codePoint == '\n')
		{
			posY += verticalOffset;
			posX = 0;
		}

		for (kg_u32 glyphRangeIndex = 0;
		glyphRangeIndex < numGlyphRanges;
			++glyphRangeIndex)
		{
			glyphRange = glyphRanges + glyphRangeIndex;

			if (codePoint >= glyphRange->from ||
				codePoint <= glyphRange->to)
			{
				glyphIndex = codePoint - glyphRange->from;
				break;
			}
		}

		if (glyphIndex > glyphRange->to)
			continue;

		glyph = glyphs + glyphIndex;
		advanceWidth = glyph->advanceWidth;

		if (glyph)
		{
			kg_s16 height = glyph->glyphRect.bottom - glyph->glyphRect.top;
			posX += advanceWidth;
			posY = K15_GUI_MAX(posY, height);

			p_OutRect->right = K15_GUI_MAX(p_OutRect->right, posX);
			p_OutRect->bottom = K15_GUI_MAX(p_OutRect->bottom, posY);
		}
	}
}
/*********************************************************************************/
kg_internal kg_result K15_GUICreateToolBarDrawCommands(K15_GUIContextMemory* p_GUIContextMemory,
	K15_GUIElement* p_Element, K15_GUIDrawCommandBuffer* p_DrawCmdBuffer)
{
	kg_result result = K15_GUI_RESULT_SUCCESS;
	kg_color32 upperBackgroundColor = 0;
	kg_color32 lowerBackgroundColor = 0;
	kg_u32 offset = 0;

	result = K15_GUIGetElementData(p_GUIContextMemory, p_Element, &upperBackgroundColor,
		sizeof(kg_color32), offset);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	offset += sizeof(kg_color32);

	result = K15_GUIGetElementData(p_GUIContextMemory, p_Element, &lowerBackgroundColor,
		sizeof(kg_color32), offset);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_GUIColorGradient linearGradient = K15_GUICreateLinearColorGradiant(upperBackgroundColor,
		lowerBackgroundColor);

	result = K15_GUIAddRectShapeDrawCommand(p_DrawCmdBuffer, &p_Element->clipRect, linearGradient);

functionEnd:
	return result;
}
/*********************************************************************************/
typedef struct 
{
	K15_GUIFont* font;
	K15_GUIRect rect;
	kg_u32 textLength;
	kg_color32 textColor;
} K15_GUITextShapeData;
/*********************************************************************************/
kg_internal kg_result K15_GUIAddTextDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer,
	K15_GUIRect* p_ClipRect, K15_GUIFont* p_Font, const char* p_Text, kg_u32 p_TextLength, kg_color32 p_TextColor)
{
	K15_GUITextShapeData shapeData = { 0 };
	shapeData.textLength = p_TextLength;
	shapeData.textColor = p_TextColor;
	shapeData.rect = *p_ClipRect;
	shapeData.font = p_Font;

	K15_GUIDrawCommand* drawCmd = 0;

	kg_result result = K15_GUIAddDrawCommand(p_DrawCommandBuffer, &drawCmd, K15_GUI_DRAW_TEXT_COMMAND);

	if (result == K15_GUI_RESULT_SUCCESS)
		K15_GUIAddDrawCommandData(p_DrawCommandBuffer, drawCmd, &shapeData, sizeof(shapeData));

	if (result == K15_GUI_RESULT_SUCCESS)
		result = K15_GUIAddDrawCommandData(p_DrawCommandBuffer, drawCmd, (void*)p_Text, p_TextLength);

	return result;
}
/*********************************************************************************/
kg_internal kg_result K15_GUICreateButtonDrawCommands(K15_GUIContextMemory* p_GUIContextMemory,
	K15_GUIElement* p_Element, K15_GUIDrawCommandBuffer* p_DrawCmdBuffer)
{
	K15_GUIButtonData buttonData = { 0 };
	kg_result result = K15_GUI_RESULT_SUCCESS;
	kg_u32 offset = 0;

	result = K15_GUIGetElementData(p_GUIContextMemory, p_Element, &buttonData,
		sizeof(buttonData), offset);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	offset += sizeof(buttonData);

	char* text = (char*)alloca(buttonData.textLength);
	result = K15_GUIGetElementData(p_GUIContextMemory, p_Element, text,
		buttonData.textLength, offset);

	if (result != K15_GUI_RESULT_SUCCESS)
		goto functionEnd;

	K15_GUIButtonStyle* buttonStyle = buttonData.buttonStyle;
	kg_color32 upperBackgroundColor = buttonStyle->upperBackgroundColor;
	kg_color32 lowerBackgroundColor = buttonStyle->lowerBackgroundColor;
	kg_color32 textColor = buttonStyle->textColor;
	K15_GUIFont* font = buttonStyle->font;

	K15_GUIColorGradient linearGradient = K15_GUICreateLinearColorGradiant(upperBackgroundColor, 
		lowerBackgroundColor);

	result = K15_GUIAddRectShapeDrawCommand(p_DrawCmdBuffer, &p_Element->clipRect, linearGradient);
	result = K15_GUIAddTextDrawCommand(p_DrawCmdBuffer, &p_Element->clipRect, font, text, buttonData.textLength, textColor);
functionEnd:
	return result;
}
/*********************************************************************************/
kg_internal kg_result K15_GUICreateDrawCommands(K15_GUIContextMemory* p_ContextMemory, 
	K15_GUIElement* p_Element, K15_GUIDrawCommandBuffer* p_DrawCmdBuffer)
{
	kg_result result = K15_GUI_RESULT_SUCCESS;

	switch (p_Element->type)
	{
	case K15_GUI_TOOLBAR_ELEMENT_TYPE:
	{
		result = K15_GUICreateToolBarDrawCommands(p_ContextMemory, p_Element, p_DrawCmdBuffer);
		break;
	}

	case K15_GUI_MENU_ELEMENT_TYPE:
	case K15_GUI_MENU_ITEM_ELEMENT_TYPE:
	case K15_GUI_BUTTON_ELEMENT_TYPE:
	{
		result = K15_GUICreateButtonDrawCommands(p_ContextMemory, p_Element, p_DrawCmdBuffer);
		break;
	}
	default:
		break;
	}
	
	return result;
}
/*********************************************************************************/
kg_internal void K15_GUIClipElements(K15_GUIContext* p_GUIContext)
{
	K15_GUIContextMemory* contextMemory = &p_GUIContext->memory;
	kg_u32 memorySize = contextMemory->memoryBufferSizeInBytes;
	kg_byte* memory = contextMemory->memoryBuffer;

	K15_GUIDrawCommandBuffer* drawCmdBuffer = &p_GUIContext->drawCmdBuffer;

	kg_result result = K15_GUI_RESULT_SUCCESS;

	kg_u32 memoryPosition = 0;
	K15_GUIElement* guiElement = 0;
	K15_GUIElement* layoutElement = 0;
	K15_GUIElement** layoutElements = p_GUIContext->layoutTable;
	K15_GUIRect* guiElementClipRect = 0;
	K15_GUIRect* contextClipRect = &p_GUIContext->clipRect;
	K15_GUIRect* clipRectUsedForClipping = contextClipRect;
		
	while (memoryPosition < memorySize)
	{
		guiElement = (K15_GUIElement*)(memory + memoryPosition);
		guiElementClipRect = &guiElement->clipRect;
		
		if (guiElement->layoutIndex != 0)
			clipRectUsedForClipping = &layoutElements[guiElement->layoutIndex - 1]->clipRect;
		else
			clipRectUsedForClipping = contextClipRect;

		if (K15_GUIPerformClipping(guiElementClipRect, clipRectUsedForClipping) == K15_GUI_RESULT_EMPTY_CLIP_RECT)
			continue;

		if (guiElement->type == K15_GUI_LAYOUT_ELEMENT_TYPE)
			K15_GUIArrangeLayoutElements(guiElement);

		result = K15_GUICreateDrawCommands(contextMemory, guiElement, drawCmdBuffer);

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			K15_GUISetLastResult(&p_GUIContext->lastResult, result);
			break;
		}

		memoryPosition += guiElement->offsetNextElementInBytes;	
	}
}
/*********************************************************************************/
kg_def kg_result K15_GUIBeginFrame(K15_GUIContext* p_GUIContext)
{
	if ((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_FRAME_FLAG) > 0)
	{
		K15_GUISetLastResult(&p_GUIContext->lastResult, K15_GUI_RESULT_FRAME_NOT_FINISHED);
		return K15_GUI_RESULT_FRAME_NOT_FINISHED;
	}
		
	p_GUIContext->drawCmdBuffer.bufferSizeInBytes = 0;
	p_GUIContext->flagMask |= K15_GUI_CONTEXT_INSIDE_FRAME_FLAG;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_def kg_result K15_GUIFinishFrame(K15_GUIContext* p_GUIContext)
{
	if ((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_FRAME_FLAG) == 0)
	{
		K15_GUISetLastResult(&p_GUIContext->lastResult, K15_GUI_RESULT_FRAME_NOT_STARTED);
		return K15_GUI_RESULT_FRAME_NOT_STARTED;
	}

	K15_GUIClipElements(p_GUIContext);

	p_GUIContext->flagMask &= ~K15_GUI_CONTEXT_INSIDE_FRAME_FLAG;
	p_GUIContext->memory.memoryBufferSizeInBytes = 0;
	p_GUIContext->numLayouts = 0;
	p_GUIContext->numMenus = 0;
	K15_GUI_MEMSET(p_GUIContext->elementHashTable, 0, sizeof(p_GUIContext->elementHashTable));

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_def void K15_GUIPopLayout(K15_GUIContext* p_GUIContext)
{
	if (!p_GUIContext)
		return;

	if (p_GUIContext->numLayouts == 0)
		return;

	--p_GUIContext->numLayouts;
}
/*********************************************************************************/
kg_def kg_result K15_GUIGetLastResult(K15_GUIContext* p_GUIContext)
{
	kg_result lastResult = p_GUIContext->lastResult;
	p_GUIContext->lastResult = K15_GUI_RESULT_SUCCESS;

	return lastResult;
}
/*********************************************************************************/
kg_def kg_u32 K15_GUIConvertResultToMessage(kg_result p_Result, char** p_OutMessage, kg_u32 p_OutMessageBufferSizeInBytes)
{
	const char* errorMsg = 0;
	kg_u32 bytesWritten = 0;

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
	else if (p_Result == K15_GUI_RESULT_NO_ICONS)
		errorMsg = "No icons";
	else if (p_Result == K15_GUI_RESULT_UNKNOWN_ERROR)
		errorMsg = "Unknown error";
	else if (p_Result == K15_GUI_RESULT_HASH_CONFLICT)
		errorMsg = "Hash conflict";
	else if (p_Result == K15_GUI_RESULT_FRAME_NOT_FINISHED)
		errorMsg = "Frame not finished";
	else if (p_Result == K15_GUI_RESULT_FRAME_NOT_STARTED)
		errorMsg = "Frame not started";
	else if (p_Result == K15_GUI_RESULT_ELEMENT_NOT_STARTED)
		errorMsg = "Element not started";
	else if (p_Result == K15_GUI_RESULT_ELEMENT_NOT_FINISHED)
		errorMsg = "Element not finished";
	else if (p_Result == K15_GUI_RESULT_DRAW_COMMAND_FINISHED)
		errorMsg = "Draw command already finished";

	if (errorMsg)
	{
		bytesWritten = K15_GUI_MIN(K15_GUI_STRLEN(errorMsg), p_OutMessageBufferSizeInBytes);
		K15_GUI_MEMCPY(*p_OutMessage, errorMsg, bytesWritten);
	}

	return bytesWritten;
}
/*********************************************************************************/
kg_def kg_result K15_GUIAddMouseInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIMouseInput p_MouseInput)
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
kg_def kg_result K15_GUIAddKeyboardInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIKeyboardInput p_KeyboardInput)
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
kg_def kg_result K15_GUIAddSystemEvent(K15_GUIContextEvents* p_GUIContextEvents, K15_GUISystemEvent p_SystemEvent)
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
kg_def kg_u32 K15_GUICalculateDrawCommandBufferSizeInBytes(K15_GUIContext* p_GUIContext)
{
	if (!p_GUIContext)
		return 0;

	return p_GUIContext->drawCmdBuffer.bufferSizeInBytes + sizeof(K15_GUIDrawCommandBuffer);
}
/*********************************************************************************/
kg_def void K15_GUIGetDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer, K15_GUIDrawCommand**
	p_DrawCommandOut)
{
	K15_GUIDrawCommand* drawCommand = (K15_GUIDrawCommand*)(p_DrawCommandBuffer->drawCommandBuffer +
		p_DrawCommandBuffer->bufferPosition);

	*p_DrawCommandOut = drawCommand;
} 
/*********************************************************************************/
kg_def void K15_GUICopyDrawCommandBuffer(K15_GUIContext* p_GUIContext, 
	K15_GUIDrawCommandBuffer* p_GUIDrawCommandBuffer)
{
	if (!p_GUIContext || !p_GUIDrawCommandBuffer)
		return;

	*p_GUIDrawCommandBuffer = p_GUIContext->drawCmdBuffer;
	p_GUIDrawCommandBuffer->bufferPosition = 0;

	if (p_GUIDrawCommandBuffer->bufferSizeInBytes > 0)
	{
		K15_IA_MEMCPY(p_GUIDrawCommandBuffer->drawCommandBuffer, 
			p_GUIContext->drawCmdBuffer.drawCommandBuffer,
			p_GUIContext->drawCmdBuffer.bufferSizeInBytes);
	}
}
/*********************************************************************************/
kg_def kg_result K15_GUIGetDrawCommandDataRaw(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer,
	K15_GUIDrawCommand* p_DrawCommand, void** p_DataPtr, kg_u32 p_OffsetInBytes)
{
	if (!p_DrawCommandBuffer || !p_DrawCommand)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	size_t addressDrawCommand = (size_t)p_DrawCommand;
	size_t addressDrawCommandBuffer = (size_t)p_DrawCommandBuffer->drawCommandBuffer;
	size_t addressOffsetDrawCommand = addressDrawCommand - addressDrawCommandBuffer + sizeof(K15_GUIDrawCommand);

	kg_u32 drawCommandBufferSizeInBytes = p_DrawCommandBuffer->bufferSizeInBytes;
	kg_u32 drawCommandCapacityInBytes = p_DrawCommandBuffer->bufferCapacityInBytes;
	kg_byte* drawCommandMemoryBuffer = p_DrawCommandBuffer->drawCommandBuffer;

	if (addressDrawCommand < addressDrawCommandBuffer ||
		addressDrawCommand > addressDrawCommandBuffer + drawCommandCapacityInBytes)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	*p_DataPtr = drawCommandMemoryBuffer + addressOffsetDrawCommand + p_OffsetInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_def kg_result K15_GUIGetDrawCommandData(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer,
	K15_GUIDrawCommand* p_DrawCommand, void* p_Data, kg_u32 p_DataSizeInBytes, kg_u32 p_OffsetInBytes)
{
	if (!p_DrawCommandBuffer || !p_Data || p_DataSizeInBytes == 0)
		return K15_GUI_RESULT_INVALID_ARGUMENTS;

	size_t addressDrawCommand = (size_t)p_DrawCommand;
	size_t addressDrawCommandBuffer = (size_t)p_DrawCommandBuffer->drawCommandBuffer;
	size_t addressOffsetDrawCommand = addressDrawCommand - addressDrawCommandBuffer + sizeof(K15_GUIDrawCommand);

	kg_u32 drawCommandParamSizeInBytes = p_DrawCommand->sizeInBytes;
	kg_u32 drawCommandBufferSizeInBytes = p_DrawCommandBuffer->bufferSizeInBytes;
	kg_u32 drawCommandCapacityInBytes = p_DrawCommandBuffer->bufferCapacityInBytes;
	kg_byte* drawCommandMemoryBuffer = p_DrawCommandBuffer->drawCommandBuffer;

	if (drawCommandParamSizeInBytes < p_OffsetInBytes + p_DataSizeInBytes)
		return K15_GUI_RESULT_OUT_OF_RANGE;

	if (drawCommandBufferSizeInBytes + p_DataSizeInBytes > drawCommandCapacityInBytes)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	void* drawCommandData = 0;
	kg_result result = K15_GUIGetDrawCommandDataRaw(p_DrawCommandBuffer, p_DrawCommand, &drawCommandData,
		p_OffsetInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
		return result;

	K15_IA_MEMCPY(p_Data, drawCommandData, p_DataSizeInBytes);

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_def kg_b8 K15_GUIHasDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer)
{
	return p_DrawCommandBuffer->bufferPosition < p_DrawCommandBuffer->bufferSizeInBytes;
}
/*********************************************************************************/
kg_def void K15_GUINextDrawCommand(K15_GUIDrawCommandBuffer* p_DrawCommandBuffer)
{
	K15_GUIDrawCommand* drawCommand = (K15_GUIDrawCommand*)(p_DrawCommandBuffer->drawCommandBuffer +
		p_DrawCommandBuffer->bufferPosition);

	p_DrawCommandBuffer->bufferPosition += drawCommand->sizeInBytes + sizeof(K15_GUIDrawCommand);
}
/*********************************************************************************/


#endif //K15_GUI_IMPLEMENTATION
#endif //_K15_GUILayer_Context_h_
#ifndef _K15_GUILayer_Context_h_
#define _K15_GUILayer_Context_h_

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

#define kg_size_kilo_bytes(n) (n*1024)

#define K15_GUI_MIN_MEMORY_SIZE_IN_BYTES sizeof(K15_GUIContext) + kg_size_kilo_bytes(10)

typedef unsigned long long kg_u64;
typedef unsigned int kg_u32;
typedef unsigned short kg_u16;
typedef unsigned char kg_u8;

typedef long long kg_s64;
typedef int kg_s32;
typedef short kg_s16;
typedef char kg_s8;

typedef unsigned char kg_byte;
typedef unsigned char kg_b8;
typedef unsigned int kg_result;

struct K15_GUIContext;
struct K15_GUIElement;

typedef void(*K15_GUIIteratorFnc)(K15_GUIContext*, K15_GUIElement*, void*);
/*********************************************************************************/
enum K15_GUIDockingAreaFlags
{
	K15_GUI_LEFT_DOCKING_AREA = 0x001,
	K15_GUI_RIGHT_DOCKING_AREA = 0x002,
	K15_GUI_TOP_DOCKING_AREA = 0x004,
	K15_GUI_BOTTOM_DOCKING_AREA = 0x008
};
/*********************************************************************************/
enum K15_GUIElementFlags
{
	K15_GUI_ELEMENT_HOVERED = 0x001,
	K15_GUI_ELEMENT_FOCUSED = 0x002,
	K15_GUI_ELEMENT_MOUSE_DOWN = 0x004,
	K15_GUI_ELEMENT_CLICKED = 0x008,
	K15_GUI_ELEMENT_LAYOUTED = 0x010
};
/*********************************************************************************/
enum K15_GUILayoutType
{
	K15_GUI_VERTICAL_LAYOUT = 0,
	K15_GUI_HORIZONTAL_LAYOUT
};
/*********************************************************************************/
enum K15_GUIElementType
{
	K15_GUI_BUTTON = 0,
	K15_GUI_SLIDER,
	K15_GUI_WINDOW,
	K15_GUI_LABEL,
	K15_GUI_MENU,
	K15_GUI_SEPARATOR,
	K15_GUI_TOOLBAR,
	K15_GUI_MENU_ITEM,
}; 
/*********************************************************************************/
typedef struct _K15_GUIRectangle
{
	kg_s16 pixelPosLeft;
	kg_s16 pixelPosTop;
	kg_s16 pixelPosRight;
	kg_s16 pixelPosBottom;
} K15_GUIRectangle;
/*********************************************************************************/
typedef struct _K15_GUIDimension
{
	kg_u16 width;
	kg_u16 height;
} K15_GUIDimension;
/*********************************************************************************/
typedef struct _K15_GUISizeHint
{
	K15_GUIRectangle* rect;
	K15_GUIDimension dimHint;
	K15_GUIDimension dimMin;
} K15_GUISizeHint;
/*********************************************************************************/
typedef struct _K15_GUIElement
{
	K15_GUIElementType type;
	K15_GUIRectangle rect;
	K15_GUIDimension minSize;
	K15_GUIDimension sizeHint;
	kg_u32 identifierHash;
	kg_u32 offsetInBytes;
	kg_u32 sizeInBytes;
	kg_u32 flagMask;
} K15_GUIElement;

/*********************************************************************************/
typedef struct _K15_GUIFont
{
	kg_u64 userData;
} K15_GUIFont;
/*********************************************************************************/
typedef struct _K15_GUIWindowStyle
{
	kg_u32 borderUpperColor;
	kg_u32 borderLowerColor;
	kg_u32 upperBackgroundColor;
	kg_u32 lowerBackgroundColor;
	kg_u32 upperTitleBackgroundColor;
	kg_u32 lowerTitleBackgroundColor;
	kg_u32 titleTextColor;
	kg_u16 titlePixelPadding;
	kg_u16 borderPixelThickness;
	K15_GUIFont* font;
} K15_GUIWindowStyle;
/*********************************************************************************/
typedef struct _K15_GUIButtonStyle
{
	kg_u32 borderUpperColor;
	kg_u32 borderLowerColor;
	kg_u32 upperBackgroundColor;
	kg_u32 lowerBackgroundColor;
	kg_u32 textColor;
	kg_u16 borderPixelThickness;
	kg_u16 verticalPixelPadding;
	kg_u16 horizontalPixelPadding;
	K15_GUIFont* font;
} K15_GUIButtonStyle;
/*********************************************************************************/
typedef struct _K15_GUILabelStyle
{
	kg_u32 textColor;
	K15_GUIFont* font;
} K15_GUILabelStyle;
/*********************************************************************************/
typedef struct _K15_GUIMenuStyle
{
	kg_u32 textColor;
	kg_u32 upperBackgroundColor;
	kg_u32 lowerBackgroundColor;
	kg_u32 upperHoveredBackgroundColor;
	kg_u32 lowerHoveredBackgroundColor;
	kg_u32 upperFocusedBackgroundColor;
	kg_u32 lowerFocusedBackgroundColor;
	kg_u32 verticalPixelPadding;
	kg_u32 horizontalPixelPadding;
	K15_GUIFont* font;
} K15_GUIMenuStyle;
/*********************************************************************************/
typedef struct _K15_GUIToolBarStyle
{
	kg_u32 lowerBackgroundColor;
	kg_u32 upperBackgroundColor;
	kg_u32 pixelHeight;
} K15_GUIToolBarStyle;
/*********************************************************************************/
typedef struct _K15_GUIMenuItemStyle
{
	kg_u32 lowerBackgroundColor;
	kg_u32 upperBackgroundColor;
	kg_u32 lowerHoveredBackgroundColor;
	kg_u32 upperHoveredBackgroundColor;
	kg_u32 lowerMouseDownBackgroundColor;
	kg_u32 upperMouseDownBackgroundColor;
	kg_u32 verticalPixelPadding;
	kg_u32 horizontalPixelPadding;
	kg_u32 textColor;
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
typedef struct _K15_GUIToolBarData
{
	K15_GUIToolBarStyle* toolBarStyle;
} K15_GUIToolBarData;
/*********************************************************************************/
typedef struct _K15_GUIMenuData
{
	K15_GUIMenuStyle* menuStyle;
	char* title;
	kg_u32 textLength;
	kg_b8 expanded;
	kg_b8 subMenu;
} K15_GUIMenuData;
/*********************************************************************************/
typedef struct _K15_GUIMenuItemData
{
	K15_GUIMenuItemStyle* menuItemStyle;
	char* text;
	kg_u32 textLength;
} K15_GUIMenuItemData;
/*********************************************************************************/
typedef struct _K15_GUIWindowData
{
	K15_GUIWindowStyle* style;
	K15_GUIRectangle contentRect;
	char* title;
	kg_u32 textLength;
	kg_b8 expanded;
} K15_GUIWindowData;
/*********************************************************************************/
typedef struct _K15_GUIButtonData
{
	K15_GUIButtonStyle* style;
	char* text;
	kg_u32 textLength;
} K15_GUIButtonData;
/*********************************************************************************/
typedef struct _K15_GUILabelData
{
	K15_GUILabelStyle* style;
	char* text;
	kg_u32 textLength;
} K15_GUILabelData;
/*********************************************************************************/
typedef struct _K15_GUILayout
{
	K15_GUISizeHint elementSizeHints[K15_GUI_MAX_ELEMENTS_PER_LAYOUT];
	K15_GUIRectangle layoutRectangle;
	K15_GUILayoutType type;
	kg_u32 numElements;

	union 
	{
		kg_u16 fixedWidthPerElement;
		kg_u16 fixedHeightPerElement;
	} params;
} K15_GUILayout;
/*********************************************************************************/
enum K15_GUIContextCreationFlags
{
	K15_GUI_CONTEXT_INSIDE_WINDOW_FLAG		= 0x01,
	K15_GUI_CONTEXT_INSIDE_MENU_FLAG		= 0x02
};
/*********************************************************************************/
enum K15_GUIDrawCommandCreationFlags
{
	K15_GUI_CONVERT_TO_NDC = 0x01
};
/*********************************************************************************/
enum K15_GUIMouseInputType : kg_u16
{
	K15_GUI_MOUSE_BUTTON_PRESSED = 0,
	K15_GUI_MOUSE_BUTTON_RELEASED,
	K15_GUI_MOUSE_WHEEL_UP,
	K15_GUI_MOUSE_WHEEL_DOWN,
	K15_GUI_MOUSE_MOVED
};
/*********************************************************************************/
enum K15_GUIMouseButtonType : kg_u16
{
	K15_GUI_MOUSE_BUTTON_LEFT = 0,
	K15_GUI_MOUSE_BUTTON_RIGHT,
	K15_GUI_MOUSE_BUTTON_MIDDLE,
	K15_GUI_MOUSE_BUTTON_SPECIAL1,
	K15_GUI_MOUSE_BUTTON_SPECIAL2
};
/*********************************************************************************/
enum K15_GUIKeyboardModifierType
{
	K15_GUI_CTRL_MODIFIER  = 0x01,
	K15_GUI_L_ALT_MODIFIER = 0x02,
	K15_GIU_R_ALT_MODIFIER = 0x04,
	K15_GUI_SHIFT_MODIFIER = 0x08
};
/*********************************************************************************/
enum K15_GUIKeyboardInputType
{
	K15_GUI_KEY_PRESSED = 0,
	K15_GUI_KEY_RELEASED,
	K15_GUI_TEXT_INPUT
};
/*********************************************************************************/
enum K15_GUIKeyboardKeyType
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
};
/*********************************************************************************/
enum K15_GUISystemEventType
{
	K15_GUI_WINDOW_RESIZED = 0,
	K15_GUI_SYSTEM_EVENT_COUNT
};
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
	kg_u16 mousePosX;
	kg_u16 mousePosY;
	kg_s16 mouseDeltaX;
	kg_s16 mouseDeltaY;
	kg_u16 numBufferedSystemEvents;
	kg_u16 numBufferedMouseInputs;
	kg_u16 numBufferedKeyboardInputs;
	K15_GUISystemEvent bufferedSystemEvents[K15_GUI_MAX_BUFFERED_SYSTEM_EVENTS];
	K15_GUIMouseInput bufferedMouseInput[K15_GUI_MAX_BUFFERED_MOUSE_INPUTS];
	K15_GUIKeyboardInput bufferedKeyboardInput[K15_GUI_MAX_BUFFERED_KEYBOARD_INPUTS];
} K15_GUIContextEvents;
/*********************************************************************************/
typedef struct _K15_GUIResources
{
		
} K15_GUIResources;
/*********************************************************************************/
typedef struct _K15_GUIContext
{
	kg_byte* memoryBuffer;
	K15_GUIResources* resources;
	K15_GUIContextStyle style;
	K15_GUIContextEvents events;
	K15_GUILayout layoutStack[K15_GUI_MAX_LAYOUTS];
	kg_u8 numMenus;
	kg_u8 numLayouts;
	kg_u8 layoutIndex;
	kg_u16 windowWidth;
	kg_u16 windowHeight;
	kg_u32 focusedElementIdHash;
	kg_u32 clickedElementIdHash;
	kg_u32 activatedElementIdHash;
	kg_u32 hoveredElementIdHash;
	kg_u32 mouseDownElementIdHash;
	kg_u32 memoryBufferCapacityInBytes;
	kg_u32 memoryBufferSizeInBytes;
	kg_u32 flagMask;
} K15_GUIContext;
/*********************************************************************************/

//how this should work:
// - Call gui logic (K15_GUIButton, K15_GUIBeginWindow, K15_GUIPushHorizontalLayout etc.)
// - Store elements internally in the gui context (just rects?) <-- headache
// - iterate over elements (layouting)
// - iterate over elements (input)
// - iterate over elements (rendering)
// - Call gui logic (next frame - retrieve results from last frame. Mainly results of the input)

kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext, kg_u32 p_InitFlag);
kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext, 
	kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes);

kg_byte* K15_GUIGetGUIElementMemory(K15_GUIElement* p_GUIElement);

void K15_GUIBeginDockingArea(K15_GUIContext* p_GUIContext, kg_s16 p_PosX, kg_s16 p_PosY,
	kg_u16 p_Width, kg_u16 p_Height, kg_u32 p_AllowedDockingAreasMask);

void K15_GUIBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier);
void K15_GUIBeginToolBarEX(K15_GUIContext* p_GUIContext, const char* p_Identifier, K15_GUIToolBarStyle* p_ToolBarStyle);

kg_b8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY,
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier);
kg_b8 K15_GUIBeginWindowEX(K15_GUIContext* p_GUIContext, kg_s16* p_PosX, kg_s16* p_PosY,
	kg_u16* p_Width, kg_u16* p_Height, const char* p_Title, const char* p_Identifier,
	K15_GUIWindowStyle* p_GUIWindowStyle);

kg_b8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier);
kg_b8 K15_GUIBeginMenuEX(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier, 
	K15_GUIMenuStyle* p_MenuStyle);

kg_b8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier);
kg_b8 K15_GUIMenuItemEX(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier,
	K15_GUIMenuItemStyle* p_MenuItemStyle);

kg_b8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier);
kg_b8 K15_GUIButtonEX(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier, 
	K15_GUIButtonStyle* p_GUIButtonStyle);

void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier);
void K15_GUILabelEX(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier, 
	K15_GUILabelStyle* p_GUILabelStyle);

void K15_GUIPushVerticalLayout(K15_GUIContext* p_GUIContext, K15_GUIRectangle p_LayoutArea, 
	kg_u16 p_FixedWidthPerElement = 0);
void K15_GUIPushHorizontalLayout(K15_GUIContext* p_GUIContext, K15_GUIRectangle p_LayoutArea,
	kg_u16 p_FixedHeightPerElement = 0);

void K15_GUIPopLayout(K15_GUIContext* p_GUIContext);

void K15_GUIEndWindow(K15_GUIContext* p_GUIContext);
void K15_GUIEndMenu(K15_GUIContext* p_GUIContext);
void K15_GUIEndDockingArea(K15_GUIContext* p_GUIContext);
void K15_GUIEndToolBar(K15_GUIContext* p_GUIContext);

void K15_GUIFinishGUIFrame(K15_GUIContext* p_GUIContext);

void K15_GUIIterateElements(K15_GUIContext* p_GUIContext, K15_GUIIteratorFnc p_Function, void* p_UserData);
void K15_GUIIterateRetainedElements(K15_GUIContext* p_GUIContext, K15_GUIIteratorFnc p_Function, void* p_UserData);

void K15_GUIAddMouseInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIMouseInput* p_MouseInput);
void K15_GUIAddKeyboardInput(K15_GUIContextEvents* p_GUIContextEvents, K15_GUIKeyboardInput* p_KeyboardInput);
void K15_GUIAddSystemEvent(K15_GUIContextEvents* p_GUIContextEvents, K15_GUISystemEvent* p_SystemEvent);



/*********************************************************************************/
intern inline K15_GUIContextStyle K15_InternalCreateDefaultStyle(K15_ResourceContext* p_ResourceContext)
{
	K15_GUIContextStyle defaultStyle = {};

	//Button Style
	defaultStyle.buttonStyle.borderLowerColor = 0xFF101010;
	defaultStyle.buttonStyle.borderUpperColor = 0xFF606060;
	defaultStyle.buttonStyle.lowerBackgroundColor = 0xFF505050;
	defaultStyle.buttonStyle.upperBackgroundColor = 0xFF303030;
	defaultStyle.buttonStyle.textColor = 0xFF000000;
	defaultStyle.buttonStyle.borderPixelThickness = 2;
	defaultStyle.buttonStyle.horizontalPixelPadding = 4;
	defaultStyle.buttonStyle.verticalPixelPadding = 2;
	defaultStyle.buttonStyle.font = K15_GetResourceRenderFontDesc(p_ResourceContext, styleFontResource);

	//Window Style
	defaultStyle.windowStyle.borderLowerColor = 0xFF000000;
	defaultStyle.windowStyle.borderUpperColor = 0xFF050545;
	defaultStyle.windowStyle.lowerBackgroundColor = 0xFF808080;
	defaultStyle.windowStyle.upperBackgroundColor = 0xFF101010;
	defaultStyle.windowStyle.upperTitleBackgroundColor = 0xFF000000;
	defaultStyle.windowStyle.lowerTitleBackgroundColor = 0xFF000000;
	defaultStyle.windowStyle.titleTextColor = 0xFFEEEEEE;
	defaultStyle.windowStyle.borderPixelThickness = 2;
	defaultStyle.windowStyle.titlePixelPadding = 2;
	defaultStyle.windowStyle.font = K15_GetResourceRenderFontDesc(p_ResourceContext, styleFontResource);

	//Label Style
	defaultStyle.labelStyle.textColor = 0xFF000000;
	defaultStyle.labelStyle.font = K15_GetResourceRenderFontDesc(p_ResourceContext, styleFontResource);

	//Toolbar Style
	defaultStyle.toolBarStyle.upperBackgroundColor = 0xFF101010;
	defaultStyle.toolBarStyle.lowerBackgroundColor = 0xFF808080;
	defaultStyle.toolBarStyle.pixelHeight = 22;

	//Menu Style
	defaultStyle.menuStyle.font = K15_GetResourceRenderFontDesc(p_ResourceContext, styleFontResource);
	defaultStyle.menuStyle.menuColors.lowerBackgroundColor = 0xFF808080;
	defaultStyle.menuStyle.menuColors.upperBackgroundColor = 0xFF101010;
	defaultStyle.menuStyle.menuColors.lowerFocusedBackgroundColor = 0xFFC0C0C0;
	defaultStyle.menuStyle.menuColors.upperFocusedBackgroundColor = 0xFF606060;
	defaultStyle.menuStyle.menuColors.lowerHoveredBackgroundColor = 0xFFA0A0A0;
	defaultStyle.menuStyle.menuColors.upperHoveredBackgroundColor = 0xFF404040;
	defaultStyle.menuStyle.subMenuColors.lowerBackgroundColor = 0xFF808080;
	defaultStyle.menuStyle.subMenuColors.upperBackgroundColor = 0xFF808080;
	defaultStyle.menuStyle.subMenuColors.lowerFocusedBackgroundColor = 0xFF404040;
	defaultStyle.menuStyle.subMenuColors.upperFocusedBackgroundColor = 0xFF404040;
	defaultStyle.menuStyle.subMenuColors.lowerHoveredBackgroundColor = 0xFF656565;
	defaultStyle.menuStyle.subMenuColors.upperHoveredBackgroundColor = 0xFF656565;
	defaultStyle.menuStyle.textColor = 0XFF000000;
	defaultStyle.menuStyle.verticalPixelPadding = 2;
	defaultStyle.menuStyle.horizontalPixelPadding = 8;

	//Menu Item Style
	defaultStyle.menuItemStyle.font = K15_GetResourceRenderFontDesc(p_ResourceContext, styleFontResource);
	defaultStyle.menuItemStyle.lowerBackgroundColor = 0xFF808080;
	defaultStyle.menuItemStyle.upperBackgroundColor = 0xFF808080;
	defaultStyle.menuItemStyle.lowerHoveredBackgroundColor = 0xFF656565;
	defaultStyle.menuItemStyle.upperHoveredBackgroundColor = 0xFF656565;
	defaultStyle.menuItemStyle.lowerMouseDownBackgroundColor = 0xFF404040;
	defaultStyle.menuItemStyle.upperMouseDownBackgroundColor = 0xFF404040;
	defaultStyle.menuItemStyle.textColor = 0xFF000000;
	defaultStyle.menuItemStyle.verticalPixelPadding = 2;
	defaultStyle.menuItemStyle.horizontalPixelPadding = 8;

	return defaultStyle;
}
/*********************************************************************************/
intern K15_GUIElement* K15_InternalGUISearchElementByIdentifier(K15_GUIContext* p_GUIContext, uint32 p_IdentifierHash,
	uint32 p_BufferOffsetInBytes, uint32 p_BufferSizeInBytes)
{
	K15_GUIElement* element = 0;
	byte* dataBuffer = p_GUIContext->memoryBuffer + p_BufferOffsetInBytes;
	uint32 offsetInBytes = 0;

	while (offsetInBytes < p_BufferSizeInBytes)
	{
		K15_GUIElement* currentElement = (K15_GUIElement*)(dataBuffer + offsetInBytes);

		if (currentElement->identifierHash == p_IdentifierHash)
		{
			element = currentElement;
			break;
		}
		offsetInBytes += currentElement->sizeInBytes;
	}

	return element;
}
/*********************************************************************************/
intern K15_GUIElement* K15_InternalGUIGetElement(K15_GUIContext* p_GUIContext, uint32 p_IdentifierHash)
{
	uint32 dataSizeInBytes = p_GUIContext->memoryCurrentSizeInBytes;
	return K15_InternalGUISearchElementByIdentifier(p_GUIContext, p_IdentifierHash,
		0, dataSizeInBytes);
}
/*********************************************************************************/
intern K15_GUILayout* K15_InternalGUIGetTopLayout(K15_GUIContext* p_GUIContext)
{
	K15_GUILayout* topLayout = 0;
	uint32 layoutIndex = p_GUIContext->layoutIndex;

	if (layoutIndex > 0)
	{
		layoutIndex -= 1;
		topLayout = &p_GUIContext->layoutStack[layoutIndex];
	}

	return topLayout;
}
/*********************************************************************************/
intern void K15_InternalGUIAddGUISizeHintsToTopLayout(K15_GUIContext* p_GUIContext, K15_GUIRectangle* p_GUIRect,
	K15_GUIDimension p_SizeHint, K15_GUIDimension p_SizeMin)
{
	K15_GUILayout* topLayout = K15_InternalGUIGetTopLayout(p_GUIContext);

	if (topLayout)
	{
		K15_ASSERT(topLayout->numElements != K15_GUI_MAX_ELEMENTS_PER_LAYOUT);

		uint32 elementIndex = topLayout->numElements++;
		topLayout->elementSizeHints[elementIndex].rect = p_GUIRect;
		topLayout->elementSizeHints[elementIndex].dimHint = p_SizeHint;
		topLayout->elementSizeHints[elementIndex].dimMin = p_SizeMin;
	}
}
/*********************************************************************************/
struct K15_GUIMousePickQuery
{
	uint16 mousePosX;
	uint16 mousePosY;
	K15_GUIElement* pickedElement;
};
/*********************************************************************************/
intern void K15_InternalGUIPickGUIElementWithMouse(K15_GUIContext* p_GUIContext, K15_GUIElement* p_GUIElement,
	void* p_UserData)
{
	K15_GUIMousePickQuery* mousePickQuery = (K15_GUIMousePickQuery*)p_UserData;

	bool8 pickedElement = K15_Collision2DBoxPoint(p_GUIElement->rect.pixelPosLeft, p_GUIElement->rect.pixelPosTop,
		p_GUIElement->rect.pixelPosRight, p_GUIElement->rect.pixelPosBottom,
		mousePickQuery->mousePosX, mousePickQuery->mousePosY);

	if (pickedElement)
	{
		mousePickQuery->pickedElement = p_GUIElement;
	}
}
/*********************************************************************************/
intern void K15_InternalGUISetHoveredElement(K15_GUIContext* p_GUIContext, K15_GUIElement* p_Element)
{
	uint32 prevHoveredElementIdHash = p_GUIContext->hoveredElementIdHash;

	K15_GUIElement* prevHoveredElement =
		K15_InternalGUIGetElement(p_GUIContext, prevHoveredElementIdHash);

	if (prevHoveredElement)
	{
		prevHoveredElement->flagMask &= ~K15_GUI_ELEMENT_HOVERED;
	}

	if (p_Element)
	{
		p_GUIContext->hoveredElementIdHash = p_Element->identifierHash;
		p_Element->flagMask |= K15_GUI_ELEMENT_HOVERED;
	}
}
/*********************************************************************************/
intern void K15_InternalGUISetMouseDownElement(K15_GUIContext* p_GUIContext, K15_GUIElement* p_Element)
{
	uint32 prevMouseDownElementIdHash = p_GUIContext->mouseDownElementIdHash;
	uint32 prevActiveElementIdHash = p_GUIContext->activatedElementIdHash;

	K15_GUIElement* prevMouseDownElement =
		K15_InternalGUIGetElement(p_GUIContext, prevMouseDownElementIdHash);

	K15_GUIElement* prevActiveElement =
		K15_InternalGUIGetElement(p_GUIContext, prevActiveElementIdHash);

	if (prevMouseDownElement)
	{
		prevMouseDownElement->flagMask &= ~K15_GUI_ELEMENT_MOUSE_DOWN;
	}

	if (p_Element)
	{
		p_GUIContext->mouseDownElementIdHash = p_Element->identifierHash;
		p_Element->flagMask |= K15_GUI_ELEMENT_MOUSE_DOWN;
	}
}
/*********************************************************************************/
intern void K15_InternalSetFocusedElement(K15_GUIContext* p_GUIContext, K15_GUIElement* p_Element)
{
	uint32 prevFocusedElementIdHash = p_GUIContext->focusedElementIdHash;
	uint32 prevActivatedElementIdHash = p_GUIContext->activatedElementIdHash;

	p_GUIContext->focusedElementIdHash = 0;
	p_GUIContext->activatedElementIdHash = 0;

	K15_GUIElement* prevFocusedDownElement =
		K15_InternalGUIGetElement(p_GUIContext, prevFocusedElementIdHash);
	K15_GUIElement* prevActivatedElement =
		K15_InternalGUIGetElement(p_GUIContext, prevActivatedElementIdHash);

	if (prevFocusedDownElement)
	{
		prevFocusedDownElement->flagMask &= ~K15_GUI_ELEMENT_FOCUSED;
	}

	if (p_Element)
	{
		p_GUIContext->focusedElementIdHash = p_Element->identifierHash;
		p_Element->flagMask |= K15_GUI_ELEMENT_FOCUSED;

		//set element to clicked when it was also the element that has the last mouse down state
		if (p_Element->flagMask & K15_GUI_ELEMENT_MOUSE_DOWN)
		{
			p_GUIContext->clickedElementIdHash = p_Element->identifierHash;
			p_Element->flagMask |= K15_GUI_ELEMENT_CLICKED;
			p_Element->flagMask &= ~K15_GUI_ELEMENT_MOUSE_DOWN;
		}
	}
}
/*********************************************************************************/
intern void K15_InternalGUIHandleMouseMoved(K15_GUIContext* p_GUIContext, uint16 p_MousePosX, uint16 p_MousePosY)
{
	K15_GUIMousePickQuery mousePickQuery = {};
	mousePickQuery.mousePosX = p_MousePosX;
	mousePickQuery.mousePosY = p_MousePosY;

	K15_GUIIterateElements(p_GUIContext, K15_InternalGUIPickGUIElementWithMouse, &mousePickQuery);
	K15_InternalGUISetHoveredElement(p_GUIContext, mousePickQuery.pickedElement);
}
/*********************************************************************************/
intern void K15_InternalGUIHandleMousePressed(K15_GUIContext* p_GUIContext, K15_GUIMouseInput* p_MouseInput,
	uint16 p_MousePosX, uint16 p_MousePosY)
{
	K15_GUIMousePickQuery mousePickQuery = {};
	mousePickQuery.mousePosX = p_MousePosX;
	mousePickQuery.mousePosY = p_MousePosY;

	K15_GUIIterateElements(p_GUIContext, K15_InternalGUIPickGUIElementWithMouse, &mousePickQuery);
	K15_InternalGUISetMouseDownElement(p_GUIContext, mousePickQuery.pickedElement);
}
/*********************************************************************************/
intern void K15_InternalGUIHandleMouseReleased(K15_GUIContext* p_GUIContext, K15_GUIMouseInput* p_MouseInput,
	uint16 p_MousePosX, uint16 p_MousePosY)
{
	K15_GUIMousePickQuery mousePickQuery = {};
	mousePickQuery.mousePosX = p_MousePosX;
	mousePickQuery.mousePosY = p_MousePosY;

	K15_GUIIterateElements(p_GUIContext, K15_InternalGUIPickGUIElementWithMouse, &mousePickQuery);
	K15_InternalSetFocusedElement(p_GUIContext, mousePickQuery.pickedElement);
}
/*********************************************************************************/
intern void K15_InternalGUIHandleMouseWheel(K15_GUIContext* p_GUIContext, K15_GUIMouseInput* p_MouseInput,
	uint16 p_MousePosX, uint16 p_MousePosY)
{

}
/*********************************************************************************/
intern void K15_InternalGUIHandleMouseInput(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	uint16 oldMousePosX = p_Events->mousePosX;
	uint16 oldMousePosY = p_Events->mousePosY;
	uint16 newMousePosX = p_Events->mousePosX;
	uint16 newMousePosY = p_Events->mousePosY;

	for (uint32 eventIndex = 0;
		eventIndex < p_Events->numBufferedMouseInputs;
		++eventIndex)
	{
		K15_GUIMouseInput* mouseInput = (p_Events->bufferedMouseInput + eventIndex);

		if (mouseInput->type == K15_GUI_MOUSE_MOVED)
		{
			newMousePosX = mouseInput->mousePosX;
			newMousePosY = mouseInput->mousePosY;
			K15_InternalGUIHandleMouseMoved(p_GUIContext, newMousePosX, newMousePosY);
		}
		else if (mouseInput->type == K15_GUI_MOUSE_BUTTON_PRESSED)
		{
			K15_InternalGUIHandleMousePressed(p_GUIContext, mouseInput, newMousePosX, newMousePosY);
		}
		else if (mouseInput->type == K15_GUI_MOUSE_BUTTON_RELEASED)
		{
			K15_InternalGUIHandleMouseReleased(p_GUIContext, mouseInput, newMousePosX, newMousePosY);
		}
		else if (mouseInput->type == K15_GUI_MOUSE_WHEEL_DOWN ||
			mouseInput->type == K15_GUI_MOUSE_WHEEL_UP)
		{
			K15_InternalGUIHandleMouseWheel(p_GUIContext, mouseInput, newMousePosX, newMousePosY);
		}
	}

	p_Events->mouseDeltaX = newMousePosX - oldMousePosX;
	p_Events->mouseDeltaY = newMousePosY - oldMousePosY;
	p_Events->mousePosX = newMousePosX;
	p_Events->mousePosY = newMousePosY;

	p_Events->numBufferedMouseInputs = 0;
}
/*********************************************************************************/
intern void K15_InternalGUIHandleKeyboardInput(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	for (uint32 eventIndex = 0;
		eventIndex < p_Events->numBufferedKeyboardInputs;
		++eventIndex)
	{
		K15_GUIKeyboardInput* keyboardInput = p_Events->bufferedKeyboardInput + eventIndex;

		if (keyboardInput->keyType == K15_GUI_KEY_F1 &&
			keyboardInput->type == K15_GUI_KEY_PRESSED)
		{
			//Toggle debug mode
			p_GUIContext->debugModeActive = !p_GUIContext->debugModeActive;
		}
	}

	p_Events->numBufferedKeyboardInputs = 0;
}
/*********************************************************************************/
intern void K15_InternalGUIHandleSystemEvents(K15_GUIContext* p_GUIContext, K15_GUIContextEvents* p_Events)
{
	for (uint32 eventIndex = 0;
		eventIndex < p_Events->numBufferedSystemEvents;
		++eventIndex)
	{
		K15_GUISystemEvent* systemEvent = p_Events->bufferedSystemEvents + eventIndex;

		if (systemEvent->type == K15_GUI_WINDOW_RESIZED)
		{
			uint16 newWidth = systemEvent->params.size.width;
			uint16 newHeight = systemEvent->params.size.height;

			p_GUIContext->windowHeight = newHeight;
			p_GUIContext->windowWidth = newWidth;
		}
	}

	p_Events->numBufferedSystemEvents = 0;
}
/*********************************************************************************/
intern void K15_InternalGUIHandleInput(K15_GUIContext* p_GUIContext)
{
	K15_GUIContextEvents* events = &p_GUIContext->events;

	//reset clicked element
	K15_GUIElement* clickedElement = K15_InternalGUIGetElement(p_GUIContext, p_GUIContext->clickedElementIdHash);

	if (clickedElement)
	{
		clickedElement->flagMask &= ~K15_GUI_ELEMENT_CLICKED;
	}

	p_GUIContext->clickedElementIdHash = 0;

	K15_InternalGUIHandleSystemEvents(p_GUIContext, events);
	K15_InternalGUIHandleMouseInput(p_GUIContext, events);
	K15_InternalGUIHandleKeyboardInput(p_GUIContext, events);
}
/*********************************************************************************/
intern void K15_InternalSetGUIRectCoordinates(K15_GUIRectangle* p_GUIRectangle,
	int16* p_PosLeft, int16* p_PosTop, uint16* p_Width, uint16* p_Height)
{
	if (p_PosLeft)
	{
		p_GUIRectangle->pixelPosLeft = *p_PosLeft;
	}

	if (p_PosTop)
	{
		p_GUIRectangle->pixelPosTop = *p_PosTop;
	}

	if (p_Width)
	{
		p_GUIRectangle->pixelPosRight = p_GUIRectangle->pixelPosLeft + *p_Width;
	}

	if (p_Height)
	{
		p_GUIRectangle->pixelPosBottom = p_GUIRectangle->pixelPosTop + *p_Height;
	}
}
/*********************************************************************************/
intern void K15_InternalRetrieveGUIRectCoordinates(K15_GUIRectangle* p_GUIRectangle,
	int16* p_PosLeft, int16* p_PosTop, uint16* p_Width, uint16* p_Height)
{
	if (p_PosLeft)
	{
		*p_PosLeft = p_GUIRectangle->pixelPosLeft;
	}

	if (p_PosTop)
	{
		*p_PosTop = p_GUIRectangle->pixelPosTop;
	}

	if (p_Width)
	{
		*p_Width = (p_GUIRectangle->pixelPosRight - p_GUIRectangle->pixelPosLeft);
	}

	if (p_Height)
	{
		*p_Height = (p_GUIRectangle->pixelPosBottom - p_GUIRectangle->pixelPosTop);
	}
}
/*********************************************************************************/
intern void K15_InternalCalculateSizeHint(K15_RenderFontDesc* p_Font, const char* p_Text, uint32 p_TextLength,
	uint16* p_WidthHintOut, uint16* p_HeightHintOut,
	uint16 p_PaddingLeft = 0, uint16 p_PaddingRight = 0,
	uint16 p_PaddingTop = 0, uint16 p_PaddingBottom = 0)
{
	float textWidth = 0.f;
	float textHeight = 0.f;
	K15_GetTextSizeInPixels(p_Font, &textWidth, &textHeight, p_Text, p_TextLength);

	if (p_WidthHintOut)
		*p_WidthHintOut = p_PaddingRight + p_PaddingLeft + textWidth;

	if (p_HeightHintOut)
		*p_HeightHintOut = p_PaddingTop + p_PaddingBottom + textHeight;
}
/*********************************************************************************/
intern K15_GUIElement* K15_InternalAddUnalignedGUIElement(K15_GUIContext* p_GUIContext,
	K15_GUIElementType p_GUIElementType, int16* p_PosLeft, int16* p_PosTop,
	uint16* p_Width, uint16* p_Height, uint16 p_WidthHint, uint16 p_HeightHint,
	const char* p_Identifier, uint16 p_MinWidth = 0, uint16 p_MinHeight = 0)
{
	K15_ASSERT(p_GUIContext->memoryCurrentSizeInBytes <= p_GUIContext->memoryMaxSizeInBytes);
	//so what do we need to do here?
	// - Add GUI Element to GUI Context (so we can iterate over it)
	// - Retrieve 'old' GUI Element (so we can retrieve the information (clicked or not etc.)
	// - Add GUI Element Rect to layout
	uint32 identifierHash = K15_GenerateStringHash(p_Identifier);

	//Add element to gui memory buffer
	K15_GUIElement* element = (K15_GUIElement*)(p_GUIContext->memoryBuffer + p_GUIContext->memoryCurrentSizeInBytes);
	element->identifierHash = identifierHash;
	element->type = p_GUIElementType;
	element->offsetInBytes = p_GUIContext->memoryCurrentSizeInBytes;
	element->sizeInBytes = sizeof(K15_GUIElement);
	element->sizeHint.height = p_HeightHint;
	element->sizeHint.width = p_WidthHint;
	element->minSize.height = p_MinHeight;
	element->minSize.width = p_MinWidth;

	if (p_GUIContext->layoutIndex > 0)
	{
		element->flagMask |= K15_GUI_ELEMENT_LAYOUTED;
	}

	p_GUIContext->memoryCurrentSizeInBytes += sizeof(K15_GUIElement);

	//try to retrieve the retained informations from the gui element
	K15_GUIElement* retainedElement = (K15_GUIElement*)K15_InternalGUIGetRetainedElement(p_GUIContext, identifierHash);

	if (retainedElement)
	{
		if (retainedElement->flagMask & K15_GUI_ELEMENT_LAYOUTED)
		{
			element->rect = retainedElement->rect;
			K15_InternalRetrieveGUIRectCoordinates(&element->rect, p_PosLeft, p_PosTop, p_Width, p_Height);
		}
		else
		{
			K15_InternalSetGUIRectCoordinates(&element->rect, p_PosLeft, p_PosTop, p_Width, p_Height);
		}
		element->flagMask = retainedElement->flagMask;
	}
	else
	{
		element->flagMask = 0;
		K15_InternalSetGUIRectCoordinates(&element->rect, p_PosLeft, p_PosTop, p_Width, p_Height);
	}

	K15_InternalGUIAddGUISizeHintsToTopLayout(p_GUIContext, &element->rect,
		element->sizeHint, element->minSize);

	return element;
}
/*********************************************************************************/
intern K15_GUIElement* K15_InternalAddAlignedGUIElement(K15_GUIContext* p_GUIContext,
	K15_GUIElementType p_GUIElementType, uint16 p_WidthHint, uint16 p_HeightHint,
	const char* p_Identifier, uint16 p_MinWidth = 0, uint16 p_MinHeight = 0)
{
	return K15_InternalAddUnalignedGUIElement(p_GUIContext, p_GUIElementType, 0, 0, 0, 0,
		p_WidthHint, p_HeightHint, p_Identifier, p_MinWidth, p_MinHeight);
}
/*********************************************************************************/
intern byte* K15_InternalAddGUIElementMemory(K15_GUIContext* p_GUIContext, K15_GUIElement* p_GUIElement,
	uint32 p_SizeMemoryInBytes)
{
	//byte* retainedBuffer = K15_InternalGUIGetRetainedDataBuffer(p_GUIContext);
	uint32 offsetInBytes = p_GUIElement->offsetInBytes + p_GUIElement->sizeInBytes;

	K15_ASSERT(offsetInBytes + p_SizeMemoryInBytes <= p_GUIContext->memoryMaxSizeInBytes);

	byte* elementMemory = p_GUIContext->memoryBuffer + offsetInBytes;

	p_GUIElement->sizeInBytes += p_SizeMemoryInBytes;
	p_GUIContext->memoryCurrentSizeInBytes += p_SizeMemoryInBytes;

	return elementMemory;
}
/*********************************************************************************/
intern K15_GUILayout* K15_InternalGUIPushLayout(K15_GUIContext* p_GUIContext, K15_GUIRectangle p_LayoutArea,
	K15_GUILayoutType p_LayoutType)
{
	++p_GUIContext->numLayouts;
	uint32 layoutIndex = p_GUIContext->layoutIndex++;
	K15_ASSERT(layoutIndex != K15_GUI_MAX_LAYOUTS);

	K15_GUILayout* layout = p_GUIContext->layoutStack + layoutIndex;
	layout->layoutRectangle = p_LayoutArea;
	layout->type = p_LayoutType;
	layout->numElements = 0;

	return layout;
}
/*********************************************************************************/
intern K15_GUIElement* K15_InternalGUIMenuItemBase(K15_GUIContext* p_GUIContext, K15_GUIElementType p_ElementType,
	const char* p_Text, const char* p_Identifier, K15_GUIMenuItemStyle* p_MenuItemStyle)
{
	uint32 textLength = (uint32)strlen(p_Text);
	uint32 verticalPixelPadding = p_MenuItemStyle->verticalPixelPadding;
	uint32 horizontalPixelPadding = p_MenuItemStyle->horizontalPixelPadding;
	K15_RenderFontDesc* font = p_MenuItemStyle->font;

	uint16 widthHint = 0;
	uint16 heightHint = 0;

	K15_InternalCalculateSizeHint(font, p_Text, textLength, &widthHint, &heightHint,
		horizontalPixelPadding, horizontalPixelPadding,
		verticalPixelPadding, verticalPixelPadding);

	K15_GUIElement* menuItemElement = K15_InternalAddAlignedGUIElement(p_GUIContext, p_ElementType,
		widthHint, heightHint, p_Identifier);

	void* menuItemDataBuffer = K15_InternalAddGUIElementMemory(p_GUIContext,
		menuItemElement, sizeof(K15_GUIMenuItemData));
	char* menuItemTextBuffer = (char*)K15_InternalAddGUIElementMemory(p_GUIContext,
		menuItemElement, textLength);

	K15_GUIMenuItemData menuItemData = {};
	menuItemData.text = menuItemTextBuffer;
	menuItemData.textLength = textLength;
	menuItemData.menuItemStyle = p_MenuItemStyle;

	memcpy(menuItemTextBuffer, p_Text, textLength);
	memcpy(menuItemDataBuffer, &menuItemData, sizeof(K15_GUIMenuItemData));

	return menuItemElement;
}
/*********************************************************************************/




/*********************************************************************************/
kg_result K15_CreateGUIContext(K15_GUIContext* p_OutGUIContext);
{
	kg_byte* guiMemory = (kg_byte*)malloc(K15_GUI_MIN_MEMORY_SIZE_IN_BYTES);

	if (!guiMemory)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	return K15_CreateGUIContextWithCustomAllocator();
}
/*********************************************************************************/
kg_result K15_CreateGUIContextWithCustomMemory(K15_GUIContext* p_OutGUIContext,
	kg_byte* p_Memory, kg_u32 p_MemorySizeInBytes)
{
	if (!p_Memory)
		return K15_GUI_RESULT_OUT_OF_MEMORY;

	if (p_MemorySizeInBytes < K15_GUI_MIN_MEMORY_SIZE_IN_BYTES)
		return K15_GUI_RESULT_NOT_ENOUGH_MEMORY;

	kg_byte* guiMemory = p_Memory;
	kg_u32 guiMemorySizeInBytes = p_MemorySizeInBytes;

	K15_GUIContext* guiContext = (K15_GUIContext*)guiMemory;
	guiMemory += sizeof(K15_GUIContext);
	guiMemorySizeInBytes -= sizeof(K15_GUIContext);

	//nullify the rest of the memory
	memset(guiMemory, 0, guiMemorySizeInBytes);

	guiContext->memoryBufferSizeInBytes = guiMemorySizeInBytes;
	guiContext->memoryBufferCapacityInBytes = guiMemorySizeInBytes;
	guiContext->focusedElementIdHash = 0;
	guiContext->hoveredElementIdHash = 0;
	guiContext->clickedElementIdHash = 0;
	guiContext->mouseDownElementIdHash = 0;
	guiContext->layoutIndex = 0;
	guiContext->numLayouts = 0;
	guiContext->numMenus = 0;
	guiContext->activatedElementIdHash = 0;
	guiContext->memoryBuffer = guiMemory;
	guiContext->style = K15_InternalCreateDefaultStyle();
	guiContext->events.numBufferedKeyboardInputs = 0;
	guiContext->events.numBufferedMouseInputs = 0;
	guiContext->windowHeight = 0;
	guiContext->windowWidth = 0;
	guiContext->flagMask = 0;

	//assign newly created gui context
	*p_OutGUIContext = *guiContext;

	K15_GUILoadFont(&guiContext, "arial.ttf")

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
byte* K15_GUIGetGUIElementMemory(K15_GUIElement* p_GUIElement)
{
	return (byte*)(p_GUIElement + 1);
}
/*********************************************************************************/
void K15_GUIBeginDockingArea(K15_GUIContext* p_GUIContext, int16 p_PosX, int16 p_PosY,
	uint16 p_Width, uint16 p_Height, uint32 p_AllowedDockingAreasMask)
{

}
/*********************************************************************************/
void K15_GUIBeginToolBar(K15_GUIContext* p_GUIContext, const char* p_Identifier)
{
	K15_GUIBeginToolBarEX(p_GUIContext, p_Identifier, &p_GUIContext->style.toolBarStyle);
}
/*********************************************************************************/
void K15_GUIBeginToolBarEX(K15_GUIContext* p_GUIContext, const char* p_Identifier, K15_GUIToolBarStyle* p_ToolBarStyle)
{
	uint16 width = p_GUIContext->windowWidth;
	uint16 height = p_ToolBarStyle->pixelHeight;

	int16 posLeft = 0;
	int16 posTop = 0;
	uint16 posRight = width;
	uint16 posBottom = height;

	K15_GUIElement* guiElement = K15_InternalAddUnalignedGUIElement(p_GUIContext, K15_GUI_TOOLBAR,
		&posLeft, &posTop, &posRight, &posBottom, width, height, p_Identifier);

	K15_GUIToolBarData toolBarData = {};
	toolBarData.toolBarStyle = p_ToolBarStyle;

	void* toolBarDataBuffer = K15_InternalAddGUIElementMemory(p_GUIContext, guiElement, sizeof(K15_GUIToolBarData));
	memcpy(toolBarDataBuffer, &toolBarData, sizeof(K15_GUIToolBarData));

	K15_GUIPushHorizontalLayout(p_GUIContext, guiElement->rect, height);
}
/*********************************************************************************/
bool8 K15_GUIBeginWindow(K15_GUIContext* p_GUIContext, int16* p_PosX, int16* p_PosY,
	uint16* p_Width, uint16* p_Height, const char* p_Title, const char* p_Identifier)
{
	K15_GUIContextStyle* style = &p_GUIContext->style;
	return K15_GUIBeginWindowEX(p_GUIContext, p_PosX, p_PosY, p_Width, p_Height, p_Title,
		p_Identifier, &style->windowStyle);
}
/*********************************************************************************/
bool8 K15_GUIBeginWindowEX(K15_GUIContext* p_GUIContext, int16* p_PosX, int16* p_PosY,
	uint16* p_Width, uint16* p_Height, const char* p_Title, const char* p_Identifier,
	K15_GUIWindowStyle* p_GUIWindowStyle)
{
	K15_ASSERT((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_WINDOW_FLAG) == 0);

	p_GUIContext->flagMask |= K15_GUI_CONTEXT_INSIDE_WINDOW_FLAG;

	K15_GUIElement* windowElement = K15_InternalAddUnalignedGUIElement(p_GUIContext, K15_GUI_WINDOW,
		p_PosX, p_PosY, p_Width, p_Height, *p_Width, *p_Height, p_Identifier);

	if (windowElement->flagMask & K15_GUI_ELEMENT_MOUSE_DOWN)
	{
		*p_PosX += p_GUIContext->events.mouseDeltaX;
		*p_PosY += p_GUIContext->events.mouseDeltaY;
	}

	uint32 sizeElementMemoryInBytes = sizeof(K15_GUIWindowData);
	uint32 titleLength = (uint32)strlen(p_Title);

	byte* windowElementMemory = K15_InternalAddGUIElementMemory(p_GUIContext, windowElement, sizeElementMemoryInBytes);
	char* titleMemory = (char*)K15_InternalAddGUIElementMemory(p_GUIContext, windowElement, titleLength);

	K15_GUIWindowData windowData = {};
	windowData.style = p_GUIWindowStyle;
	windowData.textLength = titleLength;
	windowData.title = titleMemory;
	windowData.contentRect = windowElement->rect;
	windowData.contentRect.pixelPosTop += 20;

	memcpy(titleMemory, p_Title, titleLength);
	memcpy(windowElementMemory, &windowData, sizeof(K15_GUIWindowData));

	//Add layout for this window
	K15_GUIPushHorizontalLayout(p_GUIContext, windowData.contentRect, 0);

	return K15_TRUE;
}
/*********************************************************************************/
bool8 K15_GUIBeginMenu(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier)
{
	return K15_GUIBeginMenuEX(p_GUIContext, p_MenuText, p_Identifier, &p_GUIContext->style.menuStyle);
}
/*********************************************************************************/
bool8 K15_GUIBeginMenuEX(K15_GUIContext* p_GUIContext, const char* p_MenuText, const char* p_Identifier,
	K15_GUIMenuStyle* p_MenuStyle)
{
	bool8 insideMenu = (p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_MENU_FLAG) > 0;

	uint32 verticalPixelPadding = p_MenuStyle->verticalPixelPadding;
	uint32 horizontalPixelPadding = p_MenuStyle->horizontalPixelPadding;
	uint32 textLength = (uint32)strlen(p_MenuText);
	K15_RenderFontDesc* font = p_MenuStyle->font;

	uint16 widthHint = 0;
	uint16 heightHint = 0;

	K15_InternalCalculateSizeHint(font, p_MenuText, textLength,
		&widthHint, &heightHint, horizontalPixelPadding, horizontalPixelPadding,
		verticalPixelPadding, verticalPixelPadding);

	K15_GUIElement* menuElement = K15_InternalAddAlignedGUIElement(p_GUIContext, K15_GUI_MENU,
		widthHint, heightHint, p_Identifier);
	bool8 active = K15_FALSE;

	if (!insideMenu)
		active = (menuElement->flagMask & K15_GUI_ELEMENT_FOCUSED) > 0;
	else
		active = (menuElement->flagMask & K15_GUI_ELEMENT_HOVERED) > 0;

	uint32 sizeMenuDataInBytes = sizeof(K15_GUIMenuData);

	byte* menuElementMemory = (byte*)K15_InternalAddGUIElementMemory(p_GUIContext, menuElement, sizeMenuDataInBytes);
	char* textMemory = (char*)K15_InternalAddGUIElementMemory(p_GUIContext, menuElement, textLength);

	K15_GUIMenuData menuData = {};
	menuData.menuStyle = p_MenuStyle;
	menuData.textLength = textLength;
	menuData.title = textMemory;
	menuData.expanded = active;
	menuData.subMenu = insideMenu;
	memcpy(menuElementMemory, &menuData, sizeof(K15_GUIMenuData));
	memcpy(textMemory, p_MenuText, textLength);

	if (active)
	{
		p_GUIContext->flagMask |= K15_GUI_CONTEXT_INSIDE_MENU_FLAG;
		p_GUIContext->numMenus += 1;

		K15_GUIRectangle menuLayoutRect = {};
		uint32 menuWidth = 150;
		uint32 menuHeight = 200;
		uint32 fixedElementWidth = 150;

		if (insideMenu)
		{
			menuLayoutRect.pixelPosLeft = menuElement->rect.pixelPosRight;
			menuLayoutRect.pixelPosTop = menuElement->rect.pixelPosTop;
		}
		else
		{
			menuLayoutRect.pixelPosLeft = menuElement->rect.pixelPosLeft;
			menuLayoutRect.pixelPosTop = menuElement->rect.pixelPosBottom;
		}

		menuLayoutRect.pixelPosBottom = menuElement->rect.pixelPosLeft + menuHeight;
		menuLayoutRect.pixelPosRight = menuElement->rect.pixelPosBottom + menuWidth;
		K15_GUIPushVerticalLayout(p_GUIContext, menuLayoutRect, fixedElementWidth);
	}

	return active;
}
/*********************************************************************************/
bool8 K15_GUIMenuItem(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier)
{
	return K15_GUIMenuItemEX(p_GUIContext, p_ItemText, p_Identifier, &p_GUIContext->style.menuItemStyle);
}
/*********************************************************************************/
bool8 K15_GUIMenuItemEX(K15_GUIContext* p_GUIContext, const char* p_ItemText, const char* p_Identifier,
	K15_GUIMenuItemStyle* p_MenuItemStyle)
{
	K15_ASSERT((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_MENU_FLAG) > 0);
	K15_GUIElement* menuItemElement = K15_InternalGUIMenuItemBase(p_GUIContext, K15_GUI_MENU_ITEM, p_ItemText,
		p_Identifier, p_MenuItemStyle);

	bool8 active = menuItemElement->flagMask & K15_GUI_ELEMENT_CLICKED;

	return active;
}
/*********************************************************************************/
bool8 K15_GUIButton(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier)
{
	K15_GUIButtonStyle* defaultButtonStyle = &p_GUIContext->style.buttonStyle;
	return K15_GUIButtonEX(p_GUIContext, p_ButtonText, p_Identifier, defaultButtonStyle);
}
/*********************************************************************************/
bool8 K15_GUIButtonEX(K15_GUIContext* p_GUIContext, const char* p_ButtonText, const char* p_Identifier,
	K15_GUIButtonStyle* p_GUIButtonStyle)
{
	uint32 textLength = (uint32)strlen(p_ButtonText);
	uint32 sizeButtonDataInBytes = sizeof(K15_GUIButtonData);
	uint32 horizontalPixelPadding = p_GUIButtonStyle->horizontalPixelPadding + p_GUIButtonStyle->borderPixelThickness;
	uint32 verticalPixelPadding = p_GUIButtonStyle->verticalPixelPadding + p_GUIButtonStyle->borderPixelThickness;

	K15_RenderFontDesc* font = p_GUIButtonStyle->font;

	uint16 widthHint = 0;
	uint16 heightHint = 0;
	K15_InternalCalculateSizeHint(font, p_ButtonText, textLength, &widthHint, &heightHint,
		horizontalPixelPadding, horizontalPixelPadding, verticalPixelPadding, verticalPixelPadding);

	K15_GUIElement* buttonElement = K15_InternalAddAlignedGUIElement(p_GUIContext, K15_GUI_BUTTON,
		heightHint, widthHint, p_Identifier);

	bool8 active = buttonElement->flagMask & K15_GUI_ELEMENT_CLICKED;

	byte* buttonElementMemory = (byte*)K15_InternalAddGUIElementMemory(p_GUIContext,
		buttonElement, sizeButtonDataInBytes);
	char* textMemory = (char*)K15_InternalAddGUIElementMemory(p_GUIContext, buttonElement, textLength);

	K15_GUIButtonData buttonData = {};
	buttonData.style = p_GUIButtonStyle;
	buttonData.textLength = textLength;
	buttonData.text = textMemory;

	memcpy(buttonElementMemory, &buttonData, sizeof(K15_GUIButtonData));
	memcpy(textMemory, p_ButtonText, textLength);

	return active;
}
/*********************************************************************************/
void K15_GUILabel(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier)
{
	K15_GUILabelEX(p_GUIContext, p_LabelText, p_Identifier, &p_GUIContext->style.labelStyle);
}
/*********************************************************************************/
void K15_GUILabelEX(K15_GUIContext* p_GUIContext, const char* p_LabelText, const char* p_Identifier,
	K15_GUILabelStyle* p_GUILabelStyle)
{
	uint32 textLength = (uint32)strlen(p_LabelText);
	uint16 widthHint = 0;
	uint16 heightHint = 0;

	K15_RenderFontDesc* font = p_GUILabelStyle->font;
	K15_InternalCalculateSizeHint(font, p_LabelText, textLength, &widthHint, &heightHint);

	K15_GUIElement* labelElement = K15_InternalAddAlignedGUIElement(p_GUIContext, K15_GUI_LABEL,
		widthHint, heightHint, p_Identifier);

	byte* labelElementMemory = (byte*)K15_InternalAddGUIElementMemory(p_GUIContext, labelElement,
		sizeof(K15_GUILabelData));

	char* textMemory = (char*)K15_InternalAddGUIElementMemory(p_GUIContext, labelElement, textLength);

	K15_GUILabelData labelData = {};
	labelData.style = p_GUILabelStyle;
	labelData.textLength = textLength;
	labelData.text = textMemory;

	memcpy(labelElementMemory, &labelData, sizeof(K15_GUILabelData));
	memcpy(textMemory, p_LabelText, textLength);
}
/*********************************************************************************/
void K15_GUIPushVerticalLayout(K15_GUIContext* p_GUIContext, K15_GUIRectangle p_LayoutArea,
	uint16 p_FixedWidthPerElement)
{
	K15_GUILayout* layout = K15_InternalGUIPushLayout(p_GUIContext, p_LayoutArea, K15_GUI_VERTICAL_LAYOUT);
	layout->params.fixedWidthPerElement = p_FixedWidthPerElement;
}
/*********************************************************************************/
void K15_GUIPushHorizontalLayout(K15_GUIContext* p_GUIContext, K15_GUIRectangle p_LayoutArea,
	uint16 p_FixedHeightPerElement)
{
	K15_GUILayout* layout = K15_InternalGUIPushLayout(p_GUIContext, p_LayoutArea, K15_GUI_HORIZONTAL_LAYOUT);
	layout->params.fixedHeightPerElement = p_FixedHeightPerElement;
}
/*********************************************************************************/
void K15_GUIPopLayout(K15_GUIContext* p_GUIContext)
{
	K15_ASSERT(p_GUIContext->layoutIndex);
	p_GUIContext->layoutIndex--;
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
void K15_GUIEndDockingArea(K15_GUIContext* p_GUIContext)
{

}
/*********************************************************************************/
void K15_GUIEndToolBar(K15_GUIContext* p_GUIContext)
{
	K15_GUIPopLayout(p_GUIContext);
}
/*********************************************************************************/
intern void K15_InternalGUIAlignElements(K15_GUILayout* p_Layouts, uint16 p_NumLayouts)
{
	for (uint16 layoutIndex = 0;
		layoutIndex < p_NumLayouts;
		++layoutIndex)
	{
		K15_GUILayout* layout = p_Layouts + layoutIndex;
		K15_GUILayoutType type = layout->type;
		uint16 numElements = layout->numElements;
		uint16 layoutWidth = layout->layoutRectangle.pixelPosRight - layout->layoutRectangle.pixelPosLeft;
		uint16 layoutHeight = layout->layoutRectangle.pixelPosBottom - layout->layoutRectangle.pixelPosTop;
		uint16 layoutPosX = layout->layoutRectangle.pixelPosLeft;
		uint16 layoutPosY = layout->layoutRectangle.pixelPosTop;
		uint16 offsetX = 0;
		uint16 offsetY = 0;

		if (numElements == 0)
		{
			continue;
		}

		for (uint16 elementIndex = 0;
			elementIndex < numElements;
			++elementIndex)
		{
			K15_GUISizeHint* sizeHint = layout->elementSizeHints + elementIndex;
			K15_GUIRectangle* sizeHintRect = sizeHint->rect;
			sizeHint->rect->pixelPosLeft = layoutPosX + offsetX;
			sizeHint->rect->pixelPosTop = layoutPosY + offsetY;

			//get the hint 
			uint16 elementWidthHint = sizeHint->dimHint.width;
			uint16 elementHeightHint = sizeHint->dimHint.height;

			//get the min size
			uint16 elementMinWidth = sizeHint->dimMin.width;
			uint16 elementMinHeight = sizeHint->dimMin.height;

			//how much space is left?
			uint16 elementWidthFit = (layoutWidth / (numElements - elementIndex));
			uint16 elementHeightFit = (layoutHeight / (numElements - elementIndex));

			//if there's enough space, use the size provided by the hint.
			//otherwise use something in the range [minSize, sizeHint)
			uint16 elementWidth = elementWidthFit < elementWidthHint ?
				elementWidthHint - elementWidthFit : elementWidthHint;

			uint16 elementHeight = elementHeightFit < elementHeightHint ?
				elementHeightHint - elementHeightFit : elementHeightHint;

			elementWidth = K15_MAX(elementMinWidth, elementWidth);
			elementHeight = K15_MAX(elementMinHeight, elementHeight);

			switch (type)
			{
			case K15_GUI_VERTICAL_LAYOUT:

				if (layout->params.fixedHeightPerElement > 0)
					elementWidth = layout->params.fixedHeightPerElement;

				sizeHintRect->pixelPosRight = sizeHintRect->pixelPosLeft + elementWidth;
				sizeHintRect->pixelPosBottom = sizeHintRect->pixelPosTop + elementHeight;
				offsetY += elementHeight;
				layoutHeight -= elementHeight;
				break;

			case K15_GUI_HORIZONTAL_LAYOUT:
				if (layout->params.fixedWidthPerElement > 0)
					elementHeight = layout->params.fixedWidthPerElement;

				sizeHintRect->pixelPosRight = sizeHintRect->pixelPosLeft + elementWidth;
				sizeHintRect->pixelPosBottom = sizeHintRect->pixelPosTop + elementHeight;
				offsetX += elementWidth;
				layoutWidth -= elementWidth;
				break;
			}
		}
	}
}
/*********************************************************************************/
void K15_GUIFinishGUIFrame(K15_GUIContext* p_GUIContext)
{
	K15_InternalGUIAlignElements(p_GUIContext->layoutStack, p_GUIContext->numLayouts);
	K15_InternalGUIHandleInput(p_GUIContext);

	K15_ASSERT((p_GUIContext->flagMask & K15_GUI_CONTEXT_INSIDE_MENU_FLAG) == 0);

	p_GUIContext->layoutIndex = 0;
	p_GUIContext->numLayouts = 0;
	p_GUIContext->memoryCurrentSizeInBytes = 0;
}
/*********************************************************************************/
intern void K15_InternalIterateGUIElements(K15_GUIContext* p_GUIContext,
	byte* p_Buffer, uint32 p_BufferSizeInBytes, K15_GUIIteratorFnc p_Function, void* p_UserData)
{
	uint32 offsetInBytes = 0;

	while (offsetInBytes < p_BufferSizeInBytes)
	{
		K15_GUIElement* element = (K15_GUIElement*)(p_Buffer + offsetInBytes);
		p_Function(p_GUIContext, element, p_UserData);

		offsetInBytes += element->sizeInBytes;
	}
}
/*********************************************************************************/
void K15_GUIIterateElements(K15_GUIContext* p_GUIContext, K15_GUIIteratorFnc p_Function, void* p_UserData)
{
	K15_InternalIterateGUIElements(p_GUIContext, p_GUIContext->memoryBuffer, p_GUIContext->memoryCurrentSizeInBytes,
		p_Function, p_UserData);
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


#endif //_K15_GUILayer_Context_h_
#ifndef _K15_GUILayer_Context_h_
#define _K15_GUILayer_Context_h_

#ifndef K15_GUI_STATIC
# define kg_def static
#else
# define kg_def extern
#endif //K15_GUI_STATIC

#ifndef kg_true
# define kg_true 1
#endif

#ifndef kg_false
# define kg_false 0
#endif

typedef unsigned long long 	kg_u64;
typedef unsigned int 		kg_u32;
typedef unsigned short 		kg_u16;
typedef unsigned char		kg_u8;
typedef float 				kg_f32;

typedef long long 			kg_s64;
typedef int 				kg_s32;
typedef short 				kg_s16;
typedef char 				kg_s8;

typedef char 				kg_utf8;
typedef unsigned int 		kg_crc32;
typedef unsigned int 		kg_color32;
typedef unsigned char 		kg_byte;
typedef unsigned char 		kg_bool;

/*********************************************************************************/
typedef enum 
{
	K15_GUI_RESULT_SUCCESS 						= 0,
	K15_GUI_RESULT_OUT_OF_MEMORY 				= 1,
	K15_GUI_RESULT_FONT_DATA_ERROR 				= 2,
	K15_GUI_RESULT_NOT_SUPPORTED 				= 3,
	K15_GUI_RESULT_FILE_NOT_FOUND 				= 4,
	K15_GUI_RESULT_ARRAY_EMPTY					= 5,
	K15_GUI_RESULT_INVALID_ARGUMENTS 			= 6,
	K15_GUI_RESULT_OUT_OF_BOUNDS 				= 7,
	K15_GUI_RESULT_NAME_ALREADY_IN_USE 			= 8,
	K15_GUI_RESULT_RESOURCE_NOT_FOUND 			= 9,
	K15_GUI_RESULT_IMAGE_DATA_ERROR 			= 10,
	K15_GUI_RESULT_FILE_FORMAT_NOT_SUPPORTED 	= 11,
	K15_GUI_RESULT_TOO_MANY_ICONS 				= 12,
	K15_GUI_RESULT_NO_ICONS 					= 13,
	K15_GUI_RESULT_HASH_CONFLICT 				= 14,
	K15_GUI_RESULT_FRAME_NOT_FINISHED 			= 15,
	K15_GUI_RESULT_FRAME_NOT_STARTED 			= 16,
	K15_GUI_RESULT_ELEMENT_NOT_STARTED 			= 17,
	K15_GUI_RESULT_ELEMENT_NOT_FINISHED 		= 18,
	K15_GUI_RESULT_DRAW_COMMAND_FINISHED 		= 19,
	K15_GUI_RESULT_NEED_MORE_MEMORY 			= 20,
	K15_GUI_RESULT_INVALID_CONTEXT_PARAMETER 	= 21,
	K15_GUI_RESULT_UNKNOWN_ERROR 
} kg_result;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_INPUT_TYPE_MOUSE_BUTTON_PRESSED = 0,
	K15_GUI_INPUT_TYPE_MOUSE_BUTTON_RELEASED,
	K15_GUI_INPUT_TYPE_MOUSE_WHEEL_UP,
	K15_GUI_INPUT_TYPE_MOUSE_WHEEL_DOWN,
	K15_GUI_INPUT_TYPE_MOUSE_MOVE,

	K15_GUI_INPUT_TYPE_KEY_PRESSED,
	K15_GUI_INPUT_TYPE_KEY_RELEASED,

	K15_GUI_INPUT_TYPE_WINDOW_RESIZED,

	K15_GUI_INPUT_TYPE_COUNT

} kg_input_type;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_WINDOW_COMPONENT = 0,
	K15_GUI_COMPONENT_COUNT
} kg_component_type;

/*********************************************************************************/
typedef enum 
{
	K15_GUI_MOUSE_BUTTON_LEFT = 0,
	K15_GUI_MOUSE_BUTTON_RIGHT,
	K15_GUI_MOUSE_BUTTON_MIDDLE,
	K15_GUI_MOUSE_BUTTON_SPECIAL1,
	K15_GUI_MOUSE_BUTTON_SPECIAL2
} kg_mouse_button_type;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_CTRL_MODIFIER 	= 0x01,
	K15_GUI_L_ALT_MODIFIER 	= 0x02,
	K15_GUI_R_ALT_MODIFIER 	= 0x04,
	K15_GUI_SHIFT_MODIFIER 	= 0x08
} kg_keyboard_modifier_type;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_KEY_RETURN = 0,
	K15_GUI_KEY_BACK,
	K15_GUI_KEY_TAB,
	K15_GUI_KEY_DEL,
	K15_GUI_KEY_PGDOWN,
	K15_GUI_KEY_PGUP,
	K15_GUI_KEY_HOME,
	K15_GUI_KEY_END,
	K15_GUI_KEY_INS,
	K15_GUI_KEY_ESC,

	K15_GUI_KEY_ALT,
	K15_GUI_KEY_SHIFT,
	K15_GUI_KEY_CTRL,

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
} kg_keyboard_key_type;
/*********************************************************************************/
typedef enum
{
	K15_GUI_ACTION_BUTTON_DOWN = 0,
	K15_GUI_ACTION_BUTTON_UP
} kg_input_action_type;
/*********************************************************************************/
typedef enum
{
	K15_GUI_LAYOUT_VERTICAL = 0,
	K15_GUI_LAYOUT_HORIZONTAL
} kg_layout_type;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_POSITION_ATTRIBUTE_TYPE = 0,
	K15_GUI_TEXCOORD_ATTRIBUTE_TYPE,
	K15_GUI_COLOR_ATTRIBUTE_TYPE
} kg_vertex_attribute_type;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_FLOAT2_DATA_TYPE = 0,
	K15_GUI_FLOAT4_DATA_TYPE
} kg_vertex_attribute_data_type;
/*********************************************************************************/
typedef struct 
{
	kg_byte* 	pMemory;
	kg_u32 		sizeInBytes;
	kg_u32 		capacityInBytes;
	void* 		pFirstHandle;
	void*		pLastHandle;
} kg_buffer;
/*********************************************************************************/
typedef struct
{
	float x;
	float y;
} kg_float2;
/*********************************************************************************/
typedef struct
{
	float x;
	float y;
	float z;
	float w;
} kg_float4;
/*********************************************************************************/
typedef struct
{
	kg_u32 x;
	kg_u32 y;
} kg_uint2;
/*********************************************************************************/
typedef struct
{
	kg_s32 x;
	kg_s32 y;
} kg_sint2;
/*********************************************************************************/
typedef struct
{
	void*	pNextHandle;
	void* 	pPreviousHandle;
	kg_u32 	offset;
	kg_u32 	sizeInBytes;
} kg_data_handle;
/*********************************************************************************/
typedef struct
{
	const kg_data_handle* 	pDataHandle;
	kg_buffer*				pBuffer;
	size_t 					elementSizeInBytes;
	kg_u32 					capacity;
	kg_u32 					size;
} kg_array;
/*********************************************************************************/
typedef struct
{
#ifdef K15_GUI_STORE_IDENTIFIER_STRING
	const char* pIdentifier;
#endif
	kg_array 				childArray;
	const kg_data_handle*	componentHandles[K15_GUI_COMPONENT_COUNT];
	kg_layout_type			layout;
	kg_u32 					frameUseCounter;
	kg_crc32 				identifier;
	kg_float2				position;
	kg_float2				size;
	kg_float2				minSize;
	kg_float2				maxSize;
	kg_float2				prefSize;
	kg_float2				offset;
	kg_float4				margin;
	kg_float4				padding;
	kg_float4				border;
} kg_element;
/*********************************************************************************/
typedef struct 
{
	kg_element	element;
	void* 		pNext;
	kg_crc32 	key;
} kg_hash_map_bucket;
/*********************************************************************************/
typedef struct
{
	kg_buffer				bucketBuffer;
	kg_hash_map_bucket** 	pBuckets;
	kg_u32 					size;
	kg_u32					bucketCount;
} kg_hash_map;
/*********************************************************************************/
typedef struct 
{
	const char* pFunction;
	const char* pDescription;
	const char* pIdentifier;
	void* 		pPrevious;
	kg_result 	result;
} kg_error;
/*********************************************************************************/
typedef struct
{
	kg_buffer	errorBuffer;
	kg_error* 	pLastError;
} kg_error_stack;
/*********************************************************************************/
typedef struct 
{
	kg_sint2 position;
	kg_uint2 size;
} kg_rect;
/*********************************************************************************/
typedef struct
{
	union
	{
		struct 
		{
			kg_u16 x;
			kg_u16 y;
		} mouse_move;

		struct 
		{
			kg_u16 					x;
			kg_u16 					y;
			kg_mouse_button_type 	buttonType;
			kg_input_action_type	actionType;
		} mouse_button;

		struct 
		{
			kg_keyboard_key_type		key;
			kg_keyboard_modifier_type	modifier;
		} keyboard_button;
	} data;

	kg_input_type 	type;
	void* 			pNext;
} kg_input_event;
/*********************************************************************************/
typedef struct
{
	kg_buffer 		buffer;
	kg_input_event* pFirstEvent;
	kg_input_event* pLastEvent;
} kg_input_queue;
/*********************************************************************************/
typedef struct 
{
	int left;
	int top;
	int right;
	int bottom;
} kg_viewport;
/*********************************************************************************/
typedef struct
{
	kg_hash_map* 			pElements;
} kg_window;
/*********************************************************************************/
typedef struct 
{
	kg_array				elementStack;
	kg_buffer 				memoryBuffer;
	kg_hash_map*			pElements;
	kg_element*				pRootElement;
	kg_error_stack* 		pErrorStack;
	kg_input_queue*			pInputQueue;
	kg_viewport				viewport;
	kg_u32 					frameCounter;
} kg_context;
/*********************************************************************************/
typedef struct 
{
	size_t value;
} kg_context_handle;
/*********************************************************************************/
typedef struct 
{
	kg_float2 origin;
	kg_float2 position;
	kg_float2 accumulatedSize;
	kg_float2 maxSize;
} kg_layout_state;
/*********************************************************************************/
typedef struct 
{
	kg_vertex_attribute_type 		type;
	kg_vertex_attribute_data_type	dataType;
	kg_u32							sizeInBytes;
	kg_u32							offset;
} kg_vertex_attribute_definition;
/*********************************************************************************/
typedef struct 
{
	kg_u32 							stride;
	kg_u32 							attributeCount;
	kg_vertex_attribute_definition 	attributes[3];
} kg_vertex_definition;
/*********************************************************************************/
typedef struct
{
	struct
	{
		void* 	pVertexMemory;
		void* 	pIndexMemory;
		size_t 	vertexMemorySize;
		size_t 	indexMemorySize;		
	} vertex_draw_data;

	void* 	pDataMemory;
	size_t 	dataMemorySize;
} kg_context_parameter;
/*********************************************************************************/
//how this should work:
// - Call gui logic (K15_GUIButton, K15_GUIBeginWindow, K15_GUIPushHorizontalLayout etc.)
// - Store elements internally in the gui context (just rects?) <-- headache
// - iterate over elements (layouting)
// - iterate over elements (input)
// - iterate over elements (rendering)
// - Call gui logic (next frame - retrieve results from last frame. Mainly results of the input)

//******************CONTEXT******************//
kg_def kg_context_parameter			kg_create_context_parameter();
kg_def kg_result 					kg_create_context(kg_context_handle* pOutHandle);
kg_def kg_result 					kg_create_context_with_custom_parameter(kg_context_handle* pOutHandle, const kg_context_parameter* pParameter, const char** pOutError);
kg_def kg_result 					kg_set_viewport(kg_context_handle contextHandle, const kg_viewport* pViewport);
kg_def kg_result					kg_get_viewport(kg_context_handle contextHandle, kg_viewport* pOutViewport);

//*****************CONTROLS******************//
kg_def kg_result 					kg_begin_frame(kg_context_handle contextHandle);
kg_def void 						kg_begin_toolbar(kg_context_handle contextHandle, const char* p_Identifier);
kg_def kg_bool 						kg_begin_window(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def kg_bool  					kg_begin_menu(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def kg_bool 						kg_button(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def void							kg_label(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def void							kg_separator(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def void							kg_end_menu(kg_context_handle contextHandle);
kg_def void							kg_end_window(kg_context_handle contextHandle);
kg_def void							kg_end_toolbar(kg_context_handle contextHandle);
kg_def kg_result 					kg_end_frame(kg_context_handle contextHandle);


//*****************INPUT******************//
kg_def kg_result					kg_add_input_mouse_move(kg_context_handle contextHandle, unsigned short x, unsigned short y);
kg_def kg_result 					kg_add_input_mouse_button_down(kg_context_handle contextHandle, unsigned short x, unsigned short y, kg_mouse_button_type mouseButtonType);
kg_def kg_result 					kg_add_input_mouse_button_up(kg_context_handle contextHandle, unsigned short x, unsigned short y, kg_mouse_button_type 			mouseButtonType);
kg_def kg_result					kg_add_input_key_button_down(kg_context_handle contextHandle, kg_keyboard_key_type buttonType);
kg_def kg_result					kg_add_input_key_button_up(kg_context_handle contextHandle, kg_keyboard_key_type buttonType);

//*****************UTIL******************//
kg_def unsigned int 				kg_convert_result_to_string(kg_result p_Result, char* pMessageBuffer, unsigned int messageBufferSizeInBytes);
kg_def kg_result 					kg_calculate_row_major_projection_matrix(float* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def kg_result 					kg_calculate_column_major_projection_matrix(float* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def kg_bool 						kg_pop_error(kg_context_handle contextHandle, kg_error** pOutError);


//****************RENDER*****************//
kg_def const kg_vertex_definition*	kg_get_vertex_definition();
kg_def kg_result					kg_get_render_data(kg_context_handle contextHandle, void** pOutRenderData, int* pOutRenderDataSizeInBytes);


//*****************DEBUG*****************//

kg_def const kg_color32 kg_color_white;
kg_def const kg_color32 kg_color_black;
kg_def const kg_color32 kg_color_light_red;
kg_def const kg_color32 kg_color_light_green;
kg_def const kg_color32 kg_color_light_blue;
kg_def const kg_color32 kg_color_light_grey;
kg_def const kg_color32 kg_color_dark_red;
kg_def const kg_color32 kg_color_dark_green;
kg_def const kg_color32 kg_color_dark_blue;
kg_def const kg_color32 kg_color_dark_grey;

#ifdef K15_GUI_IMPLEMENTATION

#define kg_internal static

#ifndef K15_GUI_STRIP_DEBUG_RENDERING
# define K15_GUI_STRIP_DEBUG_RENDERING 0
#endif //K15_GUI_STRIP_DEBUG_RENDERING

#ifndef K15_GUI_CUSTOM_ASSERT
# include "assert.h"
# define kg_assert(x) assert(x)
#else
# define kg_assert(x) K15_GUI_CUSTOM_ASSERT(x)
#endif //K15_GUI_CUSTOM_ASSERT

#ifndef K15_GUI_CUSTOM_MALLOC
# include "malloc.h"
# define kg_malloc(x, u) malloc(x)
#else
# ifndef K15_GUI_CUSTOM_FREE
#  error "K15_GUI_CUSTOM_MALLOC defined without matching K15_GUI_CUSTOM_FREE"
# endif //K15_GUI_CUSTOM_FREE
# define kg_malloc(x, u) K15_GUI_CUSTOM_MALLOC(x, u)
#endif //K15_GUI_CUSTOM_MALLOC

#ifndef K15_GUI_CUSTOM_FREE
# include "malloc.h"
# define kg_free(x, u) free(x)
#else
# ifndef K15_GUI_CUSTOM_MALLOC
#  error "K15_GUI_CUSTOM_FREE defined without matching K15_GUI_CUSTOM_MALLOC"
# endif //K15_GUI_CUSTOM_MALLOC
# define kg_free(x, u) K15_GUI_CUSTOM_FREE(x, u);
#endif //K15_GUI_CUSTOM_FREE

#ifndef K15_GUI_MEMSET
# include "string.h"
# define kg_memset(x, v, s) memset(x, v, s)
#else
# define kg_memset(x, v, s) K15_GUI_MEMSET(x, v, s)
#endif //K15_GUI_MEMSET

#ifndef K15_GUI_MEMCPY
# include "string.h"
# define kg_memcpy(d, s, si) memcpy(d, s, si)
#else
# define kg_memcpy(d, s, si) K15_GUI_MEMCPY(d, s, si)
#endif //K15_GUI_MEMCPY

#ifndef K15_GUI_MEMCMP
# include "string.h"
# define kg_memcmp(a, b, si) memcmp(a, b, si)
#else
# define kg_memcmp(a, b, si) K15_GUI_MEMCMP(a, b, si)
#endif //K15_GUI_MEMCMP

#ifndef K15_GUI_CLAMP
# define kg_clamp(v, min, max) ((v)>(max)?(max):(v)<(min)?(min):(v))
#else
# define kg_clamp(v, min, max) K15_GUI_CLAMP(v, min, max)
#endif //K15_GUI_CLAMP

#ifndef K15_GUI_MIN
# define kg_min(a, b) ((a)<(b)?(a):(b))
#else
# define kg_min(a, b) K15_GUI_MIN(a, b)
#endif //K15_GUI_MIN

#ifndef K15_GUI_MAX
# define kg_max(a, b) ((a)>(b)?(a):(b))
#else
# define kg_max(a, b) K15_GUI_MAX(a, b)
#endif //K15_GUI_MAX

kg_internal const kg_u32 kg_ptr_size_in_bytes = sizeof(void*);

#define kg_size_kilo_bytes(n) ((n)*1024)
#define kg_size_mega_bytes(n) ((n)*1024*1024)

#define kg_nullptr (void*)(0)

#define kg_set_error(err, str) if (err != kg_nullptr) {*err = str;}

typedef kg_u32 kg_code_point;

const kg_color32 kg_color_white 		= 0xFFFFFFFF;
const kg_color32 kg_color_black 		= 0x000000FF;
const kg_color32 kg_color_light_red		= 0xFF0000FF;
const kg_color32 kg_color_light_green	= 0x00FF00FF;
const kg_color32 kg_color_light_blue	= 0xFF00FFFF;
const kg_color32 kg_color_light_grey 	= 0xDDDDDDFF;
const kg_color32 kg_color_dark_red		= 0xDD0000FF;
const kg_color32 kg_color_dark_green	= 0x00DD00FF;
const kg_color32 kg_color_dark_blue		= 0x0000DDFF;
const kg_color32 kg_color_dark_grey		= 0x333333FF;

enum //constants
{
	//Window Component
	TitleHeightInPixels 	= 30u,
	MinAreaHeightInPixels 	= 10u,
	MinAreaWidthInPixels	= 10u
};


void kg_layout_pass(kg_element*);

typedef enum
{
	K15_GUI_WINDOW_FLAG_IS_OPEN 				= 0x001,
	K15_GUI_WINDOW_FLAG_IS_MAXIMIZED 			= 0x002,
	K15_GUI_WINDOW_FLAG_IS_MINIMIZED			= 0x004,
	K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED = 0x008,
	K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED = 0x010,
	K15_GUI_WINDOW_FLAG_CLOSE_BUTTON_CLICKED	= 0x020
} kg_window_flag;

typedef struct
{
	kg_u32			flags;
	kg_float2		originalSize;
	kg_float2		originalPosition;
	const kg_utf8* 	pText;
} kg_window_component;

/*********************************************************************************/
typedef struct
{
	kg_float4	position;
	kg_float2 	texcoord;
	kg_color32 	color;
} kg_render_vertex_data;
/*********************************************************************************/
typedef struct 
{
	kg_render_vertex_data* 	pVertexData;
	kg_u32					vertexCount;
	kg_bool 				dirty;
} kg_render_vertices;
/*********************************************************************************/

/*********************************************************************************/
enum
{
	VertexStride 		= sizeof(kg_render_vertex_data),
	IndexSize 			= sizeof(kg_u16),
	MinContextDataSize 	= kg_size_kilo_bytes(512)
};
/*********************************************************************************/
kg_internal const kg_context_parameter* kg_get_default_context_parameter()
{
	static kg_context_parameter defaultParameter;
	static const kg_u32 defaultVertexMemorySize = 4096u * VertexStride;
	static const kg_u32 defaultIndexMemorySize 	= 4096u * IndexSize;
	static const kg_u32 defaultDataMemorySize	= kg_size_mega_bytes(5);

	defaultParameter.vertex_draw_data.pVertexMemory 	= kg_malloc(defaultVertexMemorySize, kg_nullptr);
	defaultParameter.vertex_draw_data.pIndexMemory 		= kg_malloc(defaultIndexMemorySize, kg_nullptr);
	defaultParameter.pDataMemory						= kg_malloc(defaultDataMemorySize, kg_nullptr);
	defaultParameter.vertex_draw_data.vertexMemorySize 	= defaultVertexMemorySize;
	defaultParameter.vertex_draw_data.indexMemorySize 	= defaultIndexMemorySize;
	defaultParameter.dataMemorySize 					= defaultDataMemorySize;

	return &defaultParameter;
}
/*********************************************************************************/
kg_internal kg_bool kg_is_invalid_context_parameter(const kg_context_parameter* pParameter)
{
	if (pParameter == kg_nullptr)
	{
		return kg_true;
	}

	if (pParameter->vertex_draw_data.pVertexMemory == kg_nullptr ||
		pParameter->vertex_draw_data.vertexMemorySize == 0u)
	{
		return kg_true;
	}

	if (pParameter->vertex_draw_data.pIndexMemory == kg_nullptr ||
		pParameter->vertex_draw_data.indexMemorySize == 0u)
	{
		return kg_true;
	}

	if (pParameter->pDataMemory == kg_nullptr ||
		pParameter->dataMemorySize < MinContextDataSize)
	{
		return kg_true;
	}

	return kg_false;
}
/*********************************************************************************/


/*****************************UTF8-SUPPORT***************************************/
kg_internal kg_u32 kg_read_code_point(const kg_utf8* pUtf8Text, kg_code_point* pOutCodepoint)
{
	if (*pUtf8Text == 0)
	{
		return 0u;
	}

	if (( pUtf8Text[0u] & 0x80 ) == 0 )
	{
		*pOutCodepoint = pUtf8Text[ 0u ];
		return 1u;
	}
	else if ((pUtf8Text[0u] & 0xF0 ) == 0xF0 )
	{
		*pOutCodepoint = ( ( pUtf8Text[ 0u ] & 0x1F ) << 18u ) | ( pUtf8Text[ 1u ] & 0x3F ) << 12u | ( pUtf8Text[ 2u ] & 0x3F ) << 6u | ( pUtf8Text[ 3u ] & 0x3F );
		return 4u;
	}
	else if (( pUtf8Text[0u] & 0xE0 ) == 0xE0 )
	{
		*pOutCodepoint = ( ( pUtf8Text[ 0u ] & 0x1F ) << 12u ) | ( pUtf8Text[ 1u ] & 0x3F ) << 6u | ( pUtf8Text[ 2u ] & 0x3F );
		return 3u;
	}
	else if (( pUtf8Text[0u] & 0xC0 ) == 0xC0 )
	{
		*pOutCodepoint = ( ( pUtf8Text[0u] & 0x1F ) << 6u ) | ( pUtf8Text[1u] & 0x3F );
		return 2u;
	}

	return 0u;
}

kg_internal kg_float2 kg_float2_load(float x, float y)
{
	kg_float2 f2 = {x, y};
	return f2;
}

kg_internal kg_float2 kg_float2_zero()
{
	static const kg_float2 zero = {0.f, 0.f};
	return zero;
}

kg_internal kg_bool kg_float2_gt(const kg_float2* pA, const kg_float2* pB)
{
	return ( pA->x > pB->x && pA->y > pB->y );
}

kg_internal kg_float2 kg_float2_clamp(const kg_float2* pValue, const kg_float2* pMin, const kg_float2* pMax)
{
	kg_float2 clamped = kg_float2_zero();
	clamped.x = kg_clamp(pValue->x, pMin->x, pMax->x);
	clamped.y = kg_clamp(pValue->y, pMin->y, pMax->y);

	return clamped;
}

kg_internal kg_float2 kg_float2_max(const kg_float2* pA, const kg_float2* pB)
{
	kg_float2 maxValue = kg_float2_zero();
	maxValue.x = kg_max(pA->x, pB->x);
	maxValue.y = kg_max(pA->y, pB->y);

	return maxValue;
}

kg_internal kg_float2 kg_float2_add(const kg_float2* pA, const kg_float2* pB)
{
	kg_float2 sum = *pA;
	sum.x += pB->x;
	sum.y += pB->y;

	return sum;
}

kg_internal kg_float4 kg_float4_zero()
{
	static const kg_float4 zero = {0.f, 0.f, 0.f, 0.f};
	return zero;
}

kg_internal kg_uint2 kg_uint2_zero()
{
	static const kg_uint2 zero = {0u, 0u};
	return zero;
}

kg_internal kg_sint2 kg_sint2_zero()
{
	static const kg_sint2 zero = {0, 0};
	return zero;
}

kg_internal kg_float2 kg_create_float2(float x, float y)
{
	kg_float2 f2 = {x, y};
	return f2;
}

kg_internal kg_uint2 kg_create_uint2(kg_u32 x, kg_u32 y)
{
	kg_uint2 u2 = {x, y};
	return u2;
}

kg_internal kg_sint2 kg_create_sint2(kg_s32 x, kg_s32 y)
{
	kg_sint2 s2 = {x, y};
	return s2;
}

kg_internal kg_bool kg_is_invalid_context_handle(kg_context_handle contextHandle)
{
	return (contextHandle.value == 0u);
}

kg_internal kg_bool kg_is_invalid_viewport(const kg_viewport* pViewport)
{
	if (pViewport == kg_nullptr)
	{
		return kg_true;
	}

	const int width 	= pViewport->right - pViewport->left;
	const int height 	= pViewport->bottom - pViewport->top;

	if (width == 0 || height == 0 || width < 0 || height < 0)
	{
		return kg_true;
	}

	return kg_false;
}

kg_internal kg_bool kg_is_invalid_data_handle(const kg_data_handle* pHandle)
{
	if (pHandle == kg_nullptr)
	{
		return kg_true;
	}

	if (pHandle->offset == 0u && pHandle->sizeInBytes == 0u)
	{
		return kg_true;
	}

	return kg_false;
}

kg_internal kg_bool kg_is_invalid_buffer(const kg_buffer* pBuffer)
{
	if (pBuffer == kg_nullptr)
	{
		return kg_true;
	}

	if (!pBuffer->pMemory)
	{
		return kg_true;
	}

	if (pBuffer->capacityInBytes == 0)
	{
		return kg_true;
	}

	if (pBuffer->sizeInBytes > pBuffer->capacityInBytes)
	{
		return kg_true;
	}

	return kg_false;
}

kg_internal void kg_clear_buffer(kg_buffer* pBuffer)
{
	if(kg_is_invalid_buffer(pBuffer))
	{
		return;
	}

	pBuffer->sizeInBytes = 0u;
}

kg_internal void* kg_reserve_memory_from_current_buffer_position(kg_buffer* pBuffer, kg_u32 sizeInBytes)
{
	if(kg_is_invalid_buffer(pBuffer))
	{
		return kg_nullptr;
	}

	if (pBuffer->sizeInBytes + sizeInBytes >= pBuffer->capacityInBytes)
	{
		return kg_nullptr;
	}

	void* pMemory = (kg_byte*)pBuffer->pMemory + pBuffer->sizeInBytes;
	pBuffer->sizeInBytes += sizeInBytes;

	return pMemory;
}

kg_internal const kg_data_handle* kg_invalid_data_handle()
{
	static const kg_data_handle invalidDataHandles = {0u, 0u};
	return &invalidDataHandles;
}

kg_internal const kg_data_handle* kg_create_data_handle(kg_buffer* pBuffer, kg_u32 sizeInBytes)
{
	if ( pBuffer == kg_nullptr )
	{
		return kg_invalid_data_handle();
	}

	const kg_u32 totalSizeInBytes = sizeof( kg_data_handle ) + sizeInBytes;

	if ( ( pBuffer->sizeInBytes + totalSizeInBytes ) >= pBuffer->capacityInBytes )
	{
		return kg_invalid_data_handle();
	}

	kg_data_handle* pDataHandle 	= ( kg_data_handle* )( pBuffer->pMemory + pBuffer->sizeInBytes );
	pDataHandle->offset 			= pBuffer->sizeInBytes + sizeof( kg_data_handle );
	pDataHandle->sizeInBytes 		= sizeInBytes;
	pDataHandle->pNextHandle		= kg_nullptr;
	pDataHandle->pPreviousHandle 	= pBuffer->pLastHandle;

	pBuffer->sizeInBytes += sizeInBytes + sizeof(kg_data_handle);

	if (pBuffer->pFirstHandle == kg_nullptr)
	{
		pBuffer->pFirstHandle = ( void* )pDataHandle;
		pBuffer->pLastHandle = ( void* )pDataHandle;
	}
	else
	{
		kg_data_handle* pLastHandle = (kg_data_handle*)pBuffer->pLastHandle;
		pLastHandle->pNextHandle 	= pDataHandle;
		pBuffer->pLastHandle 		= pDataHandle;
	}

	return pDataHandle;
}

kg_internal kg_buffer kg_create_buffer(void* pMemory, kg_u32 capacityInBytes)
{
	kg_buffer buffer;
	buffer.pMemory 			= pMemory;
	buffer.sizeInBytes 		= 0u;
	buffer.capacityInBytes 	= capacityInBytes;
	buffer.pFirstHandle 	= kg_nullptr;
	buffer.pLastHandle 		= kg_nullptr;
	return buffer;
}

kg_internal const kg_data_handle* kg_allocate_from_buffer(kg_buffer* pBuffer, kg_u32 sizeInBytes)
{
	return kg_create_data_handle(pBuffer, sizeInBytes);
}

kg_internal void kg_defragment_buffer(kg_buffer* pBuffer, const kg_data_handle* pHandle)
{
	kg_data_handle* pNextHandle = (kg_data_handle*)pHandle->pNextHandle;

	while( pNextHandle != kg_nullptr)
	{
		pNextHandle->offset = pHandle->offset;
		pNextHandle 		= (kg_data_handle*)pNextHandle->pNextHandle;
	}
}

kg_internal void kg_free_from_buffer(kg_buffer* pBuffer, const kg_data_handle* pHandle)
{
	if ( kg_is_invalid_data_handle( pHandle ) )
	{
		return;
	}

	kg_defragment_buffer(pBuffer, pHandle); 

	if (pBuffer->pFirstHandle == pHandle)
	{
		pBuffer->pFirstHandle = pHandle->pNextHandle;
	}

	if (pHandle->pPreviousHandle != kg_nullptr)
	{
		kg_data_handle* pPreviousHandle = (kg_data_handle*)pHandle->pPreviousHandle;
		pPreviousHandle->pNextHandle = pHandle->pNextHandle;
	}

	pBuffer->sizeInBytes -= pHandle->sizeInBytes;
}

kg_internal kg_byte* kg_get_memory_from_buffer(kg_buffer* pBuffer, const kg_data_handle* pHandle)
{
	return pBuffer->pMemory + pHandle->offset;
}

kg_internal kg_result kg_create_input_queue(kg_input_queue** pOutInputQueue, void* pMemory, kg_u32 memorySizeInBytes)
{
	if (memorySizeInBytes < sizeof(kg_input_queue))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	kg_byte* 	pInputBufferMemory 				= (kg_byte*)pMemory + sizeof(kg_input_queue);
	kg_u32 		inputBufferMemorySizeInBytes 	= memorySizeInBytes -= sizeof(kg_input_queue);

	kg_input_queue* pInputQueue = (kg_input_queue*)pMemory;

	pInputQueue->buffer 		= kg_create_buffer(pInputBufferMemory, inputBufferMemorySizeInBytes);
	pInputQueue->pFirstEvent 	= kg_nullptr;
	pInputQueue->pLastEvent 	= kg_nullptr;

	*pOutInputQueue = pInputQueue;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_create_error_stack(kg_error_stack** pOutErrorStack, void* pMemory, kg_u32 memorySizeInBytes)
{
	if (memorySizeInBytes < sizeof(kg_error_stack))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	kg_byte* 	pErrorStackBufferMemory 			= (kg_byte*)pMemory + sizeof(kg_error_stack);
	kg_u32 		errorStackBufferMemorySizeInbytes 	= memorySizeInBytes -= sizeof(kg_error_stack);
	kg_buffer 	errorStackBuffer 					= kg_create_buffer(pErrorStackBufferMemory, errorStackBufferMemorySizeInbytes);
	
	if (kg_is_invalid_buffer(&errorStackBuffer))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	kg_error_stack* pErrorStack = (kg_error_stack*)pMemory;

	pErrorStack->pLastError 	= kg_nullptr;
	pErrorStack->errorBuffer	= errorStackBuffer;

	*pOutErrorStack = pErrorStack;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_create_hash_map(kg_hash_map** pOutHashMap, void* pMemory, kg_u32 memorySizeInBytes)
{
	kg_buffer hashMapBuffer = kg_create_buffer(pMemory, memorySizeInBytes);

	if (kg_is_invalid_buffer(&hashMapBuffer))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	const kg_data_handle* pHashMapDataHandle = kg_allocate_from_buffer(&hashMapBuffer, sizeof(kg_hash_map));

	if (kg_is_invalid_data_handle(pHashMapDataHandle))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	const kg_u32 defaultBucketCount 			= 128u;
	const kg_data_handle* pBucketArrayHandle 	= kg_allocate_from_buffer(&hashMapBuffer, kg_ptr_size_in_bytes * defaultBucketCount);

	if (kg_is_invalid_data_handle(pBucketArrayHandle))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	void* pBucketArray = kg_get_memory_from_buffer(&hashMapBuffer, pBucketArrayHandle);
	kg_memset(pBucketArray, 0, kg_ptr_size_in_bytes * defaultBucketCount);

	kg_hash_map* pHashMap 	= (kg_hash_map*)kg_get_memory_from_buffer(&hashMapBuffer, pHashMapDataHandle);
	pHashMap->bucketCount	= defaultBucketCount;
	pHashMap->size 			= 0u;
	pHashMap->pBuckets  	= (kg_hash_map_bucket**)kg_get_memory_from_buffer(&hashMapBuffer, pBucketArrayHandle);
	pHashMap->bucketBuffer 	= hashMapBuffer;

	*pOutHashMap = pHashMap;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_hash_map_bucket* kg_allocate_bucket(kg_hash_map* pHashMap, kg_crc32 identifier)
{
	kg_buffer* pBucketBuffer = &pHashMap->bucketBuffer;

	const kg_data_handle* pBucketHandle = kg_allocate_from_buffer(pBucketBuffer, sizeof(kg_hash_map_bucket));

	if (kg_is_invalid_data_handle(pBucketHandle))
	{
		return kg_nullptr;
	}

	kg_hash_map_bucket* pBucket = (kg_hash_map_bucket*)kg_get_memory_from_buffer(pBucketBuffer, pBucketHandle);
	pBucket->key = identifier;
	return pBucket;
}

kg_internal kg_hash_map_bucket* kg_find_hash_bucket(kg_hash_map* pHashMap, kg_u32 bucketIndex, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	if (pHashMap == kg_nullptr)
	{
		return kg_nullptr;
	}

	kg_hash_map_bucket* pBucket = pHashMap->pBuckets[ bucketIndex ];

	while (pBucket)
	{
		if (pBucket->key == identifier)
		{
			break;
		}

		pBucket = pBucket->pNext;
	}

	return pBucket;
}

kg_internal void* kg_insert_hash_element(kg_hash_map* pHashMap, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	if (pHashMap == kg_nullptr)
	{
		return kg_nullptr;
	}

	const kg_u32 hashIndex = identifier % pHashMap->bucketCount;
	kg_hash_map_bucket* pBucket = pHashMap->pBuckets[hashIndex];

	if (pHashMap->pBuckets[hashIndex] != kg_nullptr)
	{
		pBucket = kg_find_hash_bucket(pHashMap, hashIndex, identifier, pOutIsNew);
	}

	if (pBucket)
	{
		if (pOutIsNew != kg_nullptr) 
		{
			*pOutIsNew = kg_false;
		}

		return &pBucket->pElement;
	}

	if (pOutIsNew != kg_nullptr)
	{
		*pOutIsNew = kg_true;
	}

	pBucket = kg_allocate_bucket(pHashMap, identifier);

	if( pBucket == kg_nullptr )
	{
		return kg_nullptr;
	}

	pBucket->pNext = pHashMap->pBuckets[hashIndex];

	pHashMap->pBuckets[ hashIndex ] = pBucket;

	return &pBucket->pElement;
}

kg_internal kg_rect kg_create_rect(kg_s32 x, kg_s32 y, kg_u32 w, kg_u32 h)
{
	kg_rect rect;
	rect.position 	= kg_create_sint2(x, y);
	rect.size 		= kg_create_uint2(w, h);

	return rect;
}

kg_internal kg_crc32 kg_generate_crc32(const char* pIdentifier)
{	
	static const kg_u32 crc_table[] = {
		25524, 30093, 15731, 4958, 22260, 4510, 4365, 1390, 3442, 20063, 10074, 5395, 15899, 6103, 18904, 32038, 12922, 25399, 25476, 23810, 11145, 20575, 11339, 1582, 2247, 1188, 10433, 19772, 25994, 8913, 21013, 25072, 8343, 1131, 31301, 29349, 496, 6202, 16526, 7917, 29421, 2564, 10791, 32120, 31886, 6044, 13102, 14647, 16, 14108, 27619, 2496, 23998, 29294, 30228, 2805, 32266, 7185, 30424, 14304, 28892, 16665, 20608, 3298, 5930, 
		31864, 14539, 5389, 2761, 3965, 32601, 26318, 14467, 25498, 6242, 21455, 24681, 22890, 16296, 20507, 28778, 2290, 18346, 21636, 27941, 22312, 26907, 16450, 23804, 1201, 9874, 32220, 26986, 6639, 6275, 28492, 10902, 21563, 13678, 25950, 20776, 30831, 27222, 9817, 8795, 11944, 6005, 18401, 31315, 19274, 17710, 24604, 18610, 10564, 9539, 21012, 15206, 31125, 13384, 14684, 3012, 11279, 3928, 14583, 8667, 21850, 20998, 12661, 514, 
		13885, 4246, 8799, 14516, 18457, 17006, 15061, 14494, 29366, 12487, 23926, 24309, 20290, 15784, 7040, 4621, 7319, 5909, 27448, 11816, 18621, 10884, 7565, 13452, 13232, 27792, 22264, 28888, 3939, 18673, 4006, 2199, 260, 20140, 24281, 10518, 26498, 27783, 5516, 18291, 27469, 20928, 27734, 9975, 15197, 18174, 18576, 6565, 7029, 5000, 23738, 12051, 10153, 17077, 10267, 17785, 28958, 23972, 6568, 12552, 22545, 27948, 23079, 28029, 
		18202, 22550, 404, 3573, 13234, 29066, 15300, 24323, 2036, 19400, 8264, 28416, 22944, 8985, 16788, 28834, 4709, 29956, 14177, 11216, 28000, 6084, 10319, 28853, 28128, 26106, 5839, 16660, 13164, 21152, 30016, 9179, 20231, 31038, 17752, 22266, 32178, 32352, 18118, 21365, 27699, 21575, 30997, 22456, 26645, 14303, 29908, 27692, 8688, 31217, 24564, 5639, 25834, 26778, 369, 11368, 26494, 27900, 14389, 931, 6524, 12595, 22841
	};

	kg_crc32 	crc 		= 0u;
	kg_u32 		crcIndex 	= 0u;
	kg_u8 		byte 		= 0u;

	while (*pIdentifier != 0)
	{
		unsigned char byte = (unsigned char)*pIdentifier++;
		crcIndex = (crc | byte) & 0xFF;

		crc = (crc << 8u) ^ crc_table[crcIndex];
	}

	crc = crc ^ 0xFFFFFFFF;

	return crc;
}

kg_internal kg_bool kg_grow_array_capacity(kg_array* pArray)
{
	if (kg_is_invalid_buffer(pArray->pBuffer))
	{
		return kg_false;
	}

	const kg_data_handle* pArrayDataHandle = pArray->pDataHandle;

	if (kg_is_invalid_data_handle(pArrayDataHandle))
	{
		return kg_false;
	}

	const kg_u32 newCapacity = pArray->capacity * 2u;
	const kg_data_handle* pNewArrayDataHandle = kg_allocate_from_buffer(pArray->pBuffer, newCapacity * pArray->elementSizeInBytes);

	if (kg_is_invalid_data_handle(pNewArrayDataHandle))
	{
		return kg_false;
	}

	void* pArrayMemory 		= kg_get_memory_from_buffer(pArray->pBuffer, pArrayDataHandle);
	void* pNewArrayMemory 	= kg_get_memory_from_buffer(pArray->pBuffer, pNewArrayDataHandle);

	kg_memcpy(pNewArrayMemory, pArrayMemory, pArray->capacity * pArray->elementSizeInBytes);
	kg_free_from_buffer(pArray->pBuffer, pArrayDataHandle);

	pArray->capacity 	= newCapacity;
	pArray->pDataHandle = pNewArrayDataHandle;

	return kg_true;
}

kg_internal kg_array kg_invalid_array()
{
	static const kg_array invalidArray = { kg_nullptr, kg_nullptr, 0u, 0u, 0u };
	return invalidArray;
}

kg_internal kg_bool kg_is_invalid_array(kg_array* pArray)
{
	if (pArray == kg_nullptr)
	{
		return kg_true;
	}

	if (kg_is_invalid_data_handle(pArray->pDataHandle))
	{
		return kg_true;
	}

	if (pArray->elementSizeInBytes == 0u)
	{
		return kg_true;
	}

	if (pArray->capacity == 0u)
	{
		return kg_true;
	}

	return kg_false;
}

kg_internal kg_result kg_create_array(kg_array* pOutArray, kg_buffer* pBuffer, kg_u32 initialCapacity, size_t elementSizeInBytes)
{
	kg_array array;
	array.size 					= 0u;
	array.capacity 				= initialCapacity;
	array.elementSizeInBytes 	= elementSizeInBytes;
	array.pDataHandle			= kg_allocate_from_buffer(pBuffer, initialCapacity * elementSizeInBytes);
	array.pBuffer				= pBuffer;

	if (kg_is_invalid_data_handle(array.pDataHandle))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	*pOutArray = array;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_clear_array(kg_array* pArray)
{
	if (kg_is_invalid_array(pArray))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	pArray->size = 0u;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_array_get_element(void** ppOutElement, kg_array* pArray, kg_u32 index)
{
	if (ppOutElement == kg_nullptr)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (kg_is_invalid_array(pArray))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pArray->size <= index)
	{
		return K15_GUI_RESULT_OUT_OF_BOUNDS;
	}

	kg_byte* pArrayData = kg_get_memory_from_buffer(pArray->pBuffer, pArray->pDataHandle);
	kg_memcpy(ppOutElement, pArrayData + index * pArray->elementSizeInBytes, pArray->elementSizeInBytes);

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_array_get_back( void** ppOutElement, kg_array* pArray )
{
	if( ppOutElement == kg_nullptr )
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if( kg_is_invalid_array( pArray ) )
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if( pArray->size == 0 )
	{
		return K15_GUI_RESULT_ARRAY_EMPTY;
	}

	return kg_array_get_element( ppOutElement, pArray, pArray->size - 1u );
}

kg_internal kg_result kg_array_push_back(kg_array* pArray, void* pElement)
{
	if (kg_is_invalid_array(pArray))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pElement == kg_nullptr)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pArray->size == pArray->capacity)
	{
		if (!kg_grow_array_capacity(pArray))
		{
			return K15_GUI_RESULT_OUT_OF_MEMORY;
		}
	}

	const kg_data_handle* pArrayDataHandle 	= pArray->pDataHandle;
	kg_byte* pArrayData						= (kg_byte*)kg_get_memory_from_buffer(pArray->pBuffer, pArrayDataHandle);

	kg_memcpy(pArrayData + pArray->size * pArray->elementSizeInBytes, pElement, pArray->elementSizeInBytes);	
	++pArray->size;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_array_pop_back(kg_array* pArray)
{
	if (kg_is_invalid_array(pArray))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pArray->size == 0u)
	{
		return K15_GUI_RESULT_ARRAY_EMPTY;
	}

	--pArray->size;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal void kg_add_child(kg_context* pContext, kg_element* pParent, kg_element* pChild)
{
	kg_array_push_back(&pParent->childArray, &pChild);
}

kg_internal kg_bool kg_element_has_component(kg_element* pElement, kg_component_type componentType)
{
	return !kg_is_invalid_data_handle(pElement->componentHandles[componentType]);
}

kg_internal kg_element* kg_allocate_element(kg_context* pContext, const char* pIdentifier)
{
	kg_crc32 identifierHash = kg_generate_crc32(pIdentifier);

	kg_bool isNew = 0u;
	kg_element* pElement = kg_insert_hash_element(pContext->pElements, identifierHash, &isNew);

	if (isNew)
	{
		kg_result result = kg_create_array(&pElement->childArray, &pContext->memoryBuffer, 8u, kg_ptr_size_in_bytes);

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			return kg_nullptr;
		}

		pElement->offset			= kg_float2_zero();
		pElement->minSize			= kg_float2_zero();
		pElement->maxSize			= kg_float2_zero();
		pElement->prefSize			= kg_float2_zero();
		pElement->size 				= kg_float2_zero();
		pElement->position 			= kg_float2_zero();
		pElement->padding			= kg_float4_zero();
		pElement->margin			= kg_float4_zero();
		pElement->border			= kg_float4_zero();
		pElement->identifier 		= identifierHash;

		for (kg_u32 componentIndex = 0u; componentIndex < K15_GUI_COMPONENT_COUNT; ++componentIndex)
		{
			pElement->componentHandles[componentIndex] = kg_nullptr;
		}

#ifdef K15_GUI_STORE_IDENTIFIER_STRING
		pElement->p_Identifier		= pIdentifier;
#endif
	}

	kg_clear_array(&pElement->childArray);

	kg_element* pParent = kg_nullptr;
	
	if (kg_array_get_back(&pParent, &pContext->elementStack) == K15_GUI_RESULT_SUCCESS)
	{
		kg_array_push_back(&pParent->childArray, &pElement);
	}

	pElement->frameUseCounter = pContext->frameCounter;

	return pElement;
}

kg_internal void kg_process_mouse_input(kg_context* pContext, kg_input_event* pInputEvent)
{

}

kg_internal void kg_process_keyboard_input(kg_context* pContext, kg_input_event* pInputEvent)
{
	
}

kg_internal void kg_process_gamepad_input(kg_context* pContext, kg_input_event* pInputEvent)
{
	
}

kg_internal void kg_process_input_event(kg_context* pContext, kg_input_event* pInputEvent)
{

}

kg_internal void kg_process_input_events(kg_context* pContext)
{
	kg_input_queue* pInputQueue = pContext->pInputQueue;
	kg_input_event* pInputEvent = pInputQueue->pFirstEvent;

	while (pInputEvent)
	{
		kg_process_input_event(pContext, pInputEvent);
		pInputEvent = (kg_input_event*)pInputEvent->pNext;
	}

	pInputQueue->pFirstEvent 	= kg_nullptr;
	pInputQueue->pLastEvent 	= kg_nullptr;

	kg_clear_buffer(&pInputQueue->buffer);
}


kg_internal void kg_input_pass(kg_element* pElement)
{

}

kg_internal kg_float2 kg_calculate_element_layout_start_position(kg_element* pElement)
{
	kg_float2 position = pElement->position;

	position.x += pElement->padding.x;
	position.y += pElement->padding.y;

	return position;
}

kg_internal kg_layout_state kg_create_layout_state(kg_element* pElement)
{
	//FK: Calculate position from where to start layouting.
	kg_float2 layoutPosition = pElement->position;
	layoutPosition.x += pElement->padding.x;
	layoutPosition.y += pElement->padding.y;

	kg_float2 layoutSize = pElement->size;
	layoutSize.x -= (pElement->padding.x + pElement->padding.z);
	layoutSize.y -= (pElement->padding.y + pElement->padding.w);

	kg_layout_state layoutState;	
	layoutState.origin 			= layoutPosition;
	layoutState.maxSize 		= layoutSize;
	layoutState.position 		= layoutPosition;
	layoutState.accumulatedSize = kg_float2_zero();
	layoutState.maxSize			= kg_float2_zero();


	return layoutState;
}

kg_internal kg_float2 kg_calculate_element_position(kg_layout_state* pLayoutState, kg_element* pElement)
{
	kg_float2 position = pLayoutState->position;
	position.x += pElement->margin.x;
	position.y += pElement->margin.y;

	return position;
}

kg_internal kg_float2 kg_calculate_element_size_with_margin(kg_element* pElement)
{
	kg_float2 size = pElement->size;
	size.x += (pElement->margin.x + pElement->margin.z);
	size.y += (pElement->margin.y + pElement->margin.w);

	return size;
}

kg_internal void kg_advance_layout_vertical(kg_layout_state* pLayoutState, kg_element* pElement)
{
	pElement->position = kg_calculate_element_position(pLayoutState, pElement);

	const kg_float2 elementSize = kg_calculate_element_size_with_margin(pElement);
	pLayoutState->maxSize = kg_float2_max(&pLayoutState->maxSize, &elementSize);

	if (pLayoutState->accumulatedSize.y + elementSize.y > pLayoutState->maxSize.y)
	{
		pLayoutState->position.x += pLayoutState->maxSize.x;
		pLayoutState->position.y = pLayoutState->origin.y;
	}

	if (kg_float2_gt(&elementSize, &pLayoutState->maxSize))
	{
		//FK: Don't set element - too big
		return;
	}

	pLayoutState->accumulatedSize.x = kg_max( (pLayoutState->position.x - pLayoutState->origin.x) + pLayoutState->accumulatedSize.x, pLayoutState->maxSize.x);
	pLayoutState->accumulatedSize.y = kg_max( (pLayoutState->position.y - pLayoutState->origin.y) + pLayoutState->accumulatedSize.y, pLayoutState->maxSize.y);

	pLayoutState->position.y += elementSize.y;
}

kg_internal void kg_layout_vertical(kg_element* pElement)
{
	kg_layout_state layoutState = kg_create_layout_state(pElement);

	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_nullptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);

		kg_advance_layout_vertical(&layoutState, pChild);
	}

	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_nullptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);
		kg_layout_pass(pChild);
	}
}

kg_internal void kg_advance_layout_horizontal(kg_layout_state* pLayoutState, kg_element* pElement)
{
	pElement->position = kg_calculate_element_position(pLayoutState, pElement);

	const kg_float2 elementSize = kg_calculate_element_size_with_margin(pElement);
	pLayoutState->maxSize = kg_float2_max(&pLayoutState->maxSize, &elementSize);

	if (pLayoutState->accumulatedSize.x + elementSize.x > pLayoutState->maxSize.x)
	{
		pLayoutState->position.y += pLayoutState->maxSize.y;
		pLayoutState->position.x = pLayoutState->origin.x;
	}

	if (kg_float2_gt(&elementSize, &pLayoutState->maxSize))
	{
		//FK: Don't set element - too big
		return;
	}

	pLayoutState->accumulatedSize.x = kg_max( (pLayoutState->position.x - pLayoutState->origin.x) + pLayoutState->accumulatedSize.x, pLayoutState->maxSize.x);
	pLayoutState->accumulatedSize.y = kg_max( (pLayoutState->position.y - pLayoutState->origin.y) + pLayoutState->accumulatedSize.y, pLayoutState->maxSize.y);

	pLayoutState->position.x += elementSize.x;
}

kg_internal void kg_layout_horizontal(kg_element* pElement)
{
	kg_layout_state layoutState = kg_create_layout_state(pElement);

	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_nullptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);

		kg_advance_layout_horizontal(&layoutState, pChild);
	}

	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_nullptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);
		kg_layout_pass(pChild);
	}
}

kg_internal void kg_layout_pass(kg_element* pElement)
{
	const kg_float2 prefSize 	= pElement->prefSize;
	const kg_float2 maxSize		= pElement->maxSize;
	const kg_float2 minSize		= pElement->minSize;

	pElement->size 		= kg_float2_clamp(&prefSize, &minSize, &maxSize);
	pElement->position 	= kg_float2_add(&pElement->position, &pElement->offset);

	if (kg_element_has_component(pElement, K15_GUI_WINDOW_COMPONENT))
	{
		//pElement->padding.y = kg_get_font_height();
	}

	if (pElement->layout == K15_GUI_LAYOUT_VERTICAL)
	{
		kg_layout_vertical(pElement);
	}
	else if (pElement->layout == K15_GUI_LAYOUT_HORIZONTAL)
	{
		kg_layout_horizontal(pElement);
	}
}

kg_internal void kg_render_element(kg_context* pContext, kg_element* pElement)
{	
	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_nullptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);

		kg_render_element(pContext, pChild);
	}


}

kg_internal void kg_render_pass(kg_context* pContext)
{
	kg_render_element(pContext, pContext->pRootElement);
}

kg_internal void kg_push_error(kg_context* pContext, const char* pFunction, const char* pDescription, const char* pIdentifier, kg_result result)
{
	if (pContext == kg_nullptr)
	{
		return;
	}

	kg_error_stack* pErrorStack = pContext->pErrorStack;
	kg_error* 		pError		= kg_reserve_memory_from_current_buffer_position(&pErrorStack->errorBuffer, sizeof(kg_error));

	if (pError == kg_nullptr)
	{
		return;
	}

	pError->pFunction	 	= pFunction;
	pError->pDescription 	= pDescription;
	pError->pIdentifier		= pIdentifier;
	pError->result			= result;
	pError->pPrevious		= kg_nullptr;

	if (pErrorStack->pLastError == kg_nullptr)
	{
		pErrorStack->pLastError = pError;
	}
	else
	{
		pError->pPrevious = pErrorStack->pLastError;
		pErrorStack->pLastError = pError;
	}
}

/******************************RENDER LOGIC***************************************/
kg_internal void kg_set_vertex_3d(kg_render_vertices* pVertices, kg_u32 vertexIndex, float x, float y, float z, float w, float u, float v, kg_color32 color)
{
	if (vertexIndex >= pVertices->vertexCount)
	{
		return;
	}

	kg_render_vertex_data* pVertexData = &pVertices->pVertexData[vertexIndex];

	pVertexData->position.x	= x;
	pVertexData->position.y	= y;
	pVertexData->position.z	= z;
	pVertexData->position.w	= w;
	pVertexData->texcoord.x	= u;
	pVertexData->texcoord.y	= v;
	pVertexData->color 		= color;
}

kg_internal void kg_set_vertex_2d(kg_render_vertices* pVertices, kg_u32 vertexIndex, float x, float y, float u, float v, kg_color32 color)
{
	kg_set_vertex_3d(pVertices, vertexIndex, x, y, 1.f, 1.f, u, v, color);
}

kg_internal void kg_add_render_geometry(kg_context* pContext, kg_render_vertices* pVertices)
{
}

kg_internal kg_render_vertices* kg_allocate_vertices(kg_context* pContext, kg_u32 vertexCount)
{
	return kg_nullptr;
}

kg_internal kg_result kg_render_element_rect(kg_context* pContext, kg_element* pElement, kg_float2 offset, kg_float2 size, kg_color32 color)
{
	if (pContext == kg_nullptr)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pElement == kg_nullptr)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_render_vertices* pVertices = kg_allocate_vertices(pContext, 6u);

	if (pVertices == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	const kg_float2 position = kg_float2_add(&pElement->position, &offset);

	kg_set_vertex_2d(pVertices, 0, position.x, 			position.y, 			0.f, 0.f, color);	
	kg_set_vertex_2d(pVertices, 1, position.x + size.x, position.y, 			0.f, 0.f, color);	
	kg_set_vertex_2d(pVertices, 2, position.x, 			position.y + size.y, 	0.f, 0.f, color);	
	kg_set_vertex_2d(pVertices, 3, position.x, 			position.y + size.y, 	0.f, 0.f, color);	
	kg_set_vertex_2d(pVertices, 4, position.x + size.x, position.y, 			0.f, 0.f, color);	
	kg_set_vertex_2d(pVertices, 5, position.x + size.x, position.y + size.y, 	0.f, 0.f, color);	

	return K15_GUI_RESULT_SUCCESS;
}

/******************************INPUT LOGIC****************************************/
kg_internal kg_input_event* kg_allocate_input_event(kg_input_queue* pInputQueue, kg_input_type inputType)
{
	kg_input_event* pInputEvent = (kg_input_event*)kg_reserve_memory_from_current_buffer_position(&pInputQueue->buffer, sizeof(kg_input_event));
	
	if( pInputEvent == kg_nullptr)
	{
		return kg_nullptr;
	}

	if (pInputQueue->pFirstEvent == kg_nullptr)
	{
		pInputQueue->pFirstEvent = pInputEvent;
	}
	else
	{
		pInputQueue->pLastEvent->pNext = pInputEvent;
	}

	pInputQueue->pLastEvent = pInputEvent;
	pInputEvent->pNext 		= kg_nullptr;
	pInputEvent->type		= inputType;

	return pInputEvent;
}

/*****************************RESOURCE LOGIC**************************************/
kg_internal const kg_utf8* kg_find_text(kg_context* pContext, const char* pTextID)
{
	return pTextID;
}

/*****************************CONTROL LOGIC***************************************/
kg_window_component* kg_allocate_window_component(kg_context* pContext, kg_element* pElement)
{
	if (pElement->componentHandles[K15_GUI_WINDOW_COMPONENT] == kg_nullptr)
	{
		const kg_data_handle* pWindowComponentHandle = kg_allocate_from_buffer(&pContext->memoryBuffer, sizeof(kg_window_component));

		if (kg_is_invalid_data_handle(pWindowComponentHandle))
		{
			return kg_nullptr;
		}

		kg_window_component* pWindowComponent = (kg_window_component*)kg_get_memory_from_buffer(&pContext->memoryBuffer, pWindowComponentHandle);
		pWindowComponent->flags 			= K15_GUI_WINDOW_FLAG_IS_OPEN;
		pWindowComponent->originalSize 		= kg_float2_zero();
		pWindowComponent->originalPosition 	= kg_float2_zero();
		pWindowComponent->pText 			= kg_nullptr;

		pElement->componentHandles[K15_GUI_WINDOW_COMPONENT] = pWindowComponentHandle;
	}

	kg_window_component* pWindowComponent = (kg_window_component*)kg_get_memory_from_buffer( &pContext->memoryBuffer, pElement->componentHandles[K15_GUI_WINDOW_COMPONENT] );
	return pWindowComponent;
}

kg_internal kg_bool kg_window_logic(kg_context* pContext, kg_element* pElement, kg_window_component* pComponent)
{
	if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_CLOSE_BUTTON_CLICKED ) != 0 )
	{
		pComponent->flags &= ~K15_GUI_WINDOW_FLAG_IS_OPEN;
		pComponent->flags &= ~K15_GUI_WINDOW_FLAG_CLOSE_BUTTON_CLICKED;
	}

	if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_IS_OPEN ) == 0 )
	{
		return kg_false;
	}

	if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED ) != 0 )
	{
		if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_IS_MAXIMIZED ) == 0 )
		{
			pComponent->originalPosition 	= pElement->position;
			pComponent->originalSize 		= pElement->size;
			pComponent->flags |= K15_GUI_WINDOW_FLAG_IS_MAXIMIZED;	
			pComponent->flags &= ~K15_GUI_WINDOW_FLAG_IS_MINIMIZED;
		}
		else
		{
			pElement->size 		= pComponent->originalSize;
			pElement->position 	= pComponent->originalPosition;
			
			pComponent->flags &= ~K15_GUI_WINDOW_FLAG_IS_MAXIMIZED;
		}

		pComponent->flags &= ~K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED;
	}

	if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED ) != 0 )
	{
		if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_IS_MINIMIZED ) == 0)
		{
			pComponent->originalPosition 	= pElement->position;
			pComponent->originalSize 		= pElement->size;
			pComponent->flags |= K15_GUI_WINDOW_FLAG_IS_MINIMIZED;	
		}
		else
		{
			pElement->size 		= pComponent->originalSize;
			pElement->position 	= pComponent->originalPosition;

			pComponent->flags &= ~K15_GUI_WINDOW_FLAG_IS_MINIMIZED;	
		}

		pComponent->flags &= ~K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED;
	}

	const kg_float2 titleArea 	= kg_float2_load(pElement->size.x, TitleHeightInPixels);
	const kg_float2 windowArea 	= kg_float2_load(pElement->size.x, kg_max(pElement->size.y - TitleHeightInPixels, MinAreaHeightInPixels)); 
	
	kg_render_element_rect(pContext, pElement, kg_float2_load(0.f, TitleHeightInPixels), windowArea, kg_color_white);
	kg_render_element_rect(pContext, pElement, kg_float2_zero(), titleArea, kg_color_light_grey);

	return (pComponent->flags & K15_GUI_WINDOW_FLAG_IS_OPEN);
}


kg_internal kg_element* kg_insert_ui_element(kg_hash_map* pHashMap, kg_crc32 identifier)
{
	kg_bool isNew = kg_false;
	kg_element* pElement = kg_insert_hash_element(pHashMap, identifier, &isNew);

	if (isNew == kg_true)
	{
		pElement->size			= kg_float2_zero();
		pElement->maxSize		= kg_float2_zero();
		pElement->minSize		= kg_float2_zero();
		pElement->prefSize		= kg_float2_zero();
		pElement->position		= kg_float2_zero();
		pElement->offset		= kg_float2_zero();
		pElement->border		= kg_float4_zero();
		pElement->margin		= kg_float4_zero();
		pElement->padding		= kg_float4_zero();
		pElement->layout		= K15_GUI_LAYOUT_VERTICAL;
		pElement->identifier	= identifier;

		for (kg_u32 componentIndex = 0u; componentIndex < K15_GUI_COMPONENT_COUNT; ++componentIndex)
		{
			pElement->componentHandles[componentIndex] = kg_invalid_data_handle();
		}
	}

	return pElement;
}

//TODO-LIST:
//	1. Proper layouting (currently broken as PopLayout pops layouts from the stack that
//						later get references via the layoutIndex in the K15_GUIElement
//						struct).
//	2. Provide OS specific wrapper functions for input handling
//	3. Provide Render API specific wrapper functions for rendering
//	4. Somewhere store a white pixel in pre-baked texture (including default-font) to
//	   overcome the need for more than one vertex-/ fragmentshader pair.
//	5. Proper clipping of elements (Keep vertex count low)
//  6. Text processing (all those comfy keybindings)
//  7. UTF-8 support
//  8. More gui elements (slider, combobox, checkbox, proper window, scrollareas, etc)
//  9. custom gui elements (probably set of predetermined functions that together form
//							some form of new control element).
//	10. replace stb_truetype? Probably just going to strip the stuff that I need from 
//		stb_truetype
//	11. replace stb_image (I guess that is definitely doable. 
//							Only need JPEG, PNG and maybe TIFF support).
//  12. provide more style options other than just different colors.
//		Imagesets and icons come to mind.
kg_context_parameter kg_create_context_parameter()
{
	kg_context_parameter parameter;

	parameter.pDataMemory 		= kg_nullptr;
	parameter.dataMemorySize 	= 0u;

	parameter.vertex_draw_data.pVertexMemory 	= kg_nullptr;
	parameter.vertex_draw_data.pIndexMemory		= kg_nullptr;
	parameter.vertex_draw_data.vertexMemorySize = 0u;
	parameter.vertex_draw_data.indexMemorySize 	= 0u;

	return parameter;	
}

kg_result kg_create_context(kg_context_handle* pOutHandle)
{
	const kg_context_parameter* pParameter = kg_get_default_context_parameter();
	return kg_create_context_with_custom_parameter( pOutHandle, pParameter, kg_nullptr);
}

kg_result kg_create_context_with_custom_parameter(kg_context_handle* pOutHandle, const kg_context_parameter* pParameter, const char** pOutError)
{
	if (pOutHandle == kg_nullptr)
	{
		kg_set_error(pOutError, "argument 'pOutHandle' is NULL.");
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pParameter == kg_nullptr)
	{
		kg_set_error(pOutError, "argument 'pParameter' is NULL.");
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (kg_is_invalid_context_parameter(pParameter))
	{
		if (pParameter->dataMemorySize < MinContextDataSize)
		{
			return K15_GUI_RESULT_NEED_MORE_MEMORY;
		}

		return K15_GUI_RESULT_INVALID_CONTEXT_PARAMETER;
	}

	kg_buffer dataBuffer = kg_create_buffer(pParameter->pDataMemory, pParameter->dataMemorySize);

	if (kg_is_invalid_buffer(&dataBuffer))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	} 

	const kg_u32 hashMapDataSize 			= kg_size_kilo_bytes(64);
	const kg_u32 errorStackDataSize 		= kg_size_kilo_bytes(16);
	const kg_u32 inputBufferDataSize		= kg_size_kilo_bytes(16);
	const kg_u32 renderQueueChainDataSize	= kg_size_kilo_bytes(32);

	const kg_u32 totalDataSize = sizeof(kg_context) + hashMapDataSize + errorStackDataSize + inputBufferDataSize + renderQueueChainDataSize;

	kg_u8* pDataMemory = (kg_u8*)kg_reserve_memory_from_current_buffer_position(&dataBuffer, totalDataSize);

	if (pDataMemory == kg_nullptr)
	{
		pOutHandle->value = 0;
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	kg_u32 offset = 0u;

	kg_context* pContext 				= (kg_context*)(pDataMemory + offset); offset += sizeof(kg_context);
	void* 		pHashMapMemory			= pDataMemory + offset; offset += hashMapDataSize;
	void* 		pErrorStackMemory		= pDataMemory + offset; offset += errorStackDataSize;
	void* 		pInputBufferMemory		= pDataMemory + offset; offset += inputBufferDataSize;
	void*		pRenderQueueChainMemory	= pDataMemory + offset;

	pContext->memoryBuffer = dataBuffer;
	pContext->frameCounter = 0u;

	kg_result result = K15_GUI_RESULT_SUCCESS;

	result = kg_create_hash_map(&pContext->pElements, pHashMapMemory, hashMapDataSize);
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_error_stack(&pContext->pErrorStack, pErrorStackMemory, errorStackDataSize);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_input_queue(&pContext->pInputQueue, pInputBufferMemory, inputBufferDataSize);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}
	
	result = kg_create_array(&pContext->elementStack, &pContext->memoryBuffer, 16u, kg_ptr_size_in_bytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	pOutHandle->value = (size_t)pContext;

	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_set_viewport(kg_context_handle contextHandle, const kg_viewport* pViewport)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (kg_is_invalid_viewport(pViewport))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;
	pContext->viewport = *pViewport;
}

kg_result kg_get_viewport(kg_context_handle contextHandle, kg_viewport* pOutViewport)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pOutViewport == kg_nullptr)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;
	*pOutViewport = pContext->viewport;
}

kg_result kg_begin_frame(kg_context_handle contextHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;
	kg_clear_array(&pContext->elementStack);

	kg_element* pRootElement = kg_insert_ui_element(pContext->pElements, 0u);

	if (pRootElement == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pContext->pRootElement = pRootElement;

	return K15_GUI_RESULT_SUCCESS;
}

void kg_begin_toolbar(kg_context_handle contextHandle, const char* p_Identifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return;
	}
}

kg_bool kg_begin_window(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return kg_false;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;

	const kg_utf8* pText = kg_find_text(pContext, pTextID);
	kg_element* pElement = kg_allocate_element(pContext, pIdentifier);

	if (!pElement)
	{
		kg_push_error(pContext, "kg_begin_window", "Could not allocate element.", pIdentifier, K15_GUI_RESULT_OUT_OF_MEMORY);
		return kg_false;
	}

	kg_window_component* pWindowComponent = kg_allocate_window_component(pContext, pElement);

	if (!pWindowComponent)
	{
		kg_push_error(pContext, "kg_begin_window", "Could not allocate window component.", pIdentifier, K15_GUI_RESULT_OUT_OF_MEMORY);
		return kg_false;
	}

	pWindowComponent->pText = pText;

	if (kg_array_push_back(&pContext->elementStack, &pElement) != K15_GUI_RESULT_SUCCESS)
	{
		return kg_false;
	}
	
	return kg_window_logic(pContext, pElement, pWindowComponent);
}

kg_bool kg_begin_menu(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return kg_false;
	}
}

kg_bool kg_button(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return kg_false;
	}
}

void kg_label(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return;
	}
}

void kg_separator(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return;
	}
}

void kg_end_menu(kg_context_handle contextHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return;
	}
}

void kg_end_window(kg_context_handle contextHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;
	kg_array_pop_back(&pContext->elementStack);
}

void kg_end_toolbar(kg_context_handle contextHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return;
	}
}

kg_result kg_end_frame(kg_context_handle contextHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;
	kg_process_input_events(pContext);
	kg_input_pass(pContext->pRootElement);
	kg_layout_pass(pContext->pRootElement);
	kg_render_pass(pContext);
	++pContext->frameCounter;

	kg_clear_buffer(&pContext->pErrorStack->errorBuffer);

	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_add_input_mouse_move(kg_context_handle contextHandle, unsigned short x, unsigned short y)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_input_queue* pInputQueue = pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_MOUSE_MOVE);
	
	if (pInputEvent == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.mouse_move.x = x;
	pInputEvent->data.mouse_move.y = y;

	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_add_input_mouse_button_down(kg_context_handle contextHandle, unsigned short x, unsigned short y, kg_mouse_button_type mouseButtonType)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_input_queue* pInputQueue = pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_MOUSE_BUTTON_PRESSED);
	
	if (pInputEvent == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.mouse_button.x 			= x;
	pInputEvent->data.mouse_button.y 			= y;
	pInputEvent->data.mouse_button.buttonType 	= mouseButtonType;
	pInputEvent->data.mouse_button.actionType 	= K15_GUI_ACTION_BUTTON_DOWN;

	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_add_input_mouse_button_up(kg_context_handle contextHandle, unsigned short x, unsigned short y, kg_mouse_button_type mouseButtonType)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}
	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_input_queue* pInputQueue = pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_MOUSE_BUTTON_RELEASED);
	
	if (pInputEvent == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.mouse_button.x 			= x;
	pInputEvent->data.mouse_button.y 			= y;
	pInputEvent->data.mouse_button.buttonType 	= mouseButtonType;
	pInputEvent->data.mouse_button.actionType	= K15_GUI_ACTION_BUTTON_UP;

	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_add_input_key_button_down(kg_context_handle contextHandle, kg_keyboard_key_type buttonType)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}
	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_input_queue* pInputQueue = pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_KEY_PRESSED);
	
	if (pInputEvent == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.keyboard_button.key = buttonType;

	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_add_input_key_button_up(kg_context_handle contextHandle, kg_keyboard_key_type buttonType)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}
	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_input_queue* pInputQueue = pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_KEY_RELEASED);
	
	if (pInputEvent == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.keyboard_button.key = buttonType;

	return K15_GUI_RESULT_SUCCESS;
}

kg_bool kg_pop_error(kg_context_handle contextHandle, kg_error** pOutError)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return kg_false;
	}

	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_error_stack* pErrorStack = pContext->pErrorStack;
	kg_error* 		pLastError 	= pErrorStack->pLastError;

	if (pLastError == kg_nullptr)
	{
		return kg_false;
	}

	pErrorStack->pLastError = pLastError->pPrevious;
	*pOutError = pLastError;

	return kg_true;
}

const kg_vertex_definition*	kg_get_vertex_definition()
{
	static kg_vertex_definition vertexDefinition;

	vertexDefinition.stride 					= VertexStride;
	vertexDefinition.attributeCount 			= sizeof(vertexDefinition.attributes) / sizeof(vertexDefinition.attributes[0]);
	vertexDefinition.attributes[0].type 		= K15_GUI_POSITION_ATTRIBUTE_TYPE;
	vertexDefinition.attributes[0].dataType 	= K15_GUI_FLOAT4_DATA_TYPE;
	vertexDefinition.attributes[0].offset		= 0u;
	vertexDefinition.attributes[0].sizeInBytes 	= sizeof(kg_float4);

	vertexDefinition.attributes[1].type 		= K15_GUI_TEXCOORD_ATTRIBUTE_TYPE;
	vertexDefinition.attributes[1].dataType 	= K15_GUI_FLOAT2_DATA_TYPE;
	vertexDefinition.attributes[1].offset		= sizeof(kg_float4);
	vertexDefinition.attributes[1].sizeInBytes 	= sizeof(kg_float2);
	
	vertexDefinition.attributes[2].type 		= K15_GUI_COLOR_ATTRIBUTE_TYPE;
	vertexDefinition.attributes[2].dataType 	= K15_GUI_FLOAT4_DATA_TYPE;
	vertexDefinition.attributes[2].offset		= sizeof(kg_float4) + sizeof(kg_float2);
	vertexDefinition.attributes[2].sizeInBytes 	= sizeof(kg_float4);

	return &vertexDefinition;
}

kg_result kg_get_render_data(kg_context_handle contextHandle, void** pOutRenderData, int* pOutRenderDataSizeInBytes)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS; 
	}

	

	return K15_GUI_RESULT_SUCCESS;
}


#endif //K15_GUI_IMPLEMENTATION
#endif //_K15_GUILayer_Context_h_
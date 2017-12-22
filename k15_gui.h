#ifndef _K15_GUILayer_Context_h_
#define _K15_GUILayer_Context_h_

#ifndef K15_GUI_STATIC
# define kg_def static
#else
# define kg_def extern
#endif //K15_GUI_STATIC

#ifndef K15_GUI_TRUE
# define K15_GUI_TRUE 1
#endif

#ifndef K15_GUI_FALSE
# define K15_GUI_FALSE 0
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
	K15_GUI_RESULT_UNKNOWN_ERROR 				= 20
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
	K15_GIU_R_ALT_MODIFIER 	= 0x04,
	K15_GUI_SHIFT_MODIFIER 	= 0x08
} kg_keyboard_modifier_type;
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
	kg_u32 	offset;
	kg_u32 	sizeInBytes;
	void*	pNextHandle;
	void* 	pPreviousHandle;
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
	kg_crc32 	key;
	kg_element 	element;
	void* 		pNext;
} kg_hash_map_bucket;
/*********************************************************************************/
typedef struct
{
	kg_u32 					size;
	kg_u32					bucketCount;
	kg_hash_map_bucket** 	pBuckets;
	kg_buffer				bucketBuffer;
} kg_hash_map;
/*********************************************************************************/
typedef struct 
{
	const char* pFunction;
	const char* pDescription;
	const char* pIdentifier;
	kg_result 	result;
	void* 		pPrevious;
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
			kg_input_action_type		actionType;
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
	int bla;
} kg_render_command;
/*********************************************************************************/
typedef struct 
{
	kg_render_command* 	pFirstCommand;
	kg_render_command* 	pLastCommand;
	kg_bool 			inUse;
} kg_render_queue;
/*********************************************************************************/
typedef struct 
{
	kg_buffer 			buffer;
	kg_render_queue* 	pRenderQueues;
	kg_u32				renderQueueCount;
	kg_u32				activeRenderQueueIndex;	
} kg_render_queue_chain;
/*********************************************************************************/
typedef struct 
{
	kg_render_queue_chain*	pRenderQueueChain;
	kg_hash_map*			pElements;
	kg_element*				pRootElement;
	kg_error_stack* 		pErrorStack;
	kg_input_queue*			pInputQueue;
	kg_array				elementStack;
	kg_buffer 				memoryBuffer;
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
	size_t value;
} kg_render_queue_handle;
/*********************************************************************************/
typedef struct 
{
	kg_float2 origin;
	kg_float2 position;
	kg_float2 accumulatedSize;
	kg_float2 maxSize;
} kg_layout_state;

//how this should work:
// - Call gui logic (K15_GUIButton, K15_GUIBeginWindow, K15_GUIPushHorizontalLayout etc.)
// - Store elements internally in the gui context (just rects?) <-- headache
// - iterate over elements (layouting)
// - iterate over elements (input)
// - iterate over elements (rendering)
// - Call gui logic (next frame - retrieve results from last frame. Mainly results of the input)

//******************CONTEXT******************//
kg_def kg_result 				kg_create_context(kg_context_handle* pOutHandle);
kg_def kg_result 				kg_create_context_with_custom_memory(kg_context_handle* pOutHandle, void* pMemory, unsigned int memorySizeInBytes);

//*****************CONTROLS******************//
kg_def kg_result 				kg_begin_frame(kg_context_handle contextHandle);
kg_def void 					kg_begin_toolbar(kg_context_handle contextHandle, const char* p_Identifier);
kg_def kg_bool 					kg_begin_window(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def kg_bool  				kg_begin_menu(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def kg_bool 					kg_button(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def void						kg_label(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def void						kg_separator(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier);
kg_def void						kg_end_menu(kg_context_handle contextHandle);
kg_def void						kg_end_window(kg_context_handle contextHandle);
kg_def void						kg_end_toolbar(kg_context_handle contextHandle);
kg_def kg_result 				kg_end_frame(kg_context_handle contextHandle);


//*****************INPUT******************//
kg_def kg_result				kg_add_input_mouse_move(kg_context_handle contextHandle, unsigned short x, unsigned short y);
kg_def kg_result 				kg_add_input_mouse_button_down(kg_context_handle contextHandle, unsigned short x, unsigned short y, kg_mouse_button_type mouseButtonType);
kg_def kg_result 				kg_add_input_mouse_button_up(kg_context_handle contextHandle, unsigned short x, unsigned short y, kg_mouse_button_type 			mouseButtonType);

//*****************UTIL******************//
kg_def unsigned int 			kg_convert_result_to_string(kg_result p_Result, char* pMessageBuffer, unsigned int messageBufferSizeInBytes);
kg_def kg_result 				kg_calculate_row_major_projection_matrix(float* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def kg_result 				kg_calculate_column_major_projection_matrix(float* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def kg_bool 					kg_pop_error(kg_context_handle contextHandle, kg_error** pOutError);


kg_def kg_render_queue_handle	kg_lock_render_queue(kg_context_handle contextHandle);
kg_def kg_result 				kg_unlock_render_queue(kg_context_handle contextHandle, kg_render_queue_handle renderQueueHandle);
kg_def kg_bool 					kg_pop_render_command(kg_render_queue_handle renderQueueHandle, kg_render_command* pOutRenderCommand);

//*****************DEBUG*****************//


#ifdef K15_GUI_IMPLEMENTATION

#define kg_internal static

#ifndef K15_GUI_STRIP_DEBUG_RENDERING
# define K15_GUI_STRIP_DEBUG_RENDERING 0
#endif //K15_STRIP_DEBUG_RENDERING

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
# endif
# define kg_malloc(x, u) K15_GUI_CUSTOM_MALLOC(x, u)
#endif //K15_GUI_CUSTOM_MALLOC

#ifndef K15_GUI_CUSTOM_FREE
# include "malloc.h"
# define kg_free(x, u) free(x)
#else
# ifndef K15_GUI_CUSTOM_MALLOC
#  error "K15_GUI_CUSTOM_FREE defined without matching K15_GUI_CUSTOM_MALLOC"
# endif
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

#define kg_default_context_size kg_size_kilo_bytes(256)
#define kg_null_ptr (void*)(0)

typedef kg_u32 kg_code_point;

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

kg_internal kg_float2 kg_float2_max_individual(const kg_float2* pA, const kg_float2* pB)
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

kg_internal kg_bool kg_is_invalid_render_queue_handle(kg_render_queue_handle renderQueueHandle)
{
	return (renderQueueHandle.value == 0u);
}

kg_internal kg_bool kg_is_invalid_data_handle(const kg_data_handle* pHandle)
{
	if (pHandle == kg_null_ptr)
	{
		return K15_GUI_TRUE;
	}

	if (pHandle->offset == 0u && pHandle->sizeInBytes == 0u)
	{
		return K15_GUI_TRUE;
	}

	return K15_GUI_FALSE;
}

kg_internal kg_bool kg_is_invalid_buffer(const kg_buffer* pBuffer)
{
	if (pBuffer == kg_null_ptr)
	{
		return K15_GUI_TRUE;
	}

	if (!pBuffer->pMemory)
	{
		return K15_GUI_TRUE;
	}

	if (pBuffer->capacityInBytes == 0)
	{
		return K15_GUI_TRUE;
	}

	if (pBuffer->sizeInBytes > pBuffer->capacityInBytes)
	{
		return K15_GUI_TRUE;
	}

	return K15_GUI_FALSE;
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
		return kg_null_ptr;
	}

	if (pBuffer->sizeInBytes + sizeInBytes >= pBuffer->capacityInBytes)
	{
		return kg_null_ptr;
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
	const kg_u32 totalSizeInBytes = sizeof( kg_data_handle ) + sizeInBytes;

	if ( pBuffer == kg_null_ptr )
	{
		return kg_invalid_data_handle();
	}

	if ( ( pBuffer->sizeInBytes + totalSizeInBytes ) >= pBuffer->capacityInBytes )
	{
		return kg_invalid_data_handle();
	}

	kg_data_handle* pDataHandle 	= ( kg_data_handle* )( pBuffer->pMemory + pBuffer->sizeInBytes );
	pDataHandle->offset 			= pBuffer->sizeInBytes + sizeof( kg_data_handle );
	pDataHandle->sizeInBytes 		= sizeInBytes;
	pDataHandle->pNextHandle		= kg_null_ptr;
	pDataHandle->pPreviousHandle 	= pBuffer->pLastHandle;

	pBuffer->sizeInBytes += sizeInBytes + sizeof(kg_data_handle);

	if (pBuffer->pFirstHandle == kg_null_ptr)
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
	buffer.pFirstHandle 	= kg_null_ptr;
	buffer.pLastHandle 		= kg_null_ptr;
	return buffer;
}

kg_internal const kg_data_handle* kg_allocate_from_buffer(kg_buffer* pBuffer, kg_u32 sizeInBytes)
{
	return kg_create_data_handle(pBuffer, sizeInBytes);
}

kg_internal void kg_defragment_buffer(kg_buffer* pBuffer, const kg_data_handle* pHandle)
{
	kg_data_handle* pNextHandle = (kg_data_handle*)pHandle->pNextHandle;

	while( pNextHandle != kg_null_ptr)
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

	if (pHandle->pPreviousHandle != kg_null_ptr)
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
	pInputQueue->pFirstEvent 	= kg_null_ptr;
	pInputQueue->pLastEvent 	= kg_null_ptr;

	*pOutInputQueue = pInputQueue;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_create_render_queue_chain(kg_render_queue_chain** pOutRenderQueueChain, void* pMemory, kg_u32 memorySizeInBytes)
{
	if (memorySizeInBytes < sizeof(kg_render_queue_chain))
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	kg_byte* 	pRenderQueueChainMemory 			= (kg_byte*)pMemory + sizeof(kg_render_queue_chain);
	kg_u32		renderQueueChainMemorySizeInBytes 	= memorySizeInBytes -= sizeof(kg_render_queue_chain);

	kg_render_queue_chain* pRenderQueueChain = (kg_render_queue_chain*)pMemory;
	kg_buffer renderQueueChainBuffer = kg_create_buffer(pRenderQueueChainMemory, renderQueueChainMemorySizeInBytes);

	const kg_u32 renderQueueCount = 2u;

	pRenderQueueChain->pRenderQueues = kg_reserve_memory_from_current_buffer_position(&renderQueueChainBuffer, kg_ptr_size_in_bytes * renderQueueCount);

	if (pRenderQueueChain->pRenderQueues == kg_null_ptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	for (kg_u32 renderQueueIndex = 0u; renderQueueIndex < renderQueueCount; ++renderQueueIndex)
	{
		pRenderQueueChain->pRenderQueues[renderQueueIndex].pFirstCommand 	= kg_null_ptr;
		pRenderQueueChain->pRenderQueues[renderQueueIndex].pLastCommand 	= kg_null_ptr;
		pRenderQueueChain->pRenderQueues[renderQueueIndex].inUse 			= K15_GUI_FALSE;
	}

	pRenderQueueChain->buffer 					= renderQueueChainBuffer;
	pRenderQueueChain->renderQueueCount			= renderQueueCount;
	pRenderQueueChain->activeRenderQueueIndex 	= 0u;

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

	pErrorStack->pLastError 	= kg_null_ptr;
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
		return kg_null_ptr;
	}

	kg_hash_map_bucket* pBucket = (kg_hash_map_bucket*)kg_get_memory_from_buffer(pBucketBuffer, pBucketHandle);
	pBucket->key = identifier;
	return pBucket;
}

kg_internal kg_hash_map_bucket* kg_find_hash_element_bucket(kg_hash_map* pHashMap, kg_u32 bucketIndex, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	if (pHashMap == kg_null_ptr)
	{
		return kg_null_ptr;
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

kg_internal kg_element* kg_insert_hash_element(kg_hash_map* pHashMap, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	if (pHashMap == kg_null_ptr)
	{
		return kg_null_ptr;
	}

	const kg_u32 hashIndex = identifier % pHashMap->bucketCount;
	kg_hash_map_bucket* pBucket = pHashMap->pBuckets[hashIndex];

	if (pHashMap->pBuckets[hashIndex] != kg_null_ptr)
	{
		pBucket = kg_find_hash_element_bucket(pHashMap, hashIndex, identifier, pOutIsNew);
	}

	if (pBucket)
	{
		*pOutIsNew = K15_GUI_FALSE;
		return &pBucket->element;
	}

	*pOutIsNew = K15_GUI_TRUE;

	pBucket = kg_allocate_bucket(pHashMap, identifier);

	if( pBucket == kg_null_ptr )
	{
		return kg_null_ptr;
	}

	pBucket->pNext = pHashMap->pBuckets[hashIndex];

	pHashMap->pBuckets[ hashIndex ] = pBucket;

	return &pBucket->element;
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
		return K15_GUI_FALSE;
	}

	const kg_data_handle* pArrayDataHandle = pArray->pDataHandle;

	if (kg_is_invalid_data_handle(pArrayDataHandle))
	{
		return K15_GUI_FALSE;
	}

	const kg_u32 newCapacity = pArray->capacity * 2u;
	const kg_data_handle* pNewArrayDataHandle = kg_allocate_from_buffer(pArray->pBuffer, newCapacity * pArray->elementSizeInBytes);

	if (kg_is_invalid_data_handle(pNewArrayDataHandle))
	{
		return K15_GUI_FALSE;
	}

	void* pArrayMemory 		= kg_get_memory_from_buffer(pArray->pBuffer, pArrayDataHandle);
	void* pNewArrayMemory 	= kg_get_memory_from_buffer(pArray->pBuffer, pNewArrayDataHandle);

	kg_memcpy(pNewArrayMemory, pArrayMemory, pArray->capacity * pArray->elementSizeInBytes);
	kg_free_from_buffer(pArray->pBuffer, pArrayDataHandle);

	pArray->capacity 	= newCapacity;
	pArray->pDataHandle = pNewArrayDataHandle;

	return K15_GUI_TRUE;
}

kg_internal kg_render_queue_handle kg_invalid_render_queue_handle()
{
	static const kg_render_queue_handle invalidHandle = { 0u };
	return invalidHandle;
}

kg_internal kg_array kg_invalid_array()
{
	static const kg_array invalidArray = { kg_null_ptr, kg_null_ptr, 0u, 0u, 0u };
	return invalidArray;
}

kg_internal kg_bool kg_is_invalid_array(kg_array* pArray)
{
	if (pArray == kg_null_ptr)
	{
		return K15_GUI_TRUE;
	}

	if (kg_is_invalid_data_handle(pArray->pDataHandle))
	{
		return K15_GUI_TRUE;
	}

	if (pArray->elementSizeInBytes == 0u)
	{
		return K15_GUI_TRUE;
	}

	if (pArray->capacity == 0u)
	{
		return K15_GUI_TRUE;
	}

	return K15_GUI_FALSE;
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
	if (ppOutElement == kg_null_ptr)
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
	if( ppOutElement == kg_null_ptr )
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

	if (pElement == kg_null_ptr)
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
			return kg_null_ptr;
		}

		pElement->size 				= kg_float2_zero();
		pElement->position 			= kg_float2_zero();
		pElement->padding			= kg_float4_zero();
		pElement->margin			= kg_float4_zero();
		pElement->border			= kg_float4_zero();
		pElement->identifier 		= identifierHash;
		for (kg_u32 componentIndex = 0u; componentIndex < K15_GUI_COMPONENT_COUNT; ++componentIndex)
		{
			pElement->componentHandles[componentIndex] = kg_null_ptr;
		}

#ifdef K15_GUI_STORE_IDENTIFIER_STRING
		pElement->p_Identifier		= pIdentifier;
#endif
	}

	kg_clear_array(&pElement->childArray);

	kg_element* pParent = kg_null_ptr;
	
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

	pInputQueue->pFirstEvent 	= kg_null_ptr;
	pInputQueue->pLastEvent 	= kg_null_ptr;

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
	pLayoutState->maxSize = kg_float2_max_individual(&pLayoutState->maxSize, &elementSize);

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
		kg_element* pChild = kg_null_ptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);

		kg_advance_layout_vertical(&layoutState, pChild);
	}

	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_null_ptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);
		kg_layout_pass(pChild);
	}
}

kg_internal void kg_advance_layout_horizontal(kg_layout_state* pLayoutState, kg_element* pElement)
{
	pElement->position = kg_calculate_element_position(pLayoutState, pElement);

	const kg_float2 elementSize = kg_calculate_element_size_with_margin(pElement);
	pLayoutState->maxSize = kg_float2_max_individual(&pLayoutState->maxSize, &elementSize);

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
		kg_element* pChild = kg_null_ptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);

		kg_advance_layout_horizontal(&layoutState, pChild);
	}

	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_null_ptr;
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

kg_internal void kg_render_element(kg_element* pElement)
{

}

kg_internal void kg_render_pass(kg_element* pElement)
{
	kg_render_element(pElement);
}

kg_internal void kg_push_error(kg_context* pContext, const char* pFunction, const char* pDescription, const char* pIdentifier, kg_result result)
{
	if (pContext == kg_null_ptr)
	{
		return;
	}

	kg_error_stack* pErrorStack = pContext->pErrorStack;
	kg_error* 		pError		= kg_reserve_memory_from_current_buffer_position(&pErrorStack->errorBuffer, sizeof(kg_error));

	if (pError == kg_null_ptr)
	{
		return;
	}

	pError->pFunction	 	= pFunction;
	pError->pDescription 	= pDescription;
	pError->pIdentifier		= pIdentifier;
	pError->result			= result;
	pError->pPrevious		= kg_null_ptr;

	if (pErrorStack->pLastError == kg_null_ptr)
	{
		pErrorStack->pLastError = pError;
	}
	else
	{
		pError->pPrevious = pErrorStack->pLastError;
		pErrorStack->pLastError = pError;
	}
}

/******************************INPUT LOGIC****************************************/
kg_internal kg_input_event* kg_allocate_input_event(kg_input_queue* pInputQueue, kg_input_type inputType)
{
	kg_input_event* pInputEvent = (kg_input_event*)kg_reserve_memory_from_current_buffer_position(&pInputQueue->buffer, sizeof(kg_input_event));
	
	if( pInputEvent == kg_null_ptr)
	{
		return kg_null_ptr;
	}

	if (pInputQueue->pFirstEvent == kg_null_ptr)
	{
		pInputQueue->pFirstEvent = pInputEvent;
	}
	else
	{
		pInputQueue->pLastEvent->pNext = pInputEvent;
	}

	pInputQueue->pLastEvent = pInputEvent;
	pInputEvent->pNext 		= kg_null_ptr;
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
	if (pElement->componentHandles[K15_GUI_WINDOW_COMPONENT] == kg_null_ptr)
	{
		const kg_data_handle* pWindowComponentHandle = kg_allocate_from_buffer(&pContext->memoryBuffer, sizeof(kg_window_component));

		if (kg_is_invalid_data_handle(pWindowComponentHandle))
		{
			return kg_null_ptr;
		}

		kg_window_component* pWindowComponent = (kg_window_component*)kg_get_memory_from_buffer(&pContext->memoryBuffer, pWindowComponentHandle);
		pWindowComponent->flags 			= K15_GUI_WINDOW_FLAG_IS_OPEN;
		pWindowComponent->originalSize 		= kg_float2_zero();
		pWindowComponent->originalPosition 	= kg_float2_zero();
		pWindowComponent->pText 			= kg_null_ptr;

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
		return K15_GUI_FALSE;
	}

	if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED ) != 0 )
	{
		if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_IS_MAXIMIZED ) == 0 )
		{
			pComponent->originalPosition = pElement->position;
			pComponent->originalSize = pElement->size;
			pComponent->flags |= K15_GUI_WINDOW_FLAG_IS_MAXIMIZED;	
			pComponent->flags &= ~K15_GUI_WINDOW_FLAG_IS_MINIMIZED;
		}
		else
		{
			pElement->size = pComponent->originalSize;
			pElement->position = pComponent->originalPosition;
			
			pComponent->flags &= ~K15_GUI_WINDOW_FLAG_IS_MAXIMIZED;
		}

		pComponent->flags &= ~K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED;
	}

	if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED ) != 0 )
	{
		if ( ( pComponent->flags & K15_GUI_WINDOW_FLAG_IS_MINIMIZED ) == 0)
		{
			pComponent->originalPosition = pElement->position;
			pComponent->originalSize = pElement->size;
			pComponent->flags |= K15_GUI_WINDOW_FLAG_IS_MINIMIZED;	
		}
		else
		{
			pElement->size = pComponent->originalSize;
			pElement->position = pComponent->originalPosition;

			pComponent->flags &= ~K15_GUI_WINDOW_FLAG_IS_MINIMIZED;	
		}

		pComponent->flags &= ~K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED;
	}

	return (pComponent->flags & K15_GUI_WINDOW_FLAG_IS_OPEN);
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

kg_result kg_create_context(kg_context_handle* pOutHandle)
{
	kg_byte* pMemory = kg_malloc(kg_default_context_size, 0u);

	if (pMemory == kg_null_ptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}	

	return kg_create_context_with_custom_memory( pOutHandle, pMemory, kg_default_context_size );
}

kg_result kg_create_context_with_custom_memory(kg_context_handle* pOutHandle, void* pMemory, unsigned int memorySizeInBytes)
{
	if (pOutHandle == kg_null_ptr)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pMemory == kg_null_ptr)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (memorySizeInBytes == 0u)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_buffer memoryBuffer = kg_create_buffer(pMemory, memorySizeInBytes);

	const kg_u32 hashMapDataSize 			= kg_size_kilo_bytes(64);
	const kg_u32 errorStackDataSize 		= kg_size_kilo_bytes(16);
	const kg_u32 inputBufferDataSize		= kg_size_kilo_bytes(16);
	const kg_u32 renderQueueChainDataSize	= kg_size_kilo_bytes(32);

	const kg_u32 totalDataSize = sizeof(kg_context) + hashMapDataSize + errorStackDataSize + inputBufferDataSize + renderQueueChainDataSize;

	kg_u8* pDataMemory = (kg_u8*)kg_reserve_memory_from_current_buffer_position(&memoryBuffer, totalDataSize);

	if (pDataMemory == kg_null_ptr)
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

	pContext->memoryBuffer = memoryBuffer;
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
	
	result = kg_create_render_queue_chain(&pContext->pRenderQueueChain, pRenderQueueChainMemory, renderQueueChainDataSize);

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

kg_result kg_begin_frame(kg_context_handle contextHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;
	kg_clear_array(&pContext->elementStack);

	pContext->pRootElement = kg_allocate_element( pContext, "ROOT_ELEMENT" );
	kg_array_push_back( &pContext->elementStack, &pContext->pRootElement );
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
		return K15_GUI_FALSE;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;

	const kg_utf8* pText = kg_find_text(pContext, pTextID);
	kg_element* pElement = kg_allocate_element(pContext, pIdentifier);

	if (!pElement)
	{
		kg_push_error(pContext, "kg_begin_window", "Could not allocate element.", pIdentifier, K15_GUI_RESULT_OUT_OF_MEMORY);
		return K15_GUI_FALSE;
	}

	kg_window_component* pWindowComponent = kg_allocate_window_component(pContext, pElement);

	if (!pWindowComponent)
	{
		kg_push_error(pContext, "kg_begin_window", "Could not allocate window component.", pIdentifier, K15_GUI_RESULT_OUT_OF_MEMORY);
		return K15_GUI_FALSE;
	}

	pWindowComponent->pText = pText;

	if (kg_array_push_back(&pContext->elementStack, &pElement) != K15_GUI_RESULT_SUCCESS)
	{
		return K15_GUI_FALSE;
	}
	
	return kg_window_logic(pContext, pElement, pWindowComponent);
}

kg_bool kg_begin_menu(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_FALSE;
	}
}

kg_bool kg_button(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_FALSE;
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
	kg_render_pass(pContext->pRootElement);
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

	kg_context* 	 	pContext 		= (kg_context*)contextHandle.value;
	kg_input_queue* 	pInputQueue 	= pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_MOUSE_MOVE);
	
	if (pInputEvent == kg_null_ptr)
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

	kg_context* 	 	pContext 		= (kg_context*)contextHandle.value;
	kg_input_queue* 	pInputQueue 	= pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_MOUSE_MOVE);
	
	if (pInputEvent == kg_null_ptr)
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
	kg_context* 	 	pContext 		= (kg_context*)contextHandle.value;
	kg_input_queue* 	pInputQueue 	= pContext->pInputQueue;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputQueue, K15_GUI_INPUT_TYPE_MOUSE_MOVE);
	
	if (pInputEvent == kg_null_ptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.mouse_button.x 			= x;
	pInputEvent->data.mouse_button.y 			= y;
	pInputEvent->data.mouse_button.buttonType 	= mouseButtonType;
	pInputEvent->data.mouse_button.actionType	= K15_GUI_ACTION_BUTTON_UP;

	return K15_GUI_RESULT_SUCCESS;

}

kg_bool kg_pop_error(kg_context_handle contextHandle, kg_error** pOutError)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_FALSE;
	}

	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_error_stack* pErrorStack = pContext->pErrorStack;
	kg_error* 		pLastError 	= pErrorStack->pLastError;

	if (pLastError == kg_null_ptr)
	{
		return K15_GUI_FALSE;
	}

	pErrorStack->pLastError = pLastError->pPrevious;
	*pOutError = pLastError;

	return K15_GUI_TRUE;
}

kg_render_queue_handle kg_lock_render_queue(kg_context_handle contextHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return kg_invalid_render_queue_handle();
	}

	kg_context* pContext 						= (kg_context*)contextHandle.value;
	kg_render_queue_chain* pRenderQueueChain 	= pContext->pRenderQueueChain;

	kg_render_queue_handle renderQueueHandle = {0};
	return renderQueueHandle;
}

kg_result kg_unlock_render_queue(kg_context_handle contextHandle, kg_render_queue_handle renderQueueHandle)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	return K15_GUI_RESULT_SUCCESS;
}

kg_bool kg_pop_render_command(kg_render_queue_handle renderQueueHandle, kg_render_command* pOutRenderCommand)
{
	if (kg_is_invalid_render_queue_handle(renderQueueHandle))
	{
		return K15_GUI_FALSE;
	}

	return K15_GUI_FALSE;
}


#endif //K15_GUI_IMPLEMENTATION
#endif //_K15_GUILayer_Context_h_
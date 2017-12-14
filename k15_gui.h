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

typedef unsigned int 		kg_crc32;
typedef unsigned int 		kg_color32;
typedef unsigned char 		kg_byte;
typedef unsigned char 		kg_bool;
typedef unsigned char 		kg_utf8;

/*********************************************************************************/
typedef enum 
{
	K15_GUI_RESULT_SUCCESS 						= 0,
	K15_GUI_RESULT_OUT_OF_MEMORY 				= 1,
	K15_GUI_RESULT_FONT_DATA_ERROR 				= 2,
	K15_GUI_RESULT_NOT_SUPPORTED 				= 3,
	K15_GUI_RESULT_FILE_NOT_FOUND 				= 4,
	K15_GUI_RESULT_EMPTY_CLIP_RECT 				= 5,
	K15_GUI_RESULT_INVALID_ARGUMENTS 			= 6,
	K15_GUI_RESULT_OUT_OF_RANGE 				= 7,
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
	K15_GUI_MOUSE_BUTTON_PRESSED = 0,
	K15_GUI_MOUSE_BUTTON_RELEASED,
	K15_GUI_MOUSE_WHEEL_UP,
	K15_GUI_MOUSE_WHEEL_DOWN,
	K15_GUI_MOUSE_MOVED
} kg_mouse_input_type;
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
	K15_GUI_KEY_PRESSED = 0,
	K15_GUI_KEY_RELEASED,
	K15_GUI_TEXT_INPUT
} kg_keyboard_input_type;
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
	K15_GUI_WINDOW_RESIZED = 0,
	K15_GUI_SYSTEM_EVENT_COUNT
} kg_system_event_type;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_MOUSE_INPUT_TYPE = 0,
	K15_GUI_KEYBOARD_INPUT_TYPE,
	K15_GUI_GAMEPAD_INPUT_TYPE
} kg_input_event_type;
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

	kg_mouse_input_type type;
} kg_mouse_event;
/*********************************************************************************/
typedef struct 
{
	struct
	{
		kg_u16 key;
		kg_u16 modifierMask;
	} keyInput;

	kg_keyboard_input_type 		type;
	kg_keyboard_key_type 		keyType;
	kg_keyboard_modifier_type 	modifier;
} kg_keyboard_event;
/*********************************************************************************/
typedef struct 
{
	kg_system_event_type type;

	union
	{
		struct
		{
			kg_u16 width;
			kg_u16 height;
		} size;
	} params;
} kg_system_event;
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
#ifdef K15_GUI_STORE_IDENTIFIER_STRING
	const char* pIdentifier;
#endif
	kg_u32 		childCount;
	kg_u32 		frameUseCounter;
	kg_crc32 	identifier;
	kg_float2	position;
	kg_float2	size;
	kg_float2	fixedSize;
} kg_element;
/*********************************************************************************/
typedef struct _kg_hash_map_bucket
{
	kg_crc32 	key;
	kg_element 	element;
	void* 		pNext;
} kg_hash_map_bucket;
/*********************************************************************************/
typedef struct
{
	kg_u32 					size;
	kg_hash_map_bucket** 	pBuckets;
	kg_buffer*				pBucketBuffer;
} kg_hash_map;
/*********************************************************************************/
typedef struct 
{
	const char* pErrorString;
	kg_result result;
} kg_error;
/*********************************************************************************/
typedef struct
{
	kg_u32 bla;
} kg_resource_database;
/*********************************************************************************/
typedef struct 
{
	kg_float2 position;
	kg_float2 size;
} kg_rect;
/*********************************************************************************/
typedef struct
{
	kg_u32 bla;
} kg_font;
/*********************************************************************************/
typedef struct
{
	kg_u32 bla;
} kg_icon;
/*********************************************************************************/
typedef struct
{
	kg_u32 bla;
} kg_context_events;
/*********************************************************************************/
typedef struct
{
	kg_u32 bla;
	kg_input_event_type type;
} kg_input_event;
/*********************************************************************************/
typedef struct
{
	kg_u32 			inputCount;
	kg_input_event* pInputEvents;
} kg_input_buffer;
/*********************************************************************************/
typedef struct 
{
	kg_hash_map*				pElements;
	kg_element*					pRootElement;
	kg_error* 					pErrorStack;
	kg_resource_database* 		pResourceDatabase;
	kg_input_buffer*			pInputBuffer;
	kg_buffer 					memoryBuffer;
	kg_rect 					clipRect;
	kg_u32						errorCount;
	kg_u32 						frameCounter;
} kg_context;
/*********************************************************************************/

//how this should work:
// - Call gui logic (K15_GUIButton, K15_GUIBeginWindow, K15_GUIPushHorizontalLayout etc.)
// - Store elements internally in the gui context (just rects?) <-- headache
// - iterate over elements (layouting)
// - iterate over elements (input)
// - iterate over elements (rendering)
// - Call gui logic (next frame - retrieve results from last frame. Mainly results of the input)

kg_def kg_result 	kg_create_context(kg_context** pContext, kg_resource_database* pContextResources);
kg_def kg_result 	kg_create_context_with_custom_memory(kg_context** pContext, kg_resource_database* pContextResources, void* pMemory, unsigned int memorySizeInBytes);

//*****************RESOURCES******************//
kg_def kg_result 	kg_create_resource_database(kg_resource_database** pResourceDatabase);
kg_def kg_result 	kg_create_resource_database_with_custom_memory(kg_resource_database** pResourceDatabase, const char* pDatabaseMemory, unsigned int databaseMemorySizeInBytes);


//************FONTS*************//
kg_def kg_result 	kg_create_font_resource_from_file(kg_resource_database* pResourceDatabase, kg_font** pOutFont, const kg_utf8* pFontFilePath, unsigned short fontSizeInPixels, const char* pFontName);
kg_def kg_result 	kg_create_font_resource_from_memory(kg_resource_database* pResourceDatabase, kg_font** pOutFont, kg_byte* pFontBuffer, kg_u8 fontSizeInPixels, const char* pFontName);
kg_def kg_result 	kg_get_font_resource(kg_resource_database* pResourceDatabase, kg_font** pOutFont, const char* pFontName);


//************ICONS*************//
kg_def kg_result 	kg_create_icon_resource_from_file(kg_resource_database* pGUIResourceDatabase, const kg_utf8* pIconFilePath, const char* pIconName);
kg_def kg_result 	kg_create_icon_resource_from_memory(kg_resource_database* pGUIResourceDatabase, kg_byte* pIconMemoryBuffer, kg_u32 iconFileDataBufferSizeInBytes, const char* pIconName);
kg_def kg_result 	kg_create_icon_resource_from_memory_raw(kg_resource_database* pGUIResourceDatabase, kg_byte* pIconMemoryBuffer, kg_u32 width, kg_u32 geight, kg_u8 colorComponents, const char* pIconName);
kg_def kg_result 	kg_get_icon_resource(kg_resource_database* p_GUIResourceDatabase, kg_icon** pOutIcon, const char* pIconName);


//*****************CONTROLS******************//
kg_def kg_result 	kg_begin_frame(kg_context* pContext);
kg_def void 		kg_begin_toolbar(kg_context* pContext, const char* p_Identifier);

kg_def kg_bool 		kg_begin_window(kg_context* pContext, const char* pTextID, const char* pIdentifier);

kg_def kg_bool  	kg_begin_menu(kg_context* pContext, const char* pTextID, const char* pIdentifier);
kg_def kg_bool 		kg_button(kg_context* pContext, const char* pTextID, const char* pIdentifier);
kg_def void			kg_label(kg_context* pContext, const char* pTextID, const char* pIdentifier);
kg_def void			kg_separator(kg_context* pContext, const char* pTextID, const char* pIdentifier);
kg_def void			kg_end_menu(kg_context* pContext);
kg_def void			kg_end_window(kg_context* pContext);
kg_def void			kg_end_toolbar(kg_context* pContext);
kg_def kg_result 	kg_end_frame(kg_context* pContext);


//*****************INPUT******************//
kg_def kg_result 	kg_add_mouse_input(kg_context_events* pContextEvents, kg_mouse_event mouseInput);
kg_def kg_result 	kg_add_keyboard_input(kg_context_events* pContextEvents, kg_keyboard_event keyboardInput);
kg_def kg_result 	kg_add_system_event(kg_context_events* pContextEvents, kg_system_event systemEvent);


//*****************UTIL******************//
kg_def unsigned int kg_convert_result_to_string(kg_result p_Result, char* pMessageBuffer, unsigned int messageBufferSizeInBytes);
kg_def kg_result 	kg_calculate_row_major_projection_matrix(float* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def kg_result 	kg_calculate_column_major_projection_matrix(float* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def kg_bool 		kg_pop_error(kg_context* pContext, kg_error** pOutError);


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
# define kg_malloc(x, u) (u); malloc(x)
#else
# ifndef K15_GUI_CUSTOM_FREE
#  error "K15_GUI_CUSTOM_MALLOC defined without matching K15_GUI_CUSTOM_FREE"
# endif
# define kg_malloc(x, u) K15_GUI_CUSTOM_MALLOC(x, u)
#endif //K15_GUI_CUSTOM_MALLOC

#ifndef K15_GUI_CUSTOM_FREE
# include "malloc.h"
# define kg_free(x, u) (u); free(x)
#else
# ifndef K15_GUI_CUSTOM_MALLOC
#  error "K15_GUI_CUSTOM_FREE defined without matching K15_GUI_CUSTOM_MALLOC"
# endif
# define kg_free(x, u) K15_GUI_CUSTOM_FREE(x, u);
#endif //K15_GUI_CUSTOM_FREE

static const kg_u32 kg_ptr_size_in_bytes = sizeof(void*);

#define kg_size_kilo_bytes(n) (n*1024)
#define kg_size_mega_bytes(n) (n*1024*1024)

#define kg_default_context_size kg_size_kilo_bytes(128)

typedef struct
{
	kg_u32 	offset;
	kg_u32 	sizeInBytes;
	void*	pNextHandle;
	void* 	pPreviousHandle;
} kg_data_handle;

typedef struct
{
	kg_bool 		isOpen;
	kg_bool 		isMaximized;
	kg_bool 		isMinimized;
	kg_float2		originalSize;
	const kg_utf8* 	pText;
} kg_window_component;

kg_internal kg_float2 kg_f2_zero()
{
	static const kg_float2 zero = {0.f, 0.f};
	return zero;
}

kg_internal const kg_data_handle* kg_invalid_data_handle()
{
	static const kg_data_handle invalidDataHandles = {0u, 0u};
	return &invalidDataHandles;
}

kg_internal const kg_data_handle* kg_create_data_handle(kg_buffer* pBuffer, kg_u32 sizeInBytes)
{
	const kg_u32 totalSizeInBytes = sizeof( kg_data_handle ) + sizeInBytes;

	if ( pBuffer == 0 )
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
	pDataHandle->pNextHandle		= 0;
	pDataHandle->pPreviousHandle 	= pBuffer->pLastHandle;

	if (pBuffer->pFirstHandle == 0)
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

kg_internal kg_bool kg_is_invalid_data_handle(const kg_data_handle* pHandle)
{
	if (!pHandle)
	{
		return K15_GUI_TRUE;
	}

	if (pHandle->offset == 0u && pHandle->sizeInBytes == 0u)
	{
		return K15_GUI_TRUE;
	}

	return K15_GUI_FALSE;
}

kg_internal kg_buffer kg_create_buffer(void* pMemory, kg_u32 capacityInBytes)
{
	kg_buffer buffer;
	buffer.pMemory 			= pMemory;
	buffer.sizeInBytes 		= 0u;
	buffer.capacityInBytes 	= capacityInBytes;
	buffer.pFirstHandle 	= 0;

	return buffer;
}

kg_internal const kg_data_handle* kg_allocate_from_buffer(kg_buffer* pBuffer, kg_u32 sizeInBytes)
{
	return kg_create_data_handle(pBuffer, sizeInBytes);
}

kg_internal void kg_defragment_buffer(kg_buffer* pBuffer, kg_data_handle* pHandle)
{
	kg_data_handle* pNextHandle = (kg_data_handle*)pHandle->pNextHandle;

	while( pNextHandle )
	{
		pNextHandle->offset = pHandle->offset;
		pNextHandle 		= (kg_data_handle*)pNextHandle->pNextHandle;
	}
}

kg_internal void kg_free_from_buffer(kg_buffer* pBuffer, kg_data_handle* pHandle)
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

	if (pBuffer->pPreviousHandle != 0)
	{
		kg_data_handle* pPreviousHandle = (kg_data_handle*)pBuffer->pPreviousHandle;
		pPreviousHandle->pNextHandle = pHandle->pNextHandle;
	}

	pBuffer->sizeInBytes -= pHandle->sizeInBytes;
}

kg_internal kg_byte* kg_get_memory_from_buffer(kg_buffer* pBuffer, kg_data_handle* pHandle)
{
	return pBuffer->pMemory + pHandle->offset;
}

kg_internal kg_hash_map* kg_create_hash_map(kg_buffer* pBuffer)
{
	const kg_data_handle* pHashMapDataHandle = kg_allocate_from_buffer(pBuffer, sizeof(kg_hash_map));

	if (kg_is_invalid_data_handle(pHashMapDataHandle))
	{
		return 0;
	}

	const kg_u32 defaultBucketCount 			= 100u;
	const kg_data_handle* pBucketArrayHandle 	= kg_allocate_from_buffer(pBuffer, kg_ptr_size_in_bytes * defaultBucketCount);

	if (kg_is_invalid_data_handle(pBucketArrayHandle))
	{
		return 0;
	}

	kg_hash_map* pHashMap 	= (kg_hash_map*)kg_get_memory_from_buffer(pBuffer, &hashMapDataHandle);
	pHashMap->size 			= 0u;
	pHashMap->pBuckets  	= (kg_hash_map_bucket**)kg_get_memory_from_buffer(pBuffer, &bucketArrayDataHandle);
	pHashMap->pBucketBuffer = pBuffer;

	return pHashMap;
}

kg_internal kg_hash_map_bucket* kg_allocate_bucket(kg_hash_map* pHashMap, kg_crc32 identifier)
{
	kg_buffer* pBucketBuffer = pHashMap->pBucketBuffer;

	kg_data_handle* pBucketHandle = kg_allocate_from_buffer(pBucketBuffer, sizeof(kg_hash_map_bucket));

	if (kg_is_invalid_data_handle(&bucketHandle))
	{
		return 0;
	}

	kg_hash_map_bucket* pBucket = (kg_hash_map_bucket*)kg_get_memory_from_buffer(pBucketBuffer, pBucketHandle);
	pBucket->dataHandle = bucketHandle;
	pBucket->key 		= identifier;
	return pBucket;
}

kg_internal kg_hash_map_bucket* kg_find_hash_element_bucket(kg_hash_map* pHashMap, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	if (pHashMap == 0u)
	{
		return 0u;
	}

	kg_hash_map_bucket* pBucket = pHashMap->pBuckets[identifier];

	while (pBucket)
	{
		if (pBucket->key == identifier)
		{
			break;
		}

		pBucket = pBucket->pNext;
	}

	kg_assert(pBucket);

	return pBucket;
}

kg_internal kg_element* kg_insert_hash_element(kg_hash_map* pHashMap, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	if (pHashMap == 0u)
	{
		return 0u;
	}

	const kg_u32 hashIndex = identifier % pHashMap->size;
	kg_hash_map_bucket* pBucket = pHashMap->pBuckets[hashIndex];

	if (pHashMap->pBuckets[hashIndex] != 0)
	{
		pBucket = kg_find_hash_element_bucket(pHashMap, hashIndex, pOutIsNew);
	}

	if (pBucket)
	{
		*pOutIsNew = K15_GUI_FALSE;
		return &pBucket->element;
	}

	*pOutIsNew = K15_GUI_TRUE;

	pBucket = kg_allocate_bucket(pHashMap, identifier);
	pBucket->pNext = pHashMap->pBuckets[hashIndex];

	return &pBucket->element;
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

	while (*pIdentifier == 0)
	{
		unsigned char byte = (unsigned char)*pIdentifier++;
		crcIndex = (crc | byte) & 0xFF;

		crc = (crc << 8u) ^ crc_table[crcIndex];
	}

	crc = crc ^ 0xFFFFFFFF;

	return crc;
}

kg_internal kg_element* kg_allocate_element(kg_context* pContext, const char* pIdentifier)
{
	kg_crc32 identifierHash = kg_generate_crc32(pIdentifier);

	kg_bool isNew = 0u;
	kg_element* pElement = kg_insert_hash_element(pContext->pElements, identifierHash, &isNew);

	if (isNew)
	{
		pElement->size 				= kg_f2_zero();
		pElement->position 			= kg_f2_zero();
		pElement->identifier 		= kg_generate_crc32(pIdentifier);
#ifdef K15_GUI_STORE_IDENTIFIER_STRING
		pElement->p_Identifier		= pIdentifier;
#endif
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
	switch (pInputEvent->type)
	{
		case K15_GUI_MOUSE_INPUT_TYPE:
			kg_process_mouse_input(pContext, pInputEvent);
			break;

		case K15_GUI_KEYBOARD_INPUT_TYPE:
			kg_process_keyboard_input(pContext, pInputEvent);
			break;

		case K15_GUI_GAMEPAD_INPUT_TYPE:
			kg_process_gamepad_input(pContext, pInputEvent);
			break;
	}
}

kg_internal void kg_process_input_events(kg_context* pContext)
{
	kg_input_event* pInputEvent = 0;
	kg_input_buffer* pInputBuffer = pContext->pInputBuffer;

	for (kg_u32 inputIndex = 0u; inputIndex < pInputBuffer->inputCount; ++inputIndex)
	{
		pInputEvent = pInputBuffer->pInputEvents + inputIndex;
		kg_process_input_event(pContext, pInputEvent);
	}

	pInputBuffer->inputCount = 0u;
}

kg_internal void kg_process_input(kg_input_buffer* pInputBuffer)
{

}

kg_internal void kg_input_pass(kg_element* pElement)
{

}

kg_internal void kg_layout_element(kg_element* pElement)
{

}

kg_internal void kg_layout_pass(kg_element* pElement)
{
	kg_layout_element(pElement);

	for(kg_u32 childIndex = 0u; childIndex < pElement->childCount; ++childIndex)
	{
	}
}

kg_internal void kg_render_element(kg_element* pElement)
{

}

kg_internal void kg_render_pass(kg_element* pElement)
{
	kg_render_element(pElement);

	for (kg_u32 childIndex = 0u; childIndex < pElement->childCount; ++childIndex)
	{
	}
}

/*********************************************************************************/
/*****************************RESOURCE LOGIC**************************************/
/*********************************************************************************/
kg_internal const kg_utf8* kg_find_text(kg_context* pContext, const char* pTextID)
{
	return 0;
}


/*********************************************************************************/
/*****************************CONTROL LOGIC***************************************/
/*********************************************************************************/
kg_window_component* kg_allocate_window_component(kg_context* pContext, kg_element* pElement)
{
	return 0;
}

kg_internal kg_bool kg_window_logic(kg_context* pContext, kg_element* pElement, kg_window_component* pComponent)
{
	if (pComponent->isMaximized)
	{
		pComponent->originalSize 	= pElement->size;
		pElement->fixedSize 		= pContext->pRootElement->fixedSize;
	}

	if (pComponent->isMinimized)
	{

	}

	return pComponent->isOpen;
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

kg_result kg_create_context(kg_context** pContext, kg_resource_database* pContextResources)
{
	kg_byte* pMemory = kg_malloc(kg_default_context_size, 0u);

	if (!pMemory)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}	

	return kg_create_context_with_custom_memory( pContext, pContextResources, pMemory, kg_default_context_size );
}

kg_result kg_create_context_with_custom_memory(kg_context** pContext, kg_resource_database* pContextResources, void* pMemory, unsigned int memorySizeInBytes)
{
	if (!pMemory)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (memorySizeInBytes == 0u)
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_buffer memoryBuffer = kg_create_buffer(pMemory, memorySizeInBytes);

	const kg_u32 hashMapDataSize 		= kg_size_kilo_bytes(64);
	const kg_u32 errorStackDataSize 	= kg_size_kilo_bytes(16);
	const kg_u32 inputBufferDataSize	= kg_size_kilo_bytes(16);

	kg_data_handle* pHashMapDataHandle 		= kg_allocate_from_buffer(&memoryBuffer, hashMapDataSize);
	kg_data_handle* pErrorStackDataHandle 	= kg_allocate_from_buffer(&memoryBuffer, errorStackDataSize);
	kg_data_handle* pInputBufferDataHandle 	= kg_allocate_from_buffer(&memoryBuffer, inputBufferDataSize);

	pContext->pElements = kg_create_hash_
	kg_hash_map*				pElements;
	kg_element*					pRootElement;
	kg_error* 					pErrorStack;
	kg_resource_database* 		pResourceDatabase;
	kg_input_buffer*			pInputBuffer;
	kg_buffer 					memoryBuffer;
	kg_rect 					clipRect;
	kg_u32						errorCount;
	kg_u32 						frameCounter;


}

kg_result kg_begin_frame(kg_context* pContext)
{

}

void kg_begin_toolbar(kg_context* pContext, const char* p_Identifier)
{

}

kg_bool kg_begin_window(kg_context* pContext, const char* pTextID, const char* pIdentifier)
{
	const kg_utf8* pText = kg_find_text(pContext, pTextID);
	kg_element* pElement = kg_allocate_element(pContext, pIdentifier);

	if (!pElement)
	{
		return K15_GUI_FALSE;
	}

	kg_window_component* pWindowComponent = kg_allocate_window_component(pContext, pElement);

	if (!pWindowComponent)
	{
		return K15_GUI_FALSE;
	}

	pWindowComponent->pText = pText;
		
	return kg_window_logic(pContext, pElement, pWindowComponent);
}

kg_bool kg_begin_menu(kg_context* pContext, const char* pTextID, const char* pIdentifier)
{

}

kg_bool kg_button(kg_context* pContext, const char* pTextID, const char* pIdentifier)
{

}

void kg_label(kg_context* pContext, const char* pTextID, const char* pIdentifier)
{

}

void kg_separator(kg_context* pContext, const char* pTextID, const char* pIdentifier)
{

}

void kg_end_menu(kg_context* pContext)
{

}

void kg_end_window(kg_context* pContext)
{

}

void kg_end_toolbar(kg_context* pContext)
{

}

kg_result kg_end_frame(kg_context* pContext)
{
	kg_process_input(pContext->pInputBuffer);
	kg_input_pass(pContext->pRootElement);
	kg_layout_pass(pContext->pRootElement);
	kg_render_pass(pContext->pRootElement);
	++pContext->frameCounter;
}

kg_bool kg_pop_error(kg_context* pContext, kg_error** pOutError)
{
	if (pContext->errorCount > 0u)
	{
		*pOutError = pContext->pErrorStack + ( --pContext->errorCount );
		return K15_GUI_TRUE;
	}

	return K15_GUI_FALSE;
}

#endif //K15_GUI_IMPLEMENTATION
#endif //_K15_GUILayer_Context_h_
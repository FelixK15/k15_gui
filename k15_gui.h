#ifndef _K15_GUILayer_Context_h_
#define _K15_GUILayer_Context_h_

#ifdef kg_def
# undef kg_def
#endif

#ifdef kg_true
# undef kg_true
#endif

#ifdef kg_false
# undef kg_false
#endif

#ifndef K15_GUI_STATIC
# define kg_def static
#else
# define kg_def extern
#endif //K15_GUI_STATIC

#define kg_true 1 
#define kg_false 0

#ifndef K15_GUI_DEFAULT_BUCKET_COUNT
# define K15_GUI_DEFAULT_BUCKET_COUNT 128u
#endif

typedef unsigned long long 	kg_u64;
typedef unsigned int 		kg_u32;
typedef unsigned short 		kg_u16;
typedef unsigned char		kg_u8;
typedef float 				kg_f32;
typedef double 				kg_f64;

typedef long long 			kg_s64;
typedef int 				kg_s32;
typedef short 				kg_s16;
typedef char 				kg_s8;

typedef char 				kg_utf8;
typedef unsigned int 		kg_crc32;
typedef unsigned int 		kg_color32;
typedef unsigned int 		kg_code_point;
typedef unsigned int 		kg_glyph_id;
typedef unsigned char 		kg_byte;
typedef unsigned char 		kg_bool;

/*********************************************************************************/
typedef enum 
{
	K15_GUI_RESULT_SUCCESS 								= 0,
	K15_GUI_RESULT_OUT_OF_MEMORY 						= 1,
	K15_GUI_RESULT_FONT_DATA_ERROR 						= 2,
	K15_GUI_RESULT_NOT_SUPPORTED 						= 3,
	K15_GUI_RESULT_FILE_NOT_FOUND 						= 4,
	K15_GUI_RESULT_ARRAY_EMPTY							= 5,
	K15_GUI_RESULT_ARRAY_FULL							= 6,
	K15_GUI_RESULT_INVALID_ARGUMENTS 					= 7,
	K15_GUI_RESULT_OUT_OF_BOUNDS 						= 8,
	K15_GUI_RESULT_NAME_ALREADY_IN_USE 					= 9,
	K15_GUI_RESULT_RESOURCE_NOT_FOUND 					= 10,
	K15_GUI_RESULT_IMAGE_DATA_ERROR 					= 11,
	K15_GUI_RESULT_FILE_FORMAT_NOT_SUPPORTED 			= 12,
	K15_GUI_RESULT_TOO_MANY_ICONS 						= 13,
	K15_GUI_RESULT_NO_ICONS 							= 14,
	K15_GUI_RESULT_HASH_CONFLICT 						= 15,
	K15_GUI_RESULT_ELEMENT_NOT_FINISHED 				= 16,
	K15_GUI_RESULT_ELEMENT_NOT_STARTED 					= 17,
	K15_GUI_RESULT_INVALID_CONTEXT_PARAMETER 			= 18,
	K15_GUI_RESULT_INVALID_RENDER_CONTEXT_PARAMETER 	= 19,
	K15_GUI_RESULT_NEED_MORE_MEMORY			 			= 20,
	K15_GUI_RESULT_UNKNOWN_ERROR 
} kg_result;
/*********************************************************************************/
typedef enum
{
	K15_GUI_CONTEXT_INSIDE_FRAME_FLAG			= 0x1,
	K15_GUI_CONTEXT_INSIDE_WINDOW_FLAG			= 0x2,
	K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG			= 0x4
} kg_context_flags;
/*********************************************************************************/
typedef enum
{
	K15_GUI_MATRIX_INVERT_Y_AXIS_FLAG = 0x1
} kg_matrix_flags;
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
	K15_GUI_FLOAT_DATA_TYPE = 0,
	K15_GUI_UINT_DATA_TYPE,
} kg_vertex_attribute_data_type;
/*********************************************************************************/
typedef enum
{
	K15_GUI_INDEX_DATA_TYPE_SHORT,
	K15_GUI_INDEX_DATA_TYPE_INT
} kg_index_data_type;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_MAX_RENDER_BUFFER_COUNT = 4u,
	K15_GUI_WINDOW_STACK_SIZE		= 64u
} kg_array_sizes;
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_1_SFNT = 0x00010000,
	K15_GUI_TRUETYPE_2_SFNT = 0x74727565,
	K15_GUI_OPENTYPE_SFNT 	= ('O' << 0) | ('T' << 8) | ('T' << 16) | ('O' << 24)
} kg_true_type_sfnt;
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_TABLE_CFF,
	K15_GUI_TRUETYPE_TABLE_CFF2,
	K15_GUI_TRUETYPE_TABLE_GLYF,
	K15_GUI_TRUETYPE_TABLE_KERN,
	K15_GUI_TRUETYPE_TABLE_HEAD,
	K15_GUI_TRUETYPE_TABLE_HHEA,
	K15_GUI_TRUETYPE_TABLE_KERX,
	K15_GUI_TRUETYPE_TABLE_LOCA,
	K15_GUI_TRUETYPE_TABLE_MAXP,
	K15_GUI_TRUETYPE_TABLE_HMTX,
	K15_GUI_TRUETYPE_TABLE_VMTX,
	K15_GUI_TRUETYPE_TABLE_CMAP,
	K15_GUI_TRUETYPE_TABLE_SBIX,
	K15_GUI_TRUETYPE_TABLE_NAME,
	K15_GUI_TRUETYPE_TABLE_LTAG,
	K15_GUI_TRUETYPE_TABLE_SVG,
	K15_GUI_TRUETYPE_TABLE_EBDT,
	K15_GUI_TRUETYPE_TABLE_EBLC,
	K15_GUI_TRUETYPE_TABLE_EBSC,
	K15_GUI_TRUETYPE_TABLE_COLR,
	K15_GUI_TRUETYPE_TABLE_CBDT,
	K15_GUI_TRUETYPE_TABLE_CBLC,
	K15_GUI_TRUETYPE_TABLE_GSUB,
	K15_GUI_TRUETYPE_TABLE_MORX,

	K15_GUI_TRUETYPE_TABLE_COUNT
} kg_true_type_table;
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_VERTEX_TYPE_ON_CURVE,
	K15_GUI_TRUETYPE_VERTEX_TYPE_QUADRATIC,
	K15_GUI_TRUETYPE_VERTEX_TYPE_CUBIC
} kg_true_type_vertex_type;
/*********************************************************************************/
typedef enum
{
	K15_GUI_PIXEL_FORMAT_R8 		= 1,
	K15_GUI_PIXEL_FORMAT_R8G8B8A8 	= 4
} kg_pixel_format;
/*********************************************************************************/

static const kg_f32 	K15_GUI_WINDOW_TITLE_HEIGHT_IN_PIXELS 		= 30.f;
static const kg_f32 	K15_GUI_WINDOW_MIN_AREA_HEIGHT_IN_PIXELS 	= 10.f;

/*********************************************************************************/
typedef struct
{
	kg_f32 x;
	kg_f32 y;
} kg_float2;
/*********************************************************************************/
typedef struct
{
	kg_f32 x;
	kg_f32 y;
	kg_f32 z;
	kg_f32 w;
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
	kg_u32 x;
	kg_u32 y;
	kg_u32 z;
	kg_u32 w;
} kg_uint4;
/*********************************************************************************/
typedef struct
{
	kg_s32 x;
	kg_s32 y;
} kg_sint2;
/*********************************************************************************/
typedef struct
{
	kg_float2 p0;
	kg_float2 p1;
} kg_line_float_2d;
/*********************************************************************************/
typedef struct
{
	void* 				pVertexData;
	void* 				pIndexData;
	size_t 				vertexDataSizeInBytes;
	size_t 				indexDataSizeInBytes;

	int					vertexCount;
	int					indexCount;

	kg_index_data_type	indexDataType;
} kg_render_data;
/*********************************************************************************/
typedef struct
{
	size_t 	sizeInBytes;
	void* 	pNext;
	kg_u32	componentId;
} kg_element_component_header;
/*********************************************************************************/
typedef struct
{
#ifdef K15_GUI_STORE_IDENTIFIER_STRING
	const char* pIdentifier;
#endif
	kg_element_component_header* 	pFirstComponent;			
	kg_layout_type					layout;
	kg_crc32 						identifier;
	kg_float2						position;
	kg_float2						size;
} kg_element;
/*********************************************************************************/
typedef struct
{
	void*	pMemory;
	size_t	memorySizeInBytes;
	size_t 	allocPosition;
} kg_linear_allocator;
/*********************************************************************************/
typedef struct 
{
	void*		pElement;
	void* 		pNext;
	kg_crc32 	key;
} kg_hash_map_bucket;
/*********************************************************************************/
typedef struct
{
	kg_linear_allocator*	pAllocator;
	kg_hash_map_bucket*		buckets[K15_GUI_DEFAULT_BUCKET_COUNT];
	size_t					elementSizeInBytes;
} kg_hash_map;
/*********************************************************************************/
typedef struct 
{
	void* 		pNext;
	const char* pDescription;
	kg_result 	result;
} kg_error;
/*********************************************************************************/
typedef struct
{
	kg_linear_allocator errorAllocator;
	kg_error* 			pFirstError;
} kg_error_stack;
/*********************************************************************************/
typedef struct 
{
	kg_float2 position;
	kg_float2 size;
} kg_rect;
/*********************************************************************************/
typedef struct
{
	void*			pNext;
	const kg_utf8* 	pTitle;
	kg_float2 		position;
	kg_float2 		size;
	kg_u32 			zOrder;
	kg_u32 			flags;
} kg_window;
/*********************************************************************************/
typedef struct
{
	union
	{
		struct 
		{
			kg_u16 x;
			kg_u16 y;
			kg_u16 deltaX;
			kg_u16 deltaY;
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
	kg_linear_allocator		allocator;
	kg_input_event* 		pFirstEvent;
	kg_element*				pActiveElement;
	kg_element*				pHotElement;
} kg_input_system;
/*********************************************************************************/
typedef struct 
{
	int left;
	int top;
	int right;
	int bottom;
} kg_viewport;
/*********************************************************************************/

/*********************************************************************************/
typedef struct
{
	const char* 	pString;
	kg_u16 			length;
} kg_true_type_font_name;
/*********************************************************************************/
typedef struct
{
	kg_true_type_font_name fontFamiliyName;
	kg_true_type_font_name fontSubFamilyName;
	kg_true_type_font_name fontName;
} kg_true_type_font_familiy;
/*********************************************************************************/
typedef struct
{
	kg_byte* 	pMemory;
	size_t 		memorySizeInBytes;
} kg_buffer;
/*********************************************************************************/
typedef struct
{
	kg_true_type_font_familiy 	family;
	kg_buffer 					data;
	kg_true_type_sfnt 			sfnt;
	size_t 						offset;
	size_t 						tableOffsets[K15_GUI_TRUETYPE_TABLE_COUNT];
	kg_u16 						tableCount;
	kg_u16 						flags;
	kg_s16 						indexLocaFormat;
} kg_true_type_font;
/*********************************************************************************/
typedef struct
{
	kg_true_type_vertex_type 	type;
	kg_u8					 	flags;
	kg_u16						xCoordinate;
	kg_u16						yCoordinate;
} kg_true_type_vertex;
/*********************************************************************************/
typedef struct
{
	kg_u32 startIndex;
	kg_u32 length;
} kg_true_type_contour;
/*********************************************************************************/
typedef struct
{
	kg_true_type_contour* pContourBuffer;
	kg_true_type_vertex* pVertexBuffer;
	kg_s16 xMin;
	kg_s16 xMax;
	kg_s16 yMin;
	kg_s16 yMax;
	kg_u32 contourCount;
	kg_u32 vertexCount;
	kg_u32 contourCapacity; 
	kg_u32 vertexCapacity;
} kg_true_type_glyf_outline_context;
/*********************************************************************************/
typedef struct
{
	kg_true_type_contour* 	pContours;
	kg_true_type_vertex* 	pVertices;

	kg_u32 contourCount;
	kg_u32 vertexCount;
	kg_s16 xMin;
	kg_s16 xMax;
	kg_s16 yMin;
	kg_s16 yMax;
} kg_glyph_outline;
/*********************************************************************************/
typedef struct
{
	kg_uint4	uvBounds;
	kg_uint2	position;
	kg_uint2	size;
} kg_texture_atlas_slot;
/*********************************************************************************/
typedef struct
{
	void* 					pImageData;
	kg_texture_atlas_slot* 	pSlots;
	kg_uint2 				size;
	kg_uint2				skyLine;
	kg_u32					slotCount;
	kg_pixel_format 		pixelFormat;
} kg_texture_atlas;
/*********************************************************************************/
typedef struct
{
	kg_true_type_contour* 	pContours;
	kg_true_type_vertex* 	pVertices;

	kg_u32 contourCount;
} kg_glyph;
/*********************************************************************************/
typedef struct
{
	const kg_texture_atlas_slot* 	pAtlasSlot;
	kg_code_point 					codePoint;
	kg_u32							lastUsedFrameIndex;
} kg_glyph_cache_entry;
/*********************************************************************************/
typedef struct
{
	kg_glyph_cache_entry* 	pEntries;
	kg_texture_atlas 		atlas;

	kg_buffer				contourBuffer;
	kg_buffer				vertexBuffer;

	kg_u32 					size;
	kg_u32 					capacity;
} kg_glyph_cache;
/*********************************************************************************/
typedef struct
{
	kg_texture_atlas_slot* 	pAtlasSlot;
	kg_crc32				identifier;
#ifdef K15_GUI_STORE_IDENTIFIER_STRING
	const char*				pIdentifier;
#endif
} kg_image_cache_entry;
/*********************************************************************************/
typedef struct
{
	kg_hash_map 		hashMap;
	kg_texture_atlas 	atlas;
} kg_image_cache;
/*********************************************************************************/
typedef struct
{
	kg_linear_allocator* pVertexAllocator;
	kg_linear_allocator* pIndexAllocator;

	kg_linear_allocator vertexAllocators[K15_GUI_MAX_RENDER_BUFFER_COUNT];
	kg_linear_allocator indexAllocators[K15_GUI_MAX_RENDER_BUFFER_COUNT];
	kg_u32 vertexAllocatorCount;
	kg_u32 indexAllocatorCount;

	kg_index_data_type indexDataType;
} kg_render_context;
/*********************************************************************************/
typedef struct 
{
	char					fourCC[4];
	kg_linear_allocator		frameAllocators[2];
	kg_hash_map				elements[2];
	kg_hash_map				windows[2];
	kg_true_type_font		trueTypeFont;
	kg_input_system			inputSystem;
	kg_viewport				viewport;
	kg_error_stack	 		errorStack;
	kg_render_context		renderContext;
	kg_glyph_cache			glyphCache;
	kg_image_cache			imageCache;
	kg_linear_allocator*	pAllocator;
	kg_hash_map*			pWindowHashMap;
	kg_hash_map*			pElementHashMap;
	kg_window*				pFirstWindow;
	size_t					allocatorFrameDataPosition;
	kg_u32 					dpi;
	kg_u32					currentWindowStackIndex;
	kg_u32					windowZIndex;
	kg_u32 					frameCounter;
	kg_u32					flags;
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
	int								size;
	size_t							sizeInBytes;
	size_t							offset;
} kg_vertex_attribute_definition;
/*********************************************************************************/
typedef struct 
{
	size_t 							stride;
	int 							attributeCount;
	kg_vertex_attribute_definition 	attributes[3];
} kg_vertex_definition;
/*********************************************************************************/
typedef struct
{
	kg_buffer 	vertexBuffer[K15_GUI_MAX_RENDER_BUFFER_COUNT];
	kg_buffer 	indexBuffer[K15_GUI_MAX_RENDER_BUFFER_COUNT];
	kg_u32 		vertexBufferCount;
	kg_u32		indexBufferCount;

	kg_index_data_type indexDataType;
} kg_render_context_parameter;
/*********************************************************************************/
typedef struct
{
	kg_buffer 	scratchBuffer;
	kg_buffer 	fontData;
	const char* pFontName;
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
kg_def kg_render_context_parameter	kg_create_render_context_parameter();
kg_def kg_result 					kg_create_context(kg_context_handle* pOutHandle);
kg_def kg_result 					kg_create_context_with_custom_parameter(kg_context_handle* pOutHandle, const kg_context_parameter* pParameter, const kg_render_context_parameter* pRenderParameter, const char** pOutError);
kg_def kg_result 					kg_set_viewport(kg_context_handle contextHandle, const kg_viewport* pViewport);
kg_def kg_result					kg_get_viewport(kg_context_handle contextHandle, kg_viewport* pOutViewport);
kg_def kg_result 					kg_set_dpi(kg_context_handle contextHandle, short dpi);
kg_def kg_result 					kg_get_dpi(kg_context_handle contextHandle, unsigned short* pOutDpi);

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
kg_def const char*					kg_result_to_string(kg_result p_Result);
kg_def void 						kg_calculate_row_major_projection_matrix(kg_f32* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def void 						kg_calculate_column_major_projection_matrix(kg_f32* pProjectionMatrix, int screenWidth, int screenHeight, unsigned int flags);
kg_def kg_bool 						kg_pop_error(kg_context_handle contextHandle, kg_error** pOutError);
kg_def kg_buffer					kg_create_buffer(void* pMemory, size_t memorySizeInBytes);

//****************RENDER*****************//
kg_def const kg_vertex_definition*	kg_get_vertex_definition();
kg_def kg_result					kg_get_render_data(kg_context_handle contextHandle, kg_render_data* pOutRenderData);


//*****************DEBUG*****************//

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

#ifndef K15_GUI_FORMAT_STRING
# include "string.h"
# define kg_format_string(buffer, bufferSize, format, list) vsnprintf_s(buffer, bufferSize, bufferSize, format, list);
#else
# define kg_vsnprintf_s(buffer, bufferSize, format, list) K15_GUI_FORMAT_STRING(buffer, bufferSize, format, list)
#endif //K15_GUI_FORMAT_STRING

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

#ifndef K15_GUI_SQRT
# include "math.h"
# define kg_sqrtf(a) sqrtf(a)
#else
# define kg_sqrtf(a) K15_GUI_SQRTF(a)
#endif //K15_GUI_SQRT

#ifndef K15_GUI_FABS
# include "math.h"
# define kg_fabs(a) fabsf(a)
#else
# define kg_fabs(a) K15_GUI_FABS(a)
#endif //K15_GUI_FABS

kg_internal const kg_u32 kg_ptr_size_in_bytes = sizeof(void*);

#define kg_size_kilo_bytes(n) ((n)*1024)
#define kg_size_mega_bytes(n) ((n)*1024*1024)

#define kg_nullptr (void*)(0)

#define kg_set_str(err, str) if (err != kg_nullptr) {*err = str;}

typedef kg_u32 kg_code_point;

/*********************************************************************************/
typedef enum
{
	K15_GUI_COLOR_WHITE 		= 0xFFFFFFFF,
	K15_GUI_COLOR_BLACK 		= 0x000000FF,
	K15_GUI_COLOR_LIGHT_RED		= 0xFF0000FF,
	K15_GUI_COLOR_LIGHT_GREEN	= 0x00FF00FF,
	K15_GUI_COLOR_LIGHT_BLUE	= 0xFF00FFFF,
	K15_GUI_COLOR_LIGHT_GREY 	= 0xDDDDDDFF,
	K15_GUI_COLOR_DARK_RED		= 0x400000FF,
	K15_GUI_COLOR_DARK_GREEN	= 0x004400FF,
	K15_GUI_COLOR_DARK_BLUE		= 0x000044FF,
	K15_GUI_COLOR_DARK_GREY		= 0x444444FF
} kg_colors;
/*********************************************************************************/
typedef enum
{
	K15_GUI_WINDOW_FLAG_IS_OPEN 				= 0x001,
	K15_GUI_WINDOW_FLAG_IS_MAXIMIZED 			= 0x002,
	K15_GUI_WINDOW_FLAG_IS_MINIMIZED			= 0x004,
	K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED = 0x008,
	K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED = 0x010,
	K15_GUI_WINDOW_FLAG_CLOSE_BUTTON_CLICKED	= 0x020
} kg_window_flag;
/*********************************************************************************/
typedef struct
{
	kg_float4	position;  	
	kg_float4 	color;		
	kg_float2 	texcoord;	
	kg_float2	padding[3];		
} kg_render_vertex_data; 
/*********************************************************************************/
typedef struct 
{
	kg_render_vertex_data* 	pVertexData;
	kg_u32					vertexCount;
	kg_bool 				dirty;
} kg_render_vertices;
/*********************************************************************************/
enum
{
	VertexStride 		= sizeof(kg_render_vertex_data),
	IndexSize 			= sizeof(kg_u16),
	MinContextDataSize 	= kg_size_kilo_bytes(512)
};
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_MAGIC_NUMBER 					= 0x5F0F3CF5,
	K15_GUI_TRUETYPE_OFFSET_HEAD_MAGIC_NUMBER 		= 12u, 	// Relative to 'head' table
	K15_GUI_TRUETYPE_OFFSET_HEAD_INDEX_LOCA_FORMAT 	= 50u, 	// Relative to 'head' table
	K15_GUI_TRUETYPE_OFFSET_HEAD_FLAGS 				= 16u, 	// Relative to 'head' table
	K15_GUI_TRUETYPE_OFFSET_CHECKSUM_ADJUSTMENT		= 8u,	// Relative to 'head' table
	K15_GUI_TRUETYPE_TABLE_DIRECTORY				= 12u  	// Absolute offset
} kg_true_type_offsets;
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_LANGUAGE_ID_ENGLISH = 0u
} kg_true_type_language_id; 
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_NAME_ID_FONT_FAMILY 		= 1u << 0u,
	K15_GUI_TRUETYPE_NAME_ID_FONT_SUB_FAMILY 	= 1u << 1u,
	K15_GUI_TRUETYPE_NAME_ID_FONT 				= 1u << 2u
} kg_true_type_name_id;
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_PLATFORM_ID_UNICODE	= 0u,
	K15_GUI_TRUETYPE_PLATFORM_ID_MICROSOFT	= 3u
} kg_true_type_platform_id;
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUETYPE_ENCODING_ID_SYMBOL 		= 0u,
	K15_GUI_TRUETYPE_ENCODING_ID_UNICODE_BMP 	= 1u,
	K15_GUI_TRUETYPE_ENCODING_ID_UNICODE_FULL 	= 10u
} kg_true_type_encoding_id;
/*********************************************************************************/
typedef enum 
{
	K15_GUI_TRUE_TYPE_GLYPH_FLAG_ON_CURVE		= 0x01,
	K15_GUI_TRUE_TYPE_GLYPH_FLAG_X_SHORT_VECTOR	= 0x02,
	K15_GUI_TRUE_TYPE_GLYPH_FLAG_Y_SHORT_VECTOR	= 0x04,
	K15_GUI_TRUE_TYPE_GLYPH_FLAG_REPEAT			= 0x08,
	K15_GUI_TRUE_TYPE_GLYPH_FLAG_THIS_X_IS_SAME	= 0x10,
	K15_GUI_TRUE_TYPE_GLYPH_FLAG_THIS_Y_IS_SAME	= 0x20
} kg_true_type_glyph_flag;
/*********************************************************************************/
typedef enum
{
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_ARG1_AND_2_ARE_WORDS		= 1 << 0u,
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_ARGS_ARE_XY_VALUES		= 1 << 1u,
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_ROUND_XY_TO_GRID			= 1 << 2u,
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_WE_HAVE_A_SCALE			= 1 << 3u,
	//THIS_FLAG_IS_DEPRECATED						= 1 << 4u
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_MORE_COMPONENTS			= 1 << 5u,
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_WE_HAVE_AN_X_AND_Y_SCALE	= 1 << 6u,
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_WE_HAVE_A_TWO_BY_TWO		= 1 << 7u,
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_WE_HAVE_INSTRUCTIONS		= 1 << 8u, //FK: Do we really care?
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_USE_MY_METRICS			= 1 << 9u,
	K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_OVERLAP_COMPOUNDS			= 1 << 10u
} kg_true_type_compound_glyph_flag;
/*********************************************************************************/


#define kg_peek_data(t, b, o) kg_peek_data_from_buffer(t, sizeof(*t), b, o)
#define kg_read_data(t, b, o) kg_read_data_from_buffer(t, sizeof(*t), b, o);


/*********************************************************************************/
kg_internal kg_float2 kg_float2_init(kg_f32 x, kg_f32 y)
{
	kg_float2 value = {x, y};
	return value;
}
/*********************************************************************************/
kg_internal kg_float2 kg_float2_zero()
{
	static const kg_float2 zero = {0.f, 0.f};
	return zero;
}
/*********************************************************************************/
kg_internal kg_f32 kg_float2_dot(kg_float2 a, kg_float2 b)
{
	return a.x * b.x + a.y * b.y;
}
/*********************************************************************************/
kg_internal kg_bool kg_float2_gt(kg_float2 a, kg_float2 b)
{
	return ( a.x > b.x && a.y > b.y );
}
/*********************************************************************************/
kg_internal kg_float2 kg_float2_clamp(kg_float2 value, kg_float2 min, kg_float2 max)
{
	kg_float2 clamped = kg_float2_zero();
	clamped.x = kg_clamp(value.x, min.x, max.x);
	clamped.y = kg_clamp(value.y, min.y, max.y);

	return clamped;
}
/*********************************************************************************/
kg_internal kg_float2 kg_float2_max(kg_float2 a, kg_float2 b)
{
	kg_float2 maxValue = kg_float2_zero();
	maxValue.x = kg_max(a.x, b.x);
	maxValue.y = kg_max(a.y, b.y);

	return maxValue;
}
/*********************************************************************************/
kg_internal kg_float2 kg_float2_add(kg_float2 a, kg_float2 b)
{
	a.x += b.x;
	a.y += b.y;

	return a;
}
/*********************************************************************************/
kg_internal kg_float2 kg_float2_sub(kg_float2 a, kg_float2 b)
{
	a.x = a.x - b.x;
	a.y = a.y - b.y;

	return a;
}
/*********************************************************************************/
kg_internal kg_float2 kg_float2_scale(kg_float2 value, kg_f32 scale)
{
	value.x *= scale;
	value.y *= scale;

	return value;
}
/*********************************************************************************/
kg_internal kg_float2 kg_float2_normalize(kg_float2 value)
{
	kg_f32 length = kg_sqrtf(value.x * value.x + value.y * value.y);
	length = length == 0.0f ? 1.0f : length;

	value.x /= length;
	value.y /= length;

	return value;
}
/*********************************************************************************/
kg_internal kg_float4 kg_float4_zero()
{
	static const kg_float4 zero = {0.f, 0.f, 0.f, 0.f};
	return zero;
}
/*********************************************************************************/
kg_internal kg_uint2 kg_uint2_zero()
{
	static const kg_uint2 zero = {0u, 0u};
	return zero;
}
/*********************************************************************************/
kg_internal kg_sint2 kg_sint2_zero()
{
	static const kg_sint2 zero = {0, 0};
	return zero;
}
/*********************************************************************************/
kg_internal kg_float2 kg_create_float2(kg_f32 x, kg_f32 y)
{
	kg_float2 f2 = {x, y};
	return f2;
}
/*********************************************************************************/
kg_internal kg_float4 kg_create_float4(kg_f32 x, kg_f32 y, kg_f32 z, kg_f32 w)
{
	kg_float4 f4 = {x, y, z, w};
	return f4;
}
/*********************************************************************************/
kg_internal kg_uint2 kg_create_uint2(kg_u32 x, kg_u32 y)
{
	kg_uint2 u2 = {x, y};
	return u2;
}
/*********************************************************************************/
kg_internal kg_sint2 kg_create_sint2(kg_s32 x, kg_s32 y)
{
	kg_sint2 s2 = {x, y};
	return s2;
}
/*********************************************************************************/
kg_internal kg_float2 kg_uint2_to_float2_cast(kg_uint2 u2)
{
	kg_float2 f2 = { (kg_f32)u2.x, (kg_f32)u2.y };
	return f2;
}
/*********************************************************************************/
kg_internal kg_float4 kg_uint4_to_float4_cast(kg_uint4 u4)
{
	kg_float4 f4 = { (kg_f32)u4.x, (kg_f32)u4.y, (kg_f32)u4.z, (kg_f32)u4.w };
	return f4;
}
/*********************************************************************************/
kg_internal kg_line_float_2d kg_init_line_float_2d(kg_f32 xP0, kg_f32 yP0, kg_f32 xP1, kg_f32 yP1)
{
	kg_line_float_2d line;
	line.p0.x = xP0;
	line.p0.y = yP0;
	line.p1.x = xP1;
	line.p1.y = yP1;

	return line;
}
/*********************************************************************************/
kg_internal kg_bool kg_is_invalid_linear_allocator(const kg_linear_allocator* pAllocator)
{
	if (pAllocator == kg_nullptr)
	{
		return kg_true;
	}

	if (pAllocator->pMemory == kg_nullptr)
	{
		return kg_true;
	}

	if (pAllocator->memorySizeInBytes == 0u)
	{
		return kg_true;
	}

	return kg_false;
}
/*********************************************************************************/
kg_internal kg_result kg_create_linear_allocator(kg_linear_allocator* pOutAllocator, void* pMemory, size_t memorySizeInBytes)
{
	kg_assert(pOutAllocator != kg_nullptr);
	kg_assert(pMemory != kg_nullptr);
	kg_assert(memorySizeInBytes > 0u);

	kg_linear_allocator linearAllocator;
	linearAllocator.allocPosition 		= 0u;
	linearAllocator.memorySizeInBytes 	= memorySizeInBytes;
	linearAllocator.pMemory				= pMemory;

	*pOutAllocator = linearAllocator;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result kg_reset_linear_allocator(kg_linear_allocator* pAllocator, size_t position)
{
	kg_assert(pAllocator != kg_nullptr);

	position = kg_clamp(position, 0u, pAllocator->allocPosition);
	pAllocator->allocPosition = position;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal size_t kg_get_linear_allocator_position(const kg_linear_allocator* pAllocator)
{
	return pAllocator->allocPosition;
}
/*********************************************************************************/
kg_internal kg_result kg_allocate_from_linear_allocator(void** pOutPointer, kg_linear_allocator* pAllocator, size_t sizeInBytes)
{
	kg_assert(pOutPointer != kg_nullptr);
	kg_assert(kg_is_invalid_linear_allocator(pAllocator) == kg_false);
	kg_assert(sizeInBytes > 0u);

	if (pAllocator->allocPosition + sizeInBytes > pAllocator->memorySizeInBytes)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	*pOutPointer = ((kg_byte*)pAllocator->pMemory + pAllocator->allocPosition);
	pAllocator->allocPosition += sizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result kg_peek_data_from_buffer(void* pTarget, size_t targetSizeInBytes, const kg_buffer* pBuffer, size_t offsetInBytes)
{
	kg_assert(pTarget != kg_nullptr);
	kg_assert(pBuffer != kg_nullptr);
	kg_assert(offsetInBytes + targetSizeInBytes <= pBuffer->memorySizeInBytes);

	const kg_byte* pBufferMemory = (const kg_byte*)pBuffer->pMemory;
	kg_byte* pTargetByteBuffer = (kg_byte*)pTarget;
	for (size_t byteIndex = 0u; byteIndex < targetSizeInBytes; ++byteIndex)
	{
		pTargetByteBuffer[byteIndex] = pBufferMemory[offsetInBytes + targetSizeInBytes - byteIndex - 1u]; 
	}

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result kg_read_data_from_buffer(void* pTarget, size_t targetSizeInBytes, const kg_buffer* pBuffer, size_t* pOffsetInBytes)
{
	kg_result result = kg_peek_data_from_buffer(pTarget, targetSizeInBytes, pBuffer, *pOffsetInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	*pOffsetInBytes += targetSizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal size_t kg_count_string_length(const char* pString)
{
	const char* pStr = pString;
	while(*pStr++ != 0u);
	return (size_t)(pStr - pString);
}
/*********************************************************************************/
kg_internal size_t kg_copy_string(char* pStringA, const char* pStringB, size_t length)
{
	size_t counter = 0u;
	while (counter < length)
	{
		*pStringA++ = *pStringB++;
		++counter;

		if (*pStringA == 0u || *pStringB == 0u)
		{
			break;
		}
	}

	return counter;
}
/*********************************************************************************/
kg_internal kg_bool kg_string_equal(const char* pStringA, const char* pStringB, size_t length)
{
	size_t counter = 0u;

	if (*pStringA  == 0u || *pStringB == 0u)
	{
		return kg_false;
	}

	while (*pStringA && *pStringB)
	{
		if (*pStringA++ != *pStringB++)
		{
			return kg_false;
		}

		if (length == counter++)
		{
			break;
		}
	}

	return kg_true;
}
/*********************************************************************************/
kg_internal kg_result kg_create_hash_map(kg_hash_map* pOutHashMap, kg_linear_allocator* pAllocator, size_t elementSizeInBytes)
{
	pOutHashMap->pAllocator 		= pAllocator;
	pOutHashMap->elementSizeInBytes = elementSizeInBytes;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal void kg_reset_hash_map(kg_hash_map* pHashMap)
{
	for (kg_u32 bucketIndex = 0u; bucketIndex < K15_GUI_DEFAULT_BUCKET_COUNT; ++bucketIndex)
	{
		pHashMap->buckets[bucketIndex] = kg_nullptr;
	}
}
/*********************************************************************************/
kg_internal kg_hash_map_bucket* kg_allocate_hash_map_bucket(kg_hash_map* pHashMap, kg_u32 bucketIndex, kg_crc32 identifier)
{
	if (pHashMap == kg_nullptr)
	{
		return kg_nullptr;
	}

	kg_hash_map_bucket* pBucket = kg_nullptr;
	kg_result result = kg_allocate_from_linear_allocator(&pBucket, pHashMap->pAllocator, pHashMap->elementSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return kg_nullptr;
	}

	result = kg_allocate_from_linear_allocator(&pBucket->pElement, pHashMap->pAllocator, pHashMap->elementSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return kg_nullptr;
	}

	pBucket->key = identifier;	

	if (pHashMap->buckets[bucketIndex] != kg_nullptr)
	{
		pBucket->pNext = pHashMap->buckets[bucketIndex];
	}

	pHashMap->buckets[bucketIndex] = pBucket;

	return pBucket;
}
/*********************************************************************************/
kg_internal const kg_hash_map_bucket* kg_find_hash_bucket(const kg_hash_map_bucket* pBucket, kg_crc32 identifier)
{
	if (pBucket == kg_nullptr)
	{
		return kg_nullptr;
	}

	if (pBucket->key == identifier)
	{
		return pBucket;
	}

	return kg_find_hash_bucket(pBucket->pNext, identifier);
}
/*********************************************************************************/
kg_internal void* kg_find_hash_element(const kg_hash_map* pHashMap, kg_crc32 identifier)
{
	if (pHashMap == kg_nullptr)
	{
		return kg_nullptr;
	}

	const kg_u32 hashIndex 				= identifier % K15_GUI_DEFAULT_BUCKET_COUNT;
	const kg_hash_map_bucket* pBucket 	= pHashMap->buckets[hashIndex];

	if (pBucket== kg_nullptr)
	{
		return kg_nullptr;
	}

	pBucket = kg_find_hash_bucket(pBucket, identifier);

	if (pBucket == kg_nullptr)
	{
		return kg_nullptr;
	}

	return pBucket->pElement;
}
/*********************************************************************************/
kg_internal void* kg_insert_hash_element(kg_hash_map* pHashMap, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	if (pHashMap == kg_nullptr)
	{
		return kg_nullptr;
	}

	const kg_u32 hashIndex 				= identifier % K15_GUI_DEFAULT_BUCKET_COUNT;
	const kg_hash_map_bucket* pBucket 	= pHashMap->buckets[hashIndex];

	if (pBucket != kg_nullptr)
	{
		pBucket = kg_find_hash_bucket(pBucket, identifier);

		if (pBucket == kg_nullptr)
		{
			return kg_nullptr;
		}
		else
		{
			*pOutIsNew = kg_false;
			return pBucket->pElement;
		}
	}

	pBucket = kg_allocate_hash_map_bucket(pHashMap, hashIndex, identifier);
	
	if (pBucket == kg_nullptr)
	{
		return kg_nullptr;
	}

	*pOutIsNew = kg_true;

	return pBucket->pElement;
}
/*********************************************************************************/
kg_internal kg_result kg_create_texture_atlas(kg_texture_atlas* pOutTextureAtlas, kg_linear_allocator* pAllocator, kg_u32 width, kg_u32 height, kg_pixel_format pixelFormat)
{
	const size_t imageDataSizeInBytes 	= width * height * pixelFormat;
	const size_t slotSizeInBytes 		= ((width * height) / 4u) * sizeof(kg_texture_atlas_slot);

	void* pImageData = kg_nullptr;
	kg_result result = kg_allocate_from_linear_allocator(&pImageData, pAllocator, imageDataSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_texture_atlas_slot* pSlots = kg_nullptr;
	result = kg_allocate_from_linear_allocator(&pSlots, pAllocator, slotSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	pOutTextureAtlas->pImageData 	= pImageData;
	pOutTextureAtlas->size.x 		= width;
	pOutTextureAtlas->size.y 		= height;
	pOutTextureAtlas->pixelFormat 	= pixelFormat;
	pOutTextureAtlas->pSlots		= pSlots;
	pOutTextureAtlas->slotCount	 	= 0u;
	pOutTextureAtlas->skyLine 		= kg_uint2_zero();

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result kg_clear_texture_atlas(kg_texture_atlas* pTextureAtlas)
{
	pTextureAtlas->slotCount 	= 0u;
	pTextureAtlas->skyLine 		= kg_uint2_zero();
}
/*********************************************************************************/
kg_internal kg_result kg_allocate_texture_atlas_slot(kg_texture_atlas_slot** pOutSlot, kg_texture_atlas* pTextureAtlas, kg_u32 width, kg_u32 height)
{
	kg_assert(height >= 4u);
	kg_assert(width >= 4u);

	if (pTextureAtlas->skyLine.x + width > pTextureAtlas->size.x)
	{
		pTextureAtlas->skyLine.y = kg_max(pTextureAtlas->skyLine.y, height);
	}
	else if (pTextureAtlas->skyLine.y + height < pTextureAtlas->size.y)
	{
		pTextureAtlas->skyLine.x = width;
		pTextureAtlas->skyLine.y += height;
	}
	else
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	const kg_u32 slotIndex = pTextureAtlas->slotCount++;
	kg_texture_atlas_slot* pSlot = pTextureAtlas->pSlots + slotIndex;
	pSlot->size.x 		= width;
	pSlot->size.y 		= height;
	pSlot->position 	= kg_create_uint2(pTextureAtlas->skyLine.x - width, pTextureAtlas->skyLine.y);
	pSlot->uvBounds.x 	= pTextureAtlas->skyLine.x / pTextureAtlas->size.x; 
	pSlot->uvBounds.y 	= pTextureAtlas->skyLine.y / pTextureAtlas->size.y; 
	pSlot->uvBounds.z 	= (pTextureAtlas->skyLine.x + width) / pTextureAtlas->size.x; 
	pSlot->uvBounds.w 	= (pTextureAtlas->skyLine.y + height) / pTextureAtlas->size.y; 

	*pOutSlot = pSlot;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_u8* kg_get_texture_atlas_slot_pixmap(const kg_texture_atlas* pTextureAtlas, const kg_texture_atlas_slot* pTextureAtlasSlot)
{
	if (pTextureAtlas == kg_nullptr)
	{
		return kg_nullptr;
	}

	if (pTextureAtlasSlot == kg_nullptr)
	{
		return kg_nullptr;
	}

	return (kg_u8*)pTextureAtlas->pImageData + (pTextureAtlasSlot->position.x + (pTextureAtlasSlot->position.y * pTextureAtlas->size.x) * (kg_u8)pTextureAtlas->pixelFormat);
}
/*********************************************************************************/
kg_internal kg_u32 kg_calculate_true_type_table_checksum(const kg_true_type_font* pTrueTypeFont, kg_u32 tableLength, kg_u32 tableOffset)
{
	if (tableOffset + tableLength > pTrueTypeFont->data.memorySizeInBytes)
	{
		return 0u;
	}

	//https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6.html#Overview
	kg_u32 sum = 0;
	kg_s32 count = (kg_s32)((tableLength + 3) & ~3) / 4;
	while ( count-- > 0 && ( ( tableOffset + 4u ) < pTrueTypeFont->data.memorySizeInBytes ) )
	{
		kg_u32 part = 0u;
		kg_peek_data(&part, &pTrueTypeFont->data, tableOffset);
		
		sum += part;
		tableOffset += 4u;
	}

	return sum;
}
/*********************************************************************************/
kg_internal kg_u32 kg_calculate_true_type_checksum(const kg_true_type_font* pTrueTypeFont)
{
	kg_u32 sum = 0;
	kg_s32 count = (((kg_s32)pTrueTypeFont->data.memorySizeInBytes + 3) & ~3) / 4;
	kg_u32 offset = 0u;
	while ( count-- > 0 )
	{
		kg_u32 part = 0u;

		if (offset != (pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] + K15_GUI_TRUETYPE_OFFSET_CHECKSUM_ADJUSTMENT))
		{
			kg_peek_data(&part, &pTrueTypeFont->data, offset);
		}

		sum += part;
		offset += 4u;
	}

	return 0xB1B0AFBA - sum;
}
/*********************************************************************************/
kg_internal size_t kg_query_true_type_table_offset(kg_true_type_font* pTrueTypeFont, kg_u16 tableCount, const char* pTableIdentifier)
{
	char tableTag[4u];

	size_t offset = pTrueTypeFont->offset + K15_GUI_TRUETYPE_TABLE_DIRECTORY;

	for (kg_u16 tableIndex = 0u; tableIndex < tableCount; ++tableIndex)
	{
		kg_read_data(&tableTag[0], &pTrueTypeFont->data, &offset);
		kg_read_data(&tableTag[1], &pTrueTypeFont->data, &offset);
		kg_read_data(&tableTag[2], &pTrueTypeFont->data, &offset);
		kg_read_data(&tableTag[3], &pTrueTypeFont->data, &offset);

		if (kg_string_equal(tableTag, pTableIdentifier, 4u))
		{
			kg_u32 tableChecksum 	= 0u;
			kg_u32 tableOffset 		= 0u;
			kg_u32 tableLength 		= 0u;

			kg_read_data(&tableChecksum, &pTrueTypeFont->data, &offset);
			kg_read_data(&tableOffset, &pTrueTypeFont->data, &offset);
			kg_read_data(&tableLength, &pTrueTypeFont->data, &offset);

			if (kg_string_equal(tableTag, "head", 4u) == kg_false)
			{
				const kg_u32 calculatedTableChecksum = kg_calculate_true_type_table_checksum(pTrueTypeFont, tableLength, tableOffset);
				if (tableChecksum != calculatedTableChecksum)
				{
					return 0u;
				}
			}

			return tableOffset;
		}

		offset += 12u;
	}

	return 0u;
}
/*********************************************************************************/
kg_internal void kg_parse_true_type_table_offsets(kg_true_type_font* pTrueTypeFont)
{
	kg_u16 tableCount = 0u;
	kg_peek_data(&tableCount, &pTrueTypeFont->data, pTrueTypeFont->offset + 4u);

	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CFF ] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "cff ");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CFF2] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "cff2");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GLYF] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "glyf");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "head");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HHEA] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "hhea");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_KERN] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "kern");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_KERX] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "kerx");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_LOCA] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "loca");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_MAXP] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "maxp");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HMTX] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "htmx");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_VMTX] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "vmtx");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CMAP] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "cmap");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_SBIX] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "sbix");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_NAME] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "name");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_LTAG] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "ltag");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_SVG ] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "SVG ");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_EBDT] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "EBDT");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_EBLC] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "EBLC");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_EBSC] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "EBSC");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_COLR] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "COLR");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CBDT] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "CBDT");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CBLC] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "CBLC");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GSUB] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "GSUB");
	pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_MORX] = kg_query_true_type_table_offset(pTrueTypeFont, tableCount, "morx");
}
/*********************************************************************************/
kg_internal kg_result kg_verify_true_type_data(const kg_true_type_font* pTrueTypeFont)
{
	const kg_u32 calculatedTrueTypeChecksum = kg_calculate_true_type_checksum(pTrueTypeFont);
	kg_u32 trueTypeChecksum = 0u;
	kg_peek_data(&trueTypeChecksum, &pTrueTypeFont->data, pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] + K15_GUI_TRUETYPE_OFFSET_CHECKSUM_ADJUSTMENT);

	if (trueTypeChecksum != calculatedTrueTypeChecksum)
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;
	}
	
	if (pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] == 0u	||
		pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CMAP] == 0u)
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;	
	}

	if (pTrueTypeFont->sfnt == K15_GUI_OPENTYPE_SFNT)
	{
		if (pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CFF] == 0u)
		{
			return K15_GUI_RESULT_FONT_DATA_ERROR;	
		}
	}
	else if (pTrueTypeFont->sfnt == K15_GUI_TRUETYPE_1_SFNT || pTrueTypeFont->sfnt == K15_GUI_TRUETYPE_2_SFNT)
	{
		if (pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GLYF] == 0u)
		{
			return K15_GUI_RESULT_FONT_DATA_ERROR;
		}
	}	

	const kg_u32 offset = pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] + K15_GUI_TRUETYPE_OFFSET_HEAD_MAGIC_NUMBER;
	kg_u32 magicNumber 	= 0u;
	kg_result result 	= kg_peek_data(&magicNumber, &pTrueTypeFont->data, offset);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;
	}

	if (magicNumber != K15_GUI_TRUETYPE_MAGIC_NUMBER)
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;
	}

	//IndexLocaFormat can only have 2 valid values
	if (pTrueTypeFont->indexLocaFormat != 0u && pTrueTypeFont->indexLocaFormat != 1u)
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;
	}

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal void kg_read_true_type_name_utf8( kg_true_type_font_name* pOutName, const kg_true_type_font* pTrueTypeFont, kg_u16 length, kg_u32 offset)
{
	pOutName->pString = (const kg_utf8*)( pTrueTypeFont->data.pMemory + offset );
	pOutName->length  = length;
}
/*********************************************************************************/
kg_internal kg_result kg_read_true_type_name( kg_true_type_font_name* pOutName, const kg_true_type_font* pTrueTypeFont, kg_u16 length, kg_u32 offset, kg_u16 platformId, kg_u16 platformSpecificId)
{
	if( platformId == 0u || ( platformId == 3u && platformSpecificId == 1u ) || ( platformId == 3u && platformSpecificId == 10u ) )
	{
		return K15_GUI_RESULT_NOT_SUPPORTED;
		//kg_read_true_type_name_utf16(pOutName, pTrueTypeFont, length, offset);
	}
	else if ( platformId == 1u )
	{
		kg_read_true_type_name_utf8(pOutName, pTrueTypeFont, length, offset);
		return K15_GUI_RESULT_SUCCESS;
	}

	return K15_GUI_RESULT_NOT_SUPPORTED;
}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_font_names(kg_true_type_font* pTrueTypeFont)
{
	size_t offset = pTrueTypeFont->tableOffsets[ K15_GUI_TRUETYPE_TABLE_NAME ];
	offset += 2u; //FK: skip version

	kg_u16 nameRecordCount 	= 0u;
	kg_u16 stringOffset 	= 0u;

	kg_result result = K15_GUI_RESULT_SUCCESS; 
	result |= kg_read_data(&nameRecordCount, &pTrueTypeFont->data, &offset);
	result |= kg_read_data(&stringOffset, &pTrueTypeFont->data, &offset);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	for( kg_u16 nameRecordIndex = 0u; nameRecordIndex < nameRecordCount; ++nameRecordIndex )
	{
		//FK: Skip platformId and platformSpecificId for now...
		kg_u32 nameRecordOffset = offset;

		kg_u16 platformId 			= 0u;
		kg_u16 platformSpecificId 	= 0u;
		kg_u16 languageId 			= 0u;

		result |= kg_read_data(&platformId, &pTrueTypeFont->data, &nameRecordOffset);
		result |= kg_read_data(&platformSpecificId, &pTrueTypeFont->data, &nameRecordOffset);
		result |= kg_read_data(&languageId, &pTrueTypeFont->data, &nameRecordOffset);

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			return result;
		}

		//FK: we're only interested in english names...I guess
		if( languageId == K15_GUI_TRUETYPE_LANGUAGE_ID_ENGLISH || ( pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_LTAG] > 0u && languageId == 0xFFFF ) )
		{
			kg_u16 nameId 			= 0u;
			kg_u16 lengthInBytes 	= 0u;
			kg_u16 localOffset		= 0u;

			result |= kg_read_data(&nameId, &pTrueTypeFont->data, &nameRecordOffset);
			result |= kg_read_data(&lengthInBytes, &pTrueTypeFont->data, &nameRecordOffset);
			result |= kg_read_data(&localOffset, &pTrueTypeFont->data, &nameRecordOffset);

			if (result != K15_GUI_RESULT_SUCCESS)
			{
				return result;
			}

			if (lengthInBytes > 0u)
			{
				if( nameId == K15_GUI_TRUETYPE_NAME_ID_FONT_FAMILY ||
					nameId == K15_GUI_TRUETYPE_NAME_ID_FONT_SUB_FAMILY ||
					nameId == K15_GUI_TRUETYPE_NAME_ID_FONT_FAMILY )
				{
					const size_t offsetToStringData = pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_NAME] + (size_t)stringOffset + (size_t)localOffset;
					if( nameId == K15_GUI_TRUETYPE_NAME_ID_FONT_FAMILY )
					{
						kg_read_true_type_name( &pTrueTypeFont->family.fontFamiliyName, pTrueTypeFont, lengthInBytes, offsetToStringData, platformId, platformSpecificId );
					}
					else if( nameId == K15_GUI_TRUETYPE_NAME_ID_FONT_SUB_FAMILY )
					{
						kg_read_true_type_name( &pTrueTypeFont->family.fontSubFamilyName, pTrueTypeFont, lengthInBytes, offsetToStringData, platformId, platformSpecificId );
					}
					else if( nameId == K15_GUI_TRUETYPE_NAME_ID_FONT )
					{
						kg_read_true_type_name( &pTrueTypeFont->family.fontFamiliyName, pTrueTypeFont, lengthInBytes, offsetToStringData, platformId, platformSpecificId );
					}
				}
			}
		}
		offset += 12u; //FK: Skip to next name record
	}

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal void kg_parse_true_type_index_loca_format(kg_true_type_font* pTrueTypeFont)
{
	if (pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] == 0u)
	{
		return;
	}

	size_t offset = 0u;

	offset = pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] + K15_GUI_TRUETYPE_OFFSET_HEAD_INDEX_LOCA_FORMAT;
	kg_peek_data(&pTrueTypeFont->indexLocaFormat, &pTrueTypeFont->data, offset);

	offset = pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_HEAD] + K15_GUI_TRUETYPE_OFFSET_HEAD_FLAGS;
	kg_peek_data(&pTrueTypeFont->flags, &pTrueTypeFont->data, offset);
}
/*********************************************************************************/
kg_internal kg_bool kg_true_type_check_font_name(const kg_true_type_font* pTrueTypeFont, const char* pFontName)
{
	if (kg_string_equal(pTrueTypeFont->family.fontName.pString, pFontName, pTrueTypeFont->family.fontName.length))
	{
		return kg_true;
	}

	//FK: create temporary font names for further checks
	static const char separators[] = {
		'-', ' ', '_'
	};

	enum
	{
		maxStringLength = 256u
	};
	char temporaryFontName[ maxStringLength ];

	for( kg_u32 separatorIndex = 0u; separatorIndex < 3u; ++separatorIndex )
	{
		size_t stringLength = kg_copy_string(temporaryFontName, pTrueTypeFont->family.fontFamiliyName.pString, maxStringLength);
		temporaryFontName[ stringLength ] = separators[separatorIndex];

		stringLength += kg_copy_string( temporaryFontName + stringLength + 1u, pTrueTypeFont->family.fontSubFamilyName.pString, maxStringLength - ( stringLength + 1u ));     

		if (kg_string_equal(pFontName, temporaryFontName, stringLength))
		{
			return kg_true;
		}
	}

	return kg_false;
}
/*********************************************************************************/
kg_internal kg_result kg_init_true_type_font_from_offset(kg_true_type_font* pOutTrueTypeFont, const kg_buffer* pTrueTypeData, size_t offset)
{
	kg_true_type_sfnt sfnt;
	kg_result result = kg_peek_data(&sfnt, pTrueTypeData, offset);

	if (result != K15_GUI_RESULT_SUCCESS || ( sfnt != K15_GUI_TRUETYPE_1_SFNT && sfnt != K15_GUI_TRUETYPE_2_SFNT && sfnt != K15_GUI_OPENTYPE_SFNT))
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;
	}

	pOutTrueTypeFont->offset 	= offset;
	pOutTrueTypeFont->data 		= *pTrueTypeData;
	pOutTrueTypeFont->sfnt 		= sfnt;

	kg_parse_true_type_table_offsets(pOutTrueTypeFont);
	kg_parse_true_type_index_loca_format(pOutTrueTypeFont);

	result |= kg_parse_true_type_font_names(pOutTrueTypeFont);
	result |= kg_verify_true_type_data(pOutTrueTypeFont);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	return K15_GUI_RESULT_SUCCESS;

}
/*********************************************************************************/
kg_internal void kg_query_true_type_font_offset_in_collection(size_t* pOutOffset, const kg_buffer* pFontData, const char* pFontName)
{
	size_t offset = 8u; //FK: skip fourCC and version
	kg_u32 fontCount = 0u;

	kg_peek_data(&fontCount, pFontData, offset);
	offset += 4u;

	kg_true_type_font tempFont;

	for (kg_u32 fontIndex = 0u; fontIndex < fontCount; ++fontIndex)
	{
		kg_u32 offsetToFontData = 0u;
		kg_peek_data(&offsetToFontData, pFontData, offset);
	
		kg_result result = kg_init_true_type_font_from_offset(&tempFont, pFontData, offsetToFontData);

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			continue;
		}

		if (kg_true_type_check_font_name(&tempFont, pFontName))
		{
			*pOutOffset = (size_t)offsetToFontData;
			break;
		}
	}
}
/*********************************************************************************/
kg_internal kg_result kg_init_true_type_font(kg_true_type_font* pOutTrueTypeFont, const kg_buffer* pTrueTypeData, const char* pFontName)
{
	size_t offset = 0u;

	if (pFontName != kg_nullptr)
	{
		const kg_u8* pFontMemory = (const kg_u8*)pTrueTypeData->pMemory;
		if (pTrueTypeData->memorySizeInBytes >= 4u &&
			pFontMemory[0] == 't' && 
			pFontMemory[1] == 't' &&
			pFontMemory[2] == 'c' &&
			pFontMemory[3] == 'f')
			{
				kg_query_true_type_font_offset_in_collection(&offset, pTrueTypeData, pFontName);
			}
	}

	return kg_init_true_type_font_from_offset(pOutTrueTypeFont, pTrueTypeData, offset);
}
/*********************************************************************************/
kg_internal kg_result kg_parse_glyph_index_format_4(const kg_true_type_font* pTrueTypeFont, kg_glyph_id* pOutGlyphId, size_t offset, kg_code_point codePoint)
{
	if (codePoint > 0xFFFF)
	{
		return K15_GUI_RESULT_NOT_SUPPORTED;
	}

	const size_t cmapOffset = offset;

	//FK: skip format
	offset += 2u;

	kg_u16 tableLength = 0u;
	kg_read_data(&tableLength, &pTrueTypeFont->data, &offset);

	//FK:	Skip language
	//		https://docs.microsoft.com/de-de/typography/opentype/spec/cmap#language
	//		The language field must be set to zero for all cmap subtables whose platform IDs are other than Macintosh (platform ID 1)
	offset += 2u;

	if (tableLength < 14u)
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;
	}

	kg_u16 segCount = 0u;
	kg_read_data(&segCount, &pTrueTypeFont->data, &offset);
	segCount >>= 1u;

	if (tableLength < (16u + segCount * 8u))
	{
		return K15_GUI_RESULT_FONT_DATA_ERROR;
	}

	kg_u16 searchRange 		= 0u;
	kg_u16 entrySelector 	= 0u;
	kg_u16 rangeShift 		= 0u;

	kg_read_data(&searchRange, &pTrueTypeFont->data, &offset);
	kg_read_data(&entrySelector, &pTrueTypeFont->data, &offset);
	kg_read_data(&rangeShift, &pTrueTypeFont->data, &offset);

	searchRange >>= 1u;
	rangeShift 	>>= 1u;

	const kg_u32 endCountPosition = offset;
	kg_u32 search = endCountPosition;

	kg_u16 cp = 0u;
	kg_peek_data(&cp, &pTrueTypeFont->data, search + rangeShift * 2u);

	if (codePoint >= (kg_code_point)cp)
	{
		search += rangeShift * 2u;
	}

	search -= 2u;

	while( entrySelector )
	{
		kg_u16 end = 0u;
		searchRange >>= 1u;

		kg_peek_data(&end, &pTrueTypeFont->data, search + searchRange * 2u);

		if (codePoint > (kg_code_point)end)
		{
			search += searchRange * 2u;
		}

		--entrySelector;
	}

	search += 2u;

	const kg_u32 item = ((search - endCountPosition) >> 1u);
	kg_u16 start = 0u;

	kg_peek_data(&start, &pTrueTypeFont->data, cmapOffset + 14u + segCount * 2u + 2u + 2u * item);

	if (codePoint < (kg_code_point)start)
	{
		return K15_GUI_RESULT_OUT_OF_BOUNDS;
	}

	kg_u16 idOffset = 0u;
	kg_peek_data(&idOffset, &pTrueTypeFont->data, cmapOffset + 14u + segCount * 6u + 2u + 2u * item);	

	offset = (size_t)idOffset;

	kg_u16 codePointOffset = 0u;
	
	if (offset == 0u)
	{
		kg_peek_data(&codePointOffset, &pTrueTypeFont->data, cmapOffset + 14u + segCount * 4u + 2u + 2u * item);
		*pOutGlyphId = (codePoint + (kg_code_point)codePointOffset) & 0xffffu;
		return K15_GUI_RESULT_SUCCESS;
	}

	kg_peek_data(&codePointOffset, &pTrueTypeFont->data, offset + (codePoint - (kg_code_point)start) * 2u + cmapOffset + 14u + segCount * 6u + 2u + 2u * item);
	*pOutGlyphId = (kg_code_point)codePointOffset & 0xffffu;
	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result kg_parse_glyph_index_format_12_and_13(const kg_true_type_font* pTrueTypeFont, kg_glyph_id* pOutGlyphId, size_t offset, kg_u16 format, kg_code_point codePoint)
{
	//FK: Skip format, ength, language and reserved
	offset += 12u;

	kg_u32 segCount = 0u;
	kg_read_data(&segCount, &pTrueTypeFont->data, &offset);

	for (kg_u32 segId = 0u; segId < segCount; ++segId)
	{
		kg_u32 startChar = 0u;
		kg_u32 endChar = 0u;

		kg_read_data(&startChar, &pTrueTypeFont->data, &offset);
		kg_read_data(&endChar, &pTrueTypeFont->data, &offset);
	
		if (codePoint < startChar || codePoint > endChar)
		{
			offset += 4u;
			continue;
		}

		kg_u32 startGlyphId = 0u;
		kg_read_data(&startGlyphId, &pTrueTypeFont->data, &offset);

		if (format == 12u)
		{
			*pOutGlyphId = startGlyphId + codePoint - startChar;
			return K15_GUI_RESULT_SUCCESS;
		}
		else if (format == 13u)
		{
			*pOutGlyphId = startGlyphId;
			return K15_GUI_RESULT_SUCCESS;
		}		
	}

	return K15_GUI_RESULT_OUT_OF_BOUNDS;
}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_code_point_glyph_id(const kg_true_type_font* pTrueTypeFont, kg_glyph_id* pOutGlyphId, kg_code_point codePoint)
{
	if (((codePoint & 0xFFFFu) == 0xFFFFu) || ((codePoint & 0xFFFFu) == 0xFFFEu) || ((codePoint >= 0xFDD0u) && (codePoint <= 0xFDEFu)))
	{
		return K15_GUI_RESULT_OUT_OF_BOUNDS;
	}

	kg_result result = K15_GUI_RESULT_NOT_SUPPORTED; 
	size_t offset = pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CMAP];
	
	//FK: Skip version entry in cmpa table
	offset += 2u;

	kg_u16 encodingTableCount = 0u;
	kg_read_data(&encodingTableCount, &pTrueTypeFont->data, &offset);

	kg_u32 cmapBlockOffset = 0u;

	for (kg_u16 encodingTableIndex = 0u; encodingTableIndex < encodingTableCount; ++encodingTableIndex)
	{
		size_t 	encodingEntryOffset = (size_t)(pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CMAP] + 4u + 8u * encodingTableIndex);
		kg_u16 	encodingPlatform = 0u;

		kg_read_data(&encodingPlatform, &pTrueTypeFont->data, &encodingEntryOffset);
	
		switch(encodingPlatform)
		{
			case K15_GUI_TRUETYPE_PLATFORM_ID_MICROSOFT:
				kg_u16 encodingId = 0u;
				kg_read_data(&encodingId, &pTrueTypeFont->data, &encodingEntryOffset);

				switch(encodingId)
				{
					case K15_GUI_TRUETYPE_ENCODING_ID_UNICODE_BMP:
					case K15_GUI_TRUETYPE_ENCODING_ID_UNICODE_FULL:
						kg_peek_data(&cmapBlockOffset, &pTrueTypeFont->data, encodingEntryOffset);
						break;
				}
				break;

			case K15_GUI_TRUETYPE_PLATFORM_ID_UNICODE:
				encodingEntryOffset += 2u;
				kg_peek_data(&cmapBlockOffset, &pTrueTypeFont->data, encodingEntryOffset);
				break;
		}

		if (cmapBlockOffset == 0u)
		{
			continue;
		}

		const kg_u32 cmapBlockPosition = cmapBlockOffset + pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CMAP];
		offset = cmapBlockPosition;

		kg_u16 format = 0u;
		kg_peek_data(&format, &pTrueTypeFont->data, offset);

		kg_result result;

		switch (format)
		{
			case 4u:
				result = kg_parse_glyph_index_format_4( pTrueTypeFont, pOutGlyphId, offset, codePoint);
				break;

			case 12u:
			case 13u:
				result = kg_parse_glyph_index_format_12_and_13( pTrueTypeFont, pOutGlyphId, offset, format, codePoint);
				break;
		}

		if (result == K15_GUI_RESULT_SUCCESS)
		{
			return K15_GUI_RESULT_SUCCESS;
		}
	}

	return K15_GUI_RESULT_NOT_SUPPORTED;
}
/*********************************************************************************/

/*********************************************************************************/
kg_internal kg_glyph_cache_entry* kg_find_glyph_r(kg_code_point codePoint, const kg_glyph_cache_entry* pStart, const kg_glyph_cache_entry* pEnd)
{
	if (pStart->codePoint == codePoint)
	{
		return (kg_glyph_cache_entry*)pStart;
	}
	else if (pEnd->codePoint == codePoint)
	{
		return (kg_glyph_cache_entry*)pEnd;
	}
	else if (pStart == pEnd)
	{
		return kg_nullptr;
	}

	const size_t range = (size_t)(pEnd - pStart);
	const kg_glyph_cache_entry* pMid = pStart + (range >> 1u);

	if (codePoint > pMid->codePoint)
	{
		return kg_find_glyph_r(codePoint, pMid, pEnd);
	}
	
	return kg_find_glyph_r(codePoint, pStart, pMid);
	
}
/*********************************************************************************/
kg_internal kg_glyph_cache_entry* kg_find_glyph(kg_glyph_cache* pGlyphCache, kg_code_point codePoint)
{
	if (pGlyphCache->size == 0u)
	{
		return kg_nullptr;
	}

	const kg_glyph_cache_entry* pStart 	= pGlyphCache->pEntries + 0u;
	const kg_glyph_cache_entry* pEnd 	= pGlyphCache->pEntries + (pGlyphCache->size - 1u);

	//FK: binary search
	return kg_find_glyph_r(codePoint, pStart, pEnd);
} 
/*********************************************************************************/
kg_internal kg_glyph_cache_entry* kg_push_glyph(kg_glyph_cache* pGlyphCache)
{
	if (pGlyphCache->size + 1 == pGlyphCache->capacity)
	{
		return kg_nullptr;
	}

	return &pGlyphCache->pEntries[pGlyphCache->size++];
}
/*********************************************************************************/
kg_internal void kg_evict_least_used_glyph(kg_glyph_cache* pGlyphCache)
{
	typedef struct
	{
		kg_glyph_cache_entry* 	pEntry;
		kg_u32					frameIndex;
	} kg_least_used_glyph;

	kg_least_used_glyph leastUsedGlyph;
	leastUsedGlyph.pEntry 		= &pGlyphCache->pEntries[0];
	leastUsedGlyph.frameIndex 	= pGlyphCache->pEntries[0].lastUsedFrameIndex;

	for (kg_u32 glyphIndex = 0u; glyphIndex < pGlyphCache->size; ++glyphIndex)
	{
		if (leastUsedGlyph.frameIndex > pGlyphCache->pEntries[glyphIndex].lastUsedFrameIndex)
		{
			leastUsedGlyph.frameIndex 	= pGlyphCache->pEntries[glyphIndex].lastUsedFrameIndex;
			leastUsedGlyph.pEntry 		= &pGlyphCache->pEntries[glyphIndex];
		}
	}

	const kg_u32 glyphIndex = (size_t)(leastUsedGlyph.pEntry - pGlyphCache->pEntries) / sizeof(kg_glyph_cache_entry);

	if (glyphIndex < (pGlyphCache->size - 1u))
	{
		kg_memcpy(pGlyphCache->pEntries + glyphIndex, pGlyphCache->pEntries + glyphIndex + 1u, (pGlyphCache->size - glyphIndex - 1u)* sizeof(kg_glyph_cache_entry));
	}

	--pGlyphCache->size;
}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_glyf_offset(kg_u32* pOutGlyfOffset, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId)
{
	const kg_u32 offset = pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_LOCA];

	if ( offset == 0u )
	{
		return K15_GUI_RESULT_RESOURCE_NOT_FOUND;
	}

	if ( pTrueTypeFont->indexLocaFormat == 0u )
	{
		kg_u16 glyfOffset 		= 0u;
		kg_u16 nextGlyfOffset 	= 0u;

		kg_peek_data(&glyfOffset, 		&pTrueTypeFont->data, offset + (glyphId + 0u) * 2u);
		kg_peek_data(&nextGlyfOffset, 	&pTrueTypeFont->data, offset + (glyphId + 1u) * 2u);

		if (glyfOffset == nextGlyfOffset)
		{
			return K15_GUI_RESULT_RESOURCE_NOT_FOUND;
		}

		*pOutGlyfOffset = glyfOffset * 2u;

		return K15_GUI_RESULT_SUCCESS;
	}
	else
	{
		kg_u32 glyfOffset 		= 0u;
		kg_u32 nextGlyfOffset 	= 0u;

		kg_peek_data(&glyfOffset,		&pTrueTypeFont->data, offset + (glyphId + 0u) * 4u);
		kg_peek_data(&nextGlyfOffset,	&pTrueTypeFont->data, offset + (glyphId + 1u) * 4u);

		if (glyfOffset == nextGlyfOffset)
		{
			return K15_GUI_RESULT_RESOURCE_NOT_FOUND;
		}

		*pOutGlyfOffset = glyfOffset;

		return K15_GUI_RESULT_SUCCESS;
	}

	return K15_GUI_RESULT_FONT_DATA_ERROR;
}
/*********************************************************************************/
kg_internal kg_true_type_contour* kg_allocate_true_type_glyf_contours(kg_true_type_glyf_outline_context* pOutlineContext, kg_u32 contourCount)
{
	if (pOutlineContext->contourCount + contourCount >= pOutlineContext->contourCapacity)
	{
		return kg_nullptr;
	}

	kg_true_type_contour* pContours = pOutlineContext->pContourBuffer + pOutlineContext->contourCount;
	pOutlineContext->contourCount += contourCount;

	return pContours;
}
/*********************************************************************************/
kg_internal kg_true_type_vertex* kg_allocate_true_type_glyf_vertices(kg_true_type_glyf_outline_context* pOutlineContext, kg_u32 vertexCount)
{
	if (pOutlineContext->vertexCount + vertexCount >= pOutlineContext->vertexCapacity)
	{
		return kg_nullptr;
	}

	kg_true_type_vertex* pVertices = pOutlineContext->pVertexBuffer + pOutlineContext->vertexCount;
	pOutlineContext->vertexCount += vertexCount;

	return pVertices;
}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_simple_glyf_outline(kg_true_type_glyf_outline_context* pOutlineContext, const kg_true_type_font* pTrueTypeFont, kg_u32 glyfOffset)
{
	kg_u32 offset = glyfOffset + pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GLYF];
	kg_u16 contourCount = 0u;

	kg_read_data(&contourCount, &pTrueTypeFont->data, &offset);
	offset += 8u; //FK: skip bounding box

	kg_u16 endPointsOfPreviousContour 	= 0u;
	kg_u32 totalVertexCount 			= 0u;
	const kg_u32 startVertexIndex 		= pOutlineContext->vertexCount;

	kg_true_type_contour* pContours = kg_allocate_true_type_glyf_contours(pOutlineContext, contourCount);

	if (pContours == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	for (kg_u16 contourIndex = 0u; contourIndex < contourCount; ++contourIndex)
	{
		kg_u16 endPointOfContour = 0u;

		kg_read_data(&endPointOfContour, &pTrueTypeFont->data, &offset);
		endPointOfContour += 1u;

		const kg_u32 vertexCount = ((kg_s32)endPointOfContour - (kg_s32)endPointsOfPreviousContour) < 0 ? 0u : endPointOfContour - endPointsOfPreviousContour;

		pContours[ contourIndex ].startIndex 	= startVertexIndex + totalVertexCount;
		pContours[ contourIndex ].length		= vertexCount;

		totalVertexCount += vertexCount;

		endPointsOfPreviousContour = endPointOfContour;
	}

	kg_u16 instructionCount = 0u;
	kg_read_data(&instructionCount, &pTrueTypeFont->data, &offset);
	offset += instructionCount;

	kg_u8 flags = 0u;
	kg_u8 flagRepeatCount = 0u;

	kg_true_type_vertex* pVertices = kg_allocate_true_type_glyf_vertices(pOutlineContext, totalVertexCount);

	if (pVertices == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	for (kg_u32 vertexIndex = 0u; vertexIndex < totalVertexCount; ++vertexIndex)
	{
		if (flagRepeatCount > 0u)
		{
			--flagRepeatCount;
		}
		else
		{
			kg_read_data(&flags, &pTrueTypeFont->data, &offset);

			if ((flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_REPEAT) > 0u)
			{
				if (flagRepeatCount == 0u)
				{
					kg_read_data(&flagRepeatCount, &pTrueTypeFont->data, &offset);
				}
			}
		}

		pVertices[ vertexIndex ].flags 	= flags;
		pVertices[ vertexIndex ].type 	= (flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_ON_CURVE) > 0u ? K15_GUI_TRUETYPE_VERTEX_TYPE_ON_CURVE : K15_GUI_TRUETYPE_VERTEX_TYPE_QUADRATIC;
	}

	kg_s16 previousXCoordinate = 0u;
	kg_s16 previousYCoordinate = 0u;
	kg_s16 xCoordinate = 0u;
	kg_s16 yCoordinate = 0u;

	for (kg_u32 vertexIndex = startVertexIndex; vertexIndex < totalVertexCount; ++vertexIndex)
	{
		kg_true_type_vertex* pVertex = pVertices + vertexIndex;

		if ((pVertex->flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_X_SHORT_VECTOR) > 0u)
		{
			kg_u8 xScale = 0u;
			kg_read_data(&xScale, &pTrueTypeFont->data, &offset);

			xCoordinate = ((pVertex->flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_THIS_X_IS_SAME) > 0u ? 1 : -1);
			xCoordinate *= xScale;
			xCoordinate = previousXCoordinate + xCoordinate;
		}
		else if ((pVertex->flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_THIS_X_IS_SAME) == 0u)
		{
			kg_read_data(&xCoordinate, &pTrueTypeFont->data, &offset);
			xCoordinate = previousXCoordinate + xCoordinate;
		}

		pVertex->xCoordinate 	= xCoordinate;
		previousXCoordinate 	= xCoordinate;
	}

	for (kg_u32 vertexIndex = startVertexIndex; vertexIndex < totalVertexCount; ++vertexIndex)
	{
		kg_true_type_vertex* pVertex = pVertices + vertexIndex;

		if ((pVertex->flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_Y_SHORT_VECTOR) > 0u)
		{
			kg_u8 scale = 0u;
			kg_read_data(&scale, &pTrueTypeFont->data, &offset);

			yCoordinate = ((pVertex->flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_THIS_Y_IS_SAME) > 0u ? 1 : -1);
			yCoordinate *= scale;
			yCoordinate = previousYCoordinate + yCoordinate;
		}
		else if ((pVertex->flags & K15_GUI_TRUE_TYPE_GLYPH_FLAG_THIS_Y_IS_SAME) == 0u)
		{
			kg_read_data(&yCoordinate, &pTrueTypeFont->data, &offset);
			yCoordinate = previousYCoordinate + yCoordinate;
		}

		pVertex->yCoordinate 	= pOutlineContext->yMax - yCoordinate;
		previousYCoordinate 	= yCoordinate;
	}

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_f32 kg_convert_fixed_point_to_f32(kg_s16 fixedPoint)
{
	return (kg_f32)fixedPoint / 16384.0f;
}
/*********************************************************************************/
kg_internal void kg_parse_true_type_glyf_transformation(kg_f32* pOutTransformation, kg_u32* pInOutOffset, const kg_true_type_font* pTrueTypeFont, kg_u16 flags)
{
	if ( (flags & K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_ARGS_ARE_XY_VALUES) > 0u )
	{
		if ( (flags & K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_ARG1_AND_2_ARE_WORDS) > 0u )
		{
			kg_u16 arg1 = 0u;
			kg_u16 arg2 = 0u;

			kg_read_data(&arg1, &pTrueTypeFont->data, pInOutOffset);
			kg_read_data(&arg2, &pTrueTypeFont->data, pInOutOffset);

			pOutTransformation[4] = (kg_f32)arg1;
			pOutTransformation[5] = (kg_f32)arg2;
		}
		else
		{
			kg_u8 arg1 = 0u;
			kg_u8 arg2 = 0u;

			kg_read_data(&arg1, &pTrueTypeFont->data, pInOutOffset);
			kg_read_data(&arg2, &pTrueTypeFont->data, pInOutOffset);

			pOutTransformation[4] = (kg_f32)arg1;
			pOutTransformation[5] = (kg_f32)arg2;
		}
	}

	if ( (flags & K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_WE_HAVE_A_SCALE) > 0u )
	{
		kg_s16 fixedPointScale = 0u;
		kg_read_data(&fixedPointScale, &pTrueTypeFont->data, pInOutOffset);

		const kg_f32 scaleFloat = kg_convert_fixed_point_to_f32(fixedPointScale);

		pOutTransformation[0] = scaleFloat;
		pOutTransformation[1] = 0.0f;
		pOutTransformation[2] = 0.0f;
		pOutTransformation[3] = scaleFloat;
	}
	else if ( (flags & K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_WE_HAVE_AN_X_AND_Y_SCALE) > 0u )
	{
		kg_s16 fixedPointScaleX = 0u;
		kg_s16 fixedPointScaleY = 0u;

		kg_read_data(&fixedPointScaleX, &pTrueTypeFont->data, pInOutOffset);
		kg_read_data(&fixedPointScaleY, &pTrueTypeFont->data, pInOutOffset);

		pOutTransformation[0] = kg_convert_fixed_point_to_f32(fixedPointScaleX);
		pOutTransformation[1] = 0.f;
		pOutTransformation[2] = 0.f;
		pOutTransformation[3] = kg_convert_fixed_point_to_f32(fixedPointScaleY);
	}
	else if ( (flags & K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_WE_HAVE_A_TWO_BY_TWO) > 0u )
	{
		kg_s16 fixedPointScaleX = 0u;
		kg_s16 fixedPointScaleY = 0u;
		kg_s16 fixedPointPosX 	= 0u;
		kg_s16 fixedPointPosY 	= 0u;

		kg_read_data(&fixedPointScaleX, &pTrueTypeFont->data, pInOutOffset);
		kg_read_data(&fixedPointPosX, 	&pTrueTypeFont->data, pInOutOffset);
		kg_read_data(&fixedPointPosY, 	&pTrueTypeFont->data, pInOutOffset);
		kg_read_data(&fixedPointScaleY, &pTrueTypeFont->data, pInOutOffset);

		pOutTransformation[0] = kg_convert_fixed_point_to_f32( fixedPointScaleX );
		pOutTransformation[1] = kg_convert_fixed_point_to_f32( fixedPointPosX );
		pOutTransformation[2] = kg_convert_fixed_point_to_f32( fixedPointPosY );
		pOutTransformation[3] = kg_convert_fixed_point_to_f32( fixedPointScaleY );
	}
}
/*********************************************************************************/
kg_result kg_parse_true_type_glyf_outline(kg_true_type_glyf_outline_context* pOutlineContext, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId);
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_compound_glyf_outline(kg_true_type_glyf_outline_context* pOutlineContext, const kg_true_type_font* pTrueTypeFont, kg_u32 offset)
{
	offset = offset + pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GLYF];
	offset += 10u; //FK: Skip contour count and bounding box
	while ( kg_true )
	{
		kg_u16 flags 				= 0u;
		kg_u16 contourGlyphIndex 	= 0u;
		
		kg_read_data(&flags, &pTrueTypeFont->data, &offset);
		kg_read_data(&contourGlyphIndex, &pTrueTypeFont->data, &offset);

		const kg_u32 startVertexIndex = pOutlineContext->vertexCount;
		kg_result result = kg_parse_true_type_glyf_outline(pOutlineContext, pTrueTypeFont, contourGlyphIndex);			
		
		if (result != K15_GUI_RESULT_SUCCESS)
		{
			return result;
		}
		
		kg_f32 transformation[6] = { 1.f, 0.f, 0.f, 1.f, 0.f, 0.f };
		kg_parse_true_type_glyf_transformation(transformation, &offset, pTrueTypeFont, flags);

		const kg_f32 xScale = kg_sqrtf( transformation[0] * transformation[0] + transformation[1] * transformation[1] );
		const kg_f32 yScale = kg_sqrtf( transformation[2] * transformation[2] + transformation[3] * transformation[3] );

		for (kg_u32 vertexIndex = startVertexIndex; vertexIndex < pOutlineContext->vertexCount; ++vertexIndex)
		{
			kg_true_type_vertex* pVertex = pOutlineContext->pVertexBuffer + vertexIndex;
			const kg_f32 x = (kg_f32)pVertex->xCoordinate;
			const kg_f32 y = (kg_f32)pVertex->yCoordinate;
		
			pVertex->xCoordinate = (kg_s16)(xScale * (transformation[0] * x + transformation[2] * y + transformation[4]));
			pVertex->yCoordinate = (kg_s16)(yScale * (transformation[1] * x + transformation[3] * y + transformation[5]));
		}

		if ( (flags & K15_GUI_TRUE_TYPE_COMPOUND_GLYPH_FLAG_MORE_COMPONENTS) == 0u )
		{
			break;
		}
	}
	return K15_GUI_RESULT_SUCCESS;

}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_glyf_outline(kg_true_type_glyf_outline_context* pOutlineContext, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId)
{
	kg_u32 glyfOffset = 0u;
	kg_result result = kg_parse_true_type_glyf_offset(&glyfOffset, pTrueTypeFont, glyphId);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_u32 offset = glyfOffset + pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GLYF];

	kg_s16 contourCount = 0u;
	kg_read_data(&contourCount, &pTrueTypeFont->data, &offset);

	result = K15_GUI_RESULT_NOT_SUPPORTED;

	if (contourCount < 0)
	{
		result = kg_parse_true_type_compound_glyf_outline(pOutlineContext, pTrueTypeFont, glyfOffset);
	}
	else
	{
		result = kg_parse_true_type_simple_glyf_outline(pOutlineContext, pTrueTypeFont, glyfOffset);
	}

	return result;
}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_glyf_outline_and_bounding_box(kg_true_type_glyf_outline_context* pOutlineContext, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId)
{
	kg_u32 glyfOffset = 0u;
	kg_result result = kg_parse_true_type_glyf_offset(&glyfOffset, pTrueTypeFont, glyphId);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_u32 offset = glyfOffset + pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GLYF] + 2u;
	kg_read_data(&pOutlineContext->xMin, &pTrueTypeFont->data, &offset);
	kg_read_data(&pOutlineContext->yMin, &pTrueTypeFont->data, &offset);
	kg_read_data(&pOutlineContext->xMax, &pTrueTypeFont->data, &offset);
	kg_read_data(&pOutlineContext->yMax, &pTrueTypeFont->data, &offset);

	return kg_parse_true_type_glyf_outline(pOutlineContext, pTrueTypeFont, glyphId);
}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_glyph_outline_cff(kg_glyph_outline* pOutGlyphOutline, kg_linear_allocator* pAllocator, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId)
{
	return K15_GUI_RESULT_NOT_SUPPORTED;
}
/*********************************************************************************/
kg_internal kg_result kg_begin_true_type_glyf_outline_parse(kg_glyph_outline* pOutGlyphOutline, kg_linear_allocator* pAllocator, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId)
{
	kg_true_type_contour* pContourBuffer = kg_nullptr;
	kg_true_type_vertex* pVertexBuffer = kg_nullptr;

	const size_t maxVertexCount = 512u;
	const size_t maxContourCount = 256u;

	kg_result result = K15_GUI_RESULT_SUCCESS;
	result |= kg_allocate_from_linear_allocator(&pContourBuffer, pAllocator, sizeof(kg_true_type_contour) * 512u);
	result |= kg_allocate_from_linear_allocator(&pVertexBuffer, pAllocator, sizeof(kg_true_type_vertex) * 512u);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_true_type_glyf_outline_context outlineContext;
	outlineContext.pContourBuffer 	= pContourBuffer;
	outlineContext.pVertexBuffer 	= pVertexBuffer;
	outlineContext.vertexCount 		= 0u;
	outlineContext.contourCount 	= 0u;
	outlineContext.vertexCapacity 	= maxVertexCount;
	outlineContext.contourCapacity 	= maxContourCount;

	result |= kg_parse_true_type_glyf_outline_and_bounding_box(&outlineContext, pTrueTypeFont, glyphId);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	pOutGlyphOutline->pContours 	= outlineContext.pContourBuffer;
	pOutGlyphOutline->pVertices 	= outlineContext.pVertexBuffer;
	pOutGlyphOutline->contourCount 	= outlineContext.contourCount;
	pOutGlyphOutline->vertexCount 	= outlineContext.vertexCount;
	pOutGlyphOutline->xMin 			= outlineContext.xMin;
	pOutGlyphOutline->yMin 			= outlineContext.yMin;
	pOutGlyphOutline->xMax 			= outlineContext.xMax;
	pOutGlyphOutline->yMax 			= outlineContext.yMax;
	
	return result;
}
/*********************************************************************************/
kg_internal kg_result kg_parse_true_type_glyph_outline(kg_glyph_outline* pOutGlyphOutline, kg_linear_allocator* pAllocator, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId)
{
	if ( pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_GLYF] > 0u )
	{
		return kg_begin_true_type_glyf_outline_parse(pOutGlyphOutline, pAllocator, pTrueTypeFont, glyphId);
	}
	else if( pTrueTypeFont->tableOffsets[K15_GUI_TRUETYPE_TABLE_CFF] > 0u )
	{
		return kg_parse_true_type_glyph_outline_cff(pOutGlyphOutline, pAllocator, pTrueTypeFont, glyphId);
	}

	return K15_GUI_RESULT_FONT_DATA_ERROR;
}
/*********************************************************************************/
kg_internal kg_float2 kg_generate_line_points_on_quadratic_curve_step(kg_float2 p0, kg_float2 p1, kg_float2 cp, kg_f32 t)
{
	if (t <= 0.0f)
	{
		return p0;
	}

	if (t >= 1.0f)
	{
		return p1;
	}

	kg_float2 a0 = kg_float2_zero();
	kg_float2 a1 = kg_float2_zero();
	kg_float2 a2 = kg_float2_zero();

	a0.x = p0.x * (1.0f - t) + cp.x * t;
	a0.y = p0.y * (1.0f - t) + cp.y * t;

	a1.x = cp.x * (1.0f - t) + p1.x * t;
	a1.y = cp.y * (1.0f - t) + p1.y * t;

	a2.x = a0.x * (1.0f - t) + a1.x * t;
	a2.y = a0.y * (1.0f - t) + a1.y * t;

	return a2;
}
/*********************************************************************************/
kg_internal size_t kg_generate_line_points_on_quadratic_curve(kg_float2* pPoints, size_t pointCount, kg_float2 p0, kg_float2 p1, kg_float2 cp, kg_f32 error)
{
	if (pointCount == 0u)
	{
		return 0u;
	}

	if (pPoints == kg_nullptr)
	{
		return 0u;
	}

	pPoints[0u] = p0;

	if (pointCount == 2u)
	{
		pPoints[1u] = p1;
		return 2u;
	}

	if (pointCount == 1u)
	{
		return 1u;
	}

	size_t pointCounter = 1u;

	const float dt = 1.f / (float)(pointCount - 1u);
	float t = dt;

	kg_float2 nextPointOnCurve = kg_generate_line_points_on_quadratic_curve_step(p0, p1, cp, dt);
	kg_float2 lastTangent = kg_float2_normalize(kg_float2_sub(nextPointOnCurve, p0));

	for (size_t pointIndex = 1u; pointIndex < (pointCount - 1u); ++pointIndex, t += dt)
	{
		const kg_float2 currentPointOnCurve = nextPointOnCurve;
		nextPointOnCurve = kg_generate_line_points_on_quadratic_curve_step(p0, p1, cp, t + dt);

		const kg_float2 tangent = kg_float2_normalize(kg_float2_sub(nextPointOnCurve, currentPointOnCurve));
		const float d = kg_float2_dot(tangent, lastTangent);

		if (d < error)
		{
			pPoints[pointCounter++] = currentPointOnCurve;
			lastTangent = tangent;
		}
	}

	pPoints[pointCounter++] = p1;

	kg_assert(pointCounter <= pointCount);

	return pointCounter;
}
/*********************************************************************************/
kg_internal size_t kg_true_type_create_line_segments_from_glyph_outline(kg_line_float_2d** pOutLines, kg_linear_allocator* pAllocator, kg_glyph_outline* pOutline)
{
	const kg_f32 defaultError = 0.98f;
	const size_t lineBatchCount = 256u;
	kg_line_float_2d* pLines = kg_nullptr;

	kg_result result = kg_allocate_from_linear_allocator(&pLines, pAllocator, sizeof(kg_line_float_2d) * lineBatchCount);
	if (result != K15_GUI_RESULT_SUCCESS)
	{	
		return 0u;
	}

	size_t lineIndex = 0u;
	for (kg_u32 contourIndex = 0u; contourIndex < pOutline->contourCount; ++contourIndex)
	{
		const kg_true_type_contour* pContour 	= pOutline->pContours + contourIndex;
		const kg_true_type_vertex* pV0 			= pOutline->pVertices + pContour->startIndex; 
		for (kg_u32 vertexIndex = pContour->startIndex; vertexIndex < pContour->startIndex + pContour->length; )
		{
			const kg_true_type_vertex* pV1 = ( vertexIndex + 1u ) == pContour->length + pContour->startIndex ? pOutline->pVertices + pContour->startIndex : pOutline->pVertices + vertexIndex + 1u;
			const kg_true_type_vertex* pV2 = ( vertexIndex + 2u ) == pContour->length + pContour->startIndex ? pOutline->pVertices + pContour->startIndex : pOutline->pVertices + vertexIndex + 2u;
			
			if(pV1->type == K15_GUI_TRUETYPE_VERTEX_TYPE_ON_CURVE)
			{
				pLines[lineIndex++] = kg_init_line_float_2d(pV0->xCoordinate, pV0->yCoordinate, pV1->xCoordinate, pV1->yCoordinate);
				pV0 = pV1;
				vertexIndex += 1u;
				continue;
			}
			else if(pV1->type == K15_GUI_TRUETYPE_VERTEX_TYPE_QUADRATIC && pV2->type == K15_GUI_TRUETYPE_VERTEX_TYPE_ON_CURVE)
			{
				const kg_float2 p0 = {pV0->xCoordinate, pV0->yCoordinate};
				const kg_float2 cp = {pV1->xCoordinate, pV1->yCoordinate};
				const kg_float2 p1 = {pV2->xCoordinate, pV2->yCoordinate};

				kg_float2* pPoints = kg_nullptr;
				kg_allocate_from_linear_allocator(&pPoints, pAllocator, sizeof(kg_float2) * 32u);
				const size_t pointCount = kg_generate_line_points_on_quadratic_curve(pPoints, 32u, p0, p1, cp, defaultError);
				if (pointCount == 0u)
				{
					continue;
				}

				for (size_t pointIndex = 0u; pointIndex < ( pointCount - 1u ); ++pointIndex)
				{
					pLines[lineIndex++] = kg_init_line_float_2d(pPoints[pointIndex].x, pPoints[pointIndex].y, pPoints[pointIndex + 1].x, pPoints[pointIndex + 1].y);					
				}

				pV0 = pV2;
				vertexIndex += 2u;
			}
			else if(pV1->type == K15_GUI_TRUETYPE_VERTEX_TYPE_QUADRATIC && pV2->type == K15_GUI_TRUETYPE_VERTEX_TYPE_QUADRATIC)
			{
				const kg_true_type_vertex* pV3 = pOutline->pVertices + vertexIndex + 3u;

				const kg_float2 cp1 = {pV1->xCoordinate, pV1->yCoordinate};
				const kg_float2 cp2 = {pV2->xCoordinate, pV2->yCoordinate};

				const kg_float2 p0 = {pV0->xCoordinate, pV0->yCoordinate};
				const kg_float2 p1 = {(cp1.x + cp2.x) * 0.5f, (cp1.y + cp2.y) * 0.5f};
				const kg_float2 p2 = {pV3->xCoordinate, pV3->yCoordinate};
				
				vertexIndex += 3u;
				pV0 = pV3;

				kg_float2* pPoints = kg_nullptr;
				kg_allocate_from_linear_allocator(&pPoints, pAllocator, sizeof(kg_float2) * 32u);
				size_t pointCount = kg_generate_line_points_on_quadratic_curve(pPoints, 32u, p0, p1, cp1, defaultError);
				if (pointCount == 0u)
				{
					continue;
				}
				
				for (size_t pointIndex = 0u; pointIndex < (pointCount - 1u); ++pointIndex)
				{
					pLines[lineIndex++] = kg_init_line_float_2d(pPoints[pointIndex].x, pPoints[pointIndex].y, pPoints[pointIndex + 1].x, pPoints[pointIndex + 1].y);					
				}

				if (lineIndex == lineBatchCount)
				{
					break;
				}

				pointCount = kg_generate_line_points_on_quadratic_curve(pPoints, 32u, p1, p2, cp2, defaultError);
				if (pointCount == 0u)
				{
					continue;
				}
				
				for (size_t pointIndex = 0u; pointIndex < (pointCount - 1u); ++pointIndex)
				{
					pLines[lineIndex++] = kg_init_line_float_2d(pPoints[pointIndex].x, pPoints[pointIndex].y, pPoints[pointIndex + 1].x, pPoints[pointIndex + 1].y);					
				}

				if (lineIndex == lineBatchCount)
				{
					break;
				}

			}
		}
	}

	*pOutLines = pLines;
	return lineIndex;
}
/*********************************************************************************/
kg_internal kg_result kg_rasterize_true_type_glyph(kg_linear_allocator* pAllocator, kg_glyph_cache_entry* pGlyph, kg_texture_atlas* pAtlas, const kg_true_type_font* pTrueTypeFont, kg_glyph_id glyphId, kg_u32 unitsPerEm, kg_u32 dpi, kg_u32 fontSize)
{
	kg_glyph_outline glyphOutline;
	kg_result result = kg_parse_true_type_glyph_outline(&glyphOutline, pAllocator, pTrueTypeFont, glyphId);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_line_float_2d* pLines = kg_nullptr;
	const size_t lineCount = kg_true_type_create_line_segments_from_glyph_outline(&pLines, pAllocator, &glyphOutline);

	const kg_f32 unitsToPixel 			= (float)(fontSize * dpi * (glyphOutline.xMax - glyphOutline.xMin)) / (float)(dpi * unitsPerEm);//pointSize * resolution / ( 72 points per inch * units_per_em )
	const kg_u32 glyphWidthInPixels 	= (kg_u32)(((glyphOutline.xMax - glyphOutline.xMin) * unitsToPixel) + 0.5f);
	const kg_u32 glyphHeightInPixels 	= (kg_u32)(((glyphOutline.yMax - glyphOutline.yMin) * unitsToPixel) + 0.5f);
	
	kg_texture_atlas_slot* pAtlasSlot = kg_nullptr;
	result = kg_allocate_texture_atlas_slot(&pAtlasSlot, pAtlas, glyphWidthInPixels, glyphHeightInPixels);
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	//pAtlas->
	//FK: TODO rasterize


	return result;
}
/*********************************************************************************/
kg_internal kg_result kg_create_glyph_cache(kg_glyph_cache* pOutGlyphCache, kg_linear_allocator* pAllocator, kg_u32 glyphCacheSize, kg_u16 glyphAtlasDimension)
{
	kg_texture_atlas glyphAtlas;
	kg_result result = kg_create_texture_atlas(&glyphAtlas, pAllocator, glyphAtlasDimension, glyphAtlasDimension, K15_GUI_PIXEL_FORMAT_R8);
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	const size_t glyphArraySize = sizeof(kg_glyph_cache_entry) * glyphCacheSize;
	kg_glyph_cache_entry* pGlyphEntries = kg_nullptr;

	result = kg_allocate_from_linear_allocator(&pGlyphEntries, pAllocator, glyphArraySize);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	pOutGlyphCache->capacity 	= glyphCacheSize;
	pOutGlyphCache->size		= 0u;
	pOutGlyphCache->pEntries	= pGlyphEntries;
	pOutGlyphCache->atlas		= glyphAtlas;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result kg_create_image_cache(kg_image_cache* pOutImageCache, kg_linear_allocator* pAllocator, kg_u32 imageAtlasDimension)
{
	kg_texture_atlas imageAtlas;
	kg_result result = kg_create_texture_atlas(&imageAtlas, pAllocator, imageAtlasDimension, imageAtlasDimension, K15_GUI_PIXEL_FORMAT_R8G8B8A8);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_hash_map imageHashMap;
	result = kg_create_hash_map(&imageHashMap, pAllocator, sizeof(kg_image_cache_entry));

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	pOutImageCache->hashMap = imageHashMap;
	pOutImageCache->atlas 	= imageAtlas;

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal const kg_context_parameter* kg_get_default_context_parameter()
{
	static kg_context_parameter defaultParameter;
	static const size_t defaultDataMemorySize = kg_size_mega_bytes(5);
		
	void* pMemory = kg_malloc(defaultDataMemorySize, kg_nullptr);

	if (pMemory == kg_nullptr)
	{
	}

	defaultParameter.scratchBuffer = kg_create_buffer(pMemory, defaultDataMemorySize);

	return &defaultParameter;
}
/*********************************************************************************/
kg_internal const kg_render_context_parameter* kg_get_default_render_context_parameter()
{
	static const kg_u32 defaultVertexMemorySize = 4096u * VertexStride;
	static const kg_u32 defaultIndexMemorySize 	= 4096u * IndexSize;
	
	static kg_render_context_parameter defaultParameter;

	void* pVertexMemory = kg_malloc(defaultVertexMemorySize, kg_nullptr);
	void* pIndexMemory 	= kg_malloc(defaultIndexMemorySize, kg_nullptr);

	defaultParameter.vertexBufferCount 	= 1u;
	defaultParameter.vertexBuffer[0] = kg_create_buffer(pVertexMemory, defaultVertexMemorySize);

	defaultParameter.indexBufferCount 	= 1u;
	defaultParameter.indexBuffer[0] = kg_create_buffer(pIndexMemory, defaultIndexMemorySize);

	return &defaultParameter;
}
/*********************************************************************************/
kg_internal kg_bool kg_is_invalid_buffer(const kg_buffer* pBuffer)
{
	if (pBuffer == kg_nullptr)
	{
		return kg_true;
	}

	if (pBuffer->pMemory == kg_nullptr)
	{
		return kg_true;
	}

	if (pBuffer->memorySizeInBytes == 0u)
	{
		return kg_true;
	}

	return kg_false;
}
/*********************************************************************************/
kg_internal kg_bool kg_is_invalid_context_parameter(const kg_context_parameter* pParameter)
{
	if (pParameter == kg_nullptr)
	{
		return kg_true;
	}

	if (kg_is_invalid_buffer(&pParameter->scratchBuffer))
	{
		return kg_true;
	}

	return kg_false;
}
/*********************************************************************************/
kg_internal kg_bool kg_is_invalid_render_context_parameter(const kg_render_context_parameter* pParameter)
{
	if (pParameter == kg_nullptr)
	{
		return kg_true;
	}	

	if (pParameter->vertexBufferCount == 0u)
	{
		return kg_true;
	}

	if (pParameter->vertexBufferCount > K15_GUI_MAX_RENDER_BUFFER_COUNT)
	{
		return kg_true;
	}

	if (pParameter->indexBufferCount == 0u)
	{
		return kg_true;
	}

	if (pParameter->indexBufferCount > K15_GUI_MAX_RENDER_BUFFER_COUNT)
	{
		return kg_true;
	}

	if (pParameter->indexDataType != K15_GUI_INDEX_DATA_TYPE_INT && pParameter->indexDataType != K15_GUI_INDEX_DATA_TYPE_SHORT)
	{
		return kg_true;
	}

	for (kg_u32 vertexBufferIndex = 0u; vertexBufferIndex < pParameter->vertexBufferCount; ++vertexBufferIndex)
	{
		if (kg_is_invalid_buffer(&pParameter->vertexBuffer[vertexBufferIndex]))
		{
			return kg_true;
		}
	}

	for (kg_u32 indexBufferIndex = 0u; indexBufferIndex < pParameter->indexBufferCount; ++indexBufferIndex)
	{
		if (kg_is_invalid_buffer(&pParameter->indexBuffer[indexBufferIndex]))
		{
			return kg_true;
		}
	}

	return kg_false;
}
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
/*********************************************************************************/
kg_internal kg_u32 kg_get_text_length(const kg_utf8* pUtf8Text)
{
	kg_u32 length = 0u;
	while(*pUtf8Text)
	{
		kg_code_point codePoint;
		pUtf8Text += kg_read_code_point(pUtf8Text, &codePoint);
		++length;
	}

	return length;
}

kg_internal kg_bool kg_is_invalid_context_handle(kg_context_handle contextHandle)
{
	if (contextHandle.value == 0)
	{
		return kg_true;
	}

	const kg_context* pContext = (kg_context*)contextHandle.value;
	return !(pContext->fourCC[0] == 'K' && pContext->fourCC[1] == 'G' && pContext->fourCC[2] == 'U' && pContext->fourCC[3] == 'I');
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

kg_internal kg_linear_allocator* kg_get_frame_allocator_from_current_frame(kg_context* pContext)
{
	return &pContext->frameAllocators[pContext->frameCounter % 2 == 0 ? 0 : 1];
}

kg_internal kg_hash_map* kg_get_element_hash_map_from_current_frame(kg_context* pContext)
{
	return &pContext->elements[pContext->frameCounter % 2  == 0 ? 0 : 1];
}

kg_internal kg_hash_map* kg_get_window_hash_map_from_current_frame(kg_context* pContext)
{
	return &pContext->windows[pContext->frameCounter % 2  == 0 ? 0 : 1];
}

kg_internal const kg_hash_map* kg_get_element_hash_map_from_last_frame(const kg_context* pContext)
{
	return &pContext->elements[pContext->frameCounter % 2  != 0 ? 0 : 1];
}

kg_internal const kg_hash_map* kg_get_window_hash_map_from_last_frame(const kg_context* pContext)
{
	return &pContext->windows[pContext->frameCounter % 2  != 0 ? 0 : 1];
}

kg_internal kg_result kg_create_input_system(kg_input_system* pOutinputSystem, kg_linear_allocator* pAllocator)
{
	kg_assert(pOutinputSystem != kg_nullptr);
	kg_assert(kg_is_invalid_linear_allocator(pAllocator) == kg_false);

	const size_t inputBufferCount		= 32u;
	const size_t inputBufferSizeInBytes = inputBufferCount * sizeof(kg_input_event);

	void* pInputMemory = kg_nullptr;
	kg_result result = kg_allocate_from_linear_allocator(&pInputMemory, pAllocator, inputBufferSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_linear_allocator allocator;
	result = kg_create_linear_allocator(&allocator, pInputMemory, inputBufferSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_input_system inputSystem;
	inputSystem.pFirstEvent 	= kg_nullptr;
	inputSystem.allocator 		= allocator;
	inputSystem.pHotElement		= kg_nullptr;
	inputSystem.pActiveElement	= kg_nullptr;
	*pOutinputSystem = inputSystem;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_create_render_context(kg_render_context* pOutRenderContext, const kg_render_context_parameter* pParameter)
{
	if (kg_is_invalid_render_context_parameter(pParameter))
	{
		return K15_GUI_RESULT_INVALID_RENDER_CONTEXT_PARAMETER;
	}
	
	kg_render_context context;
 	kg_result result = K15_GUI_RESULT_SUCCESS;
	 
	for (kg_u32 indexBufferIndex = 0u; indexBufferIndex < pParameter->indexBufferCount; ++indexBufferIndex)
	{
		result = kg_create_linear_allocator(&context.indexAllocators[indexBufferIndex], pParameter->indexBuffer[indexBufferIndex].pMemory, pParameter->indexBuffer[indexBufferIndex].memorySizeInBytes );

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			return result;
		}
	}

	for (kg_u32 vertexBufferIndex = 0u; vertexBufferIndex < pParameter->vertexBufferCount; ++vertexBufferIndex)
	{
		result = kg_create_linear_allocator(&context.vertexAllocators[vertexBufferIndex], pParameter->vertexBuffer[vertexBufferIndex].pMemory, pParameter->vertexBuffer[vertexBufferIndex].memorySizeInBytes );

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			return result;
		}
	}

	context.vertexAllocatorCount 	= pParameter->vertexBufferCount;
	context.indexAllocatorCount 	= pParameter->indexBufferCount;
	
	*pOutRenderContext = context;

	pOutRenderContext->pIndexAllocator 	= &pOutRenderContext->indexAllocators[0u];
	pOutRenderContext->pVertexAllocator = &pOutRenderContext->vertexAllocators[0u];
	pOutRenderContext->indexDataType	= pParameter->indexDataType;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal void kg_swap_render_buffers(kg_render_context* pRenderContext)
{
	const kg_u32 indexAllocatorIndex 	= (1u + (pRenderContext->pIndexAllocator  - pRenderContext->indexAllocators)  / kg_ptr_size_in_bytes) % pRenderContext->indexAllocatorCount;
	const kg_u32 vertexAllocatorIndex 	= (1u + (pRenderContext->pVertexAllocator - pRenderContext->pVertexAllocator) / kg_ptr_size_in_bytes) % pRenderContext->vertexAllocatorCount;

	pRenderContext->pIndexAllocator 	= &pRenderContext->indexAllocators[indexAllocatorIndex];
	pRenderContext->pVertexAllocator	= &pRenderContext->vertexAllocators[vertexAllocatorIndex];

	kg_reset_linear_allocator(pRenderContext->pIndexAllocator, 0u);
	kg_reset_linear_allocator(pRenderContext->pVertexAllocator, 0u);
}

kg_internal kg_u32 kg_get_index_data_type_size_in_bytes(kg_index_data_type indexDataType)
{
	switch(indexDataType)
	{
		case K15_GUI_INDEX_DATA_TYPE_SHORT:
			return 2u;

		case K15_GUI_INDEX_DATA_TYPE_INT:
			return 4u;
	}

	return 0u;
}

kg_internal kg_result kg_create_error_stack(kg_error_stack* pOutErrorStack, kg_linear_allocator* pAllocator)
{
	kg_assert(pOutErrorStack != kg_nullptr);
	kg_assert(kg_is_invalid_linear_allocator(pAllocator) == kg_false);

	const size_t errorStackCount 		= 32u;
	const size_t errorStackSizeInBytes 	= errorStackCount * sizeof(kg_error);

	void* pMemory = kg_nullptr;
	kg_result result = kg_allocate_from_linear_allocator(&pMemory, pAllocator, errorStackSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_linear_allocator errorAllocator;
	result = kg_create_linear_allocator(&errorAllocator, pMemory, errorStackSizeInBytes);
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	pOutErrorStack->errorAllocator 	= errorAllocator;
	pOutErrorStack->pFirstError 	= kg_nullptr;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_rect kg_create_rect(kg_f32 x, kg_f32 y, kg_f32 w, kg_f32 h)
{
	kg_rect rect;
	rect.position 	= kg_create_float2(x, y);
	rect.size 		= kg_create_float2(w, h);

	return rect;
}

kg_internal kg_float4 kg_unpack_color(kg_color32 color)
{
	const kg_f32 r = (kg_f32)((color >> 24) & 0xFF) / 255.f;
	const kg_f32 g = (kg_f32)((color >> 16) & 0xFF) / 255.f;
	const kg_f32 b = (kg_f32)((color >>  8) & 0xFF) / 255.f;
	const kg_f32 a = (kg_f32)((color >>  0) & 0xFF) / 255.f;

	return kg_create_float4(r, g, b, a);
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

kg_internal kg_bool kg_element_has_component(kg_element* pElement, kg_component_type componentType)
{
	return kg_false;
	//return pElement->componentHandles[componentType] != kg_nullptr;
}

kg_internal kg_element* kg_allocate_element(kg_context* pContext, const char* pIdentifier)
{
	#if 1
	return kg_nullptr;
	#else
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
		pElement->padding			= kg_float2_zero();
		pElement->margin			= kg_float2_zero();
		pElement->border			= kg_float2_zero();
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
	#endif

}

kg_internal void kg_process_mouse_movement(kg_context* pContext, const kg_input_event* pInputEvent)
{
	kg_input_system* pInputSystem = &pContext->inputSystem;

	const kg_window* pHotWindow 	= kg_nullptr;
	const kg_window* pWindow 		= pContext->pFirstWindow;
	const kg_float2 mousePosition 	= kg_create_float2((kg_f32)pInputEvent->data.mouse_move.x, (kg_f32)pInputEvent->data.mouse_move.y);
	
	while( pWindow )
	{
		if (mousePosition.x > pWindow->position.x && mousePosition.x < pWindow->position.x + pWindow->size.x && mousePosition.y > pWindow->position.y && mousePosition.y < pWindow->position.y + pWindow->size.y)
		{
			pHotWindow = pWindow;
		}

		pWindow = (const kg_window*)pWindow->pNext;
	}
}

kg_internal void kg_process_keyboard_input(kg_context* pContext, const kg_input_event* pInputEvent)
{
	
}

kg_internal void kg_process_gamepad_input(kg_context* pContext, const kg_input_event* pInputEvent)
{
	
}

kg_internal void kg_process_input_events(kg_context* pContext)
{
	kg_input_system* pInputSystem = &pContext->inputSystem;
	const kg_input_event* pInputEvent = pInputSystem->pFirstEvent;

	while (pInputEvent != kg_nullptr)
	{
		switch(pInputEvent->type)
		{
			case K15_GUI_INPUT_TYPE_MOUSE_MOVE:
				kg_process_mouse_movement(pContext, pInputEvent);
				break;

			default:
				break;
		}
		pInputEvent = (const kg_input_event*)pInputEvent->pNext;
	}

	pInputSystem->pFirstEvent = kg_nullptr;
	kg_reset_linear_allocator(&pInputSystem->allocator, 0u);
}

kg_internal kg_float2 kg_calculate_element_layout_start_position(kg_element* pElement)
{
	kg_float2 position = pElement->position;

	//position.x += pElement->padding.x;
	//position.y += pElement->padding.y;

	return position;
}

kg_internal kg_layout_state kg_create_layout_state(kg_element* pElement)
{
	//FK: Calculate position from where to start layouting.
	kg_float2 layoutPosition = pElement->position;
	//layoutPosition.x += pElement->padding.x;
	//layoutPosition.y += pElement->padding.y;

	kg_float2 layoutSize = pElement->size;
	//layoutSize.x -= (pElement->padding.x + pElement->padding.z);
	//layoutSize.y -= (pElement->padding.y + pElement->padding.w);

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
	//position.x += pElement->margin.x;
	//position.y += pElement->margin.y;

	return position;
}

kg_internal kg_float2 kg_calculate_element_size_with_margin(kg_element* pElement)
{
	kg_float2 size = pElement->size;
	//size.x += (pElement->margin.x + pElement->margin.z);
	//size.y += (pElement->margin.y + pElement->margin.w);

	return size;
}

kg_internal void kg_advance_layout_vertical(kg_layout_state* pLayoutState, kg_element* pElement)
{
	pElement->position = kg_calculate_element_position(pLayoutState, pElement);

	const kg_float2 elementSize = kg_calculate_element_size_with_margin(pElement);
	pLayoutState->maxSize = kg_float2_max(pLayoutState->maxSize, elementSize);

	if (pLayoutState->accumulatedSize.y + elementSize.y > pLayoutState->maxSize.y)
	{
		pLayoutState->position.x += pLayoutState->maxSize.x;
		pLayoutState->position.y = pLayoutState->origin.y;
	}

	if (kg_float2_gt(elementSize, pLayoutState->maxSize))
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
	#if 0
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
	#endif
}

kg_internal void kg_advance_layout_horizontal(kg_layout_state* pLayoutState, kg_element* pElement)
{
	pElement->position = kg_calculate_element_position(pLayoutState, pElement);

	const kg_float2 elementSize = kg_calculate_element_size_with_margin(pElement);
	pLayoutState->maxSize = kg_float2_max(pLayoutState->maxSize, elementSize);

	if (pLayoutState->accumulatedSize.x + elementSize.x > pLayoutState->maxSize.x)
	{
		pLayoutState->position.y += pLayoutState->maxSize.y;
		pLayoutState->position.x = pLayoutState->origin.x;
	}

	if (kg_float2_gt(elementSize, pLayoutState->maxSize))
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
	#if 0
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
	#endif
}

kg_internal void kg_layout_pass(kg_element* pElement)
{
#if 0
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
#endif
}

kg_internal void kg_render_element(kg_context* pContext, kg_element* pElement)
{	
	#if 0
	for (kg_u32 childIndex = 0u; childIndex < pElement->childArray.size; ++childIndex)
	{
		kg_element* pChild = kg_nullptr;
		kg_array_get_element(&pChild, &pElement->childArray, childIndex);

		kg_render_element(pContext, pChild);
	}
	#endif

}

kg_internal void kg_render_pass(kg_context* pContext)
{
}

kg_internal void kg_push_error_va(kg_context* pContext, kg_result errorResult, const char* pFormat, va_list vaList)
{
	if (pContext == kg_nullptr)
	{
		return;
	}

	kg_error_stack* pErrorStack = &pContext->errorStack;
	kg_error* pError = kg_nullptr;

	kg_result result = kg_allocate_from_linear_allocator(&pError, &pErrorStack->errorAllocator, sizeof(kg_error));
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return;
	}

	char* pBuffer = kg_nullptr;
	result = kg_allocate_from_linear_allocator(&pBuffer, pContext->pAllocator, 256u);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return;
	}

	va_start(vaList, pFormat);
	kg_format_string(pBuffer, 256u, pFormat, vaList);
	va_end(vaList);

	pError->pDescription 	= pBuffer;
	pError->result			= errorResult;

	if (pErrorStack->pFirstError == kg_nullptr)
	{
		pErrorStack->pFirstError 	= pError;
		pError->pNext				= kg_nullptr;
	}
	else
	{
		pError->pNext = pErrorStack->pFirstError;
		pErrorStack->pFirstError = pError;
	}
}

kg_internal void kg_push_error(kg_context* pContext, kg_result errorResult, const char* pDescription, ...)
{
	va_list list;
	va_start(list, pDescription);

	kg_push_error_va(pContext, errorResult, pDescription, list);

	va_end(list);
}

/******************************RENDER LOGIC***************************************/
kg_internal void kg_set_vertex_3d(kg_render_vertices* pVertices, kg_u32 vertexIndex, kg_f32 x, kg_f32 y, kg_f32 z, kg_f32 w, kg_f32 u, kg_f32 v, kg_color32 color)
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
	pVertexData->color 		= kg_unpack_color(color);
}

kg_internal void kg_set_vertex_2d(kg_render_vertices* pVertices, kg_u32 vertexIndex, kg_f32 x, kg_f32 y, kg_f32 u, kg_f32 v, kg_color32 color)
{
	kg_set_vertex_3d(pVertices, vertexIndex, x, y, 0.f, 1.f, u, v, color);
}

#if 0
kg_internal void kg_add_render_geometry(kg_context* pContext, kg_render_vertices* pVertices)
{
	
}
#endif

kg_internal kg_result kg_allocate_vertices(kg_render_vertices* pOutVertices, kg_linear_allocator* pAllocator, kg_u32 vertexCount)
{
	kg_assert(pOutVertices != kg_nullptr);
	kg_assert(pAllocator != kg_nullptr);
	kg_assert(vertexCount > 0u);

	kg_render_vertices renderVertices;

	const size_t vertexDataSizeInBytes = sizeof(kg_render_vertex_data) * vertexCount; 
	kg_result result = kg_allocate_from_linear_allocator(&renderVertices.pVertexData, pAllocator, vertexDataSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	renderVertices.vertexCount = vertexCount;
	*pOutVertices = renderVertices;

	return K15_GUI_RESULT_SUCCESS;
}

kg_internal kg_result kg_render_element_rect(kg_context* pContext, kg_rect rect, kg_color32 color)
{
	kg_assert(pContext != kg_nullptr);

	kg_render_vertices vertices;
	const kg_result result = kg_allocate_vertices(&vertices, pContext->renderContext.pVertexAllocator, 6u);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	kg_set_vertex_2d(&vertices, 0, rect.position.x, 				rect.position.y + rect.size.y, 	0.f, 0.f, color);	
	kg_set_vertex_2d(&vertices, 1, rect.position.x + rect.size.x, 	rect.position.y + rect.size.y, 	0.f, 0.f, color);	
	kg_set_vertex_2d(&vertices, 2, rect.position.x, 				rect.position.y , 				0.f, 0.f, color);	
	kg_set_vertex_2d(&vertices, 3, rect.position.x, 				rect.position.y , 				0.f, 0.f, color);	
	kg_set_vertex_2d(&vertices, 4, rect.position.x + rect.size.x, 	rect.position.y + rect.size.y, 	0.f, 0.f, color);	
	kg_set_vertex_2d(&vertices, 5, rect.position.x + rect.size.x, 	rect.position.y, 				0.f, 0.f, color);	

	return K15_GUI_RESULT_SUCCESS;
}
/*********************************************************************************/
kg_internal kg_result kg_render_element_text(kg_context* pContext, kg_rect textRect, const kg_utf8* pText, kg_color32 color)
{
	kg_code_point codePoint;
	kg_glyph_cache_entry* pGlyph = kg_nullptr;

	const kg_u32 textSize = kg_get_text_length(pText);
	const kg_u32 vertexCount = textSize * 6u;

	kg_render_vertices vertices;
	const kg_result result = kg_allocate_vertices(&vertices, pContext->renderContext.pVertexAllocator, vertexCount);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	};

	kg_float4 uvBounds  = kg_float4_zero();
	kg_float2 size 		= kg_float2_zero();
	kg_float2 position  = textRect.position;
	kg_f32 advance 		= 0.f;

	pText = "gG";

	while (*pText != 0)
	{
		const kg_u32  offset = kg_read_code_point(pText, &codePoint);
		pGlyph = kg_find_glyph(&pContext->glyphCache, codePoint);

		if (!pGlyph)
		{
			pGlyph = kg_push_glyph(&pContext->glyphCache);

			if (pGlyph == kg_nullptr)
			{
				kg_evict_least_used_glyph(&pContext->glyphCache);
				pGlyph = kg_push_glyph(&pContext->glyphCache);
			}

			kg_glyph_id glyphId = 0u;
			kg_result result = kg_parse_true_type_code_point_glyph_id(&pContext->trueTypeFont, &glyphId, codePoint); 
			//FK: consider result

			kg_linear_allocator* pAllocator = kg_get_frame_allocator_from_current_frame(pContext);
			const size_t allocatorPosition = kg_get_linear_allocator_position(pAllocator);
		
			//result = kg_rasterize_true_type_glyph(pAllocator, pGlyph, &pContext->glyphCache.atlas, &pContext->trueTypeFont, glyphId, 24.f);
		
			kg_reset_linear_allocator(pAllocator, allocatorPosition);

			//FK: consider result
		}

		pGlyph->lastUsedFrameIndex = pContext->frameCounter;

		uvBounds 	= kg_uint4_to_float4_cast(pGlyph->pAtlasSlot->uvBounds);
		size 		= kg_uint2_to_float2_cast(pGlyph->pAtlasSlot->size);
		advance 	= 0.0f;//pGlyph->metrics.advanceWidth;

		kg_set_vertex_2d(&vertices, 0, position.x, 				position.y + size.y, uvBounds.x, uvBounds.w, color);	
		kg_set_vertex_2d(&vertices, 1, position.x + size.x, 	position.y + size.y, uvBounds.z, uvBounds.w, color);	
		kg_set_vertex_2d(&vertices, 2, position.x, 				position.y, 		 uvBounds.x, uvBounds.y, color);	
		kg_set_vertex_2d(&vertices, 3, position.x, 				position.y, 		 uvBounds.x, uvBounds.y, color);	
		kg_set_vertex_2d(&vertices, 4, position.x + size.x, 	position.y + size.y, uvBounds.z, uvBounds.w, color);	
		kg_set_vertex_2d(&vertices, 5, position.x + size.x, 	position.y, 		 uvBounds.z, uvBounds.y, color);	

		position.x += advance;
		
		pText += offset;
	}

	return K15_GUI_RESULT_NOT_SUPPORTED;	
}
/******************************INPUT LOGIC****************************************/
kg_internal kg_input_event* kg_allocate_input_event(kg_input_system* pInputSystem, kg_input_type inputType)
{
	kg_input_event* pInputEvent = kg_nullptr;
	kg_result result = kg_allocate_from_linear_allocator(&pInputEvent, &pInputSystem->allocator, sizeof(kg_input_event));

	if(result != K15_GUI_RESULT_SUCCESS)
	{
		return kg_nullptr;
	}

	pInputEvent->pNext 	= kg_nullptr;
	pInputEvent->type	= inputType;

	if (pInputSystem->pFirstEvent == kg_nullptr)
	{
		pInputSystem->pFirstEvent = pInputEvent;
	}
	else
	{
		pInputEvent->pNext = pInputSystem->pFirstEvent;
		pInputSystem->pFirstEvent = pInputEvent;
	}

	return pInputEvent;
}
/*****************************RESOURCE LOGIC**************************************/
kg_internal const kg_utf8* kg_find_text(kg_context* pContext, const char* pTextID)
{
	return pTextID;
}
/*****************************CONTROL LOGIC***************************************/
kg_internal kg_bool kg_window_logic(kg_context* pContext, kg_window* pWindow)
{
	if ( ( pWindow->flags & K15_GUI_WINDOW_FLAG_CLOSE_BUTTON_CLICKED ) != 0 )
	{
		pWindow->flags &= ~K15_GUI_WINDOW_FLAG_IS_OPEN;
		pWindow->flags &= ~K15_GUI_WINDOW_FLAG_CLOSE_BUTTON_CLICKED;
	}

	if ( ( pWindow->flags & K15_GUI_WINDOW_FLAG_IS_OPEN ) == 0 )
	{
		return kg_false;
	}

	if ( ( pWindow->flags & K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED ) != 0 )
	{
		if ( ( pWindow->flags & K15_GUI_WINDOW_FLAG_IS_MAXIMIZED ) == 0 )
		{
			pWindow->flags |= K15_GUI_WINDOW_FLAG_IS_MAXIMIZED;	
			pWindow->flags &= ~K15_GUI_WINDOW_FLAG_IS_MINIMIZED;
		}
		else
		{
			pWindow->flags &= ~K15_GUI_WINDOW_FLAG_IS_MAXIMIZED;
		}

		pWindow->flags &= ~K15_GUI_WINDOW_FLAG_MAXIMIZE_BUTTON_CLICKED;
	}

	if ( ( pWindow->flags & K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED ) != 0 )
	{
		if ( ( pWindow->flags & K15_GUI_WINDOW_FLAG_IS_MINIMIZED ) == 0)
		{
			pWindow->flags |= K15_GUI_WINDOW_FLAG_IS_MINIMIZED;	
		}
		else
		{
			pWindow->flags &= ~K15_GUI_WINDOW_FLAG_IS_MINIMIZED;	
		}

		pWindow->flags &= ~K15_GUI_WINDOW_FLAG_MINIMIZE_BUTTON_CLICKED;
	}

	return (pWindow->flags & K15_GUI_WINDOW_FLAG_IS_OPEN);
}

kg_internal kg_element* kg_insert_ui_element(kg_hash_map* pHashMap, kg_crc32 identifier)
{
	kg_bool isNew = kg_false;
	kg_element* pElement = kg_insert_hash_element(pHashMap, identifier, &isNew);

	if (isNew == kg_true)
	{
		pElement->size			= kg_float2_zero();
		//pElement->maxSize		= kg_float2_zero();
		//pElement->minSize		= kg_float2_zero();
		//pElement->prefSize		= kg_float2_zero();
		pElement->position		= kg_float2_zero();
		//pElement->offset		= kg_float2_zero();
		//pElement->border		= kg_float2_zero();
		//pElement->margin		= kg_float2_zero();
		//pElement->padding		= kg_float2_zero();
		pElement->layout		= K15_GUI_LAYOUT_VERTICAL;
		pElement->identifier	= identifier;

		//for (kg_u32 componentIndex = 0u; componentIndex < K15_GUI_COMPONENT_COUNT; ++componentIndex)
		//{
		//	pElement->componentHandles[componentIndex] = kg_nullptr;
		//}
	}

	return pElement;
}

kg_internal void kg_push_window(kg_context* pContext, kg_window* pWindow)
{
	pWindow->pNext = pContext->pFirstWindow;
	pContext->pFirstWindow = pWindow;
}

kg_internal void kg_reset_context_state(kg_context* pContext)
{
	pContext->pFirstWindow 		= kg_nullptr;
	pContext->windowZIndex 		= 0u;
	
	kg_reset_linear_allocator(pContext->pAllocator, pContext->allocatorFrameDataPosition);
}

kg_internal kg_buffer kg_invalid_buffer()
{
	return kg_create_buffer(kg_nullptr, 0u);
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
//							Only need JPE G, PNG and maybe TIFF support).
//  12. provide more style options other  than just different colors.
//		Imagesets and icons come to mind.


/*********************************************************************************/
kg_context_parameter kg_create_context_parameter()
{ 
	kg_context_parameter parameter;

	parameter.scratchBuffer.pMemory 			= kg_nullptr;
	parameter.scratchBuffer.memorySizeInBytes 	= 0u;
	parameter.pFontName = kg_nullptr;
	parameter.fontData 	= kg_invalid_buffer();
	return parameter;	
}
/*********************************************************************************/
kg_render_context_parameter kg_create_render_context_parameter()
{
	kg_render_context_parameter parameter;

	parameter.vertexBufferCount = 0u;
	parameter.indexBufferCount = 0u;

	return parameter;
}
/*********************************************************************************/
kg_result kg_create_context(kg_context_handle* pOutHandle)
{
	const kg_context_parameter* pParameter = kg_get_default_context_parameter();
	const kg_render_context_parameter* pRenderParameter = kg_get_default_render_context_parameter();
	return kg_create_context_with_custom_parameter( pOutHandle, pParameter, pRenderParameter, kg_nullptr);
}
/*********************************************************************************/
kg_result kg_create_context_with_custom_parameter(kg_context_handle* pOutHandle, const kg_context_parameter* pParameter, const kg_render_context_parameter* pRenderParameter, const char** pOutError)
{
	if (pOutHandle == kg_nullptr)
	{
		kg_set_str(pOutError, "argument 'pOutHandle' is NULL.");
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pParameter == kg_nullptr)
	{
		kg_set_str(pOutError, "argument 'pParameter' is NULL.");
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (pRenderParameter == kg_nullptr)
	{
		kg_set_str(pOutError, "argument 'pRenderParameter' is NULL.");
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	if (kg_is_invalid_context_parameter(pParameter))
	{
		return K15_GUI_RESULT_INVALID_CONTEXT_PARAMETER;
	}

	if (pParameter->scratchBuffer.memorySizeInBytes < MinContextDataSize)
	{
		return K15_GUI_RESULT_NEED_MORE_MEMORY;
	}

	if (kg_is_invalid_render_context_parameter(pRenderParameter))
	{
		return K15_GUI_RESULT_INVALID_RENDER_CONTEXT_PARAMETER;
	}

	kg_linear_allocator allocator;
	kg_result result = kg_create_linear_allocator(&allocator, pParameter->scratchBuffer.pMemory, pParameter->scratchBuffer.memorySizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return K15_GUI_RESULT_INVALID_CONTEXT_PARAMETER;
	}

	kg_context* pContext = kg_nullptr;
	result = kg_allocate_from_linear_allocator(&pContext, &allocator, sizeof(kg_context));

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_error_stack(&pContext->errorStack, &allocator);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_input_system(&pContext->inputSystem, &allocator);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_render_context(&pContext->renderContext, pRenderParameter);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_init_true_type_font(&pContext->trueTypeFont, &pParameter->fontData, pParameter->pFontName);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		kg_set_str(pOutError, "Could not load provided font - will fall back to default font.");
		//FK: TODO: Load default font
		//result = kg_init_true_type_font(&pContext->trueTypeFont, defaultFontData, kg_nullptr);

		if (result != K15_GUI_RESULT_SUCCESS)
		{
			kg_set_str(pOutError, "Could not load default font.");
			return result;
		}
	}

	result = kg_create_glyph_cache(&pContext->glyphCache, &allocator, 64u, 512u);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_image_cache(&pContext->imageCache, &allocator, 256u);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	const size_t allocatorPosition = kg_get_linear_allocator_position(&allocator);

	const size_t remainingMemorySizeInBytes = (pParameter->scratchBuffer.memorySizeInBytes - allocatorPosition);
	const size_t sizePerFrameAllocator 		= remainingMemorySizeInBytes / 2u;

	result = kg_create_linear_allocator(&pContext->frameAllocators[0], (kg_u8*)pParameter->scratchBuffer.pMemory + allocatorPosition, sizePerFrameAllocator);
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_linear_allocator(&pContext->frameAllocators[1], (kg_u8*)pParameter->scratchBuffer.pMemory + allocatorPosition + sizePerFrameAllocator, sizePerFrameAllocator);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_hash_map(&pContext->elements[0], &pContext->frameAllocators[0], sizeof(kg_element));
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_hash_map(&pContext->elements[1], &pContext->frameAllocators[1], sizeof(kg_element));
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	result = kg_create_hash_map(&pContext->windows[0], &pContext->frameAllocators[0], sizeof(kg_window));
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}	

	result = kg_create_hash_map(&pContext->windows[1], &pContext->frameAllocators[1], sizeof(kg_window));
	
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return result;
	}

	pContext->fourCC[0] 		= 'K';
	pContext->fourCC[1] 		= 'G';
	pContext->fourCC[2] 		= 'U';
	pContext->fourCC[3] 		= 'I';
	pContext->frameCounter 		= 0u;
	pContext->windowZIndex 		= 0u;
	pContext->pAllocator 		= &pContext->frameAllocators[0];
	pContext->pElementHashMap 	= &pContext->elements[0];
	pContext->pWindowHashMap 	= &pContext->windows[0];
	pContext->pFirstWindow		= kg_nullptr;
	pContext->dpi 				= 96u;
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

	if ((pContext->flags & K15_GUI_CONTEXT_INSIDE_FRAME_FLAG) > 0)
	{
		kg_push_error(pContext, K15_GUI_RESULT_ELEMENT_NOT_FINISHED, "[frame] called kg_begin_frame without calling kg_end_frame first." );
		return K15_GUI_RESULT_ELEMENT_NOT_FINISHED;
	}

	kg_reset_context_state(pContext);
	kg_swap_render_buffers(&pContext->renderContext);

	pContext->flags |= K15_GUI_CONTEXT_INSIDE_FRAME_FLAG;

	return K15_GUI_RESULT_SUCCESS;
}

void kg_begin_toolbar(kg_context_handle contextHandle, const char* p_Identifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;

	if ((pContext->flags & K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG) > 0)
	{
		//kg_push_error()
	}

	pContext->flags |= K15_GUI_CONTEXT_INSIDE_TOOLBAR_FLAG;
}

kg_internal void* kg_allocate_element_component(kg_linear_allocator* pAllocator, kg_element* pElement, kg_u32 componentId, size_t componentSizeInBytes)
{
	kg_element_component_header* pHeader = kg_nullptr;
	kg_result result = kg_allocate_from_linear_allocator(&pHeader, pAllocator, sizeof(kg_element_component_header) + componentSizeInBytes);

	if (result != K15_GUI_RESULT_SUCCESS)
	{
		return kg_nullptr;
	}

	pHeader->sizeInBytes = componentSizeInBytes;
	pHeader->componentId = componentId;
	
	if (pElement->pFirstComponent != kg_nullptr)
	{
		pElement->pFirstComponent->pNext = pHeader;
	}

	pHeader->pNext = pElement->pFirstComponent;

	return (pHeader + 1u);
}

kg_internal void kg_copy_element(kg_linear_allocator* pAllocator, kg_element* pDestination, const kg_element* pSource)
{
	kg_memcpy(pDestination, pSource, sizeof(kg_element));
	pDestination->pFirstComponent = kg_nullptr;

	//FK: Copy components
	const kg_element_component_header* pSourceComponentHeader = pSource->pFirstComponent;
	while (pSourceComponentHeader)
	{	
		void* pComponent = kg_allocate_element_component(pAllocator, pDestination, pSourceComponentHeader->componentId, pSourceComponentHeader->sizeInBytes);
		kg_memcpy(pComponent, pSourceComponentHeader + 1, pSourceComponentHeader->sizeInBytes);
		pSourceComponentHeader = (kg_element_component_header*)pSourceComponentHeader->pNext;
	}
}

kg_internal kg_window* kg_insert_window(kg_context* pContext, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	const kg_hash_map* pWindowsLastFrame 	= kg_get_window_hash_map_from_last_frame(pContext);
	const kg_window* pWindowLastFrame 		= (const kg_window*)kg_find_hash_element(pWindowsLastFrame, identifier);
	kg_window* pWindow 						= (kg_window*)kg_insert_hash_element(pContext->pWindowHashMap, identifier, pOutIsNew);
	
	if (pWindowLastFrame != kg_nullptr)
	{
		*pOutIsNew = kg_false;
		kg_memcpy(pWindow, pWindowLastFrame, sizeof(kg_window));
	}

	return pWindow;
}

kg_internal kg_element* kg_insert_element(kg_context* pContext, kg_crc32 identifier, kg_bool* pOutIsNew)
{
	const kg_hash_map* pElementsLastFrame = kg_get_element_hash_map_from_last_frame(pContext);
	const kg_element* pElementLastFrame = (const kg_element*)kg_find_hash_element(pElementsLastFrame, identifier);
	kg_element* pElement 				= (kg_element*)kg_insert_hash_element(pContext->pElementHashMap, identifier, pOutIsNew);
	
	if (pElementLastFrame != kg_nullptr)
	{
		*pOutIsNew = kg_false;
		kg_copy_element(pContext->pAllocator, pElement, pElementLastFrame);
	}

	return pElement;
}

kg_bool kg_begin_window(kg_context_handle contextHandle, const char* pTextID, const char* pIdentifier)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return kg_false;
	}

	kg_context* pContext = (kg_context*)contextHandle.value;
	
	if ((pContext->flags & K15_GUI_CONTEXT_INSIDE_WINDOW_FLAG) > 0)
	{
		kg_push_error(pContext, K15_GUI_RESULT_ELEMENT_NOT_FINISHED, "[window] called kg_begin_frame without having called kg_end_frame first." );
		return kg_false;
	}

	const kg_crc32 identifier = kg_generate_crc32(pIdentifier);
	kg_bool isNew = kg_false;

	kg_window* pWindow = kg_insert_window(pContext, identifier, &isNew);

	if (isNew)
	{
		pWindow->position 	= kg_create_float2(10.f, 10.f);
		pWindow->size		= kg_create_float2(150.f, 150.f);
		pWindow->flags		= K15_GUI_WINDOW_FLAG_IS_OPEN;
	}

	pWindow->zOrder = pContext->windowZIndex++;
	pWindow->pTitle = kg_find_text(pContext, pTextID);
	kg_push_window(pContext, pWindow);

	return kg_window_logic(pContext, pWindow);
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
	const kg_window* pWindow = pContext->pFirstWindow;

	if (pWindow == kg_nullptr)
	{
		kg_push_error(pContext, K15_GUI_RESULT_ELEMENT_NOT_STARTED, "[window] called kg_end_window without calling kg_begin_window first." );
		return;
	}

	const kg_float2 titleArea 	= kg_create_float2(pWindow->size.x, K15_GUI_WINDOW_TITLE_HEIGHT_IN_PIXELS);
	const kg_rect titleRect 	= kg_create_rect(pWindow->position.x, pWindow->position.y, titleArea.x, titleArea.y);

	kg_result result = K15_GUI_RESULT_SUCCESS;

	result |= kg_render_element_rect(pContext, titleRect, K15_GUI_COLOR_WHITE);

	if ( ( pWindow->flags & K15_GUI_WINDOW_FLAG_IS_OPEN ) == 0 )
	{
		goto kg_end_window_end;
	}

	const kg_float2 windowArea 	= kg_create_float2(pWindow->size.x, kg_max(pWindow->size.y - K15_GUI_WINDOW_TITLE_HEIGHT_IN_PIXELS, K15_GUI_WINDOW_MIN_AREA_HEIGHT_IN_PIXELS)); 
	const kg_rect windowRect	= kg_create_rect(pWindow->position.x, pWindow->position.y + K15_GUI_WINDOW_TITLE_HEIGHT_IN_PIXELS, windowArea.x, windowArea.y);

	result |= kg_render_element_rect(pContext, windowRect, K15_GUI_COLOR_DARK_GREEN);
	result |= kg_render_element_text(pContext, titleRect, pWindow->pTitle, K15_GUI_COLOR_WHITE);

kg_end_window_end:
	if (result != K15_GUI_RESULT_SUCCESS)
	{
		kg_push_error(pContext, result, "[kg_end_window] could not render window." );
	}
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
	
	if ((pContext->flags & K15_GUI_CONTEXT_INSIDE_FRAME_FLAG) == 0)
	{
		kg_push_error(pContext, K15_GUI_RESULT_ELEMENT_NOT_STARTED, "[frame] called kg_end_frame without calling kg_begin_frame first." );
		return K15_GUI_RESULT_ELEMENT_NOT_STARTED;
	}

	kg_process_input_events(pContext);
	//kg_layout_pass(pContext->pRootElement);
	kg_render_pass(pContext);
	++pContext->frameCounter;

	kg_linear_allocator* pAllocator = kg_get_frame_allocator_from_current_frame(pContext);
	kg_hash_map* pWindowHashMap 	= kg_get_window_hash_map_from_current_frame(pContext);
	kg_hash_map* pElementHashMap	= kg_get_element_hash_map_from_current_frame(pContext);
	kg_reset_linear_allocator(pAllocator, 0u);
	kg_reset_hash_map(pWindowHashMap);

	pContext->pAllocator 		= pAllocator;
	pContext->pElementHashMap 	= pElementHashMap;
	pContext->pWindowHashMap 	= pWindowHashMap;
	pContext->flags				&= ~K15_GUI_CONTEXT_INSIDE_FRAME_FLAG;


	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_add_input_mouse_move(kg_context_handle contextHandle, unsigned short x, unsigned short y)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_input_system* pInputSystem = &pContext->inputSystem;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputSystem, K15_GUI_INPUT_TYPE_MOUSE_MOVE);
	
	if (pInputEvent == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.mouse_move.x = x;
	pInputEvent->data.mouse_move.y = y;
	pInputEvent->data.mouse_move.deltaX = pInputEvent->data.mouse_move.x - y;
	pInputEvent->data.mouse_move.deltaY = pInputEvent->data.mouse_move.y - y;

	return K15_GUI_RESULT_SUCCESS;
}

kg_result kg_add_input_mouse_button_down(kg_context_handle contextHandle, unsigned short x, unsigned short y, kg_mouse_button_type mouseButtonType)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS;
	}

	kg_context* 	pContext 	= (kg_context*)contextHandle.value;
	kg_input_system* pInputSystem = &pContext->inputSystem;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputSystem, K15_GUI_INPUT_TYPE_MOUSE_BUTTON_PRESSED);
	
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
	kg_input_system* pInputSystem = &pContext->inputSystem;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputSystem, K15_GUI_INPUT_TYPE_MOUSE_BUTTON_RELEASED);
	
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
	kg_input_system* pInputSystem = &pContext->inputSystem;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputSystem, K15_GUI_INPUT_TYPE_KEY_PRESSED);
	
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
	kg_input_system* pInputSystem = &pContext->inputSystem;

	kg_input_event* pInputEvent = kg_allocate_input_event(pInputSystem, K15_GUI_INPUT_TYPE_KEY_RELEASED);
	
	if (pInputEvent == kg_nullptr)
	{
		return K15_GUI_RESULT_OUT_OF_MEMORY;
	}

	pInputEvent->data.keyboard_button.key = buttonType;

	return K15_GUI_RESULT_SUCCESS;
}

const char* kg_result_to_string(kg_result result)
{
	switch(result)
	{
		case K15_GUI_RESULT_SUCCESS:
			return "success";

		case K15_GUI_RESULT_OUT_OF_MEMORY:
			return "out of memory";

		case K15_GUI_RESULT_INVALID_ARGUMENTS:
			return "invalid arguments";

		case K15_GUI_RESULT_INVALID_CONTEXT_PARAMETER:
			return "invalid context parameter";

		case K15_GUI_RESULT_INVALID_RENDER_CONTEXT_PARAMETER:
			return "invalid render context parameter";
	}

	return "";
}

void kg_calculate_column_major_projection_matrix(kg_f32* pMatrix, int screenWidth, int screenHeight, unsigned int flags)
{
	// m0  m1  m2  m3
	// m4  m5  m6  m7
	// m8  m9  m10 m11
	// m12 m13 m14 m15

	// x x x x
	// y y y y
	// z z z z
	// w w w w

	const kg_f32 w = 1.f / (kg_f32)screenWidth;
	const kg_f32 h = 1.f / (kg_f32)screenHeight;

	pMatrix[ 0] = (2.f * w);
	pMatrix[ 1] = 0.f;
	pMatrix[ 2] = 0.f;
	pMatrix[ 3] = 0.f;
	pMatrix[ 4] = 0.f;
	pMatrix[ 5] = (2.f * h);
	pMatrix[ 6] = 0.f;
	pMatrix[ 7] = 0.f;
	pMatrix[ 8] = 0.f;
	pMatrix[ 9] = 0.f;
	pMatrix[10] = 1.f;
	pMatrix[11] = 0.f;
	pMatrix[12] = -1.f;
	pMatrix[13] = -1.f;
	pMatrix[14] = 0.f;
	pMatrix[15] = 1.f;

	if ((flags & K15_GUI_MATRIX_INVERT_Y_AXIS_FLAG) > 0)
	{
		pMatrix[ 5] = -(2.f * h);
		pMatrix[13] = 1.f;
	}
}

void kg_calculate_row_major_projection_matrix(kg_f32* pMatrix, int screenWidth, int screenHeight, unsigned int flags)
{
	// m0  m1  m2  m3
	// m4  m5  m6  m7
	// m8  m9  m10 m11
	// m12 m13 m14 m15

	// x y z w
	// x y z w
	// x y z w
	// x y z w

	const kg_f32 w = 1.f / (kg_f32)screenWidth;
	const kg_f32 h = 1.f / (kg_f32)screenHeight;

	pMatrix[ 0] = (2.f * w);
	pMatrix[ 1] = 0.f;
	pMatrix[ 2] = 0.f;
	pMatrix[ 3] = -1.f;
	pMatrix[ 4] = 0.f;
	pMatrix[ 5] = (2.f * h);
	pMatrix[ 6] = 0.f;
	pMatrix[ 7] = -1.f;
	pMatrix[ 8] = 0.f;
	pMatrix[ 9] = 0.f;
	pMatrix[10] = 1.f;
	pMatrix[11] = 0.f;
	pMatrix[12] = 0.f;
	pMatrix[13] = 0.f;
	pMatrix[14] = 0.f;
	pMatrix[15] = 1.f;

	if ((flags & K15_GUI_MATRIX_INVERT_Y_AXIS_FLAG) > 0)
	{
		pMatrix[5] = -(2.f * h);
		pMatrix[7] = 1.f;
	}
}

kg_bool kg_pop_error(kg_context_handle contextHandle, kg_error** pOutError)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return kg_false;
	}

	kg_context* 	pContext 		= (kg_context*)contextHandle.value;
	kg_error_stack* pErrorStack 	= &pContext->errorStack;
	kg_error* 		pFirstError 	= pErrorStack->pFirstError;

	if (pFirstError == kg_nullptr)
	{
		return kg_false;
	}

	pErrorStack->pFirstError = pFirstError->pNext;
	*pOutError = pFirstError;

	return kg_true;
}

kg_buffer kg_create_buffer(void* pMemory, size_t memorySizeInBytes)
{
	kg_buffer buffer;
	buffer.memorySizeInBytes 	= memorySizeInBytes;
	buffer.pMemory				= pMemory;

	return buffer;
}

const kg_vertex_definition*	kg_get_vertex_definition()
{
	static kg_vertex_definition vertexDefinition;

	vertexDefinition.stride 					= VertexStride;
	vertexDefinition.attributeCount 			= sizeof(vertexDefinition.attributes) / sizeof(vertexDefinition.attributes[0]);
	vertexDefinition.attributes[0].type 		= K15_GUI_POSITION_ATTRIBUTE_TYPE;
	vertexDefinition.attributes[0].dataType 	= K15_GUI_FLOAT_DATA_TYPE;
	vertexDefinition.attributes[0].offset		= 0u;
	vertexDefinition.attributes[0].sizeInBytes 	= sizeof(kg_float2);
	vertexDefinition.attributes[0].size 		= 4;

	vertexDefinition.attributes[1].type 		= K15_GUI_COLOR_ATTRIBUTE_TYPE;
	vertexDefinition.attributes[1].dataType 	= K15_GUI_FLOAT_DATA_TYPE;
	vertexDefinition.attributes[1].offset		= sizeof(kg_float2);
	vertexDefinition.attributes[1].sizeInBytes 	= sizeof(kg_float2);
	vertexDefinition.attributes[1].size 		= 4;

	vertexDefinition.attributes[2].type 		= K15_GUI_TEXCOORD_ATTRIBUTE_TYPE;
	vertexDefinition.attributes[2].dataType 	= K15_GUI_FLOAT_DATA_TYPE;
	vertexDefinition.attributes[2].offset		= sizeof(kg_float2) * 2u;
	vertexDefinition.attributes[2].sizeInBytes 	= sizeof(kg_float2);
	vertexDefinition.attributes[2].size 		= 2;
	
	return &vertexDefinition;
}

kg_result kg_get_render_data(kg_context_handle contextHandle, kg_render_data* pOutRenderData)
{
	if (kg_is_invalid_context_handle(contextHandle))
	{
		return K15_GUI_RESULT_INVALID_ARGUMENTS; 
	}

	kg_context* pContext = (kg_context*)contextHandle.value;

	pOutRenderData->pVertexData 			= pContext->renderContext.pVertexAllocator->pMemory;
	pOutRenderData->vertexDataSizeInBytes 	= pContext->renderContext.pVertexAllocator->allocPosition;
	pOutRenderData->vertexCount				= pOutRenderData->vertexDataSizeInBytes / sizeof(kg_render_vertex_data);
	pOutRenderData->pIndexData				= pContext->renderContext.pIndexAllocator->pMemory;
	pOutRenderData->indexDataSizeInBytes	= pContext->renderContext.pIndexAllocator->allocPosition;
	pOutRenderData->indexDataType			= pContext->renderContext.indexDataType;
	pOutRenderData->indexCount 				= pOutRenderData->indexDataSizeInBytes / kg_get_index_data_type_size_in_bytes(pContext->renderContext.indexDataType);

	return K15_GUI_RESULT_SUCCESS;
}


#endif //K15_GUI_IMPLEMENTATION
#endif //_K15_GUILayer_Context_h_
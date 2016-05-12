#ifndef _K15_ImageAtlas_h_
#define _K15_ImageAtlas_h_

typedef unsigned int kia_u32;
typedef unsigned char kia_u8;
typedef unsigned char kia_b8;
typedef unsigned char kia_byte;

typedef enum _K15_IAInsertMethod
{
	KIA_INSERT_LARGEST_TO_SMALLEST = 1,	//KIA_INSERT_METHOD_1_FLAG
	KIA_INSERT_RANDOM_SIZES				//KIA_INSERT_METHOD_2_FLAG
} K15_IAInsertMethod;

enum _K15_IAAtlasFlags
{
	KIA_EXTERNAL_MEMORY_FLAG	= 0x01,
	KIA_INSERT_METHOD_LTS_FLAG = 0x02,	//KIA_INSERT_LARGEST_TO_SMALLEST
	KIA_INSERT_METHOD_RND_FLAG = 0x03	//KIA_INSERT_RANDOM_SIZES
};

enum _K15_IANodeFlags
{
	KIA_ADDED_TO_ATLAS_FLAG = 0x01,
	KIA_ROOT_NODE_FLAG		= 0x02
};

typedef enum _K15_IAPixelFormat
{
	KIA_PIXEL_FORMAT_R8			= 1,
	KIA_PIXEL_FORMAT_R8A8		= 2,
	KIA_PIXEL_FORMAT_R8G8B8		= 3,
	KIA_PIXEL_FORMAT_R8G8B8A8	= 4
} K15_IAPixelFormat;

typedef enum _K15_AtlasResults
{
	K15_IA_RESULT_SUCCESS = 0,				//<! Everything went fine
	K15_IA_RESULT_OUT_OF_MEMORY = 1,		//<! Out of memory
	K15_IA_RESULT_OUT_OF_RANGE = 2,			//<! Out of range (passed wrong index)
	K15_IA_RESULT_INVALID_ARGUMENTS = 3,	//<! Invalid arguments (nullptr, etc)
	K15_IA_RESULT_ATLAS_TOO_SMALL = 4,		//<! Only used internally
	K15_IA_RESULT_ATLAS_TOO_LARGE = 5		//<! The atlas has grown too large (Specfied by K15_TA_THRESHOLD)
											//	 note: There's an upper texture dimension limit to what you 
											//		   can upload to the GPU. 
											//		   K15_TA_THRESHOLD should be that upper limit value.
} kia_result;

typedef struct _K15_IAImageNode
{
	_K15_IAImageNode* right;
	_K15_IAImageNode* beneath;

	K15_IAPixelFormat pixelDataFormat;

	kia_u32 pixelPosX;
	kia_u32 pixelPosY;
	kia_u32 pixelWidth;
	kia_u32 pixelHeight;
	kia_byte* pixelData;
	kia_u8 flags;
} K15_IAImageNode;

typedef struct _K15_ImageAtlas
{
	K15_IAImageNode* imageNodes;
	kia_byte* pixelData;		//<! Pixel data of the atlas

	K15_IAInsertMethod insertMethod;
	K15_IAPixelFormat pixelFormat;

	kia_u32 maxPixelWidth;		//<! Width of the atlas in pixels
	kia_u32 maxPixelHeight;		//<! Height of the atlas in pixels

	kia_u32 virtualPixelWidth;
	kia_u32 virtualPixelHeight;
	
	kia_u32 numImageNodes;
	kia_u32 imageNodeIndex;
	kia_u8 flags;
} K15_ImageAtlas;


//Create a new atlas which is capable of storing pixel data where each pixel
//consists of exactly p_Components number of color components (max 4)
//Note: Returns on of the following results:
//			- K15_IA_RESULT_INVALID_ARGUMENTS (p_OutImageAtlas is NULL or p_Components is invalid)
//			- K15_IA_RESULT_SUCCESS
kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages, K15_IAInsertMethod p_InsertMethod = KIA_INSERT_RANDOM_SIZES);

kia_result K15_IACreateAtlasWithCustomMemory(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages, kia_u32 p_PixelWidth, kia_u32 p_PixelHeight, kia_byte* p_PixelDataMemory,
	K15_IAInsertMethod p_InsertMethod = KIA_INSERT_RANDOM_SIZES);

kia_u32 K15_IACalculateAtlasMemorySizeInBytes(kia_u32 p_NumImages, kia_u32 p_MaxPixelWidth,
	kia_u32 p_MaxPixelHeight, K15_IAPixelFormat p_PixelFormat);

//Free a previously created atlas (K15_IACreateAtlas). Deallocates all memory associated with 
//an image atlas.
void K15_IAFreeAtlas(K15_ImageAtlas* p_ImageAtlas);

//Add an image to a specific atlas. 
//Note: The image will be added immediately to the atlas, which could potentially mean
//		that the atlas has to resize itself if the image does not fit in the current atlas.
//		This in turn will trigger a memory allocation and deallocation.
//		
//		Also if the number of color components of the image mismatch with the number of color components
//		of the atlas (specified in K15_IACreateAtlas) the function will convert the image to match up with
//		the pixel format of the atlas.
kia_result K15_IAAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_byte* p_PixelData, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight,
	kia_u32* p_OutX, kia_u32* p_OutY);

#ifdef K15_IA_IMPLEMENTATION

#define K15_IA_TRUE 1
#define K15_IA_FALSE 0

#define K15_IA_ACCESS_MAP_FREE 0x00
#define K15_IA_ACCESS_MAP_OCCUPIED 0xFF
 
#ifndef K15_IA_DEFAULT_MAX_ATLAS_DIMENSION
# define K15_IA_DEFAULT_MAX_ATLAS_DIMENSION 2048
#endif //K15_IA_DEFAULT_MAX_ATLAS_DIMENSION

#ifndef K15_IA_DEFAULT_MIN_ATLAS_DIMENSION
# define K15_IA_DEFAULT_MIN_ATLAS_DIMENSION 16
#endif //K15_IA_DEFAULT_MIN_ATLAS_DIMENSION

#if K15_IA_DEFAULT_MIN_ATLAS_DIMENSION <= 8
# error "'K15_IA_DEFAULT_MIN_ATLAS_DIMENSION' needs to be at least 8"
#endif

#if K15_IA_DEFAULT_MAX_ATLAS_DIMENSION <= 0
# error "'K15_IA_DEFAULT_MAX_ATLAS_DIMENSION' can not be negative or zero"
#endif

#if K15_IA_DEFAULT_MIN_ATLAS_DIMENSION > K15_IA_DEFAULT_MAX_ATLAS_DIMENSION
# error "'K15_IA_DEFAULT_MIN_ATLAS_DIMENSION' is greater than 'K15_IA_DEFAULT_MAX_ATLAS_DIMENSION'"
#endif

#ifndef K15_IA_MALLOC
# include <stdlib.h>
# define K15_IA_MALLOC malloc
# define K15_IA_FREE free
#endif //K15_IA_MALLOC

#ifndef K15_IA_MEMCPY
# include <string.h>
# define K15_IA_MEMCPY memcpy
#endif //K15_IA_MEMCPY

#ifndef K15_IA_MEMSET
# include <string.h>
# define K15_IA_MEMSET memset
#endif //K15_IA_MEMSET

/*********************************************************************************/
static kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutTextureAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages, K15_IAInsertMethod p_InsertMethod)
{
	if (p_NumImages == 0)
		return K15_IA_RESULT_INVALID_ARGUMENTS;

	kia_u32 memoryBufferSizeInBytes = K15_IACalculateAtlasMemorySizeInBytes(p_NumImages, 
		K15_IA_DEFAULT_MAX_ATLAS_DIMENSION, K15_IA_DEFAULT_MAX_ATLAS_DIMENSION, 
		p_PixelFormat);

	kia_byte* memoryBuffer = (kia_byte*)K15_IA_MALLOC(memoryBufferSizeInBytes);

	if (!memoryBuffer)
		return K15_IA_RESULT_OUT_OF_MEMORY;

	kia_result result = K15_IACreateAtlasWithCustomMemory(p_OutTextureAtlas, p_PixelFormat,
		p_NumImages, K15_IA_DEFAULT_MAX_ATLAS_DIMENSION, K15_IA_DEFAULT_MAX_ATLAS_DIMENSION, 
		memoryBuffer, p_InsertMethod);

	if (result != K15_IA_RESULT_SUCCESS)
		K15_IA_FREE(memoryBuffer);
	else
		p_OutTextureAtlas->flags &= ~KIA_EXTERNAL_MEMORY_FLAG; //Reset 'KIA_EXTERNAL_MEMORY_FLAG' flag

	return result;
}
/*********************************************************************************/
kia_result K15_IACreateAtlasWithCustomMemory(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages, kia_u32 p_MaxPixelWidth, kia_u32 p_MaxPixelHeight, kia_byte* p_MemoryBuffer,
	K15_IAInsertMethod p_InsertMethod)
{
	if (!p_OutImageAtlas || p_NumImages == 0
		|| p_MaxPixelHeight < K15_IA_DEFAULT_MIN_ATLAS_DIMENSION 
		|| p_MaxPixelWidth < K15_IA_DEFAULT_MIN_ATLAS_DIMENSION 
		|| !p_MemoryBuffer)
	{
		return K15_IA_RESULT_INVALID_ARGUMENTS;
	}

	kia_u32 memoryBufferSizeInBytes = K15_IACalculateAtlasMemorySizeInBytes(p_NumImages, 
		p_MaxPixelWidth, p_MaxPixelHeight, p_PixelFormat);

	kia_u32 imageNodeMemoryBufferOffset = p_MaxPixelWidth * p_MaxPixelHeight * p_PixelFormat;
	
	//clear memory
	K15_IA_MEMSET(p_MemoryBuffer, 0, memoryBufferSizeInBytes);

	K15_ImageAtlas atlas = {};
	atlas.insertMethod = p_InsertMethod;
	atlas.virtualPixelHeight = K15_IA_DEFAULT_MIN_ATLAS_DIMENSION;
	atlas.virtualPixelWidth = K15_IA_DEFAULT_MIN_ATLAS_DIMENSION;
	atlas.maxPixelHeight = p_MaxPixelHeight;
	atlas.maxPixelWidth = p_MaxPixelWidth;
	atlas.pixelFormat = p_PixelFormat;
	atlas.pixelData = p_MemoryBuffer;
	atlas.numImageNodes = p_NumImages;
	atlas.imageNodeIndex = 0;
	atlas.imageNodes = (K15_IAImageNode*)(p_MemoryBuffer + imageNodeMemoryBufferOffset);
	atlas.flags = KIA_EXTERNAL_MEMORY_FLAG | 
		(p_InsertMethod == KIA_INSERT_LARGEST_TO_SMALLEST) ? 
		KIA_INSERT_METHOD_LTS_FLAG :
		KIA_INSERT_METHOD_RND_FLAG;

	*p_OutImageAtlas = atlas;

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
kia_u32 K15_IACalculateAtlasMemorySizeInBytes(kia_u32 p_NumImages, kia_u32 p_MaxPixelWidth,
	kia_u32 p_MaxPixelHeight, K15_IAPixelFormat p_PixelFormat)
{
	kia_u32 numPixels = p_MaxPixelHeight * p_MaxPixelWidth;
	kia_u32 pixelDataSizeInBytes = numPixels * p_PixelFormat;
	kia_u32 imageNodeDataSizeInBytes = p_NumImages * sizeof(K15_IAImageNode);

	return pixelDataSizeInBytes + imageNodeDataSizeInBytes;
}
/*********************************************************************************/
static void K15_IAFreeAtlas(K15_ImageAtlas* p_ImageAtlas)
{
	if (!p_ImageAtlas)
		return;

	if ((p_ImageAtlas->flags & KIA_EXTERNAL_MEMORY_FLAG) == 0)
		K15_IA_FREE(p_ImageAtlas->pixelData);
}
/*********************************************************************************/
kia_result K15_IAAddImageToAtlasLargestToSmallest_R(K15_IAImageNode* p_RootNode,
	K15_IAImageNode* p_NodeToInsert, kia_u32 p_VirtualWidth, kia_u32 p_VirtualHeight)
{
	kia_u32 nodeWidth = p_NodeToInsert->pixelWidth;
	kia_u32 nodeHeight = p_NodeToInsert->pixelHeight;

	kia_u32 rootNodeWidth = p_RootNode->pixelWidth;
	kia_u32 rootNodeHeight = p_RootNode->pixelHeight;
	kia_u32 rootNodePosX = p_RootNode->pixelPosX;
	kia_u32 rootNodePosY = p_RootNode->pixelPosY;

	kia_u32 spaceUntilRightBorder = p_VirtualWidth - (rootNodePosX + rootNodeWidth);
	kia_u32 spaceUntilLowerBorder = p_VirtualHeight - (rootNodePosY + rootNodeHeight);

	if (p_RootNode->right == 0 && nodeHeight < rootNodeHeight)
	{
		if (spaceUntilRightBorder < p_NodeToInsert->pixelWidth)
			return K15_IA_RESULT_ATLAS_TOO_SMALL;

		p_RootNode->right = p_NodeToInsert;
		p_NodeToInsert->pixelPosY = p_RootNode->pixelPosY;
		p_NodeToInsert->pixelPosX = p_RootNode->pixelPosX + p_RootNode->pixelWidth;
		return K15_IA_RESULT_SUCCESS;
	}

	if (p_RootNode->beneath == 0 && nodeWidth < rootNodeWidth)
	{
		if (spaceUntilLowerBorder < p_NodeToInsert->pixelHeight)
			return K15_IA_RESULT_ATLAS_TOO_SMALL;

		p_RootNode->beneath = p_NodeToInsert;
		p_NodeToInsert->pixelPosX = p_RootNode->pixelPosX;
		p_NodeToInsert->pixelPosY = p_RootNode->pixelPosY + p_RootNode->pixelHeight;
		return K15_IA_RESULT_SUCCESS;
	}

	kia_result result = K15_IA_RESULT_SUCCESS;
	if (p_RootNode->right)
	{
		//Insert Right Function
		result = K15_IAAddImageToAtlasLargestToSmallest_R(p_RootNode->right, p_NodeToInsert,
			p_VirtualWidth, p_VirtualHeight);

		if (result == K15_IA_RESULT_SUCCESS)
			return result;
	}

	if (p_RootNode->beneath)
	{
		//Insert Beneath Function
		result = K15_IAAddImageToAtlasLargestToSmallest_R(p_RootNode->beneath, p_NodeToInsert,
			p_VirtualWidth, p_VirtualHeight);

		if (result == K15_IA_RESULT_SUCCESS)
			return result;
	}

	return K15_IA_RESULT_OUT_OF_RANGE;
}
/*********************************************************************************/
kia_result K15_IATryToGroVirtualAtlasSize(K15_ImageAtlas* p_ImageAtlas)
{
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;
	kia_u32 maxWidth = p_ImageAtlas->maxPixelWidth;
	kia_u32 maxHeight = p_ImageAtlas->maxPixelHeight;

	if (virtualWidth > virtualHeight)
		virtualHeight = virtualHeight << 1;
	else
		virtualWidth = virtualWidth << 1;

	if (virtualWidth > maxWidth || virtualHeight > maxHeight)
		return K15_IA_RESULT_ATLAS_TOO_SMALL;

	p_ImageAtlas->virtualPixelWidth = virtualWidth;
	p_ImageAtlas->virtualPixelHeight = virtualHeight;

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
kia_result K15_IAAddImageToAtlasLargestToSmallest(K15_ImageAtlas* p_ImageAtlas, K15_IAImageNode* p_ImageNode, 
	kia_u32* p_OutX, kia_u32* p_OutY)
{
	kia_result result = K15_IA_RESULT_SUCCESS;
	kia_u32 numNodes = p_ImageAtlas->imageNodeIndex;
	K15_IAImageNode* nodes = p_ImageAtlas->imageNodes;
	
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;

	while (p_ImageNode->pixelWidth > virtualHeight ||
		p_ImageNode->pixelHeight > virtualWidth)
	{
		result = K15_IATryToGroVirtualAtlasSize(p_ImageAtlas);
		
		virtualWidth = p_ImageAtlas->virtualPixelWidth;
		virtualHeight = p_ImageAtlas->virtualPixelHeight;

		if (result == K15_IA_RESULT_ATLAS_TOO_SMALL)
			return result;
	}

	//if the first node has not the root flag, than p_ImageNode is the first node
	if ((nodes[0].flags & KIA_ROOT_NODE_FLAG) == 0)
	{
		p_ImageNode->flags |= KIA_ROOT_NODE_FLAG;
		return K15_IA_RESULT_SUCCESS;
	}

	while (result != K15_IA_RESULT_SUCCESS || result != K15_IA_RESULT_ATLAS_TOO_SMALL)
	{
		virtualWidth = p_ImageAtlas->virtualPixelWidth;
		virtualHeight = p_ImageAtlas->virtualPixelHeight;

		K15_IAImageNode* node = 0;

		for (kia_u32 nodeIndex = 0;
			nodeIndex < numNodes;
			++nodeIndex)
		{
			node = nodes + nodeIndex;

			if ((node->flags & KIA_ROOT_NODE_FLAG) > 0)
			{
				result = K15_IAAddImageToAtlasLargestToSmallest_R(node, p_ImageNode, virtualWidth, virtualHeight);

				if (result == K15_IA_RESULT_SUCCESS)
					return result;
			}
		}

		if (result != K15_IA_RESULT_SUCCESS)
			result = K15_IATryToGroVirtualAtlasSize(p_ImageAtlas);
	}
	
	return result;
}
/*********************************************************************************/
kia_result K15_IAAddImageToAtlasRandom(K15_ImageAtlas* p_ImageAtlas, K15_IAImageNode* p_ImageNode,
	kia_u32* p_OutX, kia_u32* p_OutY)
{
	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
kia_result K15_IAAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas, K15_IAPixelFormat p_PixelFormat, 
	kia_byte* p_PixelData, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight,
	kia_u32* p_OutX, kia_u32* p_OutY)
{
	if (!p_ImageAtlas || !p_PixelData || p_PixelDataWidth == 0 || p_PixelDataHeight == 0 ||
		!p_OutX || !p_OutY)
	{
		return K15_IA_RESULT_INVALID_ARGUMENTS;
	}

	if (p_ImageAtlas->imageNodeIndex == p_ImageAtlas->numImageNodes)
		return K15_IA_RESULT_OUT_OF_RANGE;

	kia_result result = K15_IA_RESULT_SUCCESS;

	kia_u32 imageNodeIndex = p_ImageAtlas->imageNodeIndex++;
	K15_IAImageNode* imageNode = p_ImageAtlas->imageNodes + imageNodeIndex;

	imageNode->pixelData = p_PixelData;
	imageNode->pixelDataFormat = p_PixelFormat;
	imageNode->pixelHeight = p_PixelDataHeight;
	imageNode->pixelWidth = p_PixelDataWidth;

	if (p_ImageAtlas->flags & KIA_INSERT_METHOD_LTS_FLAG)
		result = K15_IAAddImageToAtlasLargestToSmallest(p_ImageAtlas, imageNode, p_OutX, p_OutY);
	else if (p_ImageAtlas->flags & KIA_INSERT_METHOD_RND_FLAG)
		result = K15_IAAddImageToAtlasRandom(p_ImageAtlas, imageNode, p_OutX, p_OutY);

	return result;
}
/*********************************************************************************/
static kia_result K15_IAConvertPixelData(kia_byte* p_SourcePixelData, kia_u8 p_SourceNumColorComponents, 
	kia_u8 p_DestinationNumColorComponents, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight)
{
	if (!p_SourcePixelData || p_SourceNumColorComponents == 0 || p_SourceNumColorComponents > 4 ||
		p_DestinationNumColorComponents == 0 || p_DestinationNumColorComponents > 4 ||
		p_PixelDataHeight == 0 || p_PixelDataWidth == 0)
	{
		return K15_IA_RESULT_INVALID_ARGUMENTS;
	}

	kia_u32 numPixels = p_PixelDataWidth * p_PixelDataHeight;
	kia_u32 destinationPixelDataSizeInBytes = p_DestinationNumColorComponents * numPixels;
	kia_byte* destinationPixelData = (kia_byte*)K15_IA_MALLOC(destinationPixelDataSizeInBytes);

	if (!destinationPixelData)
		return K15_IA_RESULT_OUT_OF_MEMORY;

	//convert pixel by pixel
	for (kia_u32 pixelIndex = 0;
		pixelIndex < numPixels;
		++pixelIndex)
	{
		//TODO
	}

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
#endif //K15_IMAGE_ATLAS_IMPLEMENTATION
#endif //_K15_ImageAtlas_h_
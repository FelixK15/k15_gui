#ifndef _K15_ImageAtlas_h_
#define _K15_ImageAtlas_h_

//TODO:
// Pixel Data Conversion

typedef signed int kia_s32;
typedef unsigned int kia_u32;
typedef unsigned char kia_u8;
typedef unsigned char kia_b8;
typedef unsigned char kia_byte;

enum _K15_IAAtlasFlags
{
	KIA_EXTERNAL_MEMORY_FLAG = 0x01
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
	K15_IAPixelFormat pixelDataFormat;

	kia_u32 pixelPosX;
	kia_u32 pixelPosY;
	kia_u32 pixelWidth;
	kia_u32 pixelHeight;
	kia_byte* pixelData;
	kia_u8 flags;
} K15_IAImageNode;

typedef struct _K15_IASkyline
{
	kia_u32 baseLinePosX;
	kia_u32 baseLinePosY;
	kia_u32 baseLineWidth;
} K15_IASkyline;

typedef struct _K15_ImageAtlas
{
	K15_IASkyline* skylines;
	K15_IAImageNode* imageNodes;
	kia_byte* pixelData;		//<! Pixel data of the atlas

	K15_IAPixelFormat pixelFormat;

	kia_u32 maxPixelWidth;		//<! Width of the atlas in pixels
	kia_u32 maxPixelHeight;		//<! Height of the atlas in pixels

	kia_u32 virtualPixelWidth;
	kia_u32 virtualPixelHeight;
	
	kia_u32 numSkylines;
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
	kia_u32 p_NumImages);

kia_result K15_IACreateAtlasWithCustomMemory(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages, kia_u32 p_PixelWidth, kia_u32 p_PixelHeight, kia_byte* p_PixelDataMemory);

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

#define K15_IA_MAX_SKYLINES 40

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
kia_s32 K15_IARemoveObscuredSkylines(K15_IASkyline* p_Skylines, kia_u32 p_NumSkylines, K15_IASkyline* p_NewSkyline)
{
	K15_IASkyline* skyline = 0;
	kia_u32 newSkylineWidth = p_NewSkyline->baseLineWidth;
	kia_u32 newSkylinePosX = p_NewSkyline->baseLinePosX;
	kia_u32 newSkylinePosY = p_NewSkyline->baseLinePosY;
	kia_u32 skylineWidth = 0;
	kia_u32 skylinePosX = 0;
	kia_u32 skylinePosY = 0;
	kia_s32 deltaWidth = 0;
	kia_u32 removedSkylines = 0;

	for (kia_s32 skylineIndex = 0;
		skylineIndex < p_NumSkylines;
		++skylineIndex)
	{
		skyline = p_Skylines + skylineIndex;

		if (skyline != p_NewSkyline)
		{
			skylineWidth = skyline->baseLineWidth;
			skylinePosX = skyline->baseLinePosX;
			skylinePosY = skyline->baseLinePosY;

			if (skylinePosY < newSkylinePosY &&
				skylinePosX < newSkylinePosX + newSkylineWidth)
			{
				//trim or remove
				deltaWidth = (skylinePosX + skylineWidth) - (newSkylinePosX + newSkylineWidth);

				if (deltaWidth < 0)
				{
					//remove
					memmove(p_Skylines + skylineIndex, p_Skylines + skylineIndex + 1, p_NumSkylines - (skylineIndex - 1));

					--p_NumSkylines;
					--skylineIndex;
					++removedSkylines;
				}
				else
				{
					//trim
					skyline->baseLinePosX += deltaWidth;
					skyline->baseLineWidth -= deltaWidth;
				}
			}
		}
	}

	return removedSkylines;
}
/*********************************************************************************/
kia_result K15_IATryToInsertSkyline(K15_ImageAtlas* p_ImageAtlas, kia_u32 p_BaseLineY, kia_u32 p_BaseLineX, kia_u32 p_BaseLineWidth)
{
	K15_IASkyline* skylines = p_ImageAtlas->skylines;
	kia_u32 numSkylines = p_ImageAtlas->numSkylines;

	if (numSkylines == K15_IA_MAX_SKYLINES)
		return K15_IA_RESULT_OUT_OF_MEMORY;

	K15_IASkyline* newSkyline = skylines + numSkylines++;
	newSkyline->baseLinePosX = p_BaseLineX;
	newSkyline->baseLinePosY = p_BaseLineY;
	newSkyline->baseLineWidth = p_BaseLineWidth;

	kia_u32 removedSkylines = K15_IARemoveObscuredSkylines(skylines, numSkylines, newSkyline);

	p_ImageAtlas->numSkylines = numSkylines - removedSkylines;

	

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
static kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutTextureAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages)
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
		memoryBuffer);

	if (result != K15_IA_RESULT_SUCCESS)
		K15_IA_FREE(memoryBuffer);
	else
		p_OutTextureAtlas->flags &= ~KIA_EXTERNAL_MEMORY_FLAG; //Reset 'KIA_EXTERNAL_MEMORY_FLAG' flag

	return result;
}
/*********************************************************************************/
kia_result K15_IACreateAtlasWithCustomMemory(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages, kia_u32 p_MaxPixelWidth, kia_u32 p_MaxPixelHeight, kia_byte* p_MemoryBuffer)
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
	atlas.virtualPixelHeight = K15_IA_DEFAULT_MIN_ATLAS_DIMENSION;
	atlas.virtualPixelWidth = K15_IA_DEFAULT_MIN_ATLAS_DIMENSION;
	atlas.skylines = (K15_IASkyline*)K15_IA_MALLOC(40 * sizeof(K15_IASkyline));
	atlas.maxPixelHeight = p_MaxPixelHeight;
	atlas.maxPixelWidth = p_MaxPixelWidth;
	atlas.pixelFormat = p_PixelFormat;
	atlas.pixelData = p_MemoryBuffer;
	atlas.numImageNodes = p_NumImages;
	atlas.imageNodeIndex = 0;
	atlas.numSkylines = 0;
	atlas.imageNodes = (K15_IAImageNode*)(p_MemoryBuffer + imageNodeMemoryBufferOffset);
	atlas.flags = KIA_EXTERNAL_MEMORY_FLAG;

	K15_IATryToInsertSkyline(&atlas, 0, 0, K15_IA_DEFAULT_MIN_ATLAS_DIMENSION);

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
kia_result K15_IATryToGrowVirtualAtlasSize(K15_ImageAtlas* p_ImageAtlas)
{
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;
	kia_u32 maxWidth = p_ImageAtlas->maxPixelWidth;
	kia_u32 maxHeight = p_ImageAtlas->maxPixelHeight;
	kia_u32 numSkylines = p_ImageAtlas->numSkylines;
	kia_u32 widthExtend = 0;

	kia_u32 oldVirtualWidth = virtualWidth;

	K15_IASkyline* skylines = p_ImageAtlas->skylines;

	if (virtualWidth > virtualHeight)
		virtualHeight = virtualHeight << 1;
	else
		virtualWidth = virtualWidth << 1;

	if (virtualWidth > maxWidth || virtualHeight > maxHeight)
		return K15_IA_RESULT_ATLAS_TOO_SMALL;

	widthExtend = virtualWidth - p_ImageAtlas->virtualPixelWidth;

	p_ImageAtlas->virtualPixelWidth = virtualWidth;
	p_ImageAtlas->virtualPixelHeight = virtualHeight;

	kia_b8 foundSkyline = K15_IA_FALSE;

	//find skylines with pos == 0 (at the very bottom and extend their width)
	for (kia_u32 skylineIndex = 0;
		skylineIndex < numSkylines;
		++skylineIndex)
	{
		K15_IASkyline* skyline = skylines + skylineIndex;

		if (skyline->baseLinePosY == 0)
		{
			skyline->baseLineWidth += widthExtend;
			foundSkyline = K15_IA_TRUE;
		}
	}

	if (!foundSkyline)
		K15_IATryToInsertSkyline(p_ImageAtlas, 0, oldVirtualWidth, widthExtend);

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
kia_result K15_IATryToGrowVirtualAtlasSizeToFit(K15_ImageAtlas* p_ImageAtlas,
	kia_u32 p_MinWidth, kia_u32 p_MinHeight)
{
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;

	if (virtualHeight >= p_MinHeight &&
		virtualWidth >= p_MinWidth)
	{
		return K15_IA_RESULT_SUCCESS;
	}

	while (virtualHeight < p_MinHeight || virtualWidth < p_MinWidth)
	{
		kia_result result = K15_IATryToGrowVirtualAtlasSize(p_ImageAtlas);
	
		if (result != K15_IA_RESULT_SUCCESS)
			return result;

		virtualWidth = p_ImageAtlas->virtualPixelWidth;
		virtualHeight = p_ImageAtlas->virtualPixelHeight;
	}

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
kia_u32 K15_IASplitSkyline(K15_IASkyline* p_Skyline, kia_u32 p_Width, kia_u32 p_Height, kia_u32 p_MaxWidth, kia_u32 p_MaxHeight, K15_IASkyline** p_OutSkylineSplits)
{
	kia_u32 skylineBaseLineY = p_Skyline->baseLinePosY;
	kia_u32 skylineBaseLineX = p_Skyline->baseLinePosX;
	kia_u32 skylineBaseLineWidth = p_Skyline->baseLineWidth;
	kia_u32 numOutSkylines = 0;

	if (skylineBaseLineY + p_Height < p_MaxHeight)
	{
		K15_IASkyline* leftSkyline = *p_OutSkylineSplits;
		leftSkyline->baseLinePosY = skylineBaseLineY + p_Height;
		leftSkyline->baseLinePosX = skylineBaseLineX;
		leftSkyline->baseLineWidth = p_Width;
		numOutSkylines++;
	}

	if (skylineBaseLineX + p_Width < p_MaxWidth && p_Width < skylineBaseLineWidth)
	{
		K15_IASkyline* rightSkyline = *p_OutSkylineSplits + 1;
		rightSkyline->baseLinePosY = skylineBaseLineY;
		rightSkyline->baseLinePosX = skylineBaseLineX + p_Width;
		rightSkyline->baseLineWidth = skylineBaseLineWidth - p_Width;
		numOutSkylines++;
	}

	return numOutSkylines;
}
/*********************************************************************************/
kia_result K15_IAAddImageToAtlasSkyline(K15_ImageAtlas* p_ImageAtlas, K15_IAImageNode* p_NodeToInsert, 
	int* p_OutX, int* p_OutY)
{
	kia_result result = K15_IA_RESULT_ATLAS_TOO_SMALL;
	kia_u32 numSkylines = p_ImageAtlas->numSkylines;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;
	kia_u32 lowerPixelSpace = 0;
	kia_u32 rightPixelSpace = 0;
	kia_u32 nodeWidth = p_NodeToInsert->pixelWidth;
	kia_u32 nodeHeight = p_NodeToInsert->pixelHeight;
	kia_u32 skylineIndexToRemove = 0;
	kia_u32 restWidth = 0;
	kia_u32 restHeight = 0;
	kia_u32 baseLinePosY = 0;
	kia_u32 baseLinePosX = 0;
	kia_u32 baseLineWidth = 0;
	kia_u32 numSplits = 0;

	K15_IASkyline* skylines = p_ImageAtlas->skylines;

	for (kia_u32 skylineIndex = 0;
		skylineIndex < numSkylines;
		++skylineIndex)
	{
		K15_IASkyline* skyline = skylines + skylineIndex;
		baseLinePosY = skyline->baseLinePosY;
		baseLinePosX = skyline->baseLinePosX;
		baseLineWidth = skyline->baseLineWidth;
		lowerPixelSpace = virtualHeight - baseLinePosY;
		
		if (lowerPixelSpace >= nodeHeight &&
			baseLinePosX + nodeWidth <= virtualWidth)
		{
			result = K15_IA_RESULT_SUCCESS;
			skylineIndexToRemove = skylineIndex;
			
			K15_IASkyline* splitResult = (K15_IASkyline*)K15_IA_MALLOC(sizeof(K15_IASkyline) * 2);
			numSplits = K15_IASplitSkyline(skyline, nodeWidth, nodeHeight, virtualWidth, virtualHeight, &splitResult);

			if (numSplits >= 1)
				result = K15_IATryToInsertSkyline(p_ImageAtlas, splitResult[0].baseLinePosY, 
					splitResult[0].baseLinePosX, splitResult[0].baseLineWidth);

			p_NodeToInsert->pixelPosX = skyline->baseLinePosX;
			p_NodeToInsert->pixelPosY = skyline->baseLinePosY;

			if (p_OutX)
				*p_OutX = skyline->baseLinePosX;

			if (p_OutY)
				*p_OutY = skyline->baseLinePosY;

			goto functionEnd;
		}
	}

functionEnd:
	if (result == K15_IA_RESULT_SUCCESS)
	{
		kia_u32 elementsToShift = --p_ImageAtlas->numSkylines - skylineIndexToRemove;
		memmove(skylines + skylineIndexToRemove, skylines + skylineIndexToRemove + 1, elementsToShift * sizeof(K15_IASkyline));
	}
	return result;
}
/*********************************************************************************/
kia_result K15_IAAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas, K15_IAPixelFormat p_PixelFormat, 
	kia_byte* p_PixelData, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight,
	int* p_OutX, int* p_OutY)
{
	if (!p_ImageAtlas || !p_PixelData || p_PixelDataWidth == 0 || p_PixelDataHeight == 0 ||
		!p_OutX || !p_OutY)
	{
		return K15_IA_RESULT_INVALID_ARGUMENTS;
	}

	if (p_ImageAtlas->imageNodeIndex == p_ImageAtlas->numImageNodes)
		return K15_IA_RESULT_OUT_OF_RANGE;

	kia_result result = K15_IA_RESULT_ATLAS_TOO_SMALL;

	kia_u32 imageNodeIndex = p_ImageAtlas->imageNodeIndex++;
	K15_IAImageNode* imageNode = p_ImageAtlas->imageNodes + imageNodeIndex;

	imageNode->pixelData = p_PixelData;
	imageNode->pixelDataFormat = p_PixelFormat;
	imageNode->pixelHeight = p_PixelDataHeight;
	imageNode->pixelWidth = p_PixelDataWidth;

	while (result != K15_IA_RESULT_SUCCESS)
	{
		result = K15_IAAddImageToAtlasSkyline(p_ImageAtlas, imageNode, p_OutX, p_OutY);

		if (result == K15_IA_RESULT_ATLAS_TOO_SMALL)
			K15_IATryToGrowVirtualAtlasSize(p_ImageAtlas);
		else if (result != K15_IA_RESULT_SUCCESS)
			break;
	}

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
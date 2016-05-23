#ifndef _K15_ImageAtlas_h_
#define _K15_ImageAtlas_h_

#ifndef K15_IA_STATIC
# define kia_def static
#else
# define kia_def extern
#endif //K15_IA_STATIC

//TODO:
// Pixel Data Conversion

typedef signed int kia_s32;
typedef unsigned int kia_u32;
typedef unsigned char kia_u8;
typedef unsigned char kia_b8;
typedef unsigned char kia_byte;

enum _K15_IAAtlasFlags
{
	KIA_EXTERNAL_MEMORY_FLAG = 0x01,
	KIA_FORCE_POWER_OF_TWO_DIMENSION = 0x02
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
kia_def kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages);

kia_def kia_result K15_IACreateAtlasWithCustomMemory(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_u32 p_NumImages, kia_u32 p_PixelWidth, kia_u32 p_PixelHeight, kia_byte* p_PixelDataMemory);

kia_def kia_u32 K15_IACalculateAtlasMemorySizeInBytes(kia_u32 p_NumImages, kia_u32 p_MaxPixelWidth,
	kia_u32 p_MaxPixelHeight, K15_IAPixelFormat p_PixelFormat);

//Free a previously created atlas (K15_IACreateAtlas). Deallocates all memory associated with 
//an image atlas.
kia_def void K15_IAFreeAtlas(K15_ImageAtlas* p_ImageAtlas);

//Add an image to a specific atlas. 
//Note: The image will be added immediately to the atlas, which could potentially mean
//		that the atlas has to resize itself if the image does not fit in the current atlas.
//		This in turn will trigger a memory allocation and deallocation.
//		
//		Also if the number of color components of the image mismatch with the number of color components
//		of the atlas (specified in K15_IACreateAtlas) the function will convert the image to match up with
//		the pixel format of the atlas.
kia_def kia_result K15_IAAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas, K15_IAPixelFormat p_PixelFormat,
	kia_byte* p_PixelData, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight,
	int* p_OutX, int* p_OutY);

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

#ifndef K15_IA_MEMMOVE
# include <string.h>
# define K15_IA_MEMMOVE memmove
#endif //K15_IA_MEMMOVE

#ifndef K15_IA_QSORT
# include <search.h>
# define K15_IA_QSORT qsort
#endif //K15_IA_QSORT

#ifndef kia_internal
# define kia_internal static
#endif //kia_internal

typedef struct _K15_IAPotentialPosition
{
	kia_u32 skylineIndex;
	kia_u32 heuristic;
} K15_IAPotentialPosition;

/*********************************************************************************/
kia_internal int K15_IASortSkylineByXPos(const void* p_SkylineA, const void* p_SkylineB)
{
	K15_IASkyline* skylineA = (K15_IASkyline*)p_SkylineA;
	K15_IASkyline* skylineB = (K15_IASkyline*)p_SkylineB;

	return skylineA->baseLinePosX - skylineB->baseLinePosX;
}
/*********************************************************************************/
kia_internal int K15_IASortPotentialPositionsByHeuristic(const void* p_PositionA,
	const void* p_PositionB)
{
	K15_IAPotentialPosition* posA = (K15_IAPotentialPosition*)p_PositionA;
	K15_IAPotentialPosition* posB = (K15_IAPotentialPosition*)p_PositionB;

	return posA->heuristic - posB->heuristic;
}
/*********************************************************************************/



/*********************************************************************************/
kia_internal kia_result K15_IAConvertPixelData(kia_byte* p_SourcePixelData, kia_u8 p_SourceNumColorComponents,
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
kia_internal kia_u32 K15_IARemoveSkylineByIndex(K15_IASkyline* p_Skylines, kia_u32 p_NumSkylines, 
	kia_u32 p_SkylineIndex)
{
	kia_u32 numSkylines = p_NumSkylines;

	if (p_SkylineIndex + 1 < numSkylines)
	{
		kia_u32 numSkylinesToMove = numSkylines - p_SkylineIndex;
		K15_IA_MEMMOVE(p_Skylines + p_SkylineIndex, p_Skylines + p_SkylineIndex + 1, 
			numSkylinesToMove * sizeof(K15_IASkyline));
	
		--numSkylines;
	}
	
	return numSkylines;
}
/*********************************************************************************/
kia_internal kia_u32 K15_IARemoveObscuredSkylines(K15_IASkyline* p_Skylines, kia_u32 p_NumSkylines,
	kia_u32 p_PosX, kia_u32 p_PosY, kia_u32 p_Width)
{
	kia_u32 baseLinePosX = 0;
	kia_u32 baseLinePosY = 0;
	kia_u32 baseLineWidth = 0;
	kia_u32 rightPos = p_PosX + p_Width;
	kia_u32 baseLineRightPos = 0;
	kia_u32 numSkylinesToMove = 0;
	K15_IASkyline* skyline = 0;

	for (kia_u32 skylineIndex = 0;
		skylineIndex < p_NumSkylines;
		++skylineIndex)
	{
		skyline = p_Skylines + skylineIndex;
		baseLinePosX = skyline->baseLinePosX;
		baseLinePosY = skyline->baseLinePosY;
		baseLineWidth = skyline->baseLineWidth;

		if (p_PosX < baseLinePosX && rightPos > baseLinePosX && p_PosY > baseLinePosY)
		{
			//Split if we 'reach' into another skyline
			//check first if the current skyline is fully obscured
			baseLineRightPos = baseLinePosX + baseLineWidth;

			if (rightPos < baseLineRightPos)
			{
				skyline->baseLineWidth = baseLineRightPos - rightPos;
				skyline->baseLinePosX = rightPos;
				continue;
			}

			p_NumSkylines = K15_IARemoveSkylineByIndex(p_Skylines, p_NumSkylines, skylineIndex);
			--skylineIndex;
		}
	}

	return p_NumSkylines;
}
/*********************************************************************************/
kia_internal kia_u32 K15_IAMergeSkylines(K15_IASkyline* p_Skylines, kia_u32 p_NumSkylines)
{
	K15_IASkyline* skyline = 0;
	K15_IASkyline* previousSkyline = 0;

	kia_u32 baselineY = 0;
	kia_u32 previousBaseLineY = 0;

	kia_u32 numSkylines = p_NumSkylines;

	if (numSkylines > 1)
	{
		for (kia_u32 skylineIndex = 1;
			skylineIndex < numSkylines;
			skylineIndex += 2)
		{
			skyline = p_Skylines + skylineIndex;
			previousSkyline = p_Skylines + skylineIndex - 1;

			if (skyline->baseLinePosY == previousSkyline->baseLinePosY)
			{
				previousSkyline->baseLineWidth += skyline->baseLineWidth;

				numSkylines = K15_IARemoveSkylineByIndex(p_Skylines, numSkylines, skylineIndex);
				--skylineIndex;
			}
		}
	}

	return numSkylines;
}
/*********************************************************************************/
kia_internal kia_result K15_IATryToInsertSkyline(K15_ImageAtlas* p_ImageAtlas, kia_u32 p_BaseLineY, kia_u32 p_BaseLineX,
	kia_u32 p_BaseLineWidth)
{
	K15_IASkyline* skylines = p_ImageAtlas->skylines;
	kia_u32 numSkylines = p_ImageAtlas->numSkylines;

	if (numSkylines == K15_IA_MAX_SKYLINES)
		return K15_IA_RESULT_OUT_OF_MEMORY;

	//remove/trim any skylines that would be obscured by the new skyline
	numSkylines = K15_IARemoveObscuredSkylines(skylines, numSkylines, p_BaseLineX, p_BaseLineY, p_BaseLineWidth);

	K15_IASkyline* newSkyline = skylines + numSkylines++;
	newSkyline->baseLinePosX = p_BaseLineX;
	newSkyline->baseLinePosY = p_BaseLineY;
	newSkyline->baseLineWidth = p_BaseLineWidth;

	//Sort by x position
	K15_IA_QSORT(skylines, numSkylines, sizeof(K15_IASkyline), K15_IASortSkylineByXPos);

	//try to merge neighbor skylines with the same baseline (y pos)
	p_ImageAtlas->numSkylines = K15_IAMergeSkylines(skylines, numSkylines);

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
kia_internal kia_result K15_IATryToGrowVirtualAtlasSize(K15_ImageAtlas* p_ImageAtlas)
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
kia_internal kia_result K15_IATryToGrowVirtualAtlasSizeToFit(K15_ImageAtlas* p_ImageAtlas,
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
kia_internal kia_b8 K15_IACheckNodeCollision(K15_IAImageNode* p_ImageNodes, kia_u32 p_NumImageNodes,
	kia_u32 p_PosX, kia_u32 p_PosY, kia_u32 p_Width, kia_u32 p_Height)
{
	K15_IAImageNode* imageNode = 0;
	kia_s32 intersectionL = 0;
	kia_s32 intersectionT = 0;
	kia_s32 intersectionR = 0;
	kia_s32 intersectionB = 0;

	for (kia_u32 nodeIndex = 0;
		nodeIndex < p_NumImageNodes;
		++nodeIndex)
	{
		imageNode = p_ImageNodes + nodeIndex;

		intersectionL = max(p_PosX, imageNode->pixelPosX);
		intersectionT = max(p_PosY, imageNode->pixelPosY);
		intersectionR = min(p_PosX + p_Width, imageNode->pixelPosX + imageNode->pixelWidth);
		intersectionB = min(p_PosY + p_Height, imageNode->pixelPosY + imageNode->pixelHeight);

		if (intersectionL < intersectionR &&
			intersectionT < intersectionB)
		{
			return K15_IA_TRUE;
		}

	}
	return K15_IA_FALSE;
}
/*********************************************************************************/
kia_u32 K15_IACalculatePlacementHeuristic(kia_u32 p_BaseLinePosX, kia_u32 p_BaseLinePosY, kia_u32 p_NodeWidth,
	kia_u32 p_NodeHeight, K15_IASkyline* p_PlacementSkyline, K15_IASkyline* p_Skylines, kia_u32 p_NumSkylines)
{
	kia_u32 heuristic = 0;
	K15_IASkyline* skyline = 0;

	for (kia_u32 skylineIndex = 0;
	skylineIndex < p_NumSkylines;
		++skylineIndex)
	{
		skyline = p_Skylines + skylineIndex;

		if (skyline->baseLinePosX >= skyline->baseLinePosX && skyline->baseLinePosX < p_BaseLinePosX + p_NodeWidth)
		{
			kia_u32 right = min(skyline->baseLinePosX + skyline->baseLineWidth, p_BaseLinePosX + p_NodeWidth);
			kia_u32 left = max(skyline->baseLinePosX, p_BaseLinePosX);

			kia_u32 width = right - left;
			kia_u32 height = p_BaseLinePosY - skyline->baseLinePosY;


			heuristic += width * height;
		}
	}

	return heuristic;
}
/*********************************************************************************/
kia_internal kia_result K15_IAAddImageToAtlasSkyline(K15_ImageAtlas* p_ImageAtlas, K15_IAImageNode* p_NodeToInsert,
	int* p_OutX, int* p_OutY)
{
	kia_result result = K15_IA_RESULT_ATLAS_TOO_SMALL;
	kia_u32 numSkylines = p_ImageAtlas->numSkylines;
	kia_u32 numImageNodes = p_ImageAtlas->imageNodeIndex;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;
	kia_u32 lowerPixelSpace = 0;
	kia_u32 rightPixelSpace = 0;
	kia_u32 nodeWidth = p_NodeToInsert->pixelWidth;
	kia_u32 nodeHeight = p_NodeToInsert->pixelHeight;
	kia_u32 baseLinePosY = 0;
	kia_u32 baseLinePosX = 0;
	kia_u32 baseLineWidth = 0;
	kia_u32 elementsToShift = 0;
	kia_u32 numPotentialPositions = 0;
	kia_b8 collidesWithNodes = K15_IA_FALSE;

	const kia_u32 maxPotentialPositions = 20;

	K15_IASkyline* skylines = p_ImageAtlas->skylines;
	K15_IAImageNode* imageNodes = p_ImageAtlas->imageNodes;
	K15_IAPotentialPosition potentialPositions[maxPotentialPositions];

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
			collidesWithNodes = K15_IACheckNodeCollision(imageNodes, numImageNodes,
				baseLinePosX, baseLinePosY, nodeWidth, nodeHeight);

			if (!collidesWithNodes && 
				numPotentialPositions != maxPotentialPositions)
			{
				//node potentially fits. Calculate and save heuristic
				kia_u32 heuristic = K15_IACalculatePlacementHeuristic(baseLinePosX, baseLinePosY, nodeWidth, nodeHeight, skyline, skylines, numSkylines);
				K15_IAPotentialPosition* potentialPosition = potentialPositions + numPotentialPositions++;

				potentialPosition->skylineIndex = skylineIndex;
				potentialPosition->heuristic = heuristic;
			}
		}
	}

	if (numPotentialPositions > 1)
		K15_IA_QSORT(potentialPositions, numPotentialPositions, sizeof(K15_IAPotentialPosition), 
			K15_IASortPotentialPositionsByHeuristic);

	if (numPotentialPositions > 0)
	{
		K15_IAPotentialPosition* position = potentialPositions;
		K15_IASkyline* skyline = skylines + position->skylineIndex;
		p_NodeToInsert->pixelPosX = skyline->baseLinePosX;
		p_NodeToInsert->pixelPosY = skyline->baseLinePosY;

		if (skyline->baseLineWidth > p_NodeToInsert->pixelWidth)
		{
			skyline->baseLinePosX += p_NodeToInsert->pixelWidth;
			skyline->baseLineWidth -= p_NodeToInsert->pixelWidth;
		}
		else
		{
			p_ImageAtlas->numSkylines = K15_IARemoveSkylineByIndex(skylines, numSkylines, position->skylineIndex);
		}

		result = K15_IATryToInsertSkyline(p_ImageAtlas, p_NodeToInsert->pixelPosY + p_NodeToInsert->pixelHeight, 
			p_NodeToInsert->pixelPosX, p_NodeToInsert->pixelWidth);
	}

	if (result == K15_IA_RESULT_SUCCESS)
	{
		if (p_OutX)
			*p_OutX = p_NodeToInsert->pixelPosX;

		if (p_OutY)
			*p_OutY = p_NodeToInsert->pixelPosY;
	}

	return result;
}
/*********************************************************************************/




/*********************************************************************************/
kia_def kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutTextureAtlas, K15_IAPixelFormat p_PixelFormat,
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
kia_def kia_result K15_IACreateAtlasWithCustomMemory(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
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
kia_def kia_u32 K15_IACalculateAtlasMemorySizeInBytes(kia_u32 p_NumImages, kia_u32 p_MaxPixelWidth,
	kia_u32 p_MaxPixelHeight, K15_IAPixelFormat p_PixelFormat)
{
	kia_u32 numPixels = p_MaxPixelHeight * p_MaxPixelWidth;
	kia_u32 pixelDataSizeInBytes = numPixels * p_PixelFormat;
	kia_u32 imageNodeDataSizeInBytes = p_NumImages * sizeof(K15_IAImageNode);

	return pixelDataSizeInBytes + imageNodeDataSizeInBytes;
}
/*********************************************************************************/
kia_def void K15_IAFreeAtlas(K15_ImageAtlas* p_ImageAtlas)
{
	if (!p_ImageAtlas)
		return;

	if ((p_ImageAtlas->flags & KIA_EXTERNAL_MEMORY_FLAG) == 0)
		K15_IA_FREE(p_ImageAtlas->pixelData);
}
/*********************************************************************************/
kia_def kia_result K15_IAAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas, K15_IAPixelFormat p_PixelFormat,
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
	kia_result growResult = K15_IA_RESULT_SUCCESS;

	kia_u32 imageNodeIndex = p_ImageAtlas->imageNodeIndex;
	K15_IAImageNode* imageNode = p_ImageAtlas->imageNodes + imageNodeIndex;

	imageNode->pixelData = p_PixelData;
	imageNode->pixelDataFormat = p_PixelFormat;
	imageNode->pixelHeight = p_PixelDataHeight;
	imageNode->pixelWidth = p_PixelDataWidth;

	while (result != K15_IA_RESULT_SUCCESS)
	{
		result = K15_IAAddImageToAtlasSkyline(p_ImageAtlas, imageNode, p_OutX, p_OutY);

		if (result == K15_IA_RESULT_ATLAS_TOO_SMALL)
			growResult = K15_IATryToGrowVirtualAtlasSize(p_ImageAtlas);
		else if (growResult != K15_IA_RESULT_SUCCESS)
		{
			result = growResult;
			break;
		}
	}

	if (result == K15_IA_RESULT_SUCCESS)
		++p_ImageAtlas->imageNodeIndex;

	return result;
}
/*********************************************************************************/
#endif //K15_IMAGE_ATLAS_IMPLEMENTATION
#endif //_K15_ImageAtlas_h_
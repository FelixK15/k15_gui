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

typedef enum _K15_IAPixelFormat
{
	KIA_PIXEL_FORMAT_R8			= 1,
	KIA_PIXEL_FORMAT_R8A8		= 2,
	KIA_PIXEL_FORMAT_R8G8B8		= 3,
	KIA_PIXEL_FORMAT_R8G8B8A8	= 4
} K15_IAPixelFormat;

typedef enum _K15_IAResult
{
	K15_IA_RESULT_SUCCESS = 0,				//<! Everything went fine
	K15_IA_RESULT_OUT_OF_MEMORY = 1,		//<! Out of memory
	K15_IA_RESULT_OUT_OF_RANGE = 2,			//<! Out of range (passed wrong index)
	K15_IA_NODE_LIMIT_REACHED = 3,
	K15_IA_RESULT_INVALID_ARGUMENTS = 4,	//<! Invalid arguments (nullptr, etc)
	K15_IA_RESULT_ATLAS_TOO_SMALL = 5,		//<! Only used internally
	K15_IA_RESULT_ATLAS_TOO_LARGE = 6		//<! The atlas has grown too large (Specfied by K15_TA_THRESHOLD)
											//	 note: There's an upper texture dimension limit to what you 
											//		   can upload to the GPU. 
											//		   K15_TA_THRESHOLD should be that upper limit value.
} kia_result;

typedef struct _K15_IARect
{
	kia_u32 posX;
	kia_u32 posY;
	kia_u32 width;
	kia_u32 height;
} K15_IARect;

typedef struct _K15_IAImageNode
{
	K15_IAPixelFormat pixelDataFormat;
	K15_IARect rect;
	kia_byte* pixelData;
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
	K15_IARect* wastedSpaceRects;
	kia_byte* pixelData;		//<! Pixel data of the atlas

	K15_IAPixelFormat pixelFormat;

	kia_u32 maxPixelWidth;		//<! Width of the atlas in pixels
	kia_u32 maxPixelHeight;		//<! Height of the atlas in pixels

	kia_u32 virtualPixelWidth;
	kia_u32 virtualPixelHeight;
	
	kia_u32 numSkylines;
	kia_u32 numMaxImageNodes;
	kia_u32 numWastedSpaceRects;
	kia_u32 numImageNodes;
	kia_u8 flags;
} K15_ImageAtlas;

//Create a new atlas which is capable of storing pixel data where each pixel
//consists of exactly p_Components number of color components (max 4)
//Note: Returns on of the following results:
//			- K15_IA_RESULT_INVALID_ARGUMENTS (p_OutImageAtlas is NULL or p_Components is invalid)
//			- K15_IA_RESULT_SUCCESS
kia_def kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	unsigned int p_NumImages);

kia_def kia_result K15_IACreateAtlasWithCustomMemory(K15_ImageAtlas* p_OutImageAtlas, K15_IAPixelFormat p_PixelFormat,
	unsigned int p_NumImages, unsigned int p_PixelWidth, unsigned int p_PixelHeight, unsigned char* p_PixelDataMemory);

kia_def kia_u32 K15_IACalculateAtlasMemorySizeInBytes(unsigned int p_NumImages, unsigned int p_MaxPixelWidth,
	unsigned int p_MaxPixelHeight, K15_IAPixelFormat p_PixelFormat);

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
	unsigned char* p_PixelData, int p_PixelDataWidth, int p_PixelDataHeight,
	int* p_OutX, int* p_OutY);

#ifdef K15_IA_IMPLEMENTATION

#define K15_IA_TRUE 1
#define K15_IA_FALSE 0

#ifndef K15_IA_MAX_SKYLINES 
# define K15_IA_MAX_SKYLINES 40
#endif //K15_IA_MAX_SKYLINES 

#ifndef K15_IA_MAX_WASTED_SPACE_RECTS 
# define K15_IA_MAX_WASTED_SPACE_RECTS 40
#endif //K15_IA_MAX_WASTED_SPACE_RECTS 

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

#ifndef K15_IA_MIN
# define K15_IA_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif //K15_IA_MIN

#ifndef K15_IA_MAX
# define K15_IA_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif //K15_IA_MAX

#ifndef kia_internal
# define kia_internal static
#endif //kia_internal

typedef struct _K15_IAPotentialPosition
{
	kia_u32 elementIndex;
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
	}

	return --numSkylines;
}
/*********************************************************************************/
kia_internal kia_u32 K15_IAAddWastedSpaceRect(K15_IARect* p_WastedSpaceRects, kia_u32 p_NumWastedSpaceRects,
	kia_u32 p_PosX, kia_u32 p_PosY, kia_u32 p_Width, kia_u32 p_Height)
{
	kia_u32 numWastedSpaceRects = p_NumWastedSpaceRects;

	if (numWastedSpaceRects < K15_IA_MAX_WASTED_SPACE_RECTS)
	{
		p_WastedSpaceRects[numWastedSpaceRects].posX = p_PosX;
		p_WastedSpaceRects[numWastedSpaceRects].posY = p_PosY;
		p_WastedSpaceRects[numWastedSpaceRects].width = p_Width;
		p_WastedSpaceRects[numWastedSpaceRects].height = p_Height;
		++numWastedSpaceRects;
	}

	return numWastedSpaceRects;
}
/*********************************************************************************/
kia_internal void K15_IAFindWastedSpaceAndRemoveObscuredSkylines(K15_IASkyline* p_Skylines, 
	kia_u32* p_NumSkylinesOutIn, K15_IARect* p_WastedSpaceRects, kia_u32* p_NumWastedSpaceRectsOutIn,
	kia_u32 p_PosX, kia_u32 p_PosY, kia_u32 p_Width)
{
	kia_u32 baseLinePosX = 0;
	kia_u32 baseLinePosY = 0;
	kia_u32 baseLineWidth = 0;
	kia_u32 rightPos = p_PosX + p_Width;
	kia_u32 baseLineRightPos = 0;
	kia_u32 numSkylines = *p_NumSkylinesOutIn;
	kia_u32 numWastedSpaceRects = *p_NumWastedSpaceRectsOutIn;

	K15_IASkyline* skyline = 0;
	
	for (kia_u32 skylineIndex = 0;
		skylineIndex < numSkylines;
		++skylineIndex)
	{
		skyline = p_Skylines + skylineIndex;
		baseLinePosX = skyline->baseLinePosX;
		baseLinePosY = skyline->baseLinePosY;
		baseLineWidth = skyline->baseLineWidth;

		if (p_PosX < baseLinePosX && rightPos > baseLinePosX && p_PosY >= baseLinePosY)
		{
			//Split if we 'reach' into another skyline
			//check first if the current skyline is fully obscured
			baseLineRightPos = baseLinePosX + baseLineWidth;

			if (rightPos < baseLineRightPos)
			{
				numWastedSpaceRects = K15_IAAddWastedSpaceRect(p_WastedSpaceRects, numWastedSpaceRects,
					baseLinePosX, baseLinePosY, rightPos - baseLinePosX, p_PosY - baseLinePosY);

				skyline->baseLineWidth = baseLineRightPos - rightPos;
				skyline->baseLinePosX = rightPos;
				continue;
			}

			numSkylines = K15_IARemoveSkylineByIndex(p_Skylines, numSkylines, skylineIndex);
			numWastedSpaceRects = K15_IAAddWastedSpaceRect(p_WastedSpaceRects, numWastedSpaceRects,
				baseLinePosX, baseLinePosY, baseLineWidth, p_PosY - baseLinePosY);

			--skylineIndex;
		}
	}

	*p_NumSkylinesOutIn = numSkylines;
	*p_NumWastedSpaceRectsOutIn = numWastedSpaceRects;
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
			++skylineIndex)
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
kia_internal kia_result K15_IATryToInsertSkyline(K15_IASkyline* p_Skylines, kia_u32* p_NumSkylinesInOut, 
	kia_u32 p_BaseLineY, kia_u32 p_BaseLineX, kia_u32 p_BaseLineWidth)
{
	kia_u32 numSkylines = *p_NumSkylinesInOut;

	if (numSkylines == K15_IA_MAX_SKYLINES)
		return K15_IA_RESULT_OUT_OF_MEMORY;

	K15_IASkyline* newSkyline = p_Skylines + numSkylines++;
	newSkyline->baseLinePosX = p_BaseLineX;
	newSkyline->baseLinePosY = p_BaseLineY;
	newSkyline->baseLineWidth = p_BaseLineWidth;

	//Sort by x position
	K15_IA_QSORT(p_Skylines, numSkylines, sizeof(K15_IASkyline), K15_IASortSkylineByXPos);

	//try to merge neighbor skylines with the same baseline (y pos)
	numSkylines = K15_IAMergeSkylines(p_Skylines, numSkylines);

	*p_NumSkylinesInOut = numSkylines;

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
		K15_IATryToInsertSkyline(skylines, &numSkylines, 0, oldVirtualWidth, widthExtend);

	p_ImageAtlas->numSkylines = numSkylines;

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

		intersectionL = K15_IA_MAX(p_PosX, imageNode->rect.posX);
		intersectionT = K15_IA_MAX(p_PosY, imageNode->rect.posY);
		intersectionR = K15_IA_MIN(p_PosX + p_Width, imageNode->rect.posX + imageNode->rect.width);
		intersectionB = K15_IA_MIN(p_PosY + p_Height, imageNode->rect.posY + imageNode->rect.height);

		if (intersectionL < intersectionR &&
			intersectionT < intersectionB)
		{
			return K15_IA_TRUE;
		}

	}
	return K15_IA_FALSE;
}
/*********************************************************************************/
kia_internal kia_u32 K15_IASplitWastedSpaceRect(K15_IARect* p_WastedSpaceRects, kia_u32 p_NumWastedSpaceRects,
	kia_u32 p_Index, kia_u32 p_Width, kia_u32 p_Height)
{
	K15_IARect* wastedSpaceRect = p_WastedSpaceRects + p_Index;

	kia_u32 rectHeight = wastedSpaceRect->height;
	kia_u32 rectWidth = wastedSpaceRect->width;

	kia_u32 restHeight = rectHeight - p_Height;
	kia_u32 restWidth = rectWidth - p_Width;
	
	kia_u32 posLowerX = wastedSpaceRect ->posX;
	kia_u32 posLowerY = wastedSpaceRect ->posY + p_Height;
	kia_u32 posRightX = wastedSpaceRect ->posX + p_Width;
	kia_u32 posRightY = wastedSpaceRect ->posY;

	if (p_NumWastedSpaceRects > 1)
	{
		//Remove
		kia_u32 numElementsToShift = p_NumWastedSpaceRects - p_Index;
		K15_IA_MEMMOVE(p_WastedSpaceRects + p_Index, p_WastedSpaceRects + p_Index + 1,
			sizeof(K15_IARect) * numElementsToShift);
	}

	--p_NumWastedSpaceRects;

	if (restWidth != 0 && restHeight != 0)
	{
		if (restWidth > restHeight)
		{
			p_NumWastedSpaceRects = K15_IAAddWastedSpaceRect(p_WastedSpaceRects, p_NumWastedSpaceRects, posRightX, posRightY, restWidth, rectHeight);
			p_NumWastedSpaceRects = K15_IAAddWastedSpaceRect(p_WastedSpaceRects, p_NumWastedSpaceRects, posLowerX, posLowerY, p_Width, restHeight);
		}
		else
		{
			p_NumWastedSpaceRects = K15_IAAddWastedSpaceRect(p_WastedSpaceRects, p_NumWastedSpaceRects, posLowerX, posLowerY, rectWidth, restHeight);
			p_NumWastedSpaceRects = K15_IAAddWastedSpaceRect(p_WastedSpaceRects, p_NumWastedSpaceRects, posRightX, posRightY, restWidth, p_Height);
		}
	}

	return p_NumWastedSpaceRects;
}
/*********************************************************************************/
kia_internal kia_u32 K15_IARemoveOrTrimWastedSpaceRect(K15_IARect* p_WastedSpaceRects,
	kia_u32 p_NumWastedSpaceRects, kia_u32 p_Index, kia_u32 p_Width, kia_u32 p_Height)
{
	K15_IARect* wastedSpaceRect = p_WastedSpaceRects + p_Index;
	kia_u32 numWastedSpaceRect = p_NumWastedSpaceRects;
	kia_u32 rectWidth = wastedSpaceRect->width;
	kia_u32 rectHeight = wastedSpaceRect->height;
	kia_u32 rectPosX = wastedSpaceRect->posX;
	kia_u32 rectPosY = wastedSpaceRect->posY;
	
	if (rectWidth == p_Width &&
		rectHeight > p_Height)
	{
		rectPosY += p_Height;
		rectHeight -= p_Height;
	}
	else if (rectHeight == p_Height &&
			 rectWidth > p_Width)
	{
		rectPosX += p_Width;
		rectWidth -= p_Width;
	}
	else
	{
		numWastedSpaceRect = K15_IASplitWastedSpaceRect(p_WastedSpaceRects, numWastedSpaceRect, p_Index, p_Width, p_Height);
	}
	
	return numWastedSpaceRect;
}
/*********************************************************************************/
kia_u32 K15_IACollectPotentialPlacementsInWastedSpace(K15_IARect* p_WastedSpaceRects, kia_u32 p_NumWastedSpaceRects,
	K15_IAPotentialPosition* p_PotentialPositions, kia_u32 p_NumMaxPotentialPositions,
	kia_u32 p_Width, kia_u32 p_Height)
{
	K15_IARect* wastedSpaceRect = 0;
	kia_u32 wastedSpaceRectWidth = 0;
	kia_u32 wastedSpaceRectHeight = 0;
	kia_u32 numPotentialPositions = 0;
	
	for (kia_u32 rectIndex = 0;
		rectIndex < p_NumWastedSpaceRects;
		++rectIndex)
	{
		wastedSpaceRect = p_WastedSpaceRects + rectIndex;
		wastedSpaceRectWidth = wastedSpaceRect->width;
		wastedSpaceRectHeight = wastedSpaceRect->height;

		if (wastedSpaceRectWidth >= p_Width&&
			wastedSpaceRectHeight >= p_Height)
		{
			p_PotentialPositions[numPotentialPositions].elementIndex = rectIndex;
			p_PotentialPositions[numPotentialPositions].heuristic = wastedSpaceRectHeight * wastedSpaceRectWidth;
			++numPotentialPositions;

			//limit reached?
			if (numPotentialPositions == p_NumMaxPotentialPositions)
			{
				break;
			}
		}
	}

	if (numPotentialPositions > 1)
	{
		K15_IA_QSORT(p_PotentialPositions, numPotentialPositions, sizeof(K15_IAPotentialPosition),
			K15_IASortPotentialPositionsByHeuristic);
	}


	return numPotentialPositions;
}
/*********************************************************************************/
kia_internal kia_u32 K15_IACollectPotentialPlacementsInSkylines(K15_IASkyline* p_Skylines, kia_u32 p_NumSkylines,
	K15_IAImageNode* p_ImageNodes, kia_u32 p_NumImageNodes,
	K15_IAPotentialPosition* p_PotentialPostions, kia_u32 p_NumMaxPotentialPositions,
	kia_u32 p_Width, kia_u32 p_Height, kia_u32 p_VirtualWidth, kia_u32 p_VirtualHeight)
{
	K15_IASkyline* skyline = 0;
	kia_u32 skylinePosX = 0;
	kia_u32 skylinePosY = 0;
	kia_u32 skylineWidth = 0;
	kia_u32 lowerPixelSpace = 0;
	kia_u32 numPotentialPositions = 0;
	kia_b8 collidesWithNodes = K15_IA_FALSE;

	for (kia_u32 skylineIndex = 0;
	skylineIndex < p_NumSkylines;
		++skylineIndex)
	{
		skyline = p_Skylines + skylineIndex;
		skylinePosY = skyline->baseLinePosY;
		skylinePosX = skyline->baseLinePosX;
		skylineWidth = skyline->baseLineWidth;
		lowerPixelSpace = p_VirtualWidth - skylinePosX;

		if (lowerPixelSpace >= p_Height &&
			skylinePosX + p_Width <= p_VirtualWidth)
		{
			collidesWithNodes = K15_IACheckNodeCollision(p_ImageNodes, p_NumImageNodes,
				skylinePosX, skylinePosY, p_Width, p_Height);

			if (!collidesWithNodes &&
				numPotentialPositions != p_NumMaxPotentialPositions)
			{
				//node potentially fits. Calculate and save heuristic
				kia_u32 heuristic = K15_IACalculatePlacementHeuristic(skylinePosX, skylinePosY, p_Width, p_Height, skyline, p_Skylines, p_NumSkylines);
				K15_IAPotentialPosition* potentialPosition = p_PotentialPostions + numPotentialPositions++;

				potentialPosition->elementIndex = skylineIndex;
				potentialPosition->heuristic = heuristic;
			}
		}
	}

	if (numPotentialPositions > 1)
	{
		K15_IA_QSORT(p_PotentialPostions, numPotentialPositions, sizeof(K15_IAPotentialPosition),
			K15_IASortPotentialPositionsByHeuristic);
	}

	return numPotentialPositions;
}
/*********************************************************************************/
kia_internal kia_b8 K15_IATryToFitInWastedSpace(K15_IARect* p_WastedSpaceRects, kia_u32* p_NumWastedSpaceRectsInOut,
	K15_IAImageNode* p_NodeToInsert)
{
	const kia_u32 numMaxPotentialPositions = 20;
	kia_u32 numPotentialPositions = 0;
	kia_u32 wastedRectWidth = 0;
	kia_u32 wastedRectHeight = 0;
	kia_u32 nodeWidth = p_NodeToInsert->rect.width;
	kia_u32 nodeHeight = p_NodeToInsert->rect.height;
	kia_u32 numWastedSpaceRects = *p_NumWastedSpaceRectsInOut;
	kia_b8 fitIntoWastedSpace = K15_IA_FALSE;

	K15_IARect* wastedSpaceRect = 0;
	K15_IAPotentialPosition* potentialPosition = 0;
	K15_IAPotentialPosition potentialPositions[numMaxPotentialPositions];
	
	//find the best fitting rect
	numPotentialPositions = K15_IACollectPotentialPlacementsInWastedSpace(p_WastedSpaceRects, numWastedSpaceRects,
		potentialPositions, numMaxPotentialPositions, nodeWidth, nodeHeight);

	if (numPotentialPositions > 0)
	{
		//use first element from potentialPositions and
		//copy position
		wastedSpaceRect = p_WastedSpaceRects + potentialPositions->elementIndex;
		p_NodeToInsert->rect.posX = wastedSpaceRect->posX;
		p_NodeToInsert->rect.posY = wastedSpaceRect->posY;

		numWastedSpaceRects = K15_IARemoveOrTrimWastedSpaceRect(p_WastedSpaceRects,
			numWastedSpaceRects, potentialPositions->elementIndex, nodeWidth, nodeHeight);

		*p_NumWastedSpaceRectsInOut = numWastedSpaceRects;
	}
	
	return fitIntoWastedSpace;
}
/*********************************************************************************/
kia_internal kia_result K15_IAAddImageToAtlasSkyline(K15_ImageAtlas* p_ImageAtlas, K15_IAImageNode* p_NodeToInsert,
	int* p_OutX, int* p_OutY)
{
	kia_result result = K15_IA_RESULT_ATLAS_TOO_SMALL;
	kia_u32 numSkylines = p_ImageAtlas->numSkylines;
	kia_u32 numImageNodes = p_ImageAtlas->numImageNodes;
	kia_u32 numWastedSpaceRects = p_ImageAtlas->numWastedSpaceRects;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;
	kia_u32 nodeWidth = p_NodeToInsert->rect.width;
	kia_u32 nodeHeight = p_NodeToInsert->rect.height;
	kia_u32 numPotentialPositions = 0;

	kia_u32 nodePosX = 0;
	kia_u32 nodePosY = 0;

	const kia_u32 numMaxPotentialPositions = 20;

	K15_IASkyline* skylines = p_ImageAtlas->skylines;
	K15_IAImageNode* imageNodes = p_ImageAtlas->imageNodes;
	K15_IAPotentialPosition potentialPositions[numMaxPotentialPositions];
	K15_IARect* wastedSpaceRects = p_ImageAtlas->wastedSpaceRects;

	//first try to insert the image node into the accumulated wasted space
	kia_b8 fitsInWastedSpace = K15_IATryToFitInWastedSpace(wastedSpaceRects, 
		&numWastedSpaceRects, p_NodeToInsert);

	if (fitsInWastedSpace)
	{
		p_ImageAtlas->numWastedSpaceRects = numWastedSpaceRects;
		result = K15_IA_RESULT_SUCCESS;
		goto functionEnd;
	}

	//if that failed, go through the skylines and collect all potentially fitting
	//positions
	numPotentialPositions = K15_IACollectPotentialPlacementsInSkylines(skylines, numSkylines, 
		imageNodes, numImageNodes, potentialPositions, numMaxPotentialPositions, 
		nodeWidth, nodeHeight, virtualWidth, virtualHeight);

	//grab the first potential position (already sorted)
	if (numPotentialPositions > 0)
	{
		K15_IAPotentialPosition* position = potentialPositions;
		K15_IASkyline* skyline = skylines + position->elementIndex;
		p_NodeToInsert->rect.posX = skyline->baseLinePosX;
		p_NodeToInsert->rect.posY = skyline->baseLinePosY;

		nodePosX = p_NodeToInsert->rect.posX;
		nodePosY = p_NodeToInsert->rect.posY;

		//check if the skyline we found to be best fitting is
		//fully obscured by the image node (erase skyline), or
		//if there's still space left (truncate skyline)
		if (skyline->baseLineWidth > nodeWidth)
		{
			//truncate
			skyline->baseLinePosX += nodeWidth;
			skyline->baseLineWidth -= nodeWidth;
		}
		else
		{
			//erase
			p_ImageAtlas->numSkylines = K15_IARemoveSkylineByIndex(skylines, numSkylines, position->elementIndex);
		}

		//add a new skyline beneath the new node
		result = K15_IATryToInsertSkyline(skylines, &numSkylines, nodePosY + nodeHeight,
			nodePosX, nodeWidth);
	}

functionEnd:
	if (result == K15_IA_RESULT_SUCCESS)
	{
		if (p_OutX)
			*p_OutX = nodePosX;

		if (p_OutY)
			*p_OutY = nodePosY;

		//remove/trim any skylines that would be obscured by the new skyline
		K15_IAFindWastedSpaceAndRemoveObscuredSkylines(skylines, &numSkylines,
			wastedSpaceRects, &numWastedSpaceRects,
			nodePosX, nodePosY, nodeWidth);

		p_ImageAtlas->numSkylines = numSkylines;
		p_ImageAtlas->numWastedSpaceRects = numWastedSpaceRects;
	}
		
	return result;
}
/*********************************************************************************/




/*********************************************************************************/
kia_def kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutTextureAtlas, K15_IAPixelFormat p_PixelFormat,
	unsigned int p_NumImages)
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
	unsigned int p_NumImages, unsigned int p_MaxPixelWidth, unsigned int p_MaxPixelHeight, kia_byte* p_MemoryBuffer)
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
	kia_u32 skylineMemoryBufferOffset = imageNodeMemoryBufferOffset + sizeof(K15_IAImageNode) * p_NumImages;
	kia_u32 wastedSpaceMemoryBufferOffset = skylineMemoryBufferOffset + sizeof(K15_IASkyline) * K15_IA_MAX_SKYLINES;

	//clear memory
	K15_IA_MEMSET(p_MemoryBuffer, 0, memoryBufferSizeInBytes);

	K15_ImageAtlas atlas;
	atlas.virtualPixelHeight = K15_IA_DEFAULT_MIN_ATLAS_DIMENSION;
	atlas.virtualPixelWidth = K15_IA_DEFAULT_MIN_ATLAS_DIMENSION;
	atlas.maxPixelHeight = p_MaxPixelHeight;
	atlas.maxPixelWidth = p_MaxPixelWidth;
	atlas.pixelFormat = p_PixelFormat;
	atlas.pixelData = p_MemoryBuffer;
	atlas.numMaxImageNodes = p_NumImages;
	atlas.numImageNodes = 0;
	atlas.numWastedSpaceRects = 0;
	atlas.numSkylines = 0;
	atlas.imageNodes = (K15_IAImageNode*)(p_MemoryBuffer + imageNodeMemoryBufferOffset);
	atlas.skylines = (K15_IASkyline*)(p_MemoryBuffer + skylineMemoryBufferOffset);
	atlas.wastedSpaceRects = (K15_IARect*)(p_MemoryBuffer + wastedSpaceMemoryBufferOffset);
	atlas.flags = KIA_EXTERNAL_MEMORY_FLAG;

	//Insert default skyline
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
	kia_u32 skylineDataSizeInBytes = K15_IA_MAX_SKYLINES * sizeof(K15_IASkyline);
	kia_u32 wastedSpaceRectsSizeInBytes = K15_IA_MAX_WASTED_SPACE_RECTS * sizeof(K15_IARect);

	return pixelDataSizeInBytes + imageNodeDataSizeInBytes + skylineDataSizeInBytes + wastedSpaceRectsSizeInBytes;
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

	if (p_ImageAtlas->numMaxImageNodes == p_ImageAtlas->numImageNodes)
		return K15_IA_NODE_LIMIT_REACHED;

	kia_result result = K15_IA_RESULT_ATLAS_TOO_SMALL;
	kia_result growResult = K15_IA_RESULT_SUCCESS;

	kia_u32 imageNodeIndex = p_ImageAtlas->numImageNodes;
	kia_u32 virtualHeight = p_ImageAtlas->virtualPixelHeight;
	kia_u32 virtualWidth = p_ImageAtlas->virtualPixelWidth;

	K15_IAImageNode* imageNode = p_ImageAtlas->imageNodes + imageNodeIndex;

	imageNode->pixelData = p_PixelData;
	imageNode->pixelDataFormat = p_PixelFormat;
	imageNode->rect.height = p_PixelDataHeight;
	imageNode->rect.width = p_PixelDataWidth;

	result = K15_IAAddImageToAtlasSkyline(p_ImageAtlas, imageNode, p_OutX, p_OutY);

	if (result == K15_IA_RESULT_ATLAS_TOO_SMALL)
	{
		kia_u32 newVirtualWidth = p_PixelDataWidth > p_PixelDataHeight ? p_PixelDataWidth + virtualWidth : virtualWidth;
		kia_u32 newVirtualHeight = p_PixelDataHeight > p_PixelDataWidth ? p_PixelDataHeight + virtualHeight : virtualHeight;

		growResult = K15_IATryToGrowVirtualAtlasSizeToFit(p_ImageAtlas, newVirtualWidth, newVirtualHeight);

		if (growResult == K15_IA_RESULT_SUCCESS)
			result = K15_IAAddImageToAtlasSkyline(p_ImageAtlas, imageNode, p_OutX, p_OutY);
		else
			result = growResult;
	}
	
	return result;
}
/*********************************************************************************/
#endif //K15_IMAGE_ATLAS_IMPLEMENTATION
#endif //_K15_ImageAtlas_h_
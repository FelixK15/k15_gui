#ifndef _K15_ImageAtlas_h_
#define _K15_ImageAtlas_h_

typedef unsigned int kia_u32;
typedef unsigned char kia_u8;
typedef unsigned char kia_b8;
typedef unsigned char kia_byte;

typedef struct _K15_ImageAtlas
{
	kia_u32 pixelWidth;			//<! Width of the atlas in pixels
	kia_u32 pixelHeight;		//<! Height of the atlas in pixels
	
	kia_byte* pixelData;		//<! Pixel data of the atlas
	kia_byte* accessMap;		//<! Access map used to determine where to place new pixel data

	kia_u8 numColorComponents;	//<! Number of color components used per pixel by the atlas
} K15_ImageAtlas;

typedef enum _K15_TIResults
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

//Create a new atlas which is capable of storing pixel data where each pixel
//consists of exactly p_Components number of color components (max 4)
//Note: Returns on of the following results:
//			- K15_IA_RESULT_INVALID_ARGUMENTS (p_OutImageAtlas is NULL or p_Components is invalid)
//			- K15_IA_RESULT_SUCCESS
kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutImageAtlas, kia_u8 p_Components);

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
kia_result K15_IAAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas, kia_byte* p_PixelData, 
	kia_u8 p_NumColorComponents, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight,
	kia_u32* p_OutX, kia_u32* p_OutY);


kia_byte* K15_IAGetAtlasPixelData(K15_ImageAtlas* p_ImageAtlas, kia_u32* p_OutWidth, kia_u32* p_OutHeight);
kia_u32 K15_IAGetAtlasPixelDataSizeInBytes(K15_ImageAtlas* p_ImageAtlas);

#ifdef K15_IA_IMPLEMENTATION

#define K15_IA_TRUE 1
#define K15_IA_FALSE 0

#define K15_IA_ACCESS_MAP_FREE 0x00
#define K15_IA_ACCESS_MAP_OCCUPIED 0xFF
 
#ifndef K15_IA_DIMENSION_THRESHOLD
# define K15_IA_DIMENSION_THRESHOLD 2048
#endif //K15_IA_DIMENSION_THRESHOLD

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
static void K15_IACopyAtlasData(K15_ImageAtlas* p_ImageAtlas, kg_u32 p_DestinationPixelWidth,
	kg_u32 p_DestinationPixelHeight, kg_byte* p_DestinationAccessMap, kg_byte* p_DestinationPixelData)
{
	kg_u32 numColorComponents = p_ImageAtlas->numColorComponents;
	kg_u32 atlasPixelHeight = p_ImageAtlas->pixelHeight;
	kg_u32 sourcePixelDataStride = p_ImageAtlas->pixelWidth * numColorComponents;
	kg_u32 destinationPixelDataStride = p_DestinationPixelWidth * numColorComponents;
	kg_u32 destinationAccessMapStride = p_DestinationPixelWidth;
	kg_u32 sourceAccessMapStride = p_ImageAtlas->pixelWidth;
	kg_u32 sourcePixelDataOffset = 0;
	kg_u32 destinationPixelDataOffset = 0;
	kg_u32 sourceAccessMapOffset = 0;
	kg_u32 destinationAccessMapOffset = 0;

	kg_byte* sourceAccessMap = p_ImageAtlas->accessMap;
	kg_byte* sourcePixelData = p_ImageAtlas->pixelData;

	for (kg_u32 verticalIndex = 0;
		verticalIndex < atlasPixelHeight;
		++verticalIndex)
	{
		K15_IA_MEMCPY(p_DestinationAccessMap + destinationAccessMapOffset,
			sourceAccessMap + sourceAccessMapOffset,
			sourceAccessMapStride);
	
		K15_IA_MEMCPY(p_DestinationPixelData + destinationPixelDataOffset,
			sourcePixelData + sourcePixelDataOffset,
			sourcePixelDataStride);

		sourceAccessMapOffset += sourceAccessMapStride;
		sourcePixelDataOffset += sourcePixelDataStride;

		destinationAccessMapOffset += destinationAccessMapStride;
		destinationPixelDataOffset += destinationPixelDataStride;
	}
}
/*********************************************************************************/
static kia_result K15_IAResizeAtlas(K15_ImageAtlas* p_ImageAtlas, 
	kg_u32 p_DesiredPixelWidth, kg_u32 p_DesiredPixelHeight)
{
	if (p_DesiredPixelHeight < p_ImageAtlas->pixelHeight ||
		p_DesiredPixelWidth < p_ImageAtlas->pixelWidth)
	{
		return K15_IA_RESULT_INVALID_ARGUMENTS;
	}

	kg_u32 numColorComponents = p_ImageAtlas->numColorComponents;
	kg_u32 numPixels = p_DesiredPixelWidth * p_DesiredPixelHeight;
	kg_u32 numPixelBytes = numPixels * numColorComponents;

	kia_byte* accessMapMemory = (kia_byte*)K15_IA_MALLOC(numPixels);
	kia_byte* pixelDataMemory = (kia_byte*)K15_IA_MALLOC(numPixelBytes);

	if (!accessMapMemory || !pixelDataMemory)
		return K15_IA_RESULT_OUT_OF_MEMORY;

	K15_IA_MEMSET(accessMapMemory, 0, numPixels);
	K15_IA_MEMSET(pixelDataMemory, 0, numPixelBytes);

	if (p_ImageAtlas->accessMap &&
		p_ImageAtlas->pixelData)
	{
		K15_IACopyAtlasData(p_ImageAtlas, p_DesiredPixelWidth, p_DesiredPixelHeight, 
			accessMapMemory, pixelDataMemory);
	}

	p_ImageAtlas->accessMap = accessMapMemory;
	p_ImageAtlas->pixelData = pixelDataMemory;
	p_ImageAtlas->pixelHeight = p_DesiredPixelHeight;
	p_ImageAtlas->pixelWidth = p_DesiredPixelWidth;

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
static kia_result K15_IACreateAtlas(K15_ImageAtlas* p_OutTextureAtlas, kia_u8 p_NumColorComponents)
{
	if (!p_OutTextureAtlas || p_NumColorComponents == 0 || p_NumColorComponents > 4)
		return K15_IA_RESULT_INVALID_ARGUMENTS;

	K15_ImageAtlas atlas = {};
	atlas.pixelWidth = 16;
	atlas.pixelHeight = 16;
	atlas.numColorComponents= p_NumColorComponents;

	kia_result result = K15_IAResizeAtlas(&atlas, 16, 16);
	
	if (result != K15_IA_RESULT_SUCCESS)
		return result;

	*p_OutTextureAtlas = atlas;

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
static void K15_IAFreeAtlas(K15_ImageAtlas* p_ImageAtlas)
{
	if (!p_ImageAtlas)
		return;

	K15_IA_FREE(p_ImageAtlas->pixelData);
	K15_IA_FREE(p_ImageAtlas->accessMap);
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
kia_b8 K15_IAFitsAtAccessMapPosition(kia_byte* p_AccessMap, kia_u32 p_AccessMapX, kia_u32 p_AccessMapY,
	kia_u32 p_AccessMapStride, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight)
{
	kia_b8 fits = K15_IA_TRUE;

	for (kia_u32 accessMapY = p_AccessMapY;
		accessMapY < p_PixelDataHeight + p_AccessMapY;
		++accessMapY)
	{
		for (kia_u32 accessMapX = p_AccessMapX;
			accessMapX < p_PixelDataWidth + p_AccessMapX;
			++accessMapX)
		{
			kia_u32 accessMapIndex = (accessMapY * p_AccessMapStride) + accessMapX;

			if (p_AccessMap[accessMapIndex] == K15_IA_ACCESS_MAP_OCCUPIED)
			{
				fits = K15_IA_FALSE;
				goto functionEnd;
			}
		}
	}

functionEnd:
	return fits;
}
/*********************************************************************************/
static void K15_IACopyTextureToAtlas(K15_ImageAtlas* p_ImageAtlas, kia_u32 p_PosX, kia_u32 p_PosY,
	kia_byte* p_PixelData, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight)
{
	kia_byte* accessMap = p_ImageAtlas->accessMap;

	kia_byte* atlasPixelData = p_ImageAtlas->pixelData;

	kia_u8 atlasNumColorComponents = p_ImageAtlas->numColorComponents;
	kia_u32 accessMapStride = p_ImageAtlas->pixelWidth;
	kia_u32 atlasPixelDataStride = p_ImageAtlas->pixelWidth * atlasNumColorComponents;
	kia_u32 pixelDataStride = p_PixelDataWidth * atlasNumColorComponents;

	kia_u32 accessMapIndex = 0;
	kia_u32 atlasPixelDataIndex = 0;
	kia_u32 pixelDataIndex = 0;

	//set access map values & copy texture into atlas
	for (kia_u32 offsetY = p_PosY;
		offsetY < p_PixelDataHeight + p_PosY;
		++offsetY)
	{
		accessMapIndex = (offsetY * accessMapStride) + p_PosX;
		atlasPixelDataIndex = (offsetY * atlasPixelDataStride) + (p_PosX * atlasNumColorComponents);
		pixelDataIndex = ((offsetY - p_PosY) * pixelDataStride);

		K15_IA_MEMSET(accessMap + accessMapIndex, K15_IA_ACCESS_MAP_OCCUPIED, p_PixelDataWidth);
		K15_IA_MEMCPY(atlasPixelData + atlasPixelDataIndex, p_PixelData + pixelDataIndex, pixelDataStride);
	}
}
/*********************************************************************************/
static kia_result K15_IATryToAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas,
	kia_u8 p_NumColorComponents, kia_byte* p_PixelData, kia_u32 p_PixelDataWidth, 
	kia_u32 p_PixelDataHeight, kia_u32* p_OutX, kia_u32* p_OutY)
{
	kia_u8 numAtlasColorComponents = p_ImageAtlas->numColorComponents;
	kia_result result = K15_IA_RESULT_ATLAS_TOO_SMALL;
	if (p_NumColorComponents != numAtlasColorComponents)
	{
		return K15_IA_RESULT_OUT_OF_RANGE;

// 		kta_result result = K15_TAConvertPixelData(p_PixelData, p_NumColorComponents, 
// 			numAtlasColorComponents, p_PixelDataWidth, p_PixelDataHeight);
// 
// 		if (result != K15_TA_RESULT_SUCCESS)
// 			return result;
// 
// 		convertedPixels = K15_TA_TRUE;
	}

	kia_byte* accessMap = p_ImageAtlas->accessMap;
	kia_u32 atlasPixelHeight = p_ImageAtlas->pixelHeight;
	kia_u32 atlasPixelWidth = p_ImageAtlas->pixelWidth;
	kia_u8 atlasNumColorComponents = p_ImageAtlas->numColorComponents;

	kia_u32 atlasPixelStride = atlasPixelWidth * atlasNumColorComponents;
	kia_u32 accessMapIndex = 0;

	//iterate through the access map to find a valid position
	//where we can place the texture
	for (kia_u32 accessMapY = 0;
		accessMapY < atlasPixelHeight;
		++accessMapY)
	{
		//check if there's enough space vertically
		if ((accessMapY + p_PixelDataHeight) > atlasPixelHeight)
			break;

		for (kia_u32 accessMapX = 0;
			accessMapX < atlasPixelWidth;
			++accessMapX)
		{
			//check if there's enough space horizontally
			if ((accessMapX + p_PixelDataWidth) > atlasPixelWidth)
				break;

			accessMapIndex = (accessMapY * atlasPixelWidth) + accessMapX;

			//check access map position (false == occupied | true == free)
			if (accessMap[accessMapIndex] == K15_IA_ACCESS_MAP_OCCUPIED)
				continue;

			//if we reach this point, current access map pos is free 
			//and texture could potentially fit. 
			//Check actual access map bytes to make sure, we can
			//place the texture here.
			if (K15_IAFitsAtAccessMapPosition(accessMap, accessMapX, accessMapY,
				atlasPixelWidth, p_PixelDataWidth, p_PixelDataHeight))
			{
				K15_IACopyTextureToAtlas(p_ImageAtlas, accessMapX, accessMapY,
					p_PixelData, p_PixelDataWidth, p_PixelDataHeight);

				result = K15_IA_RESULT_SUCCESS;

				if (p_OutX)
					*p_OutX = accessMapX;

				if (p_OutY)
					*p_OutY = accessMapY;

				goto functionEnd;
			}
		}
	}

functionEnd:
	return result;
}
/*********************************************************************************/
static kia_result K15_IAAddImageToAtlas(K15_ImageAtlas* p_ImageAtlas, kia_byte* p_PixelData,
	kia_u8 p_NumColorComponents, kia_u32 p_PixelDataWidth, kia_u32 p_PixelDataHeight, 
	kia_u32* p_OutX, kia_u32* p_OutY)
{
	if (!p_ImageAtlas || !p_PixelData || p_NumColorComponents == 0 || 
		p_NumColorComponents > 4 || p_PixelDataWidth == 0 || p_PixelDataHeight == 0)
		return K15_IA_RESULT_INVALID_ARGUMENTS;

	kia_u32 atlasPixelWidth = p_ImageAtlas->pixelWidth;
	kia_u32 atlasPixelHeight = p_ImageAtlas->pixelHeight;

	while (K15_IATryToAddImageToAtlas(p_ImageAtlas, p_NumColorComponents, p_PixelData, 
		p_PixelDataWidth, p_PixelDataHeight, p_OutX, p_OutY) != K15_IA_RESULT_SUCCESS)
	{
		kia_u32 newWidth = atlasPixelWidth > atlasPixelHeight ? atlasPixelWidth : atlasPixelWidth * 2;
		kia_u32 newHeight = atlasPixelWidth > atlasPixelHeight ? atlasPixelHeight * 2 : atlasPixelHeight;
		kia_result result = K15_IA_RESULT_SUCCESS;

		if (newWidth > K15_IA_DIMENSION_THRESHOLD ||
			newHeight > K15_IA_DIMENSION_THRESHOLD)
		{
			result = K15_IA_RESULT_ATLAS_TOO_LARGE;
		}

		result = K15_IAResizeAtlas(p_ImageAtlas, newWidth, newHeight);

		if (result != K15_IA_RESULT_SUCCESS)
			return result;
	}

	return K15_IA_RESULT_SUCCESS;
}
/*********************************************************************************/
static kia_byte* K15_IAGetAtlasPixelData(K15_ImageAtlas* p_ImageAtlas, 
	kia_u32* p_OutWidth, kia_u32* p_OutHeight)
{
	if (!p_ImageAtlas)
		return 0;

	if (p_OutWidth)
		*p_OutWidth = p_ImageAtlas->pixelWidth;

	if (p_OutHeight)
		*p_OutHeight = p_ImageAtlas->pixelHeight;

	return p_ImageAtlas->pixelData;
}
/*********************************************************************************/
kia_u32 K15_IAGetAtlasPixelDataSizeInBytes(K15_ImageAtlas* p_ImageAtlas)
{
	if (!p_ImageAtlas)
		return 0;

	kia_u8 colorComponents = p_ImageAtlas->numColorComponents;
	kia_u32 textureAtlasWidth = p_ImageAtlas->pixelWidth;
	kia_u32 textureAtlasHeight = p_ImageAtlas->pixelHeight;

	return colorComponents * textureAtlasHeight * textureAtlasWidth;
}
/*********************************************************************************/
#endif //K15_IMAGE_ATLAS_IMPLEMENTATION
#endif //_K15_ImageAtlas_h_
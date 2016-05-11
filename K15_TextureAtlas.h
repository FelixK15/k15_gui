#ifndef _K15_ResourceCompiler_TextureAtlas_h_
#define _K15_ResourceCompiler_TextureAtlas_h_

typedef unsigned int kta_u32;
typedef unsigned short kta_u16;
typedef unsigned char kta_u8;
typedef unsigned char kta_b8;
typedef unsigned char kta_byte;

typedef signed int kta_s32;
typedef signed short kta_s16;
typedef signed char kta_s8;

typedef struct _K15_TextureAtlas
{
	kta_u32 pixelWidth;
	kta_u32 pixelHeight;
	
	kta_byte* pixelData;
	kta_byte* accessMap;

	kta_u8 numColorComponents;
} K15_TextureAtlas;

typedef enum _K15_TAResults
{
	K15_TA_RESULT_SUCCESS = 0,
	K15_TA_RESULT_OUT_OF_MEMORY = 1,
	K15_TA_RESULT_OUT_OF_RANGE = 2,
	K15_TA_RESULT_INVALID_ARGUMENTS = 3,
	K15_TA_RESULT_ATLAS_TOO_SMALL = 4,
	K15_TA_RESULT_ATLAS_TOO_LARGE = 5
} kta_result;

kta_result K15_TACreateAtlas(K15_TextureAtlas* p_OutTextureAtlas, kta_u8 p_Components);
void K15_TAFreeAtlas(K15_TextureAtlas* p_TextureAtlas);

kta_result K15_TAAddTextureToAtlas(K15_TextureAtlas* p_TextureAtlas, kta_byte* p_PixelData, 
	kta_u8 p_NumColorComponents, kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight,
	kta_u32* p_OutX, kta_u32* p_OutY);


kta_byte* K15_TAGetAtlasPixelData(K15_TextureAtlas* p_TextureAtlas, kta_u32* p_OutWidth, kta_u32* p_OutHeight);
kta_u32 K15_TAGetAtlasPixelDataSizeInBytes(K15_TextureAtlas* p_TextureAtlas);

#ifdef K15_TA_IMPLEMENTATION

#define K15_TA_TRUE 1
#define K15_TA_FALSE 0

#define K15_TA_ACCESS_MAP_FREE 0x00
#define K15_TA_ACCESS_MAP_OCCUPIED 0xFF
 
#ifndef K15_TA_DIMENSION_THRESHOLD
# define K15_TA_DIMENSION_THRESHOLD 2048
#endif //K15_TA_DIMENSION_THRESHOLD

#ifndef internal
# define internal static
#endif //internal

#ifndef K15_TA_MALLOC
# include <stdlib.h>
# define K15_TA_MALLOC malloc
# define K15_TA_FREE free
#endif //K15_TA_MALLOC

#ifndef K15_TA_MEMCPY
# include <string.h>
# define K15_TA_MEMCPY memcpy
#endif //K15_TA_MEMCPY

#ifndef K15_TA_MEMCMP
# include <string.h>
# define K15_TA_MEMCMP memcmp
#endif //K15_TA_MEMCMP

#ifndef K15_TA_MEMSET
# include <string.h>
# define K15_TA_MEMSET memset
#endif //K15_TA_MEMSET

/*********************************************************************************/
static void K15_TACopyAtlasData(K15_TextureAtlas* p_TextureAtlas, kg_u32 p_DestinationPixelWidth,
	kg_u32 p_DestinationPixelHeight, kg_byte* p_DestinationAccessMap, kg_byte* p_DestinationPixelData)
{
	kg_u32 numColorComponents = p_TextureAtlas->numColorComponents;
	kg_u32 atlasPixelHeight = p_TextureAtlas->pixelHeight;
	kg_u32 sourcePixelDataStride = p_TextureAtlas->pixelWidth * numColorComponents;
	kg_u32 destinationPixelDataStride = p_DestinationPixelWidth * numColorComponents;
	kg_u32 destinationAccessMapStride = p_DestinationPixelWidth;
	kg_u32 sourceAccessMapStride = p_TextureAtlas->pixelWidth;
	kg_u32 sourcePixelDataOffset = 0;
	kg_u32 destinationPixelDataOffset = 0;
	kg_u32 sourceAccessMapOffset = 0;
	kg_u32 destinationAccessMapOffset = 0;

	kg_byte* sourceAccessMap = p_TextureAtlas->accessMap;
	kg_byte* sourcePixelData = p_TextureAtlas->pixelData;

	for (kg_u32 verticalIndex = 0;
		verticalIndex < atlasPixelHeight;
		++verticalIndex)
	{
		K15_TA_MEMCPY(p_DestinationAccessMap + destinationAccessMapOffset,
			sourceAccessMap + sourceAccessMapOffset,
			sourceAccessMapStride);
	
		K15_TA_MEMCPY(p_DestinationPixelData + destinationPixelDataOffset,
			sourcePixelData + sourcePixelDataOffset,
			sourcePixelDataStride);

		sourceAccessMapOffset += sourceAccessMapStride;
		sourcePixelDataOffset += sourcePixelDataStride;

		destinationAccessMapOffset += destinationAccessMapStride;
		destinationPixelDataOffset += destinationPixelDataStride;
	}
}
/*********************************************************************************/
static kta_result K15_TAResizeAtlas(K15_TextureAtlas* p_TextureAtlas, 
	kg_u32 p_DesiredPixelWidth, kg_u32 p_DesiredPixelHeight)
{
	if (p_DesiredPixelHeight < p_TextureAtlas->pixelHeight ||
		p_DesiredPixelWidth < p_TextureAtlas->pixelWidth)
	{
		return K15_TA_RESULT_INVALID_ARGUMENTS;
	}

	kg_u32 numColorComponents = p_TextureAtlas->numColorComponents;
	kg_u32 numPixels = p_DesiredPixelWidth * p_DesiredPixelHeight;
	kg_u32 numPixelBytes = numPixels * numColorComponents;

	kta_byte* accessMapMemory = (kta_byte*)K15_TA_MALLOC(numPixels);
	kta_byte* pixelDataMemory = (kta_byte*)K15_TA_MALLOC(numPixelBytes);

	if (!accessMapMemory || !pixelDataMemory)
		return K15_TA_RESULT_OUT_OF_MEMORY;

	K15_TA_MEMSET(accessMapMemory, 0, numPixels);
	K15_TA_MEMSET(pixelDataMemory, 0, numPixelBytes);

	if (p_TextureAtlas->accessMap &&
		p_TextureAtlas->pixelData)
	{
		K15_TACopyAtlasData(p_TextureAtlas, p_DesiredPixelWidth, p_DesiredPixelHeight, 
			accessMapMemory, pixelDataMemory);
	}

	p_TextureAtlas->accessMap = accessMapMemory;
	p_TextureAtlas->pixelData = pixelDataMemory;
	p_TextureAtlas->pixelHeight = p_DesiredPixelHeight;
	p_TextureAtlas->pixelWidth = p_DesiredPixelWidth;

	return K15_TA_RESULT_SUCCESS;
}
/*********************************************************************************/
static kta_result K15_TACreateAtlas(K15_TextureAtlas* p_OutTextureAtlas, kta_u8 p_NumColorComponents)
{
	if (!p_OutTextureAtlas || p_NumColorComponents == 0 || p_NumColorComponents > 4)
		return K15_TA_RESULT_INVALID_ARGUMENTS;

	K15_TextureAtlas atlas = {};
	atlas.pixelWidth = 16;
	atlas.pixelHeight = 16;
	atlas.numColorComponents= p_NumColorComponents;

	K15_TAResizeAtlas(&atlas, 16, 16);
	
	*p_OutTextureAtlas = atlas;

	return K15_TA_RESULT_SUCCESS;
}
/*********************************************************************************/
static void K15_TAFreeAtlas(K15_TextureAtlas* p_TextureAtlas)
{
	if (!p_TextureAtlas)
		return;

	K15_TA_FREE(p_TextureAtlas->pixelData);
	K15_TA_FREE(p_TextureAtlas->accessMap);
}
/*********************************************************************************/
static kta_result K15_TAConvertPixelData(kta_byte* p_SourcePixelData, kta_u8 p_SourceNumColorComponents, 
	kta_u8 p_DestinationNumColorComponents, kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight)
{
	if (!p_SourcePixelData || p_SourceNumColorComponents == 0 || p_SourceNumColorComponents > 4 ||
		p_DestinationNumColorComponents == 0 || p_DestinationNumColorComponents > 4 ||
		p_PixelDataHeight == 0 || p_PixelDataWidth == 0)
	{
		return K15_TA_RESULT_INVALID_ARGUMENTS;
	}

	kta_u32 numPixels = p_PixelDataWidth * p_PixelDataHeight;
	kta_u32 destinationPixelDataSizeInBytes = p_DestinationNumColorComponents * numPixels;
	kta_byte* destinationPixelData = (kta_byte*)K15_TA_MALLOC(destinationPixelDataSizeInBytes);

	if (!destinationPixelData)
		return K15_TA_RESULT_OUT_OF_MEMORY;

	//convert pixel by pixel
	for (kta_u32 pixelIndex = 0;
		pixelIndex < numPixels;
		++pixelIndex)
	{
		//TODO
	}

	return K15_TA_RESULT_SUCCESS;
}
/*********************************************************************************/
kta_b8 K15_TAFitsAtAccessMapPosition(kta_byte* p_AccessMap, kta_u32 p_AccessMapX, kta_u32 p_AccessMapY,
	kta_u32 p_AccessMapStride, kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight)
{
	kta_b8 fits = K15_TA_TRUE;

	for (kta_u32 accessMapY = p_AccessMapY;
		accessMapY < p_PixelDataHeight + p_AccessMapY;
		++accessMapY)
	{
		for (kta_u32 accessMapX = p_AccessMapX;
			accessMapX < p_PixelDataWidth + p_AccessMapX;
			++accessMapX)
		{
			kta_u32 accessMapIndex = (accessMapY * p_AccessMapStride) + accessMapX;

			if (p_AccessMap[accessMapIndex] == K15_TA_ACCESS_MAP_OCCUPIED)
			{
				fits = K15_TA_FALSE;
				goto functionEnd;
			}
		}
	}

functionEnd:
	return fits;
}
/*********************************************************************************/
static void K15_TACopyTextureToAtlas(K15_TextureAtlas* p_TextureAtlas, kta_u32 p_PosX, kta_u32 p_PosY,
	kta_byte* p_PixelData, kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight)
{
	kta_byte* accessMap = p_TextureAtlas->accessMap;

	kta_byte* atlasPixelData = p_TextureAtlas->pixelData;

	kta_u8 atlasNumColorComponents = p_TextureAtlas->numColorComponents;
	kta_u32 accessMapStride = p_TextureAtlas->pixelWidth;
	kta_u32 atlasPixelDataStride = p_TextureAtlas->pixelWidth * atlasNumColorComponents;
	kta_u32 pixelDataStride = p_PixelDataWidth * atlasNumColorComponents;

	kta_u32 accessMapIndex = 0;
	kta_u32 atlasPixelDataIndex = 0;
	kta_u32 pixelDataIndex = 0;

	//set access map values & copy texture into atlas
	for (kta_u32 offsetY = p_PosY;
		offsetY < p_PixelDataHeight + p_PosY;
		++offsetY)
	{
		accessMapIndex = (offsetY * accessMapStride) + p_PosX;
		atlasPixelDataIndex = (offsetY * atlasPixelDataStride) + (p_PosX * atlasNumColorComponents);
		pixelDataIndex = ((offsetY - p_PosY) * pixelDataStride);

		K15_TA_MEMSET(accessMap + accessMapIndex, K15_TA_ACCESS_MAP_OCCUPIED, p_PixelDataWidth);
		K15_TA_MEMCPY(atlasPixelData + atlasPixelDataIndex, p_PixelData + pixelDataIndex, pixelDataStride);
	}
}
/*********************************************************************************/
static kta_result K15_TATryToAddTextureToAtlas(K15_TextureAtlas* p_TextureAtlas,
	kta_u8 p_NumColorComponents, kta_byte* p_PixelData, kta_u32 p_PixelDataWidth, 
	kta_u32 p_PixelDataHeight, kta_u32* p_OutX, kta_u32* p_OutY)
{
	kta_u8 numAtlasColorComponents = p_TextureAtlas->numColorComponents;
	kta_result result = K15_TA_RESULT_ATLAS_TOO_SMALL;
	if (p_NumColorComponents != numAtlasColorComponents)
	{
		return K15_TA_RESULT_OUT_OF_RANGE;

// 		kta_result result = K15_TAConvertPixelData(p_PixelData, p_NumColorComponents, 
// 			numAtlasColorComponents, p_PixelDataWidth, p_PixelDataHeight);
// 
// 		if (result != K15_TA_RESULT_SUCCESS)
// 			return result;
// 
// 		convertedPixels = K15_TA_TRUE;
	}

	kta_byte* accessMap = p_TextureAtlas->accessMap;
	kta_u32 atlasPixelHeight = p_TextureAtlas->pixelHeight;
	kta_u32 atlasPixelWidth = p_TextureAtlas->pixelWidth;
	kta_u8 atlasNumColorComponents = p_TextureAtlas->numColorComponents;

	kta_u32 atlasPixelStride = atlasPixelWidth * atlasNumColorComponents;
	kta_u32 accessMapIndex = 0;

	//iterate through the access map to find a valid position
	//where we can place the texture
	for (kta_u32 accessMapY = 0;
		accessMapY < atlasPixelHeight;
		++accessMapY)
	{
		//check if there's enough space vertically
		if ((accessMapY + p_PixelDataHeight) > atlasPixelHeight)
			break;

		for (kta_u32 accessMapX = 0;
			accessMapX < atlasPixelWidth;
			++accessMapX)
		{
			//check if there's enough space horizontally
			if ((accessMapX + p_PixelDataWidth) > atlasPixelWidth)
				break;

			accessMapIndex = (accessMapY * atlasPixelWidth) + accessMapX;

			//check access map position (false == occupied | true == free)
			if (accessMap[accessMapIndex] == K15_TA_ACCESS_MAP_OCCUPIED)
				continue;

			//if we reach this point, current access map pos is free 
			//and texture could potentially fit. 
			//Check actual access map bytes to make sure, we can
			//place the texture here.
			if (K15_TAFitsAtAccessMapPosition(accessMap, accessMapX, accessMapY,
				atlasPixelWidth, p_PixelDataWidth, p_PixelDataHeight))
			{
				K15_TACopyTextureToAtlas(p_TextureAtlas, accessMapX, accessMapY,
					p_PixelData, p_PixelDataWidth, p_PixelDataHeight);

				result = K15_TA_RESULT_SUCCESS;

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
static kta_result K15_TAAddTextureToAtlas(K15_TextureAtlas* p_TextureAtlas, kta_byte* p_PixelData,
	kta_u8 p_NumColorComponents, kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight, 
	kta_u32* p_OutX, kta_u32* p_OutY)
{
	if (!p_TextureAtlas || !p_PixelData || p_NumColorComponents == 0 || 
		p_NumColorComponents > 4 || p_PixelDataWidth == 0 || p_PixelDataHeight == 0)
		return K15_TA_RESULT_INVALID_ARGUMENTS;

	kta_u32 atlasPixelWidth = p_TextureAtlas->pixelWidth;
	kta_u32 atlasPixelHeight = p_TextureAtlas->pixelHeight;

	while (K15_TATryToAddTextureToAtlas(p_TextureAtlas, p_NumColorComponents, p_PixelData, 
		p_PixelDataWidth, p_PixelDataHeight, p_OutX, p_OutY) != K15_TA_RESULT_SUCCESS)
	{
		kta_u32 newWidth = atlasPixelWidth > atlasPixelHeight ? atlasPixelWidth : atlasPixelWidth * 2;
		kta_u32 newHeight = atlasPixelWidth > atlasPixelHeight ? atlasPixelHeight * 2 : atlasPixelHeight;
		kta_result result = K15_TA_RESULT_SUCCESS;

		if (newWidth > K15_TA_DIMENSION_THRESHOLD ||
			newHeight > K15_TA_DIMENSION_THRESHOLD)
		{
			result = K15_TA_RESULT_ATLAS_TOO_LARGE;
		}

		result = K15_TAResizeAtlas(p_TextureAtlas, newWidth, newHeight);

		if (result != K15_TA_RESULT_SUCCESS)
			return result;
	}

	return K15_TA_RESULT_SUCCESS;
}
/*********************************************************************************/
static kta_byte* K15_TAGetAtlasPixelData(K15_TextureAtlas* p_TextureAtlas, 
	kta_u32* p_OutWidth, kta_u32* p_OutHeight)
{
	if (!p_TextureAtlas)
		return 0;

	if (p_OutWidth)
		*p_OutWidth = p_TextureAtlas->pixelWidth;

	if (p_OutHeight)
		*p_OutHeight = p_TextureAtlas->pixelHeight;

	return p_TextureAtlas->pixelData;
}
/*********************************************************************************/
kta_u32 K15_TAGetAtlasPixelDataSizeInBytes(K15_TextureAtlas* p_TextureAtlas)
{
	if (!p_TextureAtlas)
		return 0;

	kta_u8 colorComponents = p_TextureAtlas->numColorComponents;
	kta_u32 textureAtlasWidth = p_TextureAtlas->pixelWidth;
	kta_u32 textureAtlasHeight = p_TextureAtlas->pixelHeight;

	return colorComponents * textureAtlasHeight * textureAtlasWidth;
}
/*********************************************************************************/
#endif //K15_TEXTURE_ATLAS_IMPLEMENTATION
#endif //_K15_ResourceCompiler_TextureAtlas_h_
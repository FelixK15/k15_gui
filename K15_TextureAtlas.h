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
	kta_u32 numColorComponents;
	
	kta_byte* pixelData;
	kta_byte* accessMap;
} K15_TextureAtlas;

typedef enum _K15_TAResults
{
	K15_TA_RESULT_SUCCESS = 0,
	K15_TA_RESULT_OUT_OF_MEMORY = 1,
	K15_TA_RESULT_OUT_OF_RANGE = 2,
	K15_TA_RESULT_TEXTURE_AREA_IS_ZERO = 3,
	K15_TA_RESULT_INVALID_ARGUMENTS = 4
} kta_result;

kta_result K15_TACreateAtlas(K15_TextureAtlas* p_OutTextureAtlas, kta_u8 p_Components);
void K15_TAFreeAtlas(K15_TextureAtlas* p_TextureAtlas);

kta_result K15_TAAddTextureToAtlas(K15_TextureAtlas* p_TextureAtlas, kta_byte* p_PixelData, 
	kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight, kta_u32 p_TextureIndex, 
	kta_u32* p_OutX, kta_u32* p_OutY);


kta_byte* K15_TAGetAtlasPixelData(K15_TextureAtlas* p_TextureAtlas, kta_u32* p_OutWidth, kta_u32* p_OutHeight);
kta_u32 K15_TAGetAtlasPixelDataSizeInBytes(K15_TextureAtlas* p_TextureAtlas);

#ifdef K15_TA_IMPLEMENTATION

#define KTA_TRUE 1
#define KTA_FALSE 0

#ifndef internal
# define internal static
#endif //internal

#ifndef K15_TA_MALLOC
# include <stdlib.h>
# define K15_TA_MALLOC malloc
# define K15_TA_FREE free
#endif //K15_TA_MALLOC

#ifndef K15_TA_MEMCPY
# include <stdlib.h>
# define K15_TA_MEMCPY memcpy
#endif //K15_TA_MEMCPY

#ifndef K15_TA_MEMSET
# include <stdlib.h>
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
static kta_b8 K15_TATryToAddTextureToAtlas(K15_TextureAtlas* p_TextureAtlas,
	kta_byte* p_PixelData, kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight,
	kta_u32* p_OutX, kta_u32* p_OutY)
{
	kta_byte* accessMap = p_TextureAtlas->accessMap;

	//TODO add pixeldata to atlas
}
/*********************************************************************************/
static kta_result K15_TAAddTextureToAtlas(K15_TextureAtlas* p_TextureAtlas, kta_byte* p_PixelData,
	kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight, kta_u32* p_OutX, kta_u32* p_OutY)
{
	if (!p_TextureAtlas || !p_PixelData || p_PixelDataHeight == 0 || p_PixelDataWidth == 0)
		return K15_TA_RESULT_INVALID_ARGUMENTS;

	if (p_PixelDataWidth == 0 ||
		p_PixelDataHeight == 0)
	{
		return K15_TA_RESULT_TEXTURE_AREA_IS_ZERO;
	}

	kta_u32 atlasPixelWidth = p_TextureAtlas->pixelWidth;
	kta_u32 atlasPixelHeight = p_TextureAtlas->pixelHeight;

	while (!K15_TATryToAddTextureToAtlas(p_TextureAtlas, p_PixelData, p_PixelDataWidth, p_PixelDataHeight,
		p_OutX, p_OutY))
	{
		kta_u32 newWidth = atlasPixelWidth > atlasPixelHeight ? atlasPixelWidth : atlasPixelWidth * 2;
		kta_u32 newHeight = atlasPixelWidth > atlasPixelHeight ? atlasPixelHeight * 2 : atlasPixelHeight;
		kta_result result = K15_TAResizeAtlas(p_TextureAtlas, newWidth, newHeight);

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
#ifndef _K15_ResourceCompiler_TextureAtlas_h_
#define _K15_ResourceCompiler_TextureAtlas_h_

#define K15_TA_RESULT_SUCCESS 0
#define K15_TA_RESULT_OUT_OF_MEMORY 1
#define K15_TA_RESULT_OUT_OF_RANGE 2
#define K15_TA_RESULT_TEXTURE_AREA_IS_ZERO 3
#define K15_TA_RESULT_INVALID_ARGUMENTS 4

typedef unsigned int kta_u32;
typedef unsigned short kta_u16;
typedef unsigned char kta_u8;

typedef unsigned char kta_b8;

typedef signed int kta_s32;
typedef signed short kta_s16;
typedef signed char kta_s8;

typedef unsigned int kta_result;

typedef unsigned char kta_byte;

typedef struct _K15_TextureAtlasNode
{
	kta_u32 x;
	kta_u32 y;
	kta_u32 width;
	kta_u32 height;
	kta_u32 area;
	kta_byte* pixelData;
} K15_TextureAtlasNode;

typedef struct _K15_TextureAtlas
{
	kta_u32 width;
	kta_u32 height;
	kta_u32 numComponents;
	kta_u32 numNodes;
	
	kta_byte* pixelData;
	kta_byte* accessMap;
	K15_TextureAtlasNode* atlasNodes;
} K15_TextureAtlas;

kta_result K15_TACreateAtlas(K15_TextureAtlas* p_OutTextureAtlas, kta_u8 p_Components);
void K15_TAFreeAtlas(K15_TextureAtlas* p_TextureAtlas);

kta_result K15_TASetTextureCount(K15_TextureAtlas* p_TextureAtlas, unsigned int p_TextureCount);

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
internal kta_s32 K15_InternalSortTextureAtlasNodesByArea(const void* p_NodeA, const void* p_NodeB)
{
	K15_TextureAtlasNode* nodeA = (K15_TextureAtlasNode*)p_NodeA;
	K15_TextureAtlasNode* nodeB = (K15_TextureAtlasNode*)p_NodeB;

	return nodeB->area - nodeA->area;
}
/*********************************************************************************/
internal void K15_InternalSetAccessFlag(kta_byte* p_AccessMap, kta_u32 p_PosX, kta_u32 p_PosY, 
	kta_u32 p_Width, kta_u32 p_Height, kta_u32 p_Stride)
{
	kta_u32 index = p_PosY * p_Stride + p_PosX;

	for (kta_u32 y = p_PosY;
		y < p_Height + p_PosY;
		++y)
	{
		K15_TA_MEMSET(p_AccessMap + index, 1, p_Width);
		index += p_Stride;
	}
}
/*********************************************************************************/
internal void K15_InternalSetBitmap(kta_byte* p_AtlasBitmap, kta_byte* p_NodeBitmap, 
	kta_u32 p_NumAtlasColorComponents, kta_u32 p_PosX, kta_u32 p_PosY, 
	kta_u32 p_NodeWidth, kta_u32 p_NodeHeight, kta_u32 p_Stride)
{
	const kta_u32 nodeBitmapStride = p_NodeWidth;
	kta_u32 bitmapIndex = p_PosY * p_Stride + p_PosX;

	for (kta_u32 y = p_PosY;
		y < p_PosY + p_NodeHeight;
		++y)
	{
		K15_TA_MEMCPY(p_AtlasBitmap + bitmapIndex, p_NodeBitmap + (y-p_PosY) * nodeBitmapStride, nodeBitmapStride);
		bitmapIndex += p_Stride;
	}
}
/*********************************************************************************/
internal kta_b8 K15_InternalAddTextureNodeToTexture(K15_TextureAtlas* p_TextureAtlas, 
	K15_TextureAtlasNode* p_TextureAtlasNode, kta_byte* p_AtlasBitmap, kta_byte* p_AccessMap, 
	kta_u32* p_OutPosX, kta_u32* p_OutPosY)
{
	const kta_u32 atlasWidth = p_TextureAtlas->width;
	const kta_u32 atlasHeight = p_TextureAtlas->height;
	const kta_u32 nodeWidth = p_TextureAtlasNode->width;	
	const kta_u32 nodeHeight = p_TextureAtlasNode->height;
	const kta_u32 nodeArea = p_TextureAtlasNode->area;
	const kta_u32 stride = p_TextureAtlas->width;
	const kta_u32 numAtlasColorComponents = p_TextureAtlas->numComponents;
	kta_byte* nodeBitmap = p_TextureAtlasNode->pixelData;

	kta_u32 posY = 0;
	kta_u32 posX = 0;
	kta_u32 counter = 0;

	const kta_u32 maxAccessIndex = p_TextureAtlas->width * p_TextureAtlas->height;
	kta_b8 foundPossibleMatch = KTA_TRUE;
	kta_b8 foundMatch = KTA_FALSE;

	//find next free item in the access map
	for (kta_u32 accessIndex = 0;
		accessIndex < maxAccessIndex;
		++accessIndex)
	{
		foundPossibleMatch = KTA_TRUE;

		if (p_AccessMap[accessIndex] == 0)
		{
			//try to insert
			posY = accessIndex / stride;
			posX = accessIndex - (posY * stride);
			counter = 0;

			if (posY + nodeHeight > atlasHeight ||
				posX + nodeWidth > atlasWidth)
			{
				foundPossibleMatch = KTA_FALSE;
				continue;
			}

			for (kta_u32 y = posY;
				y < nodeHeight + posY;
				++y)
			{
				for (kta_u32 x = posX;
					x < nodeWidth + posX;
					++x, ++counter)
				{
					const kta_u32 index = y * stride + x;

					if (p_AccessMap[index] != 0)
					{
						foundPossibleMatch = KTA_FALSE;
						break;
					}
				}

				if (counter == nodeArea)
				{
					*p_OutPosX = posX;
					*p_OutPosY = posY;
					foundMatch = KTA_TRUE;
					break;
				}

				if (!foundPossibleMatch)
				{
					break;
				}
			}

			if (foundMatch)
			{
				break;
			}
		}

		if (foundMatch)
		{
			break;
		}
	}
	

	if (foundMatch)
	{
		K15_InternalSetAccessFlag(p_AccessMap, posX, posY, nodeWidth, nodeHeight, stride);
		K15_InternalSetBitmap(p_AtlasBitmap, nodeBitmap, numAtlasColorComponents, posX, posY, 
			nodeWidth, nodeHeight, stride);
	}

	return foundMatch;
}
/*********************************************************************************/
internal kta_result K15_InternalResizeTextureAtlas(K15_TextureAtlas* p_TextureAtlas)
{
	kta_u32 oldWidth = p_TextureAtlas->width;
	kta_u32 oldHeight = p_TextureAtlas->height;

	kta_u32 newWidth = oldWidth * 2;
	kta_u32 newHeight = oldHeight * 2;

	kta_byte* oldAtlasBitmap = p_TextureAtlas->pixelData;
	kta_byte* oldAccessMap = p_TextureAtlas->accessMap;
	kta_byte* newAtlasBitmap = (kta_byte*)K15_TA_MALLOC(newWidth * newHeight * p_TextureAtlas->numComponents);
	kta_byte* newAccessMap = (kta_byte*)K15_TA_MALLOC(newWidth * newHeight);

	if (!newAccessMap || !newAtlasBitmap)
		return K15_TA_RESULT_OUT_OF_MEMORY;

	K15_TA_MEMSET(newAccessMap, 0, newWidth * newHeight);

	kta_u32 oldStride = oldWidth;
	kta_u32 newStride = newWidth;

	for (kta_u32 y = 0;
		y < oldWidth;
		++y)
	{
		K15_TA_MEMCPY(newAtlasBitmap + newStride * y, oldAtlasBitmap + oldStride * y, 
			oldStride * p_TextureAtlas->numComponents);
		
		K15_TA_MEMCPY(newAccessMap + newStride * y, oldAccessMap + oldStride * y, oldStride);
	}

	K15_TA_FREE(oldAtlasBitmap);
	K15_TA_FREE(oldAccessMap);

	p_TextureAtlas->pixelData = newAtlasBitmap;
	p_TextureAtlas->accessMap = newAccessMap;

	p_TextureAtlas->width = newWidth;
	p_TextureAtlas->height = newHeight;

	return K15_TA_RESULT_SUCCESS;
}
/*********************************************************************************/
static kta_result K15_TACreateAtlas(K15_TextureAtlas* p_OutTextureAtlas, kta_u8 p_Components)
{
	if (!p_OutTextureAtlas || p_Components == 0)
		return K15_TA_RESULT_INVALID_ARGUMENTS;

	K15_TextureAtlas atlas = {};
	atlas.width = 16;
	atlas.height = 16;
	atlas.numComponents = p_Components;
	atlas.numNodes = 0;

	kta_byte* accessMapMemory = (kta_byte*)K15_TA_MALLOC(16 * 16);
	kta_byte* pixelDataMemory = (kta_byte*)K15_TA_MALLOC(16 * 16 * p_Components);

	if (!accessMapMemory || !pixelDataMemory)
		return K15_TA_RESULT_OUT_OF_MEMORY;

	K15_TA_MEMSET(accessMapMemory, 0, 16*16);
	K15_TA_MEMSET(pixelDataMemory, 0, 16*16 * p_Components);

	atlas.accessMap = accessMapMemory;
	atlas.pixelData = pixelDataMemory;

	return K15_TA_RESULT_SUCCESS;
}
/*********************************************************************************/
static void K15_TAFreeAtlas(K15_TextureAtlas* p_TextureAtlas)
{
	if (!p_TextureAtlas)
		return;

	K15_TA_FREE(p_TextureAtlas->pixelData);
	K15_TA_FREE(p_TextureAtlas->atlasNodes);
	K15_TA_FREE(p_TextureAtlas->accessMap);
}
/*********************************************************************************/
static kta_result K15_TASetTextureCount(K15_TextureAtlas* p_TextureAtlas, kta_u32 p_TextureCount)
{
	if (!p_TextureAtlas || p_TextureCount == 0)
		return K15_TA_RESULT_INVALID_ARGUMENTS;

	if (p_TextureAtlas->atlasNodes)
	{
		K15_TA_FREE(p_TextureAtlas->atlasNodes);
	}

	K15_TextureAtlasNode* atlasNodesMemory = 
		(K15_TextureAtlasNode*)K15_TA_MALLOC(sizeof(K15_TextureAtlasNode) * p_TextureCount);

	if (!atlasNodesMemory)
		return K15_TA_RESULT_OUT_OF_MEMORY;

	p_TextureAtlas->atlasNodes = atlasNodesMemory;
	p_TextureAtlas->numNodes = p_TextureCount;

	return K15_TA_RESULT_SUCCESS;
}
/*********************************************************************************/
static kta_result K15_TAAddTextureToAtlas(K15_TextureAtlas* p_TextureAtlas, kta_byte* p_PixelData,
	kta_u32 p_PixelDataWidth, kta_u32 p_PixelDataHeight, kta_u32 p_TextureIndex,
	kta_u32* p_OutX, kta_u32* p_OutY)
{
	if (!p_TextureAtlas || !p_PixelData || p_PixelDataHeight == 0 || p_PixelDataWidth == 0)
		return K15_TA_RESULT_INVALID_ARGUMENTS;

	if (p_TextureAtlas->numNodes >= p_TextureIndex)
		return K15_TA_RESULT_OUT_OF_RANGE;

	if (p_PixelDataWidth == 0 ||
		p_PixelDataHeight == 0)
	{
		return K15_TA_RESULT_TEXTURE_AREA_IS_ZERO;
	}

	K15_TextureAtlasNode* node = &p_TextureAtlas->atlasNodes[p_TextureIndex];

	node->area = p_PixelDataWidth * p_PixelDataHeight;
	node->height = p_PixelDataHeight;
	node->width = p_PixelDataWidth;
	node->x = 0;
	node->y = 0;
	node->pixelData = p_PixelData;

	while (!K15_InternalAddTextureNodeToTexture(p_TextureAtlas, node, p_TextureAtlas->pixelData, p_TextureAtlas->accessMap, &node->x, &node->y))
	{
		kta_result result = K15_InternalResizeTextureAtlas(p_TextureAtlas);

		if (result != K15_TA_RESULT_SUCCESS)
			return result;
	}

	if (p_OutX)
	{
		*p_OutX = node->x;
	}

	if (p_OutY)
	{
		*p_OutY = node->y;
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
		*p_OutWidth = p_TextureAtlas->width;

	if (p_OutHeight)
		*p_OutHeight = p_TextureAtlas->height;

	return p_TextureAtlas->pixelData;
}
/*********************************************************************************/
kta_u32 K15_TAGetAtlasPixelDataSizeInBytes(K15_TextureAtlas* p_TextureAtlas)
{
	if (!p_TextureAtlas)
		return 0;

	kta_u8 colorComponents = p_TextureAtlas->numComponents;
	kta_u32 textureAtlasWidth = p_TextureAtlas->width;
	kta_u32 textureAtlasHeight = p_TextureAtlas->height;

	return colorComponents * textureAtlasHeight * textureAtlasWidth;
}
/*********************************************************************************/
#endif //K15_TEXTURE_ATLAS_IMPLEMENTATION
#endif //_K15_ResourceCompiler_TextureAtlas_h_
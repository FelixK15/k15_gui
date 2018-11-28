#include "ui_true_type.hpp"

#include "keen/base/endianness.hpp"
#include "keen/base/string.hpp"
#include "keen/base/memory_allocator.hpp"

#include <stdio.h>

namespace keen
{

	KEEN_DEFINE_BOOL_VARIABLE( s_useCustomCapHeight, "UseCustomCapHeight", true, "" );	

	enum
	{
		TrueTypeSFNT_TrueType1 			= 0x00010000,
		TrueTypeSFNT_TrueType2 			= 0x74727565,
		TrueTypeSFNT_OpenType			= KEEN_FOURCC( 'O', 'T', 'T', 'O' ),

		TrueTypeDataOffset_TableDirectory	= 12u,	//FK: Absolute offset
		TrueTypeDataOffset_MagicNumber		= 12u,	//FK: Relative to 'head' table
		TrueTypeDataOffset_IndexToLoca		= 50u,	//FK: Relative to 'head' table
		TrueTypeDataOffset_Flags			= 16u,	//FK: Relative to 'head' table

		InvalidCharStringStackIndex = -1
	};

	enum TrueTypeFlags
	{
		TrueTypeFlag_LeftSideBearingFromTable = (1 << 1)
	};

	enum TrueTypeLanguageId
	{
		TrueTypeLanguageId_English = 0u
	};

	enum TrueTypeNameId
	{
		TrueTypeNameId_FontFamily		= 1u,
		TrueTypeNameId_FontSubFamily	= 2u,
		TrueTypeNameId_FontName			= 4u
	};

	enum TrueTypePlatformID
	{
		TrueTypePlatformID_Unicode		= 0,
		TrueTypePlatformID_Microsoft	= 3
	};

	enum TrueTypeMicrosoftEncodingID
	{
		TrueTypeMicrosoftEncodingID_Symbol			= 0,
		TrueTypeMicrosoftEncodingID_Unicode_BMP		= 1,
		TrueTypeMicrosoftEncodingID_ShiftJis		= 2,
		TrueTypeMicrosoftEncodingID_Unicode_Full	= 10
	};

	enum TrueTypeComponentFlag
	{
		TrueTypeComponentFlag_Arg1_and_2_are_words		= 1 << 0u,
		TrueTypeComponentFlag_Args_are_xy_values		= 1 << 1u,
		TrueTypeComponentFlag_Round_xy_to_grid			= 1 << 2u,
		TrueTypeComponentFlag_We_have_a_scale			= 1 << 3u,
		//THIS_FLAG_IS_DEPRECATED						= 1 << 4u
		TrueTypeComponentFlag_More_components			= 1 << 5u,
		TrueTypeComponentFlag_We_have_an_x_and_y_scale	= 1 << 6u,
		TrueTypeComponentFlag_We_have_a_two_by_two		= 1 << 7u,
		TrueTypeComponentFlag_We_have_instructions		= 1 << 8u, //FK: Do we really care?
		TrueTypeComponentFlag_Use_my_metrics			= 1 << 9u,
		TrueTypeComponentFlag_Overlap_compound			= 1 << 10u
	};
	
	enum TrueTypeBitmapFlag
	{
		TrueTypeBitmapFlag_HorizontalMetrics	= 1 << 0u,
		TrueTypeBitmapFlag_VerticalMetrics		= 1 << 1u
	};

	enum TrueTypeCFFKeys
	{
		CFFKey_CharStringOffset			= 17,
		CFFKey_PrivateDict				= 18,
		CFFKey_CharStringType			= 0x100 | 6,
		CFFKey_FontDictOffset			= 0x100 | 36,
		CFFKey_FontDictSelectOffset		= 0x100 | 37
	};

	enum 
	{
		TrueType_MagicNumber = 0x5F0F3CF5
	};

	enum TrueTypeCFFOperations
	{
		op_hstem		= 0x01,
		op_vstem		= 0x03, 
		op_and			= 0x0c03,
		op_vmoveto		= 0x04, 
		op_or			= 0x0c04,
		op_rlineto		= 0x05,
		op_not			= 0x0c05,
		op_hlineto		= 0x06, 
		op_vlineto		= 0x07, 
		op_rrcurveto	= 0x08,
		op_abs			= 0x0c09,
		op_callsubr		= 0x0a, 
		op_add			= 0x0c0a,
		op_return		= 0x0b, 
		op_sub			= 0x0c0b,
		op_div			= 0x0c0c,
		op_endchar		= 0x0e, 
		op_neg			= 0x0c0e,
		op_cff2vsidx	= 0x0f, 
		op_eq			= 0x0c0f,
		op_cff2blend	= 0x10, 
		op_hstemhm		= 0x12, 
		op_drop			= 0x0c12,
		op_hintmask		= 0x13, 
		op_cntrmask		= 0x14, 
		op_put			= 0x0c14,
		op_rmoveto		= 0x15, 
		op_get			= 0x0c15,
		op_hmoveto		= 0x16, 
		op_ifelse		= 0x0c16,
		op_vstemhm		= 0x17, 
		op_random		= 0x0c17,
		op_rcurveline	= 0x18, 
		op_mul			= 0x0c18,
		op_rlinecurve	= 0x19, 
		op_vvcurveto	= 0x1a, 
		op_sqrt			= 0x0c1a,
		op_hhcurveto	= 0x1b, 
		op_dup			= 0x0c1b,
		op_exch			= 0x0c1c,
		op_callgsubr	= 0x1d, 
		op_index		= 0x0c1d,
		op_vhcurveto	= 0x1e, 
		op_roll			= 0x0c1e,
		op_hvcurveto	= 0x1f, 
		op_hflex		= 0x0c22,
		op_flex			= 0x0c23,
		op_hflex1		= 0x0c24,
		op_flex1		= 0x0c25
	};

	enum TrueTypeCharStringType
	{
		CharStringType_UNKNOWN = 0,
		CharStringType_OPERATOR = 1,
		CharStringType_OPERAND = 2,
		CharStringType_FRACTION = 3
	};

	struct TrueTypeCharStringToken
	{
		TrueTypeCharStringType	type;

		union
		{
			float	fvalue;
			int		ivalue;
		};
	};

	struct TrueTypeCharStringContext
	{
		TrueTypeCharStringContext()
		{
			zeroMemory( this, sizeof( *this ) );
			result = ErrorId_Ok;
		}

		ctl::Vector<TrueTypeContour>*	pContours;
		ctl::Vector<TrueTypeVertex>*	pVertices;
		ErrorId							result;
		TrueTypeContour*				pCurrentContour;
		int4							boundingBox;
		float							x;
		float							y;
	};

	struct TrueTypeCharStringTokenStack
	{
		static const int			s_StackSize = 64;

		TrueTypeCharStringTokenStack()
		{
			zeroMemory( this, sizeof( *this ) );
			inHeader = true;
		}

		TrueTypeCharStringToken		tokens[ s_StackSize ];
		uint8						stem;
		int							index;
		int							maskBits;
		bool						inHeader;
	};

	struct TrueTypeCFFIndexObject
	{
		uint32 offsetToData;
		uint32 dataLengthInBytes;
	};

	ErrorId parseTTFOutline( ctl::Vector<TrueTypeContour>* pOutContours, ctl::Vector<TrueTypeVertex>* pOutVertices, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex );
	void	executeOTFCharStringRoutine( const TrueTypeFont* pTrueTypeFont, TrueTypeCharStringContext* pContext, TrueTypeCharStringTokenStack* pStack, uint32* pInOutOffset, uint32 length, uint32 glyphIndex );


	template< typename T >
	T peek(const uint8* pData, size_t dataSize, uint32 offset)
	{
		// :JK: :I don't like the assert 'error-handling' here.. maybe something that returns a default value and sets a (sticky) error would be better?

		KEEN_UNUSED1( dataSize );
		const size_t sizeInBytes = sizeof(T);
		KEEN_UNUSED1( sizeInBytes );
		KEEN_ASSERT(sizeInBytes + offset < dataSize);

		T value = *( T* )( pData + offset );
		value = changeEndianness( value );

		return value;
	}

	template<>
	char peek(const uint8* pData, size_t dataSize, uint32 offset)
	{
		KEEN_UNUSED1( dataSize );
		KEEN_ASSERT(1 + offset < dataSize);
		return *(char*)(pData + offset);
	}

	template<>
	sint8 peek( const uint8* pData, size_t dataSize, uint32 offset )
	{
		KEEN_UNUSED1( dataSize );
		KEEN_ASSERT( 1 + offset < dataSize );
		return *(sint8*)( pData + offset );
	}

	template<>
	uint8 peek( const uint8* pData, size_t dataSize, uint32 offset )
	{
		KEEN_UNUSED1( dataSize );
		KEEN_ASSERT( 1 + offset < dataSize );
		return *(pData + offset);
	}

	template< typename T >
	T peek(const TrueTypeFont* pTrueTypeFont, uint32 offset)
	{
		return peek<T>(pTrueTypeFont->trueTypeBlob.pStart, pTrueTypeFont->trueTypeBlob.size, offset);
	}

	template< typename T >
	T read( const TrueTypeFont* pTrueTypeFont, uint32* pInOutOffset )
	{
		const T value = peek<T>( pTrueTypeFont->trueTypeBlob.pStart, pTrueTypeFont->trueTypeBlob.size, *pInOutOffset );
		*pInOutOffset += sizeof( T );

		return value;
	}

	uint32 peekVariableSize( const TrueTypeFont* pTrueTypeFont, uint32 offset, uint32 dataSize )
	{
		uint32 value = 0u;

		for( uint32 dataIndex = 0u; dataIndex < dataSize; ++dataIndex )
		{
			value = ( value << 8 ) | peek<uint8>( pTrueTypeFont->trueTypeBlob.pStart, pTrueTypeFont->trueTypeBlob.size, offset + dataIndex );
		}

		return value;
	}

	uint32 readVariableSize( const TrueTypeFont* pTrueTypeFont, uint32* pInOutOffset, uint32 dataSize )
	{
		const uint32 value = peekVariableSize(pTrueTypeFont, *pInOutOffset, dataSize);
		*pInOutOffset += dataSize;

		return value;
	}

	TrueTypeCFFIndex readCFFIndex( const TrueTypeFont* pTrueTypeFont, uint32* pInOutOffset )
	{
		TrueTypeCFFIndex index;
		index.entryCount	= read<uint16>( pTrueTypeFont, pInOutOffset );

		if( index.entryCount == 0 )
		{
			return index;
		}

		index.offsetSize			= read<uint8>( pTrueTypeFont, pInOutOffset );
		index.offsetToDataOffset	= *pInOutOffset;

		*pInOutOffset += (uint32)( index.entryCount * index.offsetSize );
		index.dataSize = peekVariableSize( pTrueTypeFont, *pInOutOffset, index.offsetSize ) - 1u;

		//FK: Move offset to beginning of index data
		*pInOutOffset += index.offsetSize;

		index.offsetToData = *pInOutOffset;
		
		//FK: Move offset past data
		*pInOutOffset += index.dataSize;

		return index;
	}

	uint32 calculateTableCheckSum(const TrueTypeFont* pTrueTypeFont, uint32 tableLengthInBytes, uint32 tableOffset)
	{
		if (tableOffset + tableLengthInBytes > pTrueTypeFont->trueTypeBlob.size)
		{
			return 0u;
		}

		//https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6.html#Overview
		uint32 sum = 0;
		int count = (int)((tableLengthInBytes + 3) & ~3) / 4;
		while ( count-- > 0 && ( tableOffset + 4u < pTrueTypeFont->trueTypeBlob.size ) )
		{
			sum += peek<uint32>( pTrueTypeFont->trueTypeBlob.pStart, pTrueTypeFont->trueTypeBlob.size, tableOffset );
			tableOffset += 4u;
		}

		return sum;
	}

	uint32 retrieveTableOffset(const TrueTypeFont* pTrueTypeFont, const char* pTableTagToFind)
	{
		uint32 offset = TrueTypeDataOffset_TableDirectory + pTrueTypeFont->offset;
		char tableTag[4];

		for (uint32 tableIndex = 0u; tableIndex < pTrueTypeFont->numTables; ++tableIndex)
		{
			tableTag[0] = peek<char>(pTrueTypeFont, offset); offset += 1u;
			tableTag[1] = peek<char>(pTrueTypeFont, offset); offset += 1u;
			tableTag[2] = peek<char>(pTrueTypeFont, offset); offset += 1u;
			tableTag[3] = peek<char>(pTrueTypeFont, offset); offset += 1u;

			if (isStringEqualNoCase(tableTag, pTableTagToFind, 4u))
			{
				const uint32 tableCheckSum	= read<uint32>( pTrueTypeFont, &offset );
				const uint32 tableOffset	= read<uint32>( pTrueTypeFont, &offset );
				const uint32 tableLength	= read<uint32>( pTrueTypeFont, &offset );
				KEEN_UNUSED2( tableCheckSum, tableLength );

				//FK: the 'head' table's checksum is calculated differently
				if (!isStringEqualNoCase(pTableTagToFind, "head", 4u))
				{
					const uint32 calculatedCheckSum = calculateTableCheckSum(pTrueTypeFont, tableLength, tableOffset);
					if (tableCheckSum != calculatedCheckSum)
					{
						return 0u;
					}
				}
				
				return tableOffset;
			}

			//FK: Move to next table head entry
			offset += 12u;
		}

		return 0u;
	}

	void retrieveTableOffsets( TrueTypeFont* pTrueTypeFont )
	{
#if 0
		for( uint32 tableIndex = 0u; tableIndex < pTrueTypeFont->numTables; ++tableIndex )
		{
			// hacky di hack
			char id[ 5 ] = {
				peek< char >( pTrueTypeFont, TrueTypeDataOffset_TableDirectory + pTrueTypeFont->offset + tableIndex * 16u + 0u ),
				peek< char >( pTrueTypeFont, TrueTypeDataOffset_TableDirectory + pTrueTypeFont->offset + tableIndex * 16u + 1u ),
				peek< char >( pTrueTypeFont, TrueTypeDataOffset_TableDirectory + pTrueTypeFont->offset + tableIndex * 16u + 2u ),
				peek< char >( pTrueTypeFont, TrueTypeDataOffset_TableDirectory + pTrueTypeFont->offset + tableIndex * 16u + 3u ),
				0
			};
			KEEN_TRACE_INFO( "%s\n", id );
		}

		KEEN_TRACE_INFO( "\n\n\n" );

#endif

		pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF ] = retrieveTableOffset(pTrueTypeFont, "cff ");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF2] = retrieveTableOffset(pTrueTypeFont, "cff2");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_GLYF]	= retrieveTableOffset(pTrueTypeFont, "glyf");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_HEAD] = retrieveTableOffset(pTrueTypeFont, "head");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_HHEA] = retrieveTableOffset(pTrueTypeFont, "hhea");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_KERN] = retrieveTableOffset(pTrueTypeFont, "kern");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_KERX] = retrieveTableOffset(pTrueTypeFont, "kerx");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_LOCA] = retrieveTableOffset(pTrueTypeFont, "loca");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_MAXP] = retrieveTableOffset(pTrueTypeFont, "maxp");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_HMTX] = retrieveTableOffset(pTrueTypeFont, "hmtx");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_VMTX] = retrieveTableOffset(pTrueTypeFont, "vmtx");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_CMAP] = retrieveTableOffset(pTrueTypeFont, "cmap");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_SBIX] = retrieveTableOffset(pTrueTypeFont, "sbix");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_NAME] = retrieveTableOffset(pTrueTypeFont, "name");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_LTAG] = retrieveTableOffset(pTrueTypeFont, "ltag");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_SVG ] = retrieveTableOffset(pTrueTypeFont, "SVG ");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_EBDT] = retrieveTableOffset(pTrueTypeFont, "EBDT");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_EBLC] = retrieveTableOffset(pTrueTypeFont, "EBLC");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_EBSC] = retrieveTableOffset(pTrueTypeFont, "EBSC");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_COLR] = retrieveTableOffset(pTrueTypeFont, "COLR");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_CBDT] = retrieveTableOffset(pTrueTypeFont, "CBDT");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_CBLC] = retrieveTableOffset(pTrueTypeFont, "CBLC");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_GSUB] = retrieveTableOffset(pTrueTypeFont, "GSUB");
		pTrueTypeFont->tableOffsets[TrueTypeFontTable_MORX] = retrieveTableOffset(pTrueTypeFont, "morx");
	}

	bool isValidTrueTypeFont( const TrueTypeFont* pTrueTypeFont )
	{
		//FK: Check if we have valid offets for all the relevant tables
		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_HEAD ] == 0u ||
			pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CMAP ] == 0u )
		{
			return false;
		}

		if (pTrueTypeFont->sfnt == TrueTypeSFNT_OpenType)
		{
			if (pTrueTypeFont->tableOffsets[TrueTypeFontTable_HEAD] == 0u ||
				pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF ] == 0u)
			{
				return false;
			}
		}

		//FK: retrieve magic number from head table to verify valid true type format
		const uint32 offset = pTrueTypeFont->tableOffsets[TrueTypeFontTable_HEAD] + TrueTypeDataOffset_MagicNumber;
		const uint32 magicNumber = peek<uint32>(pTrueTypeFont, offset);

		if (magicNumber != TrueType_MagicNumber)
		{
			return false;
		}

		//FK: indexToLocaFormat can only have 2 valid values
		if (pTrueTypeFont->indexToLocaFormat != 0u && pTrueTypeFont->indexToLocaFormat != 1u)
		{
			return false;
		}

		return true;
	}

	int getGlyfOffset( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		uint32 offset = pTrueTypeFont->tableOffsets[TrueTypeFontTable_LOCA];

		if ( offset == 0u )
		{
			return -1;
		}

		if ( pTrueTypeFont->indexToLocaFormat == 0 )
		{
			const uint16 glyfOffset		= peek<uint16>( pTrueTypeFont, offset + (glyphIndex + 0u) * 2u );
			const uint16 nextGlyfOffset = peek<uint16>( pTrueTypeFont, offset + (glyphIndex + 1u) * 2u );
			return glyfOffset == nextGlyfOffset ? -1 : (int)glyfOffset * 2;
		}
		else
		{
			const uint32 glyfOffset		= peek<uint32>( pTrueTypeFont, offset + (glyphIndex + 0u) * 4u );
			const uint32 nextGlyfOffset = peek<uint32>( pTrueTypeFont, offset + (glyphIndex + 1u) * 4u );
			return glyfOffset == nextGlyfOffset ? -1 : (int)glyfOffset;
		}

		return -1;
	}

	float convertFixedPointToFloat( sint16 fixedPoint )
	{
		return (float)fixedPoint / 16384.0f;
	}

	int peekCFFNumber( const TrueTypeFont* pTrueTypeFont, uint32 offset )
	{
		int b0 = peek<uint8>( pTrueTypeFont, offset );
		if ( b0 >= 32 && b0 <= 246 )
		{
			return b0 - 139;
		}
		else if ( b0 >= 247 && b0 <= 250 )
		{
			const int b1 = peek<uint8>( pTrueTypeFont, offset + 1 );
			return (b0 - 247) * 256 + b1 + 108;
		}
		else if ( b0 >= 251 && b0 <= 254 )
		{
			const int b1 = peek<uint8>( pTrueTypeFont, offset + 1 );
			return -(b0 - 251) * 256 - b1 - 108;
		}
		else if ( b0 == 28 )
		{
			const int b1 = peek<uint8>( pTrueTypeFont, offset + 1 );
			const int b2 = peek<uint8>( pTrueTypeFont, offset + 2 );
			return b1 << 8 | b2 << 0;
		}
		else if ( b0 == 29 )
		{
			const int b1 = peek<uint8>( pTrueTypeFont, offset + 1 );
			const int b2 = peek<uint8>( pTrueTypeFont, offset + 2 );
			const int b3 = peek<uint8>( pTrueTypeFont, offset + 3 );
			const int b4 = peek<uint8>( pTrueTypeFont, offset + 4 );
			return b1 << 24 | b2 << 16 | b3 << 8 | b4 << 0;
		}

		return 0u;
	}

	int readCFFNumber( const TrueTypeFont* pTrueTypeFont, uint32* pInOutOffset )
	{
		const uint8 b0 = peek<uint8>( pTrueTypeFont, *pInOutOffset );
		const int number = peekCFFNumber( pTrueTypeFont, *pInOutOffset );

		*pInOutOffset += 1;

		if ( b0 >= 247 && b0 <= 254 )
		{
			*pInOutOffset += 1;
		}
		else if ( b0 == 28 )
		{
			*pInOutOffset += 2;
		}
		else if ( b0 == 29 )
		{
			*pInOutOffset += 4;
		}

		return number;
	}

	uint32 parseDictKey( const TrueTypeFont* pTrueTypeFont, const TrueTypeCFFIndex* pOpenTypeIndex, int key )
	{
		uint32 offset = pOpenTypeIndex->offsetToData;
		uint32 startOffset = offset;

		while ( offset - startOffset < pOpenTypeIndex->dataSize )
		{
			startOffset = offset;

			int op = peek<uint8>( pTrueTypeFont, offset );
			while ( op >= 28 )
			{
				readCFFNumber( pTrueTypeFont, &offset );
				op = peek<uint8>( pTrueTypeFont, offset );
			}

			offset += 1;

			if ( op == 12 )
			{
				op = read<uint8>( pTrueTypeFont, &offset ) | 0x100;
			}

			if ( op == key )
			{
				return startOffset;
			}
		}

		return 0u;
	}

	uint32 getIndexDataOffset( const TrueTypeFont* pTrueTypeFont, const TrueTypeCFFIndex* pIndex, uint32 index )
	{
		uint32 offset = index * pIndex->offsetSize;
		offset += pIndex->offsetToDataOffset;

		offset = peekVariableSize( pTrueTypeFont, offset, pIndex->offsetSize );
		return pIndex->offsetToData + offset - 1u; //-1 not sure why
	}

	TrueTypeCFFIndexObject getIndexObject( const TrueTypeFont* pTrueTypeFont, const TrueTypeCFFIndex* pIndex, uint32 index )
	{
		TrueTypeCFFIndexObject object;
		object.offsetToData = getIndexDataOffset( pTrueTypeFont, pIndex, index );
		object.dataLengthInBytes = getIndexDataOffset( pTrueTypeFont, pIndex, index + 1 ) - object.offsetToData;

		return object;
	}

	void pushTrueTypeTokenToStack( TrueTypeCharStringTokenStack* pStack, const TrueTypeCharStringToken& token )
	{
		KEEN_ASSERT( pStack->index != pStack->s_StackSize );
		pStack->tokens[pStack->index++] = token;
	}

	void clearTrueTypeTokenStack( TrueTypeCharStringTokenStack* pStack )
	{
#ifndef KEEN_BUILD_MASTER
		//FK: For better debug visualization
		zeroMemory( pStack->tokens, sizeof( pStack->tokens ) );
#endif
		pStack->index = 0u;
	}

	TrueTypeCharStringToken readToken( const TrueTypeFont* pTrueTypeFont, uint32* pInOutOffset )
	{
		TrueTypeCharStringToken token;
		token.type = CharStringType_UNKNOWN;
		token.ivalue = 0;

		const int b0 = read<uint8>( pTrueTypeFont, pInOutOffset );

		if ( b0 <= 27 )
		{
			token.type = CharStringType_OPERATOR;

			if ( b0 <= 11 || (b0 >= 13 && b0 <= 27) )
			{
				token.ivalue = b0;
			}
			else if ( b0 == 12 )
			{
				const int b1 = read<uint8>( pTrueTypeFont, pInOutOffset );
				token.ivalue = (b0 << 8 | b1 << 0);
			}
		}
		else if ( b0 == 28 )
		{
			const int b1 = read<uint8>( pTrueTypeFont, pInOutOffset );
			const int b2 = read<uint8>( pTrueTypeFont, pInOutOffset );

			token.type = CharStringType_OPERAND;
			token.ivalue = (b1 << 8 | b2 << 0);
		}
		else if ( b0 >= 29 && b0 <= 31 )
		{
			token.type = CharStringType_OPERATOR;
			token.ivalue = b0;
		}
		else if ( b0 >= 31 && b0 <= 254 )
		{
			//FK: Go one back so that readCFFNumber reads from the correct position
			*pInOutOffset -= 1;

			token.type = CharStringType_OPERAND;
			token.ivalue = readCFFNumber( pTrueTypeFont, pInOutOffset );
		}
		else if ( b0 == 255 )
		{
			const int b1 = read<uint8>( pTrueTypeFont, pInOutOffset );
			const int b2 = read<uint8>( pTrueTypeFont, pInOutOffset );
			const int b3 = read<uint8>( pTrueTypeFont, pInOutOffset );
			const int b4 = read<uint8>( pTrueTypeFont, pInOutOffset );

			const int integerPart = b1 << 8 | b2 << 0;
			const int fractionPart = b3 << 8 | b4 << 0;

			token.type = CharStringType_FRACTION;
			token.fvalue = (float)(integerPart + fractionPart / 65536.f);
		}

		if ( token.type == CharStringType_OPERAND )
		{
			//FK: ?? found this in https://github.com/caryll/otfcc
			token.type = CharStringType_FRACTION;
			token.fvalue = (float)token.ivalue;
		}

		return token;
	}

	const TrueTypeCharStringToken& readTokenFromTrueTypeTokenStack( const TrueTypeCharStringTokenStack* pStack, int index )
	{
		KEEN_ASSERT( pStack->index > index );
		return pStack->tokens[index];
	}

	const TrueTypeCharStringToken& popTokenFromTrueTypeTokenStack( TrueTypeCharStringTokenStack* pStack )
	{
		KEEN_ASSERT( pStack->index > 0 );
		return pStack->tokens[--pStack->index];
	}

	int computeSubrBias( const TrueTypeCFFIndex* pSubrIndex )
	{
		if ( pSubrIndex->entryCount < 1240 )
		{
			return 107;
		}
		else if ( pSubrIndex->entryCount < 33900 )
		{
			return 1131;
		}

		return 32768;
	}

	TrueTypeCFFIndex retrieveLocalSubrIndex( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		KEEN_UNUSED1( glyphIndex );
		uint32 subrOffset = 0u;

		//FK: CID Font?
		const uint32 fontArrayDictValue = parseDictKey( pTrueTypeFont, &pTrueTypeFont->cffIndexes[TrueTypeCFFIndex_TopDict], CFFKey_FontDictOffset );
		const uint32 fontSelectDictOffsetValue = parseDictKey( pTrueTypeFont, &pTrueTypeFont->cffIndexes[TrueTypeCFFIndex_TopDict], CFFKey_FontDictSelectOffset );

		if ( fontArrayDictValue > 0u && fontSelectDictOffsetValue > 0u )
		{
			uint32 fontArrayDictOffset = (uint32)peekCFFNumber( pTrueTypeFont, fontArrayDictValue ) + pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF];
			uint32 fontSelectOffset = (uint32)peekCFFNumber( pTrueTypeFont, fontSelectDictOffsetValue ) + pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF];

			const TrueTypeCFFIndex fontDictIndex = readCFFIndex( pTrueTypeFont, &fontArrayDictOffset );

			const uint8 fontSelectFormat = read<uint8>( pTrueTypeFont, &fontSelectOffset );

			if ( fontSelectFormat == 0 )
			{
				fontSelectOffset += glyphIndex;
				subrOffset = read<uint8>( pTrueTypeFont, &fontSelectOffset );
			}
			else if ( fontSelectFormat == 3 )
			{
				const uint16 rangeCount = read<uint16>( pTrueTypeFont, &fontSelectOffset );
				uint16 start = read<uint16>( pTrueTypeFont, &fontSelectOffset );

				int fontDictObjectIndex = -1;

				for ( uint32 selectorIndex = 0; selectorIndex < rangeCount; ++selectorIndex )
				{
					const uint8	 dictIndex = read<uint8>( pTrueTypeFont, &fontSelectOffset );
					const uint16 end = read<uint16>( pTrueTypeFont, &fontSelectOffset );

					if ( glyphIndex >= start && glyphIndex < end )
					{
						fontDictObjectIndex = dictIndex;
						break;
					}

					start = end;
				}

				if ( fontDictObjectIndex == -1 )
				{
					subrOffset = 0u;
				}
				else
				{
					TrueTypeCFFIndexObject fontDictObject = getIndexObject( pTrueTypeFont, &fontDictIndex, (uint32)fontDictObjectIndex );

					TrueTypeCFFIndex subrIndex;
					subrIndex.offsetToData = fontDictObject.offsetToData;
					subrIndex.dataSize = fontDictObject.dataLengthInBytes;

					uint32 privateDictValue = parseDictKey( pTrueTypeFont, &subrIndex, CFFKey_PrivateDict );
					const uint32 privateDictSize = (uint32)readCFFNumber( pTrueTypeFont, &privateDictValue );
					const uint32 privateDictOffset = (uint32)readCFFNumber( pTrueTypeFont, &privateDictValue ) + pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF];

					TrueTypeCFFIndex subrIndex2;
					subrIndex2.offsetToData = privateDictOffset;
					subrIndex2.dataSize = privateDictSize;

					const uint32 subrDictOffset = parseDictKey( pTrueTypeFont, &subrIndex2, 19 );
					subrOffset = (uint32)peekCFFNumber( pTrueTypeFont, subrDictOffset );

					if ( subrOffset != 0 )
					{
						subrOffset += privateDictOffset;
					}

				}
			}
			else
			{
				KEEN_NOT_IMPLEMENTED;
			}
		}
		else
		{
			uint32 privateDictValue = parseDictKey( pTrueTypeFont, &pTrueTypeFont->cffIndexes[TrueTypeCFFIndex_TopDict], CFFKey_PrivateDict );
			const uint32 privateDictSize = (uint32)readCFFNumber( pTrueTypeFont, &privateDictValue );
			const uint32 privateDictOffset = (uint32)readCFFNumber( pTrueTypeFont, &privateDictValue ) + pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF];

			TrueTypeCFFIndex subrIndex;
			subrIndex.offsetToData = privateDictOffset;
			subrIndex.dataSize = privateDictSize;

			const uint32 subrDictOffset = parseDictKey( pTrueTypeFont, &subrIndex, 19 );
			subrOffset = (uint32)peekCFFNumber( pTrueTypeFont, subrDictOffset );

			if ( subrOffset != 0 )
			{
				subrOffset += privateDictOffset;
			}
		}

		return readCFFIndex( pTrueTypeFont, &subrOffset );
	}

	int4 parseTTFGlyphBoundingBox( const TrueTypeFont* pTrueTypeFont, int glyfOffset )
	{
		if( glyfOffset == -1 )
		{
			//FK: Glyphs with a glyfOffset of -1 are glyphs, that are not visible (like SPACE or NEWLINE)
			return i4_zero();
		}

		uint32 offset = glyfOffset + pTrueTypeFont->tableOffsets[ TrueTypeFontTable_GLYF ];
		offset += 2u; //FK: Skip contour count

		int4 boundingBox = i4_zero();

		boundingBox.x = read<sint16>( pTrueTypeFont, &offset );
		boundingBox.y = read<sint16>( pTrueTypeFont, &offset );
		boundingBox.z = read<sint16>( pTrueTypeFont, &offset );
		boundingBox.w = read<sint16>( pTrueTypeFont, &offset );

		return boundingBox;
	}

	int4 parseOTFGlyphBoundingBox( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		const TrueTypeCFFIndexObject charStringRoutineObject = getIndexObject( pTrueTypeFont, &pTrueTypeFont->cffIndexes[TrueTypeCFFIndex_CharStrings], glyphIndex );
		uint32 offset = charStringRoutineObject.offsetToData;

		TrueTypeCharStringTokenStack stack;
		TrueTypeCharStringContext charStringContext;

		executeOTFCharStringRoutine( pTrueTypeFont, &charStringContext, &stack, &offset, charStringRoutineObject.dataLengthInBytes, glyphIndex );
		return charStringContext.boundingBox;
	}

	void readTrueTypeNameUTF16( char* pOutName, const TrueTypeFont* pTrueTypeFont, uint16 length, uint32 offset )
	{
		const uint16 lengthInChars = length / 2u;
		KEEN_ASSERT( lengthInChars < MaxFontName );

		pOutName[ lengthInChars ] = 0;

		//FK: No utf16->utf8 conversion here at all :(
		for( uint32 charIndex = 0u; charIndex < lengthInChars; ++charIndex )
		{
			const uint16 utf16Char = peek<uint16>( pTrueTypeFont, offset + charIndex * 2u );
			pOutName[ charIndex ] = (char)( utf16Char );
		}
	}

	void readTrueTypeNameUTF8( char* pOutName, const TrueTypeFont* pTrueTypeFont, uint16 length, uint32 offset )
	{
		KEEN_ASSERT( length < MaxFontName );

		pOutName[ length ] = 0;

		for( uint32 charIndex = 0u; charIndex < length; ++charIndex )
		{
			pOutName[ charIndex ] = peek<char>( pTrueTypeFont, offset + charIndex );
		}
	}

	void readTrueTypeName( char* pOutName, const TrueTypeFont* pTrueTypeFont, uint16 length, uint32 offset, uint16 platformId, uint16 platformSpecificId )
	{
		if( platformId == 0u || ( platformId == 3u && platformSpecificId == 1u ) || ( platformId == 3u && platformSpecificId == 10u ) )
		{
			readTrueTypeNameUTF16( pOutName, pTrueTypeFont, length, offset );
		}
		else if (platformId == 1u )
		{
			readTrueTypeNameUTF8( pOutName, pTrueTypeFont, length, offset );
		}
	}

	void retrieveTrueTypeNames( TrueTypeFont* pTrueTypeFont )
	{
		uint32 offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_NAME ];
		offset += 2u; //FK: skip version

		const uint16 nameRecordCount	= read<uint16>( pTrueTypeFont, &offset );
		const uint16 stringOffset		= read<uint16>( pTrueTypeFont, &offset );

		for( uint16 nameRecordIndex = 0u; nameRecordIndex < nameRecordCount; ++nameRecordIndex )
		{
			//FK: Skip platformId and platformSpecificId for now...
			uint32 nameRecordOffset = offset;

			const uint16 platformId			= read<uint16>( pTrueTypeFont, &nameRecordOffset );
			const uint16 platformSpecificId = read<uint16>( pTrueTypeFont, &nameRecordOffset );
			const uint16 languageId			= read<uint16>( pTrueTypeFont, &nameRecordOffset );

			//FK: we're only interested in english names...I guess
			if( languageId == TrueTypeLanguageId_English || ( pTrueTypeFont->tableOffsets[TrueTypeFontTable_LTAG] > 0u && languageId == 0xFFFF ) )
			{
				const uint16 nameId			= read<uint16>( pTrueTypeFont, &nameRecordOffset );
				const uint16 lengthInBytes	= read<uint16>( pTrueTypeFont, &nameRecordOffset ); 
				const uint16 localOffset	= read<uint16>( pTrueTypeFont, &nameRecordOffset );

				if( lengthInBytes > 0u ) //the stuff I've seen...
				{
					if( nameId == TrueTypeNameId_FontFamily ||
						nameId == TrueTypeNameId_FontSubFamily ||
						nameId == TrueTypeNameId_FontName )
					{
						const uint32 offsetToStringData = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_NAME ] + stringOffset + localOffset;

						if( nameId == TrueTypeNameId_FontFamily )
						{
							readTrueTypeName( pTrueTypeFont->family.fontFamiliyName, pTrueTypeFont, lengthInBytes, offsetToStringData, platformId, platformSpecificId );
						}
						else if( nameId == TrueTypeNameId_FontSubFamily )
						{
							readTrueTypeName( pTrueTypeFont->family.fontStyle, pTrueTypeFont, lengthInBytes, offsetToStringData, platformId, platformSpecificId );
						}
						else if( nameId == TrueTypeNameId_FontName )
						{
							readTrueTypeName( pTrueTypeFont->family.fontName, pTrueTypeFont, lengthInBytes, offsetToStringData, platformId, platformSpecificId );
						}
					}
				}
			}


			offset += 12u; //FK: Skip to next name record
		}
	}

	void retrieveOpenTypeIndexes( TrueTypeFont* pTrueTypeFont )
	{
		uint32 offset = 2u + pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF];
		const uint8 headerSize = read<uint8>( pTrueTypeFont, &offset );
		offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CFF ] + headerSize;

		pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_Name				] = readCFFIndex( pTrueTypeFont, &offset );
		pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_TopDict				] = readCFFIndex( pTrueTypeFont, &offset );
		pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_String				] = readCFFIndex( pTrueTypeFont, &offset );
		pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_GlobalSubroutines	] = readCFFIndex( pTrueTypeFont, &offset );
		
		const uint32 charStringOffsetDictValue	= parseDictKey( pTrueTypeFont, &pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_TopDict ], CFFKey_CharStringOffset );

		uint32 charStringDictOffset	= (uint32)peekCFFNumber( pTrueTypeFont, charStringOffsetDictValue ) + pTrueTypeFont->tableOffsets[TrueTypeFontTable_CFF];
		pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_CharStrings ] = readCFFIndex( pTrueTypeFont, &charStringDictOffset );

		const uint32 charType = parseDictKey( pTrueTypeFont, &pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_TopDict ], CFFKey_CharStringType );
		//FK: charStringType is 2 by default
		if ( charType != 0u )
		{
			pTrueTypeFont->charStringType = charType;
		}
		else
		{
			pTrueTypeFont->charStringType = 2u;
		}
	}

	void retrieveTrueTypeFontMetrics( TrueTypeFont* pTrueTypeFont )
	{
		uint32 offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_HHEA ];
		offset += 4u;

		pTrueTypeFont->metrics.ascent		= read<sint16>( pTrueTypeFont, &offset );
		pTrueTypeFont->metrics.descent		= read<sint16>( pTrueTypeFont, &offset );
		pTrueTypeFont->metrics.lineGap		= read<sint16>( pTrueTypeFont, &offset );

		pTrueTypeFont->metrics.capHeight	= pTrueTypeFont->metrics.ascent;

		if( s_useCustomCapHeight )
		{
			uint32 capGlyphIndex = getTrueTypeGlyphIndex( pTrueTypeFont, 'X' );
			if( capGlyphIndex == TrueTypeGlphyIndex_Invalid )
			{
				capGlyphIndex = getTrueTypeGlyphIndex( pTrueTypeFont, 'W' );
			}
			if( capGlyphIndex == TrueTypeGlphyIndex_Invalid )
			{
				capGlyphIndex = getTrueTypeGlyphIndex( pTrueTypeFont, 'N' );
			}

			if( capGlyphIndex != TrueTypeGlphyIndex_Invalid )
			{
				TrueTypeGlyphMetrics glyphMetrics;
				int4 glyphBoundingBox;
				if( getTrueTypeGlyphMetric( &glyphMetrics, &glyphBoundingBox, pTrueTypeFont, capGlyphIndex ) )
				{
					pTrueTypeFont->metrics.capHeight = (sint16)glyphBoundingBox.w;
				}
			}
		}

		//FK: get units per em from head table
		offset = pTrueTypeFont->tableOffsets[TrueTypeFontTable_HEAD];
		offset += 18u;
		pTrueTypeFont->metrics.unitsPerEm = read<uint16>( pTrueTypeFont, &offset );
	}

	TrueTypeGlyphMetrics parseTrueTypeGlyphMetric( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		TrueTypeGlyphMetrics metrics;
		zeroMemory( &metrics, sizeof( metrics ) );

		uint32 offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_HHEA ];
		offset += 34; //FK: Jump to value that interests us

		const uint16 numOfLongHorizontalMetrics = read<uint16>( pTrueTypeFont, &offset );

		if( glyphIndex < numOfLongHorizontalMetrics ) 
		{
			offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_HMTX ] + 4 * glyphIndex;

			metrics.advanceWidth = read<sint16>( pTrueTypeFont, &offset );
		}
		else
		{
			//FK: Get advance width from last entry
			KEEN_ASSERT( numOfLongHorizontalMetrics );
			offset = pTrueTypeFont->tableOffsets[TrueTypeFontTable_HMTX] + 4 * (numOfLongHorizontalMetrics - 1);
			metrics.advanceWidth = read<sint16>( pTrueTypeFont, &offset );
		}

		if ( ( pTrueTypeFont->flags & TrueTypeFlag_LeftSideBearingFromTable ) > 0 )
		{
			if ( glyphIndex < numOfLongHorizontalMetrics )
			{
				offset = pTrueTypeFont->tableOffsets[TrueTypeFontTable_HMTX] + 4 * glyphIndex + 2u;
				metrics.leftSideBearing = read<sint16>( pTrueTypeFont, &offset );
			}
			else
			{
				//FK: Get left side bearing from last entry
				KEEN_ASSERT( numOfLongHorizontalMetrics );
				offset = pTrueTypeFont->tableOffsets[TrueTypeFontTable_HMTX] + 4 * (numOfLongHorizontalMetrics - 1) + 2u;
				metrics.leftSideBearing = read<sint16>( pTrueTypeFont, &offset );
			}
		}
		else
		{
			const int4 boundingBox = parseTTFGlyphBoundingBox( pTrueTypeFont, getGlyfOffset( pTrueTypeFont, glyphIndex ) );
			metrics.leftSideBearing = (sint16)boundingBox.x;
			
		}

		return metrics;
	}

	ErrorId parseTTFSimpleOutline( ctl::Vector<TrueTypeContour>* pOutContours, ctl::Vector<TrueTypeVertex>* pOutVertices, const TrueTypeFont* pTrueTypeFont, int glyfOffset )
	{
		uint32 offset = glyfOffset + pTrueTypeFont->tableOffsets[TrueTypeFontTable_GLYF];

		const uint16 contourCount = read<uint16>( pTrueTypeFont, &offset );
		offset += 8u; //FK: Skip bounding box

		uint16 endPointsOfPreviousContour	= 0u;
		uint32 totalVertexCount				= 0u;
		const uint32 startVertexIndex		= (uint32)pOutVertices->getSize();

		TrueTypeContour* pContours = pOutContours->pushBackRange( contourCount );
		if ( pContours == nullptr )
		{
			return ErrorId_OutOfMemory;
		}

		for ( sint16 contourIndex = 0u; contourIndex < contourCount; ++contourIndex )
		{
			const uint16 endPointOfContour	= 1u + read<uint16>( pTrueTypeFont, &offset );
			const uint32 vertexCount		= endPointOfContour - endPointsOfPreviousContour < 0 ? 0u : endPointOfContour - endPointsOfPreviousContour;

			pContours[ contourIndex ].startIndex	= startVertexIndex + totalVertexCount;
			pContours[ contourIndex ].length		= vertexCount;

			totalVertexCount += vertexCount;

			endPointsOfPreviousContour = endPointOfContour;
		}

		const uint16 instructionCount = read<uint16>( pTrueTypeFont, &offset );
		offset += instructionCount; //FK: ignore instructions

		uint8 flags = 0u;
		uint8 flagRepeatCount = 0u;

		//FK: Read vertex flags

		TrueTypeVertex* pVertices = pOutVertices->pushBackRange( totalVertexCount );
		if ( pVertices == nullptr )
		{
			return ErrorId_OutOfMemory;
		}

		for ( uint32 vertexIndex = 0u; vertexIndex < totalVertexCount; ++vertexIndex )
		{
			if ( flagRepeatCount > 0u )
			{
				--flagRepeatCount;
			}
			else
			{
				flags = read<uint8>( pTrueTypeFont, &offset );

				if ( (flags & TrueTypeFontGlyphFlag_Repeat) > 0u )
				{
					if ( flagRepeatCount == 0u )
					{
						flagRepeatCount = read<uint8>( pTrueTypeFont, &offset );
					}
				}
			}

			pVertices[ vertexIndex ].flags = flags;
			pVertices[ vertexIndex ].type = (flags & TrueTypeFontGlyphFlag_OnCurve) > 0 ? TrueTypeFontVertexType_OnCurve : TrueTypeFontVertexType_Quadratic;
		}

		sint16 previousXCoordinate = 0u;
		sint16 previousYCoordinate = 0u;
		sint16 xCoordinate = 0u;
		sint16 yCoordinate = 0u;

		//FK: Get X Coordinates
		for ( uint32 vertexIndex = startVertexIndex; vertexIndex < pOutVertices->getSize(); ++vertexIndex )
		{
			TrueTypeVertex* pVertex = pOutVertices->getStart() + vertexIndex;

			if ( (pVertex->flags & TrueTypeFontGlyphFlag_XShortVector) > 0u )
			{
				xCoordinate = ((pVertex->flags & TrueTypeFontGlyphFlag_ThisXIsSame) > 0u ? 1 : -1);
				xCoordinate *= read<uint8>( pTrueTypeFont, &offset );
				xCoordinate = previousXCoordinate + xCoordinate;
			}
			else if ( (pVertex->flags & TrueTypeFontGlyphFlag_ThisXIsSame) == 0u )
			{
				xCoordinate = read<sint16>( pTrueTypeFont, &offset );
				xCoordinate = previousXCoordinate + xCoordinate;
			}

			pVertex->xCoordinate	= xCoordinate;
			previousXCoordinate		= xCoordinate;
		}

		//FK: Get Y Coordinates
		for ( uint32 vertexIndex = startVertexIndex; vertexIndex < pOutVertices->getSize(); ++vertexIndex )
		{
			TrueTypeVertex* pVertex = pOutVertices->getStart() + vertexIndex;

			if ( (pVertex->flags & TrueTypeFontGlyphFlag_YShortVector) > 0u )
			{
				yCoordinate = ((pVertex->flags & TrueTypeFontGlyphFlag_ThisYIsSame) > 0u ? 1 : -1);
				yCoordinate *= read<uint8>( pTrueTypeFont, &offset );
				yCoordinate = previousYCoordinate + yCoordinate;
			}
			else if ( (pVertex->flags & TrueTypeFontGlyphFlag_ThisYIsSame) == 0u )
			{
				yCoordinate = read<sint16>( pTrueTypeFont, &offset );
				yCoordinate = previousYCoordinate + yCoordinate;
			}

			pVertex->yCoordinate	= yCoordinate;
			previousYCoordinate		= yCoordinate;
		}

		return ErrorId_Ok;
	}

	void parseTTFOutlineTransformation(float* pTransformation, const TrueTypeFont* pTrueTypeFont, uint32* pInOutOffset, uint16 flags)
	{
		if ( (flags & TrueTypeComponentFlag_Args_are_xy_values) > 0u )
		{
			if ( (flags & TrueTypeComponentFlag_Arg1_and_2_are_words) > 0u )
			{
				pTransformation[4] = (float)read<sint16>( pTrueTypeFont, pInOutOffset );
				pTransformation[5] = (float)read<sint16>( pTrueTypeFont, pInOutOffset );
			}
			else
			{
				pTransformation[4] = (float)read<sint8>( pTrueTypeFont, pInOutOffset );
				pTransformation[5] = (float)read<sint8>( pTrueTypeFont, pInOutOffset );
			}
		}

		if ( (flags & TrueTypeComponentFlag_We_have_a_scale) > 0u )
		{
			const float scaleFloat = convertFixedPointToFloat( read<sint16>( pTrueTypeFont, pInOutOffset ) );

			pTransformation[0] = scaleFloat;
			pTransformation[1] = 0.0f;
			pTransformation[2] = 0.0f;
			pTransformation[3] = scaleFloat;
		}
		else if ( (flags & TrueTypeComponentFlag_We_have_an_x_and_y_scale) > 0u )
		{
			pTransformation[0] = convertFixedPointToFloat( read<sint16>( pTrueTypeFont, pInOutOffset ) );
			pTransformation[1] = 0.f;
			pTransformation[2] = 0.f;
			pTransformation[3] = convertFixedPointToFloat( read<sint16>( pTrueTypeFont, pInOutOffset ) );
		}
		else if ( (flags & TrueTypeComponentFlag_We_have_a_two_by_two) > 0u )
		{
			pTransformation[0] = convertFixedPointToFloat( read<sint16>( pTrueTypeFont, pInOutOffset ) );
			pTransformation[1] = convertFixedPointToFloat( read<sint16>( pTrueTypeFont, pInOutOffset ) );
			pTransformation[2] = convertFixedPointToFloat( read<sint16>( pTrueTypeFont, pInOutOffset ) );
			pTransformation[3] = convertFixedPointToFloat( read<sint16>( pTrueTypeFont, pInOutOffset ) );
		}
	}

	ErrorId parseTTFCompoundOutline( ctl::Vector<TrueTypeContour>* pOutContours, ctl::Vector<TrueTypeVertex>* pOutVertices, const TrueTypeFont* pTrueTypeFont, int glyfOffset )
	{
		uint32 offset = glyfOffset + pTrueTypeFont->tableOffsets[TrueTypeFontTable_GLYF];
		offset += 10u; //FK: Skip contour count and bounding box

		while ( true )
		{
			const uint16 flags				= read<uint16>( pTrueTypeFont, &offset );
			const uint16 contourGlyphIndex	= read<uint16>( pTrueTypeFont, &offset );
			
			const uint32 startVertexIndex = (uint32)pOutVertices->getSize();

			const ErrorId result = parseTTFOutline( pOutContours, pOutVertices, pTrueTypeFont, contourGlyphIndex );

			if ( result != ErrorId_Ok )
			{
				return result;
			}

			float transformation[6] = { 1.f, 0.f, 0.f, 1.f, 0.f, 0.f };
			parseTTFOutlineTransformation( transformation, pTrueTypeFont, &offset, flags );

			const float xScale = pf::sqrt( transformation[0] * transformation[0] + transformation[1] * transformation[1] );
			const float yScale = pf::sqrt( transformation[2] * transformation[2] + transformation[3] * transformation[3] );

			//FK: Apply transformation to contour glyph vertices
			for ( uint32 vertexIndex = startVertexIndex; vertexIndex < pOutVertices->getSize(); ++vertexIndex )
			{
				TrueTypeVertex* pVertex = pOutVertices->getStart() + vertexIndex;
				float x = (float)pVertex->xCoordinate;
				float y = (float)pVertex->yCoordinate;

				pVertex->xCoordinate = (sint16)(xScale * (transformation[0] * x + transformation[2] * y + transformation[4]));
				pVertex->yCoordinate = (sint16)(yScale * (transformation[1] * x + transformation[3] * y + transformation[5]));
			}

			if ( (flags & TrueTypeComponentFlag_More_components) == 0u )
			{
				break;
			}
		}

		return ErrorId_Ok;
	}

	ErrorId parseTTFOutline( ctl::Vector<TrueTypeContour>* pOutContours, ctl::Vector<TrueTypeVertex>* pOutVertices, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		const int glyfOffset = getGlyfOffset( pTrueTypeFont, glyphIndex );

		if ( glyfOffset == -1 )
		{
			//FK: Glyphs with a glyfOffset of -1 are glyphs, that are not visible (like SPACE or NEWLINE)
			return ErrorId_Ok;
		}

		uint32 offset = glyfOffset + pTrueTypeFont->tableOffsets[TrueTypeFontTable_GLYF];

		const sint16 contourCount = read<sint16>( pTrueTypeFont, &offset );
		ErrorId result;

		if ( contourCount < 0 )
		{
			result = parseTTFCompoundOutline( pOutContours, pOutVertices, pTrueTypeFont, glyfOffset );
		}
		else 
		{
			result = parseTTFSimpleOutline( pOutContours, pOutVertices, pTrueTypeFont, glyfOffset );
		}

		return result;
	}

	void addOTFContour( TrueTypeCharStringContext* pContext )
	{
		if ( pContext->pContours == nullptr )
		{
			//FK:	this is valid if we just want to get informations like 
			//		the bounding box without actually saving contours and vertices
			return;
		}

		if ( pContext->result != ErrorId_Ok )
		{
			return;
		}

		uint32 startIndex = 0u;

		if ( pContext->pCurrentContour != nullptr )
		{
			startIndex = pContext->pCurrentContour->startIndex + pContext->pCurrentContour->length;
		}

		pContext->pCurrentContour = pContext->pContours->pushBack();

		if ( pContext->pCurrentContour == nullptr )
		{
			pContext->result = ErrorId_OutOfMemory;
			return;
		}

		pContext->pCurrentContour->startIndex	= startIndex;
		pContext->pCurrentContour->length		= 0u;
	}

	void addOTFVertex( TrueTypeCharStringContext* pContext, float x, float y, uint8 flags )
	{
		pContext->boundingBox.x = min( pContext->boundingBox.x, (sint32)x );
		pContext->boundingBox.y = min( pContext->boundingBox.y, (sint32)y );
		pContext->boundingBox.z = max( pContext->boundingBox.z, (sint32)x );
		pContext->boundingBox.w = max( pContext->boundingBox.w, (sint32)y );

		if ( pContext->pVertices == nullptr )
		{	
			//FK:	this is valid if we just want to get informations like 
			//		the bounding box without actually saving contours and vertices
			return; 
		}

		if ( pContext->result != ErrorId_Ok )
		{
			return;
		}

		KEEN_ASSERT( pContext->pCurrentContour );

		TrueTypeVertex* pVertex = pContext->pVertices->pushBack();

		if ( pVertex == nullptr )
		{
			pContext->result = ErrorId_OutOfMemory;
			return;
		}

		++pContext->pCurrentContour->length;

		pVertex->flags			= flags;
		pVertex->xCoordinate	= (sint16)x;
		pVertex->yCoordinate	= (sint16)y;
		pVertex->type			= (flags & TrueTypeFontGlyphFlag_OnCurve) > 0 ? TrueTypeFontVertexType_OnCurve : TrueTypeFontVertexType_Cubic;
	}

	void lineTo( TrueTypeCharStringContext* pContext, float x, float y )
	{
		pContext->x += x;
		pContext->y += y;

		addOTFVertex( pContext, pContext->x, pContext->y, TrueTypeFontGlyphFlag_OnCurve );
	}

	void curveTo( TrueTypeCharStringContext* pContext, float x1, float y1, float x2, float y2, float x3, float y3 )
	{
		const float cx1 = pContext->x + x1;
		const float cy1 = pContext->y + y1;
		const float cx2 = cx1 + x2;
		const float cy2 = cy1 + y2;
		const float cx3 = cx2 + x3;
		const float cy3 = cy2 + y3;

		pContext->x = cx3;
		pContext->y = cy3;

		addOTFVertex( pContext, cx1, cy1, 0 );
		addOTFVertex( pContext, cx2, cy2, 0 );
		addOTFVertex( pContext, cx3, cy3, TrueTypeFontGlyphFlag_OnCurve );
	}

	void lineToWithStackIndex( TrueTypeCharStringContext* pContext, const TrueTypeCharStringTokenStack* pStack, int xi, int yi )
	{
		const float x = xi == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, xi ).fvalue;
		const float y = yi == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, yi ).fvalue;
		lineTo( pContext, x, y );
	}

	void curveToWithStackIndex( TrueTypeCharStringContext* pContext, const TrueTypeCharStringTokenStack* pStack, int xi1, int yi1, int xi2, int yi2, int xi3, int yi3 )
	{
		const float x1 = xi1 == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, xi1 ).fvalue;
		const float y1 = yi1 == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, yi1 ).fvalue;
		const float x2 = xi2 == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, xi2 ).fvalue;
		const float y2 = yi2 == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, yi2 ).fvalue;
		const float x3 = xi3 == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, xi3 ).fvalue;
		const float y3 = yi3 == -1 ? 0.f : readTokenFromTrueTypeTokenStack( pStack, yi3 ).fvalue;
		curveTo( pContext, x1, y1, x2, y2, x3, y3 );
	}

	void executeOTFCharStringSubRoutine( const TrueTypeFont* pTrueTypeFont, TrueTypeCharStringContext* pContext, TrueTypeCharStringTokenStack* pStack, const TrueTypeCFFIndex* pSubrIndex, uint32 glyphIndex, int subRoutine )
	{
		const int subrBias = computeSubrBias( pSubrIndex );
		subRoutine += subrBias;

		TrueTypeCFFIndexObject subRoutineObject = getIndexObject( pTrueTypeFont, pSubrIndex, (uint32)subRoutine );
		executeOTFCharStringRoutine( pTrueTypeFont, pContext, pStack, &subRoutineObject.offsetToData, subRoutineObject.dataLengthInBytes, glyphIndex );
	}

	void executeOTFCharStringLocalSubRoutine( const TrueTypeFont* pTrueTypeFont, TrueTypeCharStringContext* pContext, TrueTypeCharStringTokenStack* pStack, uint32 glyphIndex, int subRoutine )
	{
		TrueTypeCFFIndex subrIndex = retrieveLocalSubrIndex( pTrueTypeFont, glyphIndex );
		//executeOTFCharStringTokensFromSubRoutine( pContext, pOutGlyph, pStack, pTrueTypeFont, &subrIndex, subRoutine );
		executeOTFCharStringSubRoutine( pTrueTypeFont, pContext, pStack, &subrIndex, glyphIndex, subRoutine );
	}

	void executeOTFCharStringRoutine( const TrueTypeFont* pTrueTypeFont, TrueTypeCharStringContext* pContext, TrueTypeCharStringTokenStack* pStack, uint32* pInOutOffset, uint32 length, uint32 glyphIndex )
	{
		const uint32 startOffset = *pInOutOffset;

		while ( *pInOutOffset - startOffset < length )
		{
			TrueTypeCharStringToken token = readToken( pTrueTypeFont, pInOutOffset );

			switch ( token.type )
			{
			case CharStringType_OPERATOR:
			{
				switch ( token.ivalue )
				{
				case op_hstem:
				case op_vstem:
				case op_hstemhm:
				case op_vstemhm:
				{
					pStack->maskBits += (pStack->index / 2);
					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_hintmask:
				case op_cntrmask:
				{
					if ( pStack->inHeader )
					{
						pStack->maskBits += (pStack->index / 2);
					}

					pStack->inHeader = false;
					*pInOutOffset += (pStack->maskBits + 7) / 8;
					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_vmoveto:
				{
					pStack->inHeader = false;
					KEEN_ASSERT( pStack->index >= 1 );

					addOTFContour( pContext );
					lineToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, pStack->index - 1 );

					clearTrueTypeTokenStack( pStack );

					break;
				}

				case op_rmoveto:
				{
					pStack->inHeader = false;
					KEEN_ASSERT( pStack->index >= 2 );

					addOTFContour( pContext );
					lineToWithStackIndex( pContext, pStack, pStack->index - 2, pStack->index - 1 );

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_hmoveto:
				{
					pStack->inHeader = false;
					KEEN_ASSERT( pStack->index >= 1 );

					addOTFContour( pContext );
					lineToWithStackIndex( pContext, pStack, pStack->index - 1, InvalidCharStringStackIndex );

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_endchar:
				{
					break;
				}


				case op_rlineto:
				{
					//FK: Untested
					for ( int lineIndex = 0; lineIndex < pStack->index; lineIndex += 2 )
					{
						lineToWithStackIndex( pContext, pStack, lineIndex + 0, lineIndex + 1 );
					}

					clearTrueTypeTokenStack( pStack );
					break;
				}


				case op_vlineto:
				{
					if ( pStack->index % 2 == 1 )
					{
						lineToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, 0 );
						for ( int lineIndex = 1; lineIndex < pStack->index; lineIndex += 2 )
						{
							lineToWithStackIndex( pContext, pStack, lineIndex + 0, InvalidCharStringStackIndex );
							lineToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, lineIndex + 1 );
						}
					}
					else
					{
						for ( int lineIndex = 0u; lineIndex < pStack->index; lineIndex += 2 )
						{
							lineToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, lineIndex + 0 );
							lineToWithStackIndex( pContext, pStack, lineIndex + 1, InvalidCharStringStackIndex );
						}
					}
					clearTrueTypeTokenStack( pStack );
					break;
				}


				case op_hlineto:
				{
					if ( pStack->index % 2 == 1 )
					{
						lineToWithStackIndex( pContext, pStack, 0, InvalidCharStringStackIndex );
						for ( int lineIndex = 1u; lineIndex < pStack->index; lineIndex += 2 )
						{
							lineToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, lineIndex + 0 );
							lineToWithStackIndex( pContext, pStack, lineIndex + 1, InvalidCharStringStackIndex );
						}
					}
					else
					{
						for ( int lineIndex = 0u; lineIndex < pStack->index; lineIndex += 2 )
						{
							lineToWithStackIndex( pContext, pStack, lineIndex + 0, InvalidCharStringStackIndex );
							lineToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, lineIndex + 1 );
						}
					}
					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_rrcurveto:
				{
					for ( int curveIndex = 0; curveIndex < pStack->index; curveIndex += 6 )
					{
						curveToWithStackIndex( pContext, pStack, curveIndex + 0, curveIndex + 1, curveIndex + 2, curveIndex + 3, curveIndex + 4, curveIndex + 5 );
					}

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_rcurveline:
				{
					for ( int curveIndex = 0; curveIndex < pStack->index - 2; curveIndex += 6 )
					{
						curveToWithStackIndex( pContext, pStack, curveIndex + 0, curveIndex + 1, curveIndex + 2, curveIndex + 3, curveIndex + 4, curveIndex + 5 );
					}

					lineToWithStackIndex( pContext, pStack, pStack->index - 2, pStack->index - 1 );

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_rlinecurve:
				{
					for ( int curveIndex = 0; curveIndex < pStack->index - 6; curveIndex += 2 )
					{
						lineToWithStackIndex( pContext, pStack, curveIndex + 0, curveIndex + 1 );
					}

					curveToWithStackIndex( pContext, pStack, pStack->index - 6, pStack->index - 5, pStack->index - 4, pStack->index - 3, pStack->index - 2, pStack->index - 1 );
					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_vvcurveto:
				{
					if ( pStack->index % 4 == 1 )
					{
						curveToWithStackIndex( pContext, pStack, 0, 1, 2, 3, InvalidCharStringStackIndex, 4 );
						for ( int curveIndex = 5; curveIndex < pStack->index; curveIndex += 4 )
						{
							curveToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, curveIndex + 0, curveIndex + 1, curveIndex + 2, InvalidCharStringStackIndex, curveIndex + 3 );
						}
					}
					else
					{
						for ( int curveIndex = 0; curveIndex < pStack->index; curveIndex += 4 )
						{
							curveToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, curveIndex + 0, curveIndex + 1, curveIndex + 2, InvalidCharStringStackIndex, curveIndex + 3 );
						}
					}

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_hhcurveto:
				{
					if ( pStack->index % 4 == 1 )
					{
						curveToWithStackIndex( pContext, pStack, 1, 0, 2, 3, 4, InvalidCharStringStackIndex );

						for ( int curveIndex = 5; curveIndex < pStack->index; curveIndex += 4 )
						{
							curveToWithStackIndex( pContext, pStack, curveIndex + 0, InvalidCharStringStackIndex, curveIndex + 1, curveIndex + 2, curveIndex + 3, InvalidCharStringStackIndex );
						}
					}
					else
					{
						for ( int curveIndex = 0; curveIndex < pStack->index; curveIndex += 4 )
						{
							curveToWithStackIndex( pContext, pStack, curveIndex + 0, InvalidCharStringStackIndex, curveIndex + 1, curveIndex + 2, curveIndex + 3, InvalidCharStringStackIndex );
						}
					}

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_vhcurveto:
				{
					int cnt_bezier = 0;

					if ( pStack->index % 4 == 1 )
					{
						cnt_bezier = (pStack->index - 5) / 4;
					}
					else
					{
						cnt_bezier = (pStack->index / 4);
					}

					for ( int curveIndex = 0; curveIndex < 4 * cnt_bezier; curveIndex += 4 )
					{
						if ( (curveIndex / 4) % 2 == 0 )
						{
							curveToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, curveIndex + 0, curveIndex + 1, curveIndex + 2, curveIndex + 3, InvalidCharStringStackIndex );
						}
						else
						{
							curveToWithStackIndex( pContext, pStack, curveIndex + 0, InvalidCharStringStackIndex, curveIndex + 1, curveIndex + 2, InvalidCharStringStackIndex, curveIndex + 3 );
						}
					}

					if ( pStack->index % 8 == 5 )
					{
						curveToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, pStack->index - 5, pStack->index - 4, pStack->index - 3, pStack->index - 2, pStack->index - 1 );
					}

					if ( pStack->index % 8 == 1 )
					{
						curveToWithStackIndex( pContext, pStack, pStack->index - 5, InvalidCharStringStackIndex, pStack->index - 4, pStack->index - 3, pStack->index - 1, pStack->index - 2 );
					}

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_hvcurveto:
				{
					int cnt_bezier = 0;

					if ( pStack->index % 4 == 1 )
					{
						cnt_bezier = (pStack->index - 5) / 4;
					}
					else
					{
						cnt_bezier = (pStack->index / 4);
					}

					for ( int curveIndex = 0; curveIndex < 4 * cnt_bezier; curveIndex += 4 )
					{
						if ( (curveIndex / 4) % 2 == 0 )
						{
							curveToWithStackIndex( pContext, pStack, curveIndex + 0, InvalidCharStringStackIndex, curveIndex + 1, curveIndex + 2, InvalidCharStringStackIndex, curveIndex + 3 );
						}
						else
						{
							curveToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, curveIndex + 0, curveIndex + 1, curveIndex + 2, curveIndex + 3, InvalidCharStringStackIndex );
						}
					}

					if ( pStack->index % 8 == 5 )
					{
						curveToWithStackIndex( pContext, pStack, pStack->index - 5, InvalidCharStringStackIndex, pStack->index - 4, pStack->index - 3, pStack->index - 1, pStack->index - 2 );
					}

					if ( pStack->index % 8 == 1 )
					{
						curveToWithStackIndex( pContext, pStack, InvalidCharStringStackIndex, pStack->index - 5, pStack->index - 4, pStack->index - 3, pStack->index - 2, pStack->index - 1 );
					}

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_hflex:
				{
					KEEN_ASSERT( pStack->index >= 7 );
					curveToWithStackIndex( pContext, pStack, 0, InvalidCharStringStackIndex, 1, 2, 3, InvalidCharStringStackIndex );

					const float x1 = readTokenFromTrueTypeTokenStack( pStack, 4 ).fvalue;
					const float y1 = 0.f;
					const float x2 = readTokenFromTrueTypeTokenStack( pStack, 5 ).fvalue;
					const float y2 = readTokenFromTrueTypeTokenStack( pStack, 2 ).fvalue;
					const float x3 = readTokenFromTrueTypeTokenStack( pStack, 6 ).fvalue;
					const float y3 = 0.f;

					//FK: Do per hand since we have to negate y2
					curveTo( pContext, x1, y1, x2, -y2, x3, y3 );

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_flex:
				{
					KEEN_ASSERT( pStack->index >= 12 );
					curveToWithStackIndex( pContext, pStack, 0, 1, 2, 3, 4, 5 );
					curveToWithStackIndex( pContext, pStack, 6, 7, 8, 9, 10, 11 );

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_hflex1:
				{
					KEEN_ASSERT( pStack->index >= 9 );
					curveToWithStackIndex( pContext, pStack, 0, 1, 2, 3, 4, InvalidCharStringStackIndex );

					const float x1 = readTokenFromTrueTypeTokenStack( pStack, 5 ).fvalue;
					const float y1 = 0.f;
					const float x2 = readTokenFromTrueTypeTokenStack( pStack, 6 ).fvalue;
					const float y2 = readTokenFromTrueTypeTokenStack( pStack, 7 ).fvalue;
					const float x3 = readTokenFromTrueTypeTokenStack( pStack, 8 ).fvalue;
					const float y3 = readTokenFromTrueTypeTokenStack( pStack, 1 ).fvalue + readTokenFromTrueTypeTokenStack( pStack, 3 ).fvalue + readTokenFromTrueTypeTokenStack( pStack, 7 ).fvalue;

					//FK: Do per hand since we have to negate y3
					curveTo( pContext, x1, y1, x2, y2, x3, -y3 );

					clearTrueTypeTokenStack( pStack );
					break;
				}

				case op_flex1:
				{
					KEEN_ASSERT( pStack->index >= 11 );

					const float v[] = {
						readTokenFromTrueTypeTokenStack( pStack,  0 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  1 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  2 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  3 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  4 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  5 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  6 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  7 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  8 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack,  9 ).fvalue,
						readTokenFromTrueTypeTokenStack( pStack, 10 ).fvalue,
					};

					float dx = v[0] + v[2] + v[4] + v[6] + v[8];
					float dy = v[1] + v[3] + v[5] + v[7] + v[9];

					if ( pf::abs( dx ) > pf::abs( dy ) )
					{
						dx = v[10];
						dy = -dy;
					}
					else
					{
						dx = -dx;
						dy = v[10];
					}

					curveTo( pContext, v[0], v[1], v[2], v[3], v[4], v[5] );
					curveTo( pContext, v[6], v[7], v[8], v[9], dx, dy );
					clearTrueTypeTokenStack( pStack );

					break;
				}

				case op_return:
				{
					return;
				}

				case op_callsubr:
				{
					KEEN_ASSERT( pStack->index >= 1 );
					const int subr = (int)popTokenFromTrueTypeTokenStack( pStack ).fvalue;
					executeOTFCharStringLocalSubRoutine( pTrueTypeFont, pContext, pStack, glyphIndex, subr );
					break;
				}

				case op_callgsubr:
				{
					KEEN_ASSERT( pStack->index >= 1 );
					const int gsubr = (int)popTokenFromTrueTypeTokenStack( pStack ).fvalue;
					executeOTFCharStringSubRoutine( pTrueTypeFont, pContext, pStack, &pTrueTypeFont->cffIndexes[TrueTypeCFFIndex_GlobalSubroutines], glyphIndex, gsubr );
					break;
				}

				default:
				{
					KEEN_TRACE_ERROR( "[truetype] cff token op '%d' is not supported.", token.ivalue );
					break;
				}

				}
				break;
			}

			case CharStringType_OPERAND:
			case CharStringType_FRACTION:
				pushTrueTypeTokenToStack( pStack, token );
				break;

			case CharStringType_UNKNOWN:
				KEEN_BREAK( "Error in parsing CharStringType token." );
				break;
			}

			if ( pContext->result != ErrorId_Ok )
			{
				//FK: Jump out if we encoutered an error.
				return;
			}
		}
	}

	ErrorId parseOTFOutline( ctl::Vector<TrueTypeContour>* pOutContours, ctl::Vector<TrueTypeVertex>* pOutVertices, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		const TrueTypeCFFIndexObject charStringRoutineObject = getIndexObject( pTrueTypeFont, &pTrueTypeFont->cffIndexes[TrueTypeCFFIndex_CharStrings], glyphIndex );

		if( charStringRoutineObject.dataLengthInBytes == 0u )
		{
			return ErrorId_NotFound;
		}

		uint32 offset = charStringRoutineObject.offsetToData;

		TrueTypeCharStringTokenStack	stack;
		TrueTypeCharStringContext		charStringContext;

		charStringContext.pContours = pOutContours;
		charStringContext.pVertices	= pOutVertices;

		executeOTFCharStringRoutine( pTrueTypeFont, &charStringContext, &stack, &offset, charStringRoutineObject.dataLengthInBytes, glyphIndex );

		return charStringContext.result;
	}

	ErrorId getGlyphIndexFormat4( uint32* pOutGlyphIndex, const TrueTypeFont* pTrueTypeFont, uint32 offset, Rune rune )
	{
		if( rune > 0xFFFF )
		{
			return ErrorId_NotSupported;
		}

		const uint32 cmapOffset = offset;

		//FK: Skip format
		offset += 2u;

		const uint16 tableLength = read<uint16>( pTrueTypeFont, &offset );

		//FK:	Skip language
		//		https://docs.microsoft.com/de-de/typography/opentype/spec/cmap#language
		//		The language field must be set to zero for all cmap subtables whose platform IDs are other than Macintosh (platform ID 1)
		offset += 2u;

		if( tableLength < 14u )
		{
			return ErrorId_CorruptData;
		}

		const uint16 segCount = (uint16)( read<uint16>( pTrueTypeFont, &offset ) >> 1u );

		if( tableLength < 16u + segCount * 8u )
		{
			return ErrorId_CorruptData;
		}

		uint16 searchRange		= (uint16)( read<uint16>( pTrueTypeFont, &offset ) >> 1u );
		uint16 entrySelector	= (uint16)( read<uint16>( pTrueTypeFont, &offset ) );
		uint16 rangeShift		= (uint16)( read<uint16>( pTrueTypeFont, &offset ) >> 1u );

		const uint32 endCountPosition = offset;
		uint32 search = endCountPosition;

		if( rune >= peek<uint16>( pTrueTypeFont, search + rangeShift * 2u ) )
		{
			search += rangeShift * 2u;
		}

		search -= 2u;

		while( entrySelector )
		{
			uint16 end = 0u;
			searchRange >>= 1u;

			end = peek<uint16>( pTrueTypeFont, search + searchRange * 2u );

			if( rune > end )
			{
				search += searchRange * 2u;
			}

			--entrySelector;
		}

		search += 2u;

		const uint32 item = ( ( search - endCountPosition ) >> 1u );
		const uint16 start = peek<uint16>( pTrueTypeFont, cmapOffset + 14u + segCount * 2u + 2 + 2 * item );

		if( rune < start )
		{
			return ErrorId_NotFound;
		}

		offset = peek<uint16>( pTrueTypeFont, cmapOffset + 14u + segCount * 6u + 2 + 2 * item );

		if( offset == 0u )
		{
			*pOutGlyphIndex = ( rune + peek<sint16>( pTrueTypeFont, cmapOffset + 14u + segCount * 4u + 2 + 2 * item ) ) & 0xffffu;
			return ErrorId_Ok;
		}

		*pOutGlyphIndex = peek<uint16>( pTrueTypeFont, offset + ( rune - start ) * 2u + cmapOffset + 14u + segCount * 6u + 2 + 2 * item ) & 0xffffu;
		return ErrorId_Ok;
	}

	ErrorId getGlyphIndexFormat12And13( uint32* pOutGlyphIndex, const TrueTypeFont* pTrueTypeFont, uint16 format, uint32 offset, Rune rune )
	{
		//FK: Skip format, ength, language and reserved
		offset += 12u;

		const uint32 segmentCount = read<uint32>( pTrueTypeFont, &offset );

		for( uint32 segmentIndex = 0u; segmentIndex < segmentCount; ++segmentIndex )
		{
			const uint32 startChar = read<uint32>( pTrueTypeFont, &offset );
			const uint32 endChar = read<uint32>( pTrueTypeFont, &offset );

			if( rune < startChar || rune > endChar )
			{
				offset += 4u;
				continue;
			}

			const uint32 startGlyphIndex = read<uint32>( pTrueTypeFont, &offset );

			if( format == 12u )
			{
				*pOutGlyphIndex = startGlyphIndex + rune - startChar;
				return ErrorId_Ok;
			}
			else
			{
				*pOutGlyphIndex = startGlyphIndex;
				return ErrorId_Ok;
			}
		}

		return ErrorId_NotFound;
	}


#if 0
	// https://fontforge.github.io/TrueOpenTables.html
	// https://docs.microsoft.com/de-de/typography/opentype/spec/gsub
	static KEEN_UNUSED_DECLARATION void parseGsub( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		KEEN_UNUSED1( glyphIndex );

		uint32 offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_GSUB ];
		if( offset == 0u )
		{
			return;
		}

		const uint16 majorVersion = read< uint16 >( pTrueTypeFont, &offset );
		const uint16 minorVersion = read< uint16 >( pTrueTypeFont, &offset );
		const uint16 scriptListOffset = read< uint16 >( pTrueTypeFont, &offset );
		const uint16 featureListOffset = read< uint16 >( pTrueTypeFont, &offset );
		const uint16 lookupListOffset  = read< uint16 >( pTrueTypeFont, &offset );
		KEEN_UNUSED5( majorVersion, minorVersion, scriptListOffset, featureListOffset, lookupListOffset );

		KEEN_TRACE_INFO( "gsub: v %u.%u\n",majorVersion, minorVersion );
	}

	// https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6morx.html
	static KEEN_UNUSED_DECLARATION void parseMorx( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex ) 
	{
		KEEN_UNUSED1( glyphIndex );

		uint32 offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_MORX ];
		if( offset == 0u )
		{
			return;
		}

		const uint16 version = read< uint16 >( pTrueTypeFont, &offset );
		offset += 2u;
		const uint32 nChains = read< uint32 >( pTrueTypeFont, &offset );
		KEEN_UNUSED2( version, nChains );

		KEEN_TRACE_INFO( "morx: v %u  c %u\n", version, nChains );

		for( uint32 chainIndex = 0u; chainIndex < nChains; ++chainIndex )
		{
			const uint32 defaultFlags		= read< uint32 >( pTrueTypeFont, &offset );
			const uint32 chainLength		= read< uint32 >( pTrueTypeFont, &offset );
			const uint32 nFeatureEntries	= read< uint32 >( pTrueTypeFont, &offset );
			const uint32 nSubtables			= read< uint32 >( pTrueTypeFont, &offset );
			KEEN_UNUSED4( defaultFlags, chainLength, nFeatureEntries, nSubtables );

			KEEN_TRACE_INFO( "  flags:%u  length:%u  feat:%u  subtab:%u\n", defaultFlags, chainLength, nFeatureEntries, nSubtables );

			for( uint32 featureIndex = 0u; featureIndex < nFeatureEntries; ++featureIndex )
			{
				const uint16 featureType	= read< uint16 >( pTrueTypeFont, &offset );
				const uint16 featureSetting	= read< uint16 >( pTrueTypeFont, &offset );
				const uint32 enableFlags	= read< uint32 >( pTrueTypeFont, &offset );
				const uint32 disableFlags	= read< uint32 >( pTrueTypeFont, &offset );
				KEEN_UNUSED4( featureType, featureSetting, enableFlags, disableFlags );
				
				KEEN_TRACE_INFO( "    feat:%u  sett:%u  flags:%08x  !flags:%08x\n", featureType, featureSetting, enableFlags, disableFlags );
			}
		}

		KEEN_TRACE_INFO( "zink\n" );
	}
#endif

	ErrorId parseTrueTypeGlyphIndex( uint32* pOutGlyphIndex, const TrueTypeFont* pTrueTypeFont, Rune rune )
	{
		if( ( ( rune & 0xffffu ) == 0xffffu ) || ( ( rune & 0xffffu ) == 0xfffeu ) || ( ( rune >= 0xfdd0u ) && ( rune <= 0xfdefu ) ) )
		{
			return ErrorId_InvalidArgument;
		}

		if( !isValidTrueTypeFont( pTrueTypeFont ) )
		{
			return ErrorId_InvalidArgument;
		}

		uint32 offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CMAP ];

		//FK: Skip version entry in CMAP table
		offset += 2u;

		const uint16 numEncodingTables = read<uint16>( pTrueTypeFont, &offset );
		uint32 cmapBlockOffset = 0u;

		for( uint16 tableIndex = 0u; tableIndex < numEncodingTables; ++tableIndex )
		{
			uint32 encodingEntryOffset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CMAP ] + 4u + 8u * tableIndex;

			const uint16 encodingPlatform = read<uint16>( pTrueTypeFont, &encodingEntryOffset );

			switch( encodingPlatform )
			{
			case TrueTypePlatformID_Microsoft:
			{
				const uint16 encodingID = read<uint16>( pTrueTypeFont, &encodingEntryOffset );

				switch( encodingID )
				{
				case TrueTypeMicrosoftEncodingID_Unicode_BMP:
				case TrueTypeMicrosoftEncodingID_Unicode_Full:
					cmapBlockOffset = peek<uint32>( pTrueTypeFont, encodingEntryOffset );
					break;
				}
				break;
			}

			case TrueTypePlatformID_Unicode:
			{
				//FK: Skip Platform-specific encoding ID
				encodingEntryOffset += 2u;
				cmapBlockOffset = peek<uint32>( pTrueTypeFont, encodingEntryOffset );
				break;
			}
			}

			if( cmapBlockOffset == 0u )
			{
				continue;
			}

			const uint32 cmapBlockPosition = cmapBlockOffset + pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CMAP ];
			offset = cmapBlockPosition;

			const uint16 format = peek<uint16>( pTrueTypeFont, offset );

			ErrorId result = ErrorId_NotImplemented;

			if( format == 4u )
			{
				result = getGlyphIndexFormat4( pOutGlyphIndex, pTrueTypeFont, offset, rune );
			}
			else if( format == 12 || format == 13 )
			{
				result = getGlyphIndexFormat12And13( pOutGlyphIndex, pTrueTypeFont, format, offset, rune );
			}
			else
			{
				KEEN_NOT_IMPLEMENTED;
			}

			if( result == ErrorId_Ok )
			{
				return result;
			}
		}

		return ErrorId_NotFound;
	}

	uint32 getTrueTypeGlyphCount( const TrueTypeFont* pTrueTypeFont )
	{
		return (uint32)peek<uint16>( pTrueTypeFont, pTrueTypeFont->tableOffsets[ TrueTypeFontTable_MAXP ] + 4u );
	}

	ErrorId findMatchingSBIXBitmapEntry( uint32* pOutOffset, uint32* pOutDataSizeInBytes, uint32* pOutPPEM, uint32 ppemPreferred, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		const uint32 glyphCount = getTrueTypeGlyphCount( pTrueTypeFont );

		if( glyphIndex > glyphCount )
		{
			return ErrorId_NotFound;
		}

		uint32 offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_SBIX ];

		const uint16 version = read<uint16>( pTrueTypeFont, &offset );
		offset += 2u; //FK: Skip flags

		if( version != 1 )
		{
			return ErrorId_WrongVersion;
		}

		const uint32 strikeCount = read<uint32>( pTrueTypeFont, &offset );
		if( strikeCount == 0u )
		{
			return ErrorId_NotFound;
		}

		uint32	dataOffset			= 0u;
		uint32	dataSizeInBytes		= 0u;
		uint32	strikeOffset		= 0u;
		bool	foundStrike			= false;

		for( uint32 strikeIndex = 1u; strikeIndex < strikeCount; ++strikeIndex )
		{
			strikeOffset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_SBIX ] + read<uint32>( pTrueTypeFont, &offset );
			const uint32 ppem = peek<uint16>( pTrueTypeFont, strikeOffset + 0u );

			//FK: check if can find a bitmap with a better resolution as long as we're not at the end of strike array
			if( strikeIndex < ( strikeCount - 1u ) )
			{
				if( ppemPreferred > ppem )
				{
					continue;
				}
			}

			const uint32 nextDataOffset = peek<uint32>( pTrueTypeFont, strikeOffset + 4u + 4u * ( glyphIndex + 1 ) );

			dataOffset		= peek<uint32>( pTrueTypeFont, strikeOffset + 4u + 4u * glyphIndex );
			dataSizeInBytes = nextDataOffset - dataOffset;

			if( dataSizeInBytes != 0u )
			{
				if( pOutPPEM != nullptr )
				{
					*pOutPPEM = ppem;
				}

				foundStrike = true;
				break;
			}
		}

		if( !foundStrike )
		{
			return ErrorId_NotFound;
		}

		if( pOutOffset != nullptr )
		{
			*pOutOffset = strikeOffset + dataOffset;
		}

		if( pOutDataSizeInBytes != nullptr )
		{
			*pOutDataSizeInBytes = dataSizeInBytes;
		}

		return ErrorId_Ok;
	}

	ErrorId findMatchingBLCBitmapEntry( int2* pOutBearing, uint2* pOutPPEM, uint32* pOutOffset, uint32* pOutDataSizeInBytes, uint32 ppemPreferred, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		KEEN_UNUSED1( ppemPreferred );

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_EBLC ] == 0u && pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CBLC ] == 0u )
		{
			return ErrorId_NotFound;
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_EBDT ] == 0u && pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CBDT ] == 0u )
		{
			return ErrorId_NotFound;
		}

		static const uint32 metricsSize = 12u;

		const uint32 locationTableOffset	= pTrueTypeFont->tableOffsets[ TrueTypeFontTable_EBLC ] == 0u ? pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CBLC ] : pTrueTypeFont->tableOffsets[ TrueTypeFontTable_EBLC ];
		const uint32 dataTableOffset		= pTrueTypeFont->tableOffsets[ TrueTypeFontTable_EBDT ] == 0u ? pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CBDT ] : pTrueTypeFont->tableOffsets[ TrueTypeFontTable_EBDT ];

		uint32 offset = locationTableOffset;
		const uint16 majorVersion = read<uint16>( pTrueTypeFont, &offset );
		const uint16 minorVersion = read<uint16>( pTrueTypeFont, &offset );

		if( majorVersion != 2 && majorVersion != 3 )
		{
			//FK: We only support version 2 (eblc) or version 3 (cblc)
			return ErrorId_NotSupported;
		}

		if( minorVersion != 0 )
		{
			//FK: We only support version 2.0 (eblc) or version 3.0 (cblc)
			return ErrorId_NotSupported;
		}

		const uint32 tableCount = read<uint32>( pTrueTypeFont, &offset );

		for( uint32 tableIndex = 0u; tableIndex < tableCount; ++tableIndex )
		{
			const uint32 indexSubTableArrayOffset = locationTableOffset + read<uint32>( pTrueTypeFont, &offset );

			//FK: Skip index table size
			offset += 4u;
			
			const uint32 indexSubTableCount	= read<uint32>( pTrueTypeFont, &offset);

			//FK: Skip colorRef, startGlyph, endGlyph, hori and vert metrics
			offset += 8u + 2 * metricsSize;

			const uint8 ppemX = read<uint8>( pTrueTypeFont, &offset );
			const uint8 ppemY = read<uint8>( pTrueTypeFont, &offset );

			if( pOutPPEM != nullptr )
			{
				pOutPPEM->x = ppemX;
				pOutPPEM->y = ppemY;
			}

			const uint8 bitDepth = read<uint8>( pTrueTypeFont, &offset );

			if( bitDepth != 32u )
			{
				//FK: only support bitdepth == 32 (png) for now
				return ErrorId_NotSupported;
			}

			//FK: We'll be needing those later
			const uint8 flags = read<uint8>( pTrueTypeFont, &offset );

			for( uint32 indexTableIndex = 0u; indexTableIndex < indexSubTableCount; ++indexTableIndex )
			{
				const uint32 subTableArrayOffset = indexSubTableArrayOffset + 8 * indexTableIndex;

				const uint16 firstGlyphIndex	= peek<uint16>( pTrueTypeFont, subTableArrayOffset + 0u );
				const uint16 lastGlyphIndex		= peek<uint16>( pTrueTypeFont, subTableArrayOffset + 2u );

				if( glyphIndex < firstGlyphIndex || glyphIndex > lastGlyphIndex )
				{
					continue;
				}

				const uint32 additionalOffsetToIndexSubTable	= peek<uint32>( pTrueTypeFont, subTableArrayOffset + 4u );
				const uint32 indexSubTableOffset				= indexSubTableArrayOffset + additionalOffsetToIndexSubTable;

				const uint16 indexFormat		= peek<uint16>( pTrueTypeFont, indexSubTableOffset + 0u );
				const uint16 imageFormat		= peek<uint16>( pTrueTypeFont, indexSubTableOffset + 2u );
				const uint32 imageDataOffset	= peek<uint32>( pTrueTypeFont, indexSubTableOffset + 4u );

				uint32 bitmapDataOffset = 0u;
				uint32 bitmapDataSizeInBytes = 0u;

				if( indexFormat == 1u )
				{
					//FK: adjust glyph index to access the correct data
					glyphIndex -= firstGlyphIndex;

					//FK: get data size by subtracting the offset of the next glyph from the offset of the glyph we're actually looking for
					const uint32 nextBitmapDataOffset = imageDataOffset + peek<uint32>( pTrueTypeFont, indexSubTableOffset + 8u + ( glyphIndex + 1u ) * 4u );

					bitmapDataOffset		= imageDataOffset + peek<uint32>( pTrueTypeFont, indexSubTableOffset + 8u + glyphIndex * 4u );
					bitmapDataSizeInBytes	= nextBitmapDataOffset - bitmapDataOffset;
				}
				else
				{
					return ErrorId_NotSupported;
				}
				
				switch( imageFormat )
				{
				case 17:
					if( pOutBearing != nullptr )
					{
						pOutBearing->x = peek<sint8>( pTrueTypeFont, dataTableOffset + bitmapDataOffset + 2u );
						pOutBearing->y = peek<sint8>( pTrueTypeFont, dataTableOffset + bitmapDataOffset + 3u );
					}

					if( pOutOffset != nullptr )
					{
						const uint32 offsetToPNGData = 9u;
						*pOutOffset = dataTableOffset + bitmapDataOffset + offsetToPNGData;
					}

					if( pOutDataSizeInBytes != nullptr )
					{
						*pOutDataSizeInBytes = bitmapDataSizeInBytes;
					}

					return ErrorId_Ok;
				case 18:
					if( pOutBearing != nullptr )
					{
						if( ( flags & TrueTypeBitmapFlag_HorizontalMetrics ) > 0u )
						{
							pOutBearing->x = peek<sint8>( pTrueTypeFont, dataTableOffset + bitmapDataOffset + 2u );
							pOutBearing->y = peek<sint8>( pTrueTypeFont, dataTableOffset + bitmapDataOffset + 3u );
						}
						else if( ( flags & TrueTypeBitmapFlag_VerticalMetrics ) > 0u )
						{
							pOutBearing->x = peek<sint8>( pTrueTypeFont, dataTableOffset + bitmapDataOffset + 5u );
							pOutBearing->y = peek<sint8>( pTrueTypeFont, dataTableOffset + bitmapDataOffset + 6u );
						}
					}

					if( pOutOffset != nullptr )
					{
						const uint32 offsetToPNGData = 12u;
						*pOutOffset = dataTableOffset + bitmapDataOffset + offsetToPNGData;
					}

					if( pOutDataSizeInBytes != nullptr )
					{
						*pOutDataSizeInBytes = bitmapDataSizeInBytes;
					}

					return ErrorId_Ok;
				default:
					return ErrorId_NotSupported;
				}
			}
		}

		return ErrorId_NotFound;
	}

	static Result<ConstMemoryBlock> parseSBIXGlyphBitmap( int2* pOutBearing, uint2* pOutPPEM, uint32 ppemPreferred, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		uint32 offset			= 0u;
		uint32 dataSizeInBytes	= 0u;
		uint32 ppem				= 0u;
		const ErrorId result = findMatchingSBIXBitmapEntry( &offset, &dataSizeInBytes, &ppem, ppemPreferred, pTrueTypeFont, glyphIndex );

		if( result != ErrorId_Ok )
		{
			return createResult<ConstMemoryBlock>( InvalidConstMemoryBlock, result );
		}

		if( pOutPPEM != nullptr )
		{
			pOutPPEM->x = ppem;
			pOutPPEM->y = ppem;
		}

		if( pOutBearing != nullptr )
		{
			pOutBearing->x = peek<sint16>( pTrueTypeFont, offset + 0u);
			pOutBearing->y = (sint16)ppem + peek<sint16>( pTrueTypeFont, offset + 2u);
		}
		offset += 4u;

		const char graphicsTypeFourCC[] = {
			read<char>( pTrueTypeFont, &offset ),
			read<char>( pTrueTypeFont, &offset ),
			read<char>( pTrueTypeFont, &offset ),
			read<char>( pTrueTypeFont, &offset ),
			0
		};

		if( graphicsTypeFourCC[ 0u ] == 'p' &&
			graphicsTypeFourCC[ 1u ] == 'n' &&
			graphicsTypeFourCC[ 2u ] == 'g' &&
			graphicsTypeFourCC[ 3u ] == ' ' )
		{
			ConstMemoryBlock bitmapDataBlob = createConstMemoryBlock( pTrueTypeFont->trueTypeBlob.pStart + offset, dataSizeInBytes - 8u );
			return createOkResult<ConstMemoryBlock>( bitmapDataBlob );
		}

		return createResult<ConstMemoryBlock>( InvalidConstMemoryBlock, ErrorId_NotSupported );
	}

	static Result<ConstMemoryBlock> parseCBLCGlyphBitmap( int2* pOutBearing, uint2* pOutPPEM, uint32 ppemPreferred, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		KEEN_UNUSED1( pOutBearing );

		uint32 offset = 0u;
		uint32 dataSizeInBytes = 0u;
		const ErrorId result = findMatchingBLCBitmapEntry( pOutBearing, pOutPPEM, &offset, &dataSizeInBytes, ppemPreferred, pTrueTypeFont, glyphIndex );

		if( result != ErrorId_Ok )
		{
			return createResult<ConstMemoryBlock>( InvalidConstMemoryBlock, result );
		}

		ConstMemoryBlock bitmapDataBlob = createConstMemoryBlock( pTrueTypeFont->trueTypeBlob.pStart + offset, dataSizeInBytes );
		return createOkResult<ConstMemoryBlock>( bitmapDataBlob );
	}

	//////////////////////////////////////////////////////////////////////////

	ErrorId initTrueTypeFont( TrueTypeFont* pTrueTypeFont, const uint8* pFontBuffer, size_t fontBufferSize, uint32 fontBufferOffset )
	{
		KEEN_ASSERT( pTrueTypeFont );
		KEEN_ASSERT( pFontBuffer );
		KEEN_ASSERT( fontBufferSize > 0u );

		uint32 offset = fontBufferOffset;
		const uint32 sfnt = peek<uint32>( pFontBuffer, fontBufferSize, offset );
		offset += 4u;

		if( sfnt != TrueTypeSFNT_TrueType1 && sfnt != TrueTypeSFNT_TrueType2 && sfnt != TrueTypeSFNT_OpenType )
		{
			return ErrorId_WrongVersion;
		}

		pTrueTypeFont->sfnt = sfnt;
		pTrueTypeFont->offset = fontBufferOffset;
		pTrueTypeFont->numTables = peek<uint16>( pFontBuffer, fontBufferSize, offset );
		pTrueTypeFont->trueTypeBlob = createConstMemoryBlock( pFontBuffer, fontBufferSize );

		retrieveTableOffsets( pTrueTypeFont );
		retrieveTrueTypeNames( pTrueTypeFont );

		if( sfnt == TrueTypeSFNT_OpenType )
		{
			retrieveOpenTypeIndexes( pTrueTypeFont );
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_HEAD ] != 0u )
		{
			offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_HEAD ] + TrueTypeDataOffset_IndexToLoca;
			pTrueTypeFont->indexToLocaFormat = peek<sint16>( pFontBuffer, fontBufferSize, offset );

			offset = pTrueTypeFont->tableOffsets[ TrueTypeFontTable_HEAD ] + TrueTypeDataOffset_Flags;
			pTrueTypeFont->flags = peek<uint16>( pFontBuffer, fontBufferSize, offset );
		}

		if( !isValidTrueTypeFont( pTrueTypeFont ) )
		{
			return ErrorId_CorruptData;
		}

		retrieveTrueTypeFontMetrics( pTrueTypeFont );

		return ErrorId_Ok;
	}

	ErrorId parseTrueTypeGlyphOutline( ctl::Vector<TrueTypeContour>* pOutContours, ctl::Vector<TrueTypeVertex>* pOutVertices, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		KEEN_ASSERT( pOutContours );
		KEEN_ASSERT( pOutVertices );
		KEEN_ASSERT( pTrueTypeFont );

		if( !isValidTrueTypeFont( pTrueTypeFont ) || ( glyphIndex == TrueTypeGlphyIndex_Invalid ) )
		{
			return ErrorId_InvalidArgument;
		}

		if ( pTrueTypeFont->tableOffsets[TrueTypeFontTable_GLYF] > 0u )
		{
			return parseTTFOutline( pOutContours, pOutVertices, pTrueTypeFont, glyphIndex );
		}
		
		if ( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CFF ] > 0u )
		{
			return parseOTFOutline( pOutContours, pOutVertices, pTrueTypeFont, glyphIndex );
		}

		return ErrorId_NotFound;
	}

	Result<ConstMemoryBlock> parseTrueTypeGlyphBitmap( int2* pOutBearing, uint2* pOutPPEM, uint32 ppemPreferred, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		if( !isValidTrueTypeFont( pTrueTypeFont ) || ( glyphIndex == TrueTypeGlphyIndex_Invalid ) )
		{
			return createResult< ConstMemoryBlock >( InvalidConstMemoryBlock, ErrorId_InvalidArgument );
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_SBIX ] != 0u )
		{
			return parseSBIXGlyphBitmap( pOutBearing, pOutPPEM, ppemPreferred, pTrueTypeFont, glyphIndex );
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CBLC ] != 0u )
		{
			return parseCBLCGlyphBitmap( pOutBearing, pOutPPEM, ppemPreferred, pTrueTypeFont, glyphIndex );
		}

		return createResult< ConstMemoryBlock >( InvalidConstMemoryBlock, ErrorId_NotFound );
	}

	TrueTypeGlyphType getTrueTypeGlyphType( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		if( glyphIndex == TrueTypeGlphyIndex_Invalid )
		{
			return TrueTypeGlyphType_None;
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_SBIX ] > 0u )
		{
			if( findMatchingSBIXBitmapEntry( nullptr, nullptr, nullptr, 0u, pTrueTypeFont, glyphIndex ) == ErrorId_Ok )
			{
				return TrueTypeGlyphType_Bitmap;
			}
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CBLC ] > 0u )
		{
			if( findMatchingBLCBitmapEntry( nullptr, nullptr, nullptr, nullptr, 0u, pTrueTypeFont, glyphIndex ) == ErrorId_Ok )
			{
				return TrueTypeGlyphType_Bitmap;
			}
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_GLYF ] > 0u )
		{
			if( getGlyfOffset( pTrueTypeFont, glyphIndex ) > 0 )
			{
				return TrueTypeGlyphType_Spline;
			}
		}

		if( pTrueTypeFont->tableOffsets[ TrueTypeFontTable_CFF ] > 0u )
		{
			const TrueTypeCFFIndexObject charStringRoutineObject = getIndexObject( pTrueTypeFont, &pTrueTypeFont->cffIndexes[ TrueTypeCFFIndex_CharStrings ], glyphIndex );

			if( charStringRoutineObject.dataLengthInBytes > 0u )
			{
				return TrueTypeGlyphType_Spline;
			}
		}

		return TrueTypeGlyphType_None;
	}

	uint32 getTrueTypeGlyphIndex( const TrueTypeFont* pTrueTypeFont, Rune charCode )
	{
		KEEN_ASSERT( pTrueTypeFont );

		uint32 glyphIndex = 0u;
		const ErrorId result = parseTrueTypeGlyphIndex( &glyphIndex, pTrueTypeFont, charCode );
		if( result == ErrorId_Ok )
		{
			return glyphIndex;
		}

		return TrueTypeGlphyIndex_Invalid;
	}

	uint32 getTrueTypeGlyphIndex( const TrueTypeFont* pTrueTypeFont, const ctl::ConstArray< Rune >& runes )
	{
		KEEN_ASSERT( pTrueTypeFont );

		// :TODO: get all rune glyphs

		uint32 glyphIndex = 0u;
		const ErrorId result = parseTrueTypeGlyphIndex( &glyphIndex, pTrueTypeFont, runes[ 0u ] );
		if( result != ErrorId_Ok )
		{
			return TrueTypeGlphyIndex_Invalid;
		}

		// test code
		if( glyphIndex != 0u )
		{
			//parseGsub( pTrueTypeFont, glyphIndex );
			//parseMorx( pTrueTypeFont, glyphIndex );
		}

		return glyphIndex;
	}

	bool getTrueTypeGlyphMetric( TrueTypeGlyphMetrics* pOutGlyphMetrics, int4* pOutGlyphBoundingBox, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex )
	{
		KEEN_ASSERT( pOutGlyphMetrics );
		KEEN_ASSERT( pOutGlyphBoundingBox );

		if( glyphIndex == TrueTypeGlphyIndex_Invalid ) 
		{
			return false;
		}

		*pOutGlyphMetrics = parseTrueTypeGlyphMetric( pTrueTypeFont, glyphIndex );

		if( pTrueTypeFont->sfnt == TrueTypeSFNT_OpenType )
		{
			*pOutGlyphBoundingBox = parseOTFGlyphBoundingBox( pTrueTypeFont, glyphIndex );
		}
		else if (pTrueTypeFont->sfnt == TrueTypeSFNT_TrueType1 || pTrueTypeFont->sfnt == TrueTypeSFNT_TrueType2 )
		{
			const int glyfOffset = getGlyfOffset( pTrueTypeFont, glyphIndex );
			*pOutGlyphBoundingBox = parseTTFGlyphBoundingBox( pTrueTypeFont, glyfOffset );
		}

		return true;
	}

	bool isTrueTypeNameMatch( const TrueTypeFont* pTrueTypeFont, const char* pFontName )
	{
		KEEN_ASSERT( pTrueTypeFont );
		KEEN_ASSERT( pFontName );

		if( isStringEqual( pTrueTypeFont->family.fontName, pFontName ) )
		{
			return true;
		}

		//FK: create temporary font names for further checks
		static const char s_Separators[] = {
			'-', ' ', '_'
		};

		for( uint32 separatorIndex = 0u; separatorIndex < KEEN_COUNTOF( s_Separators ); ++separatorIndex )
		{
			static const size_t s_StringLength = 256u;
			char temporaryFontName[ s_StringLength ];

			const size_t stringOffset = copyString( temporaryFontName, pTrueTypeFont->family.fontFamiliyName, s_StringLength );
			temporaryFontName[ stringOffset ] = s_Separators[separatorIndex];

			copyString( temporaryFontName + stringOffset + 1u, pTrueTypeFont->family.fontStyle, s_StringLength - ( stringOffset + 1u ) );

			if( isStringEqualNoCase( pFontName, temporaryFontName ) )
			{
				return true;
			}
		}

		return false;
	}

	bool isTrueTypeCollection( const uint8* pFontBuffer, size_t fontBufferSize )
	{
		KEEN_ASSERT( pFontBuffer );
		
		if( fontBufferSize < 4u )
		{
			return false;
		}

		return ( pFontBuffer[ 0u ] == 't' && 
			pFontBuffer[ 1u ] == 't' && 
			pFontBuffer[ 2u ] == 'c' && 
			pFontBuffer[ 3u ] == 'f' );
	}

	ErrorId findOffsetForFontInTrueTypeCollection( uint32* pOutOffset, const uint8* pFontBuffer, size_t fontBufferSize, const char* pFontName )
	{
		KEEN_ASSERT( pFontBuffer );
		KEEN_ASSERT( fontBufferSize > 0u );
		KEEN_ASSERT( pFontName );

		if( !isTrueTypeCollection( pFontBuffer, fontBufferSize ) )
		{
			return ErrorId_IncompatibleData;
		}

		uint32 offset = 8u; //FK: skip fourCC and version
		const uint32 fontCount = peek<uint32>( pFontBuffer, fontBufferSize, offset );
		offset += 4u;

		for( uint32 fontIndex = 0u; fontIndex < fontCount; ++fontIndex, offset += 4u)
		{
			const uint32 fontOffset = peek<uint32>( pFontBuffer, fontBufferSize, offset );

			TrueTypeFont font;
			const ErrorId result = initTrueTypeFont( &font, pFontBuffer, fontBufferSize, fontOffset );

			if( result != ErrorId_Ok )
			{
				return result;
			}

			if( isTrueTypeNameMatch( &font, pFontName ) )
			{
				if( pOutOffset != nullptr )
				{
					*pOutOffset = fontOffset;
				}

				return ErrorId_Ok;
			}
		}

		return ErrorId_NotFound;
	}

	ErrorId findOffsetForFontInTrueTypeCollection( uint32* pOutOffset, const uint8* pFontBuffer, size_t fontBufferSize, uint32 fontIndex )
	{
		KEEN_ASSERT( pFontBuffer );
		KEEN_ASSERT( fontBufferSize > 0u );

		if( !isTrueTypeCollection( pFontBuffer, fontBufferSize ) )
		{
			return ErrorId_IncompatibleData;
		}

		uint32 offset = 8u; //FK: skip fourCC and version
		const uint32 fontCount = peek<uint32>( pFontBuffer, fontBufferSize, offset );

		if( fontCount <= fontIndex )
		{
			return ErrorId_NotFound;
		}

		*pOutOffset = offset + ( fontIndex + 1u ) * 4u;

		return ErrorId_Ok;
	}

	int getTrueTypeKerningFromIndex( const TrueTypeFont* pTrueTypFont, uint32 leftGlyphIndex, uint32 rightGlyphIndx )
	{
		if( ( leftGlyphIndex == TrueTypeGlphyIndex_Invalid ) || ( rightGlyphIndx == TrueTypeGlphyIndex_Invalid ) )
		{
			return 0;
		}

		if( pTrueTypFont->tableOffsets[ TrueTypeFontTable_KERN ] == 0 )
		{
			return 0;
		}

		uint32 offset = pTrueTypFont->tableOffsets[ TrueTypeFontTable_KERN ];

		//FK: Skip version
		offset += 2u;

		const uint16 numKernTables = read<uint16>( pTrueTypFont, &offset );

		if( numKernTables < 1 )
		{
			return 0;
		}

		//FK: We only look at the first table here


		//FK: Skip table length
		offset += 4;
		const uint16 coverageFlags = read<uint16>( pTrueTypFont, &offset );

		//FK: Check for horizontal flag
		if( coverageFlags != 1 )
		{
			return 0;
		}

		uint32 straw = 0u;

		int l = 0u;
		int m = 0u;
		int r = read<uint16>( pTrueTypFont, &offset ) - 1;
		const uint32 needle = ( leftGlyphIndex << 16 ) | rightGlyphIndx;

		offset = pTrueTypFont->tableOffsets[ TrueTypeFontTable_KERN ];

		while( l <= r )
		{
			m = ( l + r ) >> 1;
			straw = peek<uint32>( pTrueTypFont, offset + 18 + ( m * 6 ) );
			if( needle < straw )
			{
				r = m - 1;
			}
			else if( needle > straw )
			{
				l = m + 1;
			}
			else
			{
				return peek<sint16>( pTrueTypFont, offset + 22 + ( m * 6 ) );
			}
		}

		return 0;
	}

	int getTrueTypeKerning( const TrueTypeFont* pTrueTypFont, Rune runeLeft, Rune runeRight )
	{
		KEEN_ASSERTE( pTrueTypFont != nullptr );

		return getTrueTypeKerningFromIndex( pTrueTypFont, getTrueTypeGlyphIndex( pTrueTypFont, runeLeft ), getTrueTypeGlyphIndex( pTrueTypFont, runeRight ) );
	}
}
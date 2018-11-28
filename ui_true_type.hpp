#ifndef KEEN_UI_TRUE_TYPE_HEADER
#define KEEN_UI_TRUE_TYPE_HEADER

#include "keen/base/base_types.hpp"
#include "keen/base/ctl.hpp"

namespace keen
{
	class MemoryAllocator;
	//FK: Only relevant tables are listed
	enum TrueTypeFontTable
	{
		TrueTypeFontTable_CFF,		//Holds glyph outline vertices (only for OpenType fonts)
		TrueTypeFontTable_CFF2,		//Holds glyph outline vertices (only for OpenType fonts)
		TrueTypeFontTable_GLYF,		//Holds glyph outline vertices (only for TrueType fonts)
		TrueTypeFontTable_KERN,		//Holds kerning informations 
		TrueTypeFontTable_HEAD,		//Holds general informations 
		TrueTypeFontTable_HHEA,
		TrueTypeFontTable_KERX,		//Holds kerning informations (more compressed format) 
		TrueTypeFontTable_LOCA,		//Holds informations on how to access the GLYF table (only required for TrueType fonts)
		TrueTypeFontTable_MAXP,		//Holds memory related informations (how many glyphs, points, etc)
		TrueTypeFontTable_HMTX,		//Holds horizontal glyph metrics
		TrueTypeFontTable_VMTX,		//Holds vertical glyph metrics
		TrueTypeFontTable_CMAP,		//Holds mapping from unicode value to char index (used as an index into other tables to get information on a glyph basis - Only required for TrueType fonts)
		TrueTypeFontTable_SBIX,
		TrueTypeFontTable_NAME,
		TrueTypeFontTable_LTAG,
		TrueTypeFontTable_SVG,
		TrueTypeFontTable_EBDT,
		TrueTypeFontTable_EBLC,
		TrueTypeFontTable_EBSC,
		TrueTypeFontTable_COLR,
		TrueTypeFontTable_CBDT,
		TrueTypeFontTable_CBLC,

		TrueTypeFontTable_GSUB,
		TrueTypeFontTable_MORX,

		TrueTypeFontTable_Count
	};

	enum TrueTypeCFFIndexType
	{
		TrueTypeCFFIndex_Name,
		TrueTypeCFFIndex_TopDict,
		TrueTypeCFFIndex_String,
		TrueTypeCFFIndex_GlobalSubroutines,
		TrueTypeCFFIndex_CharStrings,

		TrueTypeCFFIndex_Count
	};

	enum TrueTypeFontGlyphFlag
	{
		TrueTypeFontGlyphFlag_OnCurve		= 0x01,
		TrueTypeFontGlyphFlag_XShortVector	= 0x02,
		TrueTypeFontGlyphFlag_YShortVector	= 0x04,
		TrueTypeFontGlyphFlag_Repeat		= 0x08,
		TrueTypeFontGlyphFlag_ThisXIsSame	= 0x10,
		TrueTypeFontGlyphFlag_ThisYIsSame	= 0x20
	};

	enum TrueTypeFontVertexType
	{
		TrueTypeFontVertexType_OnCurve,
		TrueTypeFontVertexType_Quadratic,
		TrueTypeFontVertexType_Cubic
	};

	enum TrueTypeGlyphType
	{
		TrueTypeGlyphType_None	= 0,
		TrueTypeGlyphType_Spline,
		TrueTypeGlyphType_Bitmap
	};

	struct TrueTypeFontMetrics
	{
		sint16 ascent;
		sint16 descent;
		sint16 capHeight;
		sint16 lineGap;
		uint16 unitsPerEm;
	};

	enum 
	{
		MaxFontName = 128u
	};

	struct TrueTypeFontFamily
	{
		char fontName[ MaxFontName ];
		char fontFamiliyName[ MaxFontName ];
		char fontStyle[ MaxFontName ];
	};

	struct TrueTypeCFFIndex
	{
		uint32			offsetToDataOffset;
		uint32			offsetToData;
		uint32			dataSize;
		uint16			entryCount;
		uint8			offsetSize;
	};

	struct TrueTypeFont
	{
		uint32				tableOffsets[TrueTypeFontTable_Count];
		TrueTypeCFFIndex	cffIndexes[ TrueTypeCFFIndex_Count ];
		ConstMemoryBlock	trueTypeBlob;
		uint32				sfnt;
		uint32				offset;
		uint16				numTables;
		uint16				flags;
		sint16				indexToLocaFormat;
		uint32				charStringType;
		TrueTypeFontMetrics	metrics;
		TrueTypeFontFamily	family;
	};

	struct TrueTypeVertex
	{
		TrueTypeFontVertexType	type;
		uint8					flags;
		sint16					xCoordinate;
		sint16					yCoordinate;
	};

	struct TrueTypeContour
	{
		uint32 startIndex;
		uint32 length;
	};

	struct TrueTypeGlyphData
	{
		uint32	glyphIndex;
		int		glyfOffset;
	};

	struct TrueTypeGlyphMetrics
	{
		sint16	advanceWidth;
		sint16	leftSideBearing;
	};

	enum
	{
		TrueTypeGlphyIndex_Invalid = 0xffffffffu
	};

	ErrorId						initTrueTypeFont( TrueTypeFont* pTrueTypeFont, const uint8* pFontBuffer, size_t fontBufferSize, uint32 offset = 0u );

	uint32						getTrueTypeGlyphIndex( const TrueTypeFont* pTrueTypeFont, Rune charCode );
	uint32						getTrueTypeGlyphIndex( const TrueTypeFont* pTrueTypeFont, const ctl::ConstArray< Rune >& runes );
	
	TrueTypeGlyphType			getTrueTypeGlyphType( const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex );
	bool						getTrueTypeGlyphMetric( TrueTypeGlyphMetrics* pOutGlyphMetrics, int4* pOutBoundingBox, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex );
	
	ErrorId						parseTrueTypeGlyphOutline( ctl::Vector<TrueTypeContour>* pOutContours, ctl::Vector<TrueTypeVertex>* pOutVertices, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex );
	Result< ConstMemoryBlock >	parseTrueTypeGlyphBitmap( int2* pOutBearing, uint2* pOutPPEM, uint32 ppemPreferred, const TrueTypeFont* pTrueTypeFont, uint32 glyphIndex );

	bool						isTrueTypeNameMatch( const TrueTypeFont* pTrueTypeFont, const char* pFontName );
	bool						isTrueTypeCollection( const uint8* pFontBuffer, size_t fontBufferSize );
	ErrorId						findOffsetForFontInTrueTypeCollection( uint32* pOutOffset, const uint8* pFontBuffer, size_t fontBufferSize, const char* pFontName );
	ErrorId						findOffsetForFontInTrueTypeCollection( uint32* pOutOffset, const uint8* pFontBuffer, size_t fontBufferSize, uint32 fontIndex );
	
	int							getTrueTypeKerning( const TrueTypeFont* pTrueTypFont, Rune runeLeft, Rune runeRight );
	int							getTrueTypeKerningFromIndex( const TrueTypeFont* pTrueTypFont, uint32 leftGlyphIndex, uint32 rightGlyphIndx );
}


#endif //KEEN_TRUETYPE_HEADER
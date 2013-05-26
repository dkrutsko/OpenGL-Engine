////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                        (C) 2012-2013  David Krutsko                        //
//                        See LICENSE.md for copyright                        //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#ifndef GRAPHICS_VERTEX_H
#define GRAPHICS_VERTEX_H

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Graphics/Color.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#pragma pack (push, 1)
class VertexElement
{
public:
	// Types
	////////////////////////////////////////////////////////////////////////////////
	/// <summary> </summary>

	enum ElementFormat
	{
		FloatFormat				= 10,
		ColorFormat				= 20,
		Vector2Format			= 30,
		Vector3Format			= 40,
		Vector4Format			= 50,
	};

	////////////////////////////////////////////////////////////////////////////////
	/// <summary> </summary>

	enum ElementType
	{
		BinormalType			= 10,
		ColorType				= 20,
		DepthType				= 30,
		NormalType				= 40,
		PointSizeType			= 50,
		PositionType			= 60,
		SampleType				= 70,
		TangentType				= 80,
		TessellateFactorType	= 90,
		TextureUVType			= 100,
	};

public:
	// Constructors
	 VertexElement (void) { }
	~VertexElement (void) { }

	 VertexElement (ElementFormat elementFormat, ElementType elementType, quint8 index = 0)
		: Index (index), Offset (0), ElementFormat (elementFormat), ElementType (elementType) { }

public:
	// Methods
	quint32 GetFormatSize		(void) const;
	quint32 GetFormatType		(void) const;
	quint32 GetComponentCount	(void) const;

public:
	// Fields
	quint8			Index;			// Buffer index to use
	quint16			Offset;			// Vertex offset value
	ElementFormat	ElementFormat;	// Vertex element format
	ElementType		ElementType;	// Vertex element type

	//
	// Vertex Element Index
	// --------------------
	//
	// +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
	// |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
	// +--+||+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
	//     ||            Vertex Buffer
	//     \/
	// +---------------+---------------+---------------+
	// |      A=1      |      B=2      |      C=3      |
	// +---------------+---------------+---------------+
	//                      Vertex
	// 
	// VertexElement[] =
	//     VertexElement (FormatA, TypeA)
	//     VertexElement (FormatB, TypeB)
	//     VertexElement (FormatC, TypeC)
	// 
	// +---------------+---------------+---------------+ +- - - - - - - -+
	// |      A=1      |      B=2      |      C=3      | |  D=4 ==> D=2  |
	// +---------------+---------------+---------------+ +- - - - - - - -+
	//
	// VertexElement[] =
	//     VertexElement (FormatA, TypeA)
	//     VertexElement (FormatB, TypeB)
	//     VertexElement (FormatC, TypeC)
	//     VertexElement (FormatD, TypeD, 2)
	//     
	// D is using the same data as B. The vertex element index is used
	// to save memory by telling D that it will be using data from B,
	// thus eliminating the need to duplicate data on the buffer.
	//
};
#pragma pack (pop)



////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class VertexDeclaration
{
public:
	// Constructors
	 VertexDeclaration (const VertexDeclaration& declaration);
	 VertexDeclaration (quint8 elementCount, const VertexElement* elements);
	~VertexDeclaration (void);

public:
	// Methods
	void					LoadPointers	(void) const;
	void					UnloadPointers	(void) const;

	quint16					GetVertexSize	(void) const { return mVertexSize;		}
	quint8					GetElementCount	(void) const { return mElementCount;	}
	const VertexElement*	GetElements		(void) const { return mElements;		}

private:
	// Fields
	quint16					mVertexSize;	// Size of declaration
	quint8					mElementCount;	// Number of elements
	VertexElement*			mElements;		// Vertex element list
};



////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class VertexBuffer
{
public:
	// Constructors
	 VertexBuffer (void);
	~VertexBuffer (void);
	 VertexBuffer (const VertexBuffer& buffer);

public:
	// Methods
	bool		Load			(void);
	bool		Reload			(void);
	void		Unload			(void);

	void		Purge			(void);

	bool		IsLoaded		(void) const { return mVertexID != 0;	}
	bool		IsPurged		(void) const { return mData == nullptr;	}

	quint32		GetVertexID		(void) const { return mVertexID;		}
	quint32		GetVertexCount	(void) const { return mVertexCount;		}

	quint32		GetDataLength	(void) const { return mDataLength;		}
	quint8*		GetData			(void) const { return mData;			}

	bool		Create			(quint32 vertexCount,
								 quint8 elementCount,
								 const VertexElement* elements);

	VertexDeclaration* GetVertexDeclaration (void) const { return mVertexDeclaration; }

private:
	// Fields
	quint32		mVertexID;		// OpenGL vertex ID
	quint32		mVertexCount;	// Number of vertices

	quint32		mDataLength;	// Vertex data length
	quint8*		mData;			// Vertex data

	// Vertex declaration of this buffer
	VertexDeclaration* mVertexDeclaration;
};



////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class IndexBuffer
{
public:
	// Constructors
	 IndexBuffer (void);
	~IndexBuffer (void);
	 IndexBuffer (const IndexBuffer& buffer);

public:
	// Methods
	bool		Load			(void);
	bool		Reload			(void);
	void		Unload			(void);

	void		Purge			(void);

	bool		IsLoaded		(void) const { return mIndexID != 0;	}
	bool		IsPurged		(void) const { return mData == nullptr;	}

	quint32		GetIndexID		(void) const { return mIndexID;			}
	quint32		GetIndexCount	(void) const { return mIndexCount;		}
	quint8		GetIndexSize	(void) const { return mIndexSize;		}

	quint32		GetDataLength	(void) const { return mDataLength;		}
	quint8*		GetData			(void) const { return mData;			}

	bool		Create			(quint32 indexCount, quint8 indexSize);

private:
	// Fields
	quint32		mIndexID;		// OpenGL index ID
	quint32		mIndexCount;	// Number of indices
	quint8		mIndexSize;		// Size of one index

	quint32		mDataLength;	// Index data length
	quint8*		mData;			// Index data
};



//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#define SYNTHESIZE_VERTEX_DECLARATION( Name, Count, Properties )		\
	__pragma (pack (push, 1))											\
																		\
	class Name 															\
	{																	\
	public:																\
		Properties;														\
																		\
	public:																\
		static const quint8 ElementCount;								\
		static const VertexElement VertexElements[Count];				\
	};																	\
																		\
	__pragma (pack (pop))												\
																		\
	bool operator == (const Name& value1, const Name& value2);			\
	bool operator != (const Name& value1, const Name& value2);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#define SYNTHESIZE_VERTEX_DEFINITION( Name, Count, ... )				\
	const quint8 Name::ElementCount = Count;							\
	const VertexElement Name::VertexElements[Count] = { __VA_ARGS__ };	\
																		\
	bool operator == (const Name& value1, const Name& value2)			\
		{ return memcmp (&value1, &value2, sizeof (Name)) == 0; }		\
																		\
	bool operator != (const Name& value1, const Name& value2)			\
		{ return memcmp (&value1, &value2, sizeof (Name)) != 0; }



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DECLARATION
(
	VertexPosition, 1,
	Vector4 Position;
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DECLARATION
(
	VertexPositionColor, 2,
	Vector4 Position;
	Color Color;
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DECLARATION
(
	VertexPositionNormal, 2,
	Vector4 Position;
	Vector3 Normal;
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DECLARATION
(
	VertexPositionTexture, 2,
	Vector4 Position;
	Vector2 Texture;
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DECLARATION
(
	VertexPositionColorTexture, 3,
	Vector4 Position;
	Color Color;
	Vector2 Texture;
);


////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DECLARATION
(
	VertexPositionNormalTexture, 3,
	Vector4 Position;
	Vector3 Normal;
	Vector2 Texture;
);

#endif // GRAPHICS_VERTEX_H

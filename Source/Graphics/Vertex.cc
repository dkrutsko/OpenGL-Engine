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

#include <cstring>
#include "Graphics/Vertex.h"
#include "Engine/Console.h"

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Methods                                                      VertexElement //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

quint32 VertexElement::GetFormatSize (void) const
{
	// No size if data is shared
	if (Index != 0) return 0;

	// Determine the format size
	switch (ElementFormat)
	{
		case   FloatFormat: return 4;
		case   ColorFormat: return 4;
		case Vector2Format: return 8;
		case Vector3Format: return 12;
		case Vector4Format: return 16;

		// Just in case
		default: return 0;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

quint32 VertexElement::GetFormatType (void) const
{
	// Determine the format type
	switch (ElementFormat)
	{
		case   FloatFormat: return GL_FLOAT;
		case   ColorFormat: return GL_UNSIGNED_INT;
		case Vector2Format: return GL_FLOAT;
		case Vector3Format: return GL_FLOAT;
		case Vector4Format: return GL_FLOAT;

		// Just in case
		default: return GL_FLOAT;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

quint32 VertexElement::GetComponentCount (void) const
{
	// Determine the component count
	switch (ElementFormat)
	{
		case   FloatFormat: return 1;
		case   ColorFormat: return 1;
		case Vector2Format: return 2;
		case Vector3Format: return 3;
		case Vector4Format: return 4;

		// Just in case
		default: return 0;
	}
}



//----------------------------------------------------------------------------//
// Constructors                                             VertexDeclaration //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

VertexDeclaration::VertexDeclaration (const VertexDeclaration& declaration)
{
	// Copy primitive data
	mElementCount = declaration.mElementCount;
	mElements = new VertexElement[mElementCount];
	mVertexSize = declaration.mVertexSize;

	// Copy elements array
	memcpy (mElements, declaration.mElements,
		mElementCount * sizeof (VertexElement));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

VertexDeclaration::VertexDeclaration (quint8 elementCount, const VertexElement* elements)
{
	// Create a new list of vertex elements
	mElementCount = elementCount;
	mElements = new VertexElement[mElementCount];
	mVertexSize = 0;

	// Copy vertex elements and compute size
	for (quint8 i = 0; i < mElementCount; ++i)
	{
		// Copy the current element
		mElements[i] = elements[i];

		// Update the element offset
		if (mElements[i].Index == 0)
			mElements[i].Offset = mVertexSize;

		// Perform a bounds check
		else if (mElements[i].Index <= i)
			// Set the offset to that of the previous element at the index
			mElements[i].Offset = mElements[mElements[i].Index - 1].Offset;

		// Add the format size to the total
		mVertexSize += mElements[i].GetFormatSize();
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

VertexDeclaration::~VertexDeclaration (void)
{
	delete[] mElements;
}



//----------------------------------------------------------------------------//
// Methods                                                  VertexDeclaration //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void VertexDeclaration::LoadPointers (void) const
{
	for (quint32 i = 0; i < mElementCount; ++i)
	{
		GL_CALL (glEnableVertexAttribArray (i));
		GL_CALL (glVertexAttribPointer (i, mElements[i].GetComponentCount(), mElements[i].
			GetFormatType(), GL_FALSE, mVertexSize, (void*) mElements[i].Offset));
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void VertexDeclaration::UnloadPointers (void) const
{
	for (quint32 i = 0; i < mElementCount; ++i)
		GL_CALL (glDisableVertexAttribArray (i));
}



//----------------------------------------------------------------------------//
// Constructors                                                  VertexBuffer //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

VertexBuffer::VertexBuffer (void)
{
	mVertexID    = 0;
	mVertexCount = 0;

	mDataLength = 0;
	mData = nullptr;

	mVertexDeclaration = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

VertexBuffer::~VertexBuffer (void)
{
	Unload();

	if (mVertexDeclaration != nullptr)
		delete mVertexDeclaration;

	if (mData != nullptr)
		delete[] mData;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

VertexBuffer::VertexBuffer (const VertexBuffer& buffer)
{
	mVertexID = 0;

	// Copy primitive data
	mVertexCount = buffer.mVertexCount;

	// Copy vertex declaration data
	mVertexDeclaration = new
		VertexDeclaration (*buffer.mVertexDeclaration);

	// Copy vertex buffer data
	if (buffer.IsPurged())
	{
		// Data is purged
		mDataLength = 0;
		mData = nullptr;
	}

	else
	{
		// Data needs to be copied
		mDataLength = buffer.mDataLength;
		mData = new quint8[mDataLength];

		memcpy (mData, buffer.mData, mDataLength);
	}
}



//----------------------------------------------------------------------------//
// Methods                                                       VertexBuffer //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool VertexBuffer::Load (void)
{
	// Check if already loaded
	if (IsLoaded()) return true;

	// Check if the data has been purged
	if (IsPurged()) return false;

	// Create a vertex buffer
	GL_CALL (glGenBuffers (1, &mVertexID));
	GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, mVertexID));

	// Set vertex buffer data
	GL_CALL (glBufferData (GL_ARRAY_BUFFER,
		mDataLength, mData, GL_STATIC_DRAW));

	// Load the vertex array pointers
	mVertexDeclaration->LoadPointers();

	// Check for any OpenGL errors
	GL_CHECK (Unload(); return false);

	// All done
	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool VertexBuffer::Reload (void)
{
	Unload(); return Load();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void VertexBuffer::Unload (void)
{
	// Check if already unloaded
	if (!IsLoaded()) return;

	// Load the vertex array pointers
	mVertexDeclaration->UnloadPointers();

	// Delete the vertex buffer
	GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, 0));
	GL_CALL (glDeleteBuffers (1, &mVertexID));
	mVertexID = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void VertexBuffer::Purge (void)
{
	// Check if data already purged
	if (IsPurged()) return;

	// Purge vertex data
	delete[] mData;
	mDataLength = 0;
	mData = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool VertexBuffer::Create (quint32 vertexCount,
	quint8 elementCount, const VertexElement* elements)
{
	// Check parameters
	if (vertexCount  == 0 ||
		elementCount == 0) return false;

	// Delete previous data
	if (mData != nullptr)
		delete[] mData;

	if (mVertexDeclaration != nullptr)
		delete mVertexDeclaration;

	// Create vertex declaration
	mVertexDeclaration = new VertexDeclaration (elementCount, elements);
	mVertexCount = vertexCount;

	// Compute data length and allocate memory
	mDataLength = vertexCount * mVertexDeclaration->GetVertexSize();
	mData       = new quint8[mDataLength];

	// All done
	return true;
}



//----------------------------------------------------------------------------//
// Constructors                                                   IndexBuffer //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

IndexBuffer::IndexBuffer (void)
{
	mIndexID    = 0;
	mIndexCount = 0;
	mIndexSize  = 0;

	mDataLength = 0;
	mData = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

IndexBuffer::~IndexBuffer (void)
{
	Unload();

	if (mData != nullptr)
		delete[] mData;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

IndexBuffer::IndexBuffer (const IndexBuffer& buffer)
{
	mIndexID = 0;

	// Copy primitive data
	mIndexCount = buffer.mIndexCount;
	mIndexSize  = buffer.mIndexSize;

	// Copy index buffer data
	if (buffer.IsPurged())
	{
		// Data is purged
		mDataLength = 0;
		mData = nullptr;
	}

	else
	{
		// Data needs to be copied
		mDataLength = buffer.mDataLength;
		mData = new quint8[mDataLength];

		memcpy (mData, buffer.mData, mDataLength);
	}
}



//----------------------------------------------------------------------------//
// Methods                                                        IndexBuffer //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool IndexBuffer::Load (void)
{
	// Check if already loaded
	if (IsLoaded()) return true;

	// Check if the data has been purged
	if (IsPurged()) return false;

	// Create an index buffer
	GL_CALL (glGenBuffers (1, &mIndexID));
	GL_CALL (glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, mIndexID));

	// Set index buffer data
	GL_CALL (glBufferData (GL_ELEMENT_ARRAY_BUFFER,
		mDataLength, mData, GL_STATIC_DRAW));

	// Check for any OpenGL errors
	GL_CHECK (Unload(); return false);

	// All done
	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool IndexBuffer::Reload (void)
{
	Unload(); return Load();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void IndexBuffer::Unload (void)
{
	// Check if already unloaded
	if (!IsLoaded()) return;

	// Delete the index buffer
	GL_CALL (glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));
	GL_CALL (glDeleteBuffers (1, &mIndexID));
	mIndexID = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void IndexBuffer::Purge (void)
{
	// Check if data already purged
	if (IsPurged()) return;

	// Purge vertex data
	delete[] mData;
	mDataLength = 0;
	mData = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// indexSize in bytes (1, 2 or 4)
/// Does not delete opengl data

bool IndexBuffer::Create (quint32 indexCount, quint8 indexSize)
{
	// Check parameters
	if (indexCount == 0 ||
		indexSize  == 0) return false;

	// Delete previous data
	if (mData != nullptr)
		delete[] mData;

	// Create index buffer
	mIndexCount = indexCount;
	mIndexSize  = indexSize;
	mDataLength = indexCount * indexSize;
	mData       = new quint8[mDataLength];

	// All done
	return true;
}



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DEFINITION
(
	VertexPosition, 1,
	VertexElement (VertexElement::Vector4Format, VertexElement::PositionType)
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DEFINITION
(
	VertexPositionColor, 2,
	VertexElement (VertexElement::Vector4Format, VertexElement::PositionType),
	VertexElement (VertexElement::ColorFormat, VertexElement::ColorType)
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DEFINITION
(
	VertexPositionNormal, 2,
	VertexElement (VertexElement::Vector4Format, VertexElement::PositionType),
	VertexElement (VertexElement::Vector3Format, VertexElement::NormalType)
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DEFINITION
(
	VertexPositionTexture, 2,
	VertexElement (VertexElement::Vector4Format, VertexElement::PositionType),
	VertexElement (VertexElement::Vector2Format, VertexElement::TextureUVType)
);

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DEFINITION
(
	VertexPositionColorTexture, 3,
	VertexElement (VertexElement::Vector4Format, VertexElement::PositionType),
	VertexElement (VertexElement::ColorFormat, VertexElement::ColorType),
	VertexElement (VertexElement::Vector2Format, VertexElement::TextureUVType)
);


////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

SYNTHESIZE_VERTEX_DEFINITION
(
	VertexPositionNormalTexture, 3,
	VertexElement (VertexElement::Vector4Format, VertexElement::PositionType),
	VertexElement (VertexElement::Vector3Format, VertexElement::NormalType),
	VertexElement (VertexElement::Vector2Format, VertexElement::TextureUVType)
);

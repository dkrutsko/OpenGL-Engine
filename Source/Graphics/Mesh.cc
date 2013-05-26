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

#include "Engine/Console.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/Vertex.h"

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Constructors                                                          Mesh //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Mesh::Mesh (void)
{
	mArrayID  = 0;
	Material  = -1;

	mVertices = new VertexBuffer();
	mIndices  = new  IndexBuffer();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Mesh::~Mesh (void)
{
	Unload();

	delete mVertices;
	delete mIndices;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// Effect gets shared

Mesh::Mesh (const Mesh& mesh)
{
	mArrayID  = 0;
	Material  = mesh.Material;

	mVertices = new VertexBuffer (*mesh.mVertices);
	mIndices  = new  IndexBuffer (*mesh.mIndices );

	Name   = mesh.Name;
}



//----------------------------------------------------------------------------//
// Methods                                                               Mesh //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Mesh::Load (void)
{
	// Check if already loaded
	if (IsLoaded()) return true;

	// Create a vertex array
	GL_CALL (glGenVertexArrays (1, &mArrayID));
	GL_CALL (glBindVertexArray (    mArrayID));

	// Load vertex and index buffers
	bool status = true;
	status &= mVertices->Load();
	status &= mIndices ->Load();

	// Check if data was loaded
	if (!status) Unload();
	else GL_CALL (glBindVertexArray (0));

	// All done
	return status;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Mesh::Reload (void)
{
	Unload(); return Load();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mesh::Unload (void)
{
	// Check if already unloaded
	if (!IsLoaded()) return;

	// Bind the vertex array
	GL_CALL (glBindVertexArray (mArrayID));

	// Unload vertex and index buffers
	mVertices->Unload();
	mIndices ->Unload();

	// Delete the vertex array
	GL_CALL (glBindVertexArray (0));
	GL_CALL (glDeleteVertexArrays (1, &mArrayID));
	mArrayID = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mesh::Purge (void)
{
	mVertices->Purge();
	mIndices ->Purge();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Mesh::IsLoaded (void) const { return mArrayID != 0;			}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Mesh::IsPurged (void) const { return mVertices->IsPurged();	}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mesh::Draw (void) const
{
	// Bind the mesh vertex array
	GL_CALL (glBindVertexArray (mArrayID));
	switch (mIndices->GetIndexSize())
	{
		// Select appropriate index type depending on the index size
		case 1: GL_CALL (glDrawElements (GL_TRIANGLES, mIndices->GetIndexCount(), GL_UNSIGNED_BYTE,  nullptr)); break;
		case 2: GL_CALL (glDrawElements (GL_TRIANGLES, mIndices->GetIndexCount(), GL_UNSIGNED_SHORT, nullptr)); break;
		case 4: GL_CALL (glDrawElements (GL_TRIANGLES, mIndices->GetIndexCount(), GL_UNSIGNED_INT,   nullptr)); break;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// indexSize in bytes (1, 2 or 4)
/// Does not delete opengl data
/// Does not change material or effect

bool Mesh::Create (quint32 vertexCount, quint8 elementCount,
	const VertexElement* elements, quint32 indexCount, quint8 indexSize)
{
	bool status = true;

	status &= mVertices->Create (vertexCount, elementCount, elements);
	status &= mIndices ->Create (indexCount, indexSize);

	return status;
}



//----------------------------------------------------------------------------//
// Static                                                                Mesh //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mesh::CreateQuad (Mesh& mesh, float x1, float y1,
	float x2, float y2, bool xFlip, bool yFlip)
{
	CreateQuad (mesh, x1, y1, x2, y2, 0, 0, 1, 1, xFlip, yFlip);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mesh::CreateQuad (Mesh& mesh, float x1,
	float y1, float x2, float y2, float mx1, float my1,
	float mx2, float my2, bool xFlip, bool yFlip)
{
	// Apply flips
	float tmp;
	if (xFlip)
	{
		tmp = mx2;
		mx2 = mx1;
		mx1 = tmp;
	}

	if (yFlip)
	{
		tmp = my2;
		my2 = my1;
		my1 = tmp;
	}

	// Create a quad
	mesh.Create (4, VertexPositionTexture::ElementCount,
		VertexPositionTexture::VertexElements, 6, 1);

	VertexPositionTexture* vertices =
		(VertexPositionTexture*) mesh.GetVertices()->GetData();

	// Compute quad vertex positions
	vertices[0].Position = Vector4 (x1, y2, 0, 1);
	vertices[1].Position = Vector4 (x2, y2, 0, 1);
	vertices[2].Position = Vector4 (x1, y1, 0, 1);
	vertices[3].Position = Vector4 (x2, y1, 0, 1);

	// Assign quad texture coordinates
	vertices[0].Texture  = Vector2 (mx1, my2);
	vertices[1].Texture  = Vector2 (mx2, my2);
	vertices[2].Texture  = Vector2 (mx1, my1);
	vertices[3].Texture  = Vector2 (mx2, my1);

	// Assign quad indicies
	quint8* indices = mesh.GetIndices() ->GetData();

	indices[0] = 0; indices[3] = 2;
	indices[1] = 2; indices[4] = 3;
	indices[2] = 1; indices[5] = 1;
}

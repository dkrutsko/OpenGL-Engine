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

#include "../AstProcessor.h"

#include "Content/Asset.h"
#include "Engine/Console.h"
#include "Content/Content.h"

#include "Graphics/Mesh.h"
#include "Graphics/Vertex.h"
#include "Graphics/Model.h"
#include "Graphics/Material.h"
#include "Graphics/Texture.h"

#include <QIODevice.h>



//----------------------------------------------------------------------------//
// Internal                                                                   //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static Mesh* ImportMesh (QIODevice& device)
{
	// Read the number of vertices
	quint32 vertexCount = 0;
	if (device.read ((char*) &vertexCount, sizeof (quint32)) != sizeof (quint32))
	{
		Console::Error ("Unable to read mesh vertex count");
		return nullptr;
	}

	// Read vertex declaration
	quint8 elementCount = 0;
	if (device.read ((char*) &elementCount, sizeof (quint8)) != sizeof (quint8))
	{
		Console::Error ("Unable to read mesh vertex element count");
		return nullptr;
	}

	VertexElement* elements = new VertexElement[elementCount];
	for (quint8 i = 0; i < elementCount; ++i)
	{
		if (device.read ((char*) &elements[i], sizeof (VertexElement)) != sizeof (VertexElement))
		{
			Console::Error ("Unable to read vertex element");
			delete[] elements; return nullptr;
		}
	}

	// Read the number of indices and size
	quint32 indexCount = 0;
	quint8  indexSize  = 0;

	if (device.read ((char*) &indexCount, sizeof (quint32)) != sizeof (quint32) ||
		device.read ((char*) &indexSize,  sizeof (quint8 )) != sizeof (quint8 ))
	{
		Console::Error ("Unable to read index count and size");
		delete[] elements; return nullptr;
	}

	// Create the mesh
	Mesh* mesh = new Mesh();
	mesh->Create (vertexCount, elementCount, elements, indexCount, indexSize);
	delete[] elements;

	// Read material reference
	if (device.read ((char*) &mesh->Material, sizeof (qint32)) != sizeof (qint32))
	{
		Console::Error ("Unable to read material reference");
		delete mesh; return nullptr;
	}

	// Read vertices and indices
	VertexBuffer* vertices = mesh->GetVertices();
	IndexBuffer*  indices  = mesh->GetIndices();

	if (device.read ((char*) vertices->GetData(), vertices->GetDataLength()) != vertices->GetDataLength() ||
		device.read ((char*) indices ->GetData(), indices ->GetDataLength()) != indices ->GetDataLength())
	{
		Console::Error ("Unable to read verticies and indicies");
		delete mesh; return nullptr;
	}

	return mesh;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static bool ExportMesh (QIODevice& device, const Mesh* mesh)
{
	// Header
	bool valid = mesh != nullptr;
	device.write ((char*) &valid, sizeof (bool));
	if (!valid) return true;

	VertexBuffer* vertices = mesh->GetVertices();
	IndexBuffer*  indices  = mesh->GetIndices();

	// Write the number of vertices
	quint32 vertexCount = vertices->GetVertexCount();
	device.write ((char*) &vertexCount, sizeof (quint32));

	// Write vertex declaration
	VertexDeclaration* declaration = vertices->GetVertexDeclaration();

	quint8 elementCount = declaration->GetElementCount();
	device.write ((char*) &elementCount, sizeof (quint8));

	const VertexElement* elements = declaration->GetElements();

	for (quint8 i = 0; i < elementCount; ++i)
		device.write ((char*) &elements[i], sizeof (VertexElement));

	// Write the number of indices and size
	quint32 indexCount = indices->GetIndexCount();
	quint8  indexSize  = indices->GetIndexSize();

	device.write ((char*) &indexCount, sizeof (quint32));
	device.write ((char*) &indexSize,  sizeof (quint8 ));

	// Write material reference
	device.write ((char*) &mesh->Material, sizeof (qint32));

	// Write vertices and indices
	device.write ((char*) vertices->GetData(), vertices->GetDataLength());
	device.write ((char*) indices ->GetData(), indices ->GetDataLength());

	return true;
}



//----------------------------------------------------------------------------//
// Internal                                                      AstProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* AstProcessor::ImportModel (QIODevice& device, Asset* asset)
{
	// Read model header
	quint16 textureCount  = 0;
	quint16 materialCount = 0;
	quint16 meshCount     = 0;

	if (device.read ((char*) &textureCount,  sizeof (quint16)) != sizeof (quint16) ||
		device.read ((char*) &materialCount, sizeof (quint16)) != sizeof (quint16) ||
		device.read ((char*) &meshCount,     sizeof (quint16)) != sizeof (quint16))
	{
		Console::Error ("Unable to read model header");
		return nullptr;
	}

	// Create the model object
	Model* model;
	bool managed = asset != nullptr;

	if (managed)
		 model = (Model*) asset;
	else model = new Model();
	
	model->Create();

	// Read textures
	for (quint16 i = 0; i < textureCount; ++i)
	{
		quint8 length = 0;
		if (device.read ((char*) &length, sizeof (quint8)) != sizeof (quint8))
		{
			Console::Error ("Unable to read texture length");
			if (!managed) model->Release(); return nullptr;
		}

		QByteArray filename = device.read (length);
		if (filename.length() != length)
		{
			Console::Error ("Unable to read texture filename");
			if (!managed) model->Release(); return nullptr;
		}

		Texture* texture = (Texture*) Content::Load (QString (filename));
		model->Textures.Add (texture);

		if (texture == nullptr)
		{
			Console::Error ("Unable to load texture");
			if (!managed) model->Release(); return nullptr;
		}
	}

	// Read materials
	for (quint16 i = 0; i < materialCount; ++i)
	{
		Material* material = new Material();
		model->Materials.Add (material);

		if (device.read ((char*) material, sizeof (Material)) != sizeof (Material))
		{
			Console::Error ("Unable to read material");
			if (!managed) model->Release(); return nullptr;
		}
	}

	// Read meshes
	for (quint16 i = 0; i < meshCount; ++i)
	{
		bool valid = false;
		if (device.read ((char*) &valid, sizeof (bool)) != sizeof (bool))
		{
			Console::Error ("Unable to verify mesh validity");
			if (!managed) model->Release(); return nullptr;
		}

		if (valid)
		{
			Mesh* mesh = ImportMesh (device);
			if (mesh == nullptr)
			{
				Console::Error ("Unable to read model mesh");
				if (!managed) model->Release(); return nullptr;
			}

			model->Meshes.Add (mesh);
		}
	}

	// Read physics mesh
	bool valid = false;
	if (device.read ((char*) &valid, sizeof (bool)) != sizeof (bool))
	{
		Console::Error ("Unable to verify mesh validity");
		if (!managed) model->Release(); return nullptr;
	}

	if (valid)
	{
		Mesh* mesh = ImportMesh (device);
		if (mesh == nullptr)
		{
			Console::Error ("Unable to read model mesh");
			if (!managed) model->Release(); return nullptr;
		}

		model->SetPhysicsMesh (mesh);
	}

	return model;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool AstProcessor::ExportModel (QIODevice& device, const Asset* asset)
{
	Model* model = (Model*) asset;

	// Check if model geomertry is purged
	if (model->IsGeometryPurged())
	{
		Console::Error ("Model geometry is purged");
		return false;
	}

	// Write model header
	quint16 textureCount  = model->Textures.Length();
	quint16 materialCount = model->Materials.Length();
	quint16 meshCount     = model->Meshes.Length();

	device.write ((char*) &textureCount,  sizeof (quint16));
	device.write ((char*) &materialCount, sizeof (quint16));
	device.write ((char*) &meshCount,     sizeof (quint16));

	// Write textures
	for (quint16 i = 0; i < textureCount; ++i)
	{
		Texture* texture = model->Textures[i];

		if (!texture->IsManaged())
		{
			Console::Warning ("Cannot export unmanaged texture");
			continue;
		}

		// Write texture source length
		quint8 length = texture->GetSource().length();
		device.write ((char*) &length, sizeof (quint8));

		// Write texture source
		device.write (texture->GetSource().toAscii().data(), length);
	}

	// Write materials
	for (quint16 i = 0; i < materialCount; ++i)
		device.write ((char*) model->Materials[i], sizeof (Material));

	// Write meshes
	for (quint16 i = 0; i < meshCount; ++i)
		if (!ExportMesh (device, model->Meshes[i]))
		{
			Console::Error ("Failed to export mesh");
			return false;
		}

	// Write physics mesh
	if (!ExportMesh (device, model->GetPhysicsMesh()))
	{
		Console::Error ("Failed to export physics mesh");
		return false;
	}

	return true;
}

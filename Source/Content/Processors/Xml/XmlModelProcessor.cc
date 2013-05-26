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

#include "Version.h"
#include "../XmlProcessor.h"
#include "Engine/Console.h"
#include "Content/Content.h"

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Vertex.h"
#include "Graphics/Material.h"
#include "Graphics/Texture.h"

#include <QDom.h>
#include <QFile.h>
#include <QFileInfo.h>
#include <QIODevice.h>
#include <QString.h>
#include <QStringList.h>



//----------------------------------------------------------------------------//
// Internal                                                                   //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void MergeAnimation (Model* result, Model* model)
{
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void ParseChannel (QDomElement& element,
	Material::Channel& channel, const QMap<QString, qint32>& textures)
{
	// Parse color
	QString color = element.attribute ("Color");
	if (!color.isEmpty())
	{
		QStringList list = color.split (',', QString::SkipEmptyParts);
		if (list.length() >= 4)
		{
			channel.Color.R = list.at(0).toFloat();
			channel.Color.G = list.at(1).toFloat();
			channel.Color.B = list.at(2).toFloat();
			channel.Color.A = list.at(3).toFloat();
		}
	}
	
	// Parse texture
	if (textures.contains (element.attribute ("Texture")))
		 channel.Texture = textures[element.attribute ("Texture")];
	else channel.Texture = -1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static Material* LoadMaterial (QDomElement& element, const QMap<QString, qint32>& textures)
{
	Material* material = new Material();

	bool status;

	// Parse through this node
	QDomNode node = element.firstChild();
	while (!node.isNull())
	{
		// Get the node element
		QDomElement element = node.toElement();

		// Get the next XML node
		node = node.nextSibling();
		if (element.isNull()) continue;

		// Parse the ambient channel
		if (element.tagName() == "Ambient")
			ParseChannel (element, material->Ambient, textures);

		// Parse the diffuse channel
		if (element.tagName() == "Diffuse")
			ParseChannel (element, material->Diffuse, textures);

		// Parse the specular channel
		if (element.tagName() == "Specular")
			ParseChannel (element, material->Specular, textures);

		// Parse the emissive channel
		if (element.tagName() == "Emissive")
			ParseChannel (element, material->Emissive, textures);

		// Parse the alpha value
		if (element.tagName() == "Alpha")
		{
			material->Alpha = element.attribute ("Value").toFloat (&status);
			if (!status) material->Alpha = 1.0f;
		}

		// Parse the shininess value
		if (element.tagName() == "Shininess")
		{
			material->Shininess = element.attribute ("Value").toFloat (&status);
			if (!status) material->Shininess = 2.0f;
		}

		// Parse the normal texture
		if (element.tagName() == "Normal")
		{
			if (textures.contains (element.attribute ("Texture")))
				 material->Normal = textures[element.attribute ("Texture")];
			else material->Normal = -1;
		}
	}

	return material;
}


////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void LoadMaterials (Model* model, QDomElement& element)
{
	QMap<QString, qint32> textures;
	QMap<QString, qint32> materials;

	// Parse through this node
	QDomNode node = element.firstChild();

	if (!node.isNull())
	{
		model->Textures.Clear();
		model->Materials.Clear();

		for (quint32 i = 0; i < model->Meshes.Length(); ++i)
			model->Meshes[i]->Material = -1;
	}

	while (!node.isNull())
	{
		// Get the node element
		QDomElement element = node.toElement();

		// Get the next XML node
		node = node.nextSibling();
		if (element.isNull()) continue;

		// Load texture value
		if (element.tagName() == "Texture")
		{
			Texture* texture = (Texture*) Content::Load (element.attribute ("File"));
			if (texture != nullptr)
			{
				textures.insert (element.attribute ("Name"), model->Textures.Length());
				model->Textures.Add (texture);
			}
		}

		// Load material value
		else if (element.tagName() == "Material")
		{
			Material* material = LoadMaterial (element, textures);
			materials.insert (element.attribute ("Name"), model->Materials.Length());
			model->Materials.Add (material);
		}

		// Assign a material value
		else if (element.tagName() == "Assign")
		{
			QString object = element.attribute ("Object");
			for (quint32 i = 0; i < model->Meshes.Length(); ++i)
				if (model->Meshes[i]->Name == object)
				{
					model->Meshes[i]->Material = materials[element.attribute ("Material")];
					break;
				}
		}
	}
}



//----------------------------------------------------------------------------//
// Internal                                                      XmlProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* XmlProcessor::ImportModel (QFile& file, QDomDocument& document, Asset* asset)
{
	// Get the root element of the document
	QDomElement root = document.documentElement();

	// Verify version
	if (root.attribute ("Version") != VERSION)
	{
		Console::Error ("Unsupported file version");
		return nullptr;
	}

	// Create the model object
	Model* model;
	bool managed = asset != nullptr;

	if (managed)
		 model = (Model*) asset;
	else model = new Model();

	model->Create();
	QFileInfo info (file);

	// Parse XML data
	QDomNode node = root.firstChild();
	while (!node.isNull())
	{
		// Get the node element
		QDomElement element = node.toElement();

		// Get the next XML node
		node = node.nextSibling();
		if (element.isNull()) continue;

		// Get the localized filename of the model
		QString filename = info.path() + "/" + element.attribute ("File");

		// Load model
		Model* elementModel = (Model*) Content::Load (filename);
		if (elementModel == nullptr) continue;

		// Load material information
		LoadMaterials (elementModel, element);

		// Load reference model information
		if (element.tagName() == "Reference")
		{
			// Merge the reference model
			for (quint32 i = 0; i < elementModel->Meshes.Length(); ++i)
				model->Meshes.Add (new Mesh (*elementModel->Meshes[i]));

			for (quint32 i = 0; i < elementModel->Materials.Length(); ++i)
				model->Materials.Add (new Material (*elementModel->Materials[i]));

			for (quint32 i = 0; i < elementModel->Textures.Length(); ++i)
			{
				elementModel->Textures[i]->Retain();
				model->Textures.Add (elementModel->Textures[i]);
			}
		}

		// Load physics model information
		else if (element.tagName() == "Physics")
		{
			// Replace the physics mesh
			model->SetPhysicsMesh (new Mesh
				(*elementModel->GetPhysicsMesh()));
		}

		// Load animation information information
		else if (element.tagName() == "Animation")
		{
			// Merge the animation
			MergeAnimation (model, elementModel);
		}

		elementModel->Release();
	}

	// All done
	return model;
}

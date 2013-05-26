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

#include "FbxProcessor.h"

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Texture.h"
#include "Graphics/Vertex.h"
#include "Graphics/Material.h"

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

#include "Engine/Console.h"
#include "Content/Content.h"

#include <QFile.h>
#include <QFileInfo.h>

#define FBXSDK_NEW_API
#include <fbxsdk.h>



//----------------------------------------------------------------------------//
// Internal                                                                   //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void LoadTextures (Model* model, FbxScene* fbxScene)
{
	const qint32 count = fbxScene->GetTextureCount();
	for (qint32 i = 0; i < count; ++i)
	{
		// Get the FBX texture information
		FbxFileTexture* fbxTexture = FbxCast
			<FbxFileTexture> (fbxScene->GetTexture(i));

		if (fbxTexture != nullptr && fbxTexture->GetUserDataPtr() == nullptr)
		{
			// Add the texture to the model
			Texture* texture = (Texture*) Content::Load (fbxTexture->GetFileName());

			if (texture == nullptr)
			{
				// Error loading texture
				Console::Warning ("Unable to load texture: %s", fbxTexture->GetFileName());
			}

			else
			{
				// Add texture to model
				model->Textures.Add (texture);

				// Save the index position of this texture so it can be referenced later
				fbxTexture->SetUserDataPtr ((void*) model->Textures.Length());
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Get specific property value and connected texture if any. </summary>

static void ApplyMaterialProperty (const FbxSurfaceMaterial* fbxSurfaceMaterial,
	const char* propertyName, const char* factorName, Material::Channel* channel)
{
	double     factor;
	FbxDouble3 color;

	// Get the specified properties
	const FbxProperty fbxProperty       = fbxSurfaceMaterial->FindProperty (propertyName);
	const FbxProperty fbxFactorProperty = fbxSurfaceMaterial->FindProperty (factorName  );

	// The property must be valid
	if (!fbxProperty.IsValid()) return;

	// Process color information
	if (fbxFactorProperty.IsValid())
	{
		// Get the color and factor
		factor = fbxFactorProperty.Get<double>();
		color  = fbxProperty.Get<FbxDouble3>();

		// Apply the material color
		channel->Color.R = color[0] * factor;
		channel->Color.G = color[1] * factor;
		channel->Color.B = color[2] * factor;
	}

	// Check for any textures
	const quint32 textureCount = fbxProperty.GetSrcObjectCount (FbxFileTexture::ClassId);
	if (textureCount != 0)
	{
		// Get the first texture
		const FbxFileTexture* fbxTexture = fbxProperty.GetSrcObject (FBX_TYPE (FbxFileTexture), 0);
		if (fbxTexture != nullptr && fbxTexture->GetUserDataPtr() != nullptr)
		{
			// Set the texture reference to the one currently loaded
			channel->Texture = (quint32) fbxTexture->GetUserDataPtr() - 1;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static Material* CreateMaterial (Model* model, FbxSurfaceMaterial* fbxMaterial)
{
	// Create a new material object
	Material* material = new Material();

	// Apply the ambient, diffuse, specular and emissive properties
	ApplyMaterialProperty (fbxMaterial, FbxSurfaceMaterial::sAmbient,  FbxSurfaceMaterial::sAmbientFactor,  &material->Ambient );
	ApplyMaterialProperty (fbxMaterial, FbxSurfaceMaterial::sDiffuse,  FbxSurfaceMaterial::sDiffuseFactor,  &material->Diffuse );
	ApplyMaterialProperty (fbxMaterial, FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor, &material->Specular);
	ApplyMaterialProperty (fbxMaterial, FbxSurfaceMaterial::sEmissive, FbxSurfaceMaterial::sEmissiveFactor, &material->Emissive);

	// Retrieve the shininess property and apply it to our material
	FbxProperty fbxShininessProperty = fbxMaterial->FindProperty (FbxSurfaceMaterial::sShininess);

	if (fbxShininessProperty.IsValid())
		material->Shininess = fbxShininessProperty.Get<float>();

	return material;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static Mesh* CreateMesh (Model* model, FbxMesh* fbxMesh)
{
	//----------------------------------------------------------------------------//
	// Metadata                                                                   //
	//----------------------------------------------------------------------------//

	// Congregate all data of a mesh to be cached
	bool hasNormal    = fbxMesh->GetElementNormalCount() > 0;
	bool hasTextureUV = fbxMesh->GetElementUVCount()     > 0;

	FbxGeometryElement::EMappingMode fbxNormalMappingMode    = FbxGeometryElement::eNone;
	FbxGeometryElement::EMappingMode fbxTextureUVMappingMode = FbxGeometryElement::eNone;

	bool allByControlPoint = true;

	// Check normals
	if (hasNormal)
	{
		// Get the normal mapping mode of this mesh
		fbxNormalMappingMode = fbxMesh->GetElementNormal(0)->GetMappingMode();

		// There are no relevant normals in this mesh
		if (fbxNormalMappingMode == FbxGeometryElement::eNone)
			hasNormal = false;

		if (hasNormal && fbxNormalMappingMode != FbxGeometryElement::eByControlPoint)
			allByControlPoint = false;
	}

	// Check texture UVs
	if (hasTextureUV)
	{
		// Get the texture UV mapping mode of this mesh
		fbxTextureUVMappingMode = fbxMesh->GetElementUV(0)->GetMappingMode();

		// There are no relevant texture UVs in this mesh
		if (fbxTextureUVMappingMode == FbxGeometryElement::eNone)
			hasTextureUV = false;

		if (hasTextureUV && fbxTextureUVMappingMode != FbxGeometryElement::eByControlPoint)
			allByControlPoint = false;
	}



	//----------------------------------------------------------------------------//
	// Initialize                                                                 //
	//----------------------------------------------------------------------------//

	// Get the mesh polygon count
	const qint32 polygonCount = fbxMesh->GetPolygonCount();

	// Get the mesh vertex count
	qint32 polygonVertexCount = fbxMesh->GetControlPointsCount();
	if (!allByControlPoint) polygonVertexCount = polygonCount * 3;

	// Get the name of the Texture UV
	FbxStringList fbxUVNames;
	fbxMesh->GetUVSetNames(fbxUVNames);
	const char* fbxUVName = nullptr;

	// Create a new mesh object
	Mesh* mesh = new Mesh();

	if (hasNormal && hasTextureUV)
	{
		fbxUVName = fbxUVNames[0];
		mesh->Create (polygonVertexCount, VertexPositionNormalTexture::ElementCount,
			VertexPositionNormalTexture::VertexElements, polygonCount * 3, 4);
	}

	else if (hasNormal)
		mesh->Create (polygonVertexCount, VertexPositionNormal::ElementCount,
			VertexPositionNormal::VertexElements, polygonCount * 3, 4);

	else if (hasTextureUV)
	{
		fbxUVName = fbxUVNames[0];
		mesh->Create (polygonVertexCount, VertexPositionTexture::ElementCount,
			VertexPositionTexture::VertexElements, polygonCount * 3, 4);
	}

	else mesh->Create (polygonVertexCount, VertexPosition::ElementCount,
			VertexPosition::VertexElements, polygonCount * 3, 4);

	float*   vertices   = (float*  ) mesh->GetVertices()->GetData();
	quint32* indices    = (quint32*) mesh->GetIndices ()->GetData();
	quint32  vertexSize = mesh->GetVertices()->GetVertexDeclaration()->GetVertexSize() / 4;



	//----------------------------------------------------------------------------//
	// Control Point                                                              //
	//----------------------------------------------------------------------------//

	const FbxVector4* controlPoints = fbxMesh->GetControlPoints();

	FbxVector4 fbxCurrentVertex;
	FbxVector4 fbxCurrentNormal;
	FbxVector2 fbxCurrentTextureUV;

	if (allByControlPoint)
	{
		const FbxGeometryElementNormal* fbxNormalElement = nullptr;
		const FbxGeometryElementUV*  fbxTextureUVElement = nullptr;

		if (hasNormal)
			fbxNormalElement = fbxMesh->GetElementNormal(0);

		if (hasTextureUV)
			fbxTextureUVElement = fbxMesh->GetElementUV(0);

		// Vertices
		for (qint32 i = 0, index = 0; i < polygonVertexCount; ++i, index += vertexSize)
		{
			// Save the vertex position
			fbxCurrentVertex = controlPoints[i];
			vertices[index + 0] = (float) fbxCurrentVertex[0];
			vertices[index + 1] = (float) fbxCurrentVertex[1];
			vertices[index + 2] = (float) fbxCurrentVertex[2];
			vertices[index + 3] = 1.0f;

			// Save the vertex normal
			if (hasNormal)
			{
				int normalIndex = i;
				if (fbxNormalElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
					normalIndex = fbxNormalElement->GetIndexArray().GetAt (i);

				fbxCurrentNormal = fbxNormalElement->GetDirectArray().GetAt (normalIndex);
				vertices[index + 4] = (float) fbxCurrentNormal[0];
				vertices[index + 5] = (float) fbxCurrentNormal[1];
				vertices[index + 6] = (float) fbxCurrentNormal[2];
			}

			// Save the vertex texture UV
			if (hasTextureUV)
			{
				int textureUVIndex = i;
				if (fbxTextureUVElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
					textureUVIndex = fbxTextureUVElement->GetIndexArray().GetAt (i);

				fbxCurrentTextureUV = fbxTextureUVElement->GetDirectArray().GetAt (textureUVIndex);
				vertices[index + 7] = (float) fbxCurrentTextureUV[0];
				vertices[index + 8] = (float) fbxCurrentTextureUV[1];
			}
		}

		// Indices
		for (qint32 i = 0, index = 0; i < polygonCount; ++i, index += 3)
		{
			indices[index + 0] = (quint32) fbxMesh->GetPolygonVertex (i, 0);
			indices[index + 1] = (quint32) fbxMesh->GetPolygonVertex (i, 1);
			indices[index + 2] = (quint32) fbxMesh->GetPolygonVertex (i, 2);
		}

		// All done
		return mesh;
	}



	//----------------------------------------------------------------------------//
	// Polygon Vertex                                                             //
	//----------------------------------------------------------------------------//

	qint32 index = 0;
	qint32 vertexCount = 0;
	qint32 indexCount  = 0;

	for (qint32 polygonIndex = 0; polygonIndex < polygonCount; ++polygonIndex, indexCount += 3)
		for (qint32 verticeIndex = 0; verticeIndex < 3; ++verticeIndex, vertexCount += vertexSize, ++index)
		{
			// Get the index of the control point based on the current polygon vertex
			const qint32 controlPointIndex = fbxMesh->GetPolygonVertex (polygonIndex, verticeIndex);

			// Save the index position
			indices[indexCount + verticeIndex] = (quint32) index;

			// Save the vertex position
			fbxCurrentVertex = controlPoints[controlPointIndex];
			vertices[vertexCount + 0] = (float) fbxCurrentVertex[0];
			vertices[vertexCount + 1] = (float) fbxCurrentVertex[1];
			vertices[vertexCount + 2] = (float) fbxCurrentVertex[2];
			vertices[vertexCount + 3] = 1.0f;

			// Save the vertex normal
			if (hasNormal)
			{
				fbxMesh->GetPolygonVertexNormal (polygonIndex, verticeIndex, fbxCurrentNormal);
				vertices[vertexCount + 4] = (float) fbxCurrentNormal[0];
				vertices[vertexCount + 5] = (float) fbxCurrentNormal[1];
				vertices[vertexCount + 6] = (float) fbxCurrentNormal[2];
			}

			// Save the vertex texture UV
			if (hasTextureUV)
			{
				fbxMesh->GetPolygonVertexUV (polygonIndex, verticeIndex, fbxUVName, fbxCurrentTextureUV);
				vertices[vertexCount + 7] = (float) fbxCurrentTextureUV[0];
				vertices[vertexCount + 8] = (float) fbxCurrentTextureUV[1];
			}
		}

	// All done
	return mesh;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void LoadGeometry (Model* model, FbxNode* fbxNode)
{
	//----------------------------------------------------------------------------//
	// Mesh                                                                       //
	//----------------------------------------------------------------------------//

	Mesh* mesh = nullptr;

	const FbxNodeAttribute* fbxAttribute = fbxNode->GetNodeAttribute();
	if (fbxAttribute != nullptr)
	{
		// Process mesh-type data
		if (fbxAttribute->GetAttributeType() == FbxNodeAttribute::eMesh  ||
			fbxAttribute->GetAttributeType() == FbxNodeAttribute::eNurbs ||
			fbxAttribute->GetAttributeType() == FbxNodeAttribute::ePatch ||
			fbxAttribute->GetAttributeType() == FbxNodeAttribute::eNurbsSurface)
		{
			// Triangulate mesh-type data
			FbxGeometryConverter converter (fbxNode->GetFbxManager());
			converter.TriangulateInPlace   (fbxNode);

			// Retrieve FBX mesh data
			FbxMesh* fbxMesh = fbxNode->GetMesh();
			if (fbxMesh != nullptr && fbxMesh->GetNode() != nullptr && fbxMesh->GetUserDataPtr() == nullptr)
			{
				// Load mesh data
				mesh = CreateMesh (model, fbxMesh);
				mesh->Name = fbxNode->GetName();

				// Add the mesh to the model
				model->Meshes.Add (mesh);

				// Save the index position of this texture so it can be referenced later
				fbxMesh->SetUserDataPtr ((void*) model->Meshes.Length());
			}
		}
	}



	//----------------------------------------------------------------------------//
	// Materials                                                                  //
	//----------------------------------------------------------------------------//

	const qint32 materialCount = fbxNode->GetMaterialCount();
	for (qint32 i = 0; i < materialCount; ++i)
	{
		// Get FBX material data
		FbxSurfaceMaterial* fbxMaterial = fbxNode->GetMaterial (i);
		if (fbxMaterial == nullptr) continue;

		if (fbxMaterial->GetUserDataPtr() == nullptr)
		{
			// Load material data
			Material* material = CreateMaterial (model, fbxMaterial);

			// Add the material to the model
			model->Materials.Add (material);

			// Save the index position of this texture so it can be referenced later
			fbxMaterial->SetUserDataPtr ((void*) model->Materials.Length());
		}

		// Only one material per mesh is supported, use the first material
		if (mesh != nullptr && i == 0)
			mesh->Material = (quint32) fbxMaterial->GetUserDataPtr() - 1;
	}



	//----------------------------------------------------------------------------//
	// Children                                                                   //
	//----------------------------------------------------------------------------//

	// Load children nodes recursively
	const qint32 childCount = fbxNode->GetChildCount();
	for (qint32 i = 0; i < childCount; ++i)
		LoadGeometry (model, fbxNode->GetChild (i));
}



//----------------------------------------------------------------------------//
// Methods                                                       FbxProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* ::FbxProcessor::Import (QFile& file, Asset* asset)
{
	//----------------------------------------------------------------------------//
	// Initialize                                                                 //
	//----------------------------------------------------------------------------//

	// FbxSDK requires loading from a filename
	const QString filename = file.fileName();

	// Initialize the Fbx SDK manager
	FbxManager* fbxManager = FbxManager::Create();

	// Create the I/O settings object
	FbxIOSettings* fbxIOSettings = FbxIOSettings::Create (fbxManager, IOSROOT);
	fbxManager->SetIOSettings (fbxIOSettings);



	//----------------------------------------------------------------------------//
	// Import                                                                     //
	//----------------------------------------------------------------------------//

	// Create an FBX importer and attempt to initialize it
	FbxImporter* fbxImporter = FbxImporter::Create (fbxManager, "");
	bool importStatus = fbxImporter->Initialize (filename.toAscii().data(), -1, fbxIOSettings);

	if (!importStatus)
	{
		Console::Error ("Failed to initialize FBX importer");

		// Check to see if the error was caused by a version mismatch
		if (fbxImporter->GetLastErrorID() == FbxIO::eFileVersionNotSupportedYet ||
			fbxImporter->GetLastErrorID() == FbxIO::eFileVersionNotSupportedAnymore)
		{
			qint32 sdkMajor, sdkMinor, sdkRev, fileMajor, fileMinor, fileRev;

			FbxManager::GetFileFormatVersion (sdkMajor,  sdkMinor,  sdkRev );
			fbxImporter->GetFileVersion      (fileMajor, fileMinor, fileRev);

			Console::Warning ("FBX version: %d.%d.%d, File version: %d.%d.%d",
				sdkMajor, sdkMinor, sdkRev, fileMajor, fileMinor, fileRev);
		}

		fbxImporter->Destroy();
		fbxManager->Destroy();
		return nullptr;
	}

	// Create a scene to store the data
	FbxScene* fbxScene = FbxScene::Create (fbxManager, "");

	// Attempt to import the scene
	if (!fbxImporter->Import (fbxScene))
	{
		Console::Error ("Failed to import the scene");

		fbxScene->Destroy();
		fbxImporter->Destroy();
		fbxManager->Destroy();
		return nullptr;
	}

	// Destroy the importer
	fbxImporter->Destroy();

	// Convert axis system to OpenGL standard
	if (fbxScene->GetGlobalSettings().GetAxisSystem() != FbxAxisSystem::OpenGL)
		FbxAxisSystem::OpenGL.ConvertScene (fbxScene);

	// Convert unit system to OpenGL standard
	if (fbxScene->GetGlobalSettings().GetSystemUnit().GetScaleFactor() != 1.0)
		FbxSystemUnit::cm.ConvertScene (fbxScene);



	//----------------------------------------------------------------------------//
	// Load                                                                       //
	//----------------------------------------------------------------------------//

	// Retrieve the root node of the scene
	FbxNode* fbxRoot = fbxScene->GetRootNode();

	// Convert animation to be 60 frames per second
//	root->ResetPivotSetAndConvertAnimation (60, false, false);

	// Create the model object
	Model* model;
	bool managed = asset != nullptr;

	if (managed)
		 model = (Model*) asset;
	else model = new Model();

	model->Create();

	// Load texture data
	LoadTextures (model, fbxScene);

	// Load mesh data
	LoadGeometry (model, fbxRoot);

	// All done
	fbxScene->Destroy();
	fbxManager->Destroy();
	return model;
}

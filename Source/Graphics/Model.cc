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

#include "Graphics/Model.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Vertex.h"
#include "Graphics/Texture.h"

#include "Content/Content.h"
ASSET_DEFINITION (Model);

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Constructors                                                         Model //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Model::Model (void) : Asset (AssetID)
{
	mPhysics = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Model::Model (const Model& model) : Asset (model)
{
	if (model.mPhysics != nullptr)
		 mPhysics = new Mesh (*model.mPhysics);
	else mPhysics = nullptr;

	Meshes    = model.Meshes;
	Materials = model.Materials;
	Textures  = model.Textures;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Model::~Model (void)
{
	UnloadTextures (false);
	UnloadGeometry ( true);

	if (mPhysics != nullptr)
		delete mPhysics;
}



//----------------------------------------------------------------------------//
// Methods                                                              Model //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Model::Create (void)
{
	if (mPhysics != nullptr)
	{
		delete mPhysics;
		mPhysics = nullptr;
	}

	Meshes.Clear();
	Materials.Clear();
	Textures.Clear();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::LoadTextures (void)
{
	// Check if already loaded
	if (AreTexturesLoaded()) return true;

	// Load all textures
	bool status = true;
	for (quint32 i = 0; i < Textures.Length(); ++i)
		status &= Textures[i]->Load();

	// Return status
	return status;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::ReloadTextures (bool force)
{
	UnloadTextures (force); return LoadTextures();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Model::UnloadTextures (bool force)
{
	// Check if already unloaded
	if (!AreTexturesLoaded()) return;

	// Unload model meshes
	for (quint32 i = 0; i < Textures.Length(); ++i)
		Textures[i]->Unload (force);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::AreTexturesLoaded (void) const
{
	return Textures.Length() > 0 ? Textures[0]->IsLoaded() : true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::AreTexturesPurged (void) const
{
	return Textures.Length() > 0 ? Textures[0]->IsPurged() : false;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Model::PurgeTextures (bool force)
{
	// Purge all textures
	for (quint32 i = 0; i < Textures.Length(); ++i)
		Textures[i]->Purge (force);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::LoadGeometry (void)
{
	// Check if already loaded
	if (IsGeometryLoaded()) return true;

	// Load all geometry
	bool status = true;
	for (quint32 i = 0; i < Meshes.Length(); ++i)
		status &= Meshes[i]->Load();

	// Return status
	return status;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::ReloadGeometry (bool force)
{
	UnloadGeometry (force); return LoadGeometry();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Model::UnloadGeometry (bool force)
{
	// Check if already unloaded
	if (!IsGeometryLoaded()) return;

	// Check for multiple references
	if (force || mReferences == 1)
	{
		// Unload model meshes
		for (quint32 i = 0; i < Meshes.Length(); ++i)
			Meshes[i]->Unload();
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::IsGeometryLoaded (void) const
{
	return Meshes.Length() > 0 ? Meshes[0]->IsLoaded() : true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Model::IsGeometryPurged (void) const
{
	return Meshes.Length() > 0 ? Meshes[0]->IsPurged() : false;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Model::PurgeGeometry (bool force)
{
	// Check for multiple references
	if (force || mReferences == 1)
	{
		// Purge model meshes
		for (quint32 i = 0; i < Meshes.Length(); ++i)
			Meshes[i]->Purge();
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Mesh* Model::GetPhysicsMesh (void) const
{
	return mPhysics;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Model::SetPhysicsMesh (Mesh* mesh)
{
	if (mPhysics != nullptr)
		delete mPhysics;

	mPhysics = mesh;
}

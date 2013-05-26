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

#ifndef GRAPHICS_MODEL_H
#define GRAPHICS_MODEL_H

class Mesh;
class Material;
class Texture;
class VertexElement;

#include "Content/Asset.h"
#include "Collections.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Model : public Asset
{
	ASSET_DECLARATION;

public:
	// Constructors
	Model (void);
	Model (const Model& model);

protected:
	virtual ~Model (void);

public:
	// Methods
	void Create				(void);

	bool LoadTextures		(void);
	bool ReloadTextures		(bool force = false);
	void UnloadTextures		(bool force = false);

	bool AreTexturesLoaded	(void) const;
	bool AreTexturesPurged	(void) const;
	void PurgeTextures		(bool force = false);

	bool LoadGeometry		(void);
	bool ReloadGeometry		(bool force = false);
	void UnloadGeometry		(bool force = false);

	bool IsGeometryLoaded	(void) const;
	bool IsGeometryPurged	(void) const;
	void PurgeGeometry		(bool force = false);

	Mesh* GetPhysicsMesh	(void) const;
	void  SetPhysicsMesh	(Mesh* mesh);

public:
	// Properties
	ElementCollection<Mesh>		Meshes;		// List of meshes
	ElementCollection<Material>	Materials;	// List of materials
	AssetCollection<Texture>	Textures;	// List of textures

protected:
	// Fields
	Mesh* mPhysics;							// Physics mesh
};

#endif // GRAPHICS_MODEL_H

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

#include "Math/Matrix.h"
#include "Content/Content.h"
#include "Engine/Engine.h"
#include "Engine/Console.h"

#include "Graphics/Mesh.h"
#include "Graphics/Vertex.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"

#include "Graphics/ParticleSystem.h"
ASSET_DEFINITION (ParticleSystem);

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Constructors                                                ParticleSystem //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

ParticleSystem::ParticleSystem (void) : Asset (AssetID)
{
	Position		= Vector3::Zero;
	Diffuse			= Color::White;

	Alpha			= 1.0f;
	Speed			= 1.0f;
	Spread			= 1.0f;
	Shape			= 1.0f;
	Size			= 1.0f;
	Gravity			= 0.0f;

	SystemHeight	= 1.0f;
	SystemShape		= 1.0f;
	FadeInTime		= 0.0f;
	FadeOutTime		= 1.0f;

	mQuantity		= 0;
	mParticles		= nullptr;

	mTexture		= nullptr;
	mParticleSystem	= nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

ParticleSystem::ParticleSystem (const ParticleSystem& system) : Asset (system)
{
	Position		= system.Position;
	Diffuse			= system.Diffuse;

	Alpha			= system.Alpha;
	Speed			= system.Speed;
	Spread			= system.Spread;
	Shape			= system.Shape;
	Size			= system.Size;
	Gravity			= system.Gravity;

	SystemHeight	= system.SystemHeight;
	SystemShape		= system.SystemShape;
	FadeInTime		= system.FadeInTime;
	FadeOutTime		= system.FadeOutTime;

	mParticleSystem	= nullptr;

	if (system.mParticles == nullptr)
	{
		mQuantity	= 0;
		mParticles	= nullptr;
	}

	else Create (system.mQuantity);

	mTexture = system.mTexture;
	mTexture->Retain();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

ParticleSystem::~ParticleSystem (void)
{
	Unload (true);

	if (mParticleSystem != nullptr)
		mParticleSystem->Release();

	if (mParticles != nullptr)
		delete[] mParticles;

	if (mTexture != nullptr)
		mTexture->Release();
}



//----------------------------------------------------------------------------//
// Methods                                                     ParticleSystem //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool ParticleSystem::Load (void)
{
	// Check if already loaded
	if (IsLoaded()) return true;

	// Check if we can load
	if (mParticles == nullptr)
		return false;

	// Load shader
	mParticleSystem = (Shader*) Content::Load ("Shaders/ParticleSystem.ast");
	if (mParticleSystem == nullptr) return false;

	mParticleSystem->Load();
	mParticleSystem->Purge();

	// Load particles
	bool status = true;

	for (quint32 i = 0; i < mQuantity; ++i)
		status &= mParticles[i].Load();

	if (!status)
		Unload (true);

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool ParticleSystem::Reload (bool force)
{
	Unload (force); return Load();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void ParticleSystem::Unload (bool force)
{
	// Check if already unloaded
	if (!IsLoaded()) return;

	// Check for multiple references
	if (force || mReferences == 1)
	{
		for (quint32 i = 0; i < mQuantity; ++i)
			mParticles[i].Unload();

		mParticleSystem->Release();
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool ParticleSystem::IsLoaded (void) const
{
	return mParticles == nullptr ? false : mParticles[0].IsLoaded();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool ParticleSystem::Create (quint16 quantity)
{
	// Make sure we have at least one particle
	if (quantity == 0) return false;

	// Remove previous instances
	if (mParticles != nullptr)
		delete[] mParticles;

	// Create particles
	mQuantity = quantity;
	mParticles = new Mesh[mQuantity];
	VertexPositionTexture* vertices;

	float z = 0.0f;
	const float zValue = 1 / (float) mQuantity;

	for (quint32 i = 0; i < mQuantity; ++i, z += zValue)
	{
		// Create a single reference quad
		Mesh::CreateQuad (mParticles[i], -1, -1, 1, 1);

		vertices = (VertexPositionTexture*)
			mParticles[i].GetVertices()->GetData();

		// Vary each quad by their z value
		vertices[0].Position.Z = z;
		vertices[1].Position.Z = z;
		vertices[2].Position.Z = z;
		vertices[3].Position.Z = z;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Texture* ParticleSystem::GetTexture (void) const
{
	return mTexture;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void ParticleSystem::SetTexture (Texture* texture)
{
	if (mTexture != nullptr)
		mTexture->Release();

	if (texture == nullptr)
		return;

	mTexture = texture;
	mTexture->Retain();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void ParticleSystem::Draw (float totalTime, const Matrix& view) const
{
	// Check if particles loaded
	if (!IsLoaded()) return;

	// Update matrices
	if (mTexture != nullptr && !mTexture->IsLoaded())
		mTexture->Load();

	// Update shader
	mParticleSystem->SetValue ("Time", totalTime  / 1000);
	mParticleSystem->SetValue ("ModelViewProj", Engine::GetPerspective() * view);
	mParticleSystem->SetValue ("ViewInverse", Matrix::Invert (view));

	mParticleSystem->SetValue ("Position", Position);
	mParticleSystem->SetValue ("Diffuse", Diffuse);
	mParticleSystem->SetValue ("Alpha", Alpha);
	mParticleSystem->SetValue ("Speed", Speed);
	mParticleSystem->SetValue ("Spread", Spread);
	mParticleSystem->SetValue ("Shape", Shape);
	mParticleSystem->SetValue ("Size", Size);
	mParticleSystem->SetValue ("Gravity", Gravity);

	mParticleSystem->SetValue ("SystemHeight", SystemHeight);
	mParticleSystem->SetValue ("SystemShape", SystemShape);
	mParticleSystem->SetValue ("FadeInTime", FadeInTime);
	mParticleSystem->SetValue ("FadeOutTime", FadeOutTime);

	mParticleSystem->SetValue ("Texture", mTexture, 1);

	// Draw particles
	GL_CALL (glDepthMask (GL_FALSE));
	for (quint32 i = 0; i < mQuantity; ++i)
		mParticles[i].Draw();
	GL_CALL (glDepthMask (GL_TRUE));
}

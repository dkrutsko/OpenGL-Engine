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

#include "Demo/Demo.h"
#include "Demo/ShadowMap.h"
#include "Demo/Camera.h"

#include "Engine/Console.h"
#include "Engine/Engine.h"
#include "Content/Content.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Random.h"

#include "Graphics/Mesh.h"
#include "Graphics/Light.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/ParticleSystem.h"

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Constructors                                                          Demo //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Demo::Demo (void)
{
	mShadowMap = new ShadowMap();
	mShadowMap->Load();
	mPrevKeyboard.Sync();

	mCamera1 = new Camera (Vector3 (   0, 115,  165), Vector3 (   0, -0.70f, 0));
	mCamera2 = new Camera (Vector3 (-320, 230, -235), Vector3 (4.1f, -0.60f, 0));
	mCamera3 = new Camera (Vector3 (   0, 400,  800), Vector3 (   0, -0.45f, 0));
	mActiveCamera = mCamera1;

	mLight1 = new Light();
	mLight2 = new Light();

	mRandom = new Random();

	mDefault = new Texture();
	mDefault->Create (1, 1, 24);
	mDefault->GetData()[0] = 0;
	mDefault->GetData()[1] = 0;
	mDefault->GetData()[2] = 0;
	mDefault->Load();
	mDefault->Purge();

	mSky   = (Shader*) Content::Load ("Shaders/Sky.ast");
	mPhong = (Shader*) Content::Load ("Shaders/Phong.ast");
	mQuad  = (Shader*) Content::Load ("Shaders/Quad.ast" );

	if (mSky   != nullptr) { mSky  ->Load(); mSky  ->Purge(); }
	if (mPhong != nullptr) { mPhong->Load(); mPhong->Purge(); }
	if (mQuad  != nullptr) { mQuad ->Load(); mQuad ->Purge(); }

	mJungle = (Model*) Content::Load ("Models/Jungle.ast");

	if (mJungle != nullptr)
	{
		mJungle->LoadTextures();
		mJungle->LoadGeometry();
		mJungle->PurgeTextures();
		mJungle->PurgeGeometry();
	}

	mSphere = (Model*) Content::Load ("Models/Sphere.ast");

	if (mSphere != nullptr)
	{
		mSphere->LoadTextures();
		mSphere->LoadGeometry();
		mSphere->PurgeTextures();
		mSphere->PurgeGeometry();
	}

	mClouds = (ParticleSystem*) Content::Load ("Particles/Clouds.ast");
	mRain   = (ParticleSystem*) Content::Load ("Particles/Rain.ast");
	mStars  = (ParticleSystem*) Content::Load ("Particles/Stars.ast");

	if (mClouds != nullptr) mClouds->Load();
	if (mRain   != nullptr) mRain  ->Load();
	if (mStars  != nullptr) mStars ->Load();

	mStopRain = false;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Demo::~Demo (void)
{
	if (mShadowMap != nullptr) delete mShadowMap;

	if (mCamera1 != nullptr) delete mCamera1;
	if (mCamera2 != nullptr) delete mCamera2;
	if (mCamera3 != nullptr) delete mCamera3;
	if (mLight1  != nullptr) delete mLight1;
	if (mLight2  != nullptr) delete mLight2;

	if (mDefault != nullptr) mDefault->Release();
	if (mRandom  != nullptr) delete mRandom;

	if (mSky   != nullptr) mSky  ->Release();
	if (mPhong != nullptr) mPhong->Release();
	if (mQuad  != nullptr) mQuad ->Release();

	if (mJungle != nullptr) mJungle->Release();
	if (mSphere != nullptr) mSphere->Release();

	if (mClouds != nullptr) mClouds->Release();
	if (mRain   != nullptr) mRain  ->Release();
	if (mStars  != nullptr) mStars ->Release();
}



//----------------------------------------------------------------------------//
// Methods                                                               Demo //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Demo::Update (quint32 elapsedTime, quint32 totalTime)
{
	// Recreate buffers if the viewport has changed
	if (Engine::HasSizeChanged()) mShadowMap->Create();

	// Update keyboard state
	mCurrKeyboard.Sync();

	// Change camera to camera 1
	if (!mPrevKeyboard.Keys[SDLK_KP1] &&
		 mCurrKeyboard.Keys[SDLK_KP1])
		mActiveCamera = mCamera1;

	// Change camera to camera 2
	if (!mPrevKeyboard.Keys[SDLK_KP2] &&
		 mCurrKeyboard.Keys[SDLK_KP2])
		mActiveCamera = mCamera2;

	// Change camera to camera 3
	if (!mPrevKeyboard.Keys[SDLK_KP3] &&
		 mCurrKeyboard.Keys[SDLK_KP3])
		mActiveCamera = mCamera3;

	// Stop raining
	if (!mPrevKeyboard.Keys[SDLK_KP5] &&
		 mCurrKeyboard.Keys[SDLK_KP5])
		mStopRain = !mStopRain;

	// Save keyboard state
	mPrevKeyboard = mCurrKeyboard;

	// Update the camera
	if (mActiveCamera != mCamera3)
		mActiveCamera->Update (elapsedTime);

	// Update the shadow camera
	quint32 time = totalTime / 40.0f;
	float angle = Math::ToRadians (time % 360);

	mCamera3->Rotation.X = -angle + 1.57071;
	mCamera3->Position.X = 800 * Math::Cosr (angle);
	mCamera3->Position.Z = 800 * Math::Sinr (angle);

	mCamera3->Update();

	// Update light positions
	mLight1->Position = mCamera1->Position;
	mLight2->Position = mCamera2->Position;

	// Update matrix values
	Matrix modelViewProj = Engine::GetPerspective() * mActiveCamera->View;

	// Update shader values
	if (mPhong != nullptr)
	{
		mPhong->SetValue ("Projection", Engine::GetPerspective());
		mPhong->SetValue ("ModelView", mActiveCamera->View);

		mPhong->SetValue ("LightCount", 2);
		mPhong->SetValue ("LightPos[0]", mLight1->Position);
		mPhong->SetValue ("LightPos[1]", mLight2->Position);
		mPhong->SetValue ("LightColor[0]", mLight1->Diffuse);
		mPhong->SetValue ("LightColor[1]", mLight2->Diffuse);

		mPhong->SetValue ("ShadowLight", Engine::GetPerspective() * mCamera3->View);
	}

	if (mSky != nullptr)
	{
		mSky->SetValue ("ModelViewProj", Engine::GetPerspective() * mActiveCamera->View *
			Matrix::CreateFromAxisAngle (Vector3::UnitY, Math::ToRadians (totalTime / 500.0f)));
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Demo::Render (quint32 elapsedTime, quint32 totalTime)
{
	// Ensure that the model is valid
	if (mJungle == nullptr ||
		mPhong  == nullptr ||
		mSphere == nullptr) return;
	
	// Render the depth map
	mShadowMap->Begin (*mCamera3);
	for (quint32 i = 0; i < mJungle->Meshes.Length(); ++i)
		mJungle->Meshes[i]->Draw();
	mShadowMap->End();

	// Set shadow map inside the shader
	GL_CALL (glActiveTexture (GL_TEXTURE6));
	GL_CALL (glBindTexture (GL_TEXTURE_2D, mShadowMap->GetID()));
	mPhong->SetValue ("ShadowMap", 6);
	
	// Render the final model on the screen
	for (quint32 i = 0; i < mJungle->Meshes.Length(); ++i)
	{
		// Get the model mesh
		Mesh* mesh = mJungle->Meshes[i];
		if (mesh->Material < 0) continue;

		// Apply the material
		ApplyMaterial (mPhong, mJungle,
			mJungle->Materials[mesh->Material]);

		// Draw the mesh
		mesh->Draw();
	}

	// Render the sky sphere
	for (quint32 i = 0; i < mSphere->Meshes.Length(); ++i)
	{
		// Get the model mesh
		Mesh* mesh = mSphere->Meshes[i];
		if (mesh->Material < 0) continue;

		// Apply the material
		mSky->SetValue ("Texture", mSphere->Textures
			[mSphere->Materials[mesh->Material]->Diffuse.Texture], 7);

		// Draw the mesh
		mesh->Draw();
	}

	// Draw the particle systems
	if (mClouds != nullptr)
		mClouds->Draw (totalTime, mActiveCamera->View);

	if (mRain != nullptr && !mStopRain)
		mRain->Draw (totalTime, mActiveCamera->View);

	if (mStars != nullptr)
		mStars->Draw (totalTime, mActiveCamera->View);
}



//----------------------------------------------------------------------------//
// Internal                                                              Demo //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Demo::ApplyMaterial (Shader* shader, const Model* model, const Material* material) const
{
	if (shader == nullptr) return;

	shader->SetValue ("Ambient.Color",  material->Ambient.Color );
	shader->SetValue ("Diffuse.Color",  material->Diffuse.Color );
	shader->SetValue ("Specular.Color", material->Specular.Color);
	shader->SetValue ("Emissive.Color", material->Emissive.Color);

	if (material->Ambient.Texture != -1)
		 shader->SetValue ("Ambient.Texture", model->Textures[material->Ambient.Texture], 1);
	else shader->SetValue ("Ambient.Texture", mDefault, 1);

	if (material->Diffuse.Texture != -1)
		 shader->SetValue ("Diffuse.Texture", model->Textures[material->Diffuse.Texture], 2);
	else shader->SetValue ("Diffuse.Texture", mDefault, 2);

	if (material->Specular.Texture != -1)
		 shader->SetValue ("Specular.Texture", model->Textures[material->Specular.Texture], 3);
	else shader->SetValue ("Specular.Texture", mDefault, 3);

	if (material->Emissive.Texture != -1)
		 shader->SetValue ("Emissive.Texture", model->Textures[material->Emissive.Texture], 4);
	else shader->SetValue ("Emissive.Texture", mDefault, 4);

	shader->SetValue ("Alpha", material->Alpha);
	shader->SetValue ("Shininess", material->Shininess);

	if (material->Normal != -1)
		 shader->SetValue ("Normal", model->Textures[material->Normal], 5);
	else shader->SetValue ("Normal", 0);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Demo::DrawQuad (qint32 x, qint32 y, qint32 w, qint32 h) const
{
	// Compute position and scale
	float ww = Engine::GetWindowWidth();
	float wh = Engine::GetWindowHeight();

	y = wh + y - h;
	x *= 2; w *= 2;
	y *= 2; h *= 2;

	float x1 = x / ww - 1;
	float y1 = y / wh - 1;
	float x2 = (x + w) / ww - 1;
	float y2 = (y + h) / wh - 1;

	// Create a quad
	Mesh mesh;
	Mesh::CreateQuad (mesh, x1, y1, x2, y2);

	// Draw the quad
	mesh.Load();
	mesh.Draw();
}

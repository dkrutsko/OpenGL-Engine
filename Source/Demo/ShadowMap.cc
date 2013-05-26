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

#include "Demo/Camera.h"
#include "Demo/ShadowMap.h"
#include "Engine/Engine.h"
#include "Engine/Console.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Content/Content.h"

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Constructors                                                    BlurFilter //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

ShadowMap::ShadowMap (void)
{
	mDepth		= nullptr;
	mBlurH		= nullptr;
	mBlurV		= nullptr;

	mColorTexID		= 0;
	mDepthTexID		= 0;
	mShadowBufferID	= 0;

	mBlurTexID		= 0;
	mBlurBufferID	= 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

ShadowMap::~ShadowMap (void)
{
	Unload();
	Destroy();
}



//----------------------------------------------------------------------------//
// Methods                                                         BlurFilter //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void ShadowMap::Begin (const Camera& camera) const
{
	if (mDepth == nullptr ||
		mBlurH == nullptr ||
		mBlurV == nullptr) return;

	quint32 width  = Engine::GetWindowWidth ();
	quint32 height = Engine::GetWindowHeight();

	// Render a depth map using the position of the light
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, mShadowBufferID));
	GL_CALL (glViewport (0, 0, width, height));
	GL_CALL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	mDepth->SetValue ("Near", 10.0f);
	mDepth->SetValue ("Far", 1000.0f);
	mDepth->SetValue ("ModelView", camera.View);
	mDepth->SetValue ("Projection", Engine::GetPerspective());
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void ShadowMap::End (void) const
{
	if (mDepth == nullptr ||
		mBlurH == nullptr ||
		mBlurV == nullptr) return;

	quint32 width  = Engine::GetWindowWidth ();
	quint32 height = Engine::GetWindowHeight();

	// Create a new mesh quad
	Mesh mesh;
	Mesh::CreateQuad (mesh, -1, -1, 1, 1);
	mesh.Load();

	mBlurH->SetValue ("Scene", 1);
	mBlurV->SetValue ("Scene", 1);
	mBlurH->SetValue ("BlurSize", 0.001953125f);
	mBlurV->SetValue ("BlurSize", 0.001953125f);

	// Blur horizontally
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, mBlurBufferID));
	GL_CALL (glViewport (0, 0, width, height));

	GL_CALL (glActiveTexture (GL_TEXTURE1));
	GL_CALL (glBindTexture   (GL_TEXTURE_2D, mColorTexID));

	mBlurH->Use();
	mesh.Draw();

	// Blur vertically
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, mShadowBufferID));
	GL_CALL (glViewport (0, 0, width, height));

	GL_CALL (glActiveTexture (GL_TEXTURE1));
	GL_CALL (glBindTexture   (GL_TEXTURE_2D, mBlurTexID));

	mBlurV->Use();
	mesh.Draw();

	// Restore the window's default framebuffer
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, 0));
	GL_CALL (glViewport (0, 0, width, height));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool ShadowMap::Create (void)
{
	// Destroy previous depth buffers
	if (mShadowBufferID != 0) Destroy();

	quint32 width  = Engine::GetWindowWidth ();
	quint32 height = Engine::GetWindowHeight();

	// Create a texture depth component
	GL_CALL (glGenTextures (1, &mDepthTexID));
	GL_CALL (glBindTexture (GL_TEXTURE_2D, mDepthTexID));

	GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
	
	GL_CALL (glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0));
	GL_CALL (glBindTexture (GL_TEXTURE_2D, 0));

	// Create a texture color component
	GL_CALL (glGenTextures (1, &mColorTexID));
	GL_CALL (glBindTexture (GL_TEXTURE_2D, mColorTexID));

	GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GL_CALL (glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, 0));
	GL_CALL (glBindTexture (GL_TEXTURE_2D, 0));

	// Create a shadow framebuffer
	GL_CALL (glGenFramebuffers (1, &mShadowBufferID));
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, mShadowBufferID));
	
	GL_CALL (glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT , GL_TEXTURE_2D, mDepthTexID, 0));
	GL_CALL (glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTexID, 0));

	// Check for any framebuffer errors
	if (glCheckFramebufferStatus (GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{ Destroy(); return false; }
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, 0));

	// Create the blur framebuffer
	GL_CALL (glGenTextures (1, &mBlurTexID));
	GL_CALL (glBindTexture (GL_TEXTURE_2D, mBlurTexID));

	GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GL_CALL (glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GL_CALL (glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GL_CALL (glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, 0));

	GL_CALL (glGenFramebuffers (1, &mBlurBufferID));
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, mBlurBufferID));

	GL_CALL (glFramebufferTexture2D (GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mBlurTexID, 0));

	// Check for any framebuffer errors
	if (glCheckFramebufferStatus (GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{ Destroy(); return false; }
	GL_CALL (glBindFramebuffer (GL_FRAMEBUFFER, 0));

	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void ShadowMap::Destroy (void)
{
	GL_CALL (glBindTexture      (GL_TEXTURE_2D ,  0));
	GL_CALL (glBindFramebuffer  (GL_FRAMEBUFFER,  0));

	GL_CALL (glDeleteTextures      (1, &mColorTexID));
	GL_CALL (glDeleteTextures      (1, &mDepthTexID));
	GL_CALL (glDeleteFramebuffers  (1, &mShadowBufferID));

	GL_CALL (glDeleteTextures      (1, &mBlurTexID));
	GL_CALL (glDeleteFramebuffers  (1, &mBlurBufferID));

	mColorTexID		= 0;
	mDepthTexID		= 0;
	mShadowBufferID	= 0;

	mBlurTexID		= 0;
	mBlurBufferID	= 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool ShadowMap::Load (void)
{
	mDepth = (Shader*) Content::Load ("Shaders/Shadow/Depth.ast");
	mBlurH = (Shader*) Content::Load ("Shaders/Shadow/BlurH.ast");
	mBlurV = (Shader*) Content::Load ("Shaders/Shadow/BlurV.ast");

	if (mDepth == nullptr ||
		mBlurH == nullptr ||
		mBlurV == nullptr)
	{
		Unload(); return false;
	}

	mDepth->Load();
	mBlurH->Load();
	mBlurV->Load();
	
	mDepth->Purge();
	mBlurH->Purge();
	mBlurV->Purge();

	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void ShadowMap::Unload (void)
{
	if (mDepth != nullptr) mDepth->Release();
	if (mBlurH != nullptr) mBlurH->Release();
	if (mBlurV != nullptr) mBlurV->Release();
}

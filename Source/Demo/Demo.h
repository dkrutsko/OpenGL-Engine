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

#ifndef DEMO_H
#define DEMO_H

class Camera;
class Light;
class Model;
class Shader;
class Material;
class Mesh;
class Random;
class Texture;
class Color;
class ParticleSystem;
class ShadowMap;

#include "Math/Matrix.h"
#include <QGlobal.h>

#include "Engine/Input.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Demo
{
public:
	// Constructors
	 Demo (void);
	~Demo (void);

public:
	// Methods
	void Update			(quint32 elapsedTime, quint32 totalTime);
	void Render			(quint32 elapsedTime, quint32 totalTime);

private:
	// Internal
	void ApplyMaterial	(Shader* shader, const Model* model, const Material* material) const;

	void DrawQuad		(qint32 x, qint32 y, qint32 width, qint32 height) const;

private:
	// Fields
	ShadowMap*			mShadowMap;

	Camera*				mCamera1;
	Camera*				mCamera2;
	Camera*				mCamera3;
	Camera*				mActiveCamera;
	Light*				mLight1;
	Light*				mLight2;

	Texture*			mDefault;
	Random*				mRandom;

	Shader*				mSky;
	Shader*				mPhong;
	Shader*				mQuad;

	Model*				mJungle;
	Model*				mSphere;

	Keyboard			mPrevKeyboard;
	Keyboard			mCurrKeyboard;

	ParticleSystem*		mClouds;
	ParticleSystem*		mRain;
	ParticleSystem*		mStars;

	bool				mStopRain;
};

#endif // DEMO_H

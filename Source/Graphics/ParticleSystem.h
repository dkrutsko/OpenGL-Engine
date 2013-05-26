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

#ifndef GRAPHICS_PARTICLE_SYSTEM_H
#define GRAPHICS_PARTICLE_SYSTEM_H

class Mesh;
class Texture;
class Shader;
class Camera;
class Matrix;

#include "Graphics/Color.h"
#include "Math/Vector3.h"
#include "Content/Asset.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ParticleSystem : public Asset
{
	ASSET_DECLARATION;

public:
	// Constructors
	ParticleSystem (void);
	ParticleSystem (const ParticleSystem& system);

protected:
	virtual ~ParticleSystem		(void);

public:
	// Methods
	bool		Load			(void);
	bool		Reload			(bool force = false);
	void		Unload			(bool force = false);

	bool		IsLoaded		(void) const;
	bool		Create			(quint16 quantity);

	Texture*	GetTexture		(void) const;
	void		SetTexture		(Texture* texture);
	quint16		GetQuantity		(void) const { return mQuantity; }

	void		Draw			(float totalTime, const Matrix& view) const;

public:
	// Properties
	Vector3		Position;
	Color		Diffuse;

	float		Alpha;
	float		Speed;
	float		Spread;
	float		Shape;
	float		Size;
	float		Gravity;

	float		SystemHeight;
	float		SystemShape;
	float		FadeInTime;
	float		FadeOutTime;

private:
	// Fields
	quint16		mQuantity;
	Mesh*		mParticles;

	Texture*	mTexture;
	Shader*		mParticleSystem;
};

#endif // GRAPHICS_PARTICLE_SYSTEM_H

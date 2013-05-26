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

#ifndef SHADOW_MAP_H
#define SHADOW_MAP_H

class Camera;
class Shader;

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class ShadowMap
{
public:
	// Constructors
	 ShadowMap		(void);
	~ShadowMap		(void);

public:
	// Methods
	void Begin		(const Camera& camera) const;
	void End		(void) const;

	bool Create		(void);
	void Destroy	(void);

	bool Load		(void);
	void Unload		(void);

	quint32 GetID	(void) const { return mColorTexID; }

private:
	// Fields
	Shader*			mDepth;
	Shader*			mBlurH;
	Shader*			mBlurV;

	quint32			mColorTexID;
	quint32			mDepthTexID;
	quint32			mShadowBufferID;

	quint32			mBlurTexID;
	quint32			mBlurBufferID;
};

#endif // SHADOW_MAP_H

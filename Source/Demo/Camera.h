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

#ifndef DEMO_CAMERA_H
#define DEMO_CAMERA_H

#include "Demo/Entity.h"
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Engine/Input.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Represents a camera entity used to navigate and traverse the 3D world.
/// </summary>

class Camera : public Entity
{
public:
	// Constructors
	Camera (void);
	Camera (const Vector3& position);
	Camera (const Vector3& position, const Vector3& rotation);

public:
	// Methods
	void		Update				(void);
	void		Update				(quint32 elapsedTime);

private:
	// Internal
	void		PositionMouse		(void);
	void		CenterMouse			(void);

public:
	// Properties
	Matrix		View;				// View matrix
	bool		Inverted;			// Is the camera Inverted

	Vector3		Position;			// Camera position
	Vector3		Rotation;			// Camera rotation

	Vector3		ResetPosition;		// Camera reset position
	Vector3		ResetRotation;		// Camera reset rotation

private:
	// Fields
	Mouse		mPrevMouse;			// Previous mouse state
	Mouse		mCurrMouse;			// Current  mouse state
	Keyboard	mPrevKeyboard;		// Previous keyboard state
	Keyboard	mCurrKeyboard;		// Current  keyboard state

	qint32		mOldMouseX;			// Previous x position
	qint32		mOldMouseY;			// Previous y position
	bool		mMouseSet;			// Mouse capture flag
};

#endif // DEMO_CAMERA_H

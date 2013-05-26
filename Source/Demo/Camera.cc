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

#include "Engine/Input.h"
#include "Engine/Engine.h"

#include "Math/Math.h"
#include "Demo/Camera.h"



//----------------------------------------------------------------------------//
// Constructors                                                        Camera //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Camera::Camera (void) : Entity()
{
	mPrevMouse   .Sync();
	mPrevKeyboard.Sync();

	Inverted  = false;
	mMouseSet = false;

	Position = Vector3::Zero;
	Rotation = Vector3::Zero;

	ResetPosition = Position;
	ResetRotation = Rotation;

	Update();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Camera::Camera (const Vector3& position) : Entity()
{
	mPrevMouse   .Sync();
	mPrevKeyboard.Sync();

	Inverted  = false;
	mMouseSet = false;

	Position = position;
	Rotation = Vector3::Zero;

	ResetPosition = Position;
	ResetRotation = Rotation;

	Update();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Camera::Camera (const Vector3& position, const Vector3& rotation) : Entity()
{
	mPrevMouse   .Sync();
	mPrevKeyboard.Sync();

	Inverted  = false;
	mMouseSet = false;

	Position = position;
	Rotation = rotation;

	ResetPosition = Position;
	ResetRotation = Rotation;

	Update();
}



//----------------------------------------------------------------------------//
// Methods                                                             Camera //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Camera::Update (void)
{
	View = Matrix::CreateFromYawPitchRoll
		(Rotation.X, Rotation.Y, Rotation.Z) *
		Matrix::CreateTranslation (-Position);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Camera::Update (quint32 elapsedTime)
{
	// Update input states
	mCurrMouse   .Sync();
	mCurrKeyboard.Sync();

	PositionMouse();

	// Reset position and rotation
	if (!mPrevKeyboard.Keys[SDLK_q] &&
		 mCurrKeyboard.Keys[SDLK_q])
	{
		Position = ResetPosition;
		Rotation = ResetRotation;
	}

	// Mouse rotations
	float xDiff = mPrevMouse.X - mCurrMouse.X;
	float yDiff = mPrevMouse.Y - mCurrMouse.Y;

	if (mCurrMouse.Right)
		if (Inverted)
		{
			Rotation.X += xDiff * 0.0025f;
			Rotation.Y -= yDiff * 0.0025f;
		}

		else
		{
			Rotation.X += xDiff * 0.0025f;
			Rotation.Y += yDiff * 0.0025f;
		}

	if (mCurrMouse.Right) CenterMouse();
 
	// Keyboard movement
	Vector3 moveVector = Vector3::Zero;
	if (mCurrKeyboard.Keys[SDLK_s])
		moveVector += Vector3::Backward;

	if (mCurrKeyboard.Keys[SDLK_w] || (mCurrMouse.Left && mCurrMouse.Right))
		moveVector += Vector3::Forward;

	if (mCurrKeyboard.Keys[SDLK_a])
		if (!mCurrMouse.Right)
			Rotation.X += 0.02f * elapsedTime;
		else
			moveVector += Vector3::Left;
	
	if (mCurrKeyboard.Keys[SDLK_d])
		if (!mCurrMouse.Right)
			Rotation.X -= 0.02f * elapsedTime;
		else
			moveVector += Vector3::Right;

	// Clamp angles
	Rotation.X = Math::WrapTwoPI (Rotation.X);
	Rotation.Z = Math::WrapTwoPI (Rotation.Z);

	Rotation.Y = Math::Clamp (Rotation.Y, -Math::PiOver2, Math::PiOver2);

	// Apply movement to position
	Matrix rotation = Matrix::CreateFromYawPitchRoll (Rotation.X, Rotation.Y, Rotation.Z);
	Vector3 rotated = Vector3::Transform (moveVector * elapsedTime, rotation);
	if (mCurrKeyboard.Keys[SDLK_LSHIFT]) rotated *= 3.0f; Position += rotated;

	if (mCurrKeyboard.Keys[SDLK_SPACE])
		if (mCurrKeyboard.Keys[SDLK_LSHIFT])
			 Position += 3.0f * Vector3::Up;
		else Position += Vector3::Up;

	if (mCurrKeyboard.Keys[SDLK_LCTRL])
		if (mCurrKeyboard.Keys[SDLK_LSHIFT])
			 Position += 3.0f * Vector3::Down;
		else Position += Vector3::Down;

	// Update matrix value
	View = rotation * Matrix::CreateTranslation (-Position);

	// Save input states
	mPrevMouse    = mCurrMouse;
	mPrevKeyboard = mCurrKeyboard;
}



//----------------------------------------------------------------------------//
// Internal                                                            Camera //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Handles initial mouse visibility and position. </summary>

void Camera::PositionMouse (void)
{
	// Mouse button was pressed
	if (!mPrevMouse.Right && mCurrMouse.Right)
	{
		mOldMouseX = mCurrMouse.X;
		mOldMouseY = mCurrMouse.Y;

		mMouseSet = true;
		Mouse::SetVisible (false);
		CenterMouse();
	}

	// Mouse button was released
	if (mMouseSet && !mCurrMouse.Right)
	{
		mMouseSet = false;
		Mouse::SetPosition (mOldMouseX, mOldMouseY);
		Mouse::SetVisible (true);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Sets the mouse position to the center of the screen and
/// 		  updates both the current and previous mouse states. </summary>

void Camera::CenterMouse (void)
{
	Mouse::SetPosition (Engine::GetWindowWidth () / 2,
						Engine::GetWindowHeight() / 2);

	mCurrMouse.Sync();
	mPrevMouse = mCurrMouse;
}

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

#include <SDL.h>
#include "Engine/Input.h"



//----------------------------------------------------------------------------//
// Constructors                                                      Keyboard //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Keyboard::Keyboard (void)
{
	Length = 0;
	Keys   = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Keyboard::~Keyboard (void)
{
	if (Keys != nullptr)
		delete[] Keys;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Keyboard::Keyboard (const Keyboard& keyboard)
{
	Length = keyboard.Length;
	Keys   = keyboard.Keys;

	if (Length != 0)
	{
		Keys = new bool[Length];
		memcpy (Keys, keyboard.Keys, Length);
	}
}



//----------------------------------------------------------------------------//
// Methods                                                           Keyboard //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Keyboard::Sync (void)
{
	SDL_PumpEvents();

	if (Keys != nullptr)
		delete[] Keys;

	quint8* keys = SDL_GetKeyState (&Length);
	Keys = new bool[Length];

	for (qint32 i = 0; i < Length; ++i)
		Keys[i] = keys[i] == 0 ? false : true;
}



//----------------------------------------------------------------------------//
// Operators                                                         Keyboard //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Keyboard::operator == (const Keyboard& value) const
{
	if (Length != value.Length)
		return false;

	for (qint32 i = 0; i < Length; ++i)
		if (Keys[i] != value.Keys[i])
			return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Keyboard::operator != (const Keyboard& value) const
{
	if (Length != value.Length)
		return true;

	for (qint32 i = 0; i < Length; ++i)
		if (Keys[i] != value.Keys[i])
			return true;

	return false;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Keyboard& Keyboard::operator = (const Keyboard& keyboard)
{
	if (Keys != nullptr)
		delete[] Keys;

	Length = keyboard.Length;
	Keys   = keyboard.Keys;

	if (Length != 0)
	{
		Keys = new bool[Length];
		memcpy (Keys, keyboard.Keys, Length);
	}

	return *this;
}



//----------------------------------------------------------------------------//
// Constructors                                                         Mouse //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Mouse::Mouse (void)
{
	X		= 0;
	Y		= 0;

	Left	= false;
	Middle	= false;
	Right	= false;

	X1		= false;
	X2		= false;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Mouse::~Mouse (void)
{
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Mouse::Mouse (const Mouse& mouse)
{
	X		= mouse.X;
	Y		= mouse.Y;

	Left	= mouse.Left;
	Middle	= mouse.Middle;
	Right	= mouse.Right;

	X1		= mouse.X1;
	X2		= mouse.X2;
}



//----------------------------------------------------------------------------//
// Methods                                                              Mouse //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mouse::Sync (void)
{
	SDL_PumpEvents();
	SDL_GetMouseState (&X, &Y);

	Left	= SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_LEFT);
	Middle	= SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_MIDDLE);
	Right	= SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_RIGHT);

	X1		= SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_X1);
	X2		= SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_X2);
}



//----------------------------------------------------------------------------//
// Static                                                               Mouse //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mouse::SetPosition (quint32 x, quint32 y)
{
	SDL_WarpMouse (x, y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Mouse::IsVisible (void)
{
	return SDL_ShowCursor (SDL_QUERY) == SDL_ENABLE ? true : false;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Mouse::SetVisible (bool visible)
{
	if (visible)
		SDL_ShowCursor (SDL_ENABLE);
	else
		SDL_ShowCursor (SDL_DISABLE);
}



//----------------------------------------------------------------------------//
// Operators                                                            Mouse //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Mouse::operator == (const Mouse& value) const
{
	return X  == value.X  &&
		   Y  == value.Y  &&
		   X1 == value.X1 &&
		   X2 == value.X2 &&

		   Left   == value.Left   &&
		   Middle == value.Middle &&
		   Right  == value.Right;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Mouse::operator != (const Mouse& value) const
{
	return X  != value.X  ||
		   Y  != value.Y  ||
		   X1 != value.X1 ||
		   X2 != value.X2 ||

		   Left   != value.Left   ||
		   Middle != value.Middle ||
		   Right  != value.Right;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Mouse& Mouse::operator = (const Mouse& mouse)
{
	X		= mouse.X;
	Y		= mouse.Y;

	Left	= mouse.Left;
	Middle	= mouse.Middle;
	Right	= mouse.Right;

	X1		= mouse.X1;
	X2		= mouse.X2;

	return *this;
}

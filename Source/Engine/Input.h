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

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <QGlobal.h>
#include <SDL_keysym.h>



//----------------------------------------------------------------------------//
// Keyboard                                                                   //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Keyboard
{
public:
	// Constructors
	 Keyboard (void);
	~Keyboard (void);
	 Keyboard (const Keyboard& keyboard);

public:
	// Methods
	void Sync (void);

public:
	// Operators
	bool operator == (const Keyboard& value) const;
	bool operator != (const Keyboard& value) const;

	Keyboard& operator = (const Keyboard& keyboard);

public:
	// Properties
	qint32 Length;	// Keys length
	bool*  Keys;	// Keys
};



//----------------------------------------------------------------------------//
// Mouse                                                                      //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Mouse
{
public:
	// Constructors
	 Mouse (void);
	~Mouse (void);
	 Mouse (const Mouse& mouse);

public:
	// Methods
	void Sync (void);

public:
	// Static
	static void SetPosition (quint32 x, quint32 y);

	static bool IsVisible  (void);
	static void SetVisible (bool visible);

public:
	// Operators
	bool operator == (const Mouse& value) const;
	bool operator != (const Mouse& value) const;

	Mouse& operator = (const Mouse& mouse);

public:
	// Properties
	qint32 X;		// X position
	qint32 Y;		// Y position

	bool Left;		// Left button
	bool Middle;	// Middle button
	bool Right;		// Right button

	bool X1;		// X1 button
	bool X2;		// X2 button
};

#endif // ENGINE_INPUT_H

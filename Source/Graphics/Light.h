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

#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H

#include "Math/Vector3.h"
#include "Graphics/Color.h"

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Light
{
public:
	// Constructors
	explicit Light (const Vector3& position = Vector3::Zero);

public:
	// Properties
	Vector3	Position;		// Position
	bool	Visible;		// Visibility

	Color	Ambient;		// Ambient color
	Color	Diffuse;		// Diffuse color
	Color	Specular;		// Specular color
	
	float	Attenuation;	// Attenuation
	float	Exponent;		// Exponent
};

#endif // GRAPHICS_LIGHT_H

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

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include "Graphics/Color.h"
#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#pragma pack (push, 1)
class Material
{
public:
	// Types
	////////////////////////////////////////////////////////////////////////////////
	/// <summary> </summary>

	class Channel
	{
	public:
		// Constructors
		Channel (void);
		Channel (float r, float g, float b, float a = 1.0f);

	public:
		// Properties
		Color  Color;
		qint32 Texture;
	};

public:
	// Constructors
	Material (void);

public:
	// Properties
	Channel	Ambient;
	Channel	Diffuse;
	Channel	Specular;
	Channel	Emissive;

	float	Alpha;
	float	Shininess;
	qint32	Normal;
};
#pragma pack (pop)

#endif // GRAPHICS_MATERIAL_H

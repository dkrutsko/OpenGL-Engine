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

#include "Math/Math.h"
#include "Graphics/Color.h"



//----------------------------------------------------------------------------//
// Constants                                                            Color //
//----------------------------------------------------------------------------//

const Color Color::Black		= Color (0, 0, 0, 1);
const Color Color::White		= Color (1, 1, 1, 1);

const Color Color::Red			= Color (1, 0, 0, 1);
const Color Color::Green		= Color (0, 1, 0, 1);
const Color Color::Blue			= Color (0, 0, 1, 1);

const Color Color::Transparent	= Color (0, 0, 0, 0);



//----------------------------------------------------------------------------//
// Constructors                                                         Color //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new Color using real values [0.0, 1.0]. </summary>

Color::Color (float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}



//----------------------------------------------------------------------------//
// Static                                                               Color //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two colors. </summary>

float Color::Distance (const Color& value1, const Color& value2)
{
	float dr = value1.R - value2.R;
	float dg = value1.G - value2.G;
	float db = value1.B - value2.B;
	float da = value1.A - value2.A;

	return Math::Sqrt ((dr * dr) + (dg * dg) + (db * db) + (da * da));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two colors squared. </summary>

float Color::DistanceSquared (const Color& value1, const Color& value2)
{
	float dr = value1.R - value2.R;
	float dg = value1.G - value2.G;
	float db = value1.B - value2.B;
	float da = value1.A - value2.A;

	return (dr * dr) + (dg * dg) + (db * db) + (da * da);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Linearly interpolates between two colors. </summary>

Color Color::Lerp (const Color& value1, const Color& value2, float amount)
{
	return Color
	(
		value1.R + ((value2.R - value1.R) * amount),
		value1.G + ((value2.G - value1.G) * amount),
		value1.B + ((value2.B - value1.B) * amount),
		value1.A + ((value2.A - value1.A) * amount)
	);
}



//----------------------------------------------------------------------------//
// Operators                                                            Color //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the specified color by a scale factor. </summary>

Color& operator *= (Color& value, float scale)
{
	quint32 R = value.R * scale;
	quint32 G = value.G * scale;
	quint32 B = value.B * scale;
	quint32 A = value.A * scale;

	value.R = (quint8) (R > 255 ? 255 : R);
	value.G = (quint8) (G > 255 ? 255 : G);
	value.B = (quint8) (B > 255 ? 255 : B);
	value.A = (quint8) (A > 255 ? 255 : A);

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the specified color by a scale factor. </summary>

Color operator * (const Color& value, float scale)
{
	quint32 R = value.R * scale;
	quint32 G = value.G * scale;
	quint32 B = value.B * scale;
	quint32 A = value.A * scale;

	return Color
	(
		(quint8) (R > 255 ? 255 : R),
		(quint8) (G > 255 ? 255 : G),
		(quint8) (B > 255 ? 255 : B),
		(quint8) (A > 255 ? 255 : A)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Determines whether the specified colors are equal. </summary>

bool operator == (const Color& value1, const Color& value2)
{
	return value1.R == value2.R &&
		   value1.G == value2.G &&
		   value1.B == value2.B &&
		   value1.A == value2.A;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Determines whether the specified colors are not equal. </summary>

bool operator != (const Color& value1, const Color& value2)
{
	return value1.R != value2.R ||
		   value1.G != value2.G ||
		   value1.B != value2.B ||
		   value1.A != value2.A;
}

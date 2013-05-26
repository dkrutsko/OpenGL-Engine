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

#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Color
{
public:
	// Constants
	static const Color Black;		// Color (0, 0, 0, 1)
	static const Color White;		// Color (1, 1, 1, 1)

	static const Color Red;			// Color (1, 0, 0, 1)
	static const Color Green;		// Color (0, 1, 0, 1)
	static const Color Blue;		// Color (0, 0, 1, 1)

	static const Color Transparent;	// Color (0, 0, 0, 0)

public:
	// Constructors
	explicit Color (void) { }
	explicit Color (float r, float g, float b, float a = 1.0f);

public:
	// Methods
//	Color			Darker			(void) const;
//	Color			Brighter		(void) const;

//	float			GetHue			(void) const;
//	float			GetSaturation	(void) const;
//	float			GetBrightness	(void) const;

//	quint8			GetRed			(void) const;
//	quint8			GetGreen		(void) const;
//	quint8			GetBlue			(void) const;
//	quint8			GetAlpha		(void) const;

//	void			SetRed			(quint8 red);
//	void			SetGreen		(quint8 red);
//	void			SetBlue			(quint8 red);
//	void			SetAlpha		(quint8 red);

//	void			ToRGB			(quint8& r, quint8& g, quint8& b)			const;
//	void			ToRGBA			(float&  r, float&  g, float&  b, float& a)	const;
//	void			ToHSB			(float&  h, float&  s, float&  b)			const;
//	void			ToLAB			(float&  l, float&  a, float&  b)			const;
//	void			ToXYZ			(float&  x, float&  y, float&  z)			const;
//	void			ToCMYK			(float&  c, float&  m, float&  y, float& k)	const;

//	quint32			ToPacked		(void) const;

public:
	// Static
	static float	Distance		(const Color& value1, const Color& value2);
	static float	DistanceSquared	(const Color& value1, const Color& value2);
	static Color	Lerp			(const Color& value1, const Color& value2, float amount);

//	static Color	FromRGB			(quint8 r, quint8 g, quint8 b);
//	static Color	FromRGBA		(float  r, float  g, float  b, float a);
//	static Color	FromHSB			(float  h, float  s, float  b);
//	static Color	FromLAB			(float  l, float  a, float  b);
//	static Color	FromXYZ			(float  x, float  y, float  z);
//	static Color	FromCMYK		(float  c, float  m, float  y, float k);

//	static Color	FromPacked		(quint32 packed);

public:
	// Properties
	float R;	// Red component
	float G;	// Green component
	float B;	// Blue component
	float A;	// Alpha component
};



//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//

Color& operator *= (      Color& value, float scale);
Color  operator *  (const Color& value, float scale);

bool operator == (const Color& value1, const Color& value2);
bool operator != (const Color& value1, const Color& value2);

#endif // GRAPHICS_COLOR_H

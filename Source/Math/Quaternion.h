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

#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H

class Matrix;
class Vector3;

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Defines a four-dimensional vector (x, y, z, w), which is used to
/// efficiently rotate an object about the (x, y, z) vector by the angle
/// theta, where w = cos (theta / 2).
/// </summary>

class Quaternion
{
public:
	// Constants
	static const Quaternion One;					// Quaternion (1, 1, 1, 1)
	static const Quaternion Zero;					// Quaternion (0, 0, 0, 0)
	static const Quaternion Identity;				// Quaternion (0, 0, 0, 1)

public:
	// Constructors
	explicit Quaternion								(void) { }
	explicit Quaternion								(float x, float y, float z, float w);
	explicit Quaternion								(const Vector3& vector, float scalar);

public:
	// Methods
	float				Length						(void) const;
	float				LengthSquared				(void) const;
	void				Normalize					(void);
	void				Conjugate					(void);

public:
	// Static
	static Quaternion	Inverse						(const Quaternion& value);
	static Quaternion	Normalize					(const Quaternion& value);
	static Quaternion	Conjugate					(const Quaternion& value);

	static Quaternion	Lerp						(const Quaternion &source, const Quaternion &target, float amount);
	static Quaternion	Slerp						(const Quaternion &source, const Quaternion &target, float amount);

	static float		Dot							(const Quaternion& value1, const Quaternion& value2);
	static Quaternion	Concatenate					(const Quaternion& value1, const Quaternion& value2);

	static Quaternion	CreateFromAxisAngle			(const Vector3& axis, float angle);
	static Quaternion	CreateFromYawPitchRoll		(float yaw, float pitch, float roll);
	static Quaternion	CreateFromRotationMatrix	(const Matrix& matrix);

public:
	// Fields
	float X;			// X-component
	float Y;			// Y-component
	float Z;			// Z-component
	float W;			// W-component
};



//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//

Quaternion& operator += (Quaternion& value1, const Quaternion& value2);
Quaternion& operator -= (Quaternion& value1, const Quaternion& value2);
Quaternion& operator *= (Quaternion& value1, const Quaternion& value2);
Quaternion& operator *= (Quaternion& value, float scalar);
Quaternion& operator /= (Quaternion& value1, const Quaternion& value2);
Quaternion& operator /= (Quaternion& value, float divider);

Quaternion operator + (const Quaternion& value1, const Quaternion& value2);
Quaternion operator - (const Quaternion& value1, const Quaternion& value2);
Quaternion operator * (const Quaternion& value1, const Quaternion& value2);
Quaternion operator * (const Quaternion& value, float scalar);
Quaternion operator * (float scalar, const Quaternion& value);
Quaternion operator / (const Quaternion& value1, const Quaternion& value2);
Quaternion operator / (const Quaternion& value1, float divider);

bool operator == (const Quaternion& value1, const Quaternion& value2);
bool operator != (const Quaternion& value1, const Quaternion& value2);

bool operator <  (const Quaternion& value1, const Quaternion& value2);
bool operator <= (const Quaternion& value1, const Quaternion& value2);
bool operator >  (const Quaternion& value1, const Quaternion& value2);
bool operator >= (const Quaternion& value1, const Quaternion& value2);

Quaternion operator - (const Quaternion& value);

#endif // MATH_QUATERNION_H

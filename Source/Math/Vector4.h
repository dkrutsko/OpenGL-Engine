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

#ifndef MATH_VECTOR4_H
#define MATH_VECTOR4_H

class Matrix;
class Quaternion;
class Vector2;
class Vector3;

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Represents a vector with four components. </summary>

class Vector4
{
public:
	// Constants
	static const Vector4 One;		// Vector4 (1, 1, 1, 1)
	static const Vector4 Zero;		// Vector4 (0, 0, 0, 0)

	static const Vector4 UnitX;		// Vector4 (1, 0, 0, 0)
	static const Vector4 UnitY;		// Vector4 (0, 1, 0, 0)
	static const Vector4 UnitZ;		// Vector4 (0, 0, 1, 0)
	static const Vector4 UnitW;		// Vector4 (0, 0, 0, 1)

	static const Vector4 Identity;	// Vector4 (0, 0, 0, 1)

public:
	// Constructors
	explicit Vector4				(void) { }
	explicit Vector4				(float x, float y, float z, float w);

	explicit Vector4				(float value);
	explicit Vector4				(float value, float z, float w);
	explicit Vector4				(float value, float w);

	explicit Vector4				(const Vector2& value, float z = 0, float w = 0);
	explicit Vector4				(const Vector3& value, float w = 0);

public:
	// Methods
	float			Length			(void) const;
	float			LengthSquared	(void) const;
	void			Normalize		(void);

public:
	// Static
	static float	Dot				(const Vector4& value1, const Vector4& value2);
	static Vector4	Min				(const Vector4& value1, const Vector4& value2);
	static Vector4	Max				(const Vector4& value1, const Vector4& value2);

	static float	Distance		(const Vector4& value1, const Vector4& value2);
	static float	DistanceSquared	(const Vector4& value1, const Vector4& value2);
	static Vector4	Normalize		(const Vector4& value);

	static Vector4	Clamp			(const Vector4& value, const Vector4& min, const Vector4& max);

	static Vector4	Lerp			(const Vector4& value1, const Vector4& value2, float amount);
	static Vector4	SmoothStep		(const Vector4& value1, const Vector4& value2, float amount);
	static Vector4	Barycentric		(const Vector4& value1, const Vector4& value2, const Vector4& value3, float amount1, float amount2);
	static Vector4	CatmullRom		(const Vector4& value1, const Vector4& value2, const Vector4& value3, const Vector4& value4, float amount);
	static Vector4	Hermite			(const Vector4& value1, const Vector4& tangent1, const Vector4& value2, const Vector4& tangent2, float amount);

	static Vector4	Transform		(const Vector2& position, const Matrix& matrix);
	static Vector4	Transform		(const Vector3& position, const Matrix& matrix);
	static Vector4	Transform		(const Vector4& position, const Matrix& matrix);

	static Vector4	Transform		(const Vector2& position, const Quaternion& rotation);
	static Vector4	Transform		(const Vector3& position, const Quaternion& rotation);
	static Vector4	Transform		(const Vector4& position, const Quaternion& rotation);

	static void		Transform		(quint32 length, const Vector4* source, const Matrix& matrix, Vector4* target);
	static void		Transform		(quint32 length, const Vector4* source, const Quaternion& rotation, Vector4* target);

	static void		Transform		(quint32 length, quint32 sourceIndex, const Vector4* source,
									 const Matrix& matrix, quint32 targetIndex, Vector4* target);

	static void		Transform		(quint32 length, quint32 sourceIndex, const Vector4* source,
									 const Quaternion& rotation, quint32 targetIndex, Vector4* target);
		
public:
	// Fields
	float X;		// X-component
	float Y;		// Y-component
	float Z;		// Z-component
	float W;		// W-component
};



//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//

Vector4& operator += (Vector4& value1, const Vector4& value2);
Vector4& operator -= (Vector4& value1, const Vector4& value2);
Vector4& operator *= (Vector4& value1, const Vector4& value2);
Vector4& operator /= (Vector4& value1, const Vector4& value2);

Vector4& operator += (Vector4& value1, float value2);
Vector4& operator -= (Vector4& value1, float value2);
Vector4& operator *= (Vector4& value1, float value2);
Vector4& operator /= (Vector4& value1, float value2);

Vector4 operator + (const Vector4& value1, const Vector4& value2);
Vector4 operator - (const Vector4& value1, const Vector4& value2);
Vector4 operator * (const Vector4& value1, const Vector4& value2);
Vector4 operator / (const Vector4& value1, const Vector4& value2);

Vector4 operator + (const Vector4& value1, float value2);
Vector4 operator - (const Vector4& value1, float value2);
Vector4 operator * (const Vector4& value1, float value2);
Vector4 operator / (const Vector4& value1, float value2);
Vector4 operator + (float value1, const Vector4& value2);
Vector4 operator - (float value1, const Vector4& value2);
Vector4 operator * (float value1, const Vector4& value2);
Vector4 operator / (float value1, const Vector4& value2);

bool operator == (const Vector4& value1, const Vector4& value2);
bool operator != (const Vector4& value1, const Vector4& value2);

bool operator <  (const Vector4& value1, const Vector4& value2);
bool operator <= (const Vector4& value1, const Vector4& value2);
bool operator >  (const Vector4& value1, const Vector4& value2);
bool operator >= (const Vector4& value1, const Vector4& value2);

Vector4 operator - (const Vector4& value);

Vector4& operator ++ (Vector4& value);
Vector4& operator -- (Vector4& value);
Vector4  operator ++ (Vector4& value, int);
Vector4  operator -- (Vector4& value, int);

#endif // MATH_VECTOR4_H

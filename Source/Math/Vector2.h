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

#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

class Matrix;
class Quaternion;
class Vector3;
class Vector4;

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Represents a vector with two components. </summary>

class Vector2
{
public:
	// Constants
	static const Vector2 One;		// Vector2 (1, 1)
	static const Vector2 Zero;		// Vector2 (0, 0)

	static const Vector2 UnitX;		// Vector2 (1, 0)
	static const Vector2 UnitY;		// Vector2 (0, 1)

public:
	// Constructors
	explicit Vector2				(void) { }
	explicit Vector2				(float x, float y);
	explicit Vector2				(float value);

	explicit Vector2				(const Vector3& value);
	explicit Vector2				(const Vector4& value);

public:
	// Methods
	float			Length			(void) const;
	float			LengthSquared	(void) const;
	void			Normalize		(void);

public:
	// Static
	static float	Dot				(const Vector2& value1, const Vector2& value2);
	static Vector2	Min				(const Vector2& value1, const Vector2& value2);
	static Vector2	Max				(const Vector2& value1, const Vector2& value2);

	static float	Distance		(const Vector2& value1, const Vector2& value2);
	static float	DistanceSquared	(const Vector2& value1, const Vector2& value2);
	static Vector2	Normalize		(const Vector2& value);

	static Vector2	Clamp			(const Vector2& value, const Vector2& min, const Vector2& max);
	static Vector2	Reflect			(const Vector2& value, const Vector2& normal);

	static Vector2	Lerp			(const Vector2& value1, const Vector2& value2, float amount);
	static Vector2	SmoothStep		(const Vector2& value1, const Vector2& value2, float amount);
	static Vector2	Barycentric		(const Vector2& value1, const Vector2& value2, const Vector2& value3, float amount1, float amount2);
	static Vector2	CatmullRom		(const Vector2& value1, const Vector2& value2, const Vector2& value3, const Vector2& value4, float amount);
	static Vector2	Hermite			(const Vector2& value1, const Vector2& tangent1, const Vector2& value2, const Vector2& tangent2, float amount);

	static Vector2	Transform		(const Vector2& position, const Matrix& matrix);
	static Vector2	Transform		(const Vector2& position, const Quaternion& rotation);
	static Vector2	TransformNormal	(const Vector2& normal, const Matrix& matrix);

	static void		Transform		(quint32 length, const Vector2* source, const Matrix& matrix, Vector2* target);
	static void		Transform		(quint32 length, const Vector2* source, const Quaternion& rotation, Vector2* target);
	static void		TransformNormal	(quint32 length, const Vector2* source, const Matrix& matrix, Vector2* target);

	static void		Transform		(quint32 length, quint32 sourceIndex, const Vector2* source,
									 const Matrix& matrix, quint32 targetIndex, Vector2* target);

	static void		Transform		(quint32 length, quint32 sourceIndex, const Vector2* source,
									 const Quaternion& rotation, quint32 targetIndex, Vector2* target);

	static void		TransformNormal	(quint32 length, quint32 sourceIndex, const Vector2* source,
									 const Matrix& matrix, quint32 targetIndex, Vector2* target);
		
public:
	// Fields
	float X;		// X-component
	float Y;		// Y-component
};



//----------------------------------------------------------------------------//
// Operators                                                          Vector2 //
//----------------------------------------------------------------------------//

Vector2& operator += (Vector2& value1, const Vector2& value2);
Vector2& operator -= (Vector2& value1, const Vector2& value2);
Vector2& operator *= (Vector2& value1, const Vector2& value2);
Vector2& operator /= (Vector2& value1, const Vector2& value2);

Vector2& operator += (Vector2& value1, float value2);
Vector2& operator -= (Vector2& value1, float value2);
Vector2& operator *= (Vector2& value1, float value2);
Vector2& operator /= (Vector2& value1, float value2);

Vector2 operator + (const Vector2& value1, const Vector2& value2);
Vector2 operator - (const Vector2& value1, const Vector2& value2);
Vector2 operator * (const Vector2& value1, const Vector2& value2);
Vector2 operator / (const Vector2& value1, const Vector2& value2);

Vector2 operator + (const Vector2& value1, float value2);
Vector2 operator - (const Vector2& value1, float value2);
Vector2 operator * (const Vector2& value1, float value2);
Vector2 operator / (const Vector2& value1, float value2);
Vector2 operator + (float value1, const Vector2& value2);
Vector2 operator - (float value1, const Vector2& value2);
Vector2 operator * (float value1, const Vector2& value2);
Vector2 operator / (float value1, const Vector2& value2);

bool operator == (const Vector2& value1, const Vector2& value2);
bool operator != (const Vector2& value1, const Vector2& value2);

bool operator <  (const Vector2& value1, const Vector2& value2);
bool operator <= (const Vector2& value1, const Vector2& value2);
bool operator >  (const Vector2& value1, const Vector2& value2);
bool operator >= (const Vector2& value1, const Vector2& value2);

Vector2 operator - (const Vector2& value);

Vector2& operator ++ (Vector2& value);
Vector2& operator -- (Vector2& value);
Vector2  operator ++ (Vector2& value, int);
Vector2  operator -- (Vector2& value, int);

#endif // MATH_VECTOR2_H

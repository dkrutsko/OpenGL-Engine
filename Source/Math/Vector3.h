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

#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

class Matrix;
class Quaternion;
class Vector2;
class Vector4;

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Represents a vector with three components. </summary>

class Vector3
{
public:
	// Constants
	static const Vector3 One;		// Vector3 (1, 1, 1)
	static const Vector3 Zero;		// Vector3 (0, 0, 0)

	static const Vector3 UnitX;		// Vector3 (1, 0, 0)
	static const Vector3 UnitY;		// Vector3 (0, 1, 0)
	static const Vector3 UnitZ;		// Vector3 (0, 0, 1)

	static const Vector3 Up;		// Vector3 ( 0,  1,  0)
	static const Vector3 Down;		// Vector3 ( 0, -1,  0)
	static const Vector3 Right;		// Vector3 ( 1,  0,  0)
	static const Vector3 Left;		// Vector3 (-1,  0,  0)
	static const Vector3 Backward;	// Vector3 ( 0,  0,  1)
	static const Vector3 Forward;	// Vector3 ( 0,  0, -1)

public:
	// Constructors
	explicit Vector3				(void) { }
	explicit Vector3				(float x, float y, float z);

	explicit Vector3				(float value);
	explicit Vector3				(float value, float z);

	explicit Vector3				(const Vector2& value, float z = 0);
	explicit Vector3				(const Vector4& value);

public:
	// Methods
	float			Length			(void) const;
	float			LengthSquared	(void) const;
	void			Normalize		(void);

public:
	// Static
	static float	Dot				(const Vector3& value1, const Vector3& value2);
	static Vector3	Cross			(const Vector3& value1, const Vector3& value2);
	static Vector3	Min				(const Vector3& value1, const Vector3& value2);
	static Vector3	Max				(const Vector3& value1, const Vector3& value2);

	static float	Distance		(const Vector3& value1, const Vector3& value2);
	static float	DistanceSquared	(const Vector3& value1, const Vector3& value2);
	static Vector3	Normalize		(const Vector3& value);
		
	static Vector3	Clamp			(const Vector3& value, const Vector3& min, const Vector3& max);
	static Vector3	Reflect			(const Vector3& value, const Vector3& normal);

	static Vector3	Lerp			(const Vector3& value1, const Vector3& value2, float amount);
	static Vector3	SmoothStep		(const Vector3& value1, const Vector3& value2, float amount);
	static Vector3	Barycentric		(const Vector3& value1, const Vector3& value2, const Vector3& value3, float amount1, float amount2);
	static Vector3	CatmullRom		(const Vector3& value1, const Vector3& value2, const Vector3& value3, const Vector3& value4, float amount);
	static Vector3	Hermite			(const Vector3& value1, const Vector3& tangent1, const Vector3& value2, const Vector3& tangent2, float amount);

	static Vector3	Transform		(const Vector3& position, const Matrix& matrix);
	static Vector3	Transform		(const Vector3& position, const Quaternion& rotation);
	static Vector3	TransformNormal	(const Vector3& normal, const Matrix& matrix);

	static void		Transform		(quint32 length, const Vector3* source, const Matrix& matrix, Vector3* target);
	static void		Transform		(quint32 length, const Vector3* source, const Quaternion& rotation, Vector3* target);
	static void		TransformNormal	(quint32 length, const Vector3* source, const Matrix& matrix, Vector3* target);

	static void		Transform		(quint32 length, quint32 sourceIndex, const Vector3* source,
									 const Matrix& matrix, quint32 targetIndex, Vector3* target);

	static void		Transform		(quint32 length, quint32 sourceIndex, const Vector3* source,
									 const Quaternion& rotation, quint32 targetIndex, Vector3* target);

	static void		TransformNormal	(quint32 length, quint32 sourceIndex, const Vector3* source,
									 const Matrix& matrix, quint32 targetIndex, Vector3* target);

public:
	// Fields
	float X;		// X-component
	float Y;		// Y-component
	float Z;		// Z-component
};



//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//

Vector3& operator += (Vector3& value1, const Vector3& value2);
Vector3& operator -= (Vector3& value1, const Vector3& value2);
Vector3& operator *= (Vector3& value1, const Vector3& value2);
Vector3& operator /= (Vector3& value1, const Vector3& value2);

Vector3& operator += (Vector3& value1, float value2);
Vector3& operator -= (Vector3& value1, float value2);
Vector3& operator *= (Vector3& value1, float value2);
Vector3& operator /= (Vector3& value1, float value2);

Vector3 operator + (const Vector3& value1, const Vector3& value2);
Vector3 operator - (const Vector3& value1, const Vector3& value2);
Vector3 operator * (const Vector3& value1, const Vector3& value2);
Vector3 operator / (const Vector3& value1, const Vector3& value2);

Vector3 operator + (const Vector3& value1, float value2);
Vector3 operator - (const Vector3& value1, float value2);
Vector3 operator * (const Vector3& value1, float value2);
Vector3 operator / (const Vector3& value1, float value2);
Vector3 operator + (float value1, const Vector3& value2);
Vector3 operator - (float value1, const Vector3& value2);
Vector3 operator * (float value1, const Vector3& value2);
Vector3 operator / (float value1, const Vector3& value2);

bool operator == (const Vector3& value1, const Vector3& value2);
bool operator != (const Vector3& value1, const Vector3& value2);

bool operator <  (const Vector3& value1, const Vector3& value2);
bool operator <= (const Vector3& value1, const Vector3& value2);
bool operator >  (const Vector3& value1, const Vector3& value2);
bool operator >= (const Vector3& value1, const Vector3& value2);

Vector3 operator - (const Vector3& value);

Vector3& operator ++ (Vector3& value);
Vector3& operator -- (Vector3& value);
Vector3  operator ++ (Vector3& value, int);
Vector3  operator -- (Vector3& value, int);

#endif // MATH_VECTOR3_H

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

#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

class Plane;
class Quaternion;

#include "Math/Vector3.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Represents a matrix with four rows and columns. </summary>

class Matrix
{
public:
	// Constants
	static const Matrix One;					// Matrix with all ones
	static const Matrix Zero;					// Matrix with all zeros
	static const Matrix Identity;				// Identity Matrix

public:
	// Constructors
	explicit Matrix								(void) { }
	explicit Matrix								(float m11, float m12, float m13, float m14,
												 float m21, float m22, float m23, float m24,
												 float m31, float m32, float m33, float m34,
												 float m41, float m42, float m43, float m44);

public:
	// Methods
	Vector3		GetUp							(void) const { return Vector3 ( M21,  M22,  M23); }
	Vector3		GetDown							(void) const { return Vector3 (-M21, -M22, -M23); }
	Vector3		GetRight						(void) const { return Vector3 ( M11,  M12,  M13); }
	Vector3		GetLeft							(void) const { return Vector3 (-M11, -M12, -M13); }

	Vector3		GetTranslation					(void) const { return Vector3 ( M41,  M42,  M43); }
	Vector3		GetForward						(void) const { return Vector3 (-M31, -M32, -M33); }
	Vector3		GetBackward						(void) const { return Vector3 ( M31,  M32,  M33); }

	void		SetUp							(const Vector3& value) { M21 =  value.X; M22 =  value.Y; M23 =  value.Z; }
	void		SetDown							(const Vector3& value) { M21 = -value.X; M22 = -value.Y; M23 = -value.Z; }
	void		SetRight						(const Vector3& value) { M11 =  value.X; M12 =  value.Y; M13 =  value.Z; }
	void		SetLeft							(const Vector3& value) { M11 = -value.X; M12 = -value.Y; M13 = -value.Z; }

	void		SetTranslation					(const Vector3& value) { M41 =  value.X; M42 =  value.Y; M43 =  value.Z; }
	void		SetForward						(const Vector3& value) { M31 = -value.X; M32 = -value.Y; M33 = -value.Z; }
	void		SetBackward						(const Vector3& value) { M31 =  value.X; M32 =  value.Y; M33 =  value.Z; }
	
	float		Determinant						(void) const;
	bool		Decompose						(Vector3& scale, Quaternion& rotation, Vector3& translation) const;

public:
	// Static
	static Matrix Invert						(const Matrix& value);
	static Matrix Transpose						(const Matrix& value);
	static Matrix Transform						(const Matrix& value, const Quaternion& rotation);
	static Matrix Lerp							(const Matrix& source, const Matrix& target, float amount);

	static Matrix CreateScale					(float scale);
	static Matrix CreateScale					(float x, float y, float z);
	static Matrix CreateScale					(const Vector3& scale);

	static Matrix CreateRotationX				(float angle);
	static Matrix CreateRotationY				(float angle);
	static Matrix CreateRotationZ				(float angle);

	static Matrix CreateTranslation				(float x, float y, float z);
	static Matrix CreateTranslation				(const Vector3& position);

	static Matrix CreateFromAxisAngle			(const Vector3& axis, float angle);
	static Matrix CreateFromYawPitchRoll		(float yaw, float pitch, float roll);
	static Matrix CreateFromQuaternion			(const Quaternion& rotation);

	static Matrix CreateReflection				(const Plane& plane);
	static Matrix CreateShadow					(const Vector3& lightDirection, const Plane& plane);

	static Matrix CreateWorld					(const Vector3& position, const Vector3& forward, const Vector3& up);
	static Matrix CreateLookAt					(const Vector3& position, const Vector3& target,  const Vector3& up);

	static Matrix CreatePerspective				(float width, float height,
												 float nearPlaneDistance, float farPlaneDistance);

	static Matrix CreatePerspectiveFieldOfView	(float fieldOfView, float aspectRatio,
												 float nearPlaneDistance, float farPlaneDistance);

	static Matrix CreatePerspectiveOffCenter	(float left, float right, float bottom, float top,
												 float nearPlaneDistance, float farPlaneDistance);

	static Matrix CreateOrthographic			(float width, float height,
												 float zNearPlane, float zFarPlane);

	static Matrix CreateOrthographicOffCenter	(float left, float right, float bottom,
												 float top, float zNearPlane, float zFarPlane);

public:
	// Fields
	float M11, M12, M13, M14;					// First row
	float M21, M22, M23, M24;					// Second row
	float M31, M32, M33, M34;					// Third row
	float M41, M42, M43, M44;					// Fourth row
};



//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//

Matrix& operator += (Matrix& value1, const Matrix& value2);
Matrix& operator -= (Matrix& value1, const Matrix& value2);
Matrix& operator *= (Matrix& value1, const Matrix& value2);
Matrix& operator *= (Matrix& value, float scalar);
Matrix& operator /= (Matrix& value1, const Matrix& value2);
Matrix& operator /= (Matrix& value, float divider);

Matrix operator + (const Matrix& value1, const Matrix& value2);
Matrix operator - (const Matrix& value1, const Matrix& value2);
Matrix operator * (const Matrix& value1, const Matrix& value2);
Matrix operator * (const Matrix& value, float scalar);
Matrix operator * (float scalar, const Matrix& value);
Matrix operator / (const Matrix& value1, const Matrix& value2);
Matrix operator / (const Matrix& value, float divider);

bool operator == (const Matrix& value1, const Matrix& value2);
bool operator != (const Matrix& value1, const Matrix& value2);

Matrix operator - (const Matrix& value);

#endif // MATH_MATRIX_H

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
#include "Math/Matrix.h"
#include "Math/Plane.h"
#include "Math/Quaternion.h"



//----------------------------------------------------------------------------//
// Constants                                                           Matrix //
//----------------------------------------------------------------------------//

const Matrix Matrix::One		= Matrix (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
const Matrix Matrix::Zero		= Matrix (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
const Matrix Matrix::Identity	= Matrix (1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);



//----------------------------------------------------------------------------//
// Constructors                                                        Matrix //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <remarks> Arguments correspond to the components of the matrix. </remarks>

Matrix::Matrix (float m11, float m12, float m13, float m14,
				float m21, float m22, float m23, float m24,
				float m31, float m32, float m33, float m34,
				float m41, float m42, float m43, float m44)
{
	M11 = m11; M21 = m21; M31 = m31; M41 = m41;
	M12 = m12; M22 = m22; M32 = m32; M42 = m42;
	M13 = m13; M23 = m23; M33 = m33; M43 = m43;
	M14 = m14; M24 = m24; M34 = m34; M44 = m44;
}



//----------------------------------------------------------------------------//
// Methods                                                             Matrix //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the determinant of this matrix. </summary>
	
float Matrix::Determinant (void) const
{
	float v1 = (M33 * M44) - (M34 * M43);
	float v2 = (M32 * M44) - (M34 * M42);
	float v3 = (M32 * M43) - (M33 * M42);
	float v4 = (M31 * M44) - (M34 * M41);
	float v5 = (M31 * M43) - (M33 * M41);
	float v6 = (M31 * M42) - (M32 * M41);

	return (M11 * ((M22 * v1) - (M23 * v2) + (M24 * v3))) -
		   (M12 * ((M21 * v1) - (M23 * v4) + (M24 * v5))) +
		   (M13 * ((M21 * v2) - (M22 * v4) + (M24 * v6))) -
		   (M14 * ((M21 * v3) - (M22 * v5) + (M23 * v6)));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Extracts the scalar, translation and rotation components of this matrix. 
/// </summary>
/// <returns> True if the Matrix can be decomposed. </returns>

bool Matrix::Decompose (Vector3& scale, Quaternion& rotation, Vector3& translation) const
{
/* NOT YET IMPLEMENTED

	// Scale
	float xs = (M11 * M12 * M13 * M14) < 0 ? -1.0f : 1.0f;
	float ys = (M21 * M22 * M23 * M24) < 0 ? -1.0f : 1.0f;
	float zs = (M31 * M32 * M33 * M34) < 0 ? -1.0f : 1.0f;

	scale.X = xs * Math::Sqrt (M11 * M11 + M12 * M12 + M13 * M13);
	scale.Y = ys * Math::Sqrt (M21 * M21 + M22 * M22 + M23 * M23);
	scale.Z = zs * Math::Sqrt (M31 * M31 + M32 * M32 + M33 * M33);

	if (scale.X == 0.0 || scale.Y == 0.0 || scale.Z == 0.0)
		return false;
	
	// Rotation
	Matrix matrix = Matrix
		(M11 / scale.X, M12 / scale.X, M13 / scale.X, 0,
		 M21 / scale.Y, M22 / scale.Y, M23 / scale.Y, 0,
		 M31 / scale.Z, M32 / scale.Z, M33 / scale.Z, 0, 0, 0, 0, 1);

	rotation = Quaternion::CreateFromRotationMatrix (matrix);

	// Translation
	translation.X = M41;
	translation.Y = M42;
	translation.Z = M43;

	return true;

*/
	return false;
}



//----------------------------------------------------------------------------//
// Static                                                              Matrix //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the inverse of a matrix. </summary>

Matrix Matrix::Invert (const Matrix& value)
{
	float det1  = value.M11 * value.M22 - value.M12 * value.M21;
	float det2  = value.M11 * value.M23 - value.M13 * value.M21;
	float det3  = value.M11 * value.M24 - value.M14 * value.M21;
	float det4  = value.M12 * value.M23 - value.M13 * value.M22;
	float det5  = value.M12 * value.M24 - value.M14 * value.M22;
	float det6  = value.M13 * value.M24 - value.M14 * value.M23;
	float det7  = value.M31 * value.M42 - value.M32 * value.M41;
	float det8  = value.M31 * value.M43 - value.M33 * value.M41;
	float det9  = value.M31 * value.M44 - value.M34 * value.M41;
	float det10 = value.M32 * value.M43 - value.M33 * value.M42;
	float det11 = value.M32 * value.M44 - value.M34 * value.M42;
	float det12 = value.M33 * value.M44 - value.M34 * value.M43;

	float det = 1 / ((det1 * det12) - (det2 * det11) +
					 (det3 * det10) + (det4 * det9 ) -
					 (det5 * det8 ) + (det6 * det7 ));

	return Matrix (( value.M22 * det12 - value.M23 * det11 + value.M24 * det10) * det,
				   (-value.M12 * det12 + value.M13 * det11 - value.M14 * det10) * det,
				   ( value.M42 * det6  - value.M43 * det5  + value.M44 * det4 ) * det,
				   (-value.M32 * det6  + value.M33 * det5  - value.M34 * det4 ) * det,
				   (-value.M21 * det12 + value.M23 * det9  - value.M24 * det8 ) * det,
				   ( value.M11 * det12 - value.M13 * det9  + value.M14 * det8 ) * det,
				   (-value.M41 * det6  + value.M43 * det3  - value.M44 * det2 ) * det,
				   ( value.M31 * det6  - value.M33 * det3  + value.M34 * det2 ) * det,
				   ( value.M21 * det11 - value.M22 * det9  + value.M24 * det7 ) * det,
				   (-value.M11 * det11 + value.M12 * det9  - value.M14 * det7 ) * det,
				   ( value.M41 * det5  - value.M42 * det3  + value.M44 * det1 ) * det,
				   (-value.M31 * det5  + value.M32 * det3  - value.M34 * det1 ) * det,
				   (-value.M21 * det10 + value.M22 * det8  - value.M23 * det7 ) * det,
				   ( value.M11 * det10 - value.M12 * det8  + value.M13 * det7 ) * det,
				   (-value.M41 * det4  + value.M42 * det2  - value.M43 * det1 ) * det,
				   ( value.M31 * det4  - value.M32 * det2  + value.M33 * det1 ) * det);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transposes the rows and columns of a matrix. </summary>

Matrix Matrix::Transpose (const Matrix& value)
{
	return Matrix (value.M11, value.M21, value.M31, value.M41,
				   value.M12, value.M22, value.M32, value.M42,
				   value.M13, value.M23, value.M33, value.M43,
				   value.M14, value.M24, value.M34, value.M44);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Matrix by applying a Quaternion rotation. </summary>
/// <param name="value"> The Matrix to transform. </param>
/// <param name="rotation"> The rotation to apply. </param>

Matrix Matrix::Transform (const Matrix& value, const Quaternion& rotation)
{
	return value * CreateFromQuaternion (rotation);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Linearly interpolates between the corresponding values of two matrices.
/// </summary>
/// <param name="amount"> How far to interpolate between the values. </param>

Matrix Matrix::Lerp (const Matrix& source, const Matrix& target, float amount)
{
	return Matrix
	(
		source.M11 + ((target.M11 - source.M11) * amount),
		source.M12 + ((target.M12 - source.M12) * amount),
		source.M13 + ((target.M13 - source.M13) * amount),
		source.M14 + ((target.M14 - source.M14) * amount),

		source.M21 + ((target.M21 - source.M21) * amount),
		source.M22 + ((target.M22 - source.M22) * amount),
		source.M23 + ((target.M23 - source.M23) * amount),
		source.M24 + ((target.M24 - source.M24) * amount),

		source.M31 + ((target.M31 - source.M31) * amount),
		source.M32 + ((target.M32 - source.M32) * amount),
		source.M33 + ((target.M33 - source.M33) * amount),
		source.M34 + ((target.M34 - source.M34) * amount),

		source.M41 + ((target.M41 - source.M41) * amount),
		source.M42 + ((target.M42 - source.M42) * amount),
		source.M43 + ((target.M43 - source.M43) * amount),
		source.M44 + ((target.M44 - source.M44) * amount)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a scaling Matrix. </summary>
/// <param name="scale"> Amount to scale by. </param>

Matrix Matrix::CreateScale (float scale)
{
	return Matrix (scale,     0,     0, 0,
				       0, scale,     0, 0,
				       0,     0, scale, 0,
				       0,     0,     0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a scaling Matrix. </summary>
/// <param name="x"> Value to scale by on the x-axis. </param>
/// <param name="y"> Value to scale by on the y-axis. </param>
/// <param name="z"> Value to scale by on the z-axis. </param>

Matrix Matrix::CreateScale (float x, float y, float z)
{
	return Matrix (x, 0, 0, 0,
				   0, y, 0, 0,
				   0, 0, z, 0,
				   0, 0, 0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a scaling Matrix. </summary>
/// <param name="scale"> Amounts to scale by on the x, y, and z axes. </param>

Matrix Matrix::CreateScale (const Vector3& scale)
{
	return Matrix (scale.X,       0,       0, 0,
				         0, scale.Y,       0, 0,
				         0,       0, scale.Z, 0,
				         0,       0,       0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a rotation matrix around the x-axis. </summary>
/// <param name="angle">
/// The amount, in radians, in which to rotate around the x-axis.
/// </param>

Matrix Matrix::CreateRotationX (float angle)
{
	float sin = Math::Sinr (angle);
	float cos = Math::Cosr (angle);

	return Matrix (1,   0,    0, 0,
				   0,  cos, sin, 0,
				   0, -sin, cos, 0,
				   0,    0,   0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a rotation matrix around the y-axis. </summary>
/// <param name="angle">
/// The amount, in radians, in which to rotate around the y-axis.
/// </param>

Matrix Matrix::CreateRotationY (float angle)
{
	float sin = Math::Sinr (angle);
	float cos = Math::Cosr (angle);

	return Matrix (cos, 0, -sin, 0,
				     0, 1,    0, 0,
				   sin, 0,  cos, 0,
				     0, 0,    0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a rotation matrix around the z-axis. </summary>
/// <param name="angle">
/// The amount, in radians, in which to rotate around the z-axis.
/// </param>

Matrix Matrix::CreateRotationZ (float angle)
{
	float sin = Math::Sinr (angle);
	float cos = Math::Cosr (angle);

	return Matrix ( cos, sin, 0, 0,
				   -sin, cos, 0, 0,
				      0,   0, 1, 0,
				      0,   0, 0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a translation Matrix. </summary>
/// <param name="x"> Value to translate by on the x-axis. </param>
/// <param name="y"> Value to translate by on the y-axis. </param>
/// <param name="z"> Value to translate by on the z-axis. </param>

Matrix Matrix::CreateTranslation (float x, float y, float z)
{
	return Matrix (1, 0, 0, x,
				   0, 1, 0, y,
				   0, 0, 1, z,
				   0, 0, 0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a translation Matrix. </summary>
/// <param name="position"> Amounts to translate by on the x, y, and z axes. </param>

Matrix Matrix::CreateTranslation (const Vector3& position)
{
	return Matrix (1, 0, 0, position.X,
				   0, 1, 0, position.Y,
				   0, 0, 1, position.Z,
				   0, 0, 0, 1);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Creates a new Matrix that rotates around an arbitrary vector.
/// </summary>
/// <param name="axis"> The axis to rotate around. </param>
/// <param name="angle"> The angle to rotate around the vector. </param>

Matrix Matrix::CreateFromAxisAngle (const Vector3& axis, float angle)
{
	float sin = Math::Sinr (angle);
	float cos = Math::Cosr (angle);

	float xx = axis.X * axis.X;
	float yy = axis.Y * axis.Y;
	float zz = axis.Z * axis.Z;
	float xy = axis.X * axis.Y;
	float xz = axis.X * axis.Z;
	float yz = axis.Y * axis.Z;

	return Matrix
	(
		xx + (cos * (1 - xx)),
		xy - (cos * xy) + (sin * axis.Z),
		xz - (cos * xz) - (sin * axis.Y), 0,

		xy - (cos * xy) - (sin * axis.Z),
		yy + (cos * (1 - yy)),
		yz - (cos * yz) + (sin * axis.X), 0,
		
		xz - (cos * xz) + (sin * axis.Y),
		yz - (cos * yz) - (sin * axis.X),
		zz + (cos * (1 - zz)), 0,
		
		0, 0, 0, 1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Creates a new rotation matrix from a specified pitch, yaw and roll.
/// </summary>
/// <param name="yaw">   Angle of rotation, in radians, around the y-axis. </param>
/// <param name="pitch"> Angle of rotation, in radians, around the x-axis. </param>
/// <param name="roll">  Angle of rotation, in radians, around the z-axis. </param>

Matrix Matrix::CreateFromYawPitchRoll (float yaw, float pitch, float roll)
{
	return CreateFromQuaternion (Quaternion::CreateFromYawPitchRoll (yaw, pitch, roll));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a rotation Matrix from a Quaternion. </summary>

Matrix Matrix::CreateFromQuaternion (const Quaternion &rotation)
{
	return Matrix
	(
		1 - 2 * (rotation.Y * rotation.Y + rotation.Z * rotation.Z),
		    2 * (rotation.X * rotation.Y + rotation.W * rotation.Z),
		    2 * (rotation.X * rotation.Z - rotation.W * rotation.Y), 0,

		    2 * (rotation.X * rotation.Y - rotation.W * rotation.Z),
		1 - 2 * (rotation.X * rotation.X + rotation.Z * rotation.Z),
		    2 * (rotation.Y * rotation.Z + rotation.W * rotation.X), 0,

		    2 * (rotation.X * rotation.Z + rotation.W * rotation.Y),
		    2 * (rotation.Y * rotation.Z - rotation.W * rotation.X),
		1 - 2 * (rotation.X * rotation.X + rotation.Y * rotation.Y), 0,
		
		0, 0, 0, 1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Creates a Matrix that reflects the coordinate system about a specified Plane.
/// </summary>

Matrix Matrix::CreateReflection (const Plane& plane)
{
	Plane normalized = Plane::Normalize (plane);

	float xx = -2 * normalized.Normal.X;
	float yy = -2 * normalized.Normal.Y;
	float zz = -2 * normalized.Normal.Z;

	return Matrix
	(
		xx * normalized.Normal.X + 1,
		yy * normalized.Normal.X,
		zz * normalized.Normal.X,
		0,

		xx * normalized.Normal.Y,
		yy * normalized.Normal.Y + 1,
		zz * normalized.Normal.Y,
		0,

		xx * normalized.Normal.Z,
		yy * normalized.Normal.Z,
		zz * normalized.Normal.Z + 1,
		0,

		xx * normalized.Distance,
		yy * normalized.Distance,
		zz * normalized.Distance,
		1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a Matrix that flattens geometry into a specified Plane
/// 		  as if casting a shadow from a specified light source. </summary>
/// 
/// <param name="lightDirection"> A Vector3 specifying the direction from which
/// 							  the light that will cast the shadow is coming. </param>
/// 
/// <param name="plane"> The Plane onto which the new matrix should
/// 					 flatten geometry so as to cast a shadow. </param>

Matrix Matrix::CreateShadow (const Vector3& lightDirection, const Plane& plane)
{
	Plane normalized = Plane::Normalize (plane);

	float dot = (normalized.Normal.X * lightDirection.X) +
				(normalized.Normal.Y * lightDirection.Y) +
				(normalized.Normal.Z * lightDirection.Z);

	float x = -normalized.Normal.X;
	float y = -normalized.Normal.Y;
	float z = -normalized.Normal.Z;
	float d = -normalized.Distance;

	return Matrix
	(
		x * lightDirection.X + dot,
		y * lightDirection.X,
		z * lightDirection.X,
		d * lightDirection.X,

		x * lightDirection.Y,
		y * lightDirection.Y + dot,
		z * lightDirection.Y,
		d * lightDirection.Y,

		x * lightDirection.Z,
		y * lightDirection.Z,
		z * lightDirection.Z + dot,
		d * lightDirection.Z,

		0, 0, 0, dot
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a world matrix using the specified parameters. </summary>
/// 
/// <param name="position">	Position of the object. This value is
/// 						used in translation operations. </param>
/// <param name="forward">	Forward direction of the object. </param>
/// <param name="up">		Upward direction of the object. </param>
/// 
/// <remarks> The up vector is usually Vector3::Up (0, 1, 0). </remarks>

Matrix Matrix::CreateWorld (const Vector3& position,
	const Vector3& forward, const Vector3& up)
{
	Vector3 vz = Vector3::Normalize (-forward);
	Vector3 vx = Vector3::Normalize (Vector3::Cross (up, vz));
	Vector3 vy = Vector3::Cross (vz, vx);

	return Matrix
	(
		vx.X, vx.Y, vx.Z, position.X,
		vy.X, vy.Y, vy.Z, position.Y,
		vz.X, vz.Y, vz.Z, position.Z,
		0, 0, 0, 1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a view matrix using the specified parameters. </summary>
/// 
/// <param name="position">	Position of the camera. </param>
/// <param name="target">	Target which the camera is pointing at. </param>
/// <param name="up">		Upward direction of the camera. </param>

Matrix Matrix::CreateLookAt (const Vector3& position,
	const Vector3& target, const Vector3& up)
{
	Vector3 vz = Vector3::Normalize (position - target);
	Vector3 vx = Vector3::Normalize (Vector3::Cross (up, vz));
	Vector3 vy = Vector3::Cross (vz, vx);

	return Matrix
	(
		vx.X, vy.X, vz.X, -Vector3::Dot (vx, position),
		vx.Y, vy.Y, vz.Y, -Vector3::Dot (vy, position),
		vx.Z, vy.Z, vz.Z, -Vector3::Dot (vz, position),
		0, 0, 0, 1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Builds a perspective projection matrix. </summary>
/// 
/// <param name="width">  Width  of the view volume at the near view plane. </param>
/// <param name="height"> Height of the view volume at the near view plane. </param>
/// 
/// <param name="nearPlaneDistance"> Distance to the near view plane. </param>
/// <param name="farPlaneDistance">  Distance to the far  view plane. </param>

Matrix Matrix::CreatePerspective (float width, float height,
	float nearPlaneDistance, float farPlaneDistance)
{
	if (nearPlaneDistance <= 0 ||
		farPlaneDistance  <= 0 ||
		nearPlaneDistance >= farPlaneDistance)
		return Matrix::Identity;

	float d = nearPlaneDistance - farPlaneDistance;

	return Matrix
	(
		(2 * nearPlaneDistance) /  width, 0, 0, 0, 0,
		(2 * nearPlaneDistance) / height, 0, 0, 0, 0,

		farPlaneDistance / d, -1, 0, 0,
		(nearPlaneDistance * farPlaneDistance) / d, 0
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Builds a perspective projection matrix based on a field of view.
/// </summary>
/// <param name="fieldOfView"> Field of view in the y direction, in radians. </param>
/// <param name="aspectRatio"> Aspect ratio as (Width / Height). </param>
/// 
/// <param name="nearPlaneDistance"> Distance to the near view plane. </param>
/// <param name="farPlaneDistance">  Distance to the far  view plane. </param>

Matrix Matrix::CreatePerspectiveFieldOfView (float fieldOfView,
	float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
    if (fieldOfView <= 0 ||
		fieldOfView >= Math::Pi)
		return Matrix::Identity;

	if (nearPlaneDistance <= 0 ||
		farPlaneDistance  <= 0 ||
		nearPlaneDistance >= farPlaneDistance)
		return Matrix::Identity;

	float d = nearPlaneDistance - farPlaneDistance;
	float cot = 1 / Math::Tanr (fieldOfView * 0.5f);
    float asp = cot / aspectRatio;

	return Matrix
	(
		asp,   0,  0, 0,
		  0, cot,  0, 0,
		  0,   0, (nearPlaneDistance + farPlaneDistance) / d, (2 * nearPlaneDistance * farPlaneDistance) / d,
		  0,   0, -1, 0
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Builds a customized, perspective projection matrix. </summary>
/// 
/// <param name="left">   Minimum x-value of the view volume at the near view plane. </param>
/// <param name="right">  Maximum x-value of the view volume at the near view plane. </param>
/// <param name="bottom"> Minimum y-value of the view volume at the near view plane. </param>
/// <param name="top">    Maximum y-value of the view volume at the near view plane. </param>
/// 
/// <param name="nearPlaneDistance"> Distance to the near view plane. </param>
/// <param name="farPlaneDistance">  Distance to the far  view plane. </param>

Matrix Matrix::CreatePerspectiveOffCenter (float left, float right,
	float bottom, float top, float nearPlaneDistance, float farPlaneDistance)
{
	if (nearPlaneDistance <= 0 ||
		farPlaneDistance  <= 0 ||
		nearPlaneDistance >= farPlaneDistance)
		return Matrix::Identity;

	float d = nearPlaneDistance - farPlaneDistance;

	return Matrix
	(
		(2 * nearPlaneDistance) / (right - left), 0, 0, 0, 0,
		(2 * nearPlaneDistance) / (top - bottom), 0, 0,

		(left + right) / (right - left),
		(top + bottom) / (top - bottom),
		farPlaneDistance / d, -1, 0, 0,

		(nearPlaneDistance * farPlaneDistance) / d, 0
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Builds an orthogonal projection matrix. </summary>
/// 
/// <param name="width">  Width  of the view volume. </param>
/// <param name="height"> Height of the view volume. </param>
/// 
/// <param name="zNearPlane"> Minimum z-value of the view volume. </param>
/// <param name="zFarPlane">  Maximum z-value of the view volume. </param>

Matrix Matrix::CreateOrthographic (float width,
	float height, float zNearPlane, float zFarPlane)
{
	float d = zNearPlane - zFarPlane;

	return Matrix
	(
		2 / width,  0, 0, 0, 0,
		2 / height, 0, 0, 0, 0,
		1 / d, 0, 0, 0,
		zNearPlane / d, 1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Builds a customized, orthogonal projection matrix. </summary>
/// 
/// <param name="left">   Minimum x-value of the view volume. </param>
/// <param name="right">  Maximum x-value of the view volume. </param>
/// <param name="bottom"> Minimum y-value of the view volume. </param>
/// <param name="top">    Maximum y-value of the view volume. </param>
/// 
/// <param name="zNearPlane"> Minimum z-value of the view volume. </param>
/// <param name="zFarPlane">  Maximum z-value of the view volume. </param>

Matrix Matrix::CreateOrthographicOffCenter (float left, float right,
	float bottom, float top, float zNearPlane, float zFarPlane)
{
	float d = zNearPlane - zFarPlane;

	return Matrix
	(
		2 / (right - left), 0, 0, 0, 0,
		2 / (top - bottom), 0, 0, 0, 0,
		1 / d, 0,

		(left + right) / (left - right),
		(top + bottom) / (bottom - top),
		zNearPlane / d, 1
	);
}



//----------------------------------------------------------------------------//
// Operators                                                           Matrix //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one matrix to another. </summary>

Matrix& operator += (Matrix& value1, const Matrix& value2)
{
	value1.M11 += value2.M11;
	value1.M12 += value2.M12;
	value1.M13 += value2.M13;
	value1.M14 += value2.M14;

	value1.M21 += value2.M21;
	value1.M22 += value2.M22;
	value1.M23 += value2.M23;
	value1.M24 += value2.M24;

	value1.M31 += value2.M31;
	value1.M32 += value2.M32;
	value1.M33 += value2.M33;
	value1.M34 += value2.M34;

	value1.M41 += value2.M41;
	value1.M42 += value2.M42;
	value1.M43 += value2.M43;
	value1.M44 += value2.M44;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one matrix from another. </summary>

Matrix& operator -= (Matrix& value1, const Matrix& value2)
{
	value1.M11 -= value2.M11;
	value1.M12 -= value2.M12;
	value1.M13 -= value2.M13;
	value1.M14 -= value2.M14;

	value1.M21 -= value2.M21;
	value1.M22 -= value2.M22;
	value1.M23 -= value2.M23;
	value1.M24 -= value2.M24;

	value1.M31 -= value2.M31;
	value1.M32 -= value2.M32;
	value1.M33 -= value2.M33;
	value1.M34 -= value2.M34;

	value1.M41 -= value2.M41;
	value1.M42 -= value2.M42;
	value1.M43 -= value2.M43;
	value1.M44 -= value2.M44;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies one matrix by another. </summary>

Matrix& operator *= (Matrix& value1, const Matrix& value2)
{
	value1 = Matrix
	(
		(value1.M11 * value2.M11) + (value1.M12 * value2.M21) + (value1.M13 * value2.M31) + (value1.M14 * value2.M41),
		(value1.M11 * value2.M12) + (value1.M12 * value2.M22) + (value1.M13 * value2.M32) + (value1.M14 * value2.M42),
		(value1.M11 * value2.M13) + (value1.M12 * value2.M23) + (value1.M13 * value2.M33) + (value1.M14 * value2.M43),
		(value1.M11 * value2.M14) + (value1.M12 * value2.M24) + (value1.M13 * value2.M34) + (value1.M14 * value2.M44),

		(value1.M21 * value2.M11) + (value1.M22 * value2.M21) + (value1.M23 * value2.M31) + (value1.M24 * value2.M41),
		(value1.M21 * value2.M12) + (value1.M22 * value2.M22) + (value1.M23 * value2.M32) + (value1.M24 * value2.M42),
		(value1.M21 * value2.M13) + (value1.M22 * value2.M23) + (value1.M23 * value2.M33) + (value1.M24 * value2.M43),
		(value1.M21 * value2.M14) + (value1.M22 * value2.M24) + (value1.M23 * value2.M34) + (value1.M24 * value2.M44),

		(value1.M31 * value2.M11) + (value1.M32 * value2.M21) + (value1.M33 * value2.M31) + (value1.M34 * value2.M41),
		(value1.M31 * value2.M12) + (value1.M32 * value2.M22) + (value1.M33 * value2.M32) + (value1.M34 * value2.M42),
		(value1.M31 * value2.M13) + (value1.M32 * value2.M23) + (value1.M33 * value2.M33) + (value1.M34 * value2.M43),
		(value1.M31 * value2.M14) + (value1.M32 * value2.M24) + (value1.M33 * value2.M34) + (value1.M34 * value2.M44),

		(value1.M41 * value2.M11) + (value1.M42 * value2.M21) + (value1.M43 * value2.M31) + (value1.M44 * value2.M41),
		(value1.M41 * value2.M12) + (value1.M42 * value2.M22) + (value1.M43 * value2.M32) + (value1.M44 * value2.M42),
		(value1.M41 * value2.M13) + (value1.M42 * value2.M23) + (value1.M43 * value2.M33) + (value1.M44 * value2.M43),
		(value1.M41 * value2.M14) + (value1.M42 * value2.M24) + (value1.M43 * value2.M34) + (value1.M44 * value2.M44)
	);

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a matrix by a scalar. </summary>

Matrix& operator *= (Matrix& value, float scalar)
{
	value.M11 *= scalar;
	value.M12 *= scalar;
	value.M13 *= scalar;
	value.M14 *= scalar;

	value.M21 *= scalar;
	value.M22 *= scalar;
	value.M23 *= scalar;
	value.M24 *= scalar;

	value.M31 *= scalar;
	value.M32 *= scalar;
	value.M33 *= scalar;
	value.M34 *= scalar;

	value.M41 *= scalar;
	value.M42 *= scalar;
	value.M43 *= scalar;
	value.M44 *= scalar;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two matrices against each other. </summary>

Matrix& operator /= (Matrix& value1, const Matrix& value2)
{
	value1.M11 /= value2.M11;
	value1.M12 /= value2.M12;
	value1.M13 /= value2.M13;
	value1.M14 /= value2.M14;

	value1.M21 /= value2.M21;
	value1.M22 /= value2.M22;
	value1.M23 /= value2.M23;
	value1.M24 /= value2.M24;

	value1.M31 /= value2.M31;
	value1.M32 /= value2.M32;
	value1.M33 /= value2.M33;
	value1.M34 /= value2.M34;

	value1.M41 /= value2.M41;
	value1.M42 /= value2.M42;
	value1.M43 /= value2.M43;
	value1.M44 /= value2.M44;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a matrix by a scalar. </summary>

Matrix& operator /= (Matrix& value, float divider)
{
	divider = 1 / divider;

	value.M11 *= divider;
	value.M12 *= divider;
	value.M13 *= divider;
	value.M14 *= divider;

	value.M21 *= divider;
	value.M22 *= divider;
	value.M23 *= divider;
	value.M24 *= divider;

	value.M31 *= divider;
	value.M32 *= divider;
	value.M33 *= divider;
	value.M34 *= divider;

	value.M41 *= divider;
	value.M42 *= divider;
	value.M43 *= divider;
	value.M44 *= divider;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one matrix to another. </summary>

Matrix operator + (const Matrix& value1, const Matrix& value2)
{
	return Matrix
	(
		value1.M11 + value2.M11,
		value1.M12 + value2.M12,
		value1.M13 + value2.M13,
		value1.M14 + value2.M14,

		value1.M21 + value2.M21,
		value1.M22 + value2.M22,
		value1.M23 + value2.M23,
		value1.M24 + value2.M24,

		value1.M31 + value2.M31,
		value1.M32 + value2.M32,
		value1.M33 + value2.M33,
		value1.M34 + value2.M34,

		value1.M41 + value2.M41,
		value1.M42 + value2.M42,
		value1.M43 + value2.M43,
		value1.M44 + value2.M44
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one matrix from another. </summary>

Matrix operator - (const Matrix& value1, const Matrix& value2)
{
	return Matrix
	(
		value1.M11 - value2.M11,
		value1.M12 - value2.M12,
		value1.M13 - value2.M13,
		value1.M14 - value2.M14,

		value1.M21 - value2.M21,
		value1.M22 - value2.M22,
		value1.M23 - value2.M23,
		value1.M24 - value2.M24,

		value1.M31 - value2.M31,
		value1.M32 - value2.M32,
		value1.M33 - value2.M33,
		value1.M34 - value2.M34,

		value1.M41 - value2.M41,
		value1.M42 - value2.M42,
		value1.M43 - value2.M43,
		value1.M44 - value2.M44
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies one matrix by another. </summary>

Matrix operator * (const Matrix& value1, const Matrix& value2)
{
	return Matrix
	(
		(value1.M11 * value2.M11) + (value1.M12 * value2.M21) + (value1.M13 * value2.M31) + (value1.M14 * value2.M41),
		(value1.M11 * value2.M12) + (value1.M12 * value2.M22) + (value1.M13 * value2.M32) + (value1.M14 * value2.M42),
		(value1.M11 * value2.M13) + (value1.M12 * value2.M23) + (value1.M13 * value2.M33) + (value1.M14 * value2.M43),
		(value1.M11 * value2.M14) + (value1.M12 * value2.M24) + (value1.M13 * value2.M34) + (value1.M14 * value2.M44),

		(value1.M21 * value2.M11) + (value1.M22 * value2.M21) + (value1.M23 * value2.M31) + (value1.M24 * value2.M41),
		(value1.M21 * value2.M12) + (value1.M22 * value2.M22) + (value1.M23 * value2.M32) + (value1.M24 * value2.M42),
		(value1.M21 * value2.M13) + (value1.M22 * value2.M23) + (value1.M23 * value2.M33) + (value1.M24 * value2.M43),
		(value1.M21 * value2.M14) + (value1.M22 * value2.M24) + (value1.M23 * value2.M34) + (value1.M24 * value2.M44),

		(value1.M31 * value2.M11) + (value1.M32 * value2.M21) + (value1.M33 * value2.M31) + (value1.M34 * value2.M41),
		(value1.M31 * value2.M12) + (value1.M32 * value2.M22) + (value1.M33 * value2.M32) + (value1.M34 * value2.M42),
		(value1.M31 * value2.M13) + (value1.M32 * value2.M23) + (value1.M33 * value2.M33) + (value1.M34 * value2.M43),
		(value1.M31 * value2.M14) + (value1.M32 * value2.M24) + (value1.M33 * value2.M34) + (value1.M34 * value2.M44),

		(value1.M41 * value2.M11) + (value1.M42 * value2.M21) + (value1.M43 * value2.M31) + (value1.M44 * value2.M41),
		(value1.M41 * value2.M12) + (value1.M42 * value2.M22) + (value1.M43 * value2.M32) + (value1.M44 * value2.M42),
		(value1.M41 * value2.M13) + (value1.M42 * value2.M23) + (value1.M43 * value2.M33) + (value1.M44 * value2.M43),
		(value1.M41 * value2.M14) + (value1.M42 * value2.M24) + (value1.M43 * value2.M34) + (value1.M44 * value2.M44)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a matrix by a scalar. </summary>

Matrix operator * (const Matrix& value, float scalar)
{
	return Matrix
	(
		value.M11 * scalar,
		value.M12 * scalar,
		value.M13 * scalar,
		value.M14 * scalar,

		value.M21 * scalar,
		value.M22 * scalar,
		value.M23 * scalar,
		value.M24 * scalar,

		value.M31 * scalar,
		value.M32 * scalar,
		value.M33 * scalar,
		value.M34 * scalar,

		value.M41 * scalar,
		value.M42 * scalar,
		value.M43 * scalar,
		value.M44 * scalar
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a matrix by a scalar. </summary>

Matrix operator * (float scalar, const Matrix& value)
{
	return Matrix
	(
		scalar * value.M11,
		scalar * value.M12,
		scalar * value.M13,
		scalar * value.M14,

		scalar * value.M21,
		scalar * value.M22,
		scalar * value.M23,
		scalar * value.M24,

		scalar * value.M31,
		scalar * value.M32,
		scalar * value.M33,
		scalar * value.M34,

		scalar * value.M41,
		scalar * value.M42,
		scalar * value.M43,
		scalar * value.M44
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two matrices against each other. </summary>

Matrix operator / (const Matrix& value1, const Matrix& value2)
{
	return Matrix
	(
		value1.M11 / value2.M11,
		value1.M12 / value2.M12,
		value1.M13 / value2.M13,
		value1.M14 / value2.M14,

		value1.M21 / value2.M21,
		value1.M22 / value2.M22,
		value1.M23 / value2.M23,
		value1.M24 / value2.M24,

		value1.M31 / value2.M31,
		value1.M32 / value2.M32,
		value1.M33 / value2.M33,
		value1.M34 / value2.M34,

		value1.M41 / value2.M41,
		value1.M42 / value2.M42,
		value1.M43 / value2.M43,
		value1.M44 / value2.M44
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a matrix by a scalar. </summary>

Matrix operator / (const Matrix& value, float divider)
{
	divider = 1 / divider;
	return Matrix
	(
		value.M11 * divider,
		value.M12 * divider,
		value.M13 * divider,
		value.M14 * divider,

		value.M21 * divider,
		value.M22 * divider,
		value.M23 * divider,
		value.M24 * divider,

		value.M31 * divider,
		value.M32 * divider,
		value.M33 * divider,
		value.M34 * divider,

		value.M41 * divider,
		value.M42 * divider,
		value.M43 * divider,
		value.M44 * divider
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two matrices for equality. </summary>

bool operator == (const Matrix& value1, const Matrix& value2)
{
	return value1.M11 == value2.M11 &&
		   value1.M12 == value2.M12 &&
		   value1.M13 == value2.M13 &&
		   value1.M14 == value2.M14 &&

		   value1.M21 == value2.M21 &&
		   value1.M22 == value2.M22 &&
		   value1.M23 == value2.M23 &&
		   value1.M24 == value2.M24 &&

		   value1.M31 == value2.M31 &&
		   value1.M32 == value2.M32 &&
		   value1.M33 == value2.M33 &&
		   value1.M34 == value2.M34 &&

		   value1.M41 == value2.M41 &&
		   value1.M42 == value2.M42 &&
		   value1.M43 == value2.M43 &&
		   value1.M44 == value2.M44;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two matrices for inequality. </summary>

bool operator != (const Matrix& value1, const Matrix& value2)
{
	return value1.M11 != value2.M11 ||
		   value1.M12 != value2.M12 ||
		   value1.M13 != value2.M13 ||
		   value1.M14 != value2.M14 ||

		   value1.M21 != value2.M21 ||
		   value1.M22 != value2.M22 ||
		   value1.M23 != value2.M23 ||
		   value1.M24 != value2.M24 ||

		   value1.M31 != value2.M31 ||
		   value1.M32 != value2.M32 ||
		   value1.M33 != value2.M33 ||
		   value1.M34 != value2.M34 ||

		   value1.M41 != value2.M41 ||
		   value1.M42 != value2.M42 ||
		   value1.M43 != value2.M43 ||
		   value1.M44 != value2.M44;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Negates the components of a matrix. </summary>

Matrix operator - (const Matrix& value)
{
	return Matrix
	(
		-value.M11, -value.M12, -value.M13, -value.M14,
		-value.M21, -value.M22, -value.M23, -value.M24,
		-value.M31, -value.M32, -value.M33, -value.M34,
		-value.M41, -value.M42, -value.M43, -value.M44
	);
}

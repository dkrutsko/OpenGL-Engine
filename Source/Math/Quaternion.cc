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
#include "Math/Vector3.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"



//----------------------------------------------------------------------------//
// Constants                                                       Quaternion //
//----------------------------------------------------------------------------//

const Quaternion Quaternion::One		= Quaternion (1, 1, 1, 1);
const Quaternion Quaternion::Zero		= Quaternion (0, 0, 0, 0);
const Quaternion Quaternion::Identity	= Quaternion (0, 0, 0, 1);



//----------------------------------------------------------------------------//
// Constructors                                                    Quaternion //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="x"> Initial value for the x component. </param>
/// <param name="y"> Initial value for the y component. </param>
/// <param name="z"> Initial value for the z component. </param>
/// <param name="w"> Initial value for the w component. </param>

Quaternion::Quaternion (float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="vector"> Initial value for the vector component. </param>
/// <param name="scalar"> Initial value for the Rotation component. </param>

Quaternion::Quaternion (const Vector3& vector, float scalar)
{
	X = vector.X;
	Y = vector.Y;
	Z = vector.Z;
	W = scalar;
}



//----------------------------------------------------------------------------//
// Methods                                                         Quaternion //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this quaternion. </summary>

float Quaternion::Length (void) const
{
	return Math::Sqrt ((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this quaternion squared. </summary>

float Quaternion::LengthSquared (void) const
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides each component of this quaternion by its length. </summary>

void Quaternion::Normalize (void)
{
	float magnitude = 1 / Math::Sqrt ((X * X) + (Y * Y) + (Z * Z) + (W * W));

	X *= magnitude;
	Y *= magnitude;
	Z *= magnitude;
	W *= magnitude;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms this Quaternion into its conjugate. </summary>

void Quaternion::Conjugate (void)
{
	X = -X;
    Y = -Y;
    Z = -Z;
}



//----------------------------------------------------------------------------//
// Static                                                          Quaternion //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Linearly interpolates between two quaternions. </summary>
/// <param name="amount"> How far to interpolate between the values. </param>

Quaternion Quaternion::Lerp (const Quaternion &source, const Quaternion &target, float amount)
{
	Quaternion result;
	float a = 1 - amount;

	if (((source.X * target.X) +
		 (source.Y * target.Y) +
		 (source.Z * target.Z) +
		 (source.W * target.W)) >= 0)
	{
		result.X = (a * source.X) + (amount * target.X);
		result.Y = (a * source.Y) + (amount * target.Y);
		result.Z = (a * source.Z) + (amount * target.Z);
		result.W = (a * source.W) + (amount * target.W);
	}

	else
	{
		result.X = (a * source.X) - (amount * target.X);
		result.Y = (a * source.Y) - (amount * target.Y);
		result.Z = (a * source.Z) - (amount * target.Z);
		result.W = (a * source.W) - (amount * target.W);
	}

	float d = 1 / Math::Sqrt ((result.X * result.X) +
							  (result.Y * result.Y) +
							  (result.Z * result.Z) +
							  (result.W * result.W));

	result.X *= d;
	result.Y *= d;
	result.Z *= d;
	result.W *= d;

	return result;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Interpolates between two quaternions, using spherical linear interpolation.
/// </summary>
/// <param name="amount"> How far to interpolate between the values. </param>

Quaternion Quaternion::Slerp (const Quaternion &source, const Quaternion &target, float amount)
{
	float a;
	float b;

	bool flag = false;
	float dot = (source.X * target.X) +
				(source.Y * target.Y) +
				(source.Z * target.Z) +
				(source.W * target.W);

	if (dot < 0)
	{
		flag = true;
		dot = -dot;
	}

	if (dot > 0.999999f)
	{
		a = 1 - amount;
		b = flag ? -amount : amount;
	}

	else
	{
		float cos =     Math::Acosr (dot);
		float sin = 1 / Math::Sinr  (cos);

		a = Math::Sinr ((1 - amount) * cos) * sin;
		b = flag ? -Math::Sinr (amount * cos) * sin :
					Math::Sinr (amount * cos) * sin;
	}

	return Quaternion ((source.X * a) + (target.X * b),
					   (source.Y * a) + (target.Y * b),
					   (source.Z * a) + (target.Z * b),
					   (source.W * a) + (target.W * b));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the inverse of the specified quaternion. </summary>

Quaternion Quaternion::Inverse (const Quaternion& value)
{
	float d = 1 / ((value.X * value.X) +
				   (value.Y * value.Y) +
				   (value.Z * value.Z) +
				   (value.W * value.W));

	return Quaternion (-value.X * d,
					   -value.Y * d,
					   -value.Z * d,
					    value.W * d);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides each component of the quaternion by its length. </summary>

Quaternion Quaternion::Normalize (const Quaternion& value)
{
	float magnitude = 1 / Math::Sqrt ((value.X * value.X) +
									  (value.Y * value.Y) +
									  (value.Z * value.Z) +
									  (value.W * value.W));

	return Quaternion (value.X * magnitude,
					   value.Y * magnitude,
					   value.Z * magnitude,
					   value.W * magnitude);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the conjugate of a specified Quaternion. </summary>

Quaternion Quaternion::Conjugate (const Quaternion& value)
{
	return Quaternion (-value.X, -value.Y, -value.Z, value.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the dot product of two Quaternions. </summary>

float Quaternion::Dot (const Quaternion& value1, const Quaternion& value2)
{
	return (value1.X * value2.X) +
		   (value1.Y * value2.Y) +
		   (value1.Z * value2.Z) +
		   (value1.W * value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Concatenates two Quaternions. </summary>
/// <returns> The rotation of value1 followed by the rotation of value2. </returns>

Quaternion Quaternion::Concatenate (const Quaternion& value1, const Quaternion& value2)
{
	return Quaternion
	(
		(value1.W * value2.X) + (value1.X * value2.W) + (value1.Z * value2.Y) - (value1.Y * value2.Z),
		(value1.W * value2.Y) + (value1.Y * value2.W) + (value1.X * value2.Z) - (value1.Z * value2.X),
		(value1.W * value2.Z) + (value1.Z * value2.W) + (value1.Y * value2.X) - (value1.X * value2.Y),
		(value1.W * value2.W) - (value1.X * value2.X) - (value1.Y * value2.Y) - (value1.Z * value2.Z)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Creates a Quaternion from a vector and an angle to rotate about the vector.
/// </summary>
/// <param name="axis">  The vector to rotate around. </param>
/// <param name="angle"> The angle to rotate around the vector. </param>

Quaternion Quaternion::CreateFromAxisAngle (const Vector3& axis, float angle)
{
	float half = angle * 0.5f;
	float sin = Math::Sinr (half);
	float cos = Math::Cosr (half);

	return Quaternion (axis.X * sin, axis.Y * sin, axis.Z * sin, cos);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Creates a new Quaternion from specified pitch, yaw and roll angles.
/// </summary>
/// <param name="yaw">   The yaw angle, in radians, around the y-axis. </param>
/// <param name="pitch"> The pitch angle, in radians, around the x-axis. </param>
/// <param name="roll">  The roll angle, in radians, around the z-axis. </param>

Quaternion Quaternion::CreateFromYawPitchRoll (float yaw, float pitch, float roll)
{
	float yHalf =   yaw * 0.5f;
	float pHalf = pitch * 0.5f;
	float rHalf =  roll * 0.5f;

	float ySin = Math::Sinr (yHalf);
	float yCos = Math::Cosr (yHalf);

	float pSin = Math::Sinr (pHalf);
	float pCos = Math::Cosr (pHalf);

	float rSin = Math::Sinr (rHalf);
	float rCos = Math::Cosr (rHalf);

	return Quaternion ((yCos * pSin * rCos) + (ySin * pCos * rSin),
					   (ySin * pCos * rCos) - (yCos * pSin * rSin),
					   (yCos * pCos * rSin) - (ySin * pSin * rCos),
					   (yCos * pCos * rCos) + (ySin * pSin * rSin));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a Quaternion from a rotation Matrix. </summary>
/// <param name="matrix"> The rotation Matrix to create from. </param>

Quaternion Quaternion::CreateFromRotationMatrix (const Matrix& matrix)
{
	float trace = matrix.M11 + matrix.M22 + matrix.M33;

	if (trace > 0)
	{
		float s = 0.5f / Math::Sqrt (trace + 1);
		return Quaternion ((matrix.M23 - matrix.M32) * s,
						   (matrix.M31 - matrix.M13) * s,
						   (matrix.M12 - matrix.M21) * s, 0.25f / s);
	}

	else if ((matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33))
	{
		float s = 0.5f / Math::Sqrt (matrix.M11 - matrix.M22 - matrix.M33 + 1);
		return Quaternion (0.25f / s, (matrix.M12 + matrix.M21) * s,
									  (matrix.M13 + matrix.M31) * s,
									  (matrix.M23 - matrix.M32) * s);
	}

	else if (matrix.M22 > matrix.M33)
	{
		float s = 0.5f / Math::Sqrt (matrix.M22 - matrix.M11 - matrix.M33 + 1);
		return Quaternion ((matrix.M21 + matrix.M12) * s, 0.25f / s,
						   (matrix.M32 + matrix.M23) * s,
						   (matrix.M31 - matrix.M13) * s);
	}

	else
	{
		float s = 0.5f / Math::Sqrt (matrix.M33 - matrix.M11 - matrix.M22 + 1);
		return Quaternion ((matrix.M31 + matrix.M13) * s,
						   (matrix.M32 + matrix.M23) * s, 0.25f / s,
						   (matrix.M12 - matrix.M21) * s);
	}
}



//----------------------------------------------------------------------------//
// Operators                                                       Quaternion //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one quaternion to another. </summary>

Quaternion& operator += (Quaternion& value1, const Quaternion& value2)
{
	value1.X += value2.X;
	value1.Y += value2.Y;
	value1.Z += value2.Z;
	value1.W += value2.W;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one quaternion from another. </summary>

Quaternion& operator -= (Quaternion& value1, const Quaternion& value2)
{
	value1.X -= value2.X;
	value1.Y -= value2.Y;
	value1.Z -= value2.Z;
	value1.W -= value2.W;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies two quaternions. </summary>

Quaternion& operator *= (Quaternion& value1, const Quaternion& value2)
{
	value1 = Quaternion
	(
		(value1.X * value2.W) + (value1.W * value2.X) + (value1.Y * value2.Z) - (value1.Z * value2.Y),
		(value1.Y * value2.W) + (value1.W * value2.Y) + (value1.Z * value2.X) - (value1.X * value2.Z),
		(value1.Z * value2.W) + (value1.W * value2.Z) + (value1.X * value2.Y) - (value1.Y * value2.X),
		(value1.W * value2.W) - (value1.X * value2.X) - (value1.Y * value2.Y) - (value1.Z * value2.Z)
	);

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies a quaternion by a scalar. </summary>

Quaternion& operator *= (Quaternion& value, float scalar)
{
	value.X *= scalar;
	value.Y *= scalar;
	value.Z *= scalar;
	value.W *= scalar;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides a quaternion by another. </summary>

Quaternion& operator /= (Quaternion& value1, const Quaternion& value2)
{
	float x = value1.X;
	float y = value1.Y;
	float z = value1.Z;
	float w = value1.W;

	float d = 1 / ((value2.X * value2.X) +
				   (value2.Y * value2.Y) +
				   (value2.Z * value2.Z) +
				   (value2.W * value2.W));

	float xd = -value2.X * d;
	float yd = -value2.Y * d;
	float zd = -value2.Z * d;
	float wd =  value2.W * d;

	value1.X = (x * wd) + (w * xd) + (y * zd) - (z * yd);
	value1.Y = (y * wd) + (w * yd) + (z * xd) - (x * zd);
	value1.Z = (z * wd) + (w * zd) + (x * yd) - (y * xd);
	value1.W = (w * wd) - (x * xd) - (y * yd) - (z * zd);

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides a quaternion by a divider. </summary>

Quaternion& operator /= (Quaternion& value, float divider)
{
	divider = 1 / divider;

	value.X *= divider;
	value.Y *= divider;
	value.Z *= divider;
	value.W *= divider;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one quaternion to another. </summary>

Quaternion operator + (const Quaternion& value1, const Quaternion& value2)
{
	return Quaternion (value1.X + value2.X,
					   value1.Y + value2.Y,
					   value1.Z + value2.Z,
					   value1.W + value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one quaternion from another. </summary>

Quaternion operator - (const Quaternion& value1, const Quaternion& value2)
{
	return Quaternion (value1.X - value2.X,
					   value1.Y - value2.Y,
					   value1.Z - value2.Z,
					   value1.W - value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies two quaternions. </summary>

Quaternion operator * (const Quaternion& value1, const Quaternion& value2)
{
	return Quaternion
	(
		(value1.X * value2.W) + (value1.W * value2.X) + (value1.Y * value2.Z) - (value1.Z * value2.Y),
		(value1.Y * value2.W) + (value1.W * value2.Y) + (value1.Z * value2.X) - (value1.X * value2.Z),
		(value1.Z * value2.W) + (value1.W * value2.Z) + (value1.X * value2.Y) - (value1.Y * value2.X),
		(value1.W * value2.W) - (value1.X * value2.X) - (value1.Y * value2.Y) - (value1.Z * value2.Z)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies a quaternion by a scalar. </summary>

Quaternion operator * (const Quaternion& value, float scalar)
{
	return Quaternion (value.X * scalar,
					   value.Y * scalar,
					   value.Z * scalar,
					   value.W * scalar);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies a quaternion by a scalar. </summary>

Quaternion operator * (float scalar, const Quaternion& value)
{
	return Quaternion (scalar * value.X,
					   scalar * value.Y,
					   scalar * value.Z,
					   scalar * value.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides a quaternion by another. </summary>

Quaternion operator / (const Quaternion& value1, const Quaternion& value2)
{
	float d = 1 / ((value2.X * value2.X) +
				   (value2.Y * value2.Y) +
				   (value2.Z * value2.Z) +
				   (value2.W * value2.W));

	float x = -value2.X * d;
	float y = -value2.Y * d;
	float z = -value2.Z * d;
	float w =  value2.W * d;

	return Quaternion
	(
		(value1.X * w) + (value1.W * x) + (value1.Y * z) - (value1.Z * y),
		(value1.Y * w) + (value1.W * y) + (value1.Z * x) - (value1.X * z),
		(value1.Z * w) + (value1.W * z) + (value1.X * y) - (value1.Y * x),
		(value1.W * w) - (value1.X * x) - (value1.Y * y) - (value1.Z * z)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides a quaternion by a divider. </summary>

Quaternion operator / (const Quaternion& value, float divider)
{
	divider = 1 / divider;
	return Quaternion (value.X * divider,
					   value.Y * divider,
					   value.Z * divider,
					   value.W * divider);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two quaternions for equality. </summary>

bool operator == (const Quaternion& value1, const Quaternion& value2)
{
	return value1.X == value2.X &&
		   value1.Y == value2.Y &&
		   value1.Z == value2.Z &&
		   value1.W == value2.W;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two quaternions for inequality. </summary>

bool operator != (const Quaternion& value1, const Quaternion& value2)
{
	return value1.X != value2.X ||
		   value1.Y != value2.Y ||
		   value1.Z != value2.Z ||
		   value1.W != value2.W;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one quaternion is lexicographically less than another.
/// </summary>
/// <remakrs> The W component is not compared. </remarks>

bool operator < (const Quaternion& value1, const Quaternion& value2)
{
	return (value1.X <  value2.X) ||(value1.X == value2.X && value1.Y <  value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z <  value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one quaternion is lexicographically less than or equal to another.
/// </summary>
/// <remakrs> The W component is not compared. </remarks>

bool operator <= (const Quaternion& value1, const Quaternion& value2)
{
	return (value1.X <= value2.X) ||(value1.X == value2.X && value1.Y <= value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z <= value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one quaternion is lexicographically greater than another.
/// </summary>
/// <remakrs> The W component is not compared. </remarks>

bool operator > (const Quaternion& value1, const Quaternion& value2)
{
	return (value1.X >  value2.X) ||(value1.X == value2.X && value1.Y >  value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z >  value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one quaternion is lexicographically greater than or equal to another.
/// </summary>
/// <remarks> The W component will be compared last. </remarks>

bool operator >= (const Quaternion& value1, const Quaternion& value2)
{
	return (value1.X >= value2.X) ||(value1.X == value2.X && value1.Y >= value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z >= value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Negates each component of the quaternion. </summary>

Quaternion operator - (const Quaternion& value)
{
	return Quaternion (-value.X, -value.Y, -value.Z, -value.W);
}

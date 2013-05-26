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
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"



//----------------------------------------------------------------------------//
// Constants                                                          Vector4 //
//----------------------------------------------------------------------------//

const Vector4 Vector4::One		= Vector4 (1, 1, 1, 1);
const Vector4 Vector4::Zero		= Vector4 (0, 0, 0, 0);

const Vector4 Vector4::UnitX	= Vector4 (1, 0, 0, 0);
const Vector4 Vector4::UnitY	= Vector4 (0, 1, 0, 0);
const Vector4 Vector4::UnitZ	= Vector4 (0, 0, 1, 0);
const Vector4 Vector4::UnitW	= Vector4 (0, 0, 0, 1);

const Vector4 Vector4::Identity	= Vector4 (0, 0, 0, 1);



//----------------------------------------------------------------------------//
// Constructors                                                       Vector4 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="x"> Initial value for the x component. </param>
/// <param name="y"> Initial value for the y component. </param>
/// <param name="z"> Initial value for the z component. </param>
/// <param name="w"> Initial value for the w component. </param>

Vector4::Vector4 (float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="value"> Value to initialize all components to. </param>

Vector4::Vector4 (float value)
{
	X = value;
	Y = value;
	Z = value;
	W = value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="value"> Initial value for the x and y components. </param>
/// <param name="z"> Initial value for the z component. </param>
/// <param name="w"> Initial value for the w component. </param>

Vector4::Vector4 (float value, float z, float w)
{
	X = value;
	Y = value;
	Z = z;
	W = w;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="value"> Initial value for the x, y and z components. </param>
/// <param name="w"> Initial value for the w component. </param>

Vector4::Vector4 (float value, float w)
{
	X = value;
	Y = value;
	Z = value;
	W = w;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Vector4::Vector4 (const Vector2& value, float z, float w)
{
	X = value.X;
	Y = value.Y;
	Z = z;
	W = w;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Vector4::Vector4 (const Vector3& value, float w)
{
	X = value.X;
	Y = value.Y;
	Z = value.Z;
	W = w;
}



//----------------------------------------------------------------------------//
// Methods                                                            Vector4 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this vector. </summary>

float Vector4::Length (void) const
{
	return Math::Sqrt ((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this vector squared. </summary>

float Vector4::LengthSquared (void) const
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Turns the current vector into a unit vector. The result is a vector,
/// one unit in length, pointing in the same direction as the original. 
/// </summary>

void Vector4::Normalize (void)
{
	float magnitude = 1 / Math::Sqrt ((X * X) + (Y * Y) + (Z * Z) + (W * W));

	X *= magnitude;
	Y *= magnitude;
	Z *= magnitude;
	W *= magnitude;
}



//----------------------------------------------------------------------------//
// Static                                                             Vector4 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the dot product of two vectors. </summary>

float Vector4::Dot (const Vector4& value1, const Vector4& value2)
{
	return (value1.X * value2.X) +
		   (value1.Y * value2.Y) +
		   (value1.Z * value2.Z) +
		   (value1.W * value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a vector that contains the lowest value from each component. 
/// </summary>

Vector4 Vector4::Min (const Vector4& value1, const Vector4& value2)
{
	return Vector4 ((value1.X < value2.X) ? value1.X : value2.X,
					(value1.Y < value2.Y) ? value1.Y : value2.Y,
					(value1.Z < value2.Z) ? value1.Z : value2.Z,
					(value1.W < value2.W) ? value1.W : value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a vector that contains the highest value from each component.
/// </summary>

Vector4 Vector4::Max (const Vector4& value1, const Vector4& value2)
{
	return Vector4 ((value1.X > value2.X) ? value1.X : value2.X,
					(value1.Y > value2.Y) ? value1.Y : value2.Y,
					(value1.Z > value2.Z) ? value1.Z : value2.Z,
					(value1.W > value2.W) ? value1.W : value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two vectors. </summary>

float Vector4::Distance (const Vector4& value1, const Vector4& value2)
{
	float dx = value1.X - value2.X;
	float dy = value1.Y - value2.Y;
	float dz = value1.Z - value2.Z;
	float dw = value1.W - value2.W;

	return Math::Sqrt ((dx * dx) + (dy * dy) + (dz * dz) + (dw * dw));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two vectors squared. </summary>

float Vector4::DistanceSquared (const Vector4& value1, const Vector4& value2)
{
	float dx = value1.X - value2.X;
	float dy = value1.Y - value2.Y;
	float dz = value1.Z - value2.Z;
	float dw = value1.W - value2.W;

	return (dx * dx) + (dy * dy) + (dz * dz) + (dw * dw);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Creates a unit vector from the specified vector. The result is a vector,
/// one unit in length, pointing in the same direction as the original.
/// </summary>

Vector4 Vector4::Normalize (const Vector4& value)
{
	float magnitude = 1 / Math::Sqrt ((value.X * value.X) +
									  (value.Y * value.Y) +
									  (value.Z * value.Z) +
									  (value.W * value.W));

	return Vector4 (value.X * magnitude,
					value.Y * magnitude,
					value.Z * magnitude,
					value.W * magnitude);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Restricts each component within a specified range. </summary>
/// <param name="value"> The vector to clamp. </param>
/// <param name="min"> The minimum value. </param>
/// <param name="max"> The maximum value. </param>

Vector4 Vector4::Clamp (const Vector4& value, const Vector4& min, const Vector4& max)
{
	float x = value.X;
	x = (x > max.X) ? max.X : x;
	x = (x < min.X) ? min.X : x;

	float y = value.Y;
	y = (y > max.Y) ? max.Y : y;
	y = (y < min.Y) ? min.Y : y;

	float z = value.Z;
	z = (z > max.Z) ? max.Z : z;
	z = (z < min.Z) ? min.Z : z;

	float w = value.W;
	w = (w > max.W) ? max.W : w;
	w = (w < min.W) ? min.W : w;

	return Vector4 (x, y, z, w);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a linear interpolation between two vectors. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

Vector4 Vector4::Lerp (const Vector4& value1, const Vector4& value2, float amount)
{
	return Vector4
	(
		value1.X + ((value2.X - value1.X) * amount),
		value1.Y + ((value2.Y - value1.Y) * amount),
		value1.Z + ((value2.Z - value1.Z) * amount),
		value1.W + ((value2.W - value1.W) * amount)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Interpolates between two values using a cubic equation. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

Vector4 Vector4::SmoothStep (const Vector4& value1, const Vector4& value2, float amount)
{
	amount = (amount * amount) * (3 - (2 * amount));

	return Vector4
	(
		value1.X + ((value2.X - value1.X) * amount),
		value1.Y + ((value2.Y - value1.Y) * amount),
		value1.Z + ((value2.Z - value1.Z) * amount),
		value1.W + ((value2.W - value1.W) * amount)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a Vector4 containing the 2D Cartesian coordinates of a point
/// specified in barycentric coordinates relative to a 2D triangle. 
/// </summary>
/// <param name="value1"> The First vertex of the triangle. </param>
/// <param name="value2"> The Second vertex of the triangle. </param>
/// <param name="value3"> The Third vertex of the triangle. </param>
/// <param name="amount1"> The weighting factor toward vertex 2. </param>
/// <param name="amount2"> The weighting factor toward vertex 3. </param>

Vector4 Vector4::Barycentric (const Vector4& value1,
							  const Vector4& value2,
							  const Vector4& value3, float amount1, float amount2)
{
	return Vector4
	(
		value1.X + (amount1 * (value2.X - value1.X)) + (amount2 * (value3.X - value1.X)),
		value1.Y + (amount1 * (value2.Y - value1.Y)) + (amount2 * (value3.Y - value1.Y)),
		value1.Z + (amount1 * (value2.Z - value1.Z)) + (amount2 * (value3.Z - value1.Z)),
		value1.W + (amount1 * (value2.W - value1.W)) + (amount2 * (value3.W - value1.W))
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Performs a Catmull-Rom interpolation using the specified positions. 
/// </summary>
/// <param name="value1"> The first position in the interpolation. </param>
/// <param name="value2"> The second position in the interpolation. </param>
/// <param name="value3"> The third position in the interpolation. </param>
/// <param name="value4"> The fourth position in the interpolation. </param>
/// <param name="amount"> The weighting factor. </param>

Vector4 Vector4::CatmullRom (const Vector4& value1, const Vector4& value2,
							 const Vector4& value3, const Vector4& value4, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	return Vector4
	(
		0.5 * ((2 * value2.X) + ((-value1.X + value3.X) * amount) +
			(((2 * value1.X) - (5 * value2.X) + (4 * value3.X) - value4.X) * amountSq) +
			((-value1.X + (3 * value2.X) - (3 * value3.X) + value4.X) * amountCu)),

		0.5 * ((2 * value2.Y) + ((-value1.Y + value3.Y) * amount) +
			(((2 * value1.Y) - (5 * value2.Y) + (4 * value3.Y) - value4.Y) * amountSq) +
			((-value1.Y + (3 * value2.Y) - (3 * value3.Y) + value4.Y) * amountCu)),

		0.5 * ((2 * value2.Z) + ((-value1.Z + value3.Z) * amount) +
			(((2 * value1.Z) - (5 * value2.Z) + (4 * value3.Z) - value4.Z) * amountSq) +
			((-value1.Z + (3 * value2.Z) - (3 * value3.Z) + value4.Z) * amountCu)),

		0.5 * ((2 * value2.W) + ((-value1.W + value3.W) * amount) +
			(((2 * value1.W) - (5 * value2.W) + (4 * value3.W) - value4.W) * amountSq) +
			((-value1.W + (3 * value2.W) - (3 * value3.W) + value4.W) * amountCu))
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a Hermite spline interpolation. </summary>
/// <param name="amount"> The weighting factor. </param>

Vector4 Vector4::Hermite (const Vector4& value1, const Vector4& tangent1,
						  const Vector4& value2, const Vector4& tangent2, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	float v1 = ( 2 * amountCu) - (3 * amountSq) + 1;
	float v2 = (-2 * amountCu) + (3 * amountSq);
	float v3 = amountCu - (2 * amountSq) + amount;
	float v4 = amountCu - amountSq;

	return Vector4
	(
		(value1.X * v1) + (value2.X * v2) + (tangent1.X * v3) + (tangent2.X * v4),
		(value1.Y * v1) + (value2.Y * v2) + (tangent1.Y * v3) + (tangent2.Y * v4),
		(value1.Z * v1) + (value2.Z * v2) + (tangent1.Z * v3) + (tangent2.Z * v4),
		(value1.W * v1) + (value2.W * v2) + (tangent1.W * v3) + (tangent2.W * v4)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector2 by the given Matrix. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="matrix"> The transformation Matrix. </param>

Vector4 Vector4::Transform (const Vector2& position, const Matrix& matrix)
{
	return Vector4
	(
		(position.X * matrix.M11) + (position.Y * matrix.M21) + matrix.M41,
		(position.X * matrix.M12) + (position.Y * matrix.M22) + matrix.M42,
		(position.X * matrix.M13) + (position.Y * matrix.M23) + matrix.M43,
		(position.X * matrix.M14) + (position.Y * matrix.M24) + matrix.M44
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector3 by the given Matrix. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="matrix"> The transformation Matrix. </param>

Vector4 Vector4::Transform (const Vector3& position, const Matrix& matrix)
{
	return Vector4
	(
		(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M41,
		(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M42,
		(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M43,
		(position.X * matrix.M14) + (position.Y * matrix.M24) + (position.Z * matrix.M34) + matrix.M44
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector4 by the given Matrix. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="matrix"> The transformation Matrix. </param>

Vector4 Vector4::Transform (const Vector4& position, const Matrix& matrix)
{
	return Vector4
	(
		(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + (position.W * matrix.M41),
		(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + (position.W * matrix.M42),
		(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + (position.W * matrix.M43),
		(position.X * matrix.M14) + (position.Y * matrix.M24) + (position.Z * matrix.M34) + (position.W * matrix.M44)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector2 by the given Quaternion. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="rotation"> The Quaternion rotation. </param>

Vector4 Vector4::Transform (const Vector2& position, const Quaternion& rotation)
{
	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float xz = rotation.X * z;
	float yy = rotation.Y * y;
	float yz = rotation.Y * z;
	float zz = rotation.Z * z;
	float wx = rotation.W * x;
	float wy = rotation.W * y;
	float wz = rotation.W * z;

	return Vector4
	(
		(position.X * (1 - yy - zz)) + (position.Y * (0 + xy - wz)),
		(position.X * (0 + xy + wz)) + (position.Y * (1 - xx - zz)),
		(position.X * (0 + xz - wy)) + (position.Y * (0 + yz + wx)), 1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector3 by the given Quaternion. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="rotation"> The Quaternion rotation. </param>

Vector4 Vector4::Transform (const Vector3& position, const Quaternion& rotation)
{
	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float xz = rotation.X * z;
	float yy = rotation.Y * y;
	float yz = rotation.Y * z;
	float zz = rotation.Z * z;
	float wx = rotation.W * x;
	float wy = rotation.W * y;
	float wz = rotation.W * z;

	return Vector4
	(
		(position.X * (1 - yy - zz)) + (position.Y * (0 + xy - wz)) + (position.Z * (0 + xz + wy)),
		(position.X * (0 + xy + wz)) + (position.Y * (1 - xx - zz)) + (position.Z * (0 + yz - wx)),
		(position.X * (0 + xz - wy)) + (position.Y * (0 + yz + wx)) + (position.Z * (1 - xx - yy)), 1
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector4 by the given Quaternion. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="rotation"> The Quaternion rotation. </param>

Vector4 Vector4::Transform (const Vector4& position, const Quaternion& rotation)
{
	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float xz = rotation.X * z;
	float yy = rotation.Y * y;
	float yz = rotation.Y * z;
	float zz = rotation.Z * z;
	float wx = rotation.W * x;
	float wy = rotation.W * y;
	float wz = rotation.W * z;

	return Vector4
	(
		((position.X * (1 - yy - zz)) + (position.Y * (0 + xy - wz))) + (position.Z * (0 + xz + wy)),
		((position.X * (0 + xy + wz)) + (position.Y * (1 - xx - zz))) + (position.Z * (0 + yz - wx)),
		((position.X * (0 + xz - wy)) + (position.Y * (0 + yz + wx))) + (position.Z * (1 - xx - yy)), position.W
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms an array of Vector4s by a specified Matrix. </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector4s to transform. </param>
/// <param name="matrix"> The transform Matrix to apply. </param>
/// <param name="target"> The destination for results. </param>

void Vector4::Transform (quint32 length, const Vector4* source,
						 const Matrix& matrix, Vector4* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (quint32 i = 0; i < length; ++i)
	{
		float sx = source[i].X;
		float sy = source[i].Y;
		float sz = source[i].Z;
		float sw = source[i].W;

		target[i].X = (sx * matrix.M11) + (sy * matrix.M21) + (sz * matrix.M31) + (sw * matrix.M41);
		target[i].Y = (sx * matrix.M12) + (sy * matrix.M22) + (sz * matrix.M32) + (sw * matrix.M42);
		target[i].Z = (sx * matrix.M13) + (sy * matrix.M23) + (sz * matrix.M33) + (sw * matrix.M43);
		target[i].W = (sx * matrix.M14) + (sy * matrix.M24) + (sz * matrix.M34) + (sw * matrix.M44);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms an array of Vector4s by a specified Quaternion. </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector4s to transform. </param>
/// <param name="rotation"> The transform Quaternion to apply. </param>
/// <param name="target"> The destination for results. </param>

void Vector4::Transform (quint32 length, const Vector4* source,
						 const Quaternion& rotation, Vector4* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float xz = rotation.X * z;
	float yy = rotation.Y * y;
	float yz = rotation.Y * z;
	float zz = rotation.Z * z;
	float wx = rotation.W * x;
	float wy = rotation.W * y;
	float wz = rotation.W * z;

	float v1 = 1 - yy - zz;
	float v2 = 0 + xy - wz;
	float v3 = 0 + xz + wy;
	float v4 = 0 + xy + wz;
	float v5 = 1 - xx - zz;
	float v6 = 0 + yz - wx;
	float v7 = 0 + xz - wy;
	float v8 = 0 + yz + wx;
	float v9 = 1 - xx - yy;

	for (quint32 i = 0; i < length; ++i)
	{
		float sx = source[i].X;
		float sy = source[i].Y;
		float sz = source[i].Z;

		target[i].X = (sx * v1) + (sy * v2) + (sz * v3);
		target[i].Y = (sx * v4) + (sy * v5) + (sz * v6);
		target[i].Z = (sx * v7) + (sy * v8) + (sz * v9);

		target[i].W = source[i].W;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector4s by a specified
/// Matrix and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector4s to transform. </param>
/// <param name="matrix"> The Matrix to transform by. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector4::Transform (quint32 length, quint32 sourceIndex, const Vector4* source,
						 const Matrix& matrix, quint32 targetIndex, Vector4* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (length; length > 0; --length, ++sourceIndex, ++targetIndex)
	{
		float sx = source[sourceIndex].X;
		float sy = source[sourceIndex].Y;
		float sz = source[sourceIndex].Z;
		float sw = source[sourceIndex].W;

		target[targetIndex].X = (sx * matrix.M11) + (sy * matrix.M21) + (sz * matrix.M31) + (sw * matrix.M41);
		target[targetIndex].Y = (sx * matrix.M12) + (sy * matrix.M22) + (sz * matrix.M32) + (sw * matrix.M42);
		target[targetIndex].Z = (sx * matrix.M13) + (sy * matrix.M23) + (sz * matrix.M33) + (sw * matrix.M43);
		target[targetIndex].W = (sx * matrix.M14) + (sy * matrix.M24) + (sz * matrix.M34) + (sw * matrix.M44);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector4s by a specified
/// Quaternion and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector4s to transform. </param>
/// <param name="rotation"> The Quaternion rotation to apply. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector4::Transform (quint32 length, quint32 sourceIndex, const Vector4* source,
						 const Quaternion& rotation, quint32 targetIndex, Vector4* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float xz = rotation.X * z;
	float yy = rotation.Y * y;
	float yz = rotation.Y * z;
	float zz = rotation.Z * z;
	float wx = rotation.W * x;
	float wy = rotation.W * y;
	float wz = rotation.W * z;

	float v1 = 1 - yy - zz;
	float v2 = 0 + xy - wz;
	float v3 = 0 + xz + wy;
	float v4 = 0 + xy + wz;
	float v5 = 1 - xx - zz;
	float v6 = 0 + yz - wx;
	float v7 = 0 + xz - wy;
	float v8 = 0 + yz + wx;
	float v9 = 1 - xx - yy;

	for (length; length > 0; --length, ++sourceIndex, ++targetIndex)
	{
		float sx = source[sourceIndex].X;
		float sy = source[sourceIndex].Y;
		float sz = source[sourceIndex].Z;

		target[targetIndex].X = (sx * v1) + (sy * v2) + (sz * v3);
		target[targetIndex].Y = (sx * v4) + (sy * v5) + (sz * v6);
		target[targetIndex].Z = (sx * v7) + (sy * v8) + (sz * v9);

		target[targetIndex].W = source[sourceIndex].W;
	}
}



//----------------------------------------------------------------------------//
// Operators                                                          Vector4 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one vector to another. </summary>

Vector4& operator += (Vector4& value1, const Vector4& value2)
{
	value1.X += value2.X;
	value1.Y += value2.Y;
	value1.Z += value2.Z;
	value1.W += value2.W;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one vector from another. </summary>

Vector4& operator -= (Vector4& value1, const Vector4& value2)
{
	value1.X -= value2.X;
	value1.Y -= value2.Y;
	value1.Z -= value2.Z;
	value1.W -= value2.W;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of two vectors by each other. </summary>

Vector4& operator *= (Vector4& value1, const Vector4& value2)
{
	value1.X *= value2.X;
	value1.Y *= value2.Y;
	value1.Z *= value2.Z;
	value1.W *= value2.W;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two vectors against each other. </summary>

Vector4& operator /= (Vector4& value1, const Vector4& value2)
{
	value1.X /= value2.X;
	value1.Y /= value2.Y;
	value1.Z /= value2.Z;
	value1.W /= value2.W;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector4& operator += (Vector4& value1, float value2)
{
	value1.X += value2;
	value1.Y += value2;
	value1.Z += value2;
	value1.W += value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector4& operator -= (Vector4& value1, float value2)
{
	value1.X -= value2;
	value1.Y -= value2;
	value1.Z -= value2;
	value1.W -= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector4& operator *= (Vector4& value1, float value2)
{
	value1.X *= value2;
	value1.Y *= value2;
	value1.Z *= value2;
	value1.W *= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector4& operator /= (Vector4& value1, float value2)
{
	value1.X /= value2;
	value1.Y /= value2;
	value1.Z /= value2;
	value1.W /= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one vector to another. </summary>

Vector4 operator + (const Vector4& value1, const Vector4& value2)
{
	return Vector4 (value1.X + value2.X,
					value1.Y + value2.Y,
					value1.Z + value2.Z,
					value1.W + value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one vector from another. </summary>

Vector4 operator - (const Vector4& value1, const Vector4& value2)
{
	return Vector4 (value1.X - value2.X,
					value1.Y - value2.Y,
					value1.Z - value2.Z,
					value1.W - value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of two vectors by each other. </summary>

Vector4 operator * (const Vector4& value1, const Vector4& value2)
{
	return Vector4 (value1.X * value2.X,
					value1.Y * value2.Y,
					value1.Z * value2.Z,
					value1.W * value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two vectors against each other. </summary>

Vector4 operator / (const Vector4& value1, const Vector4& value2)
{
	return Vector4 (value1.X / value2.X,
					value1.Y / value2.Y,
					value1.Z / value2.Z,
					value1.W / value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector4 operator + (const Vector4& value1, float value2)
{
	return Vector4 (value1.X + value2,
					value1.Y + value2,
					value1.Z + value2,
					value1.W + value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector4 operator - (const Vector4& value1, float value2)
{
	return Vector4 (value1.X - value2,
					value1.Y - value2,
					value1.Z - value2,
					value1.W - value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector4 operator * (const Vector4& value1, float value2)
{
	return Vector4 (value1.X * value2,
					value1.Y * value2,
					value1.Z * value2,
					value1.W * value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector4 operator / (const Vector4& value1, float value2)
{
	return Vector4 (value1.X / value2,
					value1.Y / value2,
					value1.Z / value2,
					value1.W / value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector4 operator + (float value1, const Vector4& value2)
{
	return Vector4 (value1 + value2.X,
					value1 + value2.Y,
					value1 + value2.Z,
					value1 + value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector4 operator - (float value1, const Vector4& value2)
{
	return Vector4 (value1 - value2.X,
					value1 - value2.Y,
					value1 - value2.Z,
					value1 - value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector4 operator * (float value1, const Vector4& value2)
{
	return Vector4 (value1 * value2.X,
					value1 * value2.Y,
					value1 * value2.Z,
					value1 * value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector4 operator / (float value1, const Vector4& value2)
{
	return Vector4 (value1 / value2.X,
					value1 / value2.Y,
					value1 / value2.Z,
					value1 / value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two vectors for equality. </summary>

bool operator == (const Vector4& value1, const Vector4& value2)
{
	return value1.X == value2.X &&
		   value1.Y == value2.Y &&
		   value1.Z == value2.Z &&
		   value1.W == value2.W;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two vectors for inequality. </summary>

bool operator != (const Vector4& value1, const Vector4& value2)
{
	return value1.X != value2.X ||
		   value1.Y != value2.Y ||
		   value1.Z != value2.Z ||
		   value1.W != value2.W;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically less than another.
/// </summary>
/// <remakrs> The W component is compared last. </remarks>

bool operator < (const Vector4& value1, const Vector4& value2)
{
	return (value1.X <  value2.X) ||(value1.X == value2.X && value1.Y <  value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z <  value2.Z) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z == value2.Z && value2.W < value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically less than or equal to another.
/// </summary>
/// <remarks> The W component is compared last. </remarks>

bool operator <= (const Vector4& value1, const Vector4& value2)
{
	return (value1.X <= value2.X) ||(value1.X == value2.X && value1.Y <= value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z <= value2.Z) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z == value2.Z && value2.W <= value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically greater than another.
/// </summary>
/// <remarks> The W component is compared last. </remarks>

bool operator > (const Vector4& value1, const Vector4& value2)
{
	return (value1.X >  value2.X) ||(value1.X == value2.X && value1.Y >  value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z >  value2.Z) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z == value2.Z && value2.W > value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically greater than or equal to another.
/// </summary>
/// <remarks> The W component is compared last. </remarks>

bool operator >= (const Vector4& value1, const Vector4& value2)
{
	return (value1.X >= value2.X) ||(value1.X == value2.X && value1.Y >= value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z >= value2.Z) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z == value2.Z && value2.W >= value2.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a vector pointing in the opposite direction. </summary>

Vector4 operator - (const Vector4& value)
{
	return Vector4 (-value.X, -value.Y, -value.Z, -value.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Pre-increments the components of the vector by one. </summary>

Vector4& operator ++ (Vector4& value)
{
	++value.X;
	++value.Y;
	++value.Z;
	++value.W;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Pre-decrements the components of the vector by one. </summary>

Vector4& operator -- (Vector4& value)
{
	--value.X;
	--value.Y;
	--value.Z;
	--value.W;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Post-increments the components of the vector by one. </summary>

Vector4 operator ++ (Vector4& value, int)
{
	Vector4 result = value;

	++value.X;
	++value.Y;
	++value.Z;
	++value.W;

	return result;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Post-decrements the components of the vector by one. </summary>

Vector4 operator -- (Vector4& value, int)
{
	Vector4 result = value;

	--value.X;
	--value.Y;
	--value.Z;
	--value.W;

	return result;
}

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
// Constants                                                          Vector3 //
//----------------------------------------------------------------------------//

const Vector3 Vector3::One		= Vector3 (1, 1, 1);
const Vector3 Vector3::Zero		= Vector3 (0, 0, 0);

const Vector3 Vector3::UnitX	= Vector3 (1, 0, 0);
const Vector3 Vector3::UnitY	= Vector3 (0, 1, 0);
const Vector3 Vector3::UnitZ	= Vector3 (0, 0, 1);

const Vector3 Vector3::Up		= Vector3 ( 0,  1,  0);
const Vector3 Vector3::Down		= Vector3 ( 0, -1,  0);
const Vector3 Vector3::Right	= Vector3 ( 1,  0,  0);
const Vector3 Vector3::Left		= Vector3 (-1,  0,  0);
const Vector3 Vector3::Backward	= Vector3 ( 0,  0,  1);
const Vector3 Vector3::Forward	= Vector3 ( 0,  0, -1);



//----------------------------------------------------------------------------//
// Constructors                                                       Vector3 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="x"> Initial position for the x component. </param>
/// <param name="y"> Initial position for the y component. </param>
/// <param name="z"> Initial position for the z component. </param>

Vector3::Vector3 (float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="position"> Value to initialize all components to. </param>

Vector3::Vector3 (float value)
{
	X = value;
	Y = value;
	Z = value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="position"> Initial position for the x and y components. </param>
/// <param name="z"> Initial position for the z component. </param>

Vector3::Vector3 (float value, float z)
{
	X = value;
	Y = value;
	Z = z;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Vector3::Vector3 (const Vector2& value, float z)
{
	X = value.X;
	Y = value.Y;
	Z = z;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Vector3::Vector3 (const Vector4& value)
{
	X = value.X;
	Y = value.Y;
	Z = value.Z;
}



//----------------------------------------------------------------------------//
// Methods                                                            Vector3 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this vector. </summary>

float Vector3::Length (void) const
{
	return Math::Sqrt ((X * X) + (Y * Y) + (Z * Z));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this vector squared. </summary>

float Vector3::LengthSquared (void) const
{
	return (X * X) + (Y * Y) + (Z * Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Turns the current vector into a unit vector. The result is a vector,
/// one unit in length, pointing in the same direction as the original. 
/// </summary>

void Vector3::Normalize (void)
{
	float magnitude = 1 / Math::Sqrt ((X * X) + (Y * Y) + (Z * Z));

	X *= magnitude;
	Y *= magnitude;
	Z *= magnitude;
}



//----------------------------------------------------------------------------//
// Static                                                             Vector3 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Calculates the dot product of two vectors. If the two vectors are
/// unit vectors, the dot product returns a floating point position between
/// 1 and -1 that can be used to determine some properties of the angle
/// between two vectors. For example, it can show whether the vectors are
/// orthogonal, parallel, or have an acute or obtuse angle between them. 
/// </summary>

float Vector3::Dot (const Vector3& value1, const Vector3& value2)
{
	return (value1.X * value2.X) +
		   (value1.Y * value2.Y) +
		   (value1.Z * value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the cross product of two vectors. </summary>

Vector3 Vector3::Cross (const Vector3& value1, const Vector3& value2)
{
	return Vector3 ((value1.Y * value2.Z) - (value1.Z * value2.Y),
					(value1.Z * value2.X) - (value1.X * value2.Z),
					(value1.X * value2.Y) - (value1.Y * value2.X));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a vector that contains the lowest position from each component. 
/// </summary>

Vector3 Vector3::Min (const Vector3& value1, const Vector3& value2)
{
	return Vector3 ((value1.X < value2.X) ? value1.X : value2.X,
					(value1.Y < value2.Y) ? value1.Y : value2.Y,
					(value1.Z < value2.Z) ? value1.Z : value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a vector that contains the highest position from each component.
/// </summary>

Vector3 Vector3::Max (const Vector3& value1, const Vector3& value2)
{
	return Vector3 ((value1.X > value2.X) ? value1.X : value2.X,
					(value1.Y > value2.Y) ? value1.Y : value2.Y,
					(value1.Z > value2.Z) ? value1.Z : value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two vectors. </summary>

float Vector3::Distance (const Vector3& value1, const Vector3& value2)
{
	float dx = value1.X - value2.X;
	float dy = value1.Y - value2.Y;
	float dz = value1.Z - value2.Z;

	return Math::Sqrt ((dx * dx) + (dy * dy) + (dz * dz));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two vectors squared. </summary>

float Vector3::DistanceSquared (const Vector3& value1, const Vector3& value2)
{
	float dx = value1.X - value2.X;
	float dy = value1.Y - value2.Y;
	float dz = value1.Z - value2.Z;

	return (dx * dx) + (dy * dy) + (dz * dz);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Creates a unit vector from the specified vector. The result is a vector,
/// one unit in length, pointing in the same direction as the original.
/// </summary>

Vector3 Vector3::Normalize (const Vector3& value)
{
	float magnitude = 1 / Math::Sqrt ((value.X * value.X) +
									  (value.Y * value.Y) +
									  (value.Z * value.Z));

	return Vector3 (value.X * magnitude,
					value.Y * magnitude,
					value.Z * magnitude);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Restricts each component within a specified range. </summary>
/// <param name="value"> The vector to clamp. </param>
/// <param name="min"> The minimum value. </param>
/// <param name="max"> The maximum value. </param>
		
Vector3 Vector3::Clamp (const Vector3& value, const Vector3& min, const Vector3& max)
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

	return Vector3 (x, y, z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Determines a reflection vector based on the normal. </summary>
/// <param name="value"> The vector to reflect. </param>
/// <param name="normal"> The normal to reflect against. </param>

Vector3 Vector3::Reflect (const Vector3& value, const Vector3& normal)
{
	float dot = (value.X * normal.X) +
				(value.Y * normal.Y) +
				(value.Z * normal.Z);

	return Vector3 (value.X - (2 * dot * normal.X),
					value.Y - (2 * dot * normal.Y),
					value.Z - (2 * dot * normal.Z));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a linear interpolation between two vectors. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

Vector3 Vector3::Lerp (const Vector3& value1, const Vector3& value2, float amount)
{
	return Vector3
	(
		value1.X + ((value2.X - value1.X) * amount),
		value1.Y + ((value2.Y - value1.Y) * amount),
		value1.Z + ((value2.Z - value1.Z) * amount)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Interpolates between two values using a cubic equation. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

Vector3 Vector3::SmoothStep (const Vector3& value1, const Vector3& value2, float amount)
{
	amount = (amount * amount) * (3 - (2 * amount));

	return Vector3
	(
		value1.X + ((value2.X - value1.X) * amount),
		value1.Y + ((value2.Y - value1.Y) * amount),
		value1.Z + ((value2.Z - value1.Z) * amount)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a Vector3 containing the 3D Cartesian coordinates of a point
/// specified in barycentric coordinates relative to a 3D triangle. 
/// </summary>
/// <param name="value1"> The First vertex of the triangle. </param>
/// <param name="value2"> The Second vertex of the triangle. </param>
/// <param name="value3"> The Third vertex of the triangle. </param>
/// <param name="amount1"> The weighting factor toward vertex 2. </param>
/// <param name="amount2"> The weighting factor toward vertex 3. </param>

Vector3 Vector3::Barycentric (const Vector3& value1,
							  const Vector3& value2,
							  const Vector3& value3, float amount1, float amount2)
{
	return Vector3
	(
		value1.X + (amount1 * (value2.X - value1.X)) + (amount2 * (value3.X - value1.X)),
		value1.Y + (amount1 * (value2.Y - value1.Y)) + (amount2 * (value3.Y - value1.Y)),
		value1.Z + (amount1 * (value2.Z - value1.Z)) + (amount2 * (value3.Z - value1.Z))
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

Vector3 Vector3::CatmullRom (const Vector3& value1, const Vector3& value2,
							 const Vector3& value3, const Vector3& value4, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	return Vector3
	(
		0.5 * ((2 * value2.X) + ((-value1.X + value3.X) * amount) +
			(((2 * value1.X) - (5 * value2.X) + (4 * value3.X) - value4.X) * amountSq) +
			((-value1.X + (3 * value2.X) - (3 * value3.X) + value4.X) * amountCu)),

		0.5 * ((2 * value2.Y) + ((-value1.Y + value3.Y) * amount) +
			(((2 * value1.Y) - (5 * value2.Y) + (4 * value3.Y) - value4.Y) * amountSq) +
			((-value1.Y + (3 * value2.Y) - (3 * value3.Y) + value4.Y) * amountCu)),

		0.5 * ((2 * value2.Z) + ((-value1.Z + value3.Z) * amount) +
			(((2 * value1.Z) - (5 * value2.Z) + (4 * value3.Z) - value4.Z) * amountSq) +
			((-value1.Z + (3 * value2.Z) - (3 * value3.Z) + value4.Z) * amountCu))
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a Hermite spline interpolation. </summary>
/// <param name="amount"> The weighting factor. </param>

Vector3 Vector3::Hermite (const Vector3& value1, const Vector3& tangent1,
						  const Vector3& value2, const Vector3& tangent2, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	float v1 = ( 2 * amountCu) - (3 * amountSq) + 1;
	float v2 = (-2 * amountCu) + (3 * amountSq);
	float v3 = amountCu - (2 * amountSq) + amount;
	float v4 = amountCu - amountSq;

	return Vector3
	(
		(value1.X * v1) + (value2.X * v2) + (tangent1.X * v3) + (tangent2.X * v4),
		(value1.Y * v1) + (value2.Y * v2) + (tangent1.Y * v3) + (tangent2.Y * v4),
		(value1.Z * v1) + (value2.Z * v2) + (tangent1.Z * v3) + (tangent2.Z * v4)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector3 by the specified matrix. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="matrix"> The transformation Matrix. </param>

Vector3 Vector3::Transform (const Vector3& position, const Matrix& matrix)
{
	return Vector3
	(
		(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M14,
		(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M24,
		(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M34
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a Vector3 by a specified Quaternion rotation. </summary>
/// <param name="position"> The vector to rotate. </param>
/// <param name="rotation"> The Quaternion rotation to apply. </param>

Vector3 Vector3::Transform (const Vector3& position, const Quaternion& rotation)
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

	return Vector3
	(
		(position.X * (1 - yy - zz)) + (position.Y * (0 + xy - wz)) + (position.Z * (0 + xz + wy)),
		(position.X * (0 + xy + wz)) + (position.Y * (1 - xx - zz)) + (position.Z * (0 + yz - wx)),
		(position.X * (0 + xz - wy)) + (position.Y * (0 + yz + wx)) + (position.Z * (1 - xx - yy))
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a vector normal by a matrix. </summary>
/// <param name="normal"> The normal to transform </param>
/// <param name="matrix"> The transformation Matrix. </param>

Vector3 Vector3::TransformNormal (const Vector3& normal, const Matrix& matrix)
{
	return Vector3
	(
		(normal.X * matrix.M11) + (normal.Y * matrix.M21) + (normal.Z * matrix.M31),
		(normal.X * matrix.M12) + (normal.Y * matrix.M22) + (normal.Z * matrix.M32),
		(normal.X * matrix.M13) + (normal.Y * matrix.M32) + (normal.Z * matrix.M33)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms an array of Vector3s by a specified Matrix. </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector3s to transform. </param>
/// <param name="matrix"> The transform Matrix to apply. </param>
/// <param name="target"> The destination for results. </param>

void Vector3::Transform (quint32 length, const Vector3* source,
						 const Matrix& matrix, Vector3* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (quint32 i = 0; i < length; ++i)
	{
		float sx = source[i].X;
		float sy = source[i].Y;
		float sz = source[i].Z;

		target[i].X = (sx * matrix.M11) + (sy * matrix.M21) + (sz * matrix.M31) + matrix.M41;
		target[i].Y = (sx * matrix.M12) + (sy * matrix.M22) + (sz * matrix.M32) + matrix.M42;
		target[i].Z = (sx * matrix.M13) + (sy * matrix.M23) + (sz * matrix.M33) + matrix.M43;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms an array of Vector3s by a specified Quaternion. </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector3s to transform. </param>
/// <param name="rotation"> The transform Quaternion to apply. </param>
/// <param name="target"> The destination for results. </param>

void Vector3::Transform (quint32 length, const Vector3* source,
						 const Quaternion& rotation, Vector3* target)
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
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms an array of Vector3s vector normals by a specified Matrix. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector3s to transform. </param>
/// <param name="matrix"> The Matrix to transform by. </param>
/// <param name="target"> The destination for results. </param>

void Vector3::TransformNormal (quint32 length, const Vector3* source,
							   const Matrix& matrix, Vector3* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (quint32 i = 0; i < length; ++i)
	{
		float sx = source[i].X;
		float sy = source[i].Y;
		float sz = source[i].Z;

		target[i].X = (sx * matrix.M11) + (sy * matrix.M21) + (sz * matrix.M31);
		target[i].Y = (sx * matrix.M12) + (sy * matrix.M22) + (sz * matrix.M32);
		target[i].Z = (sx * matrix.M13) + (sy * matrix.M23) + (sz * matrix.M33);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector3s by a specified
/// Matrix and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector3s to transform. </param>
/// <param name="matrix"> The Matrix to transform by. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector3::Transform (quint32 length, quint32 sourceIndex, const Vector3* source,
						 const Matrix& matrix, quint32 targetIndex, Vector3* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (length; length > 0; --length, ++sourceIndex, ++targetIndex)
	{
		float sx = source[sourceIndex].X;
		float sy = source[sourceIndex].Y;
		float sz = source[sourceIndex].Z;

		target[targetIndex].X = (sx * matrix.M11) + (sy * matrix.M21) + (sz * matrix.M31) + matrix.M41;
		target[targetIndex].Y = (sx * matrix.M12) + (sy * matrix.M22) + (sz * matrix.M32) + matrix.M42;
		target[targetIndex].Z = (sx * matrix.M13) + (sy * matrix.M23) + (sz * matrix.M33) + matrix.M43;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector3s by a specified
/// Quaternion and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector3s to transform. </param>
/// <param name="rotation"> The Quaternion rotation to apply. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector3::Transform (quint32 length, quint32 sourceIndex, const Vector3* source,
						 const Quaternion& rotation, quint32 targetIndex, Vector3* target)
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
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector3s vector normals by a
/// specified Matrix and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector3s to transform. </param>
/// <param name="matrix"> The Matrix to transform by. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector3::TransformNormal (quint32 length, quint32 sourceIndex, const Vector3* source,
							   const Matrix& matrix, quint32 targetIndex, Vector3* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (length; length > 0; --length, ++sourceIndex, ++targetIndex)
	{
		float sx = source[sourceIndex].X;
		float sy = source[sourceIndex].Y;
		float sz = source[sourceIndex].Z;

		target[targetIndex].X = (sx * matrix.M11) + (sy * matrix.M21) + (sz * matrix.M31);
		target[targetIndex].Y = (sx * matrix.M12) + (sy * matrix.M22) + (sz * matrix.M32);
		target[targetIndex].Z = (sx * matrix.M13) + (sy * matrix.M23) + (sz * matrix.M33);
	}
}



//----------------------------------------------------------------------------//
// Operators                                                          Vector3 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one vector to another. </summary>

Vector3& operator += (Vector3& value1, const Vector3& value2)
{
	value1.X += value2.X;
	value1.Y += value2.Y;
	value1.Z += value2.Z;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one vector from another. </summary>

Vector3& operator -= (Vector3& value1, const Vector3& value2)
{
	value1.X -= value2.X;
	value1.Y -= value2.Y;
	value1.Z -= value2.Z;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of two vectors by each other. </summary>

Vector3& operator *= (Vector3& value1, const Vector3& value2)
{
	value1.X *= value2.X;
	value1.Y *= value2.Y;
	value1.Z *= value2.Z;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two vectors against each other. </summary>

Vector3& operator /= (Vector3& value1, const Vector3& value2)
{
	value1.X /= value2.X;
	value1.Y /= value2.Y;
	value1.Z /= value2.Z;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector3& operator += (Vector3& value1, float value2)
{
	value1.X += value2;
	value1.Y += value2;
	value1.Z += value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector3& operator -= (Vector3& value1, float value2)
{
	value1.X -= value2;
	value1.Y -= value2;
	value1.Z -= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector3& operator *= (Vector3& value1, float value2)
{
	value1.X *= value2;
	value1.Y *= value2;
	value1.Z *= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector3& operator /= (Vector3& value1, float value2)
{
	value1.X /= value2;
	value1.Y /= value2;
	value1.Z /= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one vector to another. </summary>

Vector3 operator + (const Vector3& value1, const Vector3& value2)
{
	return Vector3 (value1.X + value2.X,
					value1.Y + value2.Y,
					value1.Z + value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one vector from another. </summary>

Vector3 operator - (const Vector3& value1, const Vector3& value2)
{
	return Vector3 (value1.X - value2.X,
					value1.Y - value2.Y,
					value1.Z - value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of two vectors by each other. </summary>

Vector3 operator * (const Vector3& value1, const Vector3& value2)
{
	return Vector3 (value1.X * value2.X,
					value1.Y * value2.Y,
					value1.Z * value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two vectors against each other. </summary>

Vector3 operator / (const Vector3& value1, const Vector3& value2)
{
	return Vector3 (value1.X / value2.X,
					value1.Y / value2.Y,
					value1.Z / value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector3 operator + (const Vector3& value1, float value2)
{
	return Vector3 (value1.X + value2,
					value1.Y + value2,
					value1.Z + value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector3 operator - (const Vector3& value1, float value2)
{
	return Vector3 (value1.X - value2,
					value1.Y - value2,
					value1.Z - value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector3 operator * (const Vector3& value1, float value2)
{
	return Vector3 (value1.X * value2,
					value1.Y * value2,
					value1.Z * value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector3 operator / (const Vector3& value1, float value2)
{
	return Vector3 (value1.X / value2,
					value1.Y / value2,
					value1.Z / value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector3 operator + (float value1, const Vector3& value2)
{
	return Vector3 (value1 + value2.X,
					value1 + value2.Y,
					value1 + value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector3 operator - (float value1, const Vector3& value2)
{
	return Vector3 (value1 - value2.X,
					value1 - value2.Y,
					value1 - value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector3 operator * (float value1, const Vector3& value2)
{
	return Vector3 (value1 * value2.X,
					value1 * value2.Y,
					value1 * value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector3 operator / (float value1, const Vector3& value2)
{
	return Vector3 (value1 / value2.X,
					value1 / value2.Y,
					value1 / value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two vectors for equality. </summary>

bool operator == (const Vector3& value1, const Vector3& value2)
{
	return value1.X == value2.X &&
		   value1.Y == value2.Y &&
		   value1.Z == value2.Z;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two vectors for inequality. </summary>

bool operator != (const Vector3& value1, const Vector3& value2)
{
	return value1.X != value2.X ||
		   value1.Y != value2.Y ||
		   value1.Z != value2.Z;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically less than another.
/// </summary>

bool operator < (const Vector3& value1, const Vector3& value2)
{
	return (value1.X <  value2.X) ||(value1.X == value2.X && value1.Y <  value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z <  value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically less than or equal to another. 
/// </summary>

bool operator <= (const Vector3& value1, const Vector3& value2)
{
	return (value1.X <= value2.X) ||(value1.X == value2.X && value1.Y <= value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z <= value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically greater than another.
/// </summary>

bool operator > (const Vector3& value1, const Vector3& value2)
{
	return (value1.X >  value2.X) ||(value1.X == value2.X && value1.Y >  value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z >  value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically greater than or equal to another. 
/// </summary>

bool operator >= (const Vector3& value1, const Vector3& value2)
{
	return (value1.X >= value2.X) ||(value1.X == value2.X && value1.Y >= value2.Y) ||
		   (value1.X == value2.X &&  value1.Y == value2.Y && value1.Z >= value2.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a vector pointing in the opposite direction. </summary>

Vector3 operator - (const Vector3& value)
{
	return Vector3 (-value.X, -value.Y, -value.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Pre-increments the components of the vector by one. </summary>

Vector3& operator ++ (Vector3& value)
{
	++value.X;
	++value.Y;
	++value.Z;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Pre-decrements the components of the vector by one. </summary>

Vector3& operator -- (Vector3& value)
{
	--value.X;
	--value.Y;
	--value.Z;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Post-increments the components of the vector by one. </summary>

Vector3 operator ++ (Vector3& value, int)
{
	Vector3 result = value;

	++value.X;
	++value.Y;
	++value.Z;

	return result;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Post-decrements the components of the vector by one. </summary>

Vector3 operator -- (Vector3& value, int)
{
	Vector3 result = value;

	--value.X;
	--value.Y;
	--value.Z;

	return result;
}

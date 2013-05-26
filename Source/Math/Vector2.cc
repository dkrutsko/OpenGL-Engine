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
// Constants                                                          Vector2 //
//----------------------------------------------------------------------------//

const Vector2 Vector2::One		= Vector2 (1, 1);
const Vector2 Vector2::Zero		= Vector2 (0, 0);

const Vector2 Vector2::UnitX	= Vector2 (1, 0);
const Vector2 Vector2::UnitY	= Vector2 (0, 1);



//----------------------------------------------------------------------------//
// Constructors                                                       Vector2 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="value"> Value to initialize both components to. </param>

Vector2::Vector2 (float x, float y)
{
	X = x;
	Y = y;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="x"> Initial value for the x component. </param>
/// <param name="y"> Initial value for the y component. </param>

Vector2::Vector2 (float value)
{
	X = value;
	Y = value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Vector2::Vector2 (const Vector3& value)
{
	X = value.X;
	Y = value.Y;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Vector2::Vector2 (const Vector4& value)
{
	X = value.X;
	Y = value.Y;
}



//----------------------------------------------------------------------------//
// Methods                                                            Vector2 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this vector. </summary>

float Vector2::Length (void) const
{
	return Math::Sqrt ((X * X) + (Y * Y));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the length of this vector squared. </summary>

float Vector2::LengthSquared (void) const
{
	return (X * X) + (Y * Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Turns the current vector into a unit vector. The result is a vector,
/// one unit in length, pointing in the same direction as the original. 
/// </summary>

void Vector2::Normalize (void)
{
	float magnitude = 1 / Math::Sqrt ((X * X) + (Y * Y));

	X *= magnitude;
	Y *= magnitude;
}



//----------------------------------------------------------------------------//
// Static                                                             Vector2 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Calculates the dot product of two vectors. If the two vectors are
/// unit vectors, the dot product returns a floating point value between
/// 1 and -1 that can be used to determine some properties of the angle
/// between two vectors. For example, it can show whether the vectors are
/// orthogonal, parallel, or have an acute or obtuse angle between them. 
/// </summary>

float Vector2::Dot (const Vector2& value1, const Vector2& value2)
{
	return (value1.X * value2.X) + (value1.Y * value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a vector that contains the lowest value from each component. 
/// </summary>

Vector2 Vector2::Min (const Vector2& value1, const Vector2& value2)
{
	return Vector2 ((value1.X < value2.X) ? value1.X : value2.X,
					(value1.Y < value2.Y) ? value1.Y : value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a vector that contains the highest value from each component.
/// </summary>

Vector2 Vector2::Max (const Vector2& value1, const Vector2& value2)
{
	return Vector2 ((value1.X > value2.X) ? value1.X : value2.X,
					(value1.Y > value2.Y) ? value1.Y : value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two vectors. </summary>

float Vector2::Distance (const Vector2& value1, const Vector2& value2)
{
	float dx = value1.X - value2.X;
	float dy = value1.Y - value2.Y;

	return Math::Sqrt ((dx * dx) + (dy * dy));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates the distance between two vectors squared. </summary>

float Vector2::DistanceSquared (const Vector2& value1, const Vector2& value2)
{
	float dx = value1.X - value2.X;
	float dy = value1.Y - value2.Y;

	return (dx * dx) + (dy * dy);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Creates a unit vector from the specified vector. The result is a vector,
/// one unit in length, pointing in the same direction as the original.
/// </summary>

Vector2 Vector2::Normalize (const Vector2& value)
{
	float magnitude = 1 / Math::Sqrt ((value.X * value.X) +
									  (value.Y * value.Y));

	return Vector2 (value.X * magnitude,
					value.Y * magnitude);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Restricts each component within a specified range. </summary>
/// <param name="value"> The vector to clamp. </param>
/// <param name="min"> The minimum value. </param>
/// <param name="max"> The maximum value. </param>

Vector2 Vector2::Clamp (const Vector2& value, const Vector2& min, const Vector2& max)
{
	float x = value.X;
	x = (x > max.X) ? max.X : x;
	x = (x < min.X) ? min.X : x;

	float y = value.Y;
	y = (y > max.Y) ? max.Y : y;
	y = (y < min.Y) ? min.Y : y;

	return Vector2 (x, y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Determines a reflection vector based on the normal. </summary>
/// <param name="value"> The vector to reflect. </param>
/// <param name="normal"> The normal to reflect against. </param>

Vector2 Vector2::Reflect (const Vector2& value, const Vector2& normal)
{
	float dot = (value.X * normal.X) +
				(value.Y * normal.Y);

	return Vector2 (value.X - (2 * dot * normal.X),
					value.Y - (2 * dot * normal.Y));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a linear interpolation between two vectors. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

Vector2 Vector2::Lerp (const Vector2& value1, const Vector2& value2, float amount)
{
	return Vector2
	(
		value1.X + ((value2.X - value1.X) * amount),
		value1.Y + ((value2.Y - value1.Y) * amount)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Interpolates between two values using a cubic equation. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

Vector2 Vector2::SmoothStep (const Vector2& value1, const Vector2& value2, float amount)
{
	amount = (amount * amount) * (3 - (2 * amount));

	return Vector2
	(
		value1.X + ((value2.X - value1.X) * amount),
		value1.Y + ((value2.Y - value1.Y) * amount)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Returns a Vector2 containing the 2D Cartesian coordinates of a point
/// specified in barycentric coordinates relative to a 2D triangle. 
/// </summary>
/// <param name="value1"> The First vertex of the triangle. </param>
/// <param name="value2"> The Second vertex of the triangle. </param>
/// <param name="value3"> The Third vertex of the triangle. </param>
/// <param name="amount1"> The weighting factor toward vertex 2. </param>
/// <param name="amount2"> The weighting factor toward vertex 3. </param>

Vector2 Vector2::Barycentric (const Vector2& value1,
							  const Vector2& value2,
							  const Vector2& value3, float amount1, float amount2)
{
	return Vector2
	(
		value1.X + (amount1 * (value2.X - value1.X)) + (amount2 * (value3.X - value1.X)),
		value1.Y + (amount1 * (value2.Y - value1.Y)) + (amount2 * (value3.Y - value1.Y))
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

Vector2 Vector2::CatmullRom (const Vector2& value1, const Vector2& value2,
							 const Vector2& value3, const Vector2& value4, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	return Vector2
	(
		0.5 * ((2 * value2.X) + ((-value1.X + value3.X) * amount) +
			(((2 * value1.X) - (5 * value2.X) + (4 * value3.X) - value4.X) * amountSq) +
			((-value1.X + (3 * value2.X) - (3 * value3.X) + value4.X) * amountCu)),

		0.5 * ((2 * value2.Y) + ((-value1.Y + value3.Y) * amount) +
			(((2 * value1.Y) - (5 * value2.Y) + (4 * value3.Y) - value4.Y) * amountSq) +
			((-value1.Y + (3 * value2.Y) - (3 * value3.Y) + value4.Y) * amountCu))
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a Hermite spline interpolation. </summary>
/// <param name="amount"> The weighting factor. </param>

Vector2 Vector2::Hermite (const Vector2& value1, const Vector2& tangent1,
						  const Vector2& value2, const Vector2& tangent2, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	float v1 = ( 2 * amountCu) - (3 * amountSq) + 1;
	float v2 = (-2 * amountCu) + (3 * amountSq);
	float v3 = amountCu - (2 * amountSq) + amount;
	float v4 = amountCu - amountSq;

	return Vector2
	(
		(value1.X * v1) + (value2.X * v2) + (tangent1.X * v3) + (tangent2.X * v4),
		(value1.Y * v1) + (value2.Y * v2) + (tangent1.Y * v3) + (tangent2.Y * v4)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms the vector (x, y, 0, 1) by the specified matrix. </summary>
/// <param name="position"> The vector to transform </param>
/// <param name="matrix"> The transformation Matrix. </param>

Vector2 Vector2::Transform (const Vector2& position, const Matrix& matrix)
{
	return Vector2
	(
		(position.X * matrix.M11) + (position.Y * matrix.M21) + matrix.M41,
		(position.X * matrix.M12) + (position.Y * matrix.M22) + matrix.M42
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a single Vector2, or the vector normal
/// 		  (x, y, 0, 0), by a specified Quaternion rotation. </summary>
/// 
/// <param name="value">    The vector to rotate. </param>
/// <param name="rotation"> The Quaternion rotation to apply. </param>

Vector2 Vector2::Transform (const Vector2& position, const Quaternion& rotation)
{
	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float yy = rotation.Y * y;
	float zz = rotation.Z * z;
	float wz = rotation.W * z;

	return Vector2
	(
		(position.X * (1 - yy - zz)) + (position.Y * (0 + xy - wz)),
		(position.X * (0 + xy + wz)) + (position.Y * (1 - xx - zz))
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a 2D vector normal by a matrix. </summary>
/// <param name="normal"> The normal to transform </param>
/// <param name="matrix"> The transformation Matrix. </param>

Vector2 Vector2::TransformNormal (const Vector2& normal, const Matrix& matrix)
{
	return Vector2
	(
		(normal.X * matrix.M11) + (normal.Y * matrix.M21),
		(normal.X * matrix.M12) + (normal.Y * matrix.M22)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms an array of Vector2s by a specified Matrix. </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector2s to transform. </param>
/// <param name="matrix"> The transform Matrix to apply. </param>
/// <param name="target"> The destination for results. </param>

void Vector2::Transform (quint32 length, const Vector2* source,
						 const Matrix& matrix, Vector2* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (quint32 i = 0; i < length; ++i)
	{
		float sx = source[i].X;
		float sy = source[i].Y;

		target[i].X = (sx * matrix.M11) + (sy * matrix.M21) + matrix.M41;
		target[i].Y = (sx * matrix.M12) + (sy * matrix.M22) + matrix.M42;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms an array of Vector2s by a specified Quaternion. </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector2s to transform. </param>
/// <param name="rotation"> The transform Quaternion to apply. </param>
/// <param name="target"> The destination for results. </param>

void Vector2::Transform (quint32 length, const Vector2* source,
						 const Quaternion& rotation, Vector2* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float wy = rotation.X * y;
	float yy = rotation.Y * y;
	float zz = rotation.Z * z;
	float wz = rotation.W * z;

	float v1 = 1 - yy - zz;
	float v2 = 0 + wy - wz;
	float v3 = 0 + wy + wz;
	float v4 = 1 - xx - zz;

	for (quint32 i = 0; i < length; ++i)
	{
		float sx = source[i].X;
		float sy = source[i].Y;

		target[i].X = (sx * v1) + (sy * v2);
		target[i].Y = (sx * v3) + (sy * v4);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms an array of Vector2s vector normals by a specified Matrix. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="source"> The array of Vector2s to transform. </param>
/// <param name="matrix"> The Matrix to transform by. </param>
/// <param name="target"> The destination for results. </param>

void Vector2::TransformNormal (quint32 length, const Vector2* source,
							   const Matrix& matrix, Vector2* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (quint32 i = 0; i < length; ++i)
	{
		float sx = source[i].X;
		float sy = source[i].Y;

		target[i].X = (sx * matrix.M11) + (sy * matrix.M21);
		target[i].Y = (sx * matrix.M12) + (sy * matrix.M22);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector2s by a specified
/// Matrix and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector2s to transform. </param>
/// <param name="matrix"> The Matrix to transform by. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector2::Transform (quint32 length, quint32 sourceIndex, const Vector2* source,
						 const Matrix& matrix, quint32 targetIndex, Vector2* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (length; length > 0; --length, ++sourceIndex, ++targetIndex)
	{
		float sx = source[sourceIndex].X;
		float sy = source[sourceIndex].Y;

		target[targetIndex].X = (sx * matrix.M11) + (sy * matrix.M21) + matrix.M41;
		target[targetIndex].Y = (sx * matrix.M12) + (sy * matrix.M22) + matrix.M42;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector2s by a specified
/// Quaternion and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector2s to transform. </param>
/// <param name="rotation"> The Quaternion rotation to apply. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector2::Transform (quint32 length, quint32 sourceIndex, const Vector2* source,
						 const Quaternion& rotation, quint32 targetIndex, Vector2* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float yy = rotation.Y * y;
	float zz = rotation.Z * z;
	float wz = rotation.W * z;

	float v1 = 1 - yy - zz;
	float v2 = 0 + xy - wz;
	float v3 = 0 + xy + wz;
	float v4 = 1 - xx - zz;

	for (length; length > 0; --length, ++sourceIndex, ++targetIndex)
	{
		float sx = source[sourceIndex].X;
		float sy = source[sourceIndex].Y;

		target[targetIndex].X = (sx * v1) + (sy * v2);
		target[targetIndex].Y = (sx * v3) + (sy * v4);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Transforms a specified range in an array of Vector2s vector normals by a
/// specified Matrix and places the results in a specified range in a destination. 
/// </summary>
/// <param name="length"> The length of the array to transform. </param>
/// <param name="sourceIndex"> The starting index in source. </param>
/// <param name="source"> The array of Vector2s to transform. </param>
/// <param name="matrix"> The Matrix to transform by. </param>
/// <param name="targetIndex"> The starting index in target. </param>
/// <param name="target"> The destination for results. </param>

void Vector2::TransformNormal (quint32 length, quint32 sourceIndex, const Vector2* source,
							   const Matrix& matrix, quint32 targetIndex, Vector2* target)
{
	if (source == nullptr ||
		target == nullptr) return;

	for (length; length > 0; --length, ++sourceIndex, ++targetIndex)
	{
		float sx = source[sourceIndex].X;
		float sy = source[sourceIndex].Y;

		target[targetIndex].X = (sx * matrix.M11) + (sy * matrix.M21);
		target[targetIndex].Y = (sx * matrix.M12) + (sy * matrix.M22);
	}
}



//----------------------------------------------------------------------------//
// Operators                                                          Vector2 //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one vector to another. </summary>

Vector2& operator += (Vector2& value1, const Vector2& value2)
{
	value1.X += value2.X;
	value1.Y += value2.Y;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one vector from another. </summary>

Vector2& operator -= (Vector2& value1, const Vector2& value2)
{
	value1.X -= value2.X;
	value1.Y -= value2.Y;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of two vectors by each other. </summary>

Vector2& operator *= (Vector2& value1, const Vector2& value2)
{
	value1.X *= value2.X;
	value1.Y *= value2.Y;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two vectors against each other. </summary>

Vector2& operator /= (Vector2& value1, const Vector2& value2)
{
	value1.X /= value2.X;
	value1.Y /= value2.Y;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector2& operator += (Vector2& value1, float value2)
{
	value1.X += value2;
	value1.Y += value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector2& operator -= (Vector2& value1, float value2)
{
	value1.X -= value2;
	value1.Y -= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector2& operator *= (Vector2& value1, float value2)
{
	value1.X *= value2;
	value1.Y *= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector2& operator /= (Vector2& value1, float value2)
{
	value1.X /= value2;
	value1.Y /= value2;

	return value1;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds one vector to another. </summary>


Vector2 operator + (const Vector2& value1, const Vector2& value2)
{
	return Vector2 (value1.X + value2.X,
					value1.Y + value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts one vector from another. </summary>

Vector2 operator - (const Vector2& value1, const Vector2& value2)
{
	return Vector2 (value1.X - value2.X,
					value1.Y - value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of two vectors by each other. </summary>

Vector2 operator * (const Vector2& value1, const Vector2& value2)
{
	return Vector2 (value1.X * value2.X,
					value1.Y * value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of two vectors against each other. </summary>

Vector2 operator / (const Vector2& value1, const Vector2& value2)
{
	return Vector2 (value1.X / value2.X,
					value1.Y / value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector2 operator + (const Vector2& value1, float value2)
{
	return Vector2 (value1.X + value2,
					value1.Y + value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector2 operator - (const Vector2& value1, float value2)
{
	return Vector2 (value1.X - value2,
					value1.Y - value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector2 operator * (const Vector2& value1, float value2)
{
	return Vector2 (value1.X * value2,
					value1.Y * value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector2 operator / (const Vector2& value1, float value2)
{
	return Vector2 (value1.X / value2,
					value1.Y / value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Adds the components of a vector by a scalar. </summary>

Vector2 operator + (float value1, const Vector2& value2)
{
	return Vector2 (value1 + value2.X,
					value1 + value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Subtracts the components of a vector by a scalar. </summary>

Vector2 operator - (float value1, const Vector2& value2)
{
	return Vector2 (value1 - value2.X,
					value1 - value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Multiplies the components of a vector by a scalar. </summary>

Vector2 operator * (float value1, const Vector2& value2)
{
	return Vector2 (value1 * value2.X,
					value1 * value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Divides the components of a vector by a scalar. </summary>

Vector2 operator / (float value1, const Vector2& value2)
{
	return Vector2 (value1 / value2.X,
					value1 / value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two vectors for equality. </summary>

bool operator == (const Vector2& value1, const Vector2& value2)
{
	return value1.X == value2.X &&
		   value1.Y == value2.Y;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two vectors for inequality. </summary>

bool operator != (const Vector2& value1, const Vector2& value2)
{
	return value1.X != value2.X ||
		   value1.Y != value2.Y;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically less than another.
/// </summary>

bool operator < (const Vector2& value1, const Vector2& value2)
{
	return (value1.X <  value2.X) ||(value1.X == value2.X && value1.Y <  value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically less than or equal to another. 
/// </summary>

bool operator <= (const Vector2& value1, const Vector2& value2)
{
	return (value1.X <= value2.X) ||(value1.X == value2.X && value1.Y <= value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically greater than another.
/// </summary>

bool operator > (const Vector2& value1, const Vector2& value2)
{
	return (value1.X >  value2.X) ||(value1.X == value2.X && value1.Y >  value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Tests whether one vector is lexicographically greater than or equal to another. 
/// </summary>

bool operator >= (const Vector2& value1, const Vector2& value2)
{
	return (value1.X >= value2.X) ||(value1.X == value2.X && value1.Y >= value2.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a vector pointing in the opposite direction. </summary>

Vector2 operator - (const Vector2& value)
{
	return Vector2 (-value.X, -value.Y);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Pre-increments the components of the vector by one. </summary>

Vector2& operator ++ (Vector2& value)
{
	++value.X;
	++value.Y;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Pre-decrements the components of the vector by one. </summary>

Vector2& operator -- (Vector2& value)
{
	--value.X;
	--value.Y;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Post-increments the components of the vector by one. </summary>

Vector2 operator ++ (Vector2& value, int)
{
	Vector2 result = value;

	++value.X;
	++value.Y;

	return result;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Post-decrements the components of the vector by one. </summary>

Vector2 operator -- (Vector2& value, int)
{
	Vector2 result = value;

	--value.X;
	--value.Y;

	return result;
}

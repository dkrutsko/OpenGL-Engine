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
#include "Math/Plane.h"
#include "Math/Matrix.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"



//----------------------------------------------------------------------------//
// Constructors                                                         Plane //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="value"> Vector4 with X, Y and Z components defining the normal
/// 					 of the Plane. The W component defines the distance of
/// 					 the Plane along the normal from the origin. </param>

Plane::Plane (const Vector4& value)
{
	Normal.X = value.X;
	Normal.Y = value.Y;
	Normal.Z = value.Z;
	Distance = value.W;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="point1"> One point of a triangle defining the Plane. </param>
/// <param name="point2"> One point of a triangle defining the Plane. </param>
/// <param name="point3"> One point of a triangle defining the Plane. </param>

Plane::Plane (const Vector3& point1, const Vector3& point2, const Vector3& point3)
{
	float x1 = point2.X - point1.X;
	float y1 = point2.Y - point1.Y;
	float z1 = point2.Z - point1.Z;
	float x2 = point3.X - point1.X;
	float y2 = point3.Y - point1.Y;
	float z2 = point3.Z - point1.Z;

	float x = (y1 * z2) - (z1 * y2);
	float y = (z1 * x2) - (x1 * z2);
	float z = (x1 * y2) - (y1 * x2);

	float magnitude = 1 / Math::Sqrt
		((x * x) + (y * y) + (z * z));

	Normal.X = x * magnitude;
	Normal.Y = y * magnitude;
	Normal.Z = z * magnitude;

	Distance = -((Normal.X * point1.X) +
				 (Normal.Y * point1.Y) +
				 (Normal.Z * point1.Z));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="x"> X component of the normal defining the Plane. </param>
/// <param name="y"> Y component of the normal defining the Plane. </param>
/// <param name="z"> Z component of the normal defining the Plane. </param>
/// <param name="distance"> Distance of the Plane along its normal from the origin. </param>

Plane::Plane (float x, float y, float z, float distance)
{
	Normal.X = x;
	Normal.Y = y;
	Normal.Z = z;
	Distance = distance;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <param name="normal">   Normal vector to the Plane. </param>
/// <param name="distance"> Distance along the plane's normal from the origin. </param>

Plane::Plane (const Vector3& normal, float distance)
{
	Normal.X = normal.X;
	Normal.Y = normal.Y;
	Normal.Z = normal.Z;
	Distance = distance;
}



//----------------------------------------------------------------------------//
// Methods                                                              Plane //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Calculates the dot product of a specified Vector4 and this Plane.
/// </summary>

float Plane::Dot (const Vector4& value)
{
	return (Normal.X * value.X) +
		   (Normal.Y * value.Y) +
		   (Normal.Z * value.Z) +
		   (Distance * value.W);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the dot product of a specified Vector3 and the Normal
/// vector of this Plane plus the D constant value of the Plane.
/// </summary>

float Plane::DotCoordinate (const Vector3& value)
{
	return (Normal.X * value.X) +
		   (Normal.Y * value.Y) +
		   (Normal.Z * value.Z) + Distance;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the dot product of a specified Vector3
/// 		  and the Normal vector of this Plane. </summary>

float Plane::DotNormal (const Vector3& value)
{
	return (Normal.X * value.X) +
		   (Normal.Y * value.Y) +
		   (Normal.Z * value.Z);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Changes the coefficients of the Normal vector
/// 		  of this Plane to make it of unit length. </summary>

void Plane::Normalize (void)
{
	float magnitude = (Normal.X * Normal.X) +
					  (Normal.Y * Normal.Y) +
					  (Normal.Z * Normal.Z);

	if (Math::Abs (magnitude - 1) >= 1.192093E-07f)
	{
		float d = 1 / Math::Sqrt (magnitude);

		Normal.X *= d;
		Normal.Y *= d;
		Normal.Z *= d;
		Distance *= d;
	}
}



//----------------------------------------------------------------------------//
// Static                                                               Plane //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Changes the coefficients of the Normal vector
/// 		  of a Plane to make it of unit length. </summary>

Plane Plane::Normalize (const Plane& value)
{
	float magnitude = (value.Normal.X * value.Normal.X) +
					  (value.Normal.Y * value.Normal.Y) +
					  (value.Normal.Z * value.Normal.Z);

	if (Math::Abs (magnitude - 1) < 1.192093E-07f)
		return value;

	float d = 1 / Math::Sqrt (magnitude);
	return Plane (value.Normal.X * d,
				  value.Normal.Y * d,
				  value.Normal.Z * d,
				  value.Distance * d);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a normalized Plane by a Matrix. </summary>
/// 
/// <param name="plane">
/// The normalized Plane to transform. This Plane must already be normalized,
/// so that its Normal vector is of unit length, before this method is called.
/// </param>
/// <param name="matrix"> The transform Matrix to apply to the Plane. </param>

Plane Plane::Transform (const Plane& plane, const Matrix& matrix)
{
	Matrix inverted = Matrix::Invert (matrix);

	return Plane
	(
		(plane.Normal.X * inverted.M11) +
		(plane.Normal.Y * inverted.M12) +
		(plane.Normal.Z * inverted.M13) +
		(plane.Distance * inverted.M14),

		(plane.Normal.X * inverted.M21) +
		(plane.Normal.Y * inverted.M22) +
		(plane.Normal.Z * inverted.M23) +
		(plane.Distance * inverted.M24),

		(plane.Normal.X * inverted.M31) +
		(plane.Normal.Y * inverted.M32) +
		(plane.Normal.Z * inverted.M33) +
		(plane.Distance * inverted.M34),

		(plane.Normal.X * inverted.M41) +
		(plane.Normal.Y * inverted.M42) +
		(plane.Normal.Z * inverted.M43) +
		(plane.Distance * inverted.M44)
	);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Transforms a normalized Plane by a Quaternion rotation. </summary>
/// 
/// <param name="plane">
/// The normalized Plane to transform. This Plane must already be normalized,
/// so that its Normal vector is of unit length, before this method is called.
/// </param>
/// <param name="rotation"> The Quaternion rotation to apply to the Plane. </param>

Plane Plane::Transform (const Plane& plane, const Quaternion& rotation)
{
	float x = rotation.X + rotation.X;
	float y = rotation.Y + rotation.Y;
	float z = rotation.Z + rotation.Z;

	float wx = rotation.W * x;
	float wy = rotation.W * y;
	float wz = rotation.W * z;
	float xx = rotation.X * x;
	float xy = rotation.X * y;
	float xz = rotation.X * z;
	float yy = rotation.Y * y;
	float yz = rotation.Y * z;
	float zz = rotation.Z * z;

	return Plane
	(
		(plane.Normal.X * (1 - yy - zz)) +
		(plane.Normal.Y * (0 + xy - wz)) +
		(plane.Normal.Z * (0 + xz + wy)),

		(plane.Normal.X * (0 + xy + wz)) +
		(plane.Normal.Y * (1 - xx - zz)) +
		(plane.Normal.Z * (0 + yz - wx)),

		(plane.Normal.X * (0 + xz - wy)) +
		(plane.Normal.Y * (0 + yz + wx)) +
		(plane.Normal.Z * (1 - xx - yy)),
		
		plane.Distance
	);
}



//----------------------------------------------------------------------------//
// Operators                                                            Plane //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two planes for equality. </summary>

bool operator == (const Plane& value1, const Plane& value2)
{
	return value1.Normal.X == value2.Normal.X &&
		   value1.Normal.Y == value2.Normal.Y &&
		   value1.Normal.Z == value2.Normal.Z &&
		   value1.Distance == value2.Distance;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Tests two planes for inequality. </summary>

bool operator != (const Plane& value1, const Plane& value2)
{
	return value1.Normal.X != value2.Normal.X ||
		   value1.Normal.Y != value2.Normal.Y ||
		   value1.Normal.Z != value2.Normal.Z ||
		   value1.Distance != value2.Distance;
}

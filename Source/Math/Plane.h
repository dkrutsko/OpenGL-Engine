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

#ifndef MATH_PLANE_H
#define MATH_PLANE_H

class Matrix;
class Vector4;
class Quaternion;

#include "Math/Vector3.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Represents a plane using a Vector3 normal and a distance. </summary>
/// <remarks> The distance value is stored as a negative value. </remarks>

class Plane
{
public:
	// Constructors
	explicit Plane					(void) { }

	explicit Plane					(const Vector4& value);
	explicit Plane					(const Vector3& point1,
									 const Vector3& point2,
									 const Vector3& point3);

	explicit Plane					(float x, float y, float z, float distance);
	explicit Plane					(const Vector3& normal, float distance);

public:
	// Methods
	float			Dot				(const Vector4& value);
	float			DotCoordinate	(const Vector3& value);
	float			DotNormal		(const Vector3& value);
	void			Normalize		(void);

public:
	// Static
	static Plane	Normalize		(const Plane& value);
	static Plane	Transform		(const Plane& plane, const Matrix& matrix);
	static Plane	Transform		(const Plane& plane, const Quaternion& rotation);

public:
	// Fields
	Vector3 Normal;	// Normal vector of the Plane
	float Distance;	// Distance of the Plane along its normal from the origin
};



//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//

bool operator == (const Plane& value1, const Plane& value2);
bool operator != (const Plane& value1, const Plane& value2);

#endif // MATH_PLANE_H

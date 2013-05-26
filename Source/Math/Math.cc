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
#include <cmath>



//----------------------------------------------------------------------------//
// Constants                                                             Math //
//----------------------------------------------------------------------------//

const float Math::Zero		= (float) 0;
const float Math::NaN		= (float) 0.0 / Math::Zero;
const float Math::Infinity	= (float) 1.0 / Math::Zero;

const float Math::E			= 2.7182818284590452f;
const float Math::Log10E	= 0.4342944819032518f;
const float Math::Log2E		= 1.4426950408889634f;

const float Math::Pi		= 3.1415926535897932f;
const float Math::PiOver2	= 1.5707963267948966f;
const float Math::PiOver4	= 0.7853981633974483f;
const float Math::TwoPi		= 6.2831853071795864f;

const float Math::Sqrt2		= 1.4142135623730950f;
const float Math::SqrtOver2	= 0.7071067811865475f;



//----------------------------------------------------------------------------//
// Static                                                                Math //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the absolute value of a specified number. </summary>

float Math::Abs (float value)
{
	return value < 0 ? -value : value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the smaller of two floating-point numbers. </summary>

float Math::Min (float value1, float value2)
{
	return value1 < value2 ? value1 : value2;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the larger of two floating-point numbers. </summary>

float Math::Max (float value1, float value2)
{
	return value1 > value2 ? value1 : value2;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the remainder from the specified floating-point division.
/// </summary>
/// <remarks> The result is always positive, not similar to Fmod. </remarks>

float Math::Mod (float dividend, float divisor)
{
	if (divisor == 0)
		return NaN;

	return dividend - divisor * floor (dividend / divisor);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the remainder from the specified floating-point division.
/// </summary>
/// <remarks> This function uses the built-in fmod operator. </remarks>

float Math::Fmod (float dividend, float divisor)
{
	return fmod (dividend, divisor);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the natural logarithm of a specified number. </summary>
/// <returns>
///
///				Value				Result
/// -----------------------------------------------------------------------
/// 			Positive			log_e (value)
/// 			Zero				-Infinity
/// 			Negative			NaN
/// 			NaN					Nan
/// 			Infinity			+Infinity
///
/// </returns>

float Math::Ln (float value)
{
	return log (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the base 10 logarithm of a specified number. </summary>
/// <returns>
///
///				Value				Result
/// -----------------------------------------------------------------------
/// 			Positive			log_10 (value)
/// 			Zero				-Infinity
/// 			Negative			NaN
/// 			NaN					Nan
/// 			Infinity			+Infinity
///
/// </returns>

float Math::Log (float value)
{
	return log10 (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the logarithm of a number in a specified base. </summary>
/// <returns>
///
///				Value		Base					Result
/// -----------------------------------------------------------------------
/// 			> Zero		(0, 1) (1, Infinity)	log_base (value)
/// 			< Zero		Any						NaN
/// 			Any			< Zero					NaN
/// 			Not One		Zero					NaN
/// 			Not One		+Infinity				NaN
/// 			NaN			Any						NaN
/// 			Any			NaN						NaN
/// 			Any			One						NaN
/// 			Zero		(0, 1)					+Infinity
/// 			Zero		(1, Infinity)			-Infinity
/// 			+Infinity	(0, 1)					-Infinity
/// 			+Infinity	(1, Infinity)			+Infinity
/// 			One			Zero					Zero
/// 			One			+Infinity				Zero
///
/// </returns>

float Math::Log (float value, float base)
{
	if (Type (value) == NaNType) return NaN;
	if (Type (base ) == NaNType) return NaN;

	if ((base != 1.0) && ((value == 1.0) ||
	   ((base != 0.0) && base != Infinity)))
		return log (value) / log (base);

	return NaN;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns e raised to the specified power. </summary>
/// <returns>
///
///				Power				Result
/// -----------------------------------------------------------------------
/// 			Number				e^Power
/// 			NaN					NaN
/// 			+Infinity			+Infinity
/// 			-Infinity			Zero
///
/// 	If the result is too large, +Infinity is returned
///
/// </returns>

float Math::Exp (float power)
{
	return exp (power);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the square root of a specified number. </summary>
/// <returns>
///
///				value				Result
/// -----------------------------------------------------------------------
/// 			Positive or Zero	Sqrt (Value)
/// 			Negative			NaN
/// 			NaN					NaN
/// 			+Infinity			+Infinity
///
/// </returns>

float Math::Sqrt (float value)
{
	return sqrt (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a number raised to the specified power. </summary>
/// <returns>
///
///				Value			Power				Result
/// -----------------------------------------------------------------------
/// 			Any				NaN					NaN
/// 			NaN				Any					NaN
/// 			Any				Zero				One
/// 			-Infinity		< Zero				Zero
/// 			-Infinity		Positive Odd		-Infinity
/// 			-Infinity		Positive Even		+Infinity
/// 			-One			InfinityType		NaN
/// 			(-1, 1)			-Infinity			+Infinity
/// 			(-1, 1)			+Infinity			Zero
/// 			> 1 or < -1		-Infinity			Zero
/// 			> 1 or < -1		+Infinity			+Infinity
/// 			Zero			< Zero				+Infinity
/// 			Zero			> Zero				Zero
/// 			One				Any					One
/// 			+Infinity		< Zero				Zero
/// 			+Infinity		> Zero				+Infinity
///
/// 		If the result is too large, +Infinity is returned
///
/// </returns>

float Math::Pow (float base, float power)
{
	return pow (base, power);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the sine of the specified angle. </summary>
/// <param name="value"> The angle, expressed in degrees. </param>

float Math::Sind (float value)
{
	return sin (value * 0.01745329f);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the cosine of the specified angle. </summary>
/// <param name="value"> The angle, expressed in degrees. </param>

float Math::Cosd (float value)
{
	return cos (value * 0.01745329f);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the tangent of the specified angle. </summary>
/// <param name="value"> The angle, expressed in degrees. </param>

float Math::Tand (float value)
{
	return tan (value * 0.01745329f);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the angle whose sine is the specified number. </summary>
/// <returns> The angle, in degrees, with an interval [-90, 90]. NaN is
/// 		  returned when the value is not in the interval [-1, 1]. </returns>

float Math::Asind (float value)
{
	return asin (value) * 57.2957795f;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the angle whose cosine is the specified number. </summary>
/// <returns> The angle, in degrees, with an interval [0, 180]. NaN is
/// 		  returned when the value is not in the interval [-1, 1]. </returns>

float Math::Acosd (float value)
{
	return acos (value) * 57.2957795f;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the angle whose tangent is the specified number. </summary>
/// <returns> The angle, in degrees, with an interval [-180, 180]. NaN is
/// 		  returned when the value is NaN. -90 if the value is equals
/// 		  -Infinity and 90 if the value is +Infinity. </returns>

float Math::Atand (float value)
{
	return atan (value) * 57.2957795f;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the angle whose tangent is the quotient of two specified numbers.
/// </summary>
/// <returns>
/// The resulting angle, in degrees, with an interval [-180, 180].
///
/// Quadrant 2: (  90, 180)   Quadrant 1: (  0, 90)
/// Quadrant 3: (-180, -90)   Quadrant 4: (-90,  0)
///
///    atan2 (>0,  0): 90       atan2 ( 0, >0): 0
///    atan2 ( 0, <0): 180      atan2 (<0,  0): -90
///
///    atan2 ( 0,  0): NaN
///
/// </returns>

float Math::Atan2d (float y, float x)
{
	return atan2 (y, x) * 57.2957795f;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the sine of the specified angle. </summary>
/// <param name="value"> The angle, expressed in radians. </param>

float Math::Sinr (float value)
{
	return sin (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the cosine of the specified angle. </summary>
/// <param name="value"> The angle, expressed in radians. </param>

float Math::Cosr (float value)
{
	return cos (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the tangent of the specified angle. </summary>
/// <param name="value"> The angle, expressed in radians. </param>

float Math::Tanr (float value)
{
	return tan (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the angle whose sine is the specified number. </summary>
/// <returns> The angle, in degrees, with an interval [-pi/2, pi/2]. NaN is
/// 		  returned when the value is not in the interval [-1, 1]. </returns>

float Math::Asinr (float value)
{
	return asin (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the angle whose cosine is the specified number. </summary>
/// <returns> The angle, in degrees, with an interval [0, pi]. NaN is
/// 		  returned when the value is not in the interval [-1, 1]. </returns>

float Math::Acosr (float value)
{
	return acos (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the angle whose tangent is the specified number. </summary>
/// <returns> The angle, in degrees, with an interval [-pi/2, pi/2]. NaN is
/// 		  returned when the value is NaN. -pi/2 if the value is equals
/// 		  -Infinity and pi/2 if the value is +Infinity. </returns>

float Math::Atanr (float value)
{
	return atan (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the angle whose tangent is the quotient of two specified numbers.
/// </summary>
/// <returns>
/// The resulting angle, in degrees, with an interval [-pi, pi].
///
/// Quadrant 2: (pi/2,    pi)   Quadrant 1: (    0, pi/2)
/// Quadrant 3: ( -pi, -pi/2)   Quadrant 4: (-pi/2,    0)
///
///    atan2 (>0,  0): pi/2       atan2 ( 0, >0): 0
///    atan2 ( 0, <0): pi         atan2 (<0,  0): -pi/2
///
///    atan2 ( 0,  0): NaN
///
/// </returns>

float Math::Atan2r (float y, float x)
{
	return atan2 (y, x);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Determines the classification of the specified number. </summary>
/// <returns>
/// Math::NaNType		when value is not a number.
/// Math::ZeroType		when value is zero.
/// Math::FiniteType	when value is a non-zero finite number.
/// Math::InfiniteType	when value is positive or negative infinity.
/// </returns>

Math::ValueType Math::Type (float value)
{
	volatile double v = value;

	if (v != value)
		return Math::NaNType;

	if (value ==  Math::Infinity ||
		value == -Math::Infinity)
		return Math::InfiniteType;

	if (value == 0)
		return Math::ZeroType;

	return Math::FiniteType;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the largest integer less than or equal
/// 		  to the specified floating-point number. </summary>

float Math::Floor (float value)
{
	return floor (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns the largest integer less than or equal
/// 		  to the specified floating-point number. </summary>

float Math::Ceiling (float value)
{
	return ceil (value);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Converts the value in radians to degrees. </summary>

float Math::ToDegrees (float radians)
{
	return radians * 57.2957795f;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Converts the value in degrees to radians. </summary>

float Math::ToRadians (float degrees)
{
	return degrees * 0.01745329f;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Reduces a given angle to a value between [-Pi, Pi] </summary>

float Math::WrapPI (float angle)
{
	return Mod (angle + Pi, TwoPi) - Pi;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Reduces a given angle to a value between [0, 2Pi] </summary>

float Math::WrapTwoPI (float angle)
{
	return Mod (angle, TwoPi);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Reduces a given angle to a value between [-180, 180] </summary>

float Math::Wrap180 (float angle)
{
	return Mod (angle + 180, 360) - 180;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Reduces a given angle to a value between [0, 360] </summary>

float Math::Wrap360 (float angle)
{
	return Mod (angle, 360);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Calculates the absolute value of the difference of two values.
/// </summary>

float Math::Distance (float value1, float value2)
{
	return Abs (value1 - value2);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Restricts a value to be within a specified range. </summary>
/// <param name="value"> The value to clamp. </param>
/// <param name="min"> The minimum value. </param>
/// <param name="max"> The maximum value. </param>

float Math::Clamp (float value, float min, float max)
{
	value = (value > max) ? max : value;
	value = (value < min) ? min : value;

	return value;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a linear interpolation between two values. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

float Math::Lerp (float value1, float value2, float amount)
{
	return value1 + ((value2 - value1) * amount);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Interpolates between two values using a cubic equation. </summary>
/// <param name="amount"> Value between 0 and 1 indicating the weight. </param>

float Math::SmoothStep (float value1, float value2, float amount)
{
	amount = (amount * amount) * (3 - (2 * amount));
	return value1 + ((value2 - value1) * amount);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the Cartesian coordinate for one axis of a point that
/// is defined by a given triangle and two normalized barycentric.
/// </summary>
/// <param name="value1"> The coordinate on one axis of vertex 1. </param>
/// <param name="value2"> The coordinate on the same axis of vertex 2. </param>
/// <param name="value3"> The coordinate on the same axis of vertex 3. </param>
/// <param name="amount1"> The normalized barycentric coordinate b2,
/// 					   equal to the weighting factor for vertex 2,
/// 					   the coordinate of which is specified in value2. </param>
/// <param name="amount2"> The normalized barycentric coordinate b3,
/// 					   equal to the weighting factor for vertex 3,
/// 					   the coordinate of which is specified in value3. </param>

float Math::Barycentric (float value1, float value2, float value3, float amount1, float amount2)
{
	return value1 + (amount1 * (value2 - value1)) + (amount2 * (value3 - value1));
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

float Math::CatmullRom (float value1, float value2, float value3, float value4, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	return 0.5 * ((2 * value2) + ((-value1 + value3) * amount) +
		(((2 * value1) - (5 * value2) + (4 * value3) - value4) * amountSq) +
		((-value1 + (3 * value2) - (3 * value3) + value4) * amountCu));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Performs a Hermite spline interpolation. </summary>
/// <param name="amount"> The weighting factor. </param>

float Math::Hermite (float value1, float tangent1, float value2, float tangent2, float amount)
{
	float amountSq = amount * amount;
	float amountCu = amount * amountSq;

	float v1 = ( 2 * amountCu) - (3 * amountSq) + 1;
	float v2 = (-2 * amountCu) + (3 * amountSq);
	float v3 = amountCu - (2 * amountSq) + amount;
	float v4 = amountCu - amountSq;

	return (value1 * v1) + (value2 * v2) + (tangent1 * v3) + (tangent2 * v4);
}

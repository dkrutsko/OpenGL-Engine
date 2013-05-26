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

#ifndef MATH_H
#define MATH_H

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Math
{
public:
	// Enumerations
	////////////////////////////////////////////////////////////////////////////////
	/// <summary> Specifies the number type. See Math::type (value). </summary>

	enum ValueType
	{
		////////////////////////////////////////////////////////////////////////////////
		/// <summary> The number is not a number. </summary>

		NaNType,

		////////////////////////////////////////////////////////////////////////////////
		/// <summary> The number is zero. </summary>

		ZeroType,

		////////////////////////////////////////////////////////////////////////////////
		/// <summary> The number is a non-zero finite number. </summary>

		FiniteType,

		////////////////////////////////////////////////////////////////////////////////
		/// <summary> The number is either positive or negative infinity. </summary>

		InfiniteType,
	};

public:
	// Constants
	static const float NaN;			// Represents not a number
	static const float Zero;		// Represents the value of Zero
	static const float Infinity;	// Represents the value of Infinity

	static const float E;			// Represents the mathematical constant e
	static const float Log10E;		// Represents the log base ten of e
	static const float Log2E;		// Represents the log base two of e

	static const float Pi;			// Represents the value of pi
	static const float PiOver2;		// Represents the value of pi divided by two
	static const float PiOver4;		// Represents the value of pi divided by four
	static const float TwoPi;		// Represents the value of pi times two

	static const float Sqrt2;		// Represents the value of   Sqrt(2)
	static const float SqrtOver2;	// Represents the value of 1/Sqrt(2)

private:
	// Constructors
	 Math							(void) { }
	 Math							(const Math &math) { }
	~Math							(void) { }

public:
	// Static
	static float Abs				(float value);
	static float Min				(float value1, float value2);
	static float Max				(float value1, float value2);
	static float Mod				(float dividend, float divisor);
	static float Fmod				(float dividend, float divisor);

	static float Ln					(float value);
	static float Log				(float value);
	static float Log				(float value, float base);
	static float Exp				(float power);
	static float Sqrt				(float value);
	static float Pow				(float base, float power);

	static float Sind				(float value);
	static float Cosd				(float value);
	static float Tand				(float value);

	static float Asind				(float value);
	static float Acosd				(float value);
	static float Atand				(float value);
	static float Atan2d				(float y, float x);

	static float Sinr				(float value);
	static float Cosr				(float value);
	static float Tanr				(float value);

	static float Asinr				(float value);
	static float Acosr				(float value);
	static float Atanr				(float value);
	static float Atan2r				(float y, float x);

	static ValueType Type			(float value);

	static float Floor				(float value);
	static float Ceiling			(float value);

	static float ToDegrees			(float radians);
	static float ToRadians			(float degrees);

	static float WrapPI				(float angle);
	static float WrapTwoPI			(float angle);
	static float Wrap180			(float angle);
	static float Wrap360			(float angle);

	static float Distance			(float value1, float value2);
	static float Clamp				(float value, float min, float max);

	static float Lerp				(float value1, float value2, float amount);
	static float SmoothStep			(float value1, float value2, float amount);
	static float Barycentric		(float value1, float value2, float value3, float amount1, float amount2);
	static float CatmullRom			(float value1, float value2, float value3, float value4, float amount);
	static float Hermite			(float value1, float tangent1, float value2, float tangent2, float amount);
};

#endif // MATH_H

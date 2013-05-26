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
#include "Math/Random.h"

#include <ctime>



//----------------------------------------------------------------------------//
// Constants                                                           Random //
//----------------------------------------------------------------------------//

const float Random::mFraction = 1.0f / 4294967295.0f;



//----------------------------------------------------------------------------//
// Constructors                                                        Random //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <remarks> Initialized with a time-dependent seed value. </remarks>

Random::Random (void)
{
	time_t seed = time (0);

	mIndex = 0;
	mState[ 0] = 2312041575 ^ seed;
	mState[ 1] = 3734761002 ^ seed;
	mState[ 2] = 4098595805 ^ seed;
	mState[ 3] = 2898172478 ^ seed;
	mState[ 4] = 1670301354 ^ seed;
	mState[ 5] = 3184133243 ^ seed;
	mState[ 6] = 1124276008 ^ seed;
	mState[ 7] = 4112360972 ^ seed;
	mState[ 8] = 3497678976 ^ seed;
	mState[ 9] = 1922789203 ^ seed;
	mState[10] = 2610629304 ^ seed;
	mState[11] = 4012872102 ^ seed;
	mState[12] = 1338179175 ^ seed;
	mState[13] = 4280637381 ^ seed;
	mState[14] = 3234121123 ^ seed;
	mState[15] = 2180492442 ^ seed;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a new instance of this class. </summary>
/// <remarks> Initialized with up to sixteen seed values. </remarks>

Random::Random (quint32 length, quint32* seed)
{
	mIndex = 0;
	mState[ 0] = 2312041575;
	mState[ 1] = 3734761002;
	mState[ 2] = 4098595805;
	mState[ 3] = 2898172478;
	mState[ 4] = 1670301354;
	mState[ 5] = 3184133243;
	mState[ 6] = 1124276008;
	mState[ 7] = 4112360972;
	mState[ 8] = 3497678976;
	mState[ 9] = 1922789203;
	mState[10] = 2610629304;
	mState[11] = 4012872102;
	mState[12] = 1338179175;
	mState[13] = 4280637381;
	mState[14] = 3234121123;
	mState[15] = 2180492442;

	for (quint32 i = 0; i < length && i < 16; ++i)
		mState[i] = seed[i];
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Creates a copy of the specified random class. </summary>

Random::Random (const Random& random)
{
	mIndex = random.mIndex;

	mState[ 0] = random.mState[ 0];
	mState[ 1] = random.mState[ 1];
	mState[ 2] = random.mState[ 2];
	mState[ 3] = random.mState[ 3];
	mState[ 4] = random.mState[ 4];
	mState[ 5] = random.mState[ 5];
	mState[ 6] = random.mState[ 6];
	mState[ 7] = random.mState[ 7];
	mState[ 8] = random.mState[ 8];
	mState[ 9] = random.mState[ 9];
	mState[10] = random.mState[10];
	mState[11] = random.mState[11];
	mState[12] = random.mState[12];
	mState[13] = random.mState[13];
	mState[14] = random.mState[14];
	mState[15] = random.mState[15];
}



//----------------------------------------------------------------------------//
// Methods                                                             Random //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a pseudo-random unsigned integer. </summary>

quint32 Random::NextInt (void)
{
	quint32 a, b, c, d;

	a = mState[mIndex];
	c = mState[(mIndex + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = mState[(mIndex + 9) & 15];

	c ^= (c >> 11);

	a = mState[mIndex] = b ^ c; 
	d = a ^ ((a << 5) & 0xDA442D24);

	mIndex = (mIndex + 15) & 15;

	a = mState[mIndex];
	mState[mIndex] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

	return mState[mIndex];
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a pseudo-random unsigned integer. </summary>
/// <remarks> The resulting value is in the range [min, max). If min
/// 		  is greater than or equal to max, min is returned. </remarks>

quint32 Random::NextInt (quint32 min, quint32 max)
{
	if (min >= max)
		return min;

	return (NextInt() % (max - min)) + min;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a pseudo-random unsigned integer. </summary>
/// <remarks> The resulting value is in the range [0, max). </remarks>

quint32 Random::NextInt (quint32 max)
{
	return NextInt() % max;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a pseudo-random boolean value. </summary>

bool Random::NextBool (void)
{
	return NextInt() % 2 == 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns a pseudo-random floating point value. </summary>
/// <remarks> The resulting value is in the range [0, 1]. </remarks>

float Random::NextReal (void)
{
	return NextInt() * mFraction;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Fills the specified buffer with random values. </summary>
/// <param name="length"> The length of the buffer to fill. </param>

void Random::NextBytes (quint32 length, quint8* buffer)
{
	if (buffer != nullptr)
	{
		for (quint32 i = 0; i < length; ++i)
			buffer[i] = (quint8) NextInt() % 256;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Fills the specified buffer with random values. </summary>
/// <param name="index">  The starting index of the buffer. </param>
/// <param name="length"> The length of the buffer to fill. </param>

void Random::NextBytes (quint32 length, quint32 index, quint8* buffer)
{
	if (buffer != nullptr && length >= length + index)
	{
		for (length; length > 0; --length, ++index)
			buffer[index] = (quint8) NextInt() % 256;
	}
}

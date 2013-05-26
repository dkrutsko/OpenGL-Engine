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

#ifndef MATH_RANDOM_H
#define MATH_RANDOM_H

#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Represents a pseudo-random number generator. </summary>
/// 
/// <remarks>
/// Pseudo-random numbers are generated using the WELL algorithm
/// created by F. Panneton, P. L'Ecuyer and M. Matsumoto. The
/// implementation in this class has a period of 2^512 - 1 and
/// passes the Diehard Tests. More information can be found here:
/// www.iro.umontreal.ca/~panneton/WELLRNG.html.
/// 
/// This class can be initialized with up to sixteen seed values
/// representing the internal state of the generator. Values left
/// uninitialized will be replaced by predetermined constants. This
/// ensures that two instances of this class yield the same values
/// given their seed was the same. If no seed was provided, a time
/// dependent value will be used.
/// 
/// Pseudo-random values are generated using an optimized method
/// created by Chris Lomont. This method is about forty percent
/// faster than the reference. More information can be found here:
/// www.lomont.org/Math/Papers/2008/Lomont_PRNG_2008.pdf.
/// </remarks>

class Random
{
public:
	// Constructors
	Random							(void);
	Random							(quint32 length, quint32* seed);
	Random							(const Random& random);

public:
	// Methods
	virtual quint32		NextInt		(void);
	virtual quint32		NextInt		(quint32 min, quint32 max);
	virtual quint32		NextInt		(quint32 max);

	virtual bool		NextBool	(void);
	virtual float		NextReal	(void);

	virtual void		NextBytes	(quint32 length, quint8* buffer);
	virtual void		NextBytes	(quint32 length, quint32 index, quint8* buffer);

protected:
	// Fields
	quint32	mState[16];	// Generator state
	quint32	mIndex;		// Index of state

	// (1 / MAX_UINT32)
	static const float mFraction;
};

#endif // MATH_RANDOM_H

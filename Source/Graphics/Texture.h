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

#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

class Mesh;
class Color;

#include "Content/Asset.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Texture : public Asset
{
	ASSET_DECLARATION;

public:
	// Constructors
	Texture (void);
	Texture (const Texture& texture);

protected:
	virtual ~Texture (void);

public:
	// Methods
	quint16		GetWidth		(void) const { return mWidth;		}
	quint16		GetHeight		(void) const { return mHeight;		}
	quint8		GetDepth		(void) const { return mDepth;		}

	quint32		GetTexID		(void) const { return mTexID;		}
	quint64		GetDataLength	(void) const { return mDataLength;	}
	quint8*		GetData			(void) const { return mData;		}

	Color		GetPixel		(quint16 x, quint16 y);
	bool		SetPixel		(quint16 x, quint16 y, const Color& color);

	bool		Load			(void);
	bool		Reload			(bool force = false);
	void		Unload			(bool force = false);

	void		Purge			(bool force = false);

	bool		IsLoaded		(void) const { return mTexID != 0;		}
	bool		IsPurged		(void) const { return mData == nullptr;	}

	bool		Create			(quint16 width, quint16 height, quint8 depth);

protected:
	// Fields
	quint32		mTexID;			// OpenGL texture ID

	quint16		mWidth;			// Width  (Power of two)
	quint16		mHeight;		// Height (Power of two)
	quint8		mDepth;			// Depth  (24 or 32)

	quint64		mDataLength;	// Pixel data length
	quint8*		mData;			// Pixel data
};

#endif // GRAPHICS_TEXTURE_H

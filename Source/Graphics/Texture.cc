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

#include "Engine/Console.h"

#include "Graphics/Color.h"
#include "Graphics/Texture.h"
ASSET_DEFINITION (Texture);

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Constructors                                                       Texture //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Texture::Texture (void) : Asset (AssetID)
{
	mTexID  = 0;

	mWidth  = 0;
	mHeight = 0;
	mDepth  = 0;

	mDataLength = 0;
	mData = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Texture::Texture (const Texture& texture) : Asset (texture)
{
	mTexID = 0;

	// Copy primitive data
	mWidth  = texture.mWidth;
	mHeight = texture.mHeight;
	mDepth  = texture.mDepth;

	// Copy pixel data
	if (texture.IsPurged())
	{
		// Data is purged
		mDataLength = 0;
		mData = nullptr;
	}

	else
	{
		// Data needs to be copied
		mDataLength = texture.mDataLength;
		mData = new quint8[mDataLength];

		memcpy (mData, texture.mData, mDataLength);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Texture::~Texture (void)
{
	Unload (true);

	if (mData != nullptr)
		delete[] mData;
}



//----------------------------------------------------------------------------//
// Methods                                                            Texture //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Color Texture::GetPixel (quint16 x, quint16 y)
{
	// Check if data is purged
	if (IsPurged())
		return Color::Black;

	// Check argument bounds
	if (x >= mWidth || y >= mHeight)
		return Color::Black;

	if (mDepth == 24)
	{
		// Get pixel (24 bpp)
		quint8 pos = (x * 3) + (y * mWidth * 3);
		return Color (mData[pos+0],
					  mData[pos+1],
					  mData[pos+2]);
	}

	else
	{
		// Get pixel (32 bpp)
		quint8 pos = (x * 4) + (y * mWidth * 4);
		return Color (mData[pos+0],
					  mData[pos+1],
					  mData[pos+2],
					  mData[pos+3]);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Texture::SetPixel (quint16 x, quint16 y, const Color& color)
{
	// Check if data is purged
	if (IsPurged())
		return false;

	// Check argument bounds
	if (x >= mWidth || y >= mHeight)
		return false;

	if (mDepth == 24)
	{
		// Set pixel (24 bpp)
		quint8 pos = (x * 3) + (y * mWidth * 3);
		mData[pos+0] = color.R;
		mData[pos+1] = color.G;
		mData[pos+2] = color.B;
	}

	else
	{
		// Set pixel (32 bpp)
		quint8 pos = (x * 4) + (y * mWidth * 4);
		mData[pos+0] = color.R;
		mData[pos+1] = color.G;
		mData[pos+2] = color.B;
		mData[pos+3] = color.A;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Texture::Load (void)
{
	// Check if already loaded
	if (IsLoaded()) return true;

	// Check if the data has been purged
	if (IsPurged()) return false;

	// Create a texture object
	GL_CALL (glGenTextures (1, &mTexID));
	GL_CALL (glBindTexture (GL_TEXTURE_2D, mTexID));

	// Define texture filtering modes
	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_CALL (glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));

	// Set texture data
	quint32 format = (mDepth == 32) ? GL_RGBA : GL_RGB;
	GL_CALL (glTexImage2D (GL_TEXTURE_2D, 0, format, mWidth,
		mHeight, 0, format, GL_UNSIGNED_BYTE, mData));

	// Unbind the texture object
	GL_CALL (glBindTexture (GL_TEXTURE_2D, 0));

	// Check for any OpenGL errors
	GL_CHECK (Unload (true); return false);

	// All done
	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Texture::Reload (bool force)
{
	Unload (force); return Load();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Texture::Unload (bool force)
{
	// Check if already unloaded
	if (!IsLoaded()) return;

	// Check for multiple references
	if (force || mReferences == 1)
	{
		// Delete the texture object
		GL_CALL (glBindTexture (GL_TEXTURE_2D, 0));
		GL_CALL (glDeleteTextures (1, &mTexID));
		mTexID = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Texture::Purge (bool force)
{
	// Check if data already purged
	if (IsPurged()) return;

	// Check for multiple references
	if (force || mReferences == 1)
	{
		// Purge texture data
		delete[] mData;
		mDataLength = 0;
		mData = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// depth in bits (24 or 32)
/// Does not delete opengl data

bool Texture::Create (quint16 width, quint16 height, quint8 depth)
{
	// Check texture depth
	if (depth != 24 && depth != 32)
		return false;

	// Check that dimensions are power of two
	if ((width  & (width  - 1)) != 0 ||
		(height & (height - 1)) != 0)
		return false;

	// Delete previous data
	if (mData != nullptr)
		delete[] mData;

	// Create texture
	mWidth  = width;
	mHeight = height;
	mDepth  = depth;

	mDataLength = width * height * (depth / 8);
	mData       = new quint8[mDataLength];

	// All done
	return true;
}

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

#include "TgaProcessor.h"

#include "Graphics/Texture.h"
#include "Engine/Console.h"

#include <QFile.h>



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#pragma pack (push, 1)
struct TgaHeader
{
	quint8 IdLength;		// size of ID field that follows header
	quint8 ColorMapType;	// Type of color map (0=none, 1=has palette)
	quint8 ImageType;		// Type of image (0=none, 1=indexed, 2=rgb, 3=grey, +8=rle)

	quint16 ColorMapStart;	// First color map entry in palette
	quint16 ColorMapLength;	// Number of colors in palette
	quint8  ColorMapBits;	// Number of bits per palette entry (15, 16, 24, 32)

	quint16 StartX;			// Image X origin
	quint16 StartY;			// Image Y origin

	quint16 Width;			// Image width  in pixels
	quint16 Height;			// Image height in pixels
	quint8  Depth;			// Image bits per pixel (8, 16, 24, 32)

	quint8 Descriptor;		// Image descriptor bits (vh flip bits)
};
#pragma pack (pop)



//----------------------------------------------------------------------------//
// Methods                                                       TgaProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* TgaProcessor::Import (QFile& file, Asset* asset)
{
	TgaHeader header;
	memset (&header, 0, sizeof (TgaHeader));

	// Attempt to read the header
	if (file.read ((char*) &header, sizeof (TgaHeader)) != sizeof (TgaHeader))
	{
		Console::Error ("Failed to read TGA header");
		return nullptr;
	}

	// Check for compatibility
	if (header.ImageType != 2)
	{
		Console::Error ("Unsupported TGA ImageType");
		return nullptr;
	}

	// Check for flipped texture
	if ((header.Descriptor & 0x10) == 0x10 ||
		(header.Descriptor & 0x20) == 0x20)
	{
		Console::Error ("TGA image flipping is not supported");
		return nullptr;
	}

	// Check texture depth
	if (header.Depth != 24 && header.Depth != 32)
	{
		Console::Error ("Invalid texture depth");
		return nullptr;
	}

	// Verify that dimensions are power of two
	if ((header.Width  & (header.Width  - 1)) != 0 ||
		(header.Height & (header.Height - 1)) != 0)
	{
		Console::Error ("Texture must be power of two");
		return nullptr;
	}

	// Skip the TGA image ID
	file.seek (sizeof (TgaHeader) + header.IdLength);

	// Create the texture object
	Texture* texture;
	bool managed = asset != nullptr;

	if (managed)
		 texture = (Texture*) asset;
	else texture = new Texture();
	
	texture->Create (header.Width, header.Height, header.Depth);

	quint8* data  = texture->GetData();
	quint32 depth = texture->GetDepth() == 32 ? 4 : 3;
	quint32 size  = texture->GetDataLength();

	// Read pixel information into buffer
	if (file.read ((char*) data, size) != size)
	{
		Console::Error ("Failed to read pixel data");
		if (!managed) texture->Release(); return nullptr;
	}

	// Convert TGA pixel format from BGR to RGB
	for (quint32 i = 0; i < size; i += depth)
	{
		quint8 temp = data[i  ];
		data[i  ]   = data[i+2];
		data[i+2]   = temp;
	}

	// All done
	return texture;
}

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

#include "../AstProcessor.h"

#include "Content/Asset.h"
#include "Engine/Console.h"
#include "Graphics/Texture.h"

#include <QIODevice.h>



//----------------------------------------------------------------------------//
// Internal                                                      AstProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* AstProcessor::ImportTexture (QIODevice& device, Asset* asset)
{
	// Read texture header
	quint16 width  = 0;
	quint16 height = 0;
	quint8  depth  = 0;

	if (device.read ((char*) &width,  sizeof (quint16)) != sizeof (quint16) ||
		device.read ((char*) &height, sizeof (quint16)) != sizeof (quint16) ||
		device.read ((char*) &depth,  sizeof (quint8 )) != sizeof (quint8))
	{
		Console::Error ("Unable to read texture header");
		return nullptr;
	}

	// Create the texture object
	Texture* texture;
	bool managed = asset != nullptr;

	if (managed)
		 texture = (Texture*) asset;
	else texture = new Texture();
	
	texture->Create (width, height, depth);

	// Read texture data
	if (device.read ((char*) texture->GetData(), texture->GetDataLength()) != texture->GetDataLength())
	{
		Console::Error ("Unable to read texture data");
		if (!managed) texture->Release(); return nullptr;
	}

	return texture;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool AstProcessor::ExportTexture (QIODevice& device, const Asset* asset)
{
	Texture* texture = (Texture*) asset;

	// Check if shader is purged
	if (texture->IsPurged())
	{
		Console::Error ("Texture is purged");
		return false;
	}

	// Write texture header
	quint16 width  = texture->GetWidth();
	quint16 height = texture->GetHeight();
	quint8  depth  = texture->GetDepth();

	device.write ((char*) &width,  sizeof (quint16));
	device.write ((char*) &height, sizeof (quint16));
	device.write ((char*) &depth,  sizeof (quint8 ));

	// Write texture data
	device.write ((char*) texture->GetData(), texture->GetDataLength());

	return true;
}

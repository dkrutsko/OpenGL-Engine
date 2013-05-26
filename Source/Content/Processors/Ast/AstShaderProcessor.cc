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
#include "Graphics/Shader.h"

#include <QIODevice.h>



//----------------------------------------------------------------------------//
// Internal                                                      AstProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* AstProcessor::ImportShader (QIODevice& device, Asset* asset)
{
	// Create the shader object
	Shader* shader;
	bool managed = asset != nullptr;

	if (managed)
		 shader = (Shader*) asset;
	else shader = new Shader();
	
	shader->Create();

	// Load shader contents
	quint32 vertLength = 0;
	quint32 fragLength = 0;

	if (device.read ((char*) &vertLength, sizeof (quint32)) != sizeof (quint32) ||
		device.read ((char*) &fragLength, sizeof (quint32)) != sizeof (quint32))
	{
		Console::Error ("Error reading pass header");
		if (!managed) shader->Release(); return nullptr;
	}

	shader->Vertex   = device.read (vertLength);
	shader->Fragment = device.read (fragLength);

	if (shader->Vertex  .length() != vertLength ||
		shader->Fragment.length() != fragLength)
	{
		Console::Error ("Error reading shader pass");
		if (!managed) shader->Release(); return nullptr;
	}

	return shader;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool AstProcessor::ExportShader (QIODevice& device, const Asset* asset)
{
	Shader* shader = (Shader*) asset;

	// Check if shader is purged
	if (shader->IsPurged())
	{
		Console::Error ("Shader is purged");
		return false;
	}

	// Write shader header
	QByteArray vert = shader->Vertex;
	QByteArray frag = shader->Fragment;

	quint32 vertLength = vert.length();
	quint32 fragLength = frag.length();

	device.write ((char*) &vertLength, sizeof (quint32));
	device.write ((char*) &fragLength, sizeof (quint32));
	device.write (vert);
	device.write (frag);

	return true;
}

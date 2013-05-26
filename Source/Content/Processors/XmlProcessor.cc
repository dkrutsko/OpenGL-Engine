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

#include "XmlProcessor.h"
#include "Engine/Console.h"

#include <QDom.h>
#include <QFile.h>
#include <QIODevice.h>



//----------------------------------------------------------------------------//
// Methods                                                       XmlProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* XmlProcessor::Import (QFile& file, Asset* asset)
{
	QDomDocument doc;

	// Attempt to read as XML
	if (!doc.setContent (&file))
	{
		Console::Error ("Unable to read XML file");
		return nullptr;
	}

	// Get the root element of the document
	QDomElement root = doc.documentElement();

	// Document is a model
	if (root.tagName() == "Model")
		return ImportModel (file, doc, asset);

	// Document is a shader
	if (root.tagName() == "Shader")
		return ImportShader (file, doc, asset);

	// Document is a particle system
	if (root.tagName() == "ParticleSystem")
		return ImportParticleSystem (file, doc, asset);

	// Document is of an unknown type
	Console::Error ("File is not the right type");
	return nullptr;
}

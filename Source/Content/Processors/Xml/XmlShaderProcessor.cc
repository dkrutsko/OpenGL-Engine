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

#include "Version.h"
#include "../XmlProcessor.h"

#include "Content/Asset.h"
#include "Engine/Console.h"
#include "Graphics/Shader.h"

#include <QDom.h>
#include <QFile.h>
#include <QFileInfo.h>
#include <QIODevice.h>



//----------------------------------------------------------------------------//
// Internal                                                                   //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void ParseShader (QFile& file, QDomElement& element, QByteArray& data)
{
	// Get the localized filename of the shader
	QFileInfo info (file);
	QString filename = info.path() + "/" + element.attribute ("File");

	// Get the entry point of the shader (if any)
	QString entry = element.attribute ("Entry");

	// Open shader file
	QFile input (filename);
	if (!input.open (QIODevice::ReadOnly))
	{
		Console::Error ("Unable to open shader file");
		return;
	}

	// Read the whole file
	data = input.readAll();

	// Append a main if needed
	if (!entry.isEmpty())
	{
		data.append ("\nvoid main (void)\n{");
		data.append (entry);
		data.append (";\n}\n");
	}
}



//----------------------------------------------------------------------------//
// Internal                                                      XmlProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* XmlProcessor::ImportShader (QFile& file, QDomDocument& document, Asset* asset)
{
	// Get the root element of the document
	QDomElement root = document.documentElement();

	// Verify version
	if (root.attribute ("Version") != VERSION)
	{
		Console::Error ("Unsupported file version");
		return nullptr;
	}

	// Create the shader object
	Shader* shader;
	bool managed = asset != nullptr;

	if (managed)
		 shader = (Shader*) asset;
	else shader = new Shader();

	shader->Create();

	// Parse XML data
	QDomNode node = root.firstChild();
	while (!node.isNull())
	{
		// Get the node element
		QDomElement element = node.toElement();

		// Get the next XML node
		node = node.nextSibling();
		if (element.isNull()) continue;

		// Load vertex shader information
		if (element.tagName() == "Vertex")
			ParseShader (file, element, shader->Vertex);

		// Load fragment shader information
		else if (element.tagName() == "Fragment")
			ParseShader (file, element, shader->Fragment);
	}

	// All done
	return shader;
}

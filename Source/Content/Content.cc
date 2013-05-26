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

#include <QFile.h>
#include <QFileInfo.h>
#include <QString.h>
#include <QCoreApplication.h>

#include "Engine/Console.h"

#include "Content/Asset.h"
#include "Content/Processor.h"
#include "Content/Content.h"

// Processors
#include "Processors/AstProcessor.h"
#include "Processors/FbxProcessor.h"
#include "Processors/TgaProcessor.h"
#include "Processors/XmlProcessor.h"



//----------------------------------------------------------------------------//
// Static                                                             Content //
//----------------------------------------------------------------------------//

QMap<QString, Asset*> Content::mLoaded;



//----------------------------------------------------------------------------//
// Static                                                             Content //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* Content::Load (const QString& filename)
{
	// Check if asset was previously loaded
	Asset* asset = mLoaded.value (filename);

	if (asset != nullptr)
	{
		// Return loaded asset
		asset->mReferences += 1;
		return asset;
	}

	// Get information about the file
	QString file = filename;
	QFileInfo info (file);

	if (!info.exists())
	{
		file = QCoreApplication::applicationDirPath() + "/Data/" + filename;
		info = QFileInfo (file);
	}

	Console::Message ("Loading file: %s", filename.toAscii().data());

	// Open input file
	QFile input (file);
	if (!input.open (QIODevice::ReadOnly))
	{
		Console::Error ("Unable to open input file");
		return nullptr;
	}

	// Find appropriate processor
	Processor* processor = FindProcessor (info.suffix());
	if (processor == nullptr)
	{
		Console::Error ("Unable to find processor");
		return nullptr;
	}

	// Attempt to import the asset
	asset = processor->Import (input);
	if (asset == nullptr)
	{
		Console::Error ("Unable to import asset");
		return nullptr;
	}

	// Add asset to the list
	asset->mSource  = filename;
	asset->mManaged = true;
	mLoaded.insert (filename, asset);

	// All done
	return asset;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Content::Process (const QString& filename)
{
	// Get information about the file
	QString file = filename;
	QFileInfo info (file);

	if (!info.exists())
	{
		file = QCoreApplication::applicationDirPath() + "/Data/" + filename;
		info = QFileInfo (file);
	}

	Console::Message ("Processing file: %s",
		info.fileName().toAscii().data());

	if (info.suffix() == "ast")
	{
		Console::Warning ("File is already processed");
		return true;
	}

	// Open input file
	QFile input (file);
	if (!input.open (QIODevice::ReadOnly))
	{
		Console::Error ("Unable to open input file");
		return false;
	}

	// Find appropriate importer
	Processor* importer = FindProcessor (info.suffix());
	if (importer == nullptr)
	{
		Console::Error ("Unable to find importer");
		return false;
	}

	// Attempt to import the asset
	Asset* asset = importer->Import (input);
	if (asset == nullptr)
	{
		Console::Error ("Unable to import asset");
		return false;
	}

	// Find appropriate exporter
	Processor* exporter = FindProcessor ("ast");
	if (exporter == nullptr)
	{
		delete asset;

		Console::Error ("Unable to find exporter");
		return false;
	}

	// Open output file
	QString outputName = QString ("%1/%2.ast")
		.arg (info.path()).arg (info.baseName());

	QFile output (outputName);
	if (!output.open (QIODevice::WriteOnly))
	{
		delete asset;

		Console::Error ("Unable to open ouput file");
		return false;
	}

	// Attempt to export the asset
	if (!exporter->Export (output, asset))
	{
		delete asset;

		Console::Error ("Unable to export asset");
		return false;
	}

	// All done
	delete asset;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* Content::Reload (Asset* asset)
{
	// Make sure the asset is valid
	if (asset == nullptr) return nullptr;
	if (!asset->mManaged) return nullptr;

	// Load the specified asset
	Asset* ast = mLoaded.value (asset->mSource);

	// Get information about the file
	QFileInfo info (asset->mSource);
	Console::Message ("Reloading file: %s",
		info.fileName().toAscii().data());

	// Open input file
	QFile input (asset->mSource);
	if (!input.open (QIODevice::ReadOnly))
	{
		Console::Error ("Unable to open input file");
		return nullptr;
	}

	// Find appropriate processor
	Processor* processor = FindProcessor (info.suffix());
	if (processor == nullptr)
	{
		Console::Error ("Unable to find processor");
		return nullptr;
	}

	// Attempt to import the asset
	asset = processor->Import (input, asset);
	if (asset == nullptr)
	{
		Console::Error ("Unable to import asset");
		return nullptr;
	}

	// Asset reloaded
	return asset;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Content::UnloadAll (void)
{
	// Delete all loaded assets
	foreach (Asset* asset, mLoaded)
		delete asset;

	mLoaded.clear();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Processor* Content::FindProcessor (const QString& extension)
{
	// List of all available processors
	static AstProcessor sAstProcessor;
	static FbxProcessor sFbxProcessor;
	static TgaProcessor sTgaProcessor;
	static XmlProcessor sXmlProcessor;

	// Lowercase the extension
	QString ext = extension.toLower();

	// Determine appropriate processor
	if (ext == "ast") return &sAstProcessor;
	if (ext == "fbx") return &sFbxProcessor;
	if (ext == "tga") return &sTgaProcessor;
	if (ext == "xml") return &sXmlProcessor;

	// None found
	return nullptr;
}

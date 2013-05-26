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
#include "AstProcessor.h"

#include "Content/Asset.h"
#include "Engine/Console.h"

#include <QFile.h>
#include <QByteArray.h>
#include <QBuffer.h>

#include "Graphics/Texture.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/ParticleSystem.h"



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static const qint32 CompressionLevel = 9;

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static enum DataTypes
{
	UnknownType			= 0,
	TextureType			= 10,
	ModelType			= 20,
	ShaderType			= 30,
	ParticleSystemType	= 40,
};

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static const quint32 Identifier = ('T' << 16) + ('S' << 8) + 'A';

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#pragma pack (push, 1)
struct AstHeader
{
	quint32 Identifier;		// Little endian "AST"
	quint16 Major;			// Major version
	quint16 Minor;			// Minor version
	quint16 DataType;		// Asset data type
	quint64	DataSize;		// Asset data size (Compressed)
};
#pragma pack (pop)

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static const quint16 Trailer = 0x4815;



//----------------------------------------------------------------------------//
// Methods                                                       AstProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* AstProcessor::Import (QFile& file, Asset* asset)
{
	AstHeader header;
	memset (&header, 0, sizeof (AstHeader));

	// Attempt to read the header
	if (file.read ((char*) &header, sizeof (AstHeader)) != sizeof (AstHeader))
	{
		Console::Error ("Failed to read AST header");
		return nullptr;
	}

	// Check identifier
	if (header.Identifier != Identifier)
	{
		Console::Error ("Incorrect AST header identifier");
		return nullptr;
	}

	// Check version
	if (header.Major != MAJOR && header.Minor != MINOR)
	{
		Console::Error ("Incompatible AST version");
		return nullptr;
	}

	// Read asset data
	QByteArray data = file.read (header.DataSize);
	if (data.size() != header.DataSize)
	{
		Console::Error ("Not enough data read");
		return nullptr;
	}

	// Uncompress data
	data = qUncompress (data);

	if (data.isEmpty())
	{
		Console::Error ("Unable to uncompress data");
		return nullptr;
	}

	// Check trailer
	quint16 trailer = 0;
	file.read ((char*) &trailer, sizeof (quint16));

	if (trailer != Trailer)
	{
		Console::Error ("Incorrect AST trailer");
		return nullptr;
	}

	// Open a buffer to the data
	QBuffer buffer (&data);
	buffer.open (QIODevice::ReadOnly);

	// File is a texture
	if (header.DataType == TextureType)
		return ImportTexture (buffer, asset);

	// File is a model
	if (header.DataType == ModelType)
		return ImportModel (buffer, asset);

	// File is a shader
	if (header.DataType == ShaderType)
		return ImportShader (buffer, asset);

	// File is a particle system
	if (header.DataType == ParticleSystemType)
		return ImportParticleSystem (buffer, asset);

	// File is of an unknown type
	Console::Error ("File is not the right type");
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool AstProcessor::Export (QFile& file, const Asset* asset)
{
	AstHeader header;
	QByteArray data;
	bool status = false;

	// Open a buffer to the data
	QBuffer buffer (&data);
	buffer.open (QIODevice::WriteOnly);

	// Assign correct data type
	if (asset->GetAssetID() == Texture::AssetID)
	{
		header.DataType = TextureType;
		status = ExportTexture (buffer, asset);
	}

	else if (asset->GetAssetID() == Model::AssetID)
	{
		header.DataType = ModelType;
		status = ExportModel (buffer, asset);
	}

	else if (asset->GetAssetID() == Shader::AssetID)
	{
		header.DataType = ShaderType;
		status = ExportShader (buffer, asset);
	}

	else if (asset->GetAssetID() == ParticleSystem::AssetID)
	{
		header.DataType = ParticleSystemType;
		status = ExportParticleSystem (buffer, asset);
	}

	else
	{
		Console::Error ("Asset is of unknown type");
		return false;
	}

	if (!status)
	{
		Console::Error ("Unable to export asset data");
		return false;
	}

	// Compress data
	data = qCompress (data, CompressionLevel);

	// Set header data
	header.Identifier = Identifier;
	header.Major = MAJOR;
	header.Minor = MINOR;
	header.DataSize = data.size();

	// Write data to file
	file.write ((char*) &header, sizeof (AstHeader));
	file.write (data);
	file.write ((char*) &Trailer, sizeof (quint16));

	return true;
}

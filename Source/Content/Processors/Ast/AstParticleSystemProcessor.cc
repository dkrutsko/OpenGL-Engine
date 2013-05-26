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
#include "Content/Content.h"
#include "Engine/Console.h"

#include "Math/Vector3.h"
#include "Graphics/Color.h"
#include "Graphics/ParticleSystem.h"
#include "Graphics/Texture.h"

#include <QIODevice.h>



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#pragma pack (push, 1)
struct ParticleSystemFile
{
	quint16 Quantity;
	Vector3 Position;
	Color   Diffuse;

	float Alpha;
	float Speed;
	float Spread;
	float Shape;
	float Size;
	float Gravity;

	float SystemHeight;
	float SystemShape;
	float FadeInTime;
	float FadeOutTime;
};
#pragma pack (pop)




//----------------------------------------------------------------------------//
// Internal                                                      AstProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* AstProcessor::ImportParticleSystem (QIODevice& device, Asset* asset)
{
	ParticleSystem* system;
	bool managed = asset != nullptr;

	if (managed)
		 system = (ParticleSystem*) asset;
	else system = new ParticleSystem();
	
	ParticleSystemFile file;

	if (device.read ((char*) &file,  sizeof (ParticleSystemFile)) != sizeof (ParticleSystemFile))
	{
		Console::Error ("Unable to read particle system header");
		if (!managed) system->Release(); return nullptr;
	}

	system->Create (file.Quantity);

	system->Position		= file.Position;
	system->Diffuse			= file.Diffuse;

	system->Alpha			= file.Alpha;
	system->Speed			= file.Speed;
	system->Spread			= file.Spread;
	system->Shape			= file.Shape;
	system->Size			= file.Size;
	system->Gravity			= file.Gravity;

	system->SystemHeight	= file.SystemHeight;
	system->SystemShape		= file.SystemShape;
	system->FadeInTime		= file.FadeInTime;
	system->FadeOutTime		= file.FadeOutTime;

	quint8 length = 0;
	if (device.read ((char*) &length, sizeof (quint8)) != sizeof (quint8))
	{
		Console::Error ("Unable to read texture length");
		if (!managed) system->Release(); return nullptr;
	}

	QByteArray filename = device.read (length);
	if (filename.length() != length)
	{
		Console::Error ("Unable to read texture filename");
		if (!managed) system->Release(); return nullptr;
	}

	Texture* texture = (Texture*) Content::Load (QString (filename));
	system->SetTexture (texture);

	return system;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool AstProcessor::ExportParticleSystem (QIODevice& device, const Asset* asset)
{
	ParticleSystem* system = (ParticleSystem*) asset;

	ParticleSystemFile file;

	file.Quantity		= system->GetQuantity();
	file.Position		= system->Position;
	file.Diffuse		= system->Diffuse;

	file.Alpha			= system->Alpha;
	file.Speed			= system->Speed;
	file.Spread			= system->Spread;
	file.Shape			= system->Shape;
	file.Size			= system->Size;
	file.Gravity		= system->Gravity;

	file.SystemHeight	= system->SystemHeight;
	file.SystemShape	= system->SystemShape;
	file.FadeInTime		= system->FadeInTime;
	file.FadeOutTime	= system->FadeOutTime;

	device.write ((char*) &file, sizeof (ParticleSystemFile));

	quint32 filenameLength = 0;
	Texture* texture = system->GetTexture();
	if (texture == nullptr)
	{
		device.write ((char*) &filenameLength, sizeof (quint8));
		return true;
	}

	if (!texture->IsManaged())
	{
		device.write ((char*) &filenameLength, sizeof (quint8));
		Console::Warning ("Cannot export unmanaged texture");
		return true;
	}

	filenameLength = texture->GetSource().length();
	device.write ((char*) &filenameLength, sizeof (quint8));

	device.write (texture->GetSource().toAscii().data(), filenameLength);

	return true;
}

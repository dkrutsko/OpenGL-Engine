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

#include "Content/Content.h"
#include "Content/Asset.h"
#include "Engine/Console.h"
#include "Graphics/ParticleSystem.h"

#include "Math/Vector3.h"
#include "Graphics/Color.h"

#include <QDom.h>
#include <QFile.h>
#include <QFileInfo.h>
#include <QIODevice.h>
#include <QStringList.h>



//----------------------------------------------------------------------------//
// Internal                                                                   //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void ParseVector3 (QDomElement& element, Vector3& value)
{
	QString vector = element.attribute ("Value");
	if (!vector.isEmpty())
	{
		QStringList list = vector.split (',', QString::SkipEmptyParts);
		if (list.length() >= 3)
		{
			value.X = list.at(0).toFloat();
			value.Y = list.at(1).toFloat();
			value.Z = list.at(2).toFloat();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

static void ParseColor (QDomElement& element, Color& value)
{
	QString color = element.attribute ("Value");
	if (!color.isEmpty())
	{
		QStringList list = color.split (',', QString::SkipEmptyParts);
		if (list.length() >= 4)
		{
			value.R = list.at(0).toFloat();
			value.G = list.at(1).toFloat();
			value.B = list.at(2).toFloat();
			value.A = list.at(3).toFloat();
		}
	}
}



//----------------------------------------------------------------------------//
// Internal                                                      XmlProcessor //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Asset* XmlProcessor::ImportParticleSystem (QFile& file, QDomDocument& document, Asset* asset)
{
	// Get the root element of the document
	QDomElement root = document.documentElement();

	// Verify version
	if (root.attribute ("Version") != VERSION)
	{
		Console::Error ("Unsupported file version");
		return nullptr;
	}

	// Create the particle system object
	ParticleSystem* system;
	bool managed = asset != nullptr;

	if (managed)
		 system = (ParticleSystem*) asset;
	else system = new ParticleSystem();

	bool status;
	QFileInfo info (file);

	// Parse XML data
	QDomNode node = root.firstChild();
	while (!node.isNull())
	{
		// Get the node element
		QDomElement element = node.toElement();

		// Get the next XML node
		node = node.nextSibling();
		if (element.isNull()) continue;

		// Load particle system data
		if (element.tagName() == "Position")
			ParseVector3 (element, system->Position);

		if (element.tagName() == "Diffuse")
			ParseColor (element, system->Diffuse);

		if (element.tagName() == "Alpha")
		{
			system->Alpha = element.attribute ("Value").toFloat (&status);
			if (!status) system->Alpha = 1.0f;
		}

		if (element.tagName() == "Speed")
		{
			system->Speed = element.attribute ("Value").toFloat (&status);
			if (!status) system->Speed = 1.0f;
		}

		if (element.tagName() == "Spread")
		{
			system->Spread = element.attribute ("Value").toFloat (&status);
			if (!status) system->Spread = 1.0f;
		}

		if (element.tagName() == "Shape")
		{
			system->Shape = element.attribute ("Value").toFloat (&status);
			if (!status) system->Shape = 1.0f;
		}

		if (element.tagName() == "Size")
		{
			system->Size = element.attribute ("Value").toFloat (&status);
			if (!status) system->Size = 1.0f;
		}

		if (element.tagName() == "Gravity")
		{
			system->Gravity = element.attribute ("Value").toFloat (&status);
			if (!status) system->Gravity = 0.0f;
		}

		if (element.tagName() == "SystemHeight")
		{
			system->SystemHeight = element.attribute ("Value").toFloat (&status);
			if (!status) system->SystemHeight = 1.0f;
		}

		if (element.tagName() == "SystemShape")
		{
			system->SystemShape = element.attribute ("Value").toFloat (&status);
			if (!status) system->SystemShape = 1.0f;
		}

		if (element.tagName() == "FadeInTime")
		{
			system->FadeInTime = element.attribute ("Value").toFloat (&status);
			if (!status) system->FadeInTime = 1.0f;
		}

		if (element.tagName() == "FadeOutTime")
		{
			system->FadeOutTime = element.attribute ("Value").toFloat (&status);
			if (!status) system->FadeOutTime = 1.0f;
		}

		if (element.tagName() == "Quantity")
		{
			quint16 quantity = element.attribute ("Value").toFloat (&status);
			if (status) system->Create (quantity);
		}

		if (element.tagName() == "Texture")
		{
			Texture* texture = (Texture*) Content::Load (element.attribute ("Value"));
			system->SetTexture (texture);
		}
	}

	return system;
}

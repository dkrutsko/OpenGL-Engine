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
#include "Engine/Settings.h"

#include <QDom.h>
#include <QFile.h>
#include <QTextStream.h>
#include <QByteArray.h>



//----------------------------------------------------------------------------//
// Globals                                                           Settings //
//----------------------------------------------------------------------------//

qint32 Settings::mWidth			= 0;
qint32 Settings::mHeight		= 0;

qreal Settings::mAspectRatioX	= 0;
qreal Settings::mAspectRatioY	= 0;

bool Settings::mFullscreen		= false;



//----------------------------------------------------------------------------//
// Window                                                            Settings //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Settings::SetWidth (qint32 width)
{
	mWidth = width;

	mAspectRatioX = mHeight / (qreal) mWidth;
	mAspectRatioY = mWidth  / (qreal) mHeight;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Settings::SetHeight (qint32 height)
{
	mHeight = height;

	mAspectRatioX = mHeight / (qreal) mWidth;
	mAspectRatioY = mWidth  / (qreal) mHeight;
}



//----------------------------------------------------------------------------//
// Filesystem                                                        Settings //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Settings::Load (QString filename)
{
	// Attempt to open the file
	QFile file (filename);
	if (!file.open (QIODevice::ReadOnly))
		return false;

	// Attempt to read XML
	QDomDocument xml;
	if (!xml.setContent (&file))
		return false;

	QDomElement root = xml.documentElement();

	// Verify XML data
	if (root.tagName() != "Settings")
		return false;

	// Verify version
	if (root.attribute ("Version") != VERSION)
		return false;

	// Parse XML data
	QDomNode node = root.firstChild();
	while (!node.isNull())
	{
		// Get the node element
		QDomElement element = node.toElement();

		// Get the next XML node
		node = node.nextSibling();
		if (element.isNull()) continue;

		// Load window information
		if (element.tagName() == "Window")
		{
			mWidth      = element.attribute ("Width"     ).toInt();
			mHeight     = element.attribute ("Height"    ).toInt();
			mFullscreen = element.attribute ("Fullscreen") == "True";
		}
	}

	// Boundary check width and height
	if (mWidth  < 640 ) mWidth  = 640;
	if (mWidth  > 2560) mWidth  = 2560;
	if (mHeight < 480 ) mHeight = 480;
	if (mHeight > 2048) mHeight = 2048;

	// Calculate aspect ratios
	mAspectRatioX = mHeight / (qreal) mWidth;
	mAspectRatioY = mWidth  / (qreal) mHeight;

	// Everything went well
	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Settings::Save (QString filename)
{
	// Attempt to open file
	QFile file (filename);
	if (!file.open (QIODevice::WriteOnly))
		return false;

	// Prepare settings
	QString content = QString
	(
		"<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n\n"

		"<!--////////////////////////////////////////////////////////////////////////////\n"
		"// ========================================================================== //\n"
		"//                                                                            //\n"
		"//                        (C) 2012-2013  David Krutsko                        //\n"
		"//                        See LICENSE.md for copyright                        //\n"
		"//                                                                            //\n"
		"// ========================================================================== //\n"
		"/////////////////////////////////////////////////////////////////////////////-->\n\n"

		"<Settings Version=\"%1\">\n"
			"\t\n"
			"\t<Window Width=\"%2\" Height=\"%3\" Fullscreen=\"%4\" />\n"
			"\t\n"
		"</Settings>\n"

	).arg (VERSION).arg (mWidth).arg (mHeight).arg (mFullscreen ? "True" : "False");

	// Write settings to disk
	QTextStream (&file) << content;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Settings::LoadDefault (void)
{
	mWidth			= 1280;
	mHeight			= 800;

	mAspectRatioX	= mHeight / (qreal) mWidth;
	mAspectRatioY	= mWidth  / (qreal) mHeight;

	mFullscreen		= false;
}

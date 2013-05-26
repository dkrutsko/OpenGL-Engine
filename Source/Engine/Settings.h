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

#ifndef ENGINE_SETTINGS_H
#define ENGINE_SETTINGS_H

#include <QGlobal.h>
#include <QString.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Settings
{
	friend class Engine;

private:
	// Constructors
	 Settings (void) { }
	 Settings (const Settings& settings) { }
	~Settings (void) { }

public:
	// Window
	static qint32	GetWidth		(void) { return mWidth;			}
	static qint32	GetHeight		(void) { return mHeight;		}
	static qreal	GetAspectRatioX	(void) { return mAspectRatioX;	}
	static qreal	GetAspectRatioY	(void) { return mAspectRatioY;	}
	static bool		GetFullscreen	(void) { return mFullscreen;	}

	static void		SetWidth		(qint32 width   );
	static void		SetHeight		(qint32 height  );
	static void		SetFullscreen	(bool fullscreen) { mFullscreen = fullscreen; }

public:
	// Filesystem
	static bool		Load			(void) { return Load ("Data/Settings.xml"); }
	static bool		Save			(void) { return Save ("Data/Settings.xml"); }

	static bool		Load			(QString filename);
	static bool		Save			(QString filename);

	static void		LoadDefault		(void);

private:
	// Fields
	static qint32	mWidth;			// Window width
	static qint32	mHeight;		// Window height

	static qreal	mAspectRatioX;	// Aspect ratio X
	static qreal	mAspectRatioY;	// Aspect ratio Y

	static bool		mFullscreen;	// Is fullscreen
};

#endif // ENGINE_SETTINGS_H

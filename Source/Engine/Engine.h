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

#ifndef ENGINE_H
#define ENGINE_H

class Demo;

#include "Math/Matrix.h"
#include <QGlobal.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Engine
{
private:
	// Constructors
	 Engine (void) { }
	 Engine (const Engine& engine) { }
	~Engine (void) { }

public:
	// Types
	enum ExitStatus
	{
		ExitNone,		// Continue running
		ExitDesktop,	// Exit to desktop
		ExitRestart,	// Restart the engine
	};

public:
	// Methods
	static bool				Start			(void);

	static ExitStatus		GetExitStatus	(void)				{ return mExitStatus;	}
	static void				SetExitStatus	(ExitStatus status)	{ mExitStatus = status;	}

	static qint32			GetWindowWidth	(void)				{ return mWidth;		}
	static qint32			GetWindowHeight	(void)				{ return mHeight;		}
	static bool				HasSizeChanged	(void)				{ return mSizeChanged;	}

	static const Matrix&	GetPerspective	(void)				{ return mPerspective;	}
	static float			GetNearClip		(void)				{ return 0.1f;			}
	static float			GetFarClip		(void)				{ return 10000.0f;		}

private:
	// Internal
	static void				Tick			(void);
	static void				Initialize		(void);
	static void				Shutdown		(void);

#ifdef Q_OS_WIN32
	static void				InitWin32		(void);
	static void				ExitWin32		(void);
#endif

private:
	// Fields
	static ExitStatus	mExitStatus;	// Exit status
	static Demo*		mDemo;			// Demo object

	static qint32		mWidth;			// Window width
	static qint32		mHeight;		// Window height
	static bool			mSizeChanged;	// Window size changed

	static Matrix		mPerspective;	// Projection matrix
};

#endif // ENGINE_H

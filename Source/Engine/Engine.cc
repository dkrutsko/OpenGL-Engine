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

#include "Engine/Input.h"
#include "Engine/Engine.h"
#include "Engine/Console.h"
#include "Engine/Settings.h"

#include "Demo/Demo.h"
#include "Content/Content.h"

#include <SDL.h>
#include "Version.h"

#include <QCoreApplication.h>

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Static                                                              Engine //
//----------------------------------------------------------------------------//

Demo* Engine::mDemo = nullptr;

qint32 Engine::mWidth		= 0;
qint32 Engine::mHeight		= 0;
bool   Engine::mSizeChanged	= false;

Matrix Engine::mPerspective	= Matrix::Identity;

Engine::ExitStatus Engine::mExitStatus = Engine::ExitNone;



//----------------------------------------------------------------------------//
// Methods                                                             Engine //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>
/// <returns> True if the engine needs to be restarted. </returns>

bool Engine::Start (void)
{
	Initialize();
	
	// Enter the main event loop
	while (mExitStatus == ExitNone)
		Tick();

	Shutdown();

	// Check if we need to restart
	return mExitStatus == ExitRestart;
}



//----------------------------------------------------------------------------//
// Internal                                                            Engine //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Engine::Tick (void)
{
	// Handle SDL events
	SDL_Event event;
	while (SDL_PollEvent (&event))
	{
		// User has asked to exit
		if (event.type == SDL_QUIT)
			mExitStatus = ExitDesktop;

		// User has resized the window
		if (event.type == SDL_VIDEORESIZE)
		{
			mWidth  = event.resize.w;
			mHeight = event.resize.h;

			GL_CALL (glViewport (0, 0, mWidth, mHeight));
			mPerspective = Matrix::CreatePerspectiveFieldOfView
				(0.785398f, mWidth / (float) mHeight, 0.1f, 10000);

			mSizeChanged = true;
		}
	}

	// Check for escape key
	Keyboard keyboard;
	keyboard.Sync();

	if (keyboard.Keys[SDLK_ESCAPE])
		mExitStatus = ExitDesktop;

	// Update the demo
	mDemo->Update (1, SDL_GetTicks());

	// Draw the demo
	GL_CALL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	mDemo->Render (1, SDL_GetTicks());

	// Check for any errors
	GL_CHECK (Console::Error ("Frame rendering failed!"));

	// Swap back buffer
	SDL_GL_SwapBuffers();
	mSizeChanged = false;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Engine::Initialize (void)
{
	// Reset exit flag
	mExitStatus = ExitNone;
	
	// Attempt to initialize SDL
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		Console::Fatal ("Unable to initialize SDL: %s", SDL_GetError());

#ifdef Q_OS_WIN32
	// Initialize windows extensions
	InitWin32();
#endif

	// Load demo settings
	if (!Settings::Load())
	{
		Console::Warning ("Failed to load settings, using default");
		Settings::LoadDefault();
	}

	// Attempt to create OpenGL Scene
	mWidth  = Settings::GetWidth();
	mHeight = Settings::GetHeight() - 27; // Compensate for the title bar

	if (SDL_SetVideoMode (mWidth, mHeight, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL)
		Console::Fatal ("Unable to create OpenGL scene: %s", SDL_GetError());

	// Enable Anti Aliasing 8x
	SDL_GL_SetAttribute (SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute (SDL_GL_MULTISAMPLESAMPLES, 8);

	// Set caption to the app name
	SDL_WM_SetCaption (APPNAME, NULL);

	// Initialize Glew
	GLenum glewInitResult = glewInit();

	if (glewInitResult != GLEW_OK)
		Console::Fatal ("Unable to initialize glew: %s",
			glewGetErrorString (glewInitResult));

	// Initialize OpenGL
	GL_CALL (glClearColor	(0.0f, 0.0f, 0.0f, 1.0f));
	GL_CALL (glPointSize	(2.0f));

	GL_CALL (glEnable		(GL_DEPTH_TEST));
	GL_CALL (glDepthFunc	(GL_LESS));

	GL_CALL (glEnable		(GL_CULL_FACE));
	GL_CALL (glCullFace		(GL_BACK));
	GL_CALL (glFrontFace	(GL_CCW));

	GL_CALL (glEnable		(GL_BLEND));
	GL_CALL (glBlendFunc	(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Get OpenGL version
	Console::Message ("OpenGL version: %s", glGetString (GL_VERSION));

	// Create a Demo object
	mDemo = new Demo();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Engine::Shutdown (void)
{
	// Save demo settings
	if (!Settings::Save())
		Console::Warning ("Failed to save settings");

	// Delete the demo object
	delete mDemo;

	// Unload all content
	Content::UnloadAll();

	// Quit SDL
	SDL_Quit();

#ifdef Q_OS_WIN32
	// Exit windows extensions
	ExitWin32();
#endif
}



//----------------------------------------------------------------------------//
// Windows                                                             Engine //
//----------------------------------------------------------------------------//

#ifdef Q_OS_WIN32

#include <SDL_syswm.h>

HICON   gIcon;		// Resource icon
WNDPROC gWndProc;	// SDL WndProc
RECT    gBounds;	// Previous bounds

////////////////////////////////////////////////////////////////////////////////
/// <summary> Calculates new window bounds during a resize event. </summary>

void CalcWndBounds (RECT* bounds, WPARAM wParam)
{
	switch (wParam)
	{
	case WMSZ_LEFT:
	case WMSZ_TOPLEFT:
	case WMSZ_TOPRIGHT:
		bounds->top = bounds->bottom - ((bounds->right - bounds->left) * Settings::GetAspectRatioX());
		break;

	case WMSZ_RIGHT:
	case WMSZ_BOTTOMRIGHT:
	case WMSZ_BOTTOMLEFT:
		bounds->bottom = ((bounds->right - bounds->left) * Settings::GetAspectRatioX()) + bounds->top;
		break;

	case WMSZ_TOP:
		bounds->left = bounds->right - ((bounds->bottom - bounds->top) * Settings::GetAspectRatioY());
		break;

	case WMSZ_BOTTOM:
		bounds->right = ((bounds->bottom - bounds->top) * Settings::GetAspectRatioY()) + bounds->left;
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> Represents a custom WndProc for the SDL window </summary>

LRESULT CALLBACK WndProc (HWND hWnd, UINT_PTR msg, WPARAM wParam, LPARAM lParam)
{
	// The cursor is being set
	if (msg == WM_SETCURSOR)
	{
		if (LOWORD (lParam) == HTCLIENT)
		{
			// Replace the SDL cursor with a normal one
			SetCursor (LoadCursor (NULL, IDC_ARROW));
			return TRUE;
		}
	}

	// The window is being resized
	if (msg == WM_SIZING)
	{
		// Get the current window bounds
		RECT* bounds = (RECT*) lParam;

		// Calculate the new bounds
		CalcWndBounds (bounds, wParam);

		// Stop window from becoming too small
		if (bounds->right - bounds->left >= 640)
			gBounds = *bounds; else *bounds = gBounds;

		return TRUE;
	}

	// Call the SDL WndProc
	return CallWindowProc (gWndProc, hWnd, msg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Engine::InitWin32 (void)
{
	// Load icon from the embedded resource
	gIcon = LoadIcon (GetModuleHandle (NULL), L"ICON");

	// Get the window manager info
	SDL_SysWMinfo info;
	SDL_VERSION (&info.version)

	if (SDL_GetWMInfo (&info) < 0)
		Console::Fatal ("Unable to get the window manager: %s", SDL_GetError());

	// Get the window handle
	HWND gHWnd = info.window;

	// Set the window icon
	SetClassLongPtr (gHWnd, GCLP_HICON, (LONG_PTR) gIcon);

	// Redirect SDL WndProc
	gWndProc = (WNDPROC) SetWindowLongPtr (gHWnd, GWLP_WNDPROC, (LONG_PTR) WndProc);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Engine::ExitWin32 (void)
{
	// Destroy the icon
	DestroyIcon (gIcon);
}

#endif // Q_OS_WIN32



//----------------------------------------------------------------------------//
// Main                                                                       //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Main execution point for this application. </summary>
/// <param name="argc"> Number of arguments in the command line. </param>
/// <param name="argv"> Arguments from the command line. </param>
/// <returns> Zero for success, error code for failure. </returns>

int main (int argc, char **argv)
{
	QCoreApplication app (argc, argv);

	// Setup Application Info
	app.setApplicationVersion (QString (VERSION));
	app.setApplicationName    (QString (APPNAME));

#ifdef DEBUG
	// Create a debug console
	Console::Create();

	Console::Message ("%s - %s", APPNAME, VERSION);
	Console::Message ("-------------------\n" );
#endif

	// Invoke content processor
	if (argc > 1)
	{
		// Create a debug console
		Console::Create();
		Console::Clear();

		// Print introductory header
		Console::Message ("\nContent Compiler"                   );
		Console::Message ("-------------------------------------");
		Console::Message ("Copyright (C) 2012-2013 David Krutsko");

		// Parse through all arguments
		for (int i = 1; i < argc; ++i)
		{
			Console::Message();
			Content::Process (argv[i]);
		}
	}

	// Start game engine
	else forever
	{
		// Start the engine
		if (Engine::Start() == false) break;
		Console::Message ("\nEngine restarting...\n");
	}

#ifdef DEBUG
	// Wait debug console
	Console::Message ("\nPress enter to continue...");
	Console::Wait();
#endif

	return 0;
}

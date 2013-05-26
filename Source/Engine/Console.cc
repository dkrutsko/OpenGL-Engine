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

#include "Engine/Console.h"

#include <stdlib.h>
#include <QGlobal.h>

#ifdef Q_OS_WIN32

	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

	#include <io.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <fstream>
	#include <cstdarg>

	#define MAX_CONSOLE_LINES 5000

#endif



//----------------------------------------------------------------------------//
// Fields                                                             Console //
//----------------------------------------------------------------------------//

bool Console::mCreated = false;



//----------------------------------------------------------------------------//
// Static                                                             Console //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Create (void)
{
#ifdef Q_OS_WIN32

	if (mCreated) return;
	mCreated = true;

	FILE *fp;
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;

	// Allocate a console for this app
	AllocConsole();
	
	// Aet the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo (GetStdHandle
		(STD_OUTPUT_HANDLE), &coninfo);
	
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize (GetStdHandle
		(STD_OUTPUT_HANDLE), coninfo.dwSize);
	
	// Redirect unbuffered STDOUT to the console
	lStdHandle = (long) GetStdHandle (STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle (lStdHandle, _O_TEXT);
	
	fp = _fdopen (hConHandle, "w");
	*stdout = *fp;
	
	setvbuf (stdout, NULL, _IONBF, 0);
	
	// Redirect unbuffered STDIN to the console
	lStdHandle = (long) GetStdHandle (STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle (lStdHandle, _O_TEXT);
	fp = _fdopen (hConHandle, "r");

	*stdin = *fp;
	setvbuf (stdin, NULL, _IONBF, 0);

	// Redirect unbuffered STDERR to the console
	lStdHandle = (long) GetStdHandle (STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle (lStdHandle, _O_TEXT);
	fp = _fdopen (hConHandle, "w");
	*stderr = *fp;
	
	setvbuf (stderr, NULL, _IONBF, 0);
	
	// make cout, wcout, cin, wcin, wcerr, cerr,
	// wclog and clog point to console as well
	std::ios::sync_with_stdio();

	// Clear the Screen
	Clear();

#endif
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Clear (void)
{
#ifdef Q_OS_WIN32

	if (!mCreated) return;

	// Clear the Screen
	unsigned long count;
	COORD coord = {0, 0};
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo (hStdOut, &csbi);

	FillConsoleOutputCharacter (hStdOut, ' ',
		csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
	SetConsoleCursorPosition (hStdOut, coord);

#endif
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Message (void)
{
#ifdef Q_OS_WIN32

	if (!mCreated) return;
	printf ("\n");

#endif
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Message (const char* message, ...)
{
#ifdef Q_OS_WIN32

	if (!mCreated) return;

	va_list args;

	va_start (args, message);
	vprintf  (message, args);

	va_end (args);
	printf ("\n");

#endif
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Warning (const char* message, ...)
{
#ifdef Q_OS_WIN32

	if (!mCreated) return;

	printf ("WARNING: ");
	va_list args;

	va_start (args, message);
	vprintf  (message, args);

	va_end (args);
	printf ("\n");

#endif
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Error (const char* message, ...)
{
#ifdef Q_OS_WIN32

	if (!mCreated) return;

	printf ("ERROR: ");
	va_list args;

	va_start (args, message);
	vprintf  (message, args);

	va_end (args);
	printf ("\n");

#endif
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Fatal (const char* message, ...)
{
#ifdef Q_OS_WIN32

	if (!mCreated) return;

	printf ("FATAL: ");
	va_list args;

	va_start (args, message);
	vprintf  (message, args);

	va_end (args);
	printf ("\n");

#endif

	exit (0);
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Console::Wait (void)
{
#ifdef Q_OS_WIN32

	if (!mCreated) return;
	getchar();

#endif
}

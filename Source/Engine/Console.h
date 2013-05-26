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

#ifndef ENGINE_CONSOLE_H
#define ENGINE_CONSOLE_H

#include <QFileInfo.h>



//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#define GL_CHECK( execute )											\
	if (glGetError() != GL_NO_ERROR)								\
	{																\
		while (glGetError() != GL_NO_ERROR);						\
		execute;													\
	}																\

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#ifdef DEBUG

	#define GL_CALL( exp )											\
	{																\
		exp;														\
		GLenum _err_ = GL_NO_ERROR;									\
		do															\
		{															\
			_err_ = glGetError();									\
			if (_err_ != GL_NO_ERROR)								\
			{														\
				Console::Error ("%s in %s on line %d",				\
					gluErrorString (_err_), QFileInfo (__FILE__).	\
					fileName().toAscii().data(), __LINE__);			\
			}														\
																	\
		 } while (_err_ != GL_NO_ERROR);							\
	}

#else

	#define GL_CALL( exp ) exp

#endif



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Console
{
private:
	// Constructors
	 Console (void) { }
	 Console (const Console& console) { }
	~Console (void) { }

public:
	// Static
	static void Create	(void);
	static void Clear	(void);
	static void Message	(void);

	static void Message	(const char* message, ...);
	static void Warning	(const char* message, ...);
	static void Error	(const char* message, ...);
	static void Fatal	(const char* message, ...);

	static void Wait	(void);

private:
	// Fields
	static bool mCreated;
};

#endif // ENGINE_CONSOLE_H

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

#ifndef CONTENT_H
#define CONTENT_H

class Asset;
class Processor;
class QString;

#include <QMap.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Content
{
	friend class Asset;

private:
	// Constructors
	 Content (void) { }
	 Content (const Content& content) { }
	~Content (void) { }

public:
	// Static
	static Asset*		Load			(const QString& filename);
	static bool			Process			(const QString& filename);

	static Asset*		Reload			(Asset* asset);
	static void			UnloadAll		(void);

	static Processor*	FindProcessor	(const QString& extension);

private:
	// Map of all currently loaded assets
	static QMap<QString, Asset*> mLoaded;
};

#endif // CONTENT_H

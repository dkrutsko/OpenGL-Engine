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

#ifndef CONTENT_XML_PROCESSOR_H
#define CONTENT_XML_PROCESSOR_H

class QDomDocument;

#include "Content/Processor.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class XmlProcessor : public Processor
{
public:
	// Methods
	virtual Asset* Import		(QFile& file, Asset* asset = nullptr);

private:
	// Internal
	Asset* ImportModel			(QFile& file, QDomDocument& document, Asset* asset);
	Asset* ImportShader			(QFile& file, QDomDocument& document, Asset* asset);
	Asset* ImportParticleSystem	(QFile& file, QDomDocument& document, Asset* asset);
};

#endif // CONTENT_XML_PROCESSOR_H

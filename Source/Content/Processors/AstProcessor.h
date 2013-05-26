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

#ifndef CONTENT_AST_PROCESSOR_H
#define CONTENT_AST_PROCESSOR_H

class QIODevice;

#include "Content/Processor.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class AstProcessor : public Processor
{
public:
	// Methods
	virtual Asset*	Import (QFile& file, Asset* asset = nullptr);
	virtual bool	Export (QFile& file, const Asset* asset);

private:
	// Internal
	Asset* ImportModel			(QIODevice& device, Asset* asset);
	Asset* ImportShader			(QIODevice& device, Asset* asset);
	Asset* ImportParticleSystem	(QIODevice& device, Asset* asset);
	Asset* ImportTexture		(QIODevice& device, Asset* asset);

	bool ExportModel			(QIODevice& device, const Asset* asset);
	bool ExportShader			(QIODevice& device, const Asset* asset);
	bool ExportParticleSystem	(QIODevice& device, const Asset* asset);
	bool ExportTexture			(QIODevice& device, const Asset* asset);
};

#endif // CONTENT_AST_PROCESSOR_H

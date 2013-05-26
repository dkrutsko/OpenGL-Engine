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

#ifndef CONTENT_ASSET_H
#define CONTENT_ASSET_H

#include <QString.h>



//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#define ASSET_DECLARATION				\
	public:								\
		static const quint16 AssetID;	\
										\
	private:

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

#define ASSET_DEFINITION( ClassName )	\
	const quint16 ClassName::AssetID = Asset::GenAssetID();



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Asset
{
	friend class Content;

public:
	// Constructors
	Asset (quint16 assetType);
	Asset (const Asset& asset);

protected:
	virtual ~Asset (void) { }

public:
	// Methods
	quint16			GetAssetID		(void) const { return mAssetID;		}
	quint16			GetReferences	(void) const { return mReferences;	}

	void			Retain			(void);
	void			Release			(bool force = false);

	const QString&	GetSource		(void) { return mSource;	}
	bool			IsManaged		(void) { return mManaged;	}

public:
	// Static
	static quint16	GenAssetID		(void) { return ++mAssetIDCounter;	}

protected:
	// Fields
	bool			mManaged;		// Asset is managed
	quint16			mAssetID;		// Asset type ID
	quint16			mReferences;	// References to this asset
	QString			mSource;		// Source of this asset

private:
	// State of the asset ID generator
	static quint16	mAssetIDCounter;

	// Assets loaded by the Content Manager are managed
};

#endif // CONTENT_ASSET_H

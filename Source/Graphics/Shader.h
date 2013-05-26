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

#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

class Color;
class Matrix;
class Vector2;
class Vector3;
class Vector4;
class Quaternion;
class Texture;

#include "Content/Asset.h"



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Shader : public Asset
{
	ASSET_DECLARATION;

public:
	// Constructors
	Shader						(void);
	Shader						(const Shader& shader);

protected:
	virtual ~Shader				(void);

public:
	// Methods
	void		Create			(void);

	bool		Load			(void);
	bool		Reload			(bool force = false);
	void		Unload			(bool force = false);

	void		Purge			(bool force = false);

	bool		IsLoaded		(void) const;
	bool		IsPurged		(void) const;

	void		Use				(void) const;

	quint32		GetVertexID		(void) const { return mVertexID;	}
	quint32		GetFragmentID	(void) const { return mFragmentID;	}
	quint32		GetProgramID	(void) const { return mProgramID;	}

public:
	// Accessors
	void		SetValue		(const QString& name, bool				value);
	void		SetValue		(const QString& name, float				value);
	void		SetValue		(const QString& name, qint32			value);
	void		SetValue		(const QString& name, quint32			value);

	void		SetValue		(const QString& name, const Matrix&		value);
	void		SetValue		(const QString& name, const Vector2&	value);
	void		SetValue		(const QString& name, const Vector3&	value);
	void		SetValue		(const QString& name, const Vector4&	value);
	void		SetValue		(const QString& name, const Quaternion&	value);

	void		SetValue		(const QString& name, const Color&		value);
	void		SetValue		(const QString& name, const Texture*	value, quint8 index);

public:
	// Properties
	QByteArray	Vertex;			// Vertex   shader source
	QByteArray	Fragment;		// Fragment shader source

private:
	// Fields
	quint32		mVertexID;		// OpenGL vertex ID
	quint32		mFragmentID;	// OpenGL fragment ID
	quint32		mProgramID;		// OpenGL program ID
};

#endif // GRAPHICS_SHADER_H

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

#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

class Shader;
class Material;

class VertexBuffer;
class IndexBuffer;
class VertexElement;

#include <QString.h>



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

class Mesh
{
public:
	// Constructors
	 Mesh (void);
	~Mesh (void);
	 Mesh (const Mesh& mesh);

public:
	// Methods
	bool			Load		(void);
	bool			Reload		(void);
	void			Unload		(void);

	void			Purge		(void);

	bool			IsLoaded	(void) const;
	bool			IsPurged	(void) const;

	void			Draw		(void) const;

	quint32			GetArrayID	(void) const		{ return mArrayID;		}
	VertexBuffer*	GetVertices	(void) const		{ return mVertices;		}
	IndexBuffer*	GetIndices	(void) const		{ return mIndices;		}

	bool Create (quint32 vertexCount, quint8 elementCount,
		const VertexElement* elements, quint32 indexCount, quint8 indexSize);

public:
	// Static
	static void CreateQuad (Mesh& mesh, float x1, float y1,
		float x2, float y2, bool xFlip = false, bool yFlip = false);

	static void CreateQuad (Mesh& mesh, float x1, float y1,
		float x2, float y2, float mx1, float my1, float mx2,
		float my2, bool xFlip = false, bool yFlip = false);

public:
	// Properties
	qint32			Material;	// Mesh Material reference
	QString			Name;		// Mesh name

protected:
	// Fields
	quint32			mArrayID;	// OpenGL array ID

	VertexBuffer*	mVertices;	// Mesh vertex buffer
	IndexBuffer*	mIndices;	// Mesh index  buffer
};

#endif // GRAPHICS_MESH_H

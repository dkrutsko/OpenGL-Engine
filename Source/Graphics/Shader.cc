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

#include "Graphics/Shader.h"
ASSET_DEFINITION (Shader);

#include "Graphics/Color.h"
#include "Graphics/Texture.h"

#include "Math/Matrix.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"

#define GLEW_STATIC
#include <glew.h>



//----------------------------------------------------------------------------//
// Constructors                                                        Shader //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Shader::Shader (void) : Asset (AssetID)
{
	mVertexID   = 0;
	mFragmentID = 0;
	mProgramID  = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Shader::Shader (const Shader& shader) : Asset (shader)
{
	mVertexID   = 0;
	mFragmentID = 0;
	mProgramID  = 0;

	Vertex   = shader.Vertex;
	Fragment = shader.Fragment;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

Shader::~Shader (void)
{
	Unload (true);
}



//----------------------------------------------------------------------------//
// Methods                                                             Shader //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::Create (void)
{
	// Purge shader data
	Vertex  .clear();
	Fragment.clear();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Shader::Load (void)
{
	// Check if already loaded
	if (mProgramID != 0) return true;

	// Check if the data has been purged
	if (Vertex  .isEmpty() &&
		Fragment.isEmpty())
		{ Unload(); return false; }

	// Create shader IDs
	GL_CALL (mProgramID  = glCreateProgram());
	GL_CALL (mVertexID   = glCreateShader (GL_VERTEX_SHADER  ));
	GL_CALL (mFragmentID = glCreateShader (GL_FRAGMENT_SHADER));

	// Point shaders to source
	const char* vertex   = Vertex  .data();
	const char* fragment = Fragment.data();

	GL_CALL (glShaderSource  (mVertexID,   1, &vertex,   NULL));
	GL_CALL (glShaderSource  (mFragmentID, 1, &fragment, NULL));

	// Compile and link
	GL_CALL (glCompileShader (mVertexID  ));
	GL_CALL (glCompileShader (mFragmentID));

	// Check vertex shader
	GLint vertStatus;
	glGetShaderiv (mVertexID, GL_COMPILE_STATUS, &vertStatus);
	if (vertStatus != GL_TRUE)
		Console::Error ("Unable to compile vertex shader: %s", mSource.toAscii().data());

	// Check fragment shader
	GLint fragStatus;
	glGetShaderiv (mFragmentID, GL_COMPILE_STATUS, &fragStatus);
	if (fragStatus != GL_TRUE)
		Console::Error ("Unable to compile fragment shader: %s", mSource.toAscii().data());

	// Cancel load if unable to compile
	if (vertStatus != GL_TRUE || fragStatus != GL_TRUE) { Unload(); return false; }

	// Link the shaders
	GL_CALL (glAttachShader (mProgramID, mVertexID  ));
	GL_CALL (glAttachShader (mProgramID, mFragmentID));
	GL_CALL (glLinkProgram  (mProgramID));

	// Check link status
	GLint linkStatus;
	glGetProgramiv  (mProgramID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		Console::Error ("Unable to link shaders: %s", mSource.toAscii().data());
		Unload(); return false;
	}

	// Check for any additional errors
	GL_CHECK (Unload (true); return false);

	// All done
	return true;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Shader::Reload (bool force)
{
	Unload (force); return Load();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::Unload (bool force)
{
	// Check for multiple references
	if (!force && mReferences > 1) return;

	// Check if already unloaded
	if (mProgramID == 0) return;

	// Delete the shader objects
	GL_CALL (glUseProgram   (0));
	GL_CALL (glDetachShader (mProgramID, mVertexID  ));
	GL_CALL (glDetachShader (mProgramID, mFragmentID));

	GL_CALL (glDeleteShader  (mVertexID));
	GL_CALL (glDeleteShader  (mFragmentID));
	GL_CALL (glDeleteProgram (mProgramID));

	mVertexID   = 0;
	mFragmentID = 0;
	mProgramID  = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::Purge (bool force)
{
	// Check for multiple references
	if (!force && mReferences > 1) return;

	// Purge shader data
	Vertex  .clear();
	Fragment.clear();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Shader::IsLoaded (void) const
{
	return mProgramID != 0;
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

bool Shader::IsPurged (void) const
{
	return Vertex  .isEmpty() &&
		   Fragment.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::Use (void) const
{
	GLint current;
	GL_CALL (glGetIntegerv (GL_CURRENT_PROGRAM, &current));

	if (current != mProgramID)
		GL_CALL (glUseProgram (mProgramID));
}



//----------------------------------------------------------------------------//
// Accessors                                                           Shader //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, bool value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform1i (glGetUniformLocation (mProgramID, name.toAscii().data()), value ? 1 : 0));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, float value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform1f (glGetUniformLocation (mProgramID, name.toAscii().data()), value));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, qint32 value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform1i (glGetUniformLocation (mProgramID, name.toAscii().data()), value));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, quint32 value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform1ui (glGetUniformLocation (mProgramID, name.toAscii().data()), value));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, const Matrix& value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniformMatrix4fv (glGetUniformLocation (mProgramID,
		name.toAscii().data()), 1, GL_TRUE, (GLfloat*) &value));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, const Vector2& value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform2f (glGetUniformLocation (mProgramID,
		name.toAscii().data()), value.X, value.Y));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, const Vector3& value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform3f (glGetUniformLocation (mProgramID,
		name.toAscii().data()), value.X, value.Y, value.Z));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, const Vector4& value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform4f (glGetUniformLocation (mProgramID,
		name.toAscii().data()), value.X, value.Y, value.Z, value.W));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, const Quaternion& value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform4f (glGetUniformLocation (mProgramID,
		name.toAscii().data()), value.X, value.Y, value.Z, value.W));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, const Color& value)
{
	if (mProgramID == 0) return; Use();
	GL_CALL (glUniform4f (glGetUniformLocation (mProgramID,
		name.toAscii().data()), value.R, value.G, value.B, value.A));
}

////////////////////////////////////////////////////////////////////////////////
/// <summary> </summary>

void Shader::SetValue (const QString& name, const Texture* value, quint8 index)
{
	if (mProgramID == 0) return; Use();

	if (value == nullptr)
	{
		GL_CALL (glUniform1i (glGetUniformLocation (mProgramID, name.toAscii().data()), 0));
	}

	else
	{
		GL_CALL (glActiveTexture (GL_TEXTURE0 + index));

		GL_CALL (glBindTexture (GL_TEXTURE_2D, value->GetTexID()));
		GL_CALL (glUniform1i   (glGetUniformLocation (mProgramID, name.toAscii().data()), index));
	}
}

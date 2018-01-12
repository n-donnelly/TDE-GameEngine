#include "Texture.h"

using namespace std;

namespace TDE
{
	Texture::Texture()
	{
		mGLTex = 0;
		mFileName = "";
		mWidth = 0;
		mHeight = 0;
		mBPP = 0;
		mFormat = GL_RGB;
		mError = 0;
	}

	Texture::Texture(GLuint glTex, std::string fileName, float width, float height, GLint aNumColors, GLenum aFormat, void* raw)
	{
		mGLTex = glTex;
		mFileName = fileName;
		mFilePath = fileName;
		mWidth = width;
		mHeight = height;
		mBPP = aNumColors;
		mFormat = aFormat;
		mRawData = raw;
		mError = 0;
	}

	Texture::~Texture()
	{
	}

	float Texture::GetHeight()
	{
		return mHeight;
	}

	float Texture::GetWidth()
	{
		return mWidth;
	}

	GLuint Texture::GetTex()
	{
		return mGLTex;
	}

	string Texture::GetName()
	{
		return mFileName;
	}

	void Texture::SetName(string aName)
	{
		mFileName = aName;
	}

	string Texture::GetPath()
	{
		return mFilePath;
	}

	void Texture::SetError(int err)
	{
		mError = err;
	}

	int Texture::GetError()
	{
		return mError;
	}
}
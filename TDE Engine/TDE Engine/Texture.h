#ifndef TEXTURE_H
#define TEXTURE_H

#include "Includes.h"

using namespace std;

namespace TDE
{
	class Texture
	{
	public:
		Texture();
		Texture(GLuint glTex, string fileName, float width, float height, GLint aNumColors, GLenum aFormat, void* raw);
		~Texture();
		float GetWidth();
		float GetHeight();
		GLuint GetTex();
		string GetName();
		string GetPath();
		void* GetData() { return mRawData; };
		void SetName(string aName);
		GLint GetBPP() { return mBPP; };
		GLenum GetFormat() { return mFormat; };
		void SetError(int err);
		int GetError();

	private:
		GLuint		mGLTex;
		string		mFileName;
		string		mFilePath;
		float		mWidth;
		float		mHeight;
		GLint		mBPP;
		GLenum		mFormat;
		void*		mRawData;
		int			mError;
	};
}

#endif
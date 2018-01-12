#ifndef TDEIMAGE_H
#define TDEIMAGE_H

#include "Texture.h"
#include <cmath>

using namespace std;

namespace TDE
{

	class TDEImage
	{
	public:
		TDEImage();
		TDEImage(std::string texName, int x, int y, int width, int height, string fileName);
		TDEImage(std::string texName, float x, float y, float width, float height, string fileName);
		~TDEImage();

		int GetWidth() { return mWidth; };
		int GetHeight() { return mHeight; };
		string GetName() { return mName; };
		int GetAtlasX() { return mAtlasX; };
		int GetAtlasY() { return mAtlasY; };
		string GetTexRef() { return mTexRef; };

	private:
		string		mTexRef;
		string		mName;
		int			mAtlasX;
		int			mAtlasY;
		int			mWidth;
		int			mHeight;
	};

}
#endif
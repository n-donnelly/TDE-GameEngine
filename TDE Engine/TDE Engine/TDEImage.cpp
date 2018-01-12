#include "TDEImage.h"

using namespace std;

namespace TDE
{
	TDEImage::TDEImage(void)
	{
		mTexRef = "";
		mAtlasX = 0;
		mAtlasY = 0;
		mWidth = 0;
		mHeight = 0;
	}

	TDEImage::TDEImage(string TexName, int x, int y, int width, int height, string fileName)
	{
		if(TexName.size() == 0 || fileName.size() == 0)
			return;

		mTexRef = TexName;
		mAtlasX = x;
		mAtlasY = y;
		mWidth = width;
		mHeight = height;
		mName = fileName;
	}

	TDEImage::TDEImage(string TexName, float x, float y, float width, float height, string fileName)
	{
		if(TexName.size() == 0 || fileName.size() == 0)
			return;

		mTexRef = TexName;
		mName = fileName;

		float diff = fmod(x,1.f);
		if(diff < 0.49f)
			mAtlasX = (int)x;
		else
			mAtlasX = (int)(x + 1);

		diff = fmod(y,1.f);
		if(diff < 0.49f)
			mAtlasY = (int)y;
		else
			mAtlasY = (int)(y + 1);

		diff = fmod(width,1.f);
		if(diff < 0.49f)
			mWidth = (int)width;
		else
			mWidth = (int)(width + 1);

		diff = fmod(height,1.f);
		if(diff < 0.49f)
			mHeight = (int)height;
		else
			mHeight = (int)(height + 1);
	}

	TDEImage::~TDEImage(void)
	{
	}
}
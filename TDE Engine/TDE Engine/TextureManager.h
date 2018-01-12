#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Texture.h"
#include "TDEImage.h"
#include <map>

using namespace std;

namespace TDE
{
	class TextureManager
	{
	public:
		TextureManager(void);
		~TextureManager(void);

		bool LoadAtlasesFromXML(const char* aPath, TDEColor alphaKey = TDEColor(-1,-1,-1));
		Texture LoadAtlas(const char* aPath);
		bool LoadImage(const char* aPath, const char* name);
		bool LoadImage(const char* aPath, const char* name, int imWidth, int imHeight);
		TDEImage* GetImage(string aImageName);
		Texture* GetTexture(string texName);

		int GetNumImages() { return mNumImages; };
		int GetNumAtlases() { return mNumAtlases; };

		//DEBUG only
		void PrintAtlases();
		void PrintImages();
		
	protected:
		Texture LoadTexFromSurface(SDL_Surface* aSurface, const char* aSurfPath);
		void AddImage(TDEImage aImage);
		std::string GetXMLValue(char* valString, std::string theLine);
		TDEImage MakeImage(std::string theLine, string texName);
		void MakeResources(fstream* theStream, std::string resPath, char* line);
		SDL_Color TranslateColor(Uint32 intCol);

	private:
		std::map<string, Texture> glAtlases;
		std::map<string, TDEImage> mImages;

		TDEColor	mColorKey;
		int			mNumImages;
		int			mNumAtlases;
	};
}

#endif
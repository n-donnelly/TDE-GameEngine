#include "FontManager.h"

using namespace std;

namespace TDE
{
	FontManager::FontManager(void)
	{
		mNumFonts = 0;
		if(TTF_Init())
		{
			printf("Error Loading Fonts\n");
			exit(1);
		}
	}

	FontManager::~FontManager(void)
	{
		TTF_Quit();
	}

	/*
	* Adds Font object to the Font Manager map
	*/
	bool FontManager::AddFont(TDE_Font font)
	{
		if(!font.validateFont())
			return false;

		std::string name = font.GetName();

		//An entry with the same name already exists
		map<string, TDE_Font>::iterator it = mFontMap.find(name);
		if(it != mFontMap.end())
			return false;

		mFontMap.insert(std::pair<std::string, TDE_Font>(name, font));
		mNumFonts++;
		return true;
	}

	/*
	* Returns a Font pointer matching the string
	*/
	TDE_Font* FontManager::GetFont(std::string fontName)
	{
		if(fontName.length() == 0)
			return NULL;

		map<string, TDE_Font>::iterator it = mFontMap.find(fontName);
		return it == mFontMap.end() ? NULL : &(it->second);
	}

	//Returns number of stored fonts
	int FontManager::GetNumFonts()
	{
		return mNumFonts;
	}

	//Removes the given font from the map
	bool FontManager::RemoveFont(string fontName)
	{
		mFontMap.erase(mFontMap.find(fontName));
		mNumFonts = mFontMap.size();
		return true;
	}

	//Loads the font from the given fontPath
	bool FontManager::LoadFont(string fontName, string fontPath, int size)
	{
		if(fontName.length() == 0)
			return false;
		TDE_Font f = TDE_Font(fontName, fontPath, size);
		bool success = f.validateFont();
		if(success) AddFont(f);

		return success;
	}
}
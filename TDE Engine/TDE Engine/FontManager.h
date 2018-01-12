#ifndef FONT_MGR
#define FONT_MGR

#include "TDE_Font.h"
#include <map>

namespace TDE
{
	class FontManager
	{
	public:
		FontManager(void);
		~FontManager(void);

		bool AddFont(TDE_Font font);
		TDE_Font* GetFont(std::string fontName);
		bool LoadFont(std::string fontName, std::string fontPath, int size);
		int GetNumFonts();
		bool RemoveFont(std::string fontName);

	private:
		int		mNumFonts;

		std::map<std::string, TDE_Font>		mFontMap;
	};
}

#endif
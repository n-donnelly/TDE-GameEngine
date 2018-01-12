#ifndef TDEFONT
#define TDEFONT

#include <string>
#include "SDL_ttf.h"

namespace TDE
{

	class TDE_Font
	{
	public:
		TDE_Font(std::string name, std::string path, int size);
		TDE_Font(void);
		~TDE_Font(void);

		std::string GetName();
		int GetSize();
		void SetSize(int s);
		void SetBold(bool b);
		void SetItalic(bool b);
		void SetUnderlined(bool b);
		bool validateFont();
		int GetHeight();
		TTF_Font* GetTTFFont();

	private:
		void UpdateStyle();

		std::string		name;
		std::string		path;
		int				size;
		int				style;
		TTF_Font*		font;

		bool			bold;
		bool			underlined;
		bool			italic;
	
	};
}
#endif

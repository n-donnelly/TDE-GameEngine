#include "TDE_Font.h"

namespace TDE
{
	TDE_Font::TDE_Font(std::string name, std::string path, int size)
	{
		this->name = name;
		this->path = path;
		this->size = size < 16 ? 16 : size;

		font = TTF_OpenFont(path.c_str(), this->size);

		bold = false;
		italic = false;
		underlined = false;
	}

	TDE_Font::TDE_Font(void)
	{
		this->name = "";
		this->path = "";
		this->size = 0;

		font = NULL;

		bold = false;
		italic = false;
		underlined = false;
	}


	TDE_Font::~TDE_Font(void)
	{
	}

	bool TDE_Font::validateFont()
	{
		return font != NULL;
	}

	std::string TDE_Font::GetName()
	{
		return name;
	}

	int TDE_Font::GetSize()
	{
		return size;
	}

	void TDE_Font::SetSize(int s)
	{
		TTF_CloseFont(font);
		font = TTF_OpenFont(path.c_str(), s);
		size = s;
	}

	void TDE_Font::SetBold(bool b)
	{
		bold  = b;
		UpdateStyle();
	}

	void TDE_Font::SetItalic(bool i)
	{
		italic  = i;
		UpdateStyle();
	}

	void TDE_Font::SetUnderlined(bool u)
	{
		underlined  = u;
		UpdateStyle();
	}

	void TDE_Font::UpdateStyle()
	{
		if(italic && bold && underlined)
			TTF_SetFontStyle(font, TTF_STYLE_ITALIC|TTF_STYLE_BOLD|TTF_STYLE_UNDERLINE);
		else if(italic && bold)
			TTF_SetFontStyle(font, TTF_STYLE_ITALIC|TTF_STYLE_BOLD);
		else if(italic && underlined)
			TTF_SetFontStyle(font, TTF_STYLE_ITALIC|TTF_STYLE_UNDERLINE);
		else if(underlined && bold)
			TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE|TTF_STYLE_BOLD);
		else if(bold)
			TTF_SetFontStyle(font, TTF_STYLE_BOLD);
		else if(italic)
			TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
		else if(underlined)
			TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);
		else TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	}

	int TDE_Font::GetHeight()
	{
		return TTF_FontHeight(font);
	}

	TTF_Font* TDE_Font::GetTTFFont()
	{
		return font;
	}
}
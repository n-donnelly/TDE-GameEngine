#include "TDEColor.h"

namespace TDE
{
	TDEColor::TDEColor(void)
	{
	}


	TDEColor::~TDEColor(void)
	{
	}

	TDEColor::TDEColor(float red, float green, float blue, float alpha)
	{
		m_fRed = red;
		m_fGreen = green;
		m_fBlue = blue;
		m_fAlpha = alpha;

		m_iRed = (int)(255 * red);
		m_iGreen = (int)(255 * green);
		m_iBlue = (int)(255 * blue);
		m_iAlpha = (int)(255 * alpha);
	}

	TDEColor::TDEColor(int red, int green, int blue, int alpha)
	{
		m_iRed = red;
		m_iGreen = green;
		m_iBlue = blue;
		m_iAlpha = alpha;

		m_fRed = ((float)red)/255.f;
		m_fGreen = ((float)green)/255.f;
		m_fBlue = ((float)blue)/255.f;
		m_fAlpha = ((float)alpha)/255.f;
	}

	SDL_Color TDEColor::GetSDLColor()
	{
		SDL_Color ret;
		ret.b = m_iBlue;
		ret.g = m_iGreen;
		ret.r = m_iRed;

		return ret;
	}
}

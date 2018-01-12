#ifndef TDECOLOR_H
#define TDECOLOR_H

#include <SDL.h>

namespace TDE
{
	class TDEColor
	{
	public:
		TDEColor();
		TDEColor(float red, float green, float blue, float alpha = 1.f);
		TDEColor(int red, int green, int blue, int alpha = 255);
		~TDEColor();

		SDL_Color GetSDLColor();

		float m_fRed;
		float m_fBlue;
		float m_fGreen;
		float m_fAlpha;

		int m_iRed;
		int m_iBlue;
		int m_iGreen;
		int m_iAlpha;
	};
}

#endif
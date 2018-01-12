#ifndef GLGRAPHICS_H
#define GLGRAHPICS_H

#include "Includes.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "AnimationManager.h"

namespace TDE
{
	class TDEGraphicsState
	{
	public:
		TDEGraphicsState();
		TDEGraphicsState(TDEColor color, float scale, Rect clip, TDE_Font* font, Pointf trans);
		~TDEGraphicsState();
		void EmptyState();

		friend class TDEGraphics;

	protected:
		TDE_Font* mFont;
		TDEColor mColor;
		float mScale;
		Rect mClipRect;
		Pointf mTransPoint;
	};

	class TDEGraphics
	{
	public:
		TDEGraphics(void);
		TDEGraphics(TextureManager* aTexMan, AnimationManager* aAnimMgr, FontManager* aFontMan);
		~TDEGraphics(void);
		void InitGraphics(float width, float height, char* winName);
		bool CreateWin(bool wantFullscreen, int BytesPerPixel = 0);
		void Shutdown();

		void InitDraw();
		void EndDraw();
		void UpdateAnims();

		void ToggleFullscreen();
		void ResizeGLWin(int aWidth, int aHeight);
		void ClearScreen(TDEColor color);
		void Translate(int newX, int newY);
		void Translate(float newX, float newY);

		float GetHeight() { return mHeight; };
		float GetWidth() { return mWidth; };
		Pointf GetTransPoint() { return Pointf(mTransX, mTransY);};
		
		void DrawImage(TDEImage* im, float x, float y);
		void DrawImage(TDEImage* im, int x, int y);
		void DrawImage(TDEImage* im, Rect destRect);
		void DrawImage(TDEImage* im, Rect destRet, Rect srcRect);
		void DrawImage(TDEImage* im, Rect srcRect, float x, float y);
		TDEImage* GetImage(std::string name);

		void DrawRotatedImage(TDEImage* im, float x, float y, float angle);
		void DrawRotatedImage(TDEImage* im, Rect destRect, Rect srcRect, float angle);

		void DrawAnimation(TDE_Animation* anim, float x, float y);
		void DrawAnimation(TDE_Animation* anim, int x, int y);
		void DrawAnimation(TDE_Animation* anim, Rect destRect);
		void DrawAnimation(TDE_Animation* anim, Rect destRect, Rect srcRect);
		void DrawAnimation(TDE_Animation* anim, Rect srcRect, float x, float y);

		void DrawRotatedAnim(TDE_Animation* anim, float x, float y, float angle);
		void DrawRotatedAnim(TDE_Animation* anim, Rect destRect, Rect srcRect, float angle);

		TDE_Animation GetAnim(std::string name);

		void DrawRect(float x, float y, float width, float height);
		void DrawRect(int x, int y, int width, int height);
		void DrawRect(Rect drawRect);
		void DrawRect(Rect drawRect, float angle);

		void FillRect(float x, float y, float width, float height);
		void FillRect(int x, int y, int width, int height);
		void FillRect(Rect drawRect);
		void FillRect(Rect drawRect, float angle);

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2, TDEColor color);

		void DrawShape(int verts[][2], int numPoints);
		void DrawShape(float verts[][2], int numPoints);
		void DrawShape(float verts[][2], int numPoints, TDEColor color);

		void DrawString(std::string str, float x, float y);
		void DrawString(std::string str, int x, int y);
		void DrawString(std::string str, int x, int y, TDEColor color);
		void DrawString(std::string str, int x, int y, TDE_Font* font);
		void DrawString(std::string str, int x, int y, TDEColor color, TDE_Font* font);

		void LoadFont(string name);
		TDE_Font* GetFont();
		bool LoadTTF(string name, string path);
		int GetFontHeight();
		int GetStringWidth(string s);

		void SetColor(TDEColor col);
		void SetColor(float fRed, float fGreen, float fBlue, float fAlpha = 1.f);
		void SetColor(int iRed, int iGreen, int iBlue, int iAlpha = 255);
		void ClearColor();

		TDEColor GetColor();

		void EnableClipping(bool enable);
		void SetClipRect(Rect clip);
		void SetClipRect(float x, float y, float width, float height);
		void SetClipRect(int x, int y, int width, int height);

		Rect GetClipRect();

		void SetScale(float scale);
		float GetScale();

		void PushState();
		void PopState();

		bool LoadTDEImage(std::string path, std::string name);
		bool LoadAtlasFromXML(std::string filePath, TDEColor alphaKey = TDEColor(-1,-1,-1,-1));
		bool DropAtlas(std::string fileName);

		bool LoadAnim(std::string path, std::string name, int cellWidth, int cellHeight, int numCells);
		bool LoadAnim(std::string path, std::string name, int cellWidth, int cellHeight, int totalWidth, int totalHeight, int numCells);
		bool LoadAnimFromImage(std::string name, TDEImage* im, int cellWidth, int cellHeight, int numCells);
		bool CreateAnim(std::string name, TDEImage* cells[], int numCells);

		Texture* GetTexture(std::string texName);
		void ColorizeImages(bool cIm);

		AnimationManager* GetAnimMgr();
		TextureManager* GetTexMgr();

	private:
		void InitGL();

		void ActivateColor();
		void ActivateClipRect();

		void ApplyRotation(float angle, float pointX, float pointY);
		int RoundFloat(float f);
		int getNextPow2(int x);

		std::stack<TDEGraphicsState> mStates;

		TDEGraphicsState mCurrentState;
		float			mWidth;
		float			mHeight;
		std::string		mWinTitle;
		Texture*		mCurrentTexture;
		TDEColor		mColor;
		Rect			mClipRect;
		float			mScale;
		TDE_Font*		mFont;

		float			mTransX;
		float			mTransY;

		TextureManager*			mTextureManager;
		FontManager*			mFontManager;
		AnimationManager*		mAnimMgr;

		bool			mFullscreen;
		Uint32			mSDLFlags;
		SDL_Surface*	mSurface;
		int				mBpp;

		bool			mWantColorize;
	};
}
#endif
#include "TDEGraphics.h"
#include <iostream>
#include <math.h>

namespace TDE
{

	TDEGraphicsState::TDEGraphicsState()
	{
		mColor = TDEColor(0,0,0,0);
		mScale = 1.f;
		mClipRect.x = 0;
		mClipRect.y = 0;
		mClipRect.width = _WIDTH;
		mClipRect.height = _HEIGHT;
		mTransPoint.x = 0.f;
		mTransPoint.y = 0.f;
	}

	TDEGraphicsState::TDEGraphicsState(TDEColor color, float scale, Rect clip, TDE_Font* font, Pointf trans)
	{
		mColor = color;
		mScale = scale;
		mClipRect = clip;
		mFont = font;
		mTransPoint = trans;
	}

	TDEGraphicsState::~TDEGraphicsState()
	{
	}

	void TDEGraphicsState::EmptyState()
	{
		mColor = TDEColor(0,0,0,0);
		mScale = 1.f;
		mClipRect.x = 0;
		mClipRect.y = 0;
		mClipRect.width = _WIDTH;
		mClipRect.height = _HEIGHT;
		mFont = NULL;
	}

	TDEGraphics::TDEGraphics(void)
	{
		mTextureManager = new TextureManager();
		mFontManager = new FontManager();
		mAnimMgr = new AnimationManager(mTextureManager);
		mCurrentTexture = NULL;
		mScale = 1.f;
	}


	TDEGraphics::~TDEGraphics(void)
	{
	}

	TDEGraphics::TDEGraphics(TextureManager* aTexMan, AnimationManager* aAnimMgr, FontManager* aFontMan)
	{
		if(aTexMan)
			mTextureManager = aTexMan;
		if(aAnimMgr)
			mAnimMgr = aAnimMgr;
		if(aFontMan)
			mFontManager = aFontMan;
		mCurrentState = TDEGraphicsState();
		mWidth = 0.f;
		mHeight = 0.f;
		mWinTitle = "";
		mCurrentTexture = NULL;
		mColor = TDEColor(255,255,255);
		mClipRect = Rect(0,0,0,0);
		mScale = 1.f;
		mFont = NULL;
		mTransX = 0.f;
		mTransY = 0.f;
		mFullscreen = false;
		mSDLFlags = 0;
		mSurface = 0;
		mBpp = 0;
		mWantColorize = false;
	}

	void TDEGraphics::InitGraphics(float width, float height, char* winName)
	{
		mFullscreen = false;
		mWidth = width;
		mHeight = height;
		mWinTitle = string(winName);

		mClipRect.x = 0;
		mClipRect.y = 0;
		mClipRect.width = RoundFloat(width);
		mClipRect.height = RoundFloat(height);

		mTransX = 0;
		mTransY = 0;

		mFontManager->LoadFont("Gothic", "C:\\Users\\Neil\\Documents\\Visual Studio 2012\\Projects\\TDE Engine\\TDE Engine\\GOTHIC.ttf", 24);
		mFont = mFontManager->GetFont("Gothic");

		mColor = TDEColor(255,255,255);
		mScale = 1.f;

		mCurrentState = TDEGraphicsState(mColor, mScale, mClipRect, mFont, Pointf(mTransX, mTransY));

		mWantColorize = false;
	}

	void TDEGraphics::InitGL()
	{
		glShadeModel( GL_SMOOTH );
		glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );
		glClearDepth( 0.0f );
		glDisable( GL_DEPTH_TEST );
		glDisable(GL_LIGHTING);

		//glEnable(GL_ALPHA_TEST);
		//glAlphaFunc(GL_GREATER, 0.75f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_SCISSOR_TEST);

		//setup ortho mode
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0, (GLfloat)mWidth, (GLfloat)mHeight, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glLoadIdentity();
	}

	void TDEGraphics::Shutdown()
	{
		return;
	}

	void TDEGraphics::InitDraw()
	{
		//Clear color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0,0,0,0);

		if(mCurrentTexture)
		{
			glBindTexture(GL_TEXTURE_2D, mCurrentTexture->GetTex());
		}

		//Load identity matrix
		glLoadIdentity();

		//Apply scale
		glScaled((GLfloat) mScale, (GLfloat) mScale, 1.f);
	}

	void TDEGraphics::EndDraw()
	{
		SDL_GL_SwapBuffers();
	}

	void TDEGraphics::UpdateAnims()
	{
		mAnimMgr->UpdateAll();
	}

	bool TDEGraphics::CreateWin(bool wantFullscreen, int BytesPerPixel)
	{
		mBpp = BytesPerPixel;
		if(SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			cout << "Error creating window" << SDL_GetError() << endl;
			exit(1);
		}

		mSDLFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;

		const SDL_VideoInfo* vidInfo = SDL_GetVideoInfo();

		mSDLFlags |= vidInfo->hw_available ? SDL_HWSURFACE : SDL_SWSURFACE;

		if(vidInfo->blit_hw)
			mSDLFlags |= SDL_HWACCEL;

		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

		atexit(SDL_Quit);

		mSurface = SDL_SetVideoMode((int)mWidth, (int)mHeight, mBpp, mSDLFlags);

		if(wantFullscreen && !mFullscreen)
		{
			ToggleFullscreen();
		}
		if(mSurface == NULL)
		{
			cout << "Video failed initialisation: " << SDL_GetError() << endl;
			SDL_Quit();
		}

		InitGL();

		SDL_WM_SetCaption(mWinTitle.c_str(), NULL);

		return true;
	}

	void TDEGraphics::ToggleFullscreen()
	{
		mFullscreen = !mFullscreen;

		if(mSurface != NULL)
		{
			const SDL_VideoInfo* info = SDL_GetVideoInfo();
			mWidth = (float)info->current_w;
			mHeight = (float)info->current_h;

			mSurface = SDL_SetVideoMode((int)mWidth, (int)mHeight, 0, mSurface->flags ^ SDL_FULLSCREEN); /*Toggles FullScreen Mode */
			if(mSurface == NULL) mSurface = SDL_SetVideoMode(0, 0, 0, mSDLFlags);
			SDL_ShowCursor(mFullscreen ? SDL_DISABLE : SDL_ENABLE);
		}
	}

	void TDEGraphics::ResizeGLWin(int aWidth, int aHeight)
	{
		//Checks to prevent a divide by zero error
		aHeight = aHeight == 0 ? 1 : aHeight;

		mSurface = SDL_SetVideoMode(aWidth, aHeight, mBpp, mSDLFlags);

		if(mSurface == NULL)
		{
			cout << "Couldn't resize: " << SDL_GetError() << endl;
			exit(1);
		}

		mWidth = (float)aWidth;
		mHeight = (float)aHeight;
		InitGL();
	}

	void TDEGraphics::ClearScreen(TDEColor color)
	{
		glClearColor(color.m_fRed, color.m_fGreen, color.m_fBlue, color.m_fAlpha);
	}

	TDEImage* TDEGraphics::GetImage(std::string name)
	{
		return mTextureManager->GetImage(name);
	}

	void TDEGraphics::DrawImage(TDEImage* im, float x, float y)
	{		
		DrawImage(im, RoundFloat(x*mWidth), RoundFloat(y*mHeight)); 
	}

	void TDEGraphics::DrawImage(TDEImage* im, int x, int y)
	{
		Rect destRect, srcRect;
		destRect.x = x;
		destRect.y = y;
		destRect.height = im->GetHeight();
		destRect.width = im->GetWidth();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.height = im->GetHeight();
		srcRect.width = im->GetWidth();

		DrawImage(im, destRect, srcRect);
	}

	void TDEGraphics::DrawImage(TDEImage* im, Rect destRect)
	{
		Rect srcRect;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.height = im->GetHeight();
		srcRect.width = im->GetWidth();

		DrawImage(im, destRect, srcRect);
	}

	void TDEGraphics::DrawImage(TDEImage* im, Rect srcRect, float x, float y)
	{
		Rect destRect;
		destRect.x = RoundFloat(x*mWidth);
		destRect.y = RoundFloat(y*mHeight);
		destRect.height = im->GetHeight();
		destRect.width = im->GetWidth();

		DrawImage(im, destRect, srcRect);
	}

	void TDEGraphics::DrawImage(TDEImage* im, Rect destRect, Rect srcRect)
	{
		TDEColor tmpColor;
		if(!mWantColorize)
		{
			tmpColor = GetColor();
			SetColor(255,255,255);
		}
		Texture* aTex = GetTexture(im->GetTexRef());

		float texWidth = aTex->GetWidth();
		float texHeight = aTex->GetHeight();

		float aX = (float)(im->GetAtlasX() + srcRect.x);
		float aY = (float)(im->GetAtlasY() + srcRect.y);
		float aWidth = (float)srcRect.width;
		float aHeight = (float)srcRect.height;

		float aClipDiffX = mClipRect.x > aX ? mClipRect.x - aX : 0;
		float aClipDiffY = mClipRect.y > aY ? mClipRect.y - aY : 0;

		float yOffset = texHeight - (aY + aHeight);
		float aX2 = (aX + aWidth)/texWidth;
		float aY2 = (aY + aHeight - 1.f)/texHeight;

		aX = aX/texWidth;
		aY = (aY)/texHeight;

		float drawWidth = (float)destRect.width;
		float drawHeight = (float)destRect.height;

		glPushMatrix();

		glTranslatef((float)destRect.x + mTransX, (float)destRect.y + mTransY, 0.f);
		GLint activeTex;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &activeTex);
		if(mCurrentTexture != aTex)
		{
			mCurrentTexture = aTex;
			glBindTexture(GL_TEXTURE_2D, aTex->GetTex());
		}
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &activeTex);
				
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glBegin(GL_QUADS);

			glTexCoord2f(aX, 1.f -aY2);				glVertex3f(0.f, drawHeight, 0.f);
			glTexCoord2f(aX2, 1.f - aY2);			glVertex3f(drawWidth, drawHeight, 0.f);
			glTexCoord2f(aX2, 1.f - aY);			glVertex3f(drawWidth, 0.f, 0.f);
			glTexCoord2f(aX, 1.f - aY);				glVertex3f(0.f, 0.f, 0.f);

		glEnd();

		glPopMatrix();

		if(!mWantColorize)
		{
			SetColor(tmpColor);
		}
		return;
	}

	void TDEGraphics::DrawRotatedImage(TDEImage* im, float x, float y, float angle)
	{
		ApplyRotation(angle, x + im->GetWidth()/2, y + im->GetHeight()/2);
		DrawImage(im, RoundFloat(x), RoundFloat(y));
		ApplyRotation(-angle, x + im->GetWidth()/2, y + im->GetHeight()/2);
	}

	void TDEGraphics::DrawRotatedImage(TDEImage* im, Rect destRect, Rect srcRect, float angle)
	{
		ApplyRotation(angle, (float)(destRect.x + destRect.width/2), (float)(destRect.y + destRect.height/2));
		DrawImage(im, destRect, srcRect);
		ApplyRotation(-angle, (float)(destRect.x + destRect.width/2), (float)(destRect.y + destRect.height/2));
	}

	void TDEGraphics::DrawAnimation(TDE_Animation* anim, float x, float y)
	{
		if(!(anim->GetCell(0)))
			return;

		DrawImage(anim->GetCurrentCell(), x, y);
	}
	
	void TDEGraphics::DrawAnimation(TDE_Animation* anim, int x, int y)
	{
		if(!(anim->GetCell(0)))
			return;

		DrawImage(anim->GetCurrentCell(), x, y);
	}
	
	void TDEGraphics::DrawAnimation(TDE_Animation* anim, Rect destRect, Rect srcRect)
	{
		if(!(anim->GetCell(0)) || anim->GetName().empty())
			return;

		DrawImage(anim->GetCurrentCell(), destRect, srcRect);
	}
	
	void TDEGraphics::DrawAnimation(TDE_Animation* anim, Rect destRect)
	{
		if(!(anim->GetCell(0)))
			return;

		DrawImage(anim->GetCurrentCell(), destRect);
	}
	
	void TDEGraphics::DrawAnimation(TDE_Animation* anim, Rect srcRect, float x, float y)
	{
		if(!(anim->GetCell(0)))
			return;

		DrawImage(anim->GetCurrentCell(), srcRect, x, y);
	}

	void TDEGraphics::DrawRotatedAnim(TDE_Animation* anim, float x, float y, float angle)
	{
		if(!(anim->GetCell(0)))
			return;

		DrawRotatedImage(anim->GetCurrentCell(), x, y, angle);
	}
	
	void TDEGraphics::DrawRotatedAnim(TDE_Animation* anim, Rect destRect, Rect srcRect, float angle)
	{
		if(!(anim->GetCell(0)))
			return;

		DrawRotatedImage(anim->GetCurrentCell(), destRect, srcRect, angle);
	}

	TDE_Animation TDEGraphics::GetAnim(std::string name)
	{
		TDE_Animation anim = mAnimMgr->GetAnim(name);
		return anim;
	}

	void TDEGraphics::DrawRect(float x, float y, float width, float height)
	{
		DrawLine(x,y,x+width,y);
		DrawLine(x+width,y,x+width,y+height);
		DrawLine(x+width, y+height, x, y+height);
		DrawLine(x,y,x,y+height);
	}

	void TDEGraphics::DrawRect(int x, int y, int width, int height)
	{
		DrawLine(x,y,x+width,y);
		DrawLine(x+width,y,x+width,y+height);
		DrawLine(x+width, y+height, x, y+height);
		DrawLine(x,y,x,y+height);
	}

	void TDEGraphics::DrawRect(Rect drawRect)
	{
		DrawRect(drawRect.x, drawRect.y, drawRect.width, drawRect.height);
	}

	void TDEGraphics::DrawRect(Rect drawRect, float angle)
	{
		ApplyRotation(angle, (float)(drawRect.x + drawRect.width/2), (float)(drawRect.y + drawRect.height/2));
		DrawRect(drawRect);
		ApplyRotation(-angle, (float)(drawRect.x + drawRect.width/2), (float)(drawRect.y + drawRect.height/2));
	}

	void TDEGraphics::FillRect(float x1, float y1, float x2, float y2)
	{
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glVertex3f(x1 + mTransX, y1 + mTransY, 0.f);
			glVertex3f(x2 + mTransX, y1 + mTransY, 0.f);
			glVertex3f(x2 + mTransX, y2 + mTransY, 0.f);
			glVertex3f(x1 + mTransX, y2 + mTransY, 0.f);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	void TDEGraphics::FillRect(int x1, int y1, int width, int height)
	{
		FillRect((float)x1, (float)y1, (float)(x1+width), (float)(y1+height));
	}

	void TDEGraphics::FillRect(Rect drawRect)
	{
		FillRect(drawRect.x, drawRect.y, drawRect.width, drawRect.height);
	}

	void TDEGraphics::FillRect(Rect drawRect, float angle)
	{
		ApplyRotation(angle, (float)(drawRect.x + drawRect.width/2), (float)(drawRect.y + drawRect.height/2));
		FillRect(drawRect);
		ApplyRotation(-angle, (float)(drawRect.x + drawRect.width/2), (float)(drawRect.y + drawRect.height/2));
	}

	void TDEGraphics::DrawLine(float x1, float y1, float x2, float y2)
	{
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
			glVertex3f(x1 + mTransX, y1 + mTransY, 0);
			glVertex3f(x2 + mTransX, y2 + mTransY, 0);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	void TDEGraphics::DrawLine(int x1, int y1, int x2, int y2)
	{
		DrawLine((float)x1, (float)y1, (float)x2, (float)y2);
	}

	void TDEGraphics::DrawLine(float x1, float y1, float x2, float y2, TDEColor color)
	{
		glColor4f(color.m_fRed, color.m_fGreen, color.m_fBlue, color.m_fAlpha);
		DrawLine(x1, y1, x2, y2);
		ActivateColor();
	}

	void TDEGraphics::DrawShape(int verts[][2], int numPoints)
	{
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLE_STRIP);
		for(int i = 0; i < numPoints; i++)
		{
			glVertex3f(verts[i][0] + mTransX, verts[i][1] + mTransY, 0.f);
		}			
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	void TDEGraphics::DrawShape(float verts[][2], int numPoints, TDEColor color)
	{
		glColor4f(color.m_fRed,
			color.m_fGreen,
			color.m_fBlue,
			color.m_fAlpha);

		glDisable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLE_STRIP);
		for(int i = 0; i < numPoints; i++)
		{
			glVertex3f(verts[i][0] + mTransX, verts[i][1] + mTransY, 0.f);
		}			
		glEnd();
		glEnable(GL_TEXTURE_2D);

		glColor4f(mColor.m_fRed,
			mColor.m_fGreen,
			mColor.m_fBlue,
			mColor.m_fAlpha);
	}

	void TDEGraphics::LoadFont(string name)
	{
		mFont = mFontManager->GetFont(name);
	}

	TDE_Font* TDEGraphics::GetFont()
	{
		return mFont;
	}

	bool TDEGraphics::LoadTTF(string name, string path)
	{
		return mFontManager->LoadFont(name, path, 16);
	}

	int TDEGraphics::GetFontHeight()
	{
		return mFont->GetHeight();
	}

	int TDEGraphics::GetStringWidth(string s)
	{
		int h, w;
		TTF_SizeText(mFont->GetTTFFont(), s.c_str(), &w, &h);
		return w;
	}

	//String drawing functions
	void TDEGraphics::DrawString(string str, int x, int y, TDEColor color, TDE_Font* font)
	{
		if(str.size() < 1)
			return;

		SDL_Surface *init;
		int w, h;
		GLuint texture;

		if(!font->validateFont())
			return;

		init = TTF_RenderText_Blended(font->GetTTFFont(), str.c_str(), color.GetSDLColor());
		w = init->w;
		h = init->h;
		glDisable(GL_ALPHA_TEST); //Fix for bug caused by fixing dithering, was causing text to have weird skeletal look
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, init->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); 
				glVertex2f(x + mTransX, y + mTransY);
			glTexCoord2f(1.0f, 0.0f); 
				glVertex2f(x + w + mTransX, y + mTransY);
			glTexCoord2f(1.0f, 1.0f); 
				glVertex2f(x + w + mTransX, y + h + mTransY);
			glTexCoord2f(0.0f, 1.0f); 
				glVertex2f(x + mTransX, y+h + mTransY);
		glEnd();

		glFinish();
		glEnable(GL_ALPHA_TEST);
		SDL_FreeSurface(init);
		glDeleteTextures(1, &texture);
	}

	void TDEGraphics::DrawString(std::string str, int x, int y, TDE_Font* font)
	{
		DrawString(str, x, y, mColor, font);
	}

	void TDEGraphics::DrawString(std::string str, int x, int y, TDEColor color)
	{
		DrawString(str, x, y, color, mFont);
	}

	void TDEGraphics::DrawString(std::string str, int x, int y)
	{
		DrawString(str, x, y, mColor, mFont);
	}

	void TDEGraphics::DrawString(std::string str, float x, float y)
	{
		DrawString(str, (int) (x*mWidth), (int) (y*mHeight), mColor, mFont);
	}

	void TDEGraphics::SetColor(TDEColor col)
	{
		mColor = col;
		ActivateColor();
	}

	void TDEGraphics::SetColor(float fRed, float fGreen, float fBlue, float fAlpha)
	{
		mColor = TDEColor(fRed, fGreen, fBlue, fAlpha);
		ActivateColor();
	}

	void TDEGraphics::SetColor(int iRed, int iGreen, int iBlue, int iAlpha)
	{
		mColor = TDEColor(iRed, iGreen, iBlue, iAlpha);
		ActivateColor();
	}

	TDEColor TDEGraphics::GetColor()
	{
		return mColor;
	}

	void TDEGraphics::ClearColor()
	{
		SetColor(255,255,255);
	}

	void TDEGraphics::ActivateColor()
	{
		glColor4f(mColor.m_fRed,
			mColor.m_fGreen,
			mColor.m_fBlue,
			mColor.m_fAlpha);
	}

	void TDEGraphics::EnableClipping(bool enable)
	{
		if(enable)
			glEnable(GL_SCISSOR_TEST);
		else glDisable(GL_SCISSOR_TEST);
	}

	void TDEGraphics::SetClipRect(Rect clip)
	{
		mClipRect = clip;
		ActivateClipRect();
	}

	void TDEGraphics::SetClipRect(float x, float y, float width, float height)
	{
		Rect aRect((int)(x*mWidth), (int)(y*mHeight), (int)(width*mWidth), (int)(height*mHeight));
		mClipRect = aRect;
		ActivateClipRect();
	}

	void TDEGraphics::SetClipRect(int x, int y, int width, int height)
	{
		Rect aRect(x, y, width, height);
		mClipRect = aRect;
		ActivateClipRect();
	}

	Rect TDEGraphics::GetClipRect()
	{
		return mClipRect;
	}

	void TDEGraphics::SetScale(float scale)
	{
		if(scale > 0)
		{
			mScale = scale;
		}
	}

	float TDEGraphics::GetScale()
	{
		return mScale;
	}

	void TDEGraphics::ActivateClipRect()
	{
		//Causing problems with clipping quickly. Attempting to manually deal with the clip rectangle when drawing
		
		//glScissor cuts from bottom point and then widht and height, so reform the rectangle to match this
		GLsizei clipX = mClipRect.x;
		GLsizei clipY = (GLsizei) ( mHeight - (mClipRect.y + mClipRect.height));
		GLint clipw = mClipRect.width;
		GLint cliph = mClipRect.height;

		glScissor(clipX,
			clipY,
			clipw,
			cliph);
	}

	/*
		Pushes the current state onto the stack
	*/
	void TDEGraphics::PushState()
	{
		mCurrentState.mClipRect = mClipRect;
		mCurrentState.mColor = mColor;
		mCurrentState.mScale = mScale;
		mCurrentState.mFont = mFont;
		mCurrentState.mTransPoint = Pointf(mTransX, mTransY);
		mStates.push(mCurrentState);
		mCurrentState.EmptyState();

		ClearColor();
	}

	/*
		Sets the current Graphics state to the top of the stack whihc is popped off
	*/
	void TDEGraphics::PopState()
	{
		mCurrentState = mStates.top();
		mStates.pop();

		mClipRect = mCurrentState.mClipRect;
		mColor = mCurrentState.mColor;
		mScale = mCurrentState.mScale;
		mFont = mCurrentState.mFont;
		mTransX = mCurrentState.mTransPoint.x;
		mTransY = mCurrentState.mTransPoint.y;
	}

	/*
		Uses Texture Manager to Load the image from file
	*/
	bool TDEGraphics::LoadTDEImage(std::string path, std::string name)
	{
		return mTextureManager->LoadImage(path.c_str(), name.c_str());
	}

	/*
		Uses Texture Manager to load the atlases from the XML given in path
	*/
	bool TDEGraphics::LoadAtlasFromXML(std::string filePath, TDEColor ColorKey)
	{
		return mTextureManager->LoadAtlasesFromXML(filePath.c_str(), ColorKey);
	}

	//TODO - IS there even a use for this?
	bool TDEGraphics::DropAtlas(std::string fileName)
	{
		return true;
	}

	bool TDEGraphics::LoadAnim(std::string path, 
			std::string name,
			int cellWidth, 
			int cellHeight, 
			int numCells)
	{
		return mAnimMgr->LoadAnimation(name, path, cellWidth, cellHeight, numCells);
	}

	bool TDEGraphics::LoadAnim(std::string path, 
			std::string name, 
			int cellWidth, 
			int cellHeight,
			int totalWidth,
			int totalHeight,
			int numCells)
	{
		return mAnimMgr->LoadAnimation(name, path, cellWidth, cellHeight, totalWidth, totalHeight, numCells);
	}

	bool TDEGraphics::LoadAnimFromImage(std::string name, 
		TDEImage* im,
		int cellWidth,
		int cellHeight,
		int numCells)
	{
		return mAnimMgr->LoadAnimation(name, im, cellWidth, cellHeight, numCells);
	}

	bool TDEGraphics::CreateAnim(std::string name,
		TDEImage* cells[],
		int numCells)
	{
		return mAnimMgr->LoadAnimation(name, cells, numCells);
	}

	Texture* TDEGraphics::GetTexture(std::string texName)
	{
		return mTextureManager->GetTexture(texName);
	}

	void TDEGraphics::ApplyRotation(float angle, float pointX, float pointY)
	{
		glTranslatef(pointX, pointY, 0.f);
		glRotatef(angle, 0.f, 0.f, 1.f);
		glTranslatef(-pointX, -pointY, 0.f);
	}

	void TDEGraphics::ColorizeImages(bool cIm)
	{
		mWantColorize = cIm;
	}

	int TDEGraphics::RoundFloat(float f)
	{
		return (int)(f + 0.5);
	}

	int TDEGraphics::getNextPow2(int x)
	{
		float logbase2 = (float) (log(x) / log(2));
		return RoundFloat((float) pow(2,ceil(logbase2)));
	}

	TextureManager* TDEGraphics::GetTexMgr()
	{
		return mTextureManager;
	}

	AnimationManager* TDEGraphics::GetAnimMgr()
	{
		return mAnimMgr;
	}
}
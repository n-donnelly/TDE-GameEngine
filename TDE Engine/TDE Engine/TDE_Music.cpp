#include "TDE_Music.h"

namespace TDE
{
	TDE_Music::TDE_Music(std::string name)
	{
		mName = name;
		mPath = "";
		mCurrentVolume = 0;
		mMusic = NULL;
		mLoaded = false;
		mPlaying = false;
	}

	TDE_Music::TDE_Music(std::string name, std::string path)
	{
		mName = name;
		mPath = path;
		mCurrentVolume = 0;
		mMusic = Mix_LoadMUS(path.c_str());

		if(!mMusic)
			printf("Mix_LoadMUS(\"%s\"): %s\n", path, Mix_GetError());
		else 
		{
			mLoaded = true;
			mCurrentVolume = Mix_VolumeMusic(-1);
		}
		mPlaying = false;
	}


	TDE_Music::~TDE_Music(void)
	{
	}

	void TDE_Music::Play(int repeats)
	{
		if(Mix_PlayMusic(mMusic, repeats) == -1)
		{
			printf("Music File: %s failed to play. %s", mName, Mix_GetError());
		}
		mPlaying = true;
	}

	void TDE_Music::Pause()
	{
		Mix_PauseMusic();
		mPlaying = false;
	}

	void TDE_Music::Resume()
	{
		Mix_ResumeMusic();
		mPlaying = true;
	}

	void TDE_Music::Stop()
	{
		Mix_HaltMusic();
		mPlaying = false;
	}

	void TDE_Music::SetVolume(int newVolume)
	{
		Mix_VolumeMusic(newVolume);
		mCurrentVolume = newVolume;
	}

	int TDE_Music::GetVolume()
	{
		return mCurrentVolume;
	}

	void TDE_Music::IncVolume()
	{
		mCurrentVolume++;
		Mix_VolumeMusic(mCurrentVolume);
	}

	void TDE_Music::DecVolume()
	{
		Mix_VolumeMusic(--mCurrentVolume);
	}

	void TDE_Music::FadeIn(int repeats, int fadeTime)
	{
		if(Mix_FadeInMusic(mMusic, repeats, fadeTime)==-1)
			printf("Music File: %s failed to play", mName, Mix_GetError());
		else mPlaying = true;
	}

	void TDE_Music::FadeOut(int fadeTime)
	{
		while(!Mix_FadeOutMusic(fadeTime) && Mix_PlayingMusic())
		{
			SDL_Delay(100);
		}
		mPlaying = false;
	}

	bool TDE_Music::IsPlaying()
	{
		return Mix_PlayingMusic() && mPlaying ? true : false;
	}

	bool TDE_Music::IsPaused()
	{
		return Mix_PausedMusic() > 0 ? true : false;
	}

	void TDE_Music::Delete()
	{
		if(mMusic)
		{
			Mix_FreeMusic(mMusic);
			mMusic = false;
		}

		mLoaded = false;
	}

	bool TDE_Music::Load(std::string path)
	{
		if(mMusic)
			Delete();
		mPath = path;
		mMusic = Mix_LoadMUS(path.c_str());

		if(!mMusic)
		{
			printf("Mix_LoadMUS(\"%s\"): %s\n", path, Mix_GetError());
			return false;
		}
		else {
			mLoaded = false;
			return false;
		}
	}

	void TDE_Music::SetLoaded(bool l)
	{
		mLoaded = l;
	}

	bool TDE_Music::IsLoaded()
	{
		return mLoaded;
	}

	bool TDE_Music::ValidateMusic()
	{
		return mMusic == NULL ? false : true;
	}
}
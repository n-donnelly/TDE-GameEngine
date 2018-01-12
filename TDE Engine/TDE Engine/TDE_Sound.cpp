#include "TDE_Sound.h"

namespace TDE
{
	TDE_Sound::TDE_Sound(std::string name)
	{
		mName = name;
		mPath = "";
		mCurrentVolume = 0;
		mSound = NULL;
		mLoaded = false;
		mChannel = -1;
		mPlaying = false;
	}

	TDE_Sound::TDE_Sound(std::string name, std::string path)
	{
		mName = name;
		mPath = path;
		mChannel = -1;
		mSound = Mix_LoadWAV(path.c_str());
		if(!mSound)
		{
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
		}
		else
		{
			mCurrentVolume = Mix_VolumeChunk(mSound, -1);
			mLoaded = true;
		}
		mPlaying = false;
	}


	TDE_Sound::~TDE_Sound(void)
	{
	}

	void TDE_Sound::Play(int repeats)
	{
		mChannel = Mix_PlayChannel(-1, mSound, repeats);
		if(mChannel == -1)
		{
			printf("Sound %s failed to play. %s", mName, Mix_GetError());
		}
		mPlaying = true;
	}

	bool TDE_Sound::Play(int channel, int repeats)
	{
		mChannel = Mix_PlayChannel(channel, mSound, repeats);
		if(mChannel == -1)
		{
			printf("Sound %s failed to play on channel %d. %s", mName, channel, Mix_GetError());
			return false;
		}
		mPlaying = true;
		return true;
	}

	void TDE_Sound::Pause()
	{
		if(mChannel >= 0)
		{
			mPlaying = false;
			Mix_Pause(mChannel);
		}
	}

	void TDE_Sound::Resume()
	{
		if(mChannel >= 0)
		{
			mPlaying = true;
			Mix_Resume(mChannel);
		}
	}

	void TDE_Sound::Stop()
	{
		if(mChannel >= 0)
		{
			mPlaying = false;
			Mix_HaltChannel(mChannel);
			mChannel = -1;
		}
	}

	void TDE_Sound::SetVolume(int v)
	{
		mCurrentVolume = v;
		Mix_VolumeChunk(mSound, v); //Sets value on chunk
		Mix_Volume(mChannel, v); //In case already on channel, set channel volume as well
	}

	int TDE_Sound::GetVolume()
	{
		return mCurrentVolume;
	}

	void TDE_Sound::IncVolume()
	{
		SetVolume(++mCurrentVolume);
	}

	void TDE_Sound::DecVolume()
	{
		SetVolume(--mCurrentVolume);
	}

	bool TDE_Sound::IsPlaying()
	{
		if(mChannel >= 0)
			return (Mix_Playing(mChannel) > 0 && mPlaying) ? true : false;
		else return false;
	}

	bool TDE_Sound::IsPaused()
	{
		if(mChannel >= 0)
			return Mix_Paused(mChannel) > 0 && (!mPlaying) ? true : false;
		else return false;
	}

	bool TDE_Sound::IsLoaded()
	{
		return mLoaded;
	}

	bool TDE_Sound::Load(std::string path)
	{
		mPath = path;
		mChannel = -1;
		mSound = Mix_LoadWAV(path.c_str());
		if(!mSound)
		{
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
			return false;
		}
		else
		{
			mCurrentVolume = Mix_VolumeChunk(mSound, -1);
			mLoaded = true;
			return true;
		}
	}

	void TDE_Sound::Delete()
	{
		Mix_FreeChunk(mSound);
		mSound = NULL;
		mLoaded = false;
		mChannel = -1;
	}

	bool TDE_Sound::ValidateSound()
	{
		return mSound == NULL ? false : true;
	}

	void TDE_Sound::SetWaiting(bool w)
	{
		mWaitingOnChannel = w;
	}

	bool TDE_Sound::IsWaiting()
	{
		return mWaitingOnChannel;
	}

	void TDE_Sound::HasStopped()
	{
		mWaitingOnChannel = false;
		mChannel = -1;
	}
}
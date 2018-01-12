#include "AudioManager.h"

using namespace std;

namespace TDE
{
	AudioManager::AudioManager(void)
	{
		mNumChannels = 0;
		mAvailableChannels = 0;
		mNumWaiting = 0;
		mMusic = NULL;
		mChannels.fill(NULL);
		mChannelVolume = 64;
		mMusVolume = 128;
	}


	AudioManager::~AudioManager(void)
	{
	}

	bool AudioManager::Init()
	{
		if(SDL_Init(SDL_INIT_AUDIO) == -1)
		{
			printf("SDL_Init: %s\n", SDL_GetError());
			return false;
		}

		if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
		{
			printf("Mix_OpenAudio: %s\n", Mix_GetError());
			return false;
		}

		mNumChannels = mAvailableChannels = Mix_AllocateChannels(NUM_CHANNELS);

		ChannelHandler::SetCallback(this);
		Mix_Volume(-1, mChannelVolume);
		return true;
	}

	void AudioManager::CleanUp()
	{
		for(map<string, TDE_Sound>::iterator it = mSoundMap.begin(); it != mSoundMap.end(); it++)
		{
			it->second.Delete();
		}

		for(map<string, TDE_Music>::iterator it = mMusicMap.begin(); it != mMusicMap.end(); it++)
		{
			Mix_FreeMusic(it->second.mMusic);
		}

		mMusic = NULL;
		Mix_CloseAudio();
		Mix_Quit();
	}

	void AudioManager::Update()
	{
		while(mDoneChannels.size() > 0)
		{
			ChannelDone(mDoneChannels.back());
			mDoneChannels.pop_back();
		}
	}

	bool AudioManager::LoadSoundFile(string name, string path)
	{
		TDE_Sound s(name, path);
		if(s.ValidateSound())
		{
			mSoundMap.insert(pair<string, TDE_Sound>(name, s));
			return true;
		}
		else return false;
	}

	bool AudioManager::LoadMusicFile(string name, string path)
	{
		TDE_Music m(name, path);
		if(m.ValidateMusic())
		{
			mMusicMap.insert(pair<string, TDE_Music>(name, m));
			return true;
		}
		else return false;
	}

	TDE_Music* AudioManager::GetCurrentMusic()
	{
		return mMusic;
	}

	TDE_Music* AudioManager::GetMusic(string name)
	{
		map<string, TDE_Music>::iterator it = mMusicMap.find(name);
		if(it == mMusicMap.end())
			return NULL;
		else return &(it->second);
	}

	bool AudioManager::PlayMusic(string name, int repeats)
	{
		map<string, TDE_Music>::iterator it = mMusicMap.find(name);
		if(it == mMusicMap.end())
			return NULL;
		else
		{
			it->second.Play(repeats);
			mMusic = &(it->second);
			return true;
		}
	}

	bool AudioManager::PlayMusic(TDE_Music* m, int repeats)
	{
		if(!(m->ValidateMusic()))
			return false;

		mMusic = m;
		m->Play(repeats);
		return true;
	}

	bool AudioManager::FadeInMusic(string name, int repeats, int fadeTime)
	{
		map<string, TDE_Music>::iterator it = mMusicMap.find(name);
		if(it == mMusicMap.end())
			return false;
		else
		{
			it->second.FadeIn(repeats, fadeTime);
			mMusic = &(it->second);
			return true;
		}
	}

	bool AudioManager::FadeInMusic(TDE_Music* m, int repeats, int fadeTime)
	{
		if(!(m->ValidateMusic()))
			return false;
		mMusic = m;
		m->FadeIn(repeats, fadeTime);
		return true;
	}

	void AudioManager::FadeOutMusic(int fadeTime)
	{
		if(mMusic)
			mMusic->FadeOut(fadeTime);
	}

	void AudioManager::PauseMusic()
	{
		if(mMusic)
			mMusic->Pause();
	}

	void AudioManager::ResumeMusic()
	{
		if(mMusic)
			mMusic->Resume();
	}

	void AudioManager::StopMusic()
	{
		if(mMusic)
			mMusic->Stop();
	}

	void AudioManager::SetMusicVolume(int vol)
	{
		Mix_VolumeMusic(vol);
		mMusVolume = Mix_VolumeMusic(-1);
	}

	void AudioManager::IncremenetMusicVolume()
	{
		SetMusicVolume(mMusVolume+1);
	}

	void AudioManager::DecrementMusicVolume()
	{
		SetMusicVolume(mMusVolume-1);
	}

	TDE_Sound* AudioManager::GetSound(string name)
	{
		map<string, TDE_Sound>::iterator it = mSoundMap.find(name);
		if(it == mSoundMap.end())
			return NULL;
		else return &(it->second);
	}

	bool AudioManager::PlaySound(std::string name, int repeats)
	{
		TDE_Sound* s = GetSound(name);
		if(!s)
			return false;
		else return PlaySound(s, repeats);
	}

	bool AudioManager::PlaySound(TDE_Sound* s, int repeats)
	{
		if(!(s->ValidateSound()))
			return false;

		int channel = FindChannel();
		if(channel < 0)
		{
			s->SetWaiting(true);
			if(mNumWaiting <= 32)
			{
				mWaitingSounds.push(pair<TDE_Sound*, int>(s, repeats));
				mNumWaiting++;
			}
			else return false;
		}
		else
		{
			s->Play(channel, repeats);
			mChannels[channel] = s;
		}
		return true;
	}

	void AudioManager::ResumeSound(TDE_Sound* s)
	{
		if(s->IsPaused())
			s->Resume();
	}

	void AudioManager::ResumeSound(std::string name)
	{
		TDE_Sound* s = GetSound(name);
		if(s) ResumeSound(s);
	}

	void AudioManager::PauseSound(TDE_Sound* s)
	{
		if(s->IsPlaying())
			s->Pause();
	}

	void AudioManager::PauseSound(std::string name)
	{
		TDE_Sound* s = GetSound(name);
		if(s) PauseSound(s);
	}

	void AudioManager::StopSound(TDE_Sound* s)
	{
		s->Stop();
	}

	void AudioManager::StopSound(std::string name)
	{
		TDE_Sound* s = GetSound(name);
		if(s) StopSound(s);
	}

	void AudioManager::FreeSound(std::string name)
	{
		TDE_Sound* s = GetSound(name);
		if(s) s->Delete();
	}

	void AudioManager::PauseAllSounds()
	{
		Mix_Pause(-1);
	}

	void AudioManager::ResumeAllSounds()
	{
		Mix_Resume(-1);
	}

	void AudioManager::StopAllSounds()
	{
		Mix_HaltChannel(-1);
		mChannels.fill(NULL);
	}

	void AudioManager::FreeAllSounds()
	{
		for(map<string, TDE_Sound>::iterator it = mSoundMap.begin(); it != mSoundMap.end(); it++)
		{
			it->second.Delete();
		}
		mChannels.fill(NULL);
	}

	void AudioManager::SetVolumeForSounds(int v)
	{
		Mix_Volume(-1, v);
		mChannelVolume = Mix_Volume(-1,-1);
	}

	void AudioManager::IncrementSoundVolume()
	{
		mChannelVolume = mChannelVolume == 128 ? 128 : mChannelVolume+1;
		Mix_Volume(-1, mChannelVolume);
	}

	void AudioManager::DecrementSoundVolume()
	{
		mChannelVolume = mChannelVolume == 0 ? 0 : mChannelVolume-1;
		Mix_Volume(-1, mChannelVolume);
	}

	void AudioManager::ClearWaitingSounds()
	{
		while(!(mWaitingSounds.empty()))
			mWaitingSounds.pop();
	}

	int AudioManager::FindChannel()
	{
		for(int i = 0; i < NUM_CHANNELS; i++)
		{
			if(!(mChannels[i]))
				return i;
		}
		return -1;
	}

	void AudioManager::ChannelDone(int channel)
	{
		if(mNumWaiting == 0)
		{
			if(mChannels[channel])
				mChannels[channel]->Stop();
			mChannels[channel] = NULL;
		}
		else
		{
			pair<TDE_Sound*, int> p = mWaitingSounds.front();
			TDE_Sound* s = p.first;
			int repeats = p.second;
			mChannels[channel] = s;
			s->Play(channel, repeats);
			mWaitingSounds.pop();
			mNumWaiting--;
		}
	}

	void AudioManager::FinishedChannel(int channel)
	{
		mDoneChannels.push_back(channel);
	}
	
	AudioManager* ChannelHandler::AudioMgr;

	void ChannelHandler::SetCallback(AudioManager *am)
	{		
		AudioMgr = am;
		Mix_ChannelFinished(DoneChannel);
	}

	void ChannelHandler::DoneChannel(int channel)
	{
		AudioMgr->FinishedChannel(channel);
	}
}
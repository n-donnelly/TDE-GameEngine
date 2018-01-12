#ifndef AUDIO_MGR
#define AUDIO_MGR

#define NUM_CHANNELS 64

#include "TDE_Music.h"
#include "TDE_Sound.h"
#include <map>
#include <vector>
#include <queue>
#include <array>

namespace TDE
{
	class AudioManager
	{
	public:
		AudioManager(void);
		~AudioManager(void);

		bool Init();
		void CleanUp();
		void Update();

		bool LoadSoundFile(std::string name, std::string path);
		bool LoadMusicFile(std::string name, std::string path);
		TDE_Music* GetCurrentMusic();
		TDE_Music* GetMusic(std::string name);

		bool PlayMusic(std::string name, int repeats);
		bool PlayMusic(TDE_Music* m, int repeats);
		bool FadeInMusic(std::string name, int repeats, int fadeTime);
		bool FadeInMusic(TDE_Music* m, int repeats, int fadeTime);
		void FadeOutMusic(int fadeTime);

		void PauseMusic();
		void ResumeMusic();
		void StopMusic();

		void SetMusicVolume(int vol);
		void IncremenetMusicVolume();
		void DecrementMusicVolume();

		TDE_Sound* GetSound(std::string name);
		bool PlaySound(std::string name, int repeats);
		bool PlaySound(TDE_Sound* s, int repeats);

		void PauseSound(TDE_Sound* s);
		void PauseSound(std::string name);

		void ResumeSound(TDE_Sound* s);
		void ResumeSound(std::string name);

		void StopSound(TDE_Sound* s);
		void StopSound(std::string name);

		void FreeSound(std::string name);

		void ResumeAllSounds();
		void PauseAllSounds();
		void StopAllSounds();
		void FreeAllSounds();

		void SetVolumeForSounds(int v);
		void IncrementSoundVolume();
		void DecrementSoundVolume();

		void ClearWaitingSounds();

		void ChannelDone(int channel);
		void FinishedChannel(int channel);

		int GetNumChannels() {return mNumChannels;};
		int GetNumFreeChannels() {return mAvailableChannels;};
		int GetNumWaiting() {return mNumWaiting;};
		int GetVolume() {return mChannelVolume;};
		int GetMusVolume() {return Mix_VolumeMusic(-1);};
		int GetChannelsWaitingRefresh() {return mDoneChannels.size();};

	private:
		int FindChannel();

		int			mNumChannels;
		int			mAvailableChannels;
		int			mNumWaiting;
		int			mChannelVolume;
		int			mMusVolume;
		TDE_Music*	mMusic;

		std::map<std::string, TDE_Sound>	mSoundMap;
		std::map<std::string, TDE_Music>	mMusicMap;

		std::array<TDE_Sound*, NUM_CHANNELS> mChannels;
		std::vector<int>	mDoneChannels;
		std::queue<std::pair<TDE_Sound*, int>> mWaitingSounds;
	};

	class ChannelHandler
	{
	public:
		static void SetCallback(AudioManager *am);
		static void DoneChannel(int c);

	private:
		static AudioManager* AudioMgr;
	};
}
#endif
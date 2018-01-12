#ifndef AUDIOFILE
#define AUDIOFILE

#include <string>
#include "SDL_mixer.h"
#include "SDL.h"

namespace TDE
{
	class AudioFile
	{
	public:
		AudioFile() {};
		~AudioFile() {};

		void Play(int repeat);
		void Pause();
		void Resume();
		void Stop();

		void SetVolume(int v);
		int GetVolume();
		void IncVolume();
		void DecVolume();

		bool IsPlaying();
		bool IsPaused();
		bool IsLoaded();

	protected:
		bool Load(std::string path);
		void Delete();

		std::string mName;
		std::string mPath;
		int			mCurrentVolume;
		bool		mLoaded;
	};
}

#endif
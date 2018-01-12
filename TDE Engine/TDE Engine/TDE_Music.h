#ifndef TDE_MUSIC_H
#define TDE_MUSIC_H

#include "AudioFile.h"

namespace TDE
{
	class TDE_Music : public virtual AudioFile
	{
	public:
		TDE_Music(std::string name);
		TDE_Music(std::string name, std::string path);
		~TDE_Music(void);

		virtual void SetVolume(int v);
		virtual int GetVolume();
		virtual void IncVolume();
		virtual void DecVolume();
		virtual bool IsPlaying();
		virtual bool IsPaused();
		virtual bool IsLoaded();

		std::string GetName() {return mName;};
		friend class AudioManager;

	protected:
		virtual void Play(int repeats);
		virtual void Pause();
		virtual void Resume();
		virtual void Stop();

		void FadeIn(int repeats, int fadeTime);
		void FadeOut(int fadeTime);

		void SetLoaded(bool l);
		virtual bool Load(std::string path);
		virtual void Delete();
		bool ValidateMusic();

	private:
		Mix_Music*	mMusic;
		bool		mPlaying;

	};
}
#endif
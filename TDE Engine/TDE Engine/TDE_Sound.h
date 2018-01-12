#ifndef TDE_SOUND
#define TDE_SOUND

#include "AudioFile.h"

namespace TDE
{
	class TDE_Sound : public virtual AudioFile
	{
	public:
		TDE_Sound(std::string name);
		TDE_Sound(std::string name, std::string path);
		~TDE_Sound(void);

		virtual void SetVolume(int v);
		virtual int GetVolume();
		virtual void IncVolume();
		virtual void DecVolume();
		virtual bool IsPlaying();
		virtual bool IsPaused();
		virtual bool IsLoaded();
		
		int GetChannel() {return mChannel;};

		friend class AudioManager;

	protected:
		virtual bool Load(std::string path);
		virtual void Delete();
		bool ValidateSound();

		virtual void Play(int repeats);
		bool Play(int channel, int repeats);
		virtual void Pause();
		virtual void Resume();
		virtual void Stop();

		void SetWaiting(bool w);
		bool IsWaiting();

		void HasStopped();

		Mix_Chunk* GetChunk();

	private:
		int			mChannel;
		bool		mWaitingOnChannel;
		Mix_Chunk*	mSound;
		bool		mPlaying;
	};
}
#endif
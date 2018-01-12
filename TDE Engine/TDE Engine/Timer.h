#ifndef TIMER_H
#define TIMER_H

#include <time.h>

namespace TDE
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void Start();
		void Pause();
		void Resume();
		void Update();
		double GetTimeElapsed();
		double GetTotalTimePaused();
		time_t GetLastTime();

	private:
		double mPauseTime;
		time_t mStartTime;
		bool mPaused;
		time_t mLastTime;
	};
}
#endif
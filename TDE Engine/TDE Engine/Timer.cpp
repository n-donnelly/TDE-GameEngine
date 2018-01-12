#include "Timer.h"

namespace TDE
{
	void Timer::Start()
	{
		mStartTime = time(NULL);
		mLastTime = mStartTime;
		mPauseTime = 0.0;
	}

	void Timer::Update()
	{
		if(!mPaused)
			mLastTime = time(NULL);
	}

	void Timer::Pause()
	{
		mPaused = true;
		mLastTime = time(NULL);
	}

	void Timer::Resume()
	{
		mPaused = false;
		time_t currentTime = time(NULL);
		mPauseTime = difftime(currentTime, mLastTime);
	}

	double Timer::GetTimeElapsed()
	{
		time_t currentTime = time(NULL);
		return difftime(currentTime, mStartTime) - mPauseTime;
	}

	double Timer::GetTotalTimePaused()
	{
		return mPauseTime;
	}

	time_t Timer::GetLastTime()
	{
		return mLastTime;
	}
}
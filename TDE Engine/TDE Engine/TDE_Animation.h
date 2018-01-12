#ifndef TDE_ANIMATION
#define TDE_ANIMATION

#include "Includes.h"
#include "TextureManager.h"

namespace TDE
{

	class TDEGraphics;

	class TDE_Animation
	{
	public:
		TDE_Animation(void);
		TDE_Animation(std::string name, TDEImage* im, Texture* tex, int cellWidth, int cellHeight, int numCells);
		TDE_Animation(std::string name, TDEImage* cells[], int numCells);
		~TDE_Animation(void);

		void Update();

		void Play(int loopTime, int startCell, int numRepeats);

		void Pause();
		void Resume();
		void Stop();
		void Reset();
		void JumpToCell(int i);
		int GetCurrentCellIndex();

		bool isPlaying();
		bool isPaused();
		bool IsFinished();

		int GetCellWidth();
		int GetCellHeight();
		int GetLoopTime();
		int GetNumCells();
		string GetName();

		void Delete();

		TDEImage* GetCurrentCell();
		TDEImage* GetCell(int i);

	private:
		bool	DecomposeImage(Texture* t, TDEImage* im, int cellWidth, int cellHeight, int numCells);
		void	PopulateVector(TDEImage* cells[], int numCells);

		std::vector<TDEImage>	mCells;
		std::string				mName;

		int						mNumCells;
		int						mCellWidth;
		int						mCellHeight;
		int						mCurrentCell;
		
		int						mLoopTime;
		int						mCellPerSec;

		bool					mPlaying;
		bool					mPaused;
		bool					mFinished;
		int						mRepeats;

		int						mLastUpdate;
		int						mPauseTime;

	};

}

#endif
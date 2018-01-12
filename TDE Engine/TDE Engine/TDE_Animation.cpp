#include "TDE_Animation.h"

namespace TDE
{

	TDE_Animation::TDE_Animation(void)
	{
		mNumCells = 0;
		mCellWidth = 0;
		mCellHeight = 0;
		mCurrentCell = -1;
		mLoopTime = 0;
		mPlaying  = false;
		mPaused = false;
		mFinished = false;
		mRepeats = 0;
		mName = "";
		mCellPerSec = 0;
		mLastUpdate = 0;
		mNumCells = 0;
		mPauseTime = 0;
	}

	TDE_Animation::TDE_Animation(std::string name, 
		TDEImage* im,
		Texture* tex,
		int cellWidth,
		int cellHeight,
		int numCells)
	{
		if(name.empty())
		{
			printf("Invalid name provided for animation\n");
			return;
		}

		if(!im || !tex || cellWidth <= 0 || cellHeight <= 0 || numCells <= 0)
		{
			mNumCells = 0;
			mCellWidth = 0;
			mCellHeight = 0;
			mCurrentCell = -1;
			mLoopTime = 0;
			mPlaying  = false;
			mPaused = false;
			mFinished = false;
			mRepeats = 0;
			mName = "";
			mCellPerSec = 0;
			mLastUpdate = 0;
			mNumCells = 0;
			mPauseTime = 0;
			return;
		}

		mName = name;
		mCellHeight = cellHeight;
		mCellWidth = cellWidth;
		mCurrentCell = 0;

		DecomposeImage(tex, im, cellWidth, cellHeight, numCells);

		mLoopTime = 0;
		mPlaying = false;
		mPaused = false;
		mFinished = false;
		mRepeats = 0;
		mCellPerSec = 0;
		mLastUpdate = 0;
		mPauseTime = 0;
	}

	TDE_Animation::TDE_Animation(std::string name,
		TDEImage* cells[],
		int numCells)
	{
		if(name.empty())
		{
			printf("Invalid name provided for animation\n");
			return;
		}

		if(cells[0])
		{
			mName = name;
			mCellHeight = cells[0]->GetHeight();
			mCellWidth = cells[0]->GetWidth();
			mCurrentCell = 0;

			PopulateVector(cells, numCells);
			mNumCells = numCells;

			mLoopTime = 0;
			mPlaying = false;
			mPaused = false;
			mFinished = false;
			mRepeats = 0;
			mCellPerSec = 0;
			mLastUpdate = 0;
			mPauseTime = 0;
		}

		mNumCells = 0;
		mCellWidth = 0;
		mCellHeight = 0;
		mCurrentCell = -1;
		mLoopTime = 0;
		mPlaying  = false;
		mPaused = false;
		mFinished = false;
		mRepeats = 0;
		mName = "";
		mCellPerSec = 0;
		mLastUpdate = 0;
		mNumCells = 0;
		mPauseTime = 0;
	}

	TDE_Animation::~TDE_Animation(void)
	{
	}

	void TDE_Animation::Update()
	{
		if(mPaused == true || mCells.size() == 0 || mLoopTime <= 0 || mFinished)
			return;

		int aTime = SDL_GetTicks();
		if((aTime - mLastUpdate - mPauseTime) > mCellPerSec)
		{
			mCurrentCell++;
			if(mCurrentCell == mNumCells)
			{
				if(mRepeats == 0)
				{
					mFinished = true;
					mPaused = true;
					mPlaying = false;
				}
				else if(mRepeats > 0)
					mRepeats--;
				mCurrentCell = 0;
			}
			mLastUpdate = aTime;
			mPauseTime = 0;
		}
	}

	void TDE_Animation::Play(int loopTime, int startCell, int numRepeats)
	{
		mLoopTime = loopTime;
		mCurrentCell = (startCell < 0 || startCell >= mNumCells) ? 0 : startCell;
		mRepeats = numRepeats;
		if(mNumCells > 0)
			mCellPerSec = mLoopTime/mNumCells;
		else mCellPerSec = 0;

		mPlaying  = true;
		mPaused = false;
		mFinished = false;
		mLastUpdate = SDL_GetTicks();
	}

	void TDE_Animation::Pause()
	{
		if(mPlaying)
		{
			mPlaying = false;
			mPaused = true;
			mPauseTime = SDL_GetTicks();
		}
	}

	void TDE_Animation::Resume()
	{
		if(mPaused)
		{
			mPlaying = true;
			mPaused = false;
			mPauseTime = SDL_GetTicks() - mPauseTime;
		}
	}

	void TDE_Animation::Stop()
	{
		mPlaying = false;
		mFinished = true;
	}

	void TDE_Animation::Reset()
	{
		mCurrentCell = 0;
		mLastUpdate = SDL_GetTicks();
	}

	bool TDE_Animation::isPlaying()
	{
		return mPlaying;
	}

	bool TDE_Animation::isPaused()
	{
		return mPaused;
	}

	bool TDE_Animation::IsFinished()
	{
		return mFinished;
	}

	int TDE_Animation::GetCellWidth()
	{
		return mCellWidth;
	}

	int TDE_Animation::GetCellHeight()
	{
		return mCellHeight;
	}

	int TDE_Animation::GetLoopTime()
	{
		return mLoopTime;
	}

	int TDE_Animation::GetNumCells()
	{
		return mNumCells;
	}

	string TDE_Animation::GetName()
	{
		return mName;
	}

	void TDE_Animation::JumpToCell(int i)
	{
		if(i < mNumCells)
			mCurrentCell = i;
	}

	int TDE_Animation::GetCurrentCellIndex()
	{
		return mCurrentCell;
	}

	void TDE_Animation::Delete()
	{
		mName = "";
		mCells.clear();
		mNumCells = 0;
		mLastUpdate = 0;
		mLoopTime = 0;
		mCellPerSec = 0;
	}

	TDEImage* TDE_Animation::GetCurrentCell()
	{
		return &(mCells[mCurrentCell]);
	}

	TDEImage* TDE_Animation::GetCell(int i)
	{
		if(i < mNumCells)
			return &(mCells[i]);
		else return NULL;
	}

	bool TDE_Animation::DecomposeImage(Texture* t, TDEImage* im, int cellWidth, int cellHeight, int numCells)
	{
		int nameIndex = 0;
		for(int i = 0; i <= im->GetHeight() - cellHeight; i += cellHeight)
		{
			for(int j = 0; j <= im->GetWidth() - cellWidth; j += cellWidth)
			{
				if(nameIndex == numCells)
				{
					mNumCells = nameIndex;
					return true;
				}

				TDEImage t(t->GetName(), 
					im->GetAtlasX() + j, 
					im->GetAtlasY() + i, 
					cellWidth,
					cellHeight, 
					im->GetName()+"_"+std::to_string(nameIndex)); 

				mCells.push_back(t);
				nameIndex++;
			}
		}

		mNumCells = nameIndex;
		return true;
	}

	void TDE_Animation::PopulateVector(TDEImage* cells[], int numCells)
	{
		for(int i = 0; i < numCells; i++)
		{
			if(cells[i])
				mCells.push_back(TDEImage(cells[i]->GetTexRef(),
					cells[i]->GetAtlasX(), 
					cells[i]->GetAtlasY(), 
					cells[i]->GetWidth(), 
					cells[i]->GetHeight(), 
					mName+"_"+std::to_string(i)));
			else return;
		}
	}
}
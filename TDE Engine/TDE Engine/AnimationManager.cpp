#include "AnimationManager.h"

using namespace std;

namespace TDE
{
	AnimationManager::AnimationManager(TextureManager* aTexMgr)
	{
		mTexMgr = aTexMgr;
		mAnimMap.clear();
		mControlVec.clear();
	}

	AnimationManager::AnimationManager(void)
	{
		mTexMgr = NULL;
	}

	AnimationManager::~AnimationManager(void)
	{
	}

	bool AnimationManager::LoadAnimation(string name, TDEImage* cells[], int numCells)
	{
		TDE_Animation anim = TDE_Animation(name, cells, numCells);
		if(anim.GetNumCells() > 0)
		{
			mAnimMap.insert(pair<string, TDE_Animation>(name, anim));
			return true;
		}
		else return false;
	}

	bool AnimationManager::LoadAnimation(string name, TDEImage* anIm, int cellWidth, int cellHeight, int numCells)
	{
		TDE_Animation anim = TDE_Animation(TDE_Animation(name, anIm, mTexMgr->GetTexture(anIm->GetTexRef()), cellWidth, cellHeight, numCells));
		if(anim.GetNumCells() > 0)
		{
			mAnimMap.insert(pair<string, TDE_Animation>(name, anim));
			return true;
		}
		else return false;
	}

	bool AnimationManager::LoadAnimation(string name, string path, int cellWidth, int cellHeight, int numCells)
	{
		if(!(mTexMgr))
			return false;

		if(!(mTexMgr->LoadImage(path.c_str(), name.c_str())))
		{
			return false;
		}

		TDEImage* anIm = mTexMgr->GetImage(name);
		if(anIm)
		{
			TDE_Animation anim = TDE_Animation(TDE_Animation(name, anIm, mTexMgr->GetTexture(anIm->GetTexRef()), cellWidth, cellHeight, numCells));
			if(anim.GetNumCells() > 0)
			{
				mAnimMap.insert(pair<string, TDE_Animation>(name, anim));
				return true;
			}
		}

		return false;
	}

	bool AnimationManager::LoadAnimation(string name, string path, int cellWidth, int cellHeight, int totalWidth, int totalHeight, int numCells)
	{
		if(!(mTexMgr))
			return false;

		if(!(mTexMgr->LoadImage(path.c_str(), name.c_str(), totalWidth, totalHeight)))
		{
			return false;
		}

		
		TDEImage* anIm = mTexMgr->GetImage(name);
		if(anIm)
		{
			TDE_Animation anim = TDE_Animation(TDE_Animation(name, anIm, mTexMgr->GetTexture(anIm->GetTexRef()), cellWidth, cellHeight, numCells));
			if(anim.GetNumCells() > 0)
			{
				mAnimMap.insert(pair<string, TDE_Animation>(name, anim));
				return true;
			}
		}
		return false;
	}

	TDE_Animation AnimationManager::GetAnim(string name)
	{
		map<string, TDE_Animation>::iterator it = mAnimMap.find(name);
		if(it == mAnimMap.end())
			return TDE_Animation();
		else return (it->second);
	}

	bool AnimationManager::RegisterAnim(TDE_Animation* anim)
	{
		if(anim)
		{
			mControlVec.push_back(anim);
			return true;
		}
		return false;
	}

	bool AnimationManager::DeregisterAnim(TDE_Animation* anim)
	{
		vector<TDE_Animation*>::iterator it;
		for(it = mControlVec.begin(); it != mControlVec.end(); it++)
		{
			if((*it) == anim)
			{
				mControlVec.erase(it);
				return true;
			}

		}
		return false;
	}

	void AnimationManager::UpdateAll()
	{
		for(int i = 0; i < mControlVec.size(); i++)
		{
			mControlVec[i]->Update();
		}
	}

	void AnimationManager::PauseAll()
	{
		for(int i = 0; i < mControlVec.size(); i++)
		{
			mControlVec[i]->Pause();
		}
	}

	void AnimationManager::ResumeAll()
	{
		for(int i = 0; i < mControlVec.size(); i++)
		{
			mControlVec[i]->Resume();
		}
	}

	void AnimationManager::StopAll()
	{
		for(int i = 0; i < mControlVec.size(); i++)
		{
			mControlVec[i]->Stop();
		}
	}

	void AnimationManager::DeleteAll()
	{
		for(int i = 0; i < mControlVec.size(); i++)
		{
			mControlVec[i]->Delete();
		}
		mAnimMap.clear();
	}

	int AnimationManager::GetNumStoredAnims()
	{
		return mAnimMap.size();
	}

	int AnimationManager::GetRegisteredAnims()
	{
		return mControlVec.size();
	}
}
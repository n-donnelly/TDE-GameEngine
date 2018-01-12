#ifndef ANIM_MGR
#define ANIM_MGR

#include "TDE_Animation.h"

namespace TDE
{
	class AnimationManager
	{
	public:
		AnimationManager(TextureManager* aTexMgr);
		AnimationManager(void);
		~AnimationManager(void);

		bool LoadAnimation(std::string name, TDEImage* cells[], int numCells);
		bool LoadAnimation(std::string name, TDEImage* anIm, int cellWidth, int cellHeight, int numCells);
		bool LoadAnimation(std::string name, std::string path, int cellWidth, int cellHeight, int numCells);
		bool LoadAnimation(std::string name, std::string path, int cellWidth, int cellHeight, int totalWidth, int totalHeight, int numCells);

		TDE_Animation GetAnim(std::string name);

		bool RegisterAnim(TDE_Animation* anim);
		bool DeregisterAnim(TDE_Animation* anim);

		void UpdateAll();
		void PauseAll();
		void ResumeAll();
		void StopAll();
		void DeleteAll();

		int GetNumStoredAnims();
		int GetRegisteredAnims();

	private:
		TextureManager*							mTexMgr;

		std::map<std::string, TDE_Animation>	mAnimMap;
		std::vector<TDE_Animation*>				mControlVec;

		int		mStoredAnims;
		int		mAnimsToControl;

	};
}
#endif
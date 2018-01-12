#ifndef LEVELREADER_H
#define LEVELREADER_H

#include <fstream>
#include <queue>

class QuaysGame;

class LevelReader
{
public:
	LevelReader(int numRowsPerUpdate);
	LevelReader(void);
	~LevelReader(void);

	bool ReadLevel(std::string levelName, QuaysGame* game);
	int GetNextScreen(float height, float width);

private:

	int		mNumLines;
	int		mNumCols;
	int		mCurrentScreenIndex;
	std::queue<char> mLevel[5];
	int		mNumRowsPerUpdate;

	QuaysGame* mGame;
};

#endif
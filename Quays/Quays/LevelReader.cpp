#include "stdafx.h"
#include "LevelReader.h"
#include "QuaysGame.h"
#include "Lock.h"
#include "LightGate.h"


LevelReader::LevelReader(int numRowsPerUpdate)
{
	mNumLines = 5;
	mNumCols = 0;
	mCurrentScreenIndex = 0;
	mNumRowsPerUpdate = numRowsPerUpdate;
}

LevelReader::LevelReader(void)
{
	mNumLines = 5;
	mNumCols = 0;
	mCurrentScreenIndex = 0;
	mNumRowsPerUpdate = 0;
	mGame = NULL;
}


LevelReader::~LevelReader(void)
{
}

bool LevelReader::ReadLevel(std::string levelName, QuaysGame* game)
{
	mGame = game;
	ifstream fileIn("Levels\\" + levelName+".txt", ifstream::in);
	std::string line = "";
	if(fileIn.good())
	{
		int lineIndex = 0;
		while(!fileIn.eof() && lineIndex < 5)
		{
			getline(fileIn, line);
			const char* cLine = line.c_str();
			for(int i = 0; i < line.size(); i++)
			{
				mLevel[lineIndex].push(cLine[i]);
			}
			lineIndex++;
		}
		fileIn.close();
		return true;
	}
	else
	{
		printf("Unable to read level");
		return false;
	}
}

int LevelReader::GetNextScreen(float height, float width)
{
	if(!mGame)
		return -1;

	bool lastWasL = false;
	float xPos = 0.f;
	for(int i = 0; i < mNumRowsPerUpdate; i++)
	{
		float yPos = 0.f;
		for(int j = 0; j < mNumLines; j++)
		{
			char c = mLevel[j].front();
			mLevel[j].pop();
			TDE::TDEColor aCol = TDE::TDEColor(0,0,0);
			switch(c)
			{
			case 'L':
				lastWasL = true;
				break;
			case 'R':
				aCol = RED;
				break;
			case 'G':
				aCol = GREEN;
				break;
			case 'B':
				aCol = BLUE;
				break;
			case 'Y':
				aCol = YELLOW;
				break;
			case 'P' :
				aCol = PURPLE;
				break;
			case 'O':
				aCol = ORANGE;
			default:
				break;
			}
			if(aCol.m_iBlue > 0 || aCol.m_iGreen > 0 || aCol.m_iRed > 0)
			{
				if(lastWasL)
				{
					mGame->PushLock(Lock(Pointf(width+xPos, 0.f), width*0.05f, width, height, aCol));
					return 1;
				}
				else mGame->PushGate(LightGate(Pointf(width+xPos, yPos), 60.f, 150.f, aCol));
			}
			yPos += height/mNumLines;
		}
		xPos += width/mNumRowsPerUpdate;
	}
	mCurrentScreenIndex++;
	return 0;
}
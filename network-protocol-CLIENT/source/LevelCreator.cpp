#include "stdafx.h"
#include "LevelCreator.h"


LevelCreator::LevelCreator(const string p_filename)
{
	m_myFile.open(p_filename);
	ReadLevel();
}


LevelCreator::~LevelCreator()
{
}

void LevelCreator::ReadLevel()
{
	char currentLetter;

	while (!m_myFile.eof() && m_myFile.is_open())
	{
		m_myFile.get(currentLetter);

		if (m_myFile.eof())
		{
			m_myFile.close();
			CreateLevel();
			break;
		}
		myLevel.push_back(currentLetter);
	}
}

void LevelCreator::CreateLevel()
{
	CreateWalls();
}

void LevelCreator::CreateWalls()
{
	int i = 0;
	int positionX = 0;
	int positionY = 0;

	for (auto it = myLevel.begin(); it < myLevel.end(); it++, i++)
	{
		if (myLevel[i] == 'w')
		{
			Wall* wall = new Wall(positionX, positionY);
			walls.push_back(wall);
		}


		positionX += 32;

		if (myLevel[i] == '\n')
		{
			positionY += 32;
			positionX = 0;
		}
	}
}

vector<Wall*>& LevelCreator::GetWalls()
{
	return walls;
}

#pragma once
#include <fstream>
#include "stdafx.h"
#include <vector>
#include "Wall.h"
#include "Constants.h"


class Wall;


class LevelCreator

{
public:
	LevelCreator(const string p_filename);
	~LevelCreator();
	void ReadLevel();
	void CreateLevel();
	void CreateWalls();
	vector<Wall*>& GetWalls();

private:

	vector<Wall*> walls;
	vector<char> myLevel;
	ifstream m_myFile;

};

#pragma once
#include <fstream>
#include "stdafx.h"
#include <vector>
#include "Wall.h"
//#include "Constants.h"


class Wall;


class LevelCreator

{
public:
	LevelCreator(const std::string p_filename);
	~LevelCreator();
	void ReadLevel();
	void CreateLevel();
	void CreateWalls();

	std::vector<Wall*>& GetWalls();
	

private:

	std::vector<Wall*> walls;
	std::vector<char> myLevel;
	std::ifstream m_myFile;

};


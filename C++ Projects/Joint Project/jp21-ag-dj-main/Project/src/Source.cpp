#pragma comment(lib,"libyaml-cppmdd") 

#include <iostream>
#include "LevelLoader.h"



int main() 
{
	LevelData levelData;
	int levelNr = 1;
	LevelLoader::load(levelNr, levelData);
	std::cin.get();
}
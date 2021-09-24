#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Thor/Time.hpp"
#include "MathUtility.h"
#include "Thor/Vectors.hpp"
#include "CollisionDetector.h"
#include "ScreenSize.h"
#include <Thor/Vectors.hpp>
#include "Cell.h"
#include "EnemyShipAI.h"


class Grid
{
public:
	std::queue<Cell> BFSQueue;
	Grid();
	~Grid();
	void createGrid();
	void checkTraversable();
	void render(sf::RenderWindow& t_window);
	void update(double dt);

	bool m_makeVisited;
	int m_endPoint = 0;
	int m_endArrayIndex = 0;
	int m_startArrayIndex = 0;
	int m_startPoint = 0;
	int currentRow;
	int currentCol;
	bool achievedGoal = false;
	const static int m_MAXCOLS = 10;
	const static int m_MAXROWS = 10;

	std::list<std::pair<int, int>> findNeighbours(int t_currentCellArray, int t_currentCellObject);
	std::list<std::pair<int, int>> secondList;
	std::vector<int> cellsPath;
	std::vector<int> thePath;
	std::vector<int>& getPath();
	std::vector<std::vector<Cell>> vectorForTheGrid;
	std::vector<int> bfs(int t_startingArrayIndex, int t_startPoint, int t_endArrayIndex, int t_endPoint);

	int getStartingRow();
	int getStartingCol();
	int getEndingRow();
	int getEndingCol();





};


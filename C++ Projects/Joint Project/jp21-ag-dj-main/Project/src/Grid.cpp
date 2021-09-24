#include "Grid.h"

Grid::Grid()
{
	createGrid();

	cellsPath = bfs(m_startArrayIndex, m_startPoint, m_endArrayIndex, m_endPoint);

}

Grid::~Grid()
{

}



void Grid::createGrid()
{
	sf::Vector2f position{ 0,0 };

	//loop through first array for the rows
	for (int row = 0; row < m_MAXROWS; row++)
	{
		//new vector which will be used to pass values back to the master vector
		std::vector<Cell> tempArray;
		for (int i = 0; i < m_MAXCOLS; i++)
		{
			//creation of a cell - placed into the tempArray
			Cell myCell(position);
			myCell.setRow(row);
			myCell.setCol(i);
			tempArray.push_back(myCell);

			//places the cells across the screen
			position.x += ScreenSize::s_width / 10;
			if (position.x >= 1440)
			{
				position.x = 0;
				position.y += ScreenSize::s_height / 10;
			}
		}

		//pushing values back into the main array for the grid
		vectorForTheGrid.push_back(tempArray);
	}

}

std::list<std::pair<int, int>> Grid::findNeighbours(int t_currentRow, int t_currentCols)
{
	int row = t_currentRow;
	int col = t_currentCols;

	//this will list all neighbours 
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue;
		int n_row = row + ((direction % 3) - 1);
		int n_col = col + ((direction / 3) - 1);

		//checking the bounds of neighbours
		if (n_row >= 0 && n_row < m_MAXROWS && n_col >= 0 && n_col < m_MAXCOLS)
		{
			std::cout << "Neighbour is: " << n_row << " , " << n_col << " , " << std::endl;
			secondList.push_back(std::make_pair(n_row, n_col));
		}
	}

	return secondList;
}

std::vector<int>& Grid::getPath()
{
	return thePath;
}

std::vector<int> Grid::bfs(int t_startRow, int t_startCol, int t_endRow, int t_endCol)
{
	int calc = 0;
	int parentCellID = 0;
	currentRow = 0;
	currentCol = 0;
	BFSQueue.push(vectorForTheGrid.at(t_startRow).at(t_startCol));
	//neighbours value will be pushed back to the list 

	vectorForTheGrid.at(t_startRow).at(t_startCol).setVisited(m_makeVisited);
	Cell* parentNode;
	Cell* childNode;
	std::vector<Cell*> prevNodes;
	std::list<std::pair<int, int>>::iterator iteratorList;
	vectorForTheGrid.at(t_startRow).at(t_startCol).changeEndColor();
	//placing the neighbours in a list with the help of an iterator

	while (!BFSQueue.empty() && achievedGoal == false)
	{
		prevNodes.push_back(parentNode);
		parentNode = &BFSQueue.front();
		BFSQueue.pop();

		std::cout << "Cell : " << parentNode->getRow() << " col: " << parentNode->getCol() << std::endl;
		parentCellID = (parentNode->getRow() * 10) + parentNode->getCol();
		secondList = findNeighbours(parentNode->getRow(), parentNode->getCol());

		for (iteratorList = secondList.begin(); iteratorList != secondList.end() && achievedGoal == false && parentNode->getTraversable() == false;)
		{
			childNode = &vectorForTheGrid.at(secondList.front().first).at(secondList.front().second);
			iteratorList++;
			secondList.pop_front();
			//setting the node to the neigbour^

			int i = 0;
			if (childNode == &vectorForTheGrid.at(t_endRow).at(t_endCol))
			{
				std::cout << "Found the end " << std::endl;
				childNode->changeEndColor();
				calc = (parentNode->getRow() * 10) + parentNode->getCol();
				vectorForTheGrid.at(t_endRow).at(t_endCol).setParent(calc);
				thePath.push_back(t_endRow * 10 + t_endRow);
				achievedGoal = true;
			}

			//storing a ref to the parents cell below
			else if (childNode->getVisited() == false)
			{
				childNode->setVisited(m_makeVisited);
				vectorForTheGrid.at(childNode->getRow()).at(childNode->getCol()).setParent(parentCellID);
				BFSQueue.push(*childNode);
				std::cout << "not in this node " << std::endl;
			}
		}
	}

	int startingCellID = t_startRow * 10 + t_startCol;
	int currentCellID = vectorForTheGrid.at(t_endRow).at(t_endCol).getParent();
	int rowParent = vectorForTheGrid.at(t_endRow).at(t_endCol).getParent() / 10;
	int colParent = vectorForTheGrid.at(t_endRow).at(t_endCol).getParent() % 10;

	while (currentCellID != startingCellID)
	{
		thePath.push_back(currentCellID);
		currentCellID = vectorForTheGrid.at(rowParent).at(colParent).getParent();
		rowParent = vectorForTheGrid.at(rowParent).at(colParent).getParent() / 10;
		colParent = vectorForTheGrid.at(rowParent).at(colParent).getParent() % 10;
	}

	return thePath;
}


int Grid::getStartingRow()
{
	return m_startArrayIndex;
}

int Grid::getStartingCol()
{
	return m_startPoint;
}

int Grid::getEndingRow()
{
	return m_endArrayIndex;
}

int Grid::getEndingCol()
{
	return m_endPoint;
}

void Grid::checkTraversable()
{
	bool notTraversable = true;

	//input the locations of the walls (cell id) for enemy 
	vectorForTheGrid.at(1).at(9).setTraversable(notTraversable);
	vectorForTheGrid.at(2).at(3).setTraversable(notTraversable);
	vectorForTheGrid.at(2).at(9).setTraversable(notTraversable);
	vectorForTheGrid.at(2).at(10).setTraversable(notTraversable);
	vectorForTheGrid.at(3).at(4).setTraversable(notTraversable);
	vectorForTheGrid.at(4).at(5).setTraversable(notTraversable);
	vectorForTheGrid.at(6).at(6).setTraversable(notTraversable);
	vectorForTheGrid.at(6).at(7).setTraversable(notTraversable);
	vectorForTheGrid.at(7).at(0).setTraversable(notTraversable);
	vectorForTheGrid.at(7).at(1).setTraversable(notTraversable);
	vectorForTheGrid.at(7).at(6).setTraversable(notTraversable);
	vectorForTheGrid.at(7).at(7).setTraversable(notTraversable);
	vectorForTheGrid.at(8).at(1).setTraversable(notTraversable);
	vectorForTheGrid.at(1).at(1).setTraversable(notTraversable);



}

void Grid::render(sf::RenderWindow& t_window)
{

	//drawing the Grid
	for (int i = 0; i < m_MAXROWS; i++)
	{
		for (int col = 0; col < m_MAXCOLS;col++)
		{
			t_window.draw(vectorForTheGrid.at(i).at(col).getRect());
		}

	}

}



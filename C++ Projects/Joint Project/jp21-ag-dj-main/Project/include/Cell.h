#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <queue>
#include "ScreenSize.h"
#include "EnemyShipAI.h"



class Cell
{
public:

	Cell(sf::Vector2f t_position);
	Cell();
	void draw(sf::RenderWindow& t_window);
	void changeEndColor();
	void update(double dt);
	void setRow(int t_row);
	void setCol(int t_col);
	void setVisited(bool t_changeValue);
	void setTraversable(bool t_changeValue);
	void setParent(int t_parent);
	bool getTraversable();
	bool getVisited();
	int getRow();
	int getCol();
	int getParent();

	int returnParentCell();
	int returnID();
	bool checkMark();
	void setParentCell(int t_cellID);
	void mark(bool t_marked);

	sf::RectangleShape getRect();

private:


	sf::RectangleShape m_rect;
	sf::Vector2f m_Pos;

	int m_parentCellId;
	int m_id;
	int m_previousCellId;
	int m_col;
	int m_row;
	int m_parent;

	const float m_WIDTH;
	const float m_HEIGHT;

	bool m_marked = false;
	bool m_traversable;
	bool m_visited;

};

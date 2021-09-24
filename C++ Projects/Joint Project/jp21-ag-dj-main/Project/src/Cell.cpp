#include "Cell.h"

Cell::Cell(sf::Vector2f t_position) : m_WIDTH(ScreenSize::s_width / 10), m_HEIGHT(ScreenSize::s_height / 10)
, m_visited(false), m_traversable(false), m_Pos(t_position)
{
	m_rect.setSize(sf::Vector2f{ m_WIDTH,m_HEIGHT });
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(1u);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setPosition(m_Pos);
}

void Cell::update(double dt)
{
}

void Cell::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_rect);
}

Cell::Cell() : m_WIDTH(ScreenSize::s_width / 10), m_HEIGHT(ScreenSize::s_height / 10)
{

}

bool Cell::getTraversable()
{
	return m_traversable;

}

int Cell::getRow()
{
	return m_row;
}

int Cell::getCol()
{
	return m_col;
}

void Cell::setCol(int t_col)
{
	m_col = t_col;
}

void Cell::setVisited(bool t_changeValue)
{
	m_visited = t_changeValue;
}

bool Cell::getVisited()
{
	return false;
}

void Cell::setRow(int t_row)
{
	m_row = t_row;
}

void Cell::setTraversable(bool t_changeValue)
{
	m_traversable = t_changeValue;
}

void Cell::setParent(int t_parent)
{
	m_parent = t_parent;
}

int Cell::getParent()
{
	return m_parent;
}

sf::RectangleShape Cell::getRect()
{
	return m_rect;
}

void Cell::mark(bool t_marked)
{
	m_marked = t_marked;

}

void Cell::changeEndColor()
{
	m_rect.setFillColor(sf::Color::Red);
}


void Cell::setParentCell(int t_cell)
{
	m_parentCellId = t_cell;
}

bool Cell::checkMark()
{
	return m_marked;
}

int Cell::returnID()
{
	return m_id;
}

int Cell::returnParentCell()
{
	return m_parentCellId;
}



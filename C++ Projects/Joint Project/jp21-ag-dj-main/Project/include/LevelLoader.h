#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
#include <vector>
#include <SFML/Graphics.hpp>


struct ShipData
{
	float m_x;
	float m_y;
	float m_scale;
	int m_rotation;

	sf::Vector2f m_position;

};

struct ShipAiData
{
	float m_x;
	float m_y;
	float m_reloadTime;
	int m_maxProjectiles;

	sf::Vector2f m_position;
};

/// <summary>
/// @brief A struct to represent Obstacle data in the level.
/// 
/// </summary>
struct ObstacleData
{
	std::string m_type;
	sf::Vector2f m_position;
	float m_scale;
	double m_rotation;
};

/// <summary>
/// @brief A struct to store Background texture information.
/// 
/// </summary>
struct BackgroundData
{
	std::string m_fileName;
};

struct EnemyData
{
	sf::Vector2f m_position;

	float m_scale;

	double m_rotation;
};


struct LevelData
{
	BackgroundData m_background;
	ShipData m_ship;
	ShipAiData m_enemyShipAI; // ADD THIS
	EnemyData m_enemy;
	std::vector<ObstacleData> m_obstacles;
};

class LevelLoader
{
public:
	/// <summary>
	/// @brief No-op default constructor.
	/// 
	/// </summary>
	LevelLoader() = default;

	static void load(int t_levelNr, LevelData& t_level);
};
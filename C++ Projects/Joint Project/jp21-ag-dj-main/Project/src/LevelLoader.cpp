
#include "LevelLoader.h"

/// The various operator >> overloads below are non-member functions used to extract
///  the game data from the YAML data structure.

/// <summary>
/// @brief Extracts the obstacle type, position and rotation values.
/// 
/// </summary>
/// <param name="t_obstacleNode">A YAML node</param>
/// <param name="t_obstacle">A simple struct to store the obstacle data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_obstacleNode, ObstacleData& t_obstacle)
{
	t_obstacle.m_type = t_obstacleNode["type"].as<std::string>();
	t_obstacle.m_position.x = t_obstacleNode["position"]["x"].as<float>();
	t_obstacle.m_position.y = t_obstacleNode["position"]["y"].as<float>();
	t_obstacle.m_rotation = t_obstacleNode["rotation"].as<double>();
	t_obstacle.m_scale = t_obstacleNode["scale"].as<float>();
}




///// <summary>
///// the enemy position and rotation and location 
///// </summary>
///// <param name="t_enemyNode"></param>
///// <param name="t_enemy"></param>
void operator >> (const YAML::Node& t_enemyNode, EnemyData& t_enemy)
{
	t_enemy.m_position.x = t_enemyNode["position"]["x"].as<float>();
	t_enemy.m_position.y = t_enemyNode["position"]["y"].as<float>();
	t_enemy.m_rotation = t_enemyNode["rotation"].as<double>();
	t_enemy.m_scale = t_enemyNode["scale"].as<float>();
}


/// <summary>
/// @brief Extracts the filename for the game background texture.
/// 
/// </summary>
/// <param name="t_backgroundNode">A YAML node</param>
/// <param name="t_background">A simple struct to store background related data</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_backgroundNode, BackgroundData& t_background)
{
	t_background.m_fileName = t_backgroundNode["file"].as<std::string>();
}



void operator >> (const YAML::Node& t_shipNode, ShipData& t_ship)
{
	t_ship.m_x = t_shipNode["position"]["x"].as<float>();
	t_ship.m_y = t_shipNode["position"]["y"].as<float>();

	t_ship.m_scale = t_shipNode["scale"].as<float>();
	t_ship.m_rotation = t_shipNode["rotation"].as<int>();
	t_ship.m_position = sf::Vector2f(t_ship.m_x, t_ship.m_y);

}


void operator >> (const YAML::Node& t_shipAINode, ShipAiData& t_shipAI)
{
	t_shipAI.m_x = t_shipAINode["position"]["x"].as<float>();
	t_shipAI.m_y = t_shipAINode["position"]["y"].as<float>();
	t_shipAI.m_maxProjectiles = t_shipAINode["max_projectiles"].as<float>();
	t_shipAI.m_reloadTime = t_shipAINode["reload_time"].as<int>();
	t_shipAI.m_position = sf::Vector2f(t_shipAI.m_x, t_shipAI.m_y);
}


/// <summary>
/// @brief Top level function that extracts various game data from the YAML data stucture.
/// 
/// Invokes other functions to extract the background,  and obstacle data.
//   Because there are multiple obstacles, obstacle data are stored in a vector.
/// </summary>
/// <param name="t_levelNode">A YAML node</param>
/// <param name="t_level">A simple struct to store level data for the game</param>
////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{
	t_levelNode["background"] >> t_level.m_background;

	t_levelNode["ai_ship"] >> t_level.m_enemyShipAI;  // ADD THIS



	const YAML::Node& obstaclesNode = t_levelNode["obstacles"].as<YAML::Node>();
	const YAML::Node& shipsNode = t_levelNode["ships"].as<YAML::Node>();
	const YAML::Node& enemyNode = t_levelNode["enemy"].as<YAML::Node>();


	for (unsigned i = 0; i < obstaclesNode.size(); ++i)
	{
		ObstacleData obstacle;
		obstaclesNode[i] >> obstacle;
		t_level.m_obstacles.push_back(obstacle);
	}

	for (unsigned i = 0; i < shipsNode.size(); ++i)
	{
		ShipData ship;
		shipsNode[i] >> t_level.m_ship;
		//t_level.m_ship.push_back(ship);
	}

	for (unsigned i = 0; i < enemyNode.size(); ++i)
	{
		EnemyData enemy;
		enemyNode[i] >> t_level.m_enemy;

		//t_level.m_enemy.push_back(enemy);
	}


}

void LevelLoader::load(int t_levelNr, LevelData& t_level)
{
	std::string filename = "./levelData/level" + std::to_string(t_levelNr) + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		// Call overloaded operator >>, passing baseNode as arg1, t_level as arg2
		baseNode >> t_level;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}
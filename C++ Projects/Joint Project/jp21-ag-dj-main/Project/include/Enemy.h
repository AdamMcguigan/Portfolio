#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include "CollisionDetector.h"
#include "ScreenSize.h"
#include <iostream>
#include "Thor/Time.hpp"

/// <summary>
/// Name: David Jalisevs
/// ID: C00239534
/// This will manage target behaviour
/// </summary>
class Enemy
{
public:
	// constructor
	Enemy();
	/// <summary>
	/// update funcion to game.cpp
	/// </summary>
	/// <param name="dt"></param> delta
	/// <param name="pos"></param> position of the ship
	void update(double dt, sf::Vector2f& pos);
	/// <summary>
	/// render window
	/// </summary>
	/// <param name="window"></param>
	void render(sf::RenderWindow& window);
	void collisionWithWalls(std::vector<sf::Sprite>& t_wallSprites);// collision for walls with target

	float m_timeForEnemy = 0.0f; // clock holder for the enemy respawn
	bool b_enemyReady = false; // bool control for the bullet to be shot
	static constexpr float  TIMER_DUR_THOR = 5.0f; // how long enemy alvve 

	sf::Vector2f offScreenPos{ 9999,9999 }; // the position where bullet is set to when inactive 
	sf::Vector2f m_currentScale{ 0.05f,0.05f };

	sf::Sprite m_targetSprite;
	sf::Clock m_clockToSpawnTarget; // clock
	thor::Timer m_enemyTimer;// time to hold for the game end 
private:
	int ToKepAliveTarget = 0;
	int m_timeRemainThor = 0;
	float m_randomRespawnX; // randon spawn for target
	float m_randomRespawnY;
	float m_howLongTargetAlive = 5.0f;

	sf::Text m_clockText;
	sf::Font m_font;

	sf::Texture m_targetTexture; // target texture 
	sf::Vector2f m_enemyPos; // temp variable 
	sf::Vector2f m_sizeEnemy; // enemy size 

	void initSprites();

};

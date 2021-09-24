#pragma once
#include "MathUtility.h"
#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <Thor/Vectors.hpp>
#include <iostream>
#include <queue>
#include "CollisionDetector.h"

class EnemyShipAI
{
public:
	//constructor
	EnemyShipAI(std::vector<sf::Sprite> & wallSprites);
	//update and render is called in game loop
	void update(Ship const & playerShip, double dt);
	void render(sf::RenderWindow & window);
	void init(sf::Vector2f position);

/// /// <summary>
/// @brief Checks for collision between the AI and player.
/// </summary>
	bool collidesWithPlayer(Ship const& playerShip) const;
	// A sprite for the sip AI
	sf::Sprite m_AiShipBase;

private:
	void initSprites();
	void updateMovement(double dt);

	sf::Vector2f seek(sf::Vector2f playerPosition) const;
	sf::Vector2f collisionAvoidance();

	const sf::CircleShape findMostThreateningObstacle();

	// A sprite for the turret
	sf::Sprite m_turret;
	sf::Texture enemyShipAiTexture;

	// A reference to the container of wall sprites.
	std::vector<sf::Sprite> & m_wallSprites;

	// The current rotation as applied to ship base and turret.
	double m_rotation{ 0.0 };

	// Current velocity.
	sf::Vector2f m_velocity;
	// Steering vector.
	sf::Vector2f m_steering;
	// The ahead vector.
	sf::Vector2f m_ahead;
	// The half-ahead vector.
	sf::Vector2f m_halfAhead;
	//ship current pos
	sf::Vector2f m_shipCurrentPos;

	// The maximum see ahead range.
	static float constexpr MAX_SEE_AHEAD{ 30.0f };
	// The maximum avoidance turn rate.
	static float constexpr MAX_AVOID_FORCE{ 25.0f };
	static float constexpr MAX_FORCE{ 10.0f };
	static float constexpr MASS = 1.0f;
	// The maximum speed for this ship.
	float MAX_SPEED = 50.0f;

	// A container of circles that represent the obstacles to avoid.
	std::vector<sf::CircleShape> m_obstacles;

	enum class AiBehaviour
	{
		SEEK_PLAYER,
		STOP,
		RETREAT
	} m_aiBehaviour;
};


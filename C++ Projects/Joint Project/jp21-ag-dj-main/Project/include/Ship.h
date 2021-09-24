#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include "CollisionDetector.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "ParticleSystem.h"
#include "ScreenSize.h"




/// <summary>
/// Name: David Jalisevs 
/// ID: C00239534
/// This class will manage all ship movement and rotations.
/// </summary>
class Ship
{
public:
	Ship(sf::Texture const& texture, std::vector<sf::Sprite>& t_wallSprites);
	/// <summary>
	/// update to a game.cpp
	/// </summary>
	/// <param name="dt"></param> delta 
	/// <param name="pos"></param> position of the ship
	void update(double dt, sf::Vector2f& pos);
	/// render window
	void render(sf::RenderWindow& window);
	void changeSpriteOfShip();

	//deflects ship pos after collisons
	void deflect();
	void handleKeyInput();
	sf::Vector2f getShipPosition() const;
	float getTurretRotation();
	sf::Vector2f getTurretPosition();
	sf::Sprite getBaseSprite() const;
	//ship texture and sprite
	sf::Texture shipTexture;
	sf::Texture shipTextureOld;
	sf::Texture shipTextureSoy;
	sf::Sprite m_shipBase;

	shipCustom whatShipSprite = shipCustom::WARSHIP;


private:
	ParticleSystem particlesSystem;
	Particle particles;
	MenuState menuState;

	void initSprites();
	void centreTurret();
	void decreaseTurretRotation();
	void increaseTurretRotation();
	void shipDecrementFriction();
	void decreaseRotation();
	void adjustRotation();
	// Boundary check FPR THE SHIP AND THE COLLISION WIUTH WALLS
	void boundaryCheck(sf::Vector2f& pos);
	/// @brief Increases the speed by 1, max speed is capped at 100.
	void increaseSpeed();
	/// @brief Decreases the speed by 1, min speed is capped at -100.
	void decreaseSpeed();
	/// @brief Increases the rotation by 1 degree, wraps to 0 degrees after 359.
	void increaseRotation();
	/// set positon of the ship
	void setPosition(sf::Vector2f& pos);
	/// set rotation
	void setRotation(double t_rot);
	/// checks for wall collisionsPlayerToObjects
	bool checkWallCollision();

	sf::Sprite getTurretSprite() const;

	sf::Sprite m_turret;
	sf::Texture const& m_texture;


	// The current rotation as applied to ship base.
	float m_rotation = 0.0f;
	float m_previousRotation = 0.0f;
	float m_turretRotation = 0.0f;// takes ship rotation speed later on 
	float m_previousTurretRotation = 0.0f;
	float m_rotRad = 0.0f;
	float m_shipRotationSpeed = 5.0f;

	// The ship speed.
	double m_speed = 0.0f; // speed of the ship
	double m_previousSpeed = 0.0f; //holds speed

	bool b_enableRotation = true;

	sf::Vector2f m_previousPosition;
	sf::Vector2f newShipPosition;

	// A reference to the container of wall sprites.
	std::vector<sf::Sprite>& m_wallSpritesVector;
};

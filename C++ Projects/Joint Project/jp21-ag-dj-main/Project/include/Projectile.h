#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Thor/Time.hpp"
#include "MathUtility.h"
#include "Thor/Vectors.hpp"
#include "CollisionDetector.h"
#include "ScreenSize.h"
#include <SFML/Audio.hpp>


/// <summary>
/// Name: David Jalisevs
/// ID: C00239534
/// This will manage Projectile shot
/// </summary>

class Projectile //: public Ship
{
public:
	Projectile();
	void initializeBullet();
	void update(double dt, sf::Vector2f& playerPos, float t_rot); // to keep an update to the game.cpp
	void render(sf::RenderWindow& window); // render the projectile
	void collisionWithWalls(std::vector<sf::Sprite>& t_wallSprites); // collision for walls

	int m_shotsFired = 0; // how many shots fired... used it gamecpp
	sf::Vector2f m_offScreenPosition{ 20000,20000 }; // holster for a bullet when inavtive

	sf::Sprite m_bulletSprite; // sprite of the bullet

private:
	void bulletAction(sf::Vector2f pos);
	void setSound(); //setsound of the projectile

	// To represent the projectile.
	sf::Texture m_bulletTexture;
	// fireSound sound
	sf::SoundBuffer m_fireSoundBuffer;
	sf::Sound m_fireSound;

	thor::Timer m_timer;// time to hold for the next bullet shot
	int  TIMER_DUR_THOR = 100; 
	int m_timeRemainThor = 0;
	//bullet speed 
	static constexpr float PROJECTILE_SPEED{ 750.0f };
	//rotation and delta passed from the ship
	double m_rotation = 0.0f;

	// Where to draw the projectile.
	sf::Vector2f m_startPoint;
	sf::Vector2f turretPos; // holds value of the turret position 


	// if allowed to shoot
	bool b_readyToFire = true; // after it shot if allowed to fire
	bool m_fireRequest{ false };
};
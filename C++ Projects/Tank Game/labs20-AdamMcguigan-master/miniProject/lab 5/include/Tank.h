#pragma once
#include <SFML/Graphics.hpp>
#include <MathUtility.h>
#include <algorithm>
#include "CollisionDetector.h"
#include <SFML/Audio.hpp>
#include <ProjectilePool.h>
#include <functional>



/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:
	Tank(sf::Texture const& texture, std::vector<sf::Sprite> &m_sprites);//, sf::Vector2f const& pos);
	void update(double dt, std::function<void(int)> & t_funcApplyDamage, sf::Sprite t_tankBase, sf::Vector2f &t_pos);
	void render(sf::RenderWindow& window);
	void increaseSpeed();

	/// <summary>
	/// @brief Decreases the speed by 1, min speed is capped at -100.
	/// 
	/// </summary>
	void decreaseSpeed();

	/// <summary>
	/// @brief Increases the rotation by 1 degree, wraps to 0 degrees after 359.
	/// 
	/// </summary>
	void increaseRotation();

	/// <summary>
	/// @brief Decreases the rotation by 1 degree, wraps to 359 degrees after 0.
	/// 
	/// </summary>
	void decreaseRotation();
	// The tank speed.
	double m_speed{ 0.0 };
	double getTurretRotation();
	sf::Vector2f getTurretPos();
	sf::Vector2f getPosition() const;

	// The current rotation as applied to tank base.
	double m_rotation{ 0.0 };
	double m_turretRotation{ 0.0 };
	double m_previousSpeed;
	double m_previousRotation;
	double m_previousTurretRotation;
	float getTargetDuration(float t_duration);
	float targetTime;
	/// <summary>
  /// @brief Processes control keys and applies speed/rotation as appropriate.
  /// </summary>
	void handleKeyInput();

	void increaseTurretRotation();
	void decreaseTurretRotation();
	void centreTurret();
	void returnCentre();

	void setPosition(sf::Vector2f &t_pos);//m_level);

	void slowSpeed();
	bool m_enableRotation = true;
	std::vector<sf::Sprite>& m_wallSprites;
	sf::Texture const& m_texture;
	bool checkWallCollision();
	void deflect();
	void adjustRotation();
	void resetPos(float t_aiTankPosX);

	/// <summary>
	/// @brief Generates a request to fire a projectile.
	/// A projectile will be fired from the tip of the turret only if time limit between shots
	///  has expired. Fire requests are not queued.
	/// </summary>
	void requestFire();
	// The delay time between shots in milliseconds.
	static int const s_TIME_BETWEEN_SHOTS{ 800 };
	bool m_fireRequested = false;
	float m_shootTimer = 50.0f;
	ProjectilePool m_pool;

	sf::RectangleShape fuelRectangleShape;
	double fuelLeft = 600;


	sf::Vector2f m_previousPosition;
	sf::Vector2f m_position{ 500.0f,300.0f };

	sf::Sprite getTurretSprite() const;
	sf::Sprite getBaseSprite() const;
	
private:
	void initSprites(); //removed const & pos 
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;

	

};
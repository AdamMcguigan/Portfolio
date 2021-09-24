#include "Tank.h"
#include <iostream>

Tank::Tank(sf::Texture const& texture, std::vector<sf::Sprite>& m_wallSprites)//, sf::Vector2f const& pos)
	: m_texture(texture)
	, m_wallSprites(m_wallSprites)
{
	initSprites();
	fuelRectangleShape.setSize(sf::Vector2f(fuelLeft, 20));
	fuelRectangleShape.setPosition(450,10);
	fuelRectangleShape.setFillColor(sf::Color::Green);
}


void Tank::update(double dt, std::function<void(int)>& t_funcApplyDamage, sf::Sprite t_tankBase, sf::Vector2f &t_pos)
{
	
	handleKeyInput();
	float radians = (MathUtility::DEG_TO_RAD * m_rotation);

	float newPosX = t_pos.x + cos(radians) * m_speed * (dt / 1000);
	float newPosY = t_pos.y + sin(radians) * m_speed * (dt / 1000);

	t_pos.x = newPosX;
	t_pos.y = newPosY;

	//m_tankBase.setPosition(t_pos.x, t_pos.y);
	setPosition(t_pos);
	m_tankBase.setRotation(m_rotation);

	m_turret.setRotation(m_turretRotation); 
	m_turret.setPosition(m_tankBase.getPosition());

	m_pool.update(dt, t_funcApplyDamage, t_tankBase, m_wallSprites);

	if (m_fireRequested)
	{
		m_shootTimer -= dt;
		if (m_shootTimer <= 0)
		{
			m_shootTimer = s_TIME_BETWEEN_SHOTS;
			m_fireRequested = false;
		}
	}

	m_speed = std::clamp(m_speed, -50.0, 50.0);

	std::cout << m_speed << std::endl;
	slowSpeed();

	if (checkWallCollision())
	{
		deflect();
	}

	
}

void Tank::render(sf::RenderWindow& window)
{
	window.draw(m_tankBase);
	window.draw(m_turret);
	m_pool.render(window);
	window.draw(fuelRectangleShape);
}


void Tank::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
		fuelLeft += m_speed/400;
	}
	fuelRectangleShape.setSize(sf::Vector2f(fuelLeft, 20));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseSpeed();
		fuelLeft -= m_speed/400;
	}
	fuelRectangleShape.setSize(sf::Vector2f(fuelLeft, 20));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_fireRequested == false)
	{
		requestFire();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		decreaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		increaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		centreTurret();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		returnCentre();
	}
}

void Tank::increaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation += 0.5; 
	if (m_turretRotation == 360.0)
	{
		m_turretRotation = 0;
	}
}

void Tank::decreaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation -= 0.5; 
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}
}

void Tank::centreTurret()
{
	m_turretRotation = m_rotation;
	
}

bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(m_turret, sprite) || CollisionDetector::collision(m_tankBase, sprite))
		{
			return true;
		}
	}
	return false;
}

void Tank::deflect()
{
	
	// In case tank was rotating.
	adjustRotation();

	// If tank was moving.
	if (m_speed != 0)
	{
		// Temporarily disable turret rotations on collision.
		m_enableRotation = false;
		// Back up to position in previous frame.
		m_previousPosition = m_tankBase.getPosition();
		m_tankBase.setPosition(m_previousPosition);
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 8;
		}
		else
		{
			m_speed = -8;
		}
	}
	else
	{
		m_enableRotation = true;
	}
}

void Tank::adjustRotation()
{
	//enter code here
	 // If tank was rotating...
	if (m_rotation != m_previousRotation)
	{
		// Work out which direction to rotate the tank base post-collision.
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 1;
		}
		else
		{
			m_rotation = m_previousRotation + 1;
		}
	}
	// If turret was rotating while tank was moving
	if (m_turretRotation != m_previousTurretRotation)
	{
		// Set the turret rotation back to it's pre-collision value.
		m_turretRotation = m_previousTurretRotation;
	}
}

void Tank::resetPos(float t_aiTankPosX)
{
	if (t_aiTankPosX <= 720)
	{
		m_tankBase.setPosition(1000, 200);
		m_turret.setPosition(1000, 200);
	}
	else if (t_aiTankPosX > 720)
	{
		m_tankBase.setPosition(200, 200);
		m_turret.setPosition(200, 200);
	}

	//m_tankBase.setPosition(200,500);
	//m_turret.setPosition(200, 500);
}

void Tank::requestFire()
{
	m_fireRequested = true;
	if (m_shootTimer == s_TIME_BETWEEN_SHOTS)
	{
		sf::Vector2f tipOfTurret(m_turret.getPosition().x + 2.0f, m_turret.getPosition().y);
		tipOfTurret.x += std::cos(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		tipOfTurret.y += std::sin(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		m_pool.create(m_texture, tipOfTurret.x, tipOfTurret.y, m_turret.getRotation());
	}
}

void Tank::initSprites()
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	

}

void Tank::setPosition(sf::Vector2f &t_pos)
{
	if (t_pos.x > 1450)
	{
		t_pos.x = 10;
		t_pos.y = t_pos.y;
		std::cout << "WE OUT HERE GOING TO THE OTHER SIDE" << std::endl;
	}
	else if (t_pos.x < -10)
	{
		t_pos.x = 1430;
		t_pos.y = t_pos.y;
		std::cout << "WE OUT HERE GOING TO THE OTHER SIDE" << std::endl;
	}

	else if (t_pos.y > 910)
	{
		t_pos.x = t_pos.x;
		t_pos.y = 10;
		std::cout << "WE OUT HERE GOING TO THE OTHER SIDE" << std::endl;
	}
	else if (t_pos.y < -10)
	{
		t_pos.y = 900;
		t_pos.y = t_pos.y;
		std::cout << "WE OUT HERE GOING TO THE OTHER SIDE" << std::endl;
	}


	m_tankBase.setPosition(t_pos);
	m_turret.setPosition(t_pos);

}

void Tank::increaseSpeed()
{
	m_previousSpeed = m_speed;

	
	if (m_speed < 100.0)
	{
		m_speed += 2;
	}
}

////////////////////////////////////////////////////////////
void Tank::decreaseSpeed()
{
	m_previousSpeed = m_speed;


	if (m_speed > -100)
	{
		m_speed -= 2;
	}

}

////////////////////////////////////////////////////////////
void Tank::increaseRotation()
{
	m_previousRotation = m_rotation;
	m_rotation += 0.5;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
	
}

////////////////////////////////////////////////////////////
void Tank::decreaseRotation()
{
	m_previousRotation = m_rotation;
	m_rotation -= 0.5;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
	
}

void Tank::slowSpeed()
{
	m_speed = m_speed * 0.99;
}

void Tank::returnCentre()
{
	m_tankBase.setPosition(700, 500);
	m_turret.setPosition(700, 500);
}

double Tank::getTurretRotation()
{
	return m_turretRotation;
}

sf::Vector2f Tank::getTurretPos()
{
	return m_turret.getPosition();
}

float Tank::getTargetDuration(float t_duration)
{
	targetTime = t_duration;
	return targetTime;
}

sf::Vector2f Tank::getPosition() const
{
	return m_tankBase.getPosition();
}

sf::Sprite Tank::getTurretSprite() const
{
	return m_turret;
}

sf::Sprite Tank::getBaseSprite() const
{
	return m_tankBase;
}





// turretRot = current turret rotation
// tankBaseRot = current tank base rotation

//if(turretRot < tankBaseRot)
//{
//	// abs is absolute value
//	// in C++, use std::abs()
//	if(abs(turretRot - tankBaseRot) < 180)
//	{
//		// Call your increaseTurretRotation() function to increment the turret angle
//		increaseTurretRotation();
//	}
//	else
//	{
//		decreaseTurretRotation();
//	}
//}
//else
//{
//	if(abs(turretRot - tankBaseRot) < 180)
//	{
//		decreaseTurretRotation();
//	}
//	else
//	{
//		increaseTurretRotation();
//	}
//}
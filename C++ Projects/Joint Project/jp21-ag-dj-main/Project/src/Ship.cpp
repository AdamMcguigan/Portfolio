/// <summary>
/// SO far only Rotation collisionsPlayerToObjects scenario is working well
/// 
/// What yet to add and fix :
/// add ship projectile
///	make projectile go the direction ship is moving
/// fix the turret rotation when ship collides, part is commented out in the function check for walls for now
/// ship goes sicko mode when collided - fixed by applying old ship position before its collided.
/// </summary>
#include "Ship.h"

Ship::Ship(sf::Texture const& texture, std::vector<sf::Sprite>& t_wallSprites)
	: m_texture(texture),
	m_wallSpritesVector(t_wallSprites)

{
	srand(time(NULL));
	whatShipSprite = shipCustom::WARSHIP;
	initSprites();

}

void Ship::update(double dt, sf::Vector2f& pos)
{
	m_rotRad = (MathUtility::DEG_TO_RAD * m_rotation);
	newShipPosition.x = pos.x + std::cosf(m_rotRad) * m_speed * (dt / 1000);
	newShipPosition.y = pos.y + std::sinf(m_rotRad) * m_speed * (dt / 1000);//rotates the ship possition

	pos = newShipPosition;
	m_previousPosition = pos;
	setPosition(pos);

	setRotation(m_rotation);

	m_turret.setRotation(m_turretRotation);

	//check for the wall collisionsPlayerToObjects
	if (checkWallCollision())
	{
		deflect();
	}
	particlesSystem.Update();
	particles.Update();
	shipDecrementFriction();
}

void Ship::setRotation(double t_rot)
{
	m_shipBase.setRotation(t_rot);
}


void Ship::render(sf::RenderWindow& window)
{
	particlesSystem.Draw(window);
	particles.Draw(window);
	window.draw(m_shipBase);
	window.draw(m_turret);
}


void Ship::initSprites()
{

	if (!shipTexture.loadFromFile("./resources/images/ship.png"))
	{
		// error..
		std::cout << "eerror" << std::endl;
		throw std::exception();
	}
	if (!shipTextureOld.loadFromFile("./resources/images/oldSHip.png"))
	{
		// error..
		std::cout << "eerror" << std::endl;
		throw std::exception();
	}
	if (!shipTextureSoy.loadFromFile("./resources/images/soyShip.png"))
	{
		// error..
		std::cout << "eerror" << std::endl;
		throw std::exception();
	}


	
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3, turretRect.height / 2.0);
	m_turret.setScale(0.55, 0.55);
}

void  Ship::changeSpriteOfShip()
{
	// Initialise the ship base
	if (whatShipSprite == shipCustom::WARSHIP)
	{
		m_shipBase.setTexture(shipTexture);
		m_shipBase.setOrigin(105, 15);
		m_shipBase.setScale(0.65, 0.65);
	}
	else if (whatShipSprite == shipCustom::OLDSHIP)
	{
		m_shipBase.setTexture(shipTextureOld);
		m_shipBase.setOrigin(174, 75);
		m_shipBase.setScale(0.45, 0.25);
	}
	else if (whatShipSprite == shipCustom::SOYSHIP)
	{
		m_shipBase.setTexture(shipTextureSoy);
		m_shipBase.setOrigin(321, 61);
		m_shipBase.setScale(0.25, 0.25);
	}

}



/// <summary>
/// containts boundry check
/// </summary>
/// <param name="pos"></param>
void Ship::setPosition(sf::Vector2f& pos)
{
	std::cout << pos.x << std::endl;
	boundaryCheck(pos);


	m_shipBase.setPosition(pos.x + 90,pos.y);
	m_turret.setPosition(pos.x + 90,pos.y);
}


void Ship::increaseSpeed()
{
	m_previousSpeed = m_speed;
	if (m_speed < 100.0)
	{
		m_speed += 10;

	}
}

void Ship::decreaseSpeed()
{
	m_previousSpeed = m_speed;
	if (m_speed > -100.0)
	{
		m_speed -= 10;

	}
}

void Ship::increaseRotation()
{
	m_previousRotation = m_rotation; // NEW

	m_rotation += m_shipRotationSpeed;
	m_turretRotation += m_shipRotationSpeed; // so that turret stays on the same angle as ship when just rotates

	if (m_rotation >= 360.0)
	{
		m_rotation = 0;
	}
}


void Ship::decreaseRotation()
{
	m_previousRotation = m_rotation; // NEW

	m_rotation -= m_shipRotationSpeed;
	m_turretRotation -= m_shipRotationSpeed; // so that turret stays on the same angle as ship when just rotates

	if (m_rotation <= 0.0)
	{
		m_rotation = 359.0;
	}
}


void Ship::deflect()
{
	// In case ship was rotating.
	adjustRotation();
	// If ship was moving.
	if (m_speed != 0)
	{
		// Temporarily disable turret rotations on collisionsPlayerToObjects.
		b_enableRotation = false;
		// Back up to position in previous frame.
		m_shipBase.setPosition(m_previousPosition);
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
}

void Ship::adjustRotation()
{
	// If ship was rotating...
	if (m_rotation != m_previousRotation)
	{
		// Work out which direction to rotate the ship base post-collisionsPlayerToObjects.
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 0,5;
		}
		else
		{
			m_rotation = m_previousRotation + 0.5;
		}
	}
	//If turret was rotating while ship was moving
	if (m_turretRotation != m_previousTurretRotation)
	{
		// Set the turret rotation back to it's pre-collisionsPlayerToObjects value.
		m_turretRotation = m_previousTurretRotation;//Removed for now until further notice yes
	}
}




void Ship::handleKeyInput() // key input 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// Move up...
		particlesSystem.Initialise(sf::Vector2f{m_shipBase.getPosition()});

		increaseSpeed();

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Move right...
		increaseRotation();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) // rotate turret left
	{
		increaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) // rotate turret right
	{
		decreaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) // Center the turret 
	{
		centreTurret();
	}


}

void Ship::shipDecrementFriction()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false)
	{
		m_speed = m_speed * .989;
	}
}

void Ship::increaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation += 4;
	if (m_turretRotation >= 360.0)
	{
		m_turretRotation = 0;
	}
}

void Ship::decreaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation -= 4;
	if (m_turretRotation <= 0.0)
	{
		m_turretRotation = 359.0;
	}
}

void Ship::centreTurret() // centers the turret andrew helped me 
{
	//m_turretRotation = m_rotation;
	if (m_turretRotation < m_rotation)
	{
		// abs is absolute value
		// in C++, use std::abs()
		if (abs(m_turretRotation - m_rotation) < 180)
		{
			increaseTurretRotation();
		}
		else
		{
			decreaseTurretRotation();
		}
	}
	else
	{
		if (abs(m_turretRotation - m_rotation) < 180)
		{
			decreaseTurretRotation();
		}
		else
		{
			increaseTurretRotation();
		}
	}
}

bool Ship::checkWallCollision() // will finish later
{
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	for (sf::Sprite const& sprite : m_wallSpritesVector)
	{
		// Checks if either the ship base or turret has collided with the current wall sprite.
		if (CollisionDetector::collisions(m_shipBase, sprite) ||
			CollisionDetector::collisions(m_shipBase, sprite))
		{
			return true;
		}
	}
	return false;

}


/// <summary>
/// set turret rotation
/// </summary>
/// <returns></returns>
float Ship::getTurretRotation()//
{
	return m_turretRotation;
}


/// <summary>
/// sends turret pos for the projectile
/// </summary>
/// <returns></returns>
sf::Vector2f Ship::getTurretPosition()//(
{
	return m_turret.getPosition();
}

/// <summary>
/// returns player shiop possition to the shipAI
/// </summary>
/// <returns></returns>
sf::Vector2f Ship::getShipPosition() const
{
	return m_shipBase.getPosition();
}


sf::Sprite Ship::getTurretSprite() const
{
	return m_turret;
}
sf::Sprite Ship::getBaseSprite() const
{
	return m_shipBase;
}


void Ship::boundaryCheck(sf::Vector2f& pos)
{
	if (pos.x > 1420)
	{
		pos.x = -70;
		pos.y = pos.y;
		std::cout << "WENNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" << std::endl;
	}
	else if (pos.x < -100)
	{
		pos.x = 1410;
		pos.y = pos.y;
		std::cout << "WENNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" << std::endl;
	}

	else if (pos.y > 910)
	{
		pos.x = pos.x;
		pos.y = 10;
		std::cout << "WENNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" << std::endl;
	}
	else if (pos.y < -10)
	{
		pos.y = 900;
		pos.y = pos.y;
		std::cout << "WENNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" << std::endl;
	}

}
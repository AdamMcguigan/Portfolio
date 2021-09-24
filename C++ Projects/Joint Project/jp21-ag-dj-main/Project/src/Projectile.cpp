
#include "Projectile.h"
Projectile::Projectile() {
	initializeBullet();
	setSound();
}

void Projectile::initializeBullet()
{
	if (!m_bulletTexture.loadFromFile("./resources/images/projec.png"))
	{
		// error..
		std::cout << "eerror" << std::endl;
		throw std::exception();
	}
	m_bulletSprite.setTexture(m_bulletTexture);
	m_bulletSprite.setScale(sf::Vector2f(0.022, 0.022));
	m_bulletSprite.setPosition(m_offScreenPosition);
	m_bulletSprite.setOrigin(2,2);

	m_timer.reset(sf::Time(sf::milliseconds(TIMER_DUR_THOR)));
}

/// <summary>
/// If bullet is ready to be shot
/// </summary>
void Projectile::bulletAction(sf::Vector2f playerPos)
{
	if (b_readyToFire)
	{
		m_timer.start();
		m_timeRemainThor = m_timer.getRemainingTime().asSeconds();

		// check if the event is a a mouse button release
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_timeRemainThor == 0)
		{
			if (m_bulletSprite.getPosition() == m_offScreenPosition )
			{
				m_fireSound.play();

				b_readyToFire = false;
				m_shotsFired = m_shotsFired + 1;
				m_fireRequest = true;
				m_timeRemainThor = 2;
				TIMER_DUR_THOR = 2000;
				//m_timer.stop();
				m_timer.reset(sf::Time(sf::milliseconds(TIMER_DUR_THOR)));
			}
		}
	}

	else
	{
		b_readyToFire = true;
	}
}

/// <summary>
/// bullet movement
/// </summary>
void Projectile::update(double dt, sf::Vector2f& playerPos, float t_rot)
{
	bulletAction(playerPos);
	// If space has been pressed (fire request)
	// Initiate the timer
	m_rotation = t_rot;
	turretPos = playerPos;

	if (m_fireRequest)
	{
		m_startPoint = sf::Vector2f
		(
			turretPos.x + 1 * std::cos(m_rotation * MathUtility::DEG_TO_RAD),
			turretPos.y + 1 * std::sin(m_rotation * MathUtility::DEG_TO_RAD)
		);

			m_bulletSprite.setPosition(m_startPoint);
			m_bulletSprite.setRotation(t_rot);
		
		m_startPoint = thor::unitVector(m_startPoint - turretPos);
		m_fireRequest = false;
	}

	m_bulletSprite.move(m_startPoint.x * PROJECTILE_SPEED * (dt / 1000), m_startPoint.y * PROJECTILE_SPEED * (dt / 1000));

	/// <summary>
	/// Sprite reset 
	/// </summary>
	if (m_bulletSprite.getPosition().y < 0 || m_bulletSprite.getPosition().y >= 899 || m_bulletSprite.getPosition().x <= 0 || m_bulletSprite.getPosition().x >= 1439)
	{
		m_bulletSprite.setPosition(m_offScreenPosition);
	}
}

void Projectile::collisionWithWalls(std::vector<sf::Sprite>& t_wallSprites)
{
	/// <summary>
	/// collisions 
	for (sf::Sprite const& sprite : t_wallSprites)
	{
		// Checks if either the ship base or turret has collided with the current wall sprite.
		if (CollisionDetector::collisions(m_bulletSprite, sprite))
		{
			m_bulletSprite.setPosition(m_offScreenPosition);
		}
	}
}

/// <summary>
/// Sets sound for the projectile being shot
/// </summary>
void Projectile::setSound()
{
	if (!m_fireSoundBuffer.loadFromFile("./resources/audio/fireShot.wav")) // EXPLOSION SOUND./resources/
	{
		std::cout << "problem loading Explosion sound" << std::endl;
	}
	m_fireSound.setBuffer(m_fireSoundBuffer);
	m_fireSound.setVolume(70.0f);
}


void Projectile::render(sf::RenderWindow& window)
{
	window.draw(m_bulletSprite);
}

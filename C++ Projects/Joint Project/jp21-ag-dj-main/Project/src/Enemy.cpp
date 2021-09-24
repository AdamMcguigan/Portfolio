#include "Enemy.h"


Enemy::Enemy()
{
	initSprites();
}

/// <summary>
/// SPrite set up for target
/// </summary>
void Enemy::initSprites()
{
	srand(time(NULL));

	if (!m_targetTexture.loadFromFile("./resources/images/enemy.png"))
	{
		// error..
	}
	m_targetSprite.setTexture(m_targetTexture);
	m_targetSprite.setScale(m_currentScale);
	m_targetSprite.setOrigin(sf::Vector2f(572.5,572.5));
	m_targetSprite.setPosition(m_enemyPos);

	m_enemyTimer.reset(sf::Time(sf::seconds(TIMER_DUR_THOR)));
}

/// <summary>
/// update function
/// </summary>
/// <param name="dt"></param>
/// <param name="pos"></param>
void Enemy::update(double dt, sf::Vector2f& pos)
{
	m_enemyPos = pos;
	m_timeForEnemy = m_clockToSpawnTarget.getElapsedTime().asSeconds();

	if(b_enemyReady == false) 
	{
		std::cout << " TARGET SPAWN TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  TARGET SPAWN  " << std::endl;

		m_randomRespawnX = rand() % int(ScreenSize::s_width - m_targetSprite.getGlobalBounds().width);
		m_randomRespawnY = rand() % int(ScreenSize::s_height - m_targetSprite.getGlobalBounds().height);
		b_enemyReady = true; // states that enemy did appear and is ready 


		m_targetSprite.setPosition(m_randomRespawnX, m_randomRespawnY);

	}

	m_enemyTimer.start();
	m_timeRemainThor = m_enemyTimer.getRemainingTime().asSeconds();// / TIMER_DUR_THOR;
	/// <summary>
	/// RESPAWN FUNCTION
	if (b_enemyReady) // if enemy appeared then it will count to 5 seconds and then dissapear 
	{
		if (m_timeRemainThor <= 3)
		{
			m_sizeEnemy.y = m_targetSprite.getScale().y;
			m_sizeEnemy.x = m_targetSprite.getScale().x;

			m_sizeEnemy.x = m_sizeEnemy.x - 0.00007;
			m_sizeEnemy.y = m_sizeEnemy.y - 0.00007;

			m_targetSprite.setScale(m_sizeEnemy);
		}

		if (m_timeRemainThor <= 0 ) // if timer hits its end
		{
			m_randomRespawnX = rand() % int(ScreenSize::s_width - m_targetSprite.getGlobalBounds().width);
			m_randomRespawnY = rand() % int(ScreenSize::s_height - m_targetSprite.getGlobalBounds().height);
			m_targetSprite.setPosition(m_randomRespawnX, m_randomRespawnY);
			std::cout << "TARGET Reset" << std::endl;
			m_timeForEnemy = m_clockToSpawnTarget.restart().asSeconds();
			m_enemyTimer.reset(sf::Time(sf::seconds(TIMER_DUR_THOR)));
			m_targetSprite.setScale(m_currentScale);
		}			
	}
}

/// <summary>
/// Prevents target spawning inside of the wall
/// </summary>
/// <param name="t_wallSprites"></param>
void Enemy::collisionWithWalls(std::vector<sf::Sprite>& t_wallSprites)
{
/// collisions 
	for (sf::Sprite const& sprite : t_wallSprites)
	{
		// Checks if either the target has collided with the current wall sprite.
		if (CollisionDetector::collisions(m_targetSprite, sprite))
		{
			m_randomRespawnX = rand() % int(ScreenSize::s_width - m_targetSprite.getGlobalBounds().width);
			m_randomRespawnY = rand() % int(ScreenSize::s_height - m_targetSprite.getGlobalBounds().height);
			m_targetSprite.setPosition(m_randomRespawnX, m_randomRespawnY);
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Target succesfully remapped" << std::endl;
		}
	}
}

/// <summary>
/// rednder window
/// </summary>
/// <param name="window"></param>
void Enemy::render(sf::RenderWindow& window)
{
	window.draw(m_targetSprite);
}
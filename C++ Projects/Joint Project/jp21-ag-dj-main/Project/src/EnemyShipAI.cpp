#include "EnemyShipAI.h"

////////////////////////////////////////////////////////////
EnemyShipAI::EnemyShipAI(std::vector<sf::Sprite> & wallSprites)
	: m_aiBehaviour(AiBehaviour::SEEK_PLAYER)
	, m_wallSprites(wallSprites)
	, m_steering(0, 0)
{
	// Initialises the ship base and turret sprites.
	initSprites();
}

////////////////////////////////////////////////////////////
void EnemyShipAI::update(Ship const & playerShip, double dt)
{
	m_shipCurrentPos = playerShip.getShipPosition();
	sf::Vector2f vectorToPlayer = seek(playerShip.getShipPosition());
	sf::Vector2f acceleration; // ADD THIS

	switch (m_aiBehaviour)
	{
	case AiBehaviour::SEEK_PLAYER:
		m_steering += thor::unitVector(vectorToPlayer);
		m_steering += collisionAvoidance();
		m_steering = MathUtility::truncate(m_steering, MAX_FORCE);
		acceleration = m_steering / MASS;  
		m_velocity = MathUtility::truncate(m_velocity + acceleration, MAX_SPEED);

		break;
	case AiBehaviour::STOP:
		m_velocity = sf::Vector2f(0, 0);
		//motion->m_speed = 0;
	default:
		break;
	}

	// Now we need to convert our velocity vector into a rotation angle between 0 and 359 degrees.
	// The m_velocity vector works like this: vector(1,0) is 0 degrees, while vector(0, 1) is 90 degrees.
	// So for example, 223 degrees would be a clockwise offset from 0 degrees (i.e. along x axis).
	// Note: we add 180 degrees below to convert the final angle into a range 0 to 359 instead of -PI to +PI
	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_rotation;

	// Find the shortest way to rotate towards the player (clockwise or anti-clockwise)
	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}

	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation = static_cast<int>((m_rotation) + 1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation = static_cast<int>((m_rotation) - 1) % 360;
	}


	if (thor::length(vectorToPlayer) < MAX_SEE_AHEAD)
	{
		m_aiBehaviour = AiBehaviour::STOP;
	}
	else
	{
		m_aiBehaviour = AiBehaviour::SEEK_PLAYER;
	}

	updateMovement(dt);
}

////////////////////////////////////////////////////////////
void EnemyShipAI::render(sf::RenderWindow & window)
{
	// TODO: Don't draw if off-screen...
	window.draw(m_AiShipBase);
}

////////////////////////////////////////////////////////////
void EnemyShipAI::init(sf::Vector2f position)
{
	m_AiShipBase.setPosition(position);

	for (sf::Sprite const wallSprite : m_wallSprites)
	{
		sf::CircleShape circle(wallSprite.getTextureRect().width * 1.5f);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(wallSprite.getPosition());
		m_obstacles.push_back(circle);
	}
}

////////////////////////////////////////////////////////////
sf::Vector2f EnemyShipAI::seek(sf::Vector2f playerPosition) const
{
	//return sf::Vector2f(playerPosition);
	return playerPosition - m_AiShipBase.getPosition();
}

////////////////////////////////////////////////////////////
sf::Vector2f EnemyShipAI::collisionAvoidance()
{
	auto headingRadians = thor::toRadian(m_rotation);
	sf::Vector2f headingVector(std::cos(headingRadians) * MAX_SEE_AHEAD, std::sin(headingRadians) * MAX_SEE_AHEAD);
	m_ahead = m_AiShipBase.getPosition() + headingVector;
	m_halfAhead = m_AiShipBase.getPosition() + (headingVector * 0.5f);
	const sf::CircleShape mostThreatening = findMostThreateningObstacle();
	sf::Vector2f avoidance(0, 0);
	if (mostThreatening.getRadius() != 0.0)
	{		
		avoidance.x = m_ahead.x - mostThreatening.getPosition().x;
		avoidance.y = m_ahead.y - mostThreatening.getPosition().y;
		avoidance = thor::unitVector(avoidance);
		avoidance *= MAX_AVOID_FORCE;
	}
	else
	{
		avoidance *= 0.0f;
	}
	return avoidance;
}

////////////////////////////////////////////////////////////
const sf::CircleShape EnemyShipAI::findMostThreateningObstacle()
{
	//use this as the null value
	//sf::CircleShape mostThreatening = sf::CircleShape(0);
	// The initialisation of mostThreatening is just a placeholder...
	sf::CircleShape mostThreatening (0,0);
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		sf::CircleShape obstacle = m_obstacles.at(i);
		//boolean = lineIntersecsCircle(ahead, ahead2, obstacle);
		bool collision = MathUtility::lineIntersectsCircle(m_ahead, m_halfAhead, obstacle);
		// "position" is the character's current position
		if (collision && (mostThreatening.getPosition() == sf::Vector2f(0, 0) || MathUtility::distance(m_shipCurrentPos, obstacle.getPosition())
			< MathUtility::distance(m_shipCurrentPos, mostThreatening.getPosition())))
		{
			mostThreatening = obstacle;
		}
		
	}
	return mostThreatening;
}

////////////////////////////////////////////////////////////
void EnemyShipAI::initSprites()
{
	// Initialise the ship base
	if (!enemyShipAiTexture.loadFromFile("./resources/images/EnemyShip3.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading enemy shp" << std::endl;
	}

	m_AiShipBase.setTexture(enemyShipAiTexture);
	sf::IntRect baseRect(103, 43, 79, 43);
	m_AiShipBase.setTextureRect(baseRect);
	m_AiShipBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_AiShipBase.setScale(2,1.4);

}


////////////////////////////////////////////////////////////
void EnemyShipAI::updateMovement(double dt)
{
	double speed = thor::length(m_velocity);
	sf::Vector2f newPos(m_AiShipBase.getPosition().x + std::cos(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt / 1000),
		m_AiShipBase.getPosition().y + std::sin(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt / 1000));
	m_AiShipBase.setPosition(newPos.x, newPos.y);
	m_AiShipBase.setRotation(m_rotation);

}


bool EnemyShipAI::collidesWithPlayer(Ship const& playerShip) const
{
	// Checks if the AI Ship has collided with the player Ship.
	if (CollisionDetector::collisions(m_AiShipBase, playerShip.getBaseSprite()))
	{
		std::cout << "COLLIDED SHIP WITH SHIP" << std::endl;

		return true;
	}
	return false;
}
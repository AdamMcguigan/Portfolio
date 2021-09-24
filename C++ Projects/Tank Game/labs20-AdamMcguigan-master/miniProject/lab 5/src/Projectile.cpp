#include "Projectile.h"

void bullet::bulletConst()
{
	bulletload();
	alive = false;
	allowToFire = true;

}

void bullet::bulletload()
{
	if (!m_bulletTexture.loadFromFile("./resources/images/bullet.png"))
	{
		std::cout << "Error... Loading bullet texture" << std::endl;
	}

	m_bulletSprite.setTexture(m_bulletTexture);
	m_bulletSprite.setOrigin(16, 16);
	m_bulletSprite.scale(0.5, 0.5);

}

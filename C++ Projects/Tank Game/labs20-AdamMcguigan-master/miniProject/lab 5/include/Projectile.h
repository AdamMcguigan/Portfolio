#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>>
class bullet
{

public:
	void bulletConst(); //constructor
	bool alive;
	bool allowToFire;
	bool fired;
	sf::Texture m_bulletTexture;
	sf::Sprite m_bulletSprite;
	static constexpr float PROJECTILE_SPEED{ 300.0f };
private:

	void bulletload();
};
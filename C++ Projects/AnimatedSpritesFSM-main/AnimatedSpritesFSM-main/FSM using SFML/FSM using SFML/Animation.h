#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;

class Animation
{
	class State* current;
public:
	//All of the textures that were needed for animations
	sf::Texture playerTextureSheet;
	sf::Texture playerWalkingRightSheet;
	sf::Texture playerWalkingLeftSheet;
	sf::Texture playerJumpingSheet;
	sf::Texture playerCheckDaggerIdleSheet;
	sf::Texture playerGlideSheet;


	sf::Sprite playerSprite;
	sf::IntRect rectSourceSprite;

	float totalElapsed = 0;
	int animationframe = 0;

	Animation();
	void setCurrent(State* s)
	{
		current = s;
	}

	void idle();
	void jumping();
	void climbing();

	//Functions for all the animations
	void idleAnimation();
	void jumpingAnimation();
	void walkingLeftAnimation();
	void walkingRightAnimation();
	void checkDaggerAnimation();
	void glideAnimation();
	void reset();


};
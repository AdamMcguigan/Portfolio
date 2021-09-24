#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector>

enum class ButtonState { READY, OVER, DOWN };

class MenuButton
{
public:
	sf::Sprite buttonSprite;
	sf::RectangleShape shape;
	ButtonState state = ButtonState::READY;
	bool pressed = false;

	void Init(sf::Vector2f pos, sf::Font& font);
	void Update(sf::RenderWindow& window);

	sf::Text text;


private:
	void UpdateUI();
	sf::Color curFillColor;

	sf::Vector2f readyPos;
	sf::Vector2f downPos;
	sf::Texture buttonTexture;
	

};

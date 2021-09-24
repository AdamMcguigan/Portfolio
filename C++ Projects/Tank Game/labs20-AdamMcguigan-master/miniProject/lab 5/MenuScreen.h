#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "ScreenSize.h"


class MenuScreen
{
	/// Number of buttons on our menu
	static const int m_optionCount = 3;
	/// green button background
	sf::Texture m_buttonTexture;
	/// array of sprites used to display buttons
	sf::Sprite m_buttonSprites[m_optionCount];
	/// local refrence to font used by whole game
	sf::Font m_fontBigBoi;
	/// array of text objects for text on buttons
	sf::Text m_buttonTexts[m_optionCount];

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	

	/// top left of area used for menu
	float m_topOffset;
	/// top left of area used for menu
	float m_leftOffset;
	/// gap in pixels between tops of buttons
	float m_verticalSpacing;
	/// width in pixels of all buttons
	float m_buttonWidth;
	/// height of button in pixels must be less than vertical spacing
	float m_buttonHeight;

public:
	void initialise(sf::Font&);
	void draw(sf::RenderWindow&);
	void update(sf::Window&, int& t_gameMode);

};

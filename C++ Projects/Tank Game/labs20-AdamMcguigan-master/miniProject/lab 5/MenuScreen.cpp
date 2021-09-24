#include "MenuScreen.h"

/// <summary>
/// setup font and message.
/// 
/// Used to get a reference to the font and  
/// load texture and setup sprite and text
/// for each button and positions on screen
void MenuScreen::initialise(sf::Font& font)
{
	m_topOffset = 250;
	m_verticalSpacing = 100;
	m_buttonWidth = 300;
	m_leftOffset = (ScreenSize::s_width - m_buttonWidth) / 2;
	m_buttonHeight = 50;
	int textDropOffset = 10;
	sf::String m_menuTexts[] = { "Play", "Controls", "Exit" };
	m_fontBigBoi = font;

	/// display error if button.png doesnt load properly
	if (!m_buttonTexture.loadFromFile("./resources/images/tankShellButton.png"))
	{
		std::cout << "error with loading the button sprite";
	}

	if (!backgroundTexture.loadFromFile("./resources/images/menuBackground.png"))
	{
		std::cout << "error with loading the main menu background sprite";
	}

	backgroundSprite.setTexture(backgroundTexture);


	/// for loop to setup menu buttons in an array
	/// keeps them in a centre nicely laid out
	/// scales them to texture size so they look to scale
	/// 
	for (int i = 0; i < m_optionCount; i++)
	{
		m_buttonSprites[i].setTexture(m_buttonTexture);
		m_buttonSprites[i].setPosition(m_leftOffset, m_verticalSpacing * i + m_topOffset);
		sf::Vector2u textureSize = m_buttonTexture.getSize();
		m_buttonSprites[i].setScale(m_buttonWidth / textureSize.x, m_buttonHeight / textureSize.y);

		// sets font up for the array of text shapes that display over the buttons
		m_buttonTexts[i].setFont(m_fontBigBoi);
		m_buttonTexts[i].setString(m_menuTexts[i]);
		m_buttonTexts[i].setFillColor(sf::Color::White);
		m_buttonTexts[i].setCharacterSize(24);

		sf::FloatRect textSize = m_buttonTexts[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / 2;
		m_buttonTexts[i].setPosition(m_leftOffset + textOffset, m_verticalSpacing * i + m_topOffset + textDropOffset);
	}
}


/// <summary>
/// check current position of the mouse for intersection with
/// location of buttons using locations and offsets rather than rectangles
/// for intersection (create said so 'imaginary' columns and rows, then mouse x/y 
/// values are compared to see if they are intersecting columns' then rows' x/y values
/// </summary>
void MenuScreen::update(sf::Window& window, int& t_gameMode)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mouseLocation;
		mouseLocation = sf::Mouse::getPosition(window);
		if (mouseLocation.x > m_leftOffset && mouseLocation.x < m_leftOffset + m_buttonWidth)
		{
			if (mouseLocation.y > m_topOffset && mouseLocation.y && mouseLocation.y < m_topOffset + m_buttonHeight)
			{
				t_gameMode = GAME_PLAY;
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing && mouseLocation.y < m_topOffset + m_verticalSpacing + m_buttonHeight)
			{
				t_gameMode = INSTRUCTIONS;
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing * 2 && mouseLocation.y < m_topOffset + m_verticalSpacing * 2 + m_buttonHeight)
			{
				window.close();
			}
		}
	}
}

/// <summary>
///  draw menu text over buttons
/// </summary>
void MenuScreen::draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);

	for (int i = 0; i < m_optionCount; i++)
	{
		window.draw(m_buttonSprites[i]);
		window.draw(m_buttonTexts[i]);
	}
}
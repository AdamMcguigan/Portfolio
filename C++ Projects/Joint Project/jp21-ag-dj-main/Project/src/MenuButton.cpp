#include "MenuButton.h"


void MenuButton::Init(sf::Vector2f pos, sf::Font& font)
{
	if (!buttonTexture.loadFromFile("./resources/images/buttonWarship.png"))
	{
		std::cout << "Error loading the button Texture" << std::endl;
	}

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setScale(2.5, 2.2);
	buttonSprite.setPosition(pos);

	pressed = false;
	readyPos = pos;
	curFillColor = sf::Color::Blue;
	downPos = sf::Vector2f(pos.x - 10, pos.y + 10);
	//shape.setSize(sf::Vector2f(500, 100));
	//shape.setPosition(pos);

	text.setFont(font);
	UpdateUI();

}
void MenuButton::UpdateUI()
{
	text.setPosition(buttonSprite.getPosition().x + 10, buttonSprite.getPosition().y + 30);

	//shape.setFillColor(curFillColor);
}

void MenuButton::Update(sf::RenderWindow& window)
{
	pressed = false;
	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
	if (state == ButtonState::READY)
	{
		buttonSprite.setPosition(readyPos);
		curFillColor = sf::Color::Blue;
		if (buttonSprite.getGlobalBounds().contains(mousePos))
		{

			state = ButtonState::OVER;
		}

	}
	if (state == ButtonState::OVER)
	{
		curFillColor = sf::Color::Green;

		if (buttonSprite.getGlobalBounds().contains(mousePos))
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state = ButtonState::DOWN;

			}
		}
		else {

			state = ButtonState::READY;
		}
	}

	if (state == ButtonState::DOWN)
	{
		curFillColor = sf::Color::Magenta;
		buttonSprite.setPosition(downPos);
		if (buttonSprite.getGlobalBounds().contains(mousePos))
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state = ButtonState::READY;
				pressed = true;
			}
		}
		else {

			state = ButtonState::READY;
		}
	}


	UpdateUI();
}
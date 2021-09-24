#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 
#include "Player.h"
#include "coin.h"
#include "Animation.h"
#include "Particle.h"

/// <summary>
/// one button platform game 
/// Authors : Adam Mcguigan, Sasa Kuzmanovic, Sean Whelan
/// video link - https://instituteoftechnol663-my.sharepoint.com/:f:/g/personal/c00248515_itcarlow_ie/EkhpmSdezq1Jme-5xGJB2L0BqHBBIt6for7uCXcYwnCCzw?e=gqb42b

class Game
{
public:

	Player player;
	ParticleSystem particlesSystem;
	Particle particles;
	Coin coin;

	sf::Texture playerTextureSheet;
	sf::Sprite playerSpriteSheet;

	sf::Texture coinTextureSheet;
	sf::Sprite coinSpriteSheet;
	sf::Text scoreText;
	sf::Font font;

	int score = 0;
	float playerOffset = 35.0f;

	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;

	bool coinIsCollected = false;
	bool stopDrawingCoin = false;

	sf::RectangleShape playerShape;


	float velocityX = 0, velocityY = 0, gravity = 0.3;
	float pixelsPerMeter = 2.4;
	sf::Vector2f pushOff{ 0, -5 * pixelsPerMeter };


	static const int numRows = 55;
	static const int numCols = 20;
	int levelData[numRows][numCols] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,2,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,4,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,4 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3,0,0 }, 
	{ 0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,1,1,1,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,4,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,1,0,4,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },////////////////////////////
	{ 0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	

	sf::RectangleShape level[numRows][numCols];

	Game()
		: window(sf::VideoMode(800, 600, 32), "SFML Playground", sf::Style::Default),
		player(playerSpriteSheet),
		coin(coinSpriteSheet)
	{

		if (!font.loadFromFile("arial.ttf"))
		{
			std::cout << "Error loading the font for the score " << std::endl;
		}

		if (!playerTextureSheet.loadFromFile("character_robot_sheet.png"))
		{
			std::cout << "Error loading the robot sprite sheet " << std::endl;
		}
		playerSpriteSheet.setTexture(playerTextureSheet);

		if (!coinTextureSheet.loadFromFile("spr_coin_roj.png"))
		{
			std::cout << "Error loading the coin image " << std::endl;
		}
		coinSpriteSheet.setTexture(coinTextureSheet);

		window.setVerticalSyncEnabled(true);
		player.InitAnimationData();
		player.startAnimaton(PlayerAnimationState::walk);

		coin.InitAnimationData();
		coin.startAnimaton(Coin::CoinAnimationState::coinflip);


		playerSpriteSheet.setPosition(50, 50);
		playerSpriteSheet.setOrigin(39, 39);
		playerSpriteSheet.setScale(0.6, 0.6);

		
		coinSpriteSheet.setOrigin(39, 39);
		coinSpriteSheet.setScale(1.9, 1.9);

		scoreText.setFont(font);
		scoreText.setPosition(550, 0);
		scoreText.setString("Coins collected: " + std::to_string(score));
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Red);



	};

	void init()
	{
		stopDrawingCoin = false;
		score = 0;
		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);


		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{

				if (levelData[row][col] == 1)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Green);
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Red);

				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Magenta); //Trampoline

				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Yellow); //Speed Boost

				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Cyan);
				}

			}
		}

	}
	void run()
	{

		float scrollSpeed = -3.7f;

		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		sf::Clock clock;

		clock.restart();

		while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			timeSinceLastUpdate += clock.restart();

			//function to make the background scroll
			if (timeSinceLastUpdate > timePerFrame)
			{

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						level[row][col].move(scrollSpeed, 0);
					}

				}

				//update methods being called for all the classes
				player.Update();
				coin.Update();
				particlesSystem.Update();
				particles.Update();

				//setting the position for both the player and the coin 
				playerSpriteSheet.setPosition(playerShape.getPosition().x, playerShape.getPosition().y - playerOffset);
				coinSpriteSheet.setPosition(level[1][1].getPosition().x + 1000, level[1][1].getPosition().y + 400);


				sf::Vector2f position{ playerShape.getPosition() };
				float timeChange = (float)timeSinceLastUpdate.asSeconds();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
				{
					velocityY = pushOff.y;
					position.y = velocityY;
					position = position * timeChange;
				}
				else
				{
					//update position and velocity
					position.y = position.y + velocityY;
					position = position * timeChange;
					velocityY = velocityY + gravity * timeChange;
				}

				velocityY = velocityY + gravity;
				playerShape.move(0, velocityY);
				gravity = 0.6;

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (velocityY >= 0)
						{
							if (levelData[row][col] == 1)
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									scrollSpeed = -3.7;
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										if (player.animationState == PlayerAnimationState::jump)
										{
											player.startAnimaton(PlayerAnimationState::walk);
										}

										gravity = 0;
										velocityY = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);

										break;
									}
									else {
										init();
										scrollSpeed = -3.7;
									}
								}
							}
							if (levelData[row][col] == 5)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									std::cout << "Congratulations you WON!!!!" << std::endl;
								}
							}

							if (levelData[row][col] == 3) //Trampoline Block
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{

										velocityY = pushOff.y * 1.5;
										position.y = velocityY;
										position = position * timeChange;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										break;
									}
									else {
										init();
										scrollSpeed = -3.7;
									}
								}
							}
							if (levelData[row][col] == 4) //Speed boost Block
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = 0;
										velocityY = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										scrollSpeed = -10.0;
										break;
									}
									else {
										init();
									}
								}
							}
						}
						if (velocityY < 0)
						{
							if (levelData[row][col] == 1)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();

								}

							}

						}
						if (levelData[row][col] == 2)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();

							}
						}
					}
				}

				if (playerShape.getPosition().y > window.getSize().y)
				{
					init();
				}
				
				//When player collides with the coin, particle system will be called to display and the stop drawing coin bool will be set to true
				if (playerShape.getGlobalBounds().intersects(coinSpriteSheet.getGlobalBounds()))
				{
					particlesSystem.Initialise(sf::Vector2f{ level[1][1].getPosition().x + 1000, level[1][1].getPosition().y + 300 });

					score = 1;
					stopDrawingCoin = true;
				}

				scoreText.setString("Coins: " + std::to_string(score));

				window.clear();

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						window.draw(level[row][col]);

					}
				}
				
				player.Draw(window);

				//Bool to draw the coin
				if (stopDrawingCoin == false)
				{
					coin.Draw(window);
				}

				//particles being drawn
				particlesSystem.Draw(window);
				particles.Draw(window);
			
				window.draw(scoreText);

				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};


int main()
{
	Game game;
	game.init();
	game.run();

	return 0;
}

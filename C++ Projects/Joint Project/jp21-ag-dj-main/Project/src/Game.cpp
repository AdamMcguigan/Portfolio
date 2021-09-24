/// <summary>
/// Rotation was fixed by the setting up the initial rotation to 270 or -90/ but im not too sure if that is a right answer. 
/// default rotation for the ship is commented out in a switch statement
/// </summary>

#include "Game.h"
#include "LevelLoader.h"


#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
/// game constructor
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
	, m_ship(m_texture, m_wallSpritesVector)
	, m_enemy() // tarfet constructor
	, m_enemyShipAI(m_wallSpritesVector) // computer Ship consptuctor
	, m_hud(m_font)//hud constructor	
	,collectibleCoin(coinSpriteSheet)
{
	int currentLevel = 1;
	// Will generate an exception if level loading fails.
	try
	{
		LevelLoader::load(currentLevel, m_level);
	}
	catch (std::exception& e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
 	}

	//checkCell();

	m_window.setVerticalSyncEnabled(true);
	m_level.m_enemy.m_position;
	m_level.m_ship.m_position;
	m_gameState = GameState::GAME_RUNNING;
	Game::loadContent();
	m_menuSound.play();

	/// <summary>
	/// random pos at the beginning 
	/// </summary>
	int randomNumber = rand() % 4 + 1;
	if (randomNumber == 1)
	{
		m_startPos = m_level.m_ship.m_position;
	}
	if (randomNumber == 2)
	{
		//m_startPos = sf::Vector2f(100, 800);
		m_startPos = m_level.m_ship.m_position;
	}
	if (randomNumber == 3)
	{
		//m_startPos = sf::Vector2f(1300, 100);
		m_startPos = m_level.m_ship.m_position;

	}
	if (randomNumber == 4)
	{
		//m_startPos = sf::Vector2f(1300, 800);
		m_startPos = m_level.m_ship.m_position;

	}
	m_enemyShipAI.init(m_level.m_enemyShipAI.m_position);
	if (!m_font.loadFromFile("./resources/font/arial.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}


}

/// <summary>
/// loads content to the constructor
/// </summary>
void Game::loadContent()
{
	backgroundSetup();
	spriteSetup(); 
	generateWalls();
	setSound();

}


/// <summary>
/// m_wallSprite set up 
/// </summary>
void Game::spriteSetup()
{
	if (!m_texture.loadFromFile("./resources/images/EnemyShip3.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	if (!m_funExpTexture.loadFromFile("./resources/images/explosion.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	if (!coinTextureSheet.loadFromFile("./resources/images/spr_coin_roj.png"))
	{
		// error...
	}

	if (!m_returnBaseTexture.loadFromFile("./resources/images/carrier.png"))
	{
		// error...
	}
	if (!m_rubyShipTexture.loadFromFile("./resources/images/rubyShip.png"))
	{
		// error...
	}
	if (!m_rubyShipTextureOld.loadFromFile("./resources/images/oldShipRRuby.png"))
	{
		// error...
	}
	if (!m_rubyShipTextureSoy.loadFromFile("./resources/images/soyShipRuby.png"))
	{
		// error...
	}


	if (!m_backgroundTexture.loadFromFile("./resources/images/battleship background.jpeg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background for the menu" << std::endl;
	}
	if (!m_keyboardLayoutTexture.loadFromFile("./resources/images/keyboardlayout.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background for the menu" << std::endl;
	}

	if (!m_gameEndTexture.loadFromFile("./resources/images/winPic.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background for the menu" << std::endl;
	}
	if (!m_gameEndTexture2.loadFromFile("./resources/images/lostPic.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading background for the menu" << std::endl;
	}
	m_gameEndSprite.setTexture(m_gameEndTexture);

	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(1.2, 1.2);

	coinSpriteSheet.setTexture(coinTextureSheet);
	collectibleCoin.InitAnimationData();
	collectibleCoin.startAnimaton(Collectible::RubyAnimationState::ruby);
	//coinSpriteSheet.setPosition(100, 100);
	coinSpriteSheet.setOrigin(39, 39);
	coinSpriteSheet.setScale(1.9, 1.9);
	coinSpriteSheet.setPosition(1350, 200);


	m_returnBaseSprite.setTexture(m_returnBaseTexture);
	m_returnBaseSprite.setOrigin(25, 95);
	m_returnBaseSprite.setPosition(120, 790);
	m_returnBaseSprite.setRotation(-45);

	m_keyboardLayoutSprite.setTexture(m_keyboardLayoutTexture);
	m_keyboardLayoutSprite.setPosition(180,200);

	m_soyShipDisplaySprite.setTexture(m_ship.shipTextureSoy);
	m_oldShipDisplaySprite.setTexture(m_ship.shipTextureOld);
	m_warShipDisplaySprite.setTexture(m_ship.shipTexture);
	m_warShipDisplaySprite.setPosition(500, 100);
	m_soyShipDisplaySprite.setPosition(500, 300);
	m_oldShipDisplaySprite.setPosition(500, 470);
	m_warShipDisplaySprite.setScale(1.6, 1.6);
	m_soyShipDisplaySprite.setScale(0.5, 0.5);
	m_oldShipDisplaySprite.setScale(0.9, 0.7);

}

void Game::checkCell()
{
	/*for (int i = 0; i < 3; i++)
	{
		int cellOfPlayer, cellOfCurrentEnemy;

		for (int index = 0; index < 100; index++)
		{
			if (m_ship.m_shipBase.getGlobalBounds().intersects(m_grid.returnCell(index).getRect().getGlobalBounds()))
			{
				cellOfPlayer = index;
			}

			if (m_enemyShipAI.m_AiShipBase.getGlobalBounds().intersects(m_grid.returnCell(index).getRect().getGlobalBounds()))
			{
				cellOfCurrentEnemy = index;
			}
		}


		m_enemyShipAI.traversableCells.push_back(m_grid.breadthSearch(cellOfCurrentEnemy, cellOfPlayer));
		while (m_enemy.traversableCells.at(m_enemy.traversableCells.size() - 1) != cellOfPlayer)
		{
			m_enemyShipAI.traversableCells.push_back(m_grid.breadthSearch(cellOfPlayer, m_enemy.traversableCells.at(m_enemy.traversableCells.size() - 1)));
		}
		m_enemyShipAI.traversableCells.pop_back();

		m_enemyShipAI.isEnemyMoving = true;
		m_enemyShipAI.traversableCells.size();
	}*/
}

/// <summary>
/// background setup
/// </summary>
void Game::backgroundSetup()
{
	if (!m_bgTexture.loadFromFile("./resources/images/Background1.jpg"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_bgSprite.setTexture(m_bgTexture);
	m_bgSprite.setScale(0.8,0.9);
	
	m_clockText.setFont(m_font);
	m_clockText.setPosition(0.0f, 0.0f);
	m_clockText.setString("Time: " + std::to_string(m_timeRemainThor));
	m_clockText.setCharacterSize(34);
	m_clockText.setFillColor(sf::Color::Green);

	m_scoreText.setFont(m_font);
	m_scoreText.setPosition(150.0f, 0.0f);
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setCharacterSize(34);
	m_scoreText.setFillColor(sf::Color::White);

	m_aiShipHPText.setFont(m_font);
	m_aiShipHPText.setPosition(m_enemyShipAI.m_AiShipBase.getPosition().x, m_enemyShipAI.m_AiShipBase.getPosition().y);
	m_aiShipHPText.setString("HP: " + std::to_string(m_aiShipHP));
	m_aiShipHPText.setCharacterSize(28);
	m_aiShipHPText.setFillColor(sf::Color::Red);

	m_gameOverText.setFont(m_font);
	m_gameOverText.setPosition(520.0f, 400.0f);
	m_gameOverText.setString("GAME OVER");
	m_gameOverText.setCharacterSize(54);
	m_gameOverText.setFillColor(sf::Color::Red);

	m_infoScreen1.setFont(m_font);
	m_infoScreen1.setPosition(10.0f, 10.0f);
	m_infoScreen1.setString("IN ORDER TO WIN YOU WILL NEED TO RETURN RUBY BACK TO THE CARRIER");
	m_infoScreen1.setCharacterSize(34);
	m_infoScreen1.setFillColor(sf::Color::Red);

	m_infoScreen2.setFont(m_font);
	m_infoScreen2.setPosition(10.0f, 40.0f);
	m_infoScreen2.setString("KILL THE ENEMY AND GET 40 SCORE TO WIN!");
	m_infoScreen2.setCharacterSize(34);
	m_infoScreen2.setFillColor(sf::Color::Red);

	m_infoScreen3.setFont(m_font);
	m_infoScreen3.setPosition(10.0f, 850.0f);
	m_infoScreen3.setString("PRESS ESCAPE TO RETURN BACK TO MENU");
	m_infoScreen3.setCharacterSize(34);
	m_infoScreen3.setFillColor(sf::Color::Red);


	m_shotsNum.setFont(m_font);
	m_shotsNum.setPosition(300.0f, 0.0f);
	m_shotsNum.setString("Shots Fired: " + std::to_string(m_projectile.m_shotsFired));
	m_shotsNum.setCharacterSize(34);
	m_shotsNum.setFillColor(sf::Color::Red);


	

	m_authors.setFont(m_font);
	m_authors.setPosition(10.0f, 800.0f);
	m_authors.setString("By: Adam Mcguigan C00248515 and David Jalives C00239534 ");
	m_authors.setCharacterSize(34);
	m_authors.setFillColor(sf::Color::Red);

	m_accuracyText.setFont(m_font);
	m_accuracyText.setPosition(1120.0f, 0.0f);
	m_accuracyText.setString("Accuracy: " + std::to_string(m_hitAccuracy) + "%");
	m_accuracyText.setCharacterSize(34);
	m_accuracyText.setFillColor(sf::Color::Red);


	m_targetsHitText.setFont(m_font);
	m_targetsHitText.setPosition(1020.0f, 0.0f);
	m_targetsHitText.setString("Targets hit: " + std::to_string(m_shotsHit));
	m_targetsHitText.setCharacterSize(34);
	m_targetsHitText.setFillColor(sf::Color::Red);


	m_rubyState.setFont(m_font);
	m_rubyState.setPosition(620.0f, 0.0f);
	m_rubyState.setString("Capture the Ruby !");
	m_rubyState.setCharacterSize(34);
	m_rubyState.setFillColor(sf::Color::Red);


	for (int i = 0; i < 4; i++)
	{
		MainMenuButtons[i].Init(sf::Vector2f(500, 80 + (i * 110)), m_font);

	}
	MainMenuButtons[0].text.setString("Play");
	MainMenuButtons[1].text.setString("Instructions");
	MainMenuButtons[2].text.setString("Ships");
	MainMenuButtons[3].text.setString("Exit");

	for (int i = 0; i < 3; i++)
	{
		selectShipSkinButtons[i].Init(sf::Vector2f(200, 80 + (i * 200)), m_font);

	}
	selectShipSkinButtons[0].text.setString("Select");
	selectShipSkinButtons[1].text.setString("Select");
	selectShipSkinButtons[2].text.setString("Select");


	m_timer.reset(sf::Time(sf::milliseconds(TIMER_DUR_THOR)));
}

/// <summary>
/// obstacle set up
/// </summary>
void Game::generateWalls()
{
	if (!m_spriteSheetTexture.loadFromFile("./resources/images/EnemyShip3.png"))
	{
		std::string errorMsg("Error loading texture");
		throw std::exception(errorMsg.c_str());
	}
	
	sf::IntRect wallRect(2, 129, 33, 23);
	// Create the Walls 
	for (ObstacleData const& obstacle : m_level.m_obstacles)
	{
		m_wallSprite.setTexture(m_spriteSheetTexture);
		m_wallSprite.setTextureRect(wallRect);
		m_wallSprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		m_wallSprite.setPosition(obstacle.m_position);
		m_wallSprite.setRotation(obstacle.m_rotation);
		m_wallSpritesVector.push_back(m_wallSprite);
	}
}


////////////////////////////////////////////////////////////
/// runs the whole thing
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(lag);
			lag -= MS_PER_UPDATE;
		}
		update(lag);

		render();
	}
};

////////////////////////////////////////////////////////////
/// input
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
/// user input
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		m_ship.handleKeyInput();

	}
}

////////////////////////////////////////////////////////////
/// all actions goes here as it updates the game
void Game::update(double dt)
{

	if (m_gameState ==GameState::GAME_RUNNING)// if game is still alive 
	{
		if (menuState == MenuState::MENU)
		{

			for (int i = 0; i < 4; i++)
			{
				MainMenuButtons[i].Update(m_window);
			}

			if (MainMenuButtons[0].pressed == true)
			{
				m_buttonSound.play();
				//music.pause();
				menuState = MenuState::GAMEPLAY;
				std::cout << "gameplay pressed" << std::endl;

			}
			if (MainMenuButtons[1].pressed == true)
			{
				m_buttonSound.play();
				menuState = MenuState::INSTRUCTIONS;

				std::cout << " instuctions pressed" << std::endl;
			}
			if (MainMenuButtons[2].pressed == true)
			{
				m_buttonSound.play();
				menuState = MenuState::CUSTOMIZATION;

				std::cout << " opttions" << std::endl;
			}
			if (MainMenuButtons[3].pressed == true)
			{
				m_buttonSound.play();
				std::cout << " Exit" << std::endl;
				m_window.close();
				//return 0;
			}
			m_window.clear(sf::Color::Black);
			m_window.draw(m_backgroundSprite);
			m_window.draw(m_authors);
			for (int i = 0; i < 4; i++)
			{
				m_window.draw(MainMenuButtons[i].shape);
				m_window.draw(MainMenuButtons[i].buttonSprite);
				m_window.draw(MainMenuButtons[i].text);
			}

			
			m_window.display();
		}

		if (menuState == MenuState::GAMEPLAY)
		{
			m_menuSound.stop();
			//Ship updates
			m_ship.update(dt, m_startPos);
			//Projectile updates
			m_projectile.update(dt, m_ship.getTurretPosition(), m_ship.getTurretRotation());
			m_projectile.collisionWithWalls(m_wallSpritesVector);
			// target update
			m_enemy.update(dt, m_level.m_enemy.m_position);
			m_enemy.collisionWithWalls(m_wallSpritesVector);
			//timer
			m_timer.start();
			m_timeRemainThor = m_timer.getRemainingTime().asSeconds();// / TIMER_DUR_THOR;
			//shipAi update
			if (m_aiShipHP >= 1)
			{
				m_enemyShipAI.update(m_ship, dt);
				m_enemyShipAI.collidesWithPlayer(m_ship);
				if (m_enemyShipAI.collidesWithPlayer(m_ship) == false)
				{
					m_hud.update(GameState::GAME_RUNNING);
					m_gameState = GameState::GAME_RUNNING;

				}
				if (m_enemyShipAI.collidesWithPlayer(m_ship) == true)
				{
					m_hud.update(GameState::GAME_LOSE);
					m_gameState = GameState::GAME_LOSE;
				}
			}

			//additional updates

			collisions();
			animateCarrier();
			if (m_hitYes)
			{
				animateExplosion();
			}
			updateAccuracy();
			textUpdate();
			if (m_aiShipHP <= 0 && m_rubyDelivered && m_score > 40 && m_timeRemainThor <= m_gameOverSeconds)
			{
				m_hud.update(GameState::GAME_WIN);
				m_gameState = GameState::GAME_WIN;
			}

			else if (m_timeRemainThor <= m_gameOverSeconds)
			{
				m_hud.update(GameState::GAME_LOSE);
				m_gameState = GameState::GAME_LOSE;
			}
		
		}
		
		if (menuState == MenuState::INSTRUCTIONS)
		{
			m_window.display();
			if (menuState == MenuState::INSTRUCTIONS && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				menuState = MenuState::MENU;
			}

		}

		if (menuState == MenuState::CUSTOMIZATION)
		{
			if (menuState == MenuState::CUSTOMIZATION && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				menuState = MenuState::MENU;
			}
			for (int i = 0; i < 3; i++)
			{
				selectShipSkinButtons[i].Update(m_window);
			}

			if (selectShipSkinButtons[0].pressed == true)
			{
				m_buttonSound.play();
				//music.pause();
				m_ship.whatShipSprite = shipCustom::WARSHIP;
				std::cout << "SHIP 1 SELECTED" << std::endl;

			}
			if (selectShipSkinButtons[1].pressed == true)
			{
				m_buttonSound.play();
				m_ship.whatShipSprite = shipCustom::SOYSHIP;
				std::cout << "SHIP 2 SELECTED" << std::endl;
			}
			if (selectShipSkinButtons[2].pressed == true)
			{
				m_buttonSound.play();
				m_ship.whatShipSprite = shipCustom::OLDSHIP;
				std::cout << "SHIP 3 SELECTED" << std::endl;
			}
		
			for (int i = 0; i < 3; i++)
			{
				m_window.draw(selectShipSkinButtons[i].buttonSprite);
				m_window.draw(selectShipSkinButtons[i].text);
			}
			m_window.display();
		}
	}
}

////////////////////////////////////////////////////////////
/// draws out to screen
void Game::render()
{
	if (m_gameState == GameState::GAME_RUNNING)
	{
		if (menuState == MenuState::GAMEPLAY)
		{
			m_window.clear(sf::Color(0, 0, 0, 0));
			m_window.draw(m_bgSprite); // draw background to the screen 
			m_window.draw(m_sprite); // draws m_wallSprite to the screen
			for (int i = 0; i < m_spriteVector.size(); i++)
			{
				m_window.draw(m_spriteVector.at(i));
			}
			m_window.draw(m_returnBaseSprite);
			m_ship.render(m_window);
			m_projectile.render(m_window);
			m_enemy.render(m_window);
			if (m_aiShipHP >= 1)
			{
				m_enemyShipAI.render(m_window);
			}
			m_hud.render(m_window);
			m_window.draw(m_clockText);
			m_window.draw(m_scoreText);
			m_window.draw(m_shotsNum);
			if (m_aiShipHP >= 1)
			{
				m_window.draw(m_aiShipHPText);
			}

			for (int i = 0; i < m_wallSpritesVector.size(); i++)
			{
				m_window.draw(m_wallSpritesVector.at(i));
			}
			if (rubyIsCaptured)
			{
				m_rubyState.setString("Return the ruby to a Carrier!");
				m_rubyState.setFillColor(sf::Color::Green);
			}
			if (m_rubyDelivered)
			{
				m_rubyState.setString("Kill as many targets !");
				m_rubyState.setFillColor(sf::Color::Green);
			}
			if (!rubyIsCaptured)
			{
				collectibleCoin.drawRuby(m_window);
			}
			if (m_hitAccuracy < 105 && m_hitAccuracy >= -1)
			{
				m_window.draw(m_accuracyText);
			}
			m_window.draw(m_funExpSprite);
			m_window.draw(m_rubyState);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
			
				myGrid.render(m_window);
			}
			if (m_timeRemainThor > 57)
			{
				m_ship.changeSpriteOfShip();
			}
			m_window.display();
		}
		if (menuState == MenuState::INSTRUCTIONS)
		{
			m_window.draw(m_backgroundSprite);

			m_window.draw(m_infoScreen1);
			m_window.draw(m_infoScreen2);
			m_window.draw(m_infoScreen3);
			m_window.draw(m_keyboardLayoutSprite);
		}
		if (menuState == MenuState::CUSTOMIZATION)
		{
			m_window.clear(sf::Color(0, 0, 0, 0));

			m_window.draw(m_bgSprite);
			m_window.draw(m_infoScreen3);
			m_window.draw(m_soyShipDisplaySprite);
			m_window.draw(m_oldShipDisplaySprite);
			m_window.draw(m_warShipDisplaySprite);
		}
    }

	if (m_gameState == GameState::GAME_LOSE)
	{
		m_window.clear(sf::Color(0, 0, 0, 0));
		m_gameEndSprite.setTexture(m_gameEndTexture2);
		m_gameEndSprite.setScale(1, 1.2);
		m_window.draw(m_gameEndSprite);

		m_window.draw(m_gameOverText);
		m_shotsNum.setPosition(520.0f, 650.0f);
		m_targetsHitText.setPosition(520.0f, 700.0f);
		m_accuracyText.setPosition(520.0f, 750.0f);

		m_window.draw(m_shotsNum);
		m_window.draw(m_accuracyText);
		m_window.draw(m_targetsHitText);



		m_window.display();
	}


	if (m_gameState == GameState::GAME_WIN)
	{
		m_window.clear(sf::Color(0, 0, 0, 0));
		m_window.draw(m_gameEndSprite);

		m_gameOverText.setString("GAME WIN");
		m_gameOverText.setFillColor(sf::Color::Green);
		m_window.draw(m_gameOverText);
		m_shotsNum.setPosition(520.0f, 650.0f);
		m_targetsHitText.setPosition(520.0f, 700.0f);
		m_accuracyText.setPosition(520.0f, 750.0f);
		m_window.draw(m_shotsNum);
		m_window.draw(m_accuracyText);
		m_window.draw(m_targetsHitText);

		m_window.display();

	}

}

void Game::collisions()
{

	if (m_enemy.m_targetSprite.getGlobalBounds().intersects(m_projectile.m_bulletSprite.getGlobalBounds()))
	{
		m_enemyOldPos = m_enemy.m_targetSprite.getPosition();
		std::cout << "TARGET HIT" << std::endl;
		m_enemy.m_targetSprite.setPosition(m_enemy.offScreenPos); // reset the target
		m_projectile.m_bulletSprite.setPosition(10099,109999); // reset the nbullet
		m_enemy.m_timeForEnemy = 0;
		m_enemy.m_timeForEnemy = m_enemy.m_clockToSpawnTarget.restart().asSeconds();
		m_enemy.b_enemyReady = false;
		// add remaining time 
		float nextTargetPassTime = m_enemy.m_enemyTimer.getRemainingTime().asSeconds() + m_enemy.TIMER_DUR_THOR;
		m_enemy.m_enemyTimer.restart(sf::Time(sf::seconds(nextTargetPassTime)));
		m_score = m_score + 3;
		m_shotsHit = m_shotsHit + 1;
		m_enemy.m_targetSprite.setScale(m_enemy.m_currentScale);
		m_hitYes = true;
	}

	if (m_projectile.m_bulletSprite.getGlobalBounds().intersects(m_enemyShipAI.m_AiShipBase.getGlobalBounds()))
	{
		m_aiShipHP = m_aiShipHP - 20;
		m_score = m_score + 2;
		m_shotsHit = m_shotsHit + 1;
		m_enemyOldPos = m_enemyShipAI.m_AiShipBase.getPosition();
		m_projectile.m_bulletSprite.setPosition(10099, 109999); // reset the nbullet
		m_hitYes = true;
		std::cout << m_shotsHit << std::endl;
	}
	if (m_aiShipHP <= 0)
	{
		m_enemyShipAI.m_AiShipBase.setPosition(99344, 99344);
	}

	if (collectibleCoin.spriteSheetRuby.getGlobalBounds().intersects(m_ship.m_shipBase.getGlobalBounds()))
	{
		rubyIsCaptured = true;
		changedTextureForPlayerShip = true;
		collectibleCoin.spriteSheetRuby.setPosition(93434, 34934);
	}
	//this controls so that the sprite will bne set only once and not continue setting after ruby was captured
	if (rubyIsCaptured == true && changedTextureForPlayerShip==true)
	{
		if (m_ship.whatShipSprite == shipCustom::WARSHIP)
		{
			m_ship.m_shipBase.setTexture(m_rubyShipTexture);
		}
		else if (m_ship.whatShipSprite == shipCustom::OLDSHIP)
		{
			m_ship.m_shipBase.setTexture(m_rubyShipTextureOld);
		}
		else if (m_ship.whatShipSprite == shipCustom::SOYSHIP)
		{
			m_ship.m_shipBase.setTexture(m_rubyShipTextureSoy);
		}
		changedTextureForPlayerShip = false;

	}
 //Checks if the AI ship has collided with the player ship.
	if (CollisionDetector::collisions(m_ship.m_shipBase, m_returnBaseSprite))
	{
		std::cout << "COLLIDED SHIP WITH BASE" << std::endl;
		m_ship.deflect();
		if (m_ship.whatShipSprite == shipCustom::WARSHIP)
		{
			m_ship.m_shipBase.setTexture(m_ship.shipTexture);
		}
		if (m_ship.whatShipSprite == shipCustom::OLDSHIP)
		{
			m_ship.m_shipBase.setTexture(m_ship.shipTextureOld);
		}
		if (m_ship.whatShipSprite == shipCustom::SOYSHIP)
		{
			m_ship.m_shipBase.setTexture(m_ship.shipTextureSoy);
		}
		// add othger later
		if (rubyIsCaptured == true)
		{
			m_rubyDelivered = true;
		}
	}
}

void Game::textUpdate()
{
	m_clockText.setString("Time: " + std::to_string(m_timeRemainThor));
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_shotsNum.setString("ShotsFired: " + std::to_string(m_projectile.m_shotsFired));;
	m_accuracyText.setString("Accuracy: " + std::to_string(m_hitAccuracy) + "%");
	m_targetsHitText.setString("Targets hit:" + std::to_string(m_shotsHit));
	m_aiShipHPText.setPosition(m_enemyShipAI.m_AiShipBase.getPosition().x-20, m_enemyShipAI.m_AiShipBase.getPosition().y+40);
	m_aiShipHPText.setString("HP: " + std::to_string(m_aiShipHP));

	//update of the background sound set up here as fcuntion setSound works only once 
	if (menuState == MenuState::GAMEPLAY && m_timeRemainThor >59)
	{
		m_gameplaySound = true;
	}
	if (m_gameplaySound)
	{
		m_backgroundSound.play();
		m_gameplaySound = false;
	}

}

void Game::updateAccuracy()
{
	if (m_projectile.m_shotsFired > 0)
	{
		m_hitAccuracy = static_cast <float>(m_shotsHit) / m_projectile.m_shotsFired * 100.0f;
	}
}

void Game::setSound()
{
	if (!m_backgroundBuffer.loadFromFile("./resources/audio/tankBackground.wav")) // EXPLOSION SOUND./resources/
	{
		std::cout << "problem loading gameplay sound " << std::endl;
	}
	m_backgroundSound.setBuffer(m_backgroundBuffer);
	m_backgroundSound.setVolume(10.0f);

	if (!m_buttonBuffer.loadFromFile("./resources/audio/buttonPress.wav")) // EXPLOSION SOUND./resources/
	{
		std::cout << "problem loading button press sound" << std::endl;
	}
	m_buttonSound.setBuffer(m_buttonBuffer);
	m_buttonSound.setVolume(10.0f);

	if (!m_menuBuffer.loadFromFile("./resources/audio/menu.ogg")) // EXPLOSION SOUND./resources/
	{
		std::cout << "problem loading menu sound" << std::endl;
	}
	m_menuSound.setBuffer(m_menuBuffer);
	m_menuSound.setVolume(30.0f);


}

void Game::animateExplosion()
{
	m_funExpSprite.setTexture(m_funExpTexture);
	m_funExpSprite.setOrigin(sf::Vector2f{ 34.0f, 34.0f });
	m_funExpSprite.setScale(sf::Vector2f{ 2.0f, 2.0f });

	m_funExpSprite.setPosition(sf::Vector2f{ m_enemyOldPos });

	m_fameCounterExp += m_frameIncrementExp;
	m_expFrameV = static_cast<int>(m_fameCounterExp) % 6;
	m_expFrameH = static_cast<int>(m_fameCounterExp) / 6;

	m_funExpSprite.setTextureRect(sf::IntRect{ -m_expFrameV,m_expFrameH * 66, 60 , 66 });

	//std::cout << "BOOOOOOOOOOM" << std::endl;
	//m_hitYes = false;
	iLetExplosionBoom = iLetExplosionBoom + 0.051;
	//std::cout << iLetExplosionBoom << std::endl;
	if (iLetExplosionBoom >= 10)
	{
		m_expFrameV = 0; // explosuinbs frame
		m_expFrameH = 0; // explosuinbs frame
		m_fameCounterExp = 0;
		m_hitYes = false;
		iLetExplosionBoom = 0.0f;
	}
}

void Game::animateCarrier()
{
	m_fameCounterCarrier += m_frameIncrementCarrier;
	m_carrierFrameV = static_cast<int>(m_fameCounterCarrier) % 4;
	m_carrierFrameH = static_cast<int>(m_fameCounterCarrier) / 1;

	m_returnBaseSprite.setTextureRect(sf::IntRect{ m_carrierFrameV * 79 , 0, 79 , 233 });
}

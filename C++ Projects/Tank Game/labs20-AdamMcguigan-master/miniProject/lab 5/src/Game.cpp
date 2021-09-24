#include "Game.h"
#include <iostream>
#include <Thor/Vectors.hpp>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

bullet myBullet;


void Game::loadContent()
{
	//SpriteSheet
	if (!m_texture.loadFromFile("./resources/images/SpriteSheet3.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	//Background Image
	if (!m_bgTexture.loadFromFile("./resources/images/Background.png"))
	{
		std::string s("Error loading the texture");
		throw std::exception(s.c_str());
	}
	m_bgSprite.setTexture(m_bgTexture);

	//Timing Bar
	if (!m_timerTexture.loadFromFile("./resources/images/timerbarFlag.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	//Target Sprite
	if (!m_targetTexture.loadFromFile("./resources/images/target2.png"))
	{
		std::cout << "Error... Loading target texture" << std::endl;
	}

	//Fuel Can Sprite
	if (!m_fuelCanTexture.loadFromFile("./resources/images/gas can.png"))
	{
		std::cout << "Error loading the gas can texture " << std::endl;
	}

	if (!m_collectableTexture.loadFromFile("./resources/images/pixil-frame-0.png"))
	{
		std::cout << "Error loading the collectable texture" << std::endl;
	}

	if (!m_goalTexture.loadFromFile("./resources/images/goal.png"))
	{
		std::cout << "Error loading the goal texture" << std::endl;
	}

	//Tank Firing
	if (!m_soundBuffer.loadFromFile("./resources/audio/TankFire.wav"))
	{
		std::string s("Error loading audio");
		throw std::exception(s.c_str());
	}

	//Tank Driving sound
	if (!m_tankSoundBuffer.loadFromFile("./resources/audio/tankDrive.wav"))
	{
		std::string s("Error loading the tank engine noise ");
		throw std::exception(s.c_str());
	}

	if (!m_firingBuffer.loadFromFile("./resources/audio/TankFire.wav"))
	{
		std::string s("Error loading audio");
		throw std::exception(s.c_str());
	}

	//HUD
	if (!m_hudTexture.loadFromFile("./resources/images/CamoHUD.png"))
	{
		std::string s("Error loading hud Texture");
		throw std::exception(s.c_str());
	}
	
	//font
	if (!m_fontSuperBoom.loadFromFile("./resources/fonts/SUPER BOOM.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}

	//Setup for the main menu
	if (!m_backgroundForInstructionsScreen.loadFromFile("./resources/images/menuBackground.png"))
	{
		std::cout << "Error with loading the menu background ";
	}

	/*if (!m_buttonTexture.loadFromFile("./resources/images/button.png"))
	{
		std::cout << "Error with loading the buttons sprite ";
	}*/

	if (!optionsTexture.loadFromFile("./resources/images/Options Keyboard.jpg"))
	{
		std::cout << "Error with loading the options sprite ";
	}

	if (!m_font.loadFromFile("./resources/fonts/SUPER BOOM.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}


}

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
	, m_tank(m_texture, m_sprites)
	, m_aiTank(m_texture, m_sprites)
	, m_hud(m_font)
	
{

	loadContent();
	srand(time(0));

	gameMode = 1;
	m_window.setKeyRepeatEnabled(false);

	myBullet.bulletConst();

	m_window.setVerticalSyncEnabled(true);

	int currentLevel = 1;

	isTargetOneActive = true;
	isTargetTwoActive = false;
	isTargetThreeActive = false;
	isTargetFourActive = false;

	//will Generate an exception if level loading fails ***************
	try
	{
		LevelLoader::load(currentLevel, m_level);
	}
	catch (std::exception& e)
	{
		std::cout << "Level loading failure " << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	//This is used to set the keyboard image in options
	optionsSprite.setTexture(optionsTexture);
	optionsSprite.setOrigin(-180,150);

	m_InstructionsBackgroundSprite.setTexture(m_backgroundForInstructionsScreen);
	
	//text setup for the instructions screen
	m_message.setFont(m_fontSuperBoom);  // set the font for the text
	m_message.setCharacterSize(60);
	m_message.setFillColor(sf::Color::White);
	m_message.setOutlineColor(sf::Color::Black);
	m_message.setOutlineThickness(4.0f);
	m_message.setPosition(600.0f, 450.0f);

	m_mainMenu.initialise(m_fontSuperBoom);

	//text setup for the instructions screen
	m_messageInstructionsScreen.setFont(m_fontSuperBoom);  // set the font for the text
	m_messageInstructionsScreen.setCharacterSize(20);
	m_messageInstructionsScreen.setFillColor(sf::Color::White);
	m_messageInstructionsScreen.setOutlineColor(sf::Color::Black);
	m_messageInstructionsScreen.setOutlineThickness(2.0f);
	m_messageInstructionsScreen.setPosition(5.0f, 50.0f);

	
	m_youWinText.setString("YOU WIN");
	m_youWinText.setFont(m_fontSuperBoom);
	m_youWinText.setFillColor(sf::Color::White);
	m_youWinText.setOutlineColor(sf::Color::Black);
	m_youWinText.setPosition(680, 450);


	//Text setup for the timer
	m_timeText.setString("Time:");
	m_timeText.setFont(m_fontSuperBoom);
	m_timeText.setFillColor(sf::Color::White);
	m_timeText.setPosition(0, 13);

	//setup for the end game text
	m_endGameText.setString("Accuracy: ");
	m_endGameText.setFont(m_fontSuperBoom);
	m_endGameText.setFillColor(sf::Color::White);
	m_endGameText.setPosition(0, 15);

	//getting the target timer
	m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);

	//setup for the HUD
	m_hudSprite.setTexture(m_hudTexture);
	m_hudSprite.setPosition(0, 0);
	//m_hudSprite.scale(0.5, 0.5);

	//setup for the audio files
	sound.setBuffer(m_soundBuffer);
	m_projectileAudio = true;
	tankSound.setBuffer(m_tankSoundBuffer);
	m_firingSound.setBuffer(m_firingBuffer);



	//setup for the score text on the hud
	m_scoreText.setString("Score: ");
	m_scoreText.setFont(m_fontSuperBoom);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(1250, 13);
	
	//Setup for the clock on the HUD
	m_clockSpriteRectangle.setSize(sf::Vector2f(CLOCK_BAR_WIDTH, 35));
	m_clockSpriteRectangle.setPosition(75, 15);
	m_clockSpriteRectangle.setTexture(&m_timerTexture);
	m_gameTime.reset(sf::Time(sf::milliseconds(TIMER_DURATION)));
	//m_targetTimer.reset(sf::Time(sf::milliseconds(TARGET_TIMER_DURATION)));

	// Extract the wall image from the spritesheet.
	sf::Sprite sprite;
	sf::IntRect wallRect(2, 129, 33, 23);
	sprite.setTexture(m_spriteSheetTexture);
	sprite.setTextureRect(wallRect);

	//function calls 
	m_gameTime.start(); //This will start the game timer for the player
	m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);
	generateWalls(); 
	generateTargets();

	//makes the score random between 100 + 600
	randomScore = rand() % maxScore + minScore;
	
	//Warning Sprite setup
	warningSprite.setTexture(warningTexture);
	warningSprite.setScale(0.5, 0.5);
	warningSprite.setPosition(1300, 800);

	//Gas can setup
	m_fuelCanSprite.setTexture(m_fuelCanTexture);
	m_fuelCanSprite.setScale(0.1f, 0.1f);
	m_fuelCanSprite.setPosition(700, 400);

	//Collectable setup
	m_collectable.setTexture(m_collectableTexture);
	m_collectable.setScale(0.1f, 0.1f);
	m_collectable.setPosition(1300, 100);

	//goal Setup
	m_goalSprite.setTexture(m_goalTexture);
	m_goalSprite.setScale(0.1f, 0.1f);
	m_goalSprite.setPosition(720, 840);
	
	//Calling the initialise function for ai tank
	m_aiTank.init(m_level.m_aiTank.m_position);

	// Point at TankAI::applyDamage()...this function expects 1 argument (damage amount), but that argument
	//  will be supplied later when we call the function inside Projectile::udpate()
	// So we use what is called a placeholder argument and this will be substituted later with the damage amount
	using std::placeholders::_1;

	// The parameters of bind are the function to be called, followed by the name of the target instance, 
	//  followed by the placeholder argument.
	m_funcApplyDamage = std::bind(&TankAi::applyDamage, &m_aiTank, _1);

	setupObjectiveText();

}


////////////////////////////////////////////////////////////
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
}

/// /////////////////////////////////////////////

void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);
	// Create the Walls 
	for (ObstacleData const& obstacle : m_level.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_texture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_sprites.push_back(sprite);
	}
}


/// ////////////////////////////////////////////////////////
/// this is used to generate Targets in the level
void Game::generateTargets()
{
	for (TargetData const& targets : m_level.m_targets)
	{
		sf::Sprite spritesForTargets;
		spritesForTargets.setTexture(m_targetTexture);
		spritesForTargets.setPosition(targets.m_targetPos);
		m_targetSprites.push_back(spritesForTargets);
	}
}

// //////////////////////////////////////////////
//Function is called at the end of the game to calc accuracy
void Game::calculateAccuracy()
{
	if (shotsFired > 0)
	{
		shotsFired -= 3;
		accuracy = (targetsHit / shotsFired) * 100;
	}

	else if (shotsFired == 0)
	{
		accuracy = 0;
	}
}


/// //////////////////////////////////////////////////////////
/// checks if the projectile hits the wall
bool Game::checkProjectileToWallCollision()
{
	for (sf::Sprite const& sprite : m_sprites)
	{
		if (CollisionDetector::collision(myBullet.m_bulletSprite, sprite))
		{
			if (myBullet.fired == true)
			{
				myBullet.fired = false;
				myBullet.alive = false;
				myBullet.allowToFire = true;
				std::cout << "The collision with wall is working " << std::endl;
			}
		}
	}

	return false;
}

// //////////////////////////////////////////////////////////
//Checks if the projectile hits the target
bool Game::checkProjectileToTargetCollision()
{
	for (sf::Sprite const& targetSprite : m_targetSprites)
	{
		if (isTargetOneActive == true)
		{
			if (CollisionDetector::collision(myBullet.m_bulletSprite, m_targetSprites.at(0)))
			{
				myBullet.fired = false;
				myBullet.alive = false;
				myBullet.allowToFire = true;
				score += randomScore;
				std::cout << "The collision with Target is working " << std::endl;
				isTargetOneActive = false;
				isTargetTwoActive = true;
				m_targetTimer = m_targetTimer + sf::milliseconds(m_level.m_tank.m_duration);
				randomRespawnTargets();
				//sets the target to red and sets it to an offscreen position
				m_targetSprites.at(0).setColor(sf::Color::Red);
				m_targetSprites.at(0).setPosition(offScreenPositionX, offScreenPositionY);
				myBullet.m_bulletSprite.setPosition(5500, 5500);
				targetsHit+=1;
				std::cout << "Targets Hit: " << targetsHit << std::endl;

			}
		}

		if (isTargetTwoActive == true)
		{
			if (CollisionDetector::collision(myBullet.m_bulletSprite, m_targetSprites.at(1)))
			{
				//setting the bullet pre reqs so that it can reload to fire
				myBullet.fired = false;
				myBullet.alive = false;
				myBullet.allowToFire = true;
				score += randomScore;

				std::cout << "The collision with Target is working " << std::endl;
				isTargetTwoActive = false;
				isTargetThreeActive = true;
				//resetting the timer and calls the random respawn function 
				m_targetTimer = m_targetTimer + sf::milliseconds(m_level.m_tank.m_duration);
				randomRespawnTargets();
				
				m_targetSprites.at(1).setColor(sf::Color::Red);
				m_targetSprites.at(1).setPosition(offScreenPositionX, offScreenPositionY);
				myBullet.m_bulletSprite.setPosition(5500, 5500);
				targetsHit+=1;
				std::cout << "Targets Hit: " << targetsHit << std::endl;

			}
		}

		if (isTargetThreeActive == true)
		{
			if (CollisionDetector::collision(myBullet.m_bulletSprite, m_targetSprites.at(2)))
			{
				myBullet.fired = false;
				myBullet.alive = false;
				myBullet.allowToFire = true;
				score += randomScore;
				std::cout << "The collision with Target is working " << std::endl;
				isTargetThreeActive = false;
				isTargetFourActive = true;
				//resetting the timer and calls the random respawn function 
				m_targetTimer = m_targetTimer + sf::milliseconds(m_level.m_tank.m_duration);
				randomRespawnTargets();
				//changes the color and sets it to an offscreen position
				m_targetSprites.at(2).setColor(sf::Color::Red);
				m_targetSprites.at(2).setPosition(offScreenPositionX, offScreenPositionY);
				myBullet.m_bulletSprite.setPosition(5500, 5500);
				targetsHit+=1;
				std::cout << "Targets Hit: " << targetsHit << std::endl;

			}
		}

		if (isTargetFourActive == true)
		{
			if (CollisionDetector::collision(myBullet.m_bulletSprite, m_targetSprites.at(3)))
			{
				//score is calculated and sets the color to red and offscreen position is set
				score += randomScore;
				m_targetSprites.at(3).setColor(sf::Color::Red);
				m_targetSprites.at(3).setPosition(offScreenPositionX, offScreenPositionY);
				myBullet.m_bulletSprite.setPosition(5500, 5500);
				targetsHit+=1;
				std::cout << "Targets Hit: " << targetsHit << std::endl;
				m_targetTimer = m_targetTimer + sf::milliseconds(m_level.m_tank.m_duration);
			}

		}
	}

return false;
}



////////////////////////////////////////////////////////////
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

// //////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}
	}

	//Left and Right key presses will play sounds for the tank movement 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		tankSound.play();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		tankSound.play();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_firingSound.play();
	}

	//When Q is pressed it will allow the player to return to the menu if the want
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		gameMode = MENU;
		
	}

}


// //////////////////////////////////////////////////////////
void Game::randomRespawnTargets()
{
	//local variables 
	float positionX = rand() % 700 + 100;
	float positionY = rand() % 700 + 50;
	sf::FloatRect m_targetRect;
	m_targetRect = m_targetSprites.at(0).getGlobalBounds();


	//checks the random pos against the wall sprites location and if the collide they will get an offset of 100
	for (int i = 0; i < m_sprites.size(); i++)
	{
		if (m_sprites.at(i).getGlobalBounds().intersects(m_targetRect))
		{
			positionX = positionX + 100;
			positionY = positionY + 100;
		}
	}

	//setting the position and color to each of the targets
	m_targetSprites.at(0).setColor(sf::Color::White);
	m_targetSprites.at(1).setColor(sf::Color::White);
	m_targetSprites.at(2).setColor(sf::Color::White);
	m_targetSprites.at(3).setColor(sf::Color::White);
	m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);
	m_targetSprites.at(0).setPosition(positionX, positionY);
	m_targetSprites.at(1).setPosition(positionX, positionY);
	m_targetSprites.at(2).setPosition(positionX, positionY);
	m_targetSprites.at(3).setPosition(positionX, positionY);

	//will update the location of the warning symbol if the timer is at a certain time 
	for (int i = -1; i < m_targetSprites.size(); i++)
	{
		warningSprite.setPosition(m_targetSprites.at(i).getPosition());

	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{

	//Game mode set to menu
	if (gameMode == MENU)
	{
		m_mainMenu.update(m_window, gameMode);
		m_gameTime.reset(sf::Time(sf::milliseconds(TIMER_DURATION)));
		m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);
	
		score = 0;
	}

	//Game mode set to instructions screen
	else if (gameMode == INSTRUCTIONS)
	{
		gameInstructions();
	}

	//Game mode set to gameplay
	else if (/*gameMode == GAME_PLAY ||*/ m_gameState == GameState::GAME_RUNNING)
	{
		//Gamer and target timer set + function calls
		m_gameTime.start();
		m_targetTimer = m_targetTimer - sf::milliseconds(10);
		m_scoreText.setString("Score: " + std::to_string(score));
		m_tank.update(dt, m_funcApplyDamage, m_aiTank.getTankBase(), m_level.m_tank.m_position);
		m_aiTank.update(m_tank, dt);
		m_aiTank.collidesWithPlayer(m_tank);

		// (m_aiTank.isLeft == true)
		//{
			m_aiTank.updateVisionCone(m_tank);

		//}

		checkProjectileToWallCollision();
		checkProjectileToTargetCollision();
		m_hud.update(m_gameState);


		//checks if the bullet is allowed to fire (pre req of the bullet)
		if (myBullet.allowToFire == true)
		{
			//if space is fired plays sound and sets the bools 
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				myBullet.alive = true;
				myBullet.fired = true;
				myBullet.allowToFire = false;
				sound.play();
				shotsFired += 1;
				std::cout << "Shots fired : " << shotsFired << std::endl;

			}*/

		}

		if (m_aiTank.health <= 0)
		{
			m_gameState = GameState::GAME_WIN;
			std::cout << "You have Won" << std::endl;
		}

		/// This is an offscreen check for the projectile
		/// wont allow the tank to fire again until the projectile is offscreen or 'destroyed'
		if (myBullet.m_bulletSprite.getPosition().x < 0 || myBullet.m_bulletSprite.getPosition().x > ScreenSize::s_width 
			|| myBullet.m_bulletSprite.getPosition().y < 0 || myBullet.m_bulletSprite.getPosition().y > ScreenSize::s_height)
		{
			myBullet.allowToFire = true;
		}

		//checks for if the bullet is alive which will get the location of the tank position and turret
		if (myBullet.alive == true)
		{
			double rotation = m_tank.getTurretRotation();
			sf::Vector2f posTurret = m_tank.getTurretPos();

			m_startPoint = sf::Vector2f(posTurret.x + 1 * std::cos(rotation * MathUtility::DEG_TO_RAD),
				posTurret.y + 1 * std::sin(rotation * MathUtility::DEG_TO_RAD)
			);

			myBullet.m_bulletSprite.setPosition(m_startPoint);
			m_startPoint = thor::unitVector(m_startPoint - m_tank.getTurretPos());
			myBullet.alive = false;
		}

		//Makes the bullet move and sets the speed
		myBullet.m_bulletSprite.move(m_startPoint.x * myBullet.PROJECTILE_SPEED * (dt / 1000),
			m_startPoint.y * myBullet.PROJECTILE_SPEED * (dt / 1000));

	//If the game is running, will get the time and reduce the timer 
	 if (m_gameTime.isRunning())
		{
			float timerRemainPercent = m_gameTime.getRemainingTime().asMilliseconds() / TIMER_DURATION;
			m_clockSpriteRectangle.setScale(timerRemainPercent, 1);
			m_clockSpriteRectangle.setTextureRect(
				sf::IntRect(0, 0, m_timerTexture.getSize().x * timerRemainPercent,
					m_timerTexture.getSize().y));
		}

	 //Allows the target to respawn randomly if the target timer is less than 0 and hasnt been shot
		if (isTargetOneActive == true)
		{
			if (m_targetTimer < sf::milliseconds(0))
			{
				randomRespawnTargets();
			}
		}
		//Allows the target to respawn randomly if the target timer is less than 0 and hasnt been shot
		if (isTargetTwoActive == true)
		{
			if (m_targetTimer < sf::milliseconds(0))
			{
				randomRespawnTargets();
			}
		}

		//Allows the target to respawn randomly if the target timer is less than 0 and hasnt been shot
		if (isTargetThreeActive == true)
		{
			if (m_targetTimer < sf::milliseconds(0))
			{
				randomRespawnTargets();
			}
		}

		//Allows the target to respawn randomly if the target timer is less than 0 and hasnt been shot
		if (isTargetFourActive == true)
		{
			if (m_targetTimer < sf::milliseconds(0))
			{
				randomRespawnTargets();
			}
		}
		
	}

	//Setting up collision with fuel can 
	if (CollisionDetector::collision(m_tank.getBaseSprite(), m_fuelCanSprite))
	{
		m_fuelCanSprite.setPosition(5000, 5000);
		m_tank.fuelLeft += 250;
	}

	if (CollisionDetector::collision(m_tank.getBaseSprite(), m_collectable))
	{
		m_collectable.setPosition(m_tank.getPosition());
	}
	
	if (m_tank.fuelLeft <= 0)
	{
		m_gameState = GameState::GAME_LOSE;
	}

	if (m_aiTank.collidesWithPlayer(m_tank) == true)
	{
		m_gameState = GameState::GAME_LOSE;
	}

	if (CollisionDetector::collision(m_collectable, m_goalSprite))
	{
		m_gameState = GameState::GAME_WIN;
	}

	switch (m_gameState)
	{
	case GameState::GAME_RUNNING:
		gameMode = GAME_PLAY;
		//m_tank.update(dt, m_funcApplyDamage, m_aiTank.getTankBase(), m_level.m_tank.m_position);
		//m_aiTank.update(m_tank, dt);
		break;

	case GameState::GAME_WIN:
		//m_window.clear(sf::Color(0, 0, 0, 0));
		//m_window.draw(m_youWinText);
		break;

	case GameState::GAME_LOSE:
		m_tank.resetPos(m_aiTank.getTankBase().getPosition().x);
		//m_aiTank.resetPosition();
		m_gameTime.reset(sf::Time(sf::milliseconds(TIMER_DURATION)));
		m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);
		score = 0;
		m_tank.fuelLeft = 600;
		//m_aiTank.resetPosition();
		break;


	default:
		std::cout << "Error occured" << std::endl;
		break;
	}
}

// //////////////////////////////////////////////////////////
void Game::gameInstructions()
{
	m_messageInstructionsScreen.setString("Press the 'Q' to go back to the main menu ");
}

////////////////////////////////////////////////////////////
void Game::setupObjectiveText()
{
	objectiveText.setString("Objective: Bring the golden coin to the Flag");
	objectiveText.setFont(m_fontSuperBoom);
	objectiveText.setCharacterSize(30);
	objectiveText.setFillColor(sf::Color::Black);
	objectiveText.setOutlineColor(sf::Color::Black);
	objectiveText.setPosition(330, 30);
}


////////////////////////////////////////////////////////////
void Game::render()
{
	//Clears the window
	m_window.clear(sf::Color(0, 0, 0, 0));

	//Draws the main menu
	if (gameMode == MENU)
	{
		m_mainMenu.draw(m_window);
	}

	//draws the instructions / options screen if that screen is picked
	else if (gameMode == INSTRUCTIONS)
	{
		m_window.draw(m_InstructionsBackgroundSprite);
		m_window.draw(optionsSprite);
		m_window.draw(m_messageInstructionsScreen);

	}

	//draws everything thats required for the gameplay 
	else if (gameMode == GAME_PLAY)
	{
		m_window.draw(m_message);
		m_window.draw(m_bgSprite);

		//If the bullet has been fired the sprite will draw
		if (myBullet.fired == true)
		{
			m_window.draw(myBullet.m_bulletSprite);
		}

		//draws the HUD and tank
		m_tank.render(m_window);
		m_aiTank.render(m_window);
		m_window.draw(m_fuelCanSprite);
		m_window.draw(m_goalSprite);
		m_window.draw(m_collectable);
		m_window.draw(objectiveText);
		m_window.draw(m_hudSprite);
		m_window.draw(m_timeText);
		m_window.draw(m_clockSpriteRectangle);
		m_hud.render(m_window);
		

		//Draws the wall sprites on screen
		for (sf::Sprite m_wall : m_sprites)
		{
			m_window.draw(m_wall);
		}

		//Draws the target sprites
		for (sf::Sprite m_targets : m_targetSprites)
		{

			if (isTargetOneActive == true)
			{
				//gets the position of the target and will draw the warning sprite if the timer is less or equal to 5 seconds
				if (m_targetTimer <= sf::milliseconds(5000))
				{
					float offset = m_targetSprites.at(0).getPosition().y + (0, 25);
					m_window.draw(warningSprite);
				}
				m_window.draw(m_targetSprites.at(0));
			}

			if (isTargetTwoActive == true)
			{
				//gets the position of the target and will draw the warning sprite if the timer is less or equal to 5 seconds
				if (m_targetTimer <= sf::milliseconds(5000))
				{
					float offset = m_targetSprites.at(1).getPosition().y + (0, 25);
					m_window.draw(warningSprite);
				}

				m_window.draw(m_targetSprites.at(1));
			}

			if (isTargetThreeActive == true)
			{
				//gets the position of the target and will draw the warning sprite if the timer is less or equal to 5 seconds
				if (m_targetTimer <= sf::milliseconds(5000))
				{
					float offset = m_targetSprites.at(2).getPosition().y + (0, 25);
					m_window.draw(warningSprite);
				}

				m_window.draw(m_targetSprites.at(2));
			}

			if (isTargetFourActive == true)
			{
				//gets the position of the target and will draw the warning sprite if the timer is less or equal to 5 seconds
				if (m_targetTimer <= sf::milliseconds(5000))
				{
					float offset = m_targetSprites.at(3).getPosition().y + (0, 25);
					m_window.draw(warningSprite);
				}

				m_window.draw(m_targetSprites.at(3));
			}
		}
		

		m_window.draw(m_scoreText);
		

	}

	//If the game timer has expired the end game screen will draw
	if /*(m_gameTime.isExpired() || targetsHit == 4*/ (m_gameState == GameState::GAME_LOSE)
	{
		//m_gameState = GameState::GAME_LOSE;
		m_window.clear(sf::Color(0, 0, 0, 0));
		m_window.draw(m_InstructionsBackgroundSprite);
		m_message.setString("GAME OVER ");
	
		//This calculates the accuracy for the end game screen
		if (shotsFired > 0)
		{
		
			accuracy = (targetsHit / shotsFired) * 100;
		}

		else if (shotsFired == 0)
		{
			accuracy = 0;
		}

		//Setting the strings for the end game screen
		m_endGameText.setString("Targets Hit: " + std::to_string(targetsHit) 
			+ "\n  \n " + "Score: " + std::to_string(score) 
			+ "\n \n " + "Shots Fired: " + std::to_string(shotsFired) 
			+ "\n \n " + "Accuracy: " + std::to_string(static_cast<int>(accuracy)) + " %");

		m_window.draw(m_endGameText);
		m_window.draw(m_message);
	}

	if (m_gameState == GameState::GAME_WIN)
	{
		m_window.clear(sf::Color(0, 0, 0, 0));
		m_window.draw(m_InstructionsBackgroundSprite);
		m_window.draw(m_youWinText);
	}

	
	m_window.display();
}


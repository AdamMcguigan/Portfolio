#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Tank.h"
#include "LevelLoader.h"
#include "Projectile.h"
#include <MenuScreen.h>
#include "Globals.h"
#pragma comment(lib,"thor-d.lib") 
#pragma comment(lib,"thor.lib") 
#include "Thor/Time.hpp"
#include <SFML/Audio.hpp>
#include <TankAI.h>
#include "GameState.h"
#include "HUD.h"

/// <summary>
/// @author Adam Mcguigan
/// @date September 2020
/// @version 1.0
/// 
/// </summary>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML. 
/// Example usage:
///		Game game;
///		game.run();
/// </summary>

class Game
{
public:
	LevelData m_level;
	Tank m_tank;
	TankAi m_aiTank;
	MenuScreen m_mainMenu;
	


	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();


	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>

	GameState m_gameState{ GameState::GAME_RUNNING };
	


	//Functions Used
	void run(); 
	void generateWalls(); //Spawns in the wall Sprites from the YAML file
	void generateTargets(); //Spawns in the targets from the YAML file 
	bool checkProjectileToWallCollision(); //Wall and bullet collsion function
	bool checkProjectileToTargetCollision(); //Target and bullet collsion function
	void calculateAccuracy(); //Ask help with this as the shot count gets doubled up on
	void randomRespawnTargets(); //respawns the targets randomly
	void gameInstructions(); //function that sets up for the instructions screen, loads fonts and calcs the mouse clicks
	void loadContent(); //loads all the fonts and textures for the game

	//Variable Bool
	bool isTargetOneActive;
	bool isTargetTwoActive;
	bool isTargetThreeActive;
	bool isTargetFourActive;
	bool m_projectileAudio;

	//Variable Int
	int targetsHit = 0; //used for accuracy
	int gameMode;  // to represent the different modes in the game, example game instruction mode and game play mode
	float shotsFired = 0; //used for accuracy
	float accuracy = 100; //accuracy 
	static constexpr float TARGET_TIMER_DURATION = 10000.0f; //Timer Duration
	static const int CLOCK_BAR_WIDTH{ 210 }; 
	int minScore = 100; //Used for random score
	int maxScore = 600; ////Used for random score
	int score = 0; //score
	int randomScore = 0; //rand() % maxScore + minScore;
	float offScreenPositionX = 5000.0f; //offscreen position used once the targets have been hit
	float offScreenPositionY = 5000.0f; //offscreen position used once the targets have been hit
	static constexpr float TIMER_DURATION = 60000.0f; //game Timer

	std::function<void(int)> m_funcApplyDamage;

	void setupObjectiveText();
	sf::Text objectiveText;

protected:
	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event&);

	// main window and clocks
	thor::Timer m_gameTime;
	sf::Clock m_targetClock;
	sf::Time m_targetTimer;
	sf::Texture m_timerTexture; //Texture used for the game clock
	sf::Texture m_buttonTexture;
	//Warning Symbol during gameplay
	sf::Texture warningTexture;
	sf::Sprite warningSprite;
	//Instructions screen
	sf::Texture m_backgroundForInstructionsScreen;
	sf::Sprite m_InstructionsBackgroundSprite;
	sf::Texture optionsTexture;
	sf::Sprite optionsSprite;
	//Text for menus
	sf::Text m_message; 	//  message string for instructions
	sf::Text m_messageInstructionsScreen;
	sf::Vector2f offsetX = { 60.0 , 0.0 };
	sf::Vector2f m_startPoint;
	//Tank Sounds
	sf::SoundBuffer m_soundBuffer;
	sf::Sound sound;
	sf::SoundBuffer m_tankSoundBuffer;
	sf::Sound tankSound;
	sf::SoundBuffer m_firingBuffer;
	sf::Sound m_firingSound;
	sf::RectangleShape m_clockSpriteRectangle;
	sf::RenderWindow m_window;
	//Score
	std::string m_scoreString;
	sf::Text m_scoreText;
	//EndGame Screen
	std::string m_endGameString;
	sf::Text m_endGameText;
	//Used for the background
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;
	//Used for the timer or anything else needing font
	sf::Font m_fontSuperBoom;
	sf::Text m_timeText;
	//Used for the Hud
	sf::Sprite m_hudSprite;
	sf::Texture m_hudTexture;
	sf::Texture m_targetTexture;
	sf::Font m_font;
	//vectors for the target
	std::vector<sf::Sprite> m_targetSprites; //use pop back to delete the last element
	std::vector<sf::Sprite> m_sprites;
	// At texture for the sprite sheet 
	sf::Texture m_spriteSheetTexture;
	sf::Texture m_texture;
	//Texture and sprites used for fuel 
	sf::Sprite m_fuelCanSprite;
	sf::Texture m_fuelCanTexture;
	//texture and sprites used for the collectable
	sf::Sprite m_collectable;
	sf::Texture m_collectableTexture;
	//texture and sprites used for the goal
	sf::Sprite m_goalSprite;
	sf::Texture m_goalTexture;

	std::string m_youWin;
	sf::Text m_youWinText;

	

	HUD m_hud;
};

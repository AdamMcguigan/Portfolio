#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "LevelLoader.h"
#include "Ship.h"
#include "Projectile.h"
#include "EnemyShipAI.h"
#include "Enemy.h"
#include "GameState.h"
#include "MenuButton.h"
#include "HUD.h"
#include "Collectible.h"
#include "Grid.h"
#include "Cell.h"

#include <SFML/Audio.hpp>

/// <summary>
/// @author David Jalisevs + Adam Mcguigan
/// @date April 2021
/// @version 1.0
/// 
/// </summary>


class Game
{
public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();
	// runs the program
	void run();

protected:
	// an instance of the player ship
	Ship m_ship;
	//instance of the projectile
	Projectile m_projectile;
	// an instance for the target 
	Enemy m_enemy;
	// An instance representing the AI controlled ship.
	EnemyShipAI m_enemyShipAI;
	// The initial game state set to GAME_RUNNING
	GameState m_gameState{ GameState::GAME_RUNNING };
	MenuState menuState = MenuState::MENU;

	MenuButton MainMenuButtons[4];
	MenuButton selectShipSkinButtons[3];


	Collectible collectibleCoin;
	//shipCustom whatShipSprite;
	Grid myGrid;
	

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

	/// <summary>
	/// loads the content for the gmaee
	/// </summary>
	void loadContent();

	/// <summary>
	/// collisions between the projectile and the targer
	/// </summary>
	void collisions();
	
	/// <summary>
	/// any text update on-screen
	/// </summary>
	void textUpdate();

	/// <summary>
	/// update accuracy
	/// </summary>
	void updateAccuracy();
	/// <summary>
	/// set sound
	void setSound();
	/// </summary>
	/// <summary>
	/// animates explosion
	void animateExplosion();
	/// </summary>
/// <summary>
/// animates explosion
	void animateCarrier();
/// @brief Creates the wall sprites and loads them into a vector.
/// Note that sf::Sprite is considered a light weight class, so 
///  storing copies (instead of pointers to sf::Sprite) in std::vector is acceptable.
/// </summary>
 	void spriteSetup();

	void backgroundSetup();
	/// <summary>
	/// generates walls
	/// </summary>
	void generateWalls();

	void checkCell();


	sf::Sprite m_sprite; // sptrite 
	sf::Sprite m_bgSprite; // sptrite for lab 2
	sf::Sprite m_wallSprite; // wal sptirets
	sf::Sprite m_funExpSprite;// explosion
	sf::Sprite m_returnBaseSprite;
	sf::Sprite m_keyboardLayoutSprite; // sprite oif the keyuboard klayont for the instucriotnn
	sf::Sprite coinSpriteSheet;
	sf::Sprite m_backgroundSprite;
	sf::Sprite m_gameEndSprite;
	sf::Sprite m_oldShipDisplaySprite;
	sf::Sprite m_soyShipDisplaySprite;
	sf::Sprite m_warShipDisplaySprite;


	sf::Texture m_texture; // texture of the sprite sheet
	sf::Texture m_bgTexture;// texture sprite sheet
	sf::Texture m_spriteSheetTexture;
	sf::Texture m_funExpTexture;
	sf::Texture m_returnBaseTexture; 
	sf::Texture m_rubyShipTexture;
	sf::Texture m_rubyShipTextureOld;
	sf::Texture m_rubyShipTextureSoy;
	sf::Texture m_keyboardLayoutTexture;
	sf::Texture coinTextureSheet;
	sf::Texture m_backgroundTexture;
	sf::Texture m_gameEndTexture;
	sf::Texture m_gameEndTexture2;

	// A data structure to store our level data
	LevelData m_level;
	// A container (array) for ship sprites. 	
	std::vector<sf::Sprite> m_spriteVector;
	std::vector<sf::Sprite>  m_wallSpritesVector;
	sf::Vector2f m_startPos; // starting pos of the ship
	sf::Vector2f m_enemyOldPos{ 0.0f,0.0f}; //old pos of the enemy that holds
	// A texture for the sprite sheet
	sf::Clock clock;
	// on screen text 
	sf::Text m_clockText;
	sf::Text m_scoreText;
	sf::Text m_gameOverText;
	sf::Text m_shotsNum;
	sf::Text m_accuracyText;
	sf::Text m_targetsHitText;
	sf::Text m_aiShipHPText;
	sf::Text m_rubyState;
	sf::Text m_infoScreen1;
	sf::Text m_infoScreen2;
	sf::Text m_infoScreen3;
	sf::Text m_authors;
	sf::Font m_font;

	thor::Timer m_timer;// time to hold for the game end 
	int TIMER_DUR_THOR = 60000;
	int m_timeRemainThor = 60;
	int m_gameOverSeconds = 0;
	int m_score = 0; // score of the player
	int m_shotsHit = 0;
	int m_hitAccuracy = 0;
	int m_expFrameV = 0; // explosuinbs frame
	int m_expFrameH = 0; // explosuinbs frame
	int m_carrierFrameV = 0; // explosuinbs frame
	int m_carrierFrameH = 0; // explosuinbs frame
	int m_aiShipHP = 200;

	float m_frameIncrementExp=0.25f; // how fast 
	float m_fameCounterExp= 1.0f; // expl
	float m_frameIncrementCarrier = 0.023f; // how fast 
	float m_fameCounterCarrier= 1.0f; // expl


	float iLetExplosionBoom = 0; // literally lets exploassion boom

	bool rubyReturned = false;
	bool rubyIsCaptured = false;
	bool m_hitYes = false;
	bool m_gameplaySound = false;
	bool changedTextureForPlayerShip = false;
	bool m_rubyDelivered = false;
	bool coinIsCollected = false;
	bool stopDrawingCoin = false;

	sf::SoundBuffer m_backgroundBuffer;
	sf::Sound m_backgroundSound;

	sf::SoundBuffer m_buttonBuffer;
	sf::Sound m_buttonSound;

	sf::SoundBuffer m_menuBuffer;
	sf::Sound m_menuSound;


	// main window
	sf::RenderWindow m_window;
	// The game HUD instance.
	HUD m_hud;

};

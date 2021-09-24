//Name of project: Animated Sprite FSM			
//Author: Adam Mcguigan													
//Date: 18-01-2021																								                                                                        																	 ////




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
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 



#include "Game.h" 
#include <iostream>      
#include <chrono>
#include "Animation.h"
#include <thread>
#include <Windows.h>
#include <string>
#include "State.h"


Animation fsm;


int main()
{
	Game aGame;
	aGame.loadContent();
	aGame.run();
	return 0;
}
// Default constructor
sf::RenderWindow window(sf::VideoMode(800, 600), "Player Finite State Machine");


Game::Game()
{
	setIdle = true;
	setWalkingRight = false;
	setWalkingLeft = false;
	setJump = false;
	setReset = false;
	setDaggerCheck = false;
	setGlide = false;
	
}

void Game::loadContent()
// Load the font file & setup the message string
{


}


void Game::run()
// This function contains the main game loop which controls the game. 
{
	srand(time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}


		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			draw();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

}


void Game::update()
{
	// get keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		setGlide = true;
		setReset = false;
		setIdle = false;
		setJump = false;
		setWalkingRight = false;
		setWalkingLeft = false;
		setDaggerCheck = false;
		counter = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		setReset = true;
		setIdle = false;
		setJump = false;
		setWalkingRight = false;
		setWalkingLeft = false;
		setDaggerCheck = false;
		setGlide = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) //Every time the Q button is pressed it sets the check Dagger to true and will play that animation
	{
		std::cout << "Entering the Dagger Check Animation" << std::endl;
		setDaggerCheck = true;
		setWalkingLeft = false;
		setIdle = false;
		setJump = false;
		setWalkingRight = false;
		setGlide = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	//Every time the A button is pressed it sets the walkingLeft to true and will play that animation
	{
		std::cout << "Entering the Walking Left animation" << std::endl;
		setWalkingLeft = true;
		setIdle = false;
		setJump = false;
		setWalkingRight = false;
		setDaggerCheck = false;
		setGlide = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		//Every time the D button is pressed it sets the walkingRight to true and will play that animation
	{
		std::cout << "Entering the Walking right animation" << std::endl;
		setWalkingRight = true;
		setWalkingLeft = false;
		setJump = false;
		setReset = false;
		setDaggerCheck = false;
		setGlide = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))		//Every time I is pressed sets the bool to true and sets the player into an idle state
	{
		std::cout << "Entering the Idle animation" << std::endl;
		setIdle = true;
		setJump = false;
		setWalkingLeft = false;
		setWalkingRight = false;
		setDaggerCheck = false;
		setGlide = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  //Every time the space is pressed, sets jump to true and allows the player to jump until the timer hits 25
	{
		std::cout << "Entering the Jump animation" << std::endl;
		setJump = true;
		setIdle = false;
		setWalkingRight = false;
		setWalkingLeft = false;
		setDaggerCheck = false;
		setGlide = false;
		counter = 0;
	}

	if (setIdle == true) //When true plays the animation
	{
		std::cout <<  "Idle Animation" << std::endl;
		fsm.idleAnimation();
	}

	if (setWalkingRight == true)//When true plays the animation
	{
		std::cout << "Walking Right " << std::endl;
		fsm.walkingRightAnimation();
	}

	if (setJump == true) //When true plays the animation until timer hits 25 then sets the player back to Idle
	{
		if (counter <= 25)
		{
			fsm.jumpingAnimation();
			std::cout << "Jumping Animation" << std::endl;
			counter++;
			std::cout << counter << std::endl;
		}
		if (counter >= 25)
		{
			setJump = false;
			setIdle = true;
		}
	}

	if (setWalkingLeft == true) //When true plays the animation
	{
		fsm.walkingLeftAnimation();
		std::cout << "Walking Left Animation" << std::endl;
	}

	if (setReset == true) //When true plays the animation
	{
		fsm.reset();
		std::cout << "Resetting the player" << std::endl;
	}

	if (setDaggerCheck == true) //When true plays the animation
	{
		fsm.checkDaggerAnimation();
		std::cout << "Checking Dagger Idle Animation" << std::endl;
	}

	if (setGlide == true) //When true plays the animation until timer hits 50 then sets the player back to true
	{
		if (counter <= 50)
		{
			fsm.glideAnimation();
			std::cout << "Gliding Animation" << std::endl;
			counter++;
			std::cout << counter << std::endl;
		}
		if (counter >= 50)
		{
			setGlide = false;
			setIdle = true;
		}
	
	}
}

void Game::draw()
// This function draws the game world
{
	window.clear();		//clears the window
	window.draw(fsm.playerSprite); //drawing the player sprite
	window.display();		//display everything on screen
}


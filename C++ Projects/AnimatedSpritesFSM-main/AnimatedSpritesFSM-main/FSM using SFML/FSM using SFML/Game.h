#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

class Game
{


public:
	//I set bools to run the animations because it wasnt working if i called the animations in the is key pressed event
	bool setIdle;
	bool setWalkingRight;
	bool setWalkingLeft;
	bool setJump;
	bool setReset;
	bool setDaggerCheck;
	bool setGlide;

	//I used this variable as a counter for the jump and gliding animations
	int counter = 0;

	Game(); // default constructor
	void    loadContent();        //loading the textures
	void    run();                //run function
	void    update();            //update function
	void    draw();                //draw function


};
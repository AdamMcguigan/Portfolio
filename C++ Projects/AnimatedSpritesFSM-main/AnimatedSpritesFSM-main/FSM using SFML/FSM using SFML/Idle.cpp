#pragma once
#include <iostream>
#include "Idle.h"

void Idle::jumping(Animation* a)
{
	std::cout << "Did u see how high he jumped, the player has a future in the NBA " << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::climbing(Animation* a)
{
	std::cout << "The player is climbing now, he looks like Spoderman with his technique " << std::endl;
	a->setCurrent(new Idle());
	delete this;
}
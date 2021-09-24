#pragma once
#include "State.h"
#include "Idle.h"
#include <iostream>
using namespace std;

class Jumping : public State
{
public:
	Jumping() {};
	~Jumping() {};
	void idle(Animation* a)
	{
		cout << "Going from Jumping to Idling" << endl;
		a->setCurrent(new Idle());
		delete this;
	}
};
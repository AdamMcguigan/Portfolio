#pragma once
#include "Animation.h"
#include "State.h"
#include <iostream>
using namespace std;

class Idle : public State
{
public:
	Idle() {};
	~Idle() {};
	void jumping(Animation* a);
	void climbing(Animation* a);
};
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
/// Authors : Adam Mcguigan, Sasa Kuzmanovic, Sean Whelan
/// video link - https://instituteoftechnol663-my.sharepoint.com/:f:/g/personal/c00248515_itcarlow_ie/EkhpmSdezq1Jme-5xGJB2L0BqHBBIt6for7uCXcYwnCCzw?e=gqb42b

class Particle
{
public:
	int timetoLive;
	sf::Vector2f velocity;
	sf::RectangleShape shape;

	void Draw(sf::RenderWindow& win)
	{
		if (timetoLive > 0)
		{
			win.draw(shape);
		}
	}
	void Update()
	{
		if (timetoLive > 0)
		{
			shape.move(velocity);

			timetoLive--;
		}
	}

	Particle() {}

	Particle(sf::Vector2f pos, sf::Vector2f vel)
	{
		shape.setSize(sf::Vector2f(6, 6));
		shape.setPosition(pos);
		shape.setFillColor(sf::Color::Red);

		velocity = vel;
		timetoLive = 200;
		timetoLive = rand() % 150;

	}
};


#define maxParticles 50
class ParticleSystem
{
public:

	Particle particles[maxParticles];
	sf::Vector2f position;
	void Initialise(sf::Vector2f pos)
	{
		position = pos;
		for (int i = 0;i < maxParticles;i++)
		{
			particles[i] = Particle(position, sf::Vector2f(rand() / double(RAND_MAX) * 4 - 2, rand() / double(RAND_MAX) * 4 - 2));
		}
	}
	void Update()
	{
		for (int i = 0;i < maxParticles;i++)
		{

			particles[i].Update();


		}
	}
	void Draw(sf::RenderWindow& win)
	{
		for (int i = 0;i < maxParticles;i++)
		{
			particles[i].Draw(win);
		}
	}

	ParticleSystem() {}
};
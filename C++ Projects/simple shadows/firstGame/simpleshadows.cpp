
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

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector>
#include "Trigonometry.hpp"
#include "VectorAlgebra2D.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "2d lighting -simple shadows");

	srand(time(NULL));
	sf::VertexArray quad(sf::Quads, 4);
	sf::VertexArray quad1(sf::Quads, 4);

	sf::VertexArray shadowQuad(sf::Quads, 4);
	sf::VertexArray shadowQuad2(sf::Quads, 4);

	sf::Vector2f light = { 100,100 };
	float length = (300);

	sf::CircleShape lightShape(5);
	lightShape.setOrigin(5, 5);
	lightShape.setPosition(0, 0);
	lightShape.setFillColor(sf::Color::White);

	quad[0].position = sf::Vector2f(300.f, 300);
	quad[1].position = sf::Vector2f(500.f, 300.f);
	quad[2].position = sf::Vector2f(500.f, 400.f);
	quad[3].position = sf::Vector2f(300.f, 400.f);
	quad[0].color = sf::Color::Cyan;
	quad[1].color = sf::Color::Magenta;
	quad[2].color = sf::Color::Cyan;
	quad[3].color = sf::Color::Magenta;

	quad1[0].position = sf::Vector2f(200, 150);
	quad1[1].position = sf::Vector2f(300.f, 150.f);
	quad1[2].position = sf::Vector2f(300.f, 220.f);
	quad1[3].position = sf::Vector2f(200.f, 220.f);
	quad1[0].color = sf::Color::Red;
	quad1[1].color = sf::Color::Red;
	quad1[2].color = sf::Color::Red;
	quad1[3].color = sf::Color::Red;

	//setting the pos of the shadow quad from the old quad
	sf::Vector2f cubeVector1 = quad[0].position;
	sf::Vector2f cubeVector2 = quad[1].position;
	sf::Vector2f cubeVector3 = quad[2].position;
	sf::Vector2f cubeVector4 = quad[3].position;

	sf::Vector2f cubeVector5 = quad1[0].position;
	sf::Vector2f cubeVector6 = quad1[1].position;
	sf::Vector2f cubeVector7 = quad1[2].position;
	sf::Vector2f cubeVector8 = quad1[3].position;

	
	// set timePerFrame to 1 60th of a second. 60 frames per second
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	// the clock object keeps the time.
	sf::Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{
			sf::Vector2i position = sf::Mouse::getPosition(window);

			lightShape.setPosition(position.x, position.y);

			//Calculating P 
			shadowQuad[0].position = sf::Vector2f(quad[0].position.x, quad[0].position.y);
			shadowQuad[1].position = sf::Vector2f(quad[1].position.x, quad[1].position.y);
			shadowQuad[2].position = sf::Vector2f(quad[2].position.x - lightShape.getPosition().x, quad[2].position.y - lightShape.getPosition().y);
			shadowQuad[3].position = sf::Vector2f(quad[3].position.x - lightShape.getPosition().x, quad[3].position.y - lightShape.getPosition().y);

			shadowQuad2[0].position = sf::Vector2f(quad1[0].position.x, quad1[0].position.y);
			shadowQuad2[1].position = sf::Vector2f(quad1[1].position.x, quad1[1].position.y);
			shadowQuad2[2].position = sf::Vector2f(quad1[2].position.x - lightShape.getPosition().x, quad1[2].position.y - lightShape.getPosition().y);
			shadowQuad2[3].position = sf::Vector2f(quad1[3].position.x - lightShape.getPosition().x, quad1[3].position.y - lightShape.getPosition().y);

			//shadowQuad[0].position += cubeVector1;
			//shadowQuad[1].position += cubeVector2;
			shadowQuad[2].position += cubeVector3;
			shadowQuad[3].position += cubeVector4;

			//shadowQuad2[0].position += cubeVector5;
			//shadowQuad2[1].position += cubeVector6;
			shadowQuad2[2].position += cubeVector7;
			shadowQuad2[3].position += cubeVector8;

			//setting the length using thor
			thor::setLength(cubeVector1, length);
			thor::setLength(cubeVector2, length);
			thor::setLength(cubeVector3, length);
			thor::setLength(cubeVector4, length);

			thor::setLength(cubeVector5, length);
			thor::setLength(cubeVector6, length);
			thor::setLength(cubeVector7, length);
			thor::setLength(cubeVector8, length);


			//drawing all the shapes
			window.clear(sf::Color::Transparent);
			window.draw(shadowQuad);
			window.draw(shadowQuad2);
			window.draw(quad);
			window.draw(quad1);


			window.draw(lightShape);



			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}


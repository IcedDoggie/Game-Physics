#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

#include "Framework/Test.h"
#include "Framework/Render.h"

#include "Car.h"

int main()
{
	float fixedTimeStep = 0.02f;
	sf::Clock fixedUpdateClock;
	float timeElapsedSinceLastFrame = 0;


	int windowSizeX = 800, windowSizeY = 600;
	int windowBorderSize = 16;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Car");

	// window.setVerticalSyncEnabled(true);
	window.setActive();

	b2Vec2 gravity(0.f, 9.81f);
	b2World world(gravity);

	sf::Vector2f horizontalBorderSize(windowSizeX,windowBorderSize);
	sf::Vector2f verticalBorderSize(windowBorderSize,windowSizeY-windowBorderSize*2);
	sf::Vector2f    topBorderPos(windowSizeX/2,windowBorderSize/2);
	sf::Vector2f bottomBorderPos(windowSizeX/2,windowSizeY-windowBorderSize/2);
	sf::Vector2f   leftBorderPos(windowBorderSize/2,windowSizeY/2);
	sf::Vector2f  rightBorderPos(windowSizeX-windowBorderSize/2,windowSizeY/2);
	
	sf::Text text;
	text.setCharacterSize(16);
	text.setPosition(3, -3);
	text.setColor(sf::Color::White);
	while(window.isOpen())
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear(sf::Color(0,0,0));

		text.setString("Testing For a Car");
		window.draw(text);

		window.display();
	}
	return 0;
}

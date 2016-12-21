#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;


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

	
	sf::Text text;
	sf::Font font;
	if(!font.loadFromFile("sansation.ttf"))
	{
		cout<< "ping!";
	}


	while(window.isOpen())
	{
		sf::Event event;

		text.setString("Testing For a Car");
		text.setFont(font);
		text.setCharacterSize(16);
		text.setPosition(170.f, 150.f);
		text.setColor(sf::Color::White);
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		

		
		
		//chinkok
		window.clear(sf::Color(0,0,0));
		window.draw(text);
		window.display();
	}
	// return 0;
}

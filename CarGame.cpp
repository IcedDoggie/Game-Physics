#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

int main()
{
	// For update frames
	float fixedTimeStep = 0.02f;
	sf::Clock fixedUpdateClock;
	float timeElapsedForUpdateTime = 0;
	
	// window creation
	int windowSizeX = 800, windowSizeY = 600;
	int windowBorderSize = 16;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Car");

	// window.setVerticalSyncEnabled(true);
	window.setActive();

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}


		//chinkok
		window.clear(sf::Color(0,0,0));
		window.display();
	}
	return 0;
}

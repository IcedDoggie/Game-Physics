#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

int main()
{
	
	
	int windowSizeX = 800, windowSizeY = 600;
	int windowBorderSize = 16;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Car");

	window.setVerticalSyncEnabled(true);
	window.setActive();

	while(window.isOpen())
	{
		//chinkok
		window.clear(sf::Color(100, 149, 237));
		window.display();
	}
	return 0;
}
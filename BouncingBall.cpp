#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


using namespace std;

float calculateRotation(float degree, float up_direction, float horizontal_direction)
{

}

int main()
{
	int windowSizeX = 800, windowSizeY = 600;
	int windowBorderSize = 16;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Car");

	// Game Object
	sf::CircleShape ball(50);
	sf::Font font;
	sf::Text win;
	sf::Text lose;
	sf::Texture texture;
	ball.setPosition(300, 0);	

	// Physics Variable
	float gravity = 0.03f;
	float u_velocity = 0.20f;
	float v_velocity = 0.00f;
	float step_velocity = 0.01f;
	float rotation;
	float horizontal_direction = 0.0f;

	if(!texture.loadFromFile("football.jpg"))
	{
	}

	if(!font.loadFromFile("sansation.ttf"))
	{
	}
	ball.setTextureRect(sf::IntRect(35,0,190,190));
	ball.setTexture(&texture);


	// window.setVerticalSyncEnabled(true);
	window.setActive();
	while(window.isOpen())
	{	
		sf::Event event;	

		if(event.mouseButton.button == sf::Mouse::Left 
			&& (abs(event.mouseButton.x - ball.getPosition().x) >= 25 
			|| abs(event.mouseButton.y - ball.getPosition().y) >= 25
			|| abs(event.mouseButton.x - ball.getPosition().x) <= 25 
			|| abs(event.mouseButton.y - ball.getPosition().y) <= 25))
		{

			cout<<"diff x: "<< event.mouseButton.x - ball.getPosition().x<<" ";
			cout<<"diff y: "<< event.mouseButton.y - ball.getPosition().y<<endl; 
			ball.move(0, -u_velocity);
		}

		else
		{
			ball.move(0, gravity);
			// cout<<"ball x: "<< ball.getPosition().x<<" ";		
		}

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// display text
		if(ball.getPosition().y >= 600)
		{
			lose.setString("Lose");
			lose.setFont(font);
			lose.setCharacterSize(16);
			lose.setPosition(400.0f, 100.0f);
			lose.setColor(sf::Color::White);	
		}

		// Rendering
		window.clear(sf::Color(0,0,0));
		window.draw(ball);
		window.draw(lose);
		window.display();
	}
}
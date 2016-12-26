#include <SFML/Graphics.hpp>
#include "WorldBuilder.h"
#include <iostream>

using namespace std;
int main()
{
	//Physics Variable
	float initial_velocity_right = 0.01f;
	float initial_velocity_left = -0.01f;
	float acceleration = 0.0001f;
	float moving_time = 0.0f;
	float gravity = 0.0f;
	int current_position_car = 0;



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

	// draw world
	////1 -> tile, 2-> player
	int worldArray [6][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0},
		{1,1,1,1,0,1,1,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	};

	sf::VertexArray world(sf::Lines, 4);
	world[0].position = sf::Vector2f(0,400);
	world[1].position = sf::Vector2f(400,400);
	world[2].position = sf::Vector2f(500,400);
	world[3].position = sf::Vector2f(800,400);

	// draw car
	sf::VertexArray car(sf::Lines, 16);
	sf::CircleShape frontWheel(5);
	sf::CircleShape backWheel(5);
	//horizontal
	car[0].position = sf::Vector2f(10, 375);
	car[1].position = sf::Vector2f(20, 375);
	//slant line
	car[8].position = sf::Vector2f(20, 375);
	car[9].position = sf::Vector2f(30, 360);
	//horizontal
	car[2].position = sf::Vector2f(30, 360);
	car[3].position = sf::Vector2f(50, 360);
	//slant line
	car[10].position = sf::Vector2f(50, 360);
	car[11].position = sf::Vector2f(60, 375);
	//horizontal
	car[4].position = sf::Vector2f(60, 375);
	car[5].position = sf::Vector2f(70, 375);
	//straight line
	car[12].position = sf::Vector2f(70, 375);
	car[13].position = sf::Vector2f(70, 385);
	//horizontal
	car[6].position = sf::Vector2f(70, 385);
	car[7].position = sf::Vector2f(10, 385);
	//straight line
	car[14].position = sf::Vector2f(10, 385);
	car[15].position = sf::Vector2f(10, 375);
	//wheels
	frontWheel.setPosition(55, 385);
	backWheel.setPosition(15, 385);


	while(window.isOpen())
	{
		// cout<<"Current position: "<<current_position_car<<endl;
		
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
		// check if what is below the car is empty
		for(int i=0; i<6; i++)
		{
			for(int j=0; j<8; j++)
			{
				if(worldArray[i][j] == 2)
				{
					if(worldArray[i+1][j] == 0)
					{
						gravity = 0.1f;
					} 
					else
					{
						gravity = 0.0f;
					}
				}
			}
		}

		if(gravity > 0.0f)
		{
			for(int i=0; i<sizeof(car); i++)
			{
				car[i].position += sf::Vector2f(0, gravity);
			}

			float initial_velocity_x = frontWheel.getPosition().x;
			float initial_velocity_y = frontWheel.getPosition().y;
			frontWheel.setPosition(initial_velocity_x, initial_velocity_y + gravity);
			float initial_velocity_x_back = backWheel.getPosition().x;
			float initial_velocity_y_back = backWheel.getPosition().y;
			backWheel.setPosition(initial_velocity_x_back, initial_velocity_y_back + gravity);
			
		}

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			initial_velocity_left = -0.01f;
			for(int i=0; i<sizeof(car); i++)
			{
				car[i].position += sf::Vector2f(initial_velocity_right,0);
			}
			float initial_velocity_x = frontWheel.getPosition().x;
			float initial_velocity_y = frontWheel.getPosition().y;
			frontWheel.setPosition(initial_velocity_x + initial_velocity_right, initial_velocity_y + gravity);
			float initial_velocity_x_back = backWheel.getPosition().x;
			float initial_velocity_y_back = backWheel.getPosition().y;
			backWheel.setPosition(initial_velocity_x_back + initial_velocity_right, initial_velocity_y_back + gravity);
			initial_velocity_right += acceleration;
			// move the car in the backend array
			
			if(static_cast<int>(frontWheel.getPosition().x) % 100 == 0)
			{
				frontWheel.setPosition(initial_velocity_x + 1, initial_velocity_y);
				worldArray[2][current_position_car] = 0;
				current_position_car += 1;
				worldArray[2][current_position_car] = 2;
				cout<<"car: "<<current_position_car<<endl;

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			initial_velocity_right = 0.01f;
			for(int i=0; i<sizeof(car); i++)
			{
				car[i].position += sf::Vector2f(initial_velocity_left, 0);
			}
			float initial_velocity_x = frontWheel.getPosition().x;
			float initial_velocity_y = frontWheel.getPosition().y;
			frontWheel.setPosition(initial_velocity_x + initial_velocity_left, initial_velocity_y + gravity);
			float initial_velocity_x_back = backWheel.getPosition().x;
			float initial_velocity_y_back = backWheel.getPosition().y;
			backWheel.setPosition(initial_velocity_x_back + initial_velocity_left, initial_velocity_y_back + gravity);
			initial_velocity_left -= acceleration;
			if(static_cast<int>(frontWheel.getPosition().x) % 100 == 0)
			{
				frontWheel.setPosition(initial_velocity_x - 1, initial_velocity_y);
				current_position_car -= 1;
				cout<<"car: "<<current_position_car<<endl;
			}
		}



	
		// Rendering
		window.clear(sf::Color(0,0,0));

		// Objct Rendering

		window.draw(world);
		window.draw(car);
		window.draw(frontWheel);
		window.draw(backWheel);
		window.draw(text);
		window.display();
	}
	// return 0;
}

#include <SFML/Graphics.hpp>
#include "WorldBuilder.h"
#include <iostream>
#include <cmath>

using namespace std;

int calculateRotation(int rotationAngle, int initialVelocity)
{
	rotationAngle = rotationAngle * (M_PI/180);
	int finalVelocity = initialVelocity * cos(rotationAngle);

	if(initialVelocity > 0 )
	{
		// cout<<"Final Velocity: "<<finalVelocity<<endl;
		// cout<<"Initial Velocity: "<<initialVelocity<<endl;
		// cout<<"rotationAngle: "<<rotationAngle<<endl;
	}
	return finalVelocity;
}

int calculateCarRotation(int degree, int length_horizontal)
{
	int car_pos;
	int ratio_slope_horizontal;
	float rad = degree * (M_PI/180);
	car_pos = length_horizontal / (cos(rad));
	// cout<<"ratio: "<< car_pos <<" ";
	return car_pos;
}

int main()
{
	//Physics Variable
	float initial_velocity_right = 0.01f;
	float initial_velocity_left = -0.01f;
	float acceleration = 0.0001f;
	float moving_time = 0.0f;
	float gravity = 0.0f;
	int current_position_car_x = 2;
	int current_position_car_y = 0;

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
	sf::Transform rotation;
	rotation.rotate(10);
	if(!font.loadFromFile("sansation.ttf"))
	{
		cout<< "ping!";
	}

	// draw world
	////1 -> tile, 2-> player
	int worldArray [6][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{2,0,0,3,0,0,0,0},
		{1,1,1,1,0,1,1,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	};

	sf::VertexArray world(sf::Lines, 8);
	world[0].position = sf::Vector2f(0,400);
	world[1].position = sf::Vector2f(400,400);

	world[4].position = sf::Vector2f(200,400);
	world[5].position = sf::Vector2f(400,300);

	world[6].position = sf::Vector2f(400,300);
	world[7].position = sf::Vector2f(400,400);

	world[2].position = sf::Vector2f(500,400);
	world[3].position = sf::Vector2f(800,400);

	sf::CircleShape frontWheel(5);
	sf::CircleShape backWheel(5);

	//wheels
	frontWheel.setPosition(50, 385);
	backWheel.setPosition(10, 385);

	//try to draw rectangle as car
	sf::RectangleShape car_rect(sf::Vector2f(50,20));
	car_rect.setPosition(10,370);
	// car_rect.setRotation(45);


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
						// update backend array if car is dropping in terms of y-axis
						gravity = 0.1f;
						
					} 
					else
					{
						gravity = 0.0f;
					}
				}
			}
		}

		// let car go up slope
		if(worldArray[current_position_car_x][current_position_car_y + 1] == 3)
		{
			int initial_velocity_right_parsed = static_cast<int>(initial_velocity_right * 100);
			int rotation_speed = calculateRotation(45, initial_velocity_right_parsed);
			int rotation_car = calculateCarRotation(45, 200);
		}

		// for car to fall when there is no ground
		if(gravity > 0.0f)
		{
			car_rect.move(0, gravity);
			float initial_velocity_x = frontWheel.getPosition().x;
			float initial_velocity_y = frontWheel.getPosition().y;
			frontWheel.setPosition(initial_velocity_x, initial_velocity_y + gravity);
			float initial_velocity_x_back = backWheel.getPosition().x;
			float initial_velocity_y_back = backWheel.getPosition().y;
			backWheel.setPosition(initial_velocity_x_back, initial_velocity_y_back + gravity);
		}
		//move right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			initial_velocity_left = -0.01f;

			car_rect.move(initial_velocity_right, 0);
			cout<<"car rect: "<<car_rect.getPosition().x<<" ";
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
				worldArray[current_position_car_x][current_position_car_y] = 0;
				current_position_car_y += 1;
				worldArray[current_position_car_x][current_position_car_y] = 2;
				cout<<"car: "<<current_position_car_x<<endl;
				// if(worldArray[current_position_car_x+1][current_position_car_y] == 0)
				// {
				// 	worldArray[current_position_car_x][current_position_car_y] = 0;
				// 	current_position_car_x += 1;
				// 	worldArray[current_position_car_x][current_position_car_y] = 2;
				// }

				for(int m=0; m<6; m++)
				{
					for(int n=0; n<8; n++)
					{
						cout<<worldArray[m][n]<<" ";
					}
					cout<<endl;
				}
			}
		}
		//move left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			initial_velocity_right = 0.01f;

			car_rect.move(initial_velocity_left, 0);
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
				current_position_car_y -= 1;
				cout<<"car: "<<current_position_car_y<<endl;
			}
		}



	
		// Rendering
		window.clear(sf::Color(0,0,0));

		// Objct Rendering
		window.draw(car_rect);
		window.draw(world);
		window.draw(frontWheel);
		window.draw(backWheel);
		window.draw(text);
		window.display();
	}
	// return 0;
}

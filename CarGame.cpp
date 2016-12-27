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
	float deceleration = -0.0001f;
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
	////1 -> tile, 2-> player 3->slope
	int worldArray [15][20] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
	};

	sf::VertexArray world(sf::Lines, 24);
	//starting point
	world[0].position = sf::Vector2f(0,400);
	world[1].position = sf::Vector2f(400,400);

	//slope
	world[4].position = sf::Vector2f(200,400);
	world[5].position = sf::Vector2f(400,300);

	//slope
	world[6].position = sf::Vector2f(400,300);
	world[7].position = sf::Vector2f(400,400);

	//ending point
	world[2].position = sf::Vector2f(500,400);
	world[3].position = sf::Vector2f(800,400);


	//try to draw rectangle as car
	sf::RectangleShape car_rect(sf::Vector2f(50,20));
	car_rect.setPosition(10,370);
	// car_rect.setRotation(45);


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
		// check if what is below the car is empty
		if(worldArray[current_position_car_x+1][current_position_car_y] == 0 && initial_velocity_right >0)
		{
			cout<<current_position_car_x<<endl;
			// update backend
			worldArray[current_position_car_x][current_position_car_y] = 0;
			current_position_car_x += 1;
			worldArray[current_position_car_x][current_position_car_y] = 2;
			for(int m=0; m<15; m++)
			{
				for(int n=0; n<20; n++)
				{
					// cout<<worldArray[m][n]<<" ";
				}
				// cout<<endl;
			}	
			cout<<endl;		
			gravity = 0.01f;		
		}

		else if(worldArray[current_position_car_x+1][current_position_car_y] == 1)
		{
			gravity = 0.0f;
		}




		// for(int i=0; i<15; i++)
		// {
		// 	for(int j=0; j<20; j++)
		// 	{
		// 		if(worldArray[i][j] == 2)
		// 		{
		// 			if(worldArray[i+1][j] == 0)
		// 			{
		// 				cout<<"Falling...\n";
		// 				// update backend array if car is dropping in terms of y-axis
		// 				worldArray[current_position_car_x][current_position_car_y] = 0;
		// 				current_position_car_x -= 1;
		// 				worldArray[current_position_car_x + 1][current_position_car_y] = 2;
		// 				gravity = 0.1f;	
		// 			}

		// 			else if(worldArray[i+1][j] == 3)
		// 			{
		// 				cout<<"On slope!\n";
		// 				gravity = 0.0f;
		// 			}

		// 			else if(worldArray[i+1][j] == 1)
		// 			{
		// 				cout<<"no gravity!\n";
		// 				gravity = 0.0f;
		// 			}
		// 		}
		// 	}
		// }

		// let car go up slope
		if(worldArray[current_position_car_x][current_position_car_y + 1] == 3 && initial_velocity_right > 0)
		{

			int initial_velocity_right_parsed = static_cast<int>(initial_velocity_right * 100);
			int rotation_speed = calculateRotation(45, initial_velocity_right_parsed);
			int rotation_car = calculateCarRotation(45, 200);
			
			// visualize
			car_rect.rotate(-30);

			// update world array
			worldArray[current_position_car_x - 1][current_position_car_y + 1] = 2;
			worldArray[current_position_car_x][current_position_car_y] = 0;

			// update car position
			current_position_car_x = current_position_car_x - 1;
			current_position_car_y = current_position_car_y + 1;
		}

		// for car to fall when there is no ground
		if(gravity > 0.0f)
		{
			car_rect.move(0, gravity);
		}
		//move right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			initial_velocity_left = 0.0f;

			car_rect.move(initial_velocity_right, 0);
			initial_velocity_right += acceleration;

			// move the car in the backend array
			if(static_cast<int>(car_rect.getPosition().x) % 20 == 0 &&
			 worldArray[current_position_car_x][current_position_car_y+1] != 3)
			{
				worldArray[current_position_car_x][current_position_car_y] = 0;
				current_position_car_y += 1;
				worldArray[current_position_car_x][current_position_car_y] = 2;
			}
		}
		//move left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			initial_velocity_right = 0.0f;

			car_rect.move(initial_velocity_left, 0);
			initial_velocity_left -= acceleration;
			if(static_cast<int>(car_rect.getPosition().x) % 20 == 0 &&
				worldArray[current_position_car_x-1][current_position_car_y] != 3)
			{
				worldArray[current_position_car_x][current_position_car_y] = 0;
				current_position_car_y -= 1;
				worldArray[current_position_car_x][current_position_car_y] = 2;
			}
			if(worldArray[current_position_car_x][current_position_car_y+1] == 0)
			{
				cout<<"ping"<<endl;
				worldArray[current_position_car_x][current_position_car_y] = 0;
				current_position_car_y -= 1;
				// current_position_car_x += 1;
				worldArray[current_position_car_x][current_position_car_y] = 2;
				car_rect.rotate(30);
			}

		}

		// Rendering
		window.clear(sf::Color(0,0,0));

		// Objct Rendering
		window.draw(car_rect);
		window.draw(world);
		window.draw(text);
		window.display();
	}
	// return 0;
}

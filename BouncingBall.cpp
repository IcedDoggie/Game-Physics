#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime>


using namespace std;

float calculateRotation(float degree, float up_direction, float horizontal_direction)
{
	float resultant_direction;
	// convert degree to radian
	float radian = degree * (3.142 / 180);
	up_direction =  up_direction * radian;
	horizontal_direction = horizontal_direction * radian * 10.0f;
	// cout<< radian<< endl;
	return up_direction, horizontal_direction;	
}

float calculateGravityEffectUp(float velocity, float acceleration, float bounce_time)
{
	float after_velocity = velocity + acceleration * bounce_time;
	// cout<< velocity << " "<< acceleration<< " "<< bounce_time<<endl;
	return after_velocity;
}

float calculateGravityEffectDown(float velocity, float acceleration, float bounce_time)
{
	float after_velocity = velocity + acceleration * bounce_time;
	return after_velocity;
}

template <typename T>
 string NumberToString ( T Number )
 {
    ostringstream ss;
    ss << Number;
    return ss.str();
 }

int main()
{
	int windowSizeX = 800, windowSizeY = 600;
	int windowBorderSize = 16;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Car");

	// Game Object
	sf::CircleShape ball(50);
	sf::Font font;
	sf::Text score;
	sf::Text gameStatus;
	sf::Texture texture;
	ball.setPosition(300, 0);	

	// Physics Variable
	float gravity = 0.03f;
	float u_velocity;
	float v_velocity = 0.00f;
	float step_velocity = 0.01f;
	float rotation;
	float horizontal_direction = 0.03f;
	float bounce_time = 1.0f;

	// Game Variable
	int points = 0;
	bool checkHold = false;
	clock_t start;
	clock_t gameTime_score;
	clock_t gameTime_ends;
	bool gameOver = false;
	// clock_t 

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
		gameTime_score = clock();
		// trigger the ball to move up
		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
			checkHold == false && gameOver == false
			&& (abs(event.mouseButton.x - ball.getPosition().x) <= 50 
			|| abs(event.mouseButton.y - ball.getPosition().y) <= 50))
		{
			u_velocity = -3.0f;
			horizontal_direction = 0.07f;
			start = 1;
			checkHold = true;
			// ball.move(0, -u_velocity);

			// calculate rotation
			// cout<<event.mouseButton.x - ball.getPosition().x<<endl;
			if( (event.mouseButton.x - ball.getPosition().x) > 0 )
			{
				rotation = -45.0f;
			}

			else if( (event.mouseButton.x - ball.getPosition().x < 0) )
			{
				rotation = 45.0f;
			}
			u_velocity, horizontal_direction = calculateRotation(rotation, u_velocity, horizontal_direction);
			// update score
			points += 1;
			gameTime_score = gameTime_score / (float) CLOCKS_PER_SEC;
			string temp = NumberToString(gameTime_score);
			score.setString(temp);
			score.setFont(font);
			score.setCharacterSize(16);
			score.setPosition(600.0f, 50.0f);
			score.setColor(sf::Color::White);
		}

		// allowing the ball to move in a decelerating way
		else if(start%100!=0 && checkHold == true )
		{
			start = clock();
			// cout<<u_velocity<<endl;
			v_velocity = calculateGravityEffectUp(u_velocity, gravity, bounce_time);
			// check for repeated calculation
			if( (v_velocity < u_velocity) || v_velocity > 0)
			{
				start = 100;
			}
			ball.move(horizontal_direction, v_velocity);
			u_velocity = v_velocity;

			// trigger when touches edges on both sides
			if( ball.getPosition().x >= 700 || ball.getPosition().x <=0)
			{
				cout<<"before: "<<horizontal_direction<<" "<<u_velocity<<endl;
				u_velocity = -u_velocity * 12.0f;
				horizontal_direction = -horizontal_direction * 30.5f;
				cout<<"after: "<<horizontal_direction<<" "<<u_velocity<<endl;
				ball.move(horizontal_direction, 0);
			}

			if( ball.getPosition().y <= 0)
			{
				gravity += 0.001f;
			}
		}

		// trigger the ball to move down
		else
		{
			checkHold = false;
			ball.move(0, gravity);
			// cout<<"ball x: "<< ball.getPosition().x<<" ";		
		}

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// display text
		if(ball.getPosition().y >= 600 && gameOver == false)
		{
			gameTime_score = gameTime_score / (float) CLOCKS_PER_SEC;
			string temp = NumberToString(gameTime_score);
			gameStatus.setString("Lose, You've survived " + temp + " seconds!");
			gameStatus.setFont(font);
			gameStatus.setCharacterSize(16);
			gameStatus.setPosition(400.0f, 100.0f);
			gameStatus.setColor(sf::Color::White);	
			gameOver = true;
		}

		// Rendering	
		window.clear(sf::Color(0,0,0));
		window.draw(ball);
		window.draw(score);
		window.draw(gameStatus);
		window.display();
	}
}
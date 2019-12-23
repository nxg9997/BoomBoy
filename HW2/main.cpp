// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//move camera with arrow keys
void MoveCamera(b2Vec2* cam) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		cam->x += 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		cam->x -= 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cam->y += 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		cam->y -= 10;
	}
}

//stuck to player
void MoveCamera(b2Vec2* cam, Player* p) {
	cam->x -= p->body->GetPosition().x - p->prevPos.x;
	cam->y -= p->body->GetPosition().y - p->prevPos.y;
}

//main function
int main()
{
	//set game variables
	b2World* world = new b2World(b2Vec2(0,10));
	std::vector<Platform*> platVec;
	b2Vec2* cameraOrigin = new b2Vec2(100, 100);

	//visualize mouse click
	sf::Vector2f mouseClick(0, 0);
	sf::CircleShape mouseCircle(2.5f);
	mouseCircle.setFillColor(sf::Color::Cyan);


	// Create the main window
	sf::RenderWindow window(sf::VideoMode(SFML_WIDTH, SFML_HEIGHT), "BoomBoy (Dev)");

	//define player and create basic environment
	Player player(world, &window, b2Vec2(100,100), b2Vec2(10,10), 1);
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 500), b2Vec2(1280, 50), b2_staticBody, 0));//gnd
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 0), b2Vec2(50, 720), b2_staticBody, 0));//left
	platVec.push_back(new Platform(world, &window, b2Vec2(1230, 0), b2Vec2(50, 720), b2_staticBody, 0));//right
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 0), b2Vec2(1280, 50), b2_staticBody, 0));//top
	platVec.push_back(new Platform(world, &window, b2Vec2(640, 360), b2Vec2(50, 720), b2_staticBody, 0));//mid

	//define world step variables
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	// Start the game loop
	while (window.isOpen())
	{
		//update the physics world
		world->Step(timeStep, velocityIterations, positionIterations);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//clear the window
		window.clear();
		
		//player controls
		MoveCamera(cameraOrigin/*,&player*/);
		player.Update();

		//draw gameobjects to screen
		player.Draw(cameraOrigin);
		for (int i = 0; i < platVec.size(); i++) {
			platVec[i]->Draw(cameraOrigin);
		}

		//update mouse click location
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			b2Vec2 mousePos = Helper::GetMouse(&window);
			mousePos.x -= 10;
			mousePos.y -= 40;
			mouseClick = sf::Vector2f(mousePos.x, mousePos.y);
			mouseCircle.setPosition(mouseClick);
		}

		window.draw(mouseCircle);

		// Update the window
		window.display();
	}

	//clean up memory
	for (int i = 0; i < platVec.size(); i++) {
		delete platVec[i];
	}
	delete world;
	delete cameraOrigin;

    return 0;
}


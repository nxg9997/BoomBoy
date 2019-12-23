// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;



//main function
int main()
{
	//set game variables
	b2World* world = new b2World(b2Vec2(0,10));
	std::vector<Platform*> platVec;
	Camera* camera = Camera::GetInstance();

	//visualize mouse click
	sf::Vector2f mouseClick(0, 0);
	sf::CircleShape mouseCircle(2.5f);
	mouseCircle.setFillColor(sf::Color::Cyan);


	// Create the main window
	sf::RenderWindow window(sf::VideoMode(SFML_WIDTH, SFML_HEIGHT), "BoomBoy (Dev)");

	//define player and create basic environment
	Player player(world, &window, b2Vec2(SFML_WIDTH/2, SFML_HEIGHT/2), b2Vec2(10,10), 1);
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 500), b2Vec2(1280, 50), b2_staticBody, 0));//gnd
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 0), b2Vec2(50, 720), b2_staticBody, 0));//left
	platVec.push_back(new Platform(world, &window, b2Vec2(1230, 0), b2Vec2(50, 720), b2_staticBody, 0));//right
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 0), b2Vec2(1280, 50), b2_staticBody, 0));//top
	platVec.push_back(new Platform(world, &window, b2Vec2(640, 360), b2Vec2(50, 720), b2_staticBody, 0));//mid

	//define triangle shape
	b2Vec2* verts = new b2Vec2[3];
	verts[0] = b2Vec2(0, 0);
	verts[1] = b2Vec2(0, 50);
	verts[2] = b2Vec2(100, 10);
	platVec.push_back(new ComplexPlatform(world, &window, b2Vec2(0, 200), verts, 3, b2_staticBody, 1));

	b2Vec2* verts2 = new b2Vec2[4];
	verts2[0] = b2Vec2(0, 25);
	verts2[1] = b2Vec2(25, 50);
	verts2[2] = b2Vec2(50, 25);
	verts2[3] = b2Vec2(25, 0);
	platVec.push_back(new ComplexPlatform(world, &window, b2Vec2(600, 200), verts2, 4, b2_staticBody, 1));

	//define world step variables
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float32 slowTimeStep = 1.f / 300.f;

	//sample of sfml polygon, need to figure out how to make an accurate box2d collider with it
	/*sf::ConvexShape polygon;
	polygon.setPointCount(4);
	polygon.setPoint(0, sf::Vector2f(0, 0));
	polygon.setPoint(1, sf::Vector2f(0, 10));
	polygon.setPoint(2, sf::Vector2f(12.5f, 30));
	polygon.setPoint(3, sf::Vector2f(25, 5));
	polygon.setOutlineColor(sf::Color::Red);
	polygon.setOutlineThickness(5);
	polygon.setPosition(10, 20);*/
	
	// Start the game loop
	while (window.isOpen())
	{
		//update the physics world, slow simulation by holding the 'Q' key
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			world->Step(slowTimeStep, velocityIterations, positionIterations);
		else
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
		camera->MoveCamera(&player);
		//camera->SoftFollowPlayer(&player);
		player.Update();

		//draw gameobjects to screen
		for (int i = 0; i < platVec.size(); i++) {
			platVec[i]->Draw(camera->origin);
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
		player.Draw(camera->origin);

		// Update the window
		window.display();
	}

	//clean up memory
	for (int i = 0; i < platVec.size(); i++) {
		delete platVec[i];
	}
	delete world;
	//delete cameraOrigin;

    return 0;
}


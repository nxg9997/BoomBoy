// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;



//main function
int main()
{
	//read level data from file
	json leveldata = Helper::ReadFile("output.json");

	//set game variables
	b2World* world = new b2World(b2Vec2(0,25));
	std::vector<Platform*> platVec;
	Camera* camera = Camera::GetInstance();

	//visualize mouse click
	sf::Vector2f mouseClick(0, 0);
	sf::CircleShape mouseCircle(2.5f);
	mouseCircle.setFillColor(sf::Color::Cyan);


	// Create the main window
	sf::RenderWindow window(sf::VideoMode(SFML_WIDTH, SFML_HEIGHT), "BoomBoy (Dev)");
	window.setFramerateLimit(60);

	sf::Texture rockTex;
	if (!rockTex.loadFromFile("rock_tex.png"))
	{
		cout << "error reading rock texture" << endl;
		return 1;
	}
	else rockTex.setRepeated(true);

	sf::Texture bg;
	if (!bg.loadFromFile("bg.png"))
	{
		cout << "error reading bg texture" << endl;
		return 1;
	}

	//define player and create basic environment
	#if USE_REL:
		Player player(world, &window, b2Vec2(SFML_WIDTH * PLAYER_X_REL, SFML_HEIGHT * PLAYER_Y_REL), b2Vec2(10,10), 1);
	#else:
		Player player(world, &window, b2Vec2(leveldata["player"]["x"], leveldata["player"]["y"]), b2Vec2(10, 10), 1);
	#endif

	camera->SetOrigin(&player);
	Snow snow(&player, &window);
	/*platVec.push_back(new Platform(world, &window, b2Vec2(0, 500), b2Vec2(1280, 50), b2_staticBody, 0));//gnd
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 0), b2Vec2(50, 720), b2_staticBody, 0));//left
	platVec.push_back(new Platform(world, &window, b2Vec2(1230, 0), b2Vec2(50, 720), b2_staticBody, 0));//right
	platVec.push_back(new Platform(world, &window, b2Vec2(0, 0), b2Vec2(1280, 50), b2_staticBody, 0));//top
	platVec.push_back(new Platform(world, &window, b2Vec2(640, 360), b2Vec2(50, 720), b2_staticBody, 0));//mid*/

	//define triangle shape
	/*b2Vec2* verts = new b2Vec2[3];
	verts[0] = b2Vec2(0, 0);
	verts[1] = b2Vec2(0, 50);
	verts[2] = b2Vec2(100, 10);
	platVec.push_back(new ComplexPlatform(world, &window, b2Vec2(0, 200), verts, 3, b2_staticBody, 1));

	b2Vec2* verts2 = new b2Vec2[4];
	verts2[0] = b2Vec2(0, 25);
	verts2[1] = b2Vec2(25, 50);
	verts2[2] = b2Vec2(50, 25);
	verts2[3] = b2Vec2(25, 0);
	platVec.push_back(new ComplexPlatform(world, &window, b2Vec2(600, 200), verts2, 4, b2_staticBody, 1));*/

	//create platforms using level data json
	for (int i = 0; i < leveldata["platforms"].size(); i++) {
		if (leveldata["platforms"][i]["type"] == 0) {
			Platform* p = new Platform(world, &window, b2Vec2(leveldata["platforms"][i]["position"]["x"], leveldata["platforms"][i]["position"]["y"]), b2Vec2(leveldata["platforms"][i]["size"]["x"], leveldata["platforms"][i]["size"]["y"]), b2_staticBody, 1);
			p->SetTexture(&rockTex);
			platVec.push_back(p);

		}
		elif(leveldata["platforms"][i]["type"] == 1) {
			b2Vec2* vertices = new b2Vec2[leveldata["platforms"][i]["vertices"].size()];
			for (int j = 0; j < leveldata["platforms"][i]["vertices"].size(); j++) {
				vertices[j] = b2Vec2(leveldata["platforms"][i]["vertices"][j]["x"], leveldata["platforms"][i]["vertices"][j]["y"]);
			}
			ComplexPlatform* p = new ComplexPlatform(world, &window, b2Vec2(leveldata["platforms"][i]["position"]["x"], leveldata["platforms"][i]["position"]["y"]), vertices, leveldata["platforms"][i]["vertices"].size(), b2_staticBody, 1);
			p->SetTexture(&rockTex);
			platVec.push_back(p);
		}
	}
	//define world step variables
	float32 timeStep = 1.0f / 60.f;
	int32 velocityIterations = 100;
	int32 positionIterations = 80;

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

	sf::RectangleShape bgRect;
	bgRect.setOrigin(0, 0);
	bgRect.setSize(sf::Vector2f(SFML_WIDTH, SFML_HEIGHT));
	bgRect.setTexture(&bg, false);

	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);

	//determine framerate
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	float elapsed = 0;
	int frameCount = 0;
	int fps = 0;
	
	// Start the game loop
	while (window.isOpen())
	{
		//determine framerate
		frameCount++;
		end = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		//std::cout << elapsed << std::endl;
		if (elapsed >= 1000000000) {
			elapsed = 0;
			fps = (float)frameCount / 1.f;
			std::cout << "FPS: " << fps << std::endl;
			frameCount = 0;
			begin = std::chrono::steady_clock::now();
		}

		bool doSlow = false;
		//cout << world->GetBodyCount() << endl;
		/*for (int i = 1; i < world->GetBodyCount(); i++) {
			//cout << (player.body->GetPosition() - world->GetBodyList()[i].GetPosition()).Length() << endl;
			if ((player.body->GetPosition() - world->GetBodyList()[i].GetPosition()).Length() < 2000) {
				doSlow = true;
				//cout << "slowing" << endl;
			}
		}*/
		
		//update the physics world, slow simulation by holding the 'Q' key
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || doSlow) {
			world->Step(slowTimeStep, velocityIterations, positionIterations);
		}
		else {
			world->Step(timeStep, velocityIterations, positionIterations);
			world->Step(timeStep, velocityIterations, positionIterations);
		}

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}

		//clear the window
		window.clear(CLEAR_COLOR);

		window.draw(bgRect);
		
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

		//window.draw(mouseCircle);
		player.Draw(camera->origin);
		snow.Update();

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


#include "stdafx.h"
#include "Snow.h"


Snow::Snow(Player* p, sf::RenderWindow* win)
{
	window = win;
	player = p;
	playerInitY = p->body->GetPosition().y;
	srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	for (int i = 0; i < flakeCount; i++) {
		//std::cout << "rgen: " << rand() % 20 << std::endl;
		flakes.push_back(new b2Vec2(rand() % SFML_WIDTH, rand() % SFML_HEIGHT));
		std::cout << flakes[i]->x << " " << flakes[i]->y << std::endl;
	}
}


Snow::~Snow()
{
	for (int i = 0; i < flakes.size(); i++) {
		//std::cout << "rgen: " << rand() % 20 << std::endl;
		delete flakes[i];
	}
}

void Snow::Update()
{
	b2Vec2 vel(-5, 5);
	vel.Normalize();
	vel = Helper::SetVecMagnitude(vel, minVel);
	for (int i = 0; i < flakeCount; i++) {
		(*flakes[i]) += vel;
		if (flakes[i]->x < 0) {
			flakes[i]->x = SFML_WIDTH;
		}
		if (flakes[i]->y > SFML_HEIGHT) {
			flakes[i]->y = 0;
		}

		sf::CircleShape circle(2.f);
		circle.setFillColor(sf::Color::White);
		circle.setPosition(flakes[i]->x, flakes[i]->y);
		window->draw(circle);
	}

	int distance = 100 - (int)Helper::Map(player->body->GetPosition().y, 0, playerInitY, 0, 100);
	//std::cout << "dist: " << distance << std::endl;
	if (distance > 80) {
		flakeCount = 100;
	}
	elif (distance > 60) {
		flakeCount = 75;
	}
	elif (distance > 40) {
		flakeCount = 50;
	}
	elif(distance > 20) {
		flakeCount = 25;
	}
	else {
		flakeCount = 5;
	}

	UpdateFlakeVector();
}

void Snow::UpdateFlakeVector()
{
	if (flakes.size() < flakeCount) {
		int num = flakeCount - flakes.size();
		for (int i = 0; i < num; i++) {
			flakes.push_back(new b2Vec2(rand() % SFML_WIDTH, rand() % SFML_HEIGHT));
		}
	}
	/*else if (flakes.size() > flakeCount) {
		int num = flakes.size() - flakeCount;
		for (int i = 0; i < num; i++) {
			b2Vec2* f = flakes[flakes.size() - i - 1];
			flakes.pop_back();
			delete f;
		}
	}*/
}

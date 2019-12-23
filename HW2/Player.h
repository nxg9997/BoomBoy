#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player(b2World* _world, sf::RenderWindow* _win, b2Vec2 _pos, b2Vec2 _size, float _density);
	~Player();

	float moveForce = 100;
	float minBoom = 1500;
	float maxBoom = 20000;
	bool isInput = false;
	bool prevInput = false;
	bool prevSpace = false;
	b2Vec2 prevPos;

	void HandleInput();

	void Boom(b2Vec2 force);

	void Update();

};


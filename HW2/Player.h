#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player(b2World* _world, sf::RenderWindow* _win, b2Vec2 _pos, b2Vec2 _size, float _density);
	~Player();

	//player data
	float moveForce = 100;
	float minBoom = 1500;
	float maxBoom = 20000;
	bool isInput = false;
	bool prevInput = false;
	bool prevSpace = false;
	bool mouseHeld = false;
	bool prevMouseClicked = false;
	b2Vec2 prevPos;
	b2Vec2 prevMousePos = b2Vec2(0, 0);
	float launchIncrement = 200;
	float currLaunchPower = 0;
	b2Vec2 initPos = b2Vec2(0,0);

	//reticle data
	sf::Color retColor = sf::Color::Cyan;
	float retRadius = 5.f;
	b2Vec2 retPos = b2Vec2(20, 0);
	bool drawRet = false;

	void HandleInput();
	void CreateBoom();

	void Boom(b2Vec2 force);

	void MoveRet();

	void Update();

	void Draw(b2Vec2* origin) override;
};


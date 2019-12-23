#pragma once
#include "stdafx.h"
class GameObject
{
public:
	GameObject(b2World* _world, sf::RenderWindow* _win, b2Vec2 _pos, b2Vec2 _size, b2BodyType _type, float _density, sf::Color _color, float friction);
	~GameObject();

	//game data
	sf::RenderWindow* window;
	b2World* world;
	b2Vec2* cam = nullptr;

	//gameobject data
	b2Body* body;
	b2Vec2* size;
	sf::Color color;

	void Draw(b2Vec2* origin);

};


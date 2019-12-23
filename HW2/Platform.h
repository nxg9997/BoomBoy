#pragma once
#include "GameObject.h"
class Platform :
	public GameObject
{
public:
	Platform(b2World* _world, sf::RenderWindow* _win, b2Vec2 _pos, b2Vec2 _size, b2BodyType _type, float _density);
	~Platform();
};


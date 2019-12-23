#pragma once
#include "Platform.h"
class ComplexPlatform :
	public Platform
{
public:
	ComplexPlatform(b2World* _world, sf::RenderWindow* _win, b2Vec2 _pos, b2Vec2* _verts, int vertCount, b2BodyType _type, float _density);
	~ComplexPlatform();

	b2Vec2* verticies;
	int vertCount = 0;

	void Draw(b2Vec2* origin) override;
};


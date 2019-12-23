#include "stdafx.h"
#include "Platform.h"

Platform::Platform(b2World * _world, sf::RenderWindow * _win, b2Vec2 _pos, b2Vec2 _size, b2BodyType _type, float _density = 1.0f):GameObject(_world, _win, _pos, _size, _type, _density, sf::Color::Blue,.3)
{
}

Platform::Platform():GameObject()
{
}

Platform::~Platform()
{
}

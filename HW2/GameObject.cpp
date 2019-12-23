#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(b2World * _world, sf::RenderWindow * _win, b2Vec2 _pos, b2Vec2 _size, b2BodyType _type, float _density=1.0f, sf::Color _color=sf::Color::Green, float friction=0)
{
	world = _world;
	window = _win;
	size = new b2Vec2(_size.x, _size.y);
	_pos.x += size->x/2;
	_pos.y += size->y/2;
	body = Helper::CreateBody(world, _pos, _size, _type, _density,friction);
	color = _color;
}

GameObject::~GameObject()
{
	delete size;
}

void GameObject::Draw(b2Vec2* origin)
{
	if (cam == nullptr) {
		cam = origin;
	}
	sf::RectangleShape shape(Helper::B2Vec2ToSfVec2(*size));
	shape.setFillColor(color);
	shape.setPosition(sf::Vector2f(body->GetPosition().x - size->x/2 + origin->x, body->GetPosition().y - size->y/2 + origin->y));
	window->draw(shape);
}
#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(b2World * _world, sf::RenderWindow * _win, b2Vec2 _pos, b2Vec2 _size, b2BodyType _type, float _density=1.0f, sf::Color _color=sf::Color::Green, float friction=0)
{
	world = _world;
	window = _win;
	size = new b2Vec2(_size.x, _size.y);

	//correct for box2d -> sfml coordinate conversion
	_pos.x += size->x/2;
	_pos.y += size->y/2;

	body = Helper::CreateBody(world, _pos, _size, _type, _density,friction);
	color = _color;
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	delete size;
}

void GameObject::Draw(b2Vec2* origin)
{
	//set the camera position if its not already set
	if (cam == nullptr) {
		cam = origin;
	}

	sf::RectangleShape shape(Helper::B2Vec2ToSfVec2(*size));
	if (texture == nullptr) {
		shape.setFillColor(color);
	}
	else {
		shape.setTexture(texture,false);
		//shape.setTextureRect(sf::IntRect(0, 0, 50, 50));
	}
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1);
	shape.setPosition(sf::Vector2f(body->GetPosition().x - size->x/2 + origin->x, body->GetPosition().y - size->y/2 + origin->y));
	window->draw(shape);
}

void GameObject::SetTexture(sf::Texture * tex)
{
	texture = tex;
}

#include "stdafx.h"
#include "ComplexPlatform.h"


ComplexPlatform::ComplexPlatform(b2World* _world, sf::RenderWindow* _win, b2Vec2 _pos, b2Vec2* _verts, int _vertCount, b2BodyType _type, float _density):Platform()
{
	world = _world;
	window = _win;

	b2Vec2 min(0, 0);
	b2Vec2 max(0, 0);
	for (int i = 0; i < _vertCount; i++) {
		if (_verts[i].x < min.x) min.x = _verts[i].x;
		else if (_verts[i].x > max.x) max.x = _verts[i].x;
		if (_verts[i].y < min.y) min.y = _verts[i].y;
		else if (_verts[i].y > max.y) max.y = _verts[i].y;
	}
	size = new b2Vec2(max.x - min.x, max.y - min.y);
	//std::cout << size->y << std::endl;

	verticies = _verts;
	vertCount = _vertCount;

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = _type;
	bodyDef.position.Set(_pos.x, _pos.y);
	b2Body* _body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.Set(verticies, _vertCount);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = _density;

	// Override the default friction.
	fixtureDef.friction = .3;

	// Add the shape to the body.
	_body->CreateFixture(&fixtureDef);

	body = _body;
}


ComplexPlatform::~ComplexPlatform()
{
	delete[] verticies;
}

void ComplexPlatform::Draw(b2Vec2* origin)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertCount);

	for (int i = 0; i < vertCount; i++) {
		polygon.setPoint(i, sf::Vector2f(verticies[i].x, verticies[i].y));
	}
	if (texture == nullptr)
		polygon.setFillColor(sf::Color::Blue);
	else {
		polygon.setTexture(texture);
		//polygon.setTextureRect(sf::IntRect(0, 0, 50, 50));
	}
	polygon.setOutlineColor(sf::Color::Green);
	polygon.setOutlineThickness(1);
	polygon.setPosition(sf::Vector2f(body->GetPosition().x + origin->x, body->GetPosition().y + origin->y));
	window->draw(polygon);
}

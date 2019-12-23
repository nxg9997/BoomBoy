#include "stdafx.h"
#include "Helper.h"


Helper::Helper()
{
}


Helper::~Helper()
{
}



b2Body * Helper::CreateBody(b2World * world, b2Vec2 position, b2Vec2 size, b2BodyType type, float density=1.0f, float friction=0)
{
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x/2, size.y/2);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = density;

	// Override the default friction.
	fixtureDef.friction = friction;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	return body;
}

sf::Vector2f Helper::B2Vec2ToSfVec2(b2Vec2 b2vec)
{
	return sf::Vector2f(b2vec.x, b2vec.y);
}

b2Vec2 Helper::SfVec2ToB2Vec2(sf::Vector2f sfvec)
{
	return b2Vec2(sfvec.x,sfvec.y);
}

b2Vec2 Helper::SetVecMagnitude(b2Vec2 vec, float length)
{
	b2Vec2 result(vec);
	result.Normalize();
	result.x *= length;
	result.y *= length;
	return result;
}

b2Vec2 Helper::FlipY(b2Vec2 vec)
{
	return b2Vec2(vec.x, -vec.y);
}

sf::Vector2f Helper::FlipY(sf::Vector2f vec)
{
	return sf::Vector2f(vec.x, -vec.y);
}

b2Vec2 Helper::GetMouse(sf::RenderWindow* window)
{
	return SfVec2ToB2Vec2(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y) - sf::Vector2f(window->getPosition().x, window->getPosition().y));
}

float Helper::Map(float input, float input_start, float input_end, float output_start, float output_end)
{
	float output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
	return output;
}

b2Vec2 Helper::ClampMagnitude(b2Vec2 vec, float length)
{
	if (vec.Length() > length) {
		vec.Normalize();
		vec *= length;
	}
	return vec;
}

b2Vec2 Helper::Seek(b2Vec2 pos, b2Vec2 target)
{
	b2Vec2 result(0, 0);

	result = target - pos;

	return result;
}

b2Vec2 Helper::RotateVector(b2Vec2 vec, float angle)
{
	float x_rotated = cos(angle) * vec.x - sin(angle) * vec.y;
	float y_rotated = sin(angle) * vec.x + cos(angle) * vec.y;
	return b2Vec2(x_rotated, y_rotated);
}

json Helper::ReadFile(std::string path)
{
	json result;

	//read file from path
	std::ifstream input(path, std::ios::binary);
	input.seekg(0, std::ios::end);
	int len = (int)input.tellg();
	input.seekg(0, std::ios::beg);
	char* data = new char[len + 1];
	input.read(data, len);
	data[len] = 0;
	input.close();

	//parse data to json
	result = json::parse(std::string(data));

	return result;
}

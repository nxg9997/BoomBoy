#pragma once
#include "stdafx.h"
static class Helper
{
public:
	Helper();
	~Helper();


	static b2Body* CreateBody(b2World* world, b2Vec2 position, b2Vec2 size, b2BodyType type, float density, float friction);
	static sf::Vector2f B2Vec2ToSfVec2(b2Vec2 b2vec);
	static b2Vec2 SfVec2ToB2Vec2(sf::Vector2f sfvec);
	static b2Vec2 SetVecMagnitude(b2Vec2 vec, float length);
	static b2Vec2 FlipY(b2Vec2 vec);
	static sf::Vector2f FlipY(sf::Vector2f vec);
	static b2Vec2 GetMouse(sf::RenderWindow* window);
	static float Map(float input, float input_start, float input_end, float output_start, float output_end);
	static b2Vec2 ClampMagnitude(b2Vec2 vec, float length);
	static b2Vec2 Seek(b2Vec2 pos, b2Vec2 target);
	static b2Vec2 RotateVector(b2Vec2 vec, float angle);
	static nlohmann::json ReadFile(std::string path);
};


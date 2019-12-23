#pragma once
class Camera
{
private:
	Camera();
	~Camera();
	static Camera* instance;

public:
	static Camera* GetInstance();

	//camera data
	b2Vec2* origin;
	b2Vec2* acceleration;
	b2Vec2* velocity;
	float maxSpeed = 2;
	float distanceFromPlayer = 300;
	b2Vec2 distFromPlayerVec;

	void MoveCamera();
	void MoveCamera(Player* p);
	void SoftFollowPlayer(Player* p);
};




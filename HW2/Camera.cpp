#include "stdafx.h"
#include "Camera.h"

Camera* Camera::instance = 0;

Camera::Camera()
{
	origin = new b2Vec2(0, 0);
	acceleration = new b2Vec2(0, 0);
	velocity = new b2Vec2(0, 0);
	distFromPlayerVec = b2Vec2(100, 50);
}


Camera::~Camera()
{
	delete origin;
}

Camera * Camera::GetInstance()
{
	if (!instance) {
		instance = new Camera;
	}
	return instance;
}

//move camera with arrow keys
void Camera::MoveCamera() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		origin->x += 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		origin->x -= 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		origin->y += 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		origin->y -= 10;
	}
}

//stuck to player
void Camera::MoveCamera(Player* p) {
	origin->x -= p->body->GetPosition().x - p->prevPos.x;
	origin->y -= p->body->GetPosition().y - p->prevPos.y;
}

void Camera::SoftFollowPlayer(Player * p)
{
	/*velocity->x = 0;
	velocity->y = 0;*/
	/*if ((*velocity).Length() > 0) {
		*velocity *= 0.5;
	}*/

	//convert to player position to screenspace
	b2Vec2 screenPos(p->body->GetPosition().x - p->size->x / 2 + origin->x, p->body->GetPosition().y - p->size->y / 2 + origin->y);

	std::cout << (b2Vec2(SFML_WIDTH / 2, SFML_HEIGHT / 2) - screenPos).Length() << std::endl;

	
	//check if the distance from the player is less than a certain amount
	if ((b2Vec2(SFML_WIDTH / 2, SFML_HEIGHT / 2) - screenPos).Length() < distanceFromPlayer) return;

	//create and apply the steering force
	b2Vec2 force = Helper::Seek(p->body->GetPosition(), b2Vec2(SFML_WIDTH / 2, SFML_HEIGHT / 2));
	force = Helper::ClampMagnitude(force, maxSpeed);
	*origin += force;
	

	/*b2Vec2 distVec = b2Vec2(SFML_WIDTH / 2, SFML_HEIGHT / 2) - screenPos;
	b2Vec2 force(0, 0);

	if (abs(distVec.y) > distFromPlayerVec.y) {
		force.y = p->body->GetPosition().y - (SFML_HEIGHT / 2);
	}
	if (abs(distVec.x) > distFromPlayerVec.x) {
		force.x = p->body->GetPosition().x - (SFML_WIDTH / 2);
	}

	*acceleration -= force;
	*velocity += *acceleration;
	*velocity = Helper::ClampMagnitude(*velocity, maxSpeed);

	*origin += *velocity;

	acceleration->x = 0;
	acceleration->y = 0;*/
}

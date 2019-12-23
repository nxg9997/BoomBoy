#include "stdafx.h"
#include "Player.h"


Player::Player(b2World* _world, sf::RenderWindow* _win, b2Vec2 _pos, b2Vec2 _size, float _density = 1.0f):GameObject(_world, _win, _pos, _size, b2_dynamicBody, _density, sf::Color::Red,.3)
{
	prevPos = b2Vec2(body->GetPosition().x, body->GetPosition().y);
}


Player::~Player()
{
}

void Player::HandleInput()
{
	//was the player in control last frame?
	prevInput = isInput;
	isInput = false;

	//check keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		body->ApplyForceToCenter(b2Vec2(0, -moveForce), true);
		isInput = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		body->ApplyForceToCenter(b2Vec2(-moveForce, 0), true);
		isInput = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		isInput = true;
		body->ApplyForceToCenter(b2Vec2(0, moveForce), true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		body->ApplyForceToCenter(b2Vec2(moveForce, 0), true);
		isInput = true;
	}

	//if the player is in control, limit the player velocity
	if (isInput && prevInput) body->SetLinearVelocity(Helper::SetVecMagnitude(body->GetLinearVelocity(), 20));

	//only allow jumping if the button is tapped and not held
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !prevSpace) {
		body->ApplyLinearImpulseToCenter(b2Vec2(0, -20000), true);
		//isInput = true;
		prevSpace = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		prevSpace = false;
	}

	//check if the mouse is clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		b2Vec2 bForce(0,0);
		b2Vec2 mousePos = Helper::GetMouse(window);
		mousePos.x -= cam->x + size->x;
		mousePos.y -= cam->y + size->y;
		//std::cout << "Mouse Pos: " << mousePos.x << ", " << mousePos.y << std::endl;
		bForce = body->GetPosition() - mousePos;
		Boom(bForce);
	}
}

void Player::Boom(b2Vec2 force)
{
	//apply explosive force to the player based on the mouse click
	if (body->GetLinearVelocity().Length() > -b2_epsilon && body->GetLinearVelocity().Length() < b2_epsilon) {
		force = Helper::ClampMagnitude(force, 300);
		force = Helper::SetVecMagnitude(force, Helper::Map(300 - force.Length(), 0, 100, minBoom, maxBoom));
		//std::cout << "Boom Force: " << force.Length() << std::endl;
		body->ApplyLinearImpulseToCenter(force, true);
	}
	
}

void Player::Update()
{
	//update the previous position before modifying the current position
	prevPos = b2Vec2(body->GetPosition().x, body->GetPosition().y);

	//check input
	HandleInput();

	//if the player was in control and is no longer in control, stop them from moving
	if(!isInput && prevInput) body->SetLinearVelocity(b2Vec2(0, 0));

	std::cout << "Player Position: { " << body->GetPosition().x << ", " << body->GetPosition().y << " }" << std::endl;
}

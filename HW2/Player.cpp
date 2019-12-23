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

}

void Player::CreateBoom()
{
	//check if the mouse was released
	/*if (mouseHeld && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		b2Vec2 bForce(0, 0);
		b2Vec2 mousePos = Helper::GetMouse(window);
		mousePos.x -= cam->x + size->x;
		mousePos.y -= cam->y + size->y;
		//std::cout << "Mouse Pos: " << mousePos.x << ", " << mousePos.y << std::endl;
		bForce = body->GetPosition() - mousePos;
		Boom(bForce);
	}*/

	//use retpos instead of mouse
	if (mouseHeld && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		b2Vec2 bForce(0, 0);
		//std::cout << "Mouse Pos: " << mousePos.x << ", " << mousePos.y << std::endl;
		bForce = body->GetPosition() - (retPos + body->GetPosition());
		Boom(bForce);
	}
}

void Player::Boom(b2Vec2 force)
{
	//apply explosive force to the player based on the mouse click
	if (body->GetLinearVelocity().Length() > -b2_epsilon && body->GetLinearVelocity().Length() < b2_epsilon) {
		force = Helper::ClampMagnitude(force, 20000);
		//force = Helper::SetVecMagnitude(force, Helper::Map(300 - force.Length(), 0, 100, minBoom, maxBoom)); //for use with the mouse launch
		force = Helper::SetVecMagnitude(force, currLaunchPower);
		//std::cout << "Boom Force: " << force.Length() << std::endl;
		body->ApplyLinearImpulseToCenter(force, true);
		currLaunchPower = 0;
	}
	
}

void Player::MoveRet()
{
	//std::cout << (retPos.x + body->GetPosition().x) << std::endl;
	retPos = Helper::RotateVector(retPos, (Helper::GetMouse(window).x - prevMousePos.x) * b2_pi / 180);
}

void Player::Update()
{
	//update the previous position before modifying the current position
	prevPos = b2Vec2(body->GetPosition().x, body->GetPosition().y);

	//check input
	HandleInput();
	CreateBoom();


	//check if the mouse is being held or not
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (prevMouseClicked) mouseHeld = true;
		prevMouseClicked = true;
	}
	else {
		prevMouseClicked = false;
		mouseHeld = false;
	}

	//while he left click is held
	if (mouseHeld && (body->GetLinearVelocity().Length() > -b2_epsilon && body->GetLinearVelocity().Length() < b2_epsilon)) {
		//rotate the reticle with the mouse's horizontal movement
		MoveRet();
		drawRet = true;

		//increase the launch power while the right click is held
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			currLaunchPower += launchIncrement;
			//std::cout << currLaunchPower << std::endl;
		}
	}
	else drawRet = false;
	prevMousePos = Helper::GetMouse(window);

	//if the player was in control and is no longer in control, stop them from moving
	if(!isInput && prevInput) body->SetLinearVelocity(b2Vec2(0, 0));

	//std::cout << "Player Position: { " << body->GetPosition().x << ", " << body->GetPosition().y << " }" << std::endl;
}

void Player::Draw(b2Vec2 * origin)
{
	GameObject::Draw(origin);

	if (!drawRet) return;

	sf::CircleShape shape(retRadius);
	shape.setFillColor(retColor);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1);
	shape.setPosition(sf::Vector2f(body->GetPosition().x - size->x / 2 + origin->x + retPos.x, body->GetPosition().y - size->y / 2 + origin->y + retPos.y));
	window->draw(shape);

	float radius = 100 - Helper::Map(currLaunchPower < maxBoom ? currLaunchPower : maxBoom, 0, maxBoom, 0, 100);
	sf::CircleShape shape2(radius);
	shape2.setFillColor(sf::Color::Transparent);
	shape2.setOutlineColor(sf::Color(255,0,0,255 - Helper::Map(radius, 0, 100, 0, 255)));
	shape2.setOutlineThickness(2);
	shape2.setPosition(sf::Vector2f(body->GetPosition().x - size->x / 2 + origin->x + retPos.x - radius + retRadius, body->GetPosition().y - size->y / 2 + origin->y + retPos.y - radius + retRadius));
	window->draw(shape2);
}

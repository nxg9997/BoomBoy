#pragma once
class Snow
{
public:
	Snow(Player* p, sf::RenderWindow* win);
	~Snow();
	void Update();
	void UpdateFlakeVector();

	
	float minVel = 5;
	float velRng = 5;
	int flakeCount = 5;
	float playerInitY;
	Player* player = nullptr;
	sf::RenderWindow* window = nullptr;

	std::vector<b2Vec2*> flakes;
};


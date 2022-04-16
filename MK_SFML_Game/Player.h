#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	Player(std::string charName);
	~Player();

	void update() override;
	void render(sf::RenderTarget* target) override;
private:
	//inits
	void initVariables() override;
};
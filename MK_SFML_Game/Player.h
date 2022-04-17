#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	Player(std::string charName);
	~Player();
	
	//overrides
	void update() override;
	void render(sf::RenderTarget* target) override;
	
	//methods
	bool canMove();
private:
	//properties
	bool isAirborne;
	float xAxisMomentum;

	//inits
	void initVariables() override;
};
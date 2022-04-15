#pragma once
#include "GameObject.h"

class Player : GameObject {
public:
	Player();
	~Player();

	void update() override;
	void render(sf::RenderTarget* target) override;
private:
};
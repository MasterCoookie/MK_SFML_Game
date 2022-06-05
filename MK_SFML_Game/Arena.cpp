#include "Arena.h"

Arena::Arena()
{
	std::shared_ptr<sf::Texture> klocek = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> lewyHak = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> prawyHak = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> head = std::make_shared<sf::Texture>();
	if (!klocek->loadFromFile("./Textures/klocek.png")) {
		std::cout << "ERR: ARENA::INITTEXTURE: Could not load klocek file" << std::endl;
	}
	if (!lewyHak->loadFromFile("./Textures/hak_l.png")) {
		std::cout << "ERR: ARENA::INITTEXTURE: Could not load klocek file" << std::endl;
	}
	if (!prawyHak->loadFromFile("./Textures/hak_p.png")) {
		std::cout << "ERR: ARENA::INITTEXTURE: Could not load klocek file" << std::endl;
	}
	if (!head->loadFromFile("./Textures/leb.png")) {
		std::cout << "ERR: ARENA::INITTEXTURE: Could not load klocek file" << std::endl;
	}
	this->vectorOfElements.push_back(std::make_unique<BackgroundElement>(klocek, 788, 768));
	this->vectorOfElements.push_back(std::make_unique<BackgroundElement>(klocek, 1661, 772));
	this->vectorOfElements.push_back(std::make_unique<BackgroundElement>(klocek, 2434,773 ));
	this->vectorOfElements.push_back(std::make_unique<BackgroundElement>(lewyHak, 48, -19));
	this->vectorOfElements.push_back(std::make_unique<BackgroundElement>(prawyHak, 2326, -17));
	this->vectorOfElements.push_back(std::make_unique<BackgroundElement>(head, 0, 645));
}

void Arena::render(std::shared_ptr<sf::RenderTarget> win)
{
	for (auto& it : vectorOfElements) {
		it->render(win);
	}
}



void Arena::reset()
{
	for (auto& it : vectorOfElements) {
		it->reset();
	}
}

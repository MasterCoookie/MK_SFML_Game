#include "SceneWelcomeScreen.h"

SceneWelcomeScreen::SceneWelcomeScreen() {}
SceneWelcomeScreen::SceneWelcomeScreen(sf::RenderWindow* win)
{
	this->window = win;
	this->setCurrentSeconds(0.f);
	this->setShowForSeconds(5.f); //initialize for how long the loading screen should display
	this->initTexture("load.png"); //loading screen
	this->setOverTime(false); //initialize the flag 
}
;

SceneWelcomeScreen::~SceneWelcomeScreen() {};

void SceneWelcomeScreen::run() {
	//UNCOMMENT TO DISPLAY LOADING SCREEN!
	while (!this->overTime && this->window->isOpen()) { 
		this->pollEvents();
		this->update();
		this->render();
	}
};

std::vector<std::string> SceneWelcomeScreen::getResult() {
	std::vector<std::string> vec; //returns nothing, no need to pass any parameters beetwen scene loading screen and rest of the programme
	return vec; 
}
void SceneWelcomeScreen::setInterSceneValues(std::vector<std::string>& vec)
{
};

void SceneWelcomeScreen::pollEvents() {
	sf::Event e;
	while (this->window->pollEvent(e)) {
		//red cross clicked
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		//were keys pressed?
		else if (e.Event::KeyPressed) {
			//escape button
			if (e.Event::key.code == sf::Keyboard::Escape) {
				this->window->close();
			}			
			else if (e.Event::key.code == sf::Keyboard::LShift) {
				this->setOverTime(true);
			}
		}
	}
};

void SceneWelcomeScreen::update() {
	this->currentSeconds += 0.03;
	if (this->currentSeconds > this->showForSeconds) {
		this->setOverTime(true);
	}
};

void SceneWelcomeScreen::render() {
	this->window->clear();
	this->window->draw(this->loadingScreenSprite);
	this->window->display();
}
void SceneWelcomeScreen::initTexture(std::string textureName)
{
	this->loadingScreenTexture = std::make_unique<sf::Texture>();
	if (!this->loadingScreenTexture->loadFromFile("./Textures/" + textureName)) {
		std::cout << " ! ERR: GAMEENGINE::INITWORLD: could not load laod img" << std::endl;
	}
	//set load to loaded texture
	this->loadingScreenSprite.setTexture(*(this->loadingScreenTexture));
}
void SceneWelcomeScreen::setCurrentSeconds(float num)
{
	this->currentSeconds = num;
}

void SceneWelcomeScreen::setShowForSeconds(float num)
{
	this->showForSeconds = num;
}

void SceneWelcomeScreen::setOverTime(bool value)
{
	this->overTime = value;
}



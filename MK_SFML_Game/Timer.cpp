#include "Timer.h"

Timer::Timer()
{
	this->initText();
}

void Timer::update(sf::Time time)
{
	int num = time.asSeconds();
	std::stringstream toset;
	toset << std::setfill('0') << std::setw(2) << num;
	std::string read;
	toset >> read;
	this->text.setString(read);
}

void Timer::render(std::shared_ptr<sf::RenderTarget> win)
{
	win->draw(this->text);
}

void Timer::move(float offsetX, float offsetY)
{
	this->text.move(offsetX, offsetY);
}

void Timer::initText()
{
	this->font = std::make_unique<sf::Font>();
	if (!this->font->loadFromFile("./Textures/arial.ttf")) {
		std::cout << "Czcionka nie wczytana";
	}
	this->text.setFont(*this->font);
	this->text.setString("00:00");
	this->text.setCharacterSize(40);
	this->text.setFillColor(sf::Color::Black);
	this->text.setStyle(sf::Text::Bold);
	this->text.setPosition(1260, 50);
}

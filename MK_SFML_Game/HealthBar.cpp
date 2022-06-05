#include "HealthBar.h"

HealthBar::HealthBar(bool isLeft, std::string name)
{
	this->isLeft = isLeft;
	this->font = std::make_unique<sf::Font>();
	if (!this->font->loadFromFile("./Textures/font.ttf")) {
		std::cout << "Czcionka nie wczytana";
	}
	this->text.setFont(*this->font);

	this->text.setString(name);
	this->text.setCharacterSize(30);
	this->text.setFillColor(sf::Color::Blue);
	this->text.setStyle(sf::Text::Bold);
	this->healthShape = std::make_unique < sf::RectangleShape>();
	this->healthShape->setFillColor(sf::Color(0, 255, 0));
	this->healthShape->setSize({ 450.f, 50.f });
	this->backgroundShape = std::make_unique < sf::RectangleShape>();
	this->backgroundShape->setFillColor(sf::Color(255,0, 0));
	this->backgroundShape->setSize({ 450.f, 50.f });
	if (this->isLeft) {
		this->healthShape->setPosition({ 730.f,50.f });
		this->backgroundShape->setPosition({ 730.f,50.f });
		this->text.setPosition(730.f, 50);
		this->originalPos = sf::Vector2f(730.f, 50.f);
	}
	else {
		this->healthShape->setPosition({ 1380.f,50.f });
		this->backgroundShape->setPosition({ 1380.f,50.f });
		this->text.setPosition(1380+445-this->text.getLocalBounds().width, 50);
		this->originalPos = sf::Vector2f(1380.f, 50.f);
	}
}

void HealthBar::render(std::shared_ptr<sf::RenderTarget> win)
{
	win->draw(*(this->backgroundShape));
	win->draw(*(this->healthShape));
	win->draw(this->text);
}

void HealthBar::update(float currentHealth)
{
	if (currentHealth > 0.0) { this->healthShape->setSize({ 450.f * currentHealth / 100,50.f }); }
	else
	{
		this->healthShape->setSize({ 0 / 100,50.f });
	}
	if (this->isLeft) {}
	else {
		sf::Vector2f newVec = this->originalPos;
		newVec.x += 450.f-450.f * currentHealth / 100.f;
		this->healthShape->setPosition(newVec);
	}
}

void HealthBar::move(float offsetX, float offsetY)
{
	this->healthShape->move(offsetX, offsetY);
	this->originalPos.x += offsetX;
	this->originalPos.y += offsetY;
	this->backgroundShape->move(offsetX, offsetY);
	this->text.move(offsetX, offsetY);
}

void HealthBar::reset()
{
	if (this->isLeft) {
		this->healthShape->setPosition({ 730.f,50.f });
		this->backgroundShape->setPosition({ 730.f,50.f });
		this->text.setPosition(730.f, 50);
		this->originalPos = sf::Vector2f(730.f, 50.f);
	}
	else {
		this->healthShape->setPosition({ 1380.f,50.f });
		this->backgroundShape->setPosition({ 1380.f,50.f });
		this->text.setPosition(1380 + 445 - this->text.getLocalBounds().width, 50);
		this->originalPos = sf::Vector2f(1380.f, 50.f);
	}
}

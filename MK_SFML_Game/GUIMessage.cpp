#include "GUIMessage.h"

GUIMessage::GUIMessage()
{
	this->font = new sf::Font;
	if (!this->font->loadFromFile("./Textures/arial.ttf")) {
		std::cout << "Czcionka nie wczytana";
	}
	this->text.setFont(*this->font);
	this->text.setString("");
	this->text.setCharacterSize(80);
	this->text.setFillColor(sf::Color::Blue);
	this->text.setStyle(sf::Text::Bold);
	this->text.setPosition(1280-this->text.getLocalBounds().width/2, 480-this->text.getLocalBounds().height/2);
}

void GUIMessage::move(float offsetX, float offsetY)
{
	this->text.move(offsetX, offsetY);
}

void GUIMessage::render(sf::RenderWindow* win)
{
	win->draw(this->text);
}

void GUIMessage::updateMessage(std::string msg)
{
	this->text.setString(msg);
	this->text.setPosition(1280 - this->text.getLocalBounds().width / 2, 480 - this->text.getLocalBounds().height / 2);

	//sf::FloatRect vec = this->text.getLocalBounds();

}

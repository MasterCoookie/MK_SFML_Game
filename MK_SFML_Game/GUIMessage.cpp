#include "GUIMessage.h"

GUIMessage::GUIMessage()
{
	this->font = std::make_unique<sf::Font>();
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

void GUIMessage::render(std::shared_ptr<sf::RenderTarget> win)
{
	win->draw(this->text);
}

void GUIMessage::updateMessage(std::string msg, sf::View* view)
{
	this->text.setString(msg);
	sf::Vector2f vec = view->getCenter();
	
	this->text.setPosition(vec.x - this->text.getLocalBounds().width / 2, vec.y - this->text.getLocalBounds().height / 2);

	//sf::FloatRect vec = this->text.getLocalBounds();

}

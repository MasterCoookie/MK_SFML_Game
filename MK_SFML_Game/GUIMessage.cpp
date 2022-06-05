#include "GUIMessage.h"


GUIMessage::GUIMessage()
{
	this->font = std::make_unique<sf::Font>();
	if (!this->font->loadFromFile("./Textures/font.ttf")) {
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

void GUIMessage::reset()
{
	//this->text.setPosition(1280 - this->text.getLocalBounds().width / 2, 480 - this->text.getLocalBounds().height / 2);
	//no need to reset;
}

void GUIMessage::updateMessage(std::string msg, std::shared_ptr<sf::View> view)
{
	
	sf::Vector2f vec = view->getCenter();
	std::string myString = this->transform(100, msg);
	this->text.setString(myString);
	this->text.setPosition(vec.x - this->text.getLocalBounds().width / 2, vec.y - this->text.getLocalBounds().height / 2);

	//sf::FloatRect vec = this->text.getLocalBounds();

}

std::string GUIMessage::transform(int n, std::string message)
{
	std::stringstream s;
	s << message;
	std::string newString, toReturn="";
	while (std::getline(s, newString)) {
		for (int i = 0; i < (n - newString.size()) / 2; i++) {
			toReturn += " ";
		}
		toReturn += newString;
		for (int i = 0; i < (n - newString.size()) / 2; i++) {
			toReturn += " ";
		}
		toReturn += "\n";
	}
	return toReturn;
}


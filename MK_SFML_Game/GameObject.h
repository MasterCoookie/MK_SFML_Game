#pragma once
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();

	//setters
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void move(const float x, const float y);

	//getters
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getBounds() const;
private:
	sf::Texture texture;
	sf::Sprite sprite;
	
	//inits
	void initTexture(std::string textureName);
	void initSprite();
	void initVariables();
};
#pragma once
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

	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	
	//inits
	void initTexture();
	void initSprite();
	void initVariables();
};
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

	//virtual methods
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	void initTexture(std::string texturePath);
protected:
	//inits
	
	void initTexture(sf::Texture& targetTexture, std::string texturePath);
	void initSprite();
	void initSprite(int startingX, int startingY, int sizeX, int sizeY);
	void initSprite(sf::IntRect* intRect);
	void initSprite(sf::Texture &tex, sf::IntRect* intRect);
	virtual void initVariables() = 0;

	sf::Texture texture;
	sf::IntRect* textureRect;
	sf::Sprite sprite;
private:
};
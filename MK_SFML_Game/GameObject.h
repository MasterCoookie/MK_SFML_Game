#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <ranges>
#include <thread>
#include <semaphore>
#include <memory>

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
	void setIntRect(sf::Texture& tex,const sf::IntRect rec);
	//getters
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getBounds() const;
	const sf::IntRect getIntRect() const;
	//virtual methods
	virtual void update() = 0;
	virtual void render(std::shared_ptr<sf::RenderTarget> target) = 0;

	void initTexture(std::string texturePath);
	virtual void initVariables() = 0;
protected:
	//inits
	
	void initTexture(sf::Texture& targetTexture, std::string texturePath);
	void initTexture(std::shared_ptr<sf::Texture>& targetTexture, std::string texturePath);
	void initSprite();
	void initSprite(int startingX, int startingY, int sizeX, int sizeY);
	void initSprite(std::shared_ptr<sf::IntRect> intRect);
	void initSprite(sf::Texture &tex, std::shared_ptr<sf::IntRect> intRect);
	

	std::shared_ptr<sf::Texture> texture;
	std::shared_ptr<sf::IntRect> textureRect;
	sf::Sprite sprite;
private:
};
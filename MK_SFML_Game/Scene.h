#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Scene
{
public:
	
	

	// Metoda odpowiedzialna za dzia³anie sceny
	virtual void run() = 0;
	
	// Metoda wyci¹gaj¹ca wynik ze sceny (kto wygra³ albo jakie postacie zosta³y wybrane)
	virtual std::vector<std::string> getResult() = 0;
	virtual void setInterSceneValues(std::vector<std::string>& vec) = 0 ;
	virtual void pollEvents() = 0;


	//updates
	virtual void update() = 0;



	// renders
	virtual void render() = 0;

protected:
	std::shared_ptr<sf::RenderWindow> window;
};


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
	
	

	// Metoda odpowiedzialna za dzia�anie sceny
	virtual void run() = 0;
	
	// Metoda wyci�gaj�ca wynik ze sceny (kto wygra� albo jakie postacie zosta�y wybrane)
	virtual std::vector<std::string> getResult() = 0;
	virtual void setInterSceneValues(std::vector<std::string>& vec) = 0 ;
	virtual void pollEvents() = 0;


	//updates
	virtual void update() = 0;



	// renders
	virtual void render() = 0;

private:

};


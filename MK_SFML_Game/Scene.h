#pragma once
#include <string>
class Scene
{
public:
	Scene();
	~Scene();
	

	// Metoda odpowiedzialna za dzia�anie sceny
	virtual void run() = 0;
	
	// Metoda wyci�gaj�ca wynik ze sceny (kto wygra� albo jakie postacie zosta�y wybrane)
	virtual std::string getResult() = 0;

	virtual void pollEvents() = 0;


	//updates
	virtual void update() = 0;



	// renders
	virtual void render() = 0;

private:

};


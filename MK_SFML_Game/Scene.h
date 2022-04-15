#pragma once
#include <string>
class Scene
{
public:
	
	

	// Metoda odpowiedzialna za dzia³anie sceny
	virtual void run() = 0;
	
	// Metoda wyci¹gaj¹ca wynik ze sceny (kto wygra³ albo jakie postacie zosta³y wybrane)
	virtual std::string getResult() = 0;

	virtual void pollEvents() = 0;


	//updates
	virtual void update() = 0;



	// renders
	virtual void render() = 0;

private:

};


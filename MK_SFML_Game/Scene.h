#pragma once
#include <string>
class Scene
{
public:
	Scene();
	~Scene();
	/// <summary>
	/// Metoda odpowiedzialna za dzia�anie sceny
	/// </summary>
	virtual void run() = 0;
	/// <summary>
	/// Metoda wyci�gaj�ca wynik ze sceny (kto wygra� albo jakie postacie zosta�y wybrane)
	/// </summary>
	/// <returns></returns>
	virtual std::string getResult() = 0;

private:

};


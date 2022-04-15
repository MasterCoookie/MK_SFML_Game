#pragma once
#include <string>
class Scene
{
public:
	Scene();
	~Scene();
	/// <summary>
	/// Metoda odpowiedzialna za dzia³anie sceny
	/// </summary>
	virtual void run() = 0;
	/// <summary>
	/// Metoda wyci¹gaj¹ca wynik ze sceny (kto wygra³ albo jakie postacie zosta³y wybrane)
	/// </summary>
	/// <returns></returns>
	virtual std::string getResult() = 0;

private:

};


#include "AttackMovesMatrix.h"
import FilesAndConvertions;
AttackMovesMatrix::AttackMovesMatrix(std::string charName)
{
	
	std::string s = "Characters\\"+ charName + "\\AttackMoves";
	std::filesystem::path sandbox = s;
	for (const auto& dir_entry :std::filesystem::directory_iterator{ sandbox }) {
		std::filesystem::path sandbox = dir_entry;
		std::ifstream myFile(sandbox.string());
		if (myFile.is_open()) {
			std::string key;
			myFile >> key;
			this->attackMoveMatrix.insert({ key, ReadAttackMoveFromFile(myFile, charName)});
		}	
	}
}

AttackMovesMatrix::~AttackMovesMatrix()
{

}

bool AttackMovesMatrix::doesAttackMoveExist(bool matrix[7])
{
	return this->attackMoveMatrix.find(convertBoolToString(matrix)) != this->attackMoveMatrix.end();
}

AttackMove& AttackMovesMatrix::getAttackMove(bool matrix[7])
{
	return *(this->attackMoveMatrix[convertBoolToString(matrix)]);
}



#include "AttackMovesMatrix.h"

AttackMovesMatrix::AttackMovesMatrix(std::string charName)
{
	
	std::string s = "Characters\\"+ charName + "\\AttackMoves";
	std::filesystem::path sandbox = s;
	for (const auto& dir_entry :std::filesystem::directory_iterator{ sandbox }) {
		std::filesystem::path sandbox = dir_entry;
		std::ifstream myFile(sandbox.string());
		//std::cout << myFile.is_open();
	
	}
}

AttackMovesMatrix::~AttackMovesMatrix()
{

}

bool AttackMovesMatrix::doesAttackMoveExist(bool matrix[7])
{
	return this->attackMoveMatrix.find(this->convertBoolToString(matrix)) != this->attackMoveMatrix.end();
}

AttackMove& AttackMovesMatrix::getAttackMove(bool matrix[7])
{
	return *(this->attackMoveMatrix[this->convertBoolToString(matrix)]);
}

std::string AttackMovesMatrix::convertBoolToString(bool matrix[7])
{
	std::string index = "";
	for (int i = 0; i < 7; ++i) {
		index += std::to_string(matrix[i]);
	}
	return index;
}

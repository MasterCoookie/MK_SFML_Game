#include <unordered_map>
#include <filesystem>
#include <fstream>
#include "AttackMove.h"
#pragma once

class AttackMovesMatrix
{
public:
	AttackMovesMatrix(std::string charName);
	~AttackMovesMatrix();
	void initMatrix(std::string characterName);
	bool doesAttackMoveExist(bool matrix[7]);
	AttackMove& getAttackMove(bool matrix[7]);
private:
	std::unordered_map<std::string, std::shared_ptr<AttackMove> > attackMoveMatrix;

	
};


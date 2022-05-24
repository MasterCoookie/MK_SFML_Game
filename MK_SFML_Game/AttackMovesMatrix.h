#include <unordered_map>
#include "AttackMove.h"
#pragma once
using matrix = std::unordered_map<bool, std::unordered_map<bool, std::unordered_map<bool, std::unordered_map<bool, std::unordered_map <bool, std::unordered_map<bool, std::unordered_map <bool, AttackMove*>>>>>>>;
class AttackMovesMatrix
{
public:
	AttackMovesMatrix();
	~AttackMovesMatrix();
	void initMatrix(std::string characterName);
	AttackMove& getAttackMove(bool matrix[7]);
private:
	 matrix attackMoveMatrix;
};


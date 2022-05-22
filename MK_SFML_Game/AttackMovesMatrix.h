#include <unordered_map>
#include "AttackMove.h"
#pragma once
using matrix = std::unordered_map<bool, std::unordered_map<bool, std::unordered_map<bool, std::unordered_map<bool, std::unordered_map <bool, std::unordered_map<bool, std::unordered_map <bool, AttackMove*>>>>>>>;
class AttackMovesMatrix
{
public:
	AttackMovesMatrix();
	~AttackMovesMatrix();

private:
	 matrix attackMoveMatrix;
};


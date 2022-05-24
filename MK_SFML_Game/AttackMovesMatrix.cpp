#include "AttackMovesMatrix.h"

AttackMovesMatrix::AttackMovesMatrix()
{
	//this->attackMoveMatrix[false][true][true][false][false][false][false] = new AttackMove();
}

AttackMovesMatrix::~AttackMovesMatrix()
{
	
}

AttackMove& AttackMovesMatrix::getAttackMove(bool matrix[7])
{
	return *(this->attackMoveMatrix[matrix[0]][matrix[1]][matrix[2]][matrix[3]][matrix[4]][matrix[5]][matrix[6]]);
	// // O: tu wstawiæ instrukcjê return
}

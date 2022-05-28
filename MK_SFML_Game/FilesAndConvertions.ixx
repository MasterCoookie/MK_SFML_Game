#include <string>
#include "AttackMovesMatrix.h"
export module FilesAndConvertions;

export std::string convertBoolToString(bool matrix[7]);
export AttackMove* ReadAttackMoveFromFile(std::istream& os, std::string charName);

std::string convertBoolToString(bool matrix[7])
{
	std::string index = "";
	for (int i = 0; i < 7; ++i) {
		index += std::to_string(matrix[i]);
	}
	return index;
}
AttackMove* ReadAttackMoveFromFile(std::istream& os, std::string charName)
{
	float xSize;
	float ySize;
	float yOffset;
	float xOffset;
	int knockback;
	int knockup;
	int startupTimeMax;
	int lifespanMax;
	int targetH;
	int dmg;
	int onHitStagger;
	int onBlockStagger;
	int onHitRecovery;
	int onBlockRecovery;
	int onMissRecovery;
	//std::string key;
	std::string atkTexName;
	std::string playerAtkTexName;
	os >> xSize >> ySize >> knockback >> knockup >> yOffset >> xOffset
		>> startupTimeMax
		>> lifespanMax
		>> targetH
		>> dmg
		>> onHitStagger
		>> onBlockStagger
		>> onHitRecovery
		>> onBlockRecovery
		>> onMissRecovery
		>> atkTexName
		>> playerAtkTexName;
	std::string path1 = "Characters/" + charName + "/" + atkTexName;
	std::string path2 = "Characters/" + charName + "/" + playerAtkTexName;
	sf::Texture* atkTexture = new sf::Texture;
	if (!atkTexture->loadFromFile(path1)) {
		std::cout << "ERR: ATTACKMOVE::ATKTEXTURE: Could not load texture file" << std::endl;
	}
	sf::Texture* playerAtkTexture = new sf::Texture;

	if (!playerAtkTexture->loadFromFile(path2)) {
		std::cout << "ERR: ATTACKMOVE::PLAYERATKTEXTURE: Could not load texture file" << std::endl;
	}
	AttackMove* newAttackMove = new AttackMove(xSize, ySize, atkTexture, playerAtkTexture, knockback, knockup,
		yOffset, xOffset, startupTimeMax, lifespanMax, (TargetHeight)targetH, dmg, onHitStagger, onBlockRecovery,
		onHitRecovery, onBlockRecovery, onMissRecovery);
	return newAttackMove;
}

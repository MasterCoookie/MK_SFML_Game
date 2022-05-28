#include "AttackMovesMatrix.h"

AttackMovesMatrix::AttackMovesMatrix(std::string charName)
{
	
	std::string s = "Characters\\"+ charName + "\\AttackMoves";
	std::filesystem::path sandbox = s;
	for (const auto& dir_entry :std::filesystem::directory_iterator{ sandbox }) {
		std::filesystem::path sandbox = dir_entry;
		std::ifstream myFile(sandbox.string());
		if (myFile.is_open()) {
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
			std::string key;
			std::string atkTexName;
			std::string playerAtkTexName;
			myFile >> key >> xSize >> ySize >> knockback >> knockup >> yOffset >> xOffset
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
				std::cout << "ERR: GAMEOBJECT::INITTEXTURE: Could not load texture file" << std::endl;
			}
			sf::Texture* playerAtkTexture = new sf::Texture;
			
			if (!playerAtkTexture->loadFromFile(path2)) {
				std::cout << "ERR: GAMEOBJECT::INITTEXTURE: Could not load texture file" << std::endl;
			}
			AttackMove* newAttackMove = new AttackMove(xSize, ySize, atkTexture, playerAtkTexture, knockback, knockup,
				yOffset, xOffset, startupTimeMax, lifespanMax, (TargetHeight)targetH, dmg, onHitStagger, onBlockRecovery,
				onHitRecovery, onBlockRecovery, onMissRecovery);
			this->attackMoveMatrix.insert({ key, newAttackMove });
		}
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

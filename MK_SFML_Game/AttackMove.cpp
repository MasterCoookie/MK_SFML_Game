#include "AttackMove.h"

AttackMove::AttackMove() {

}

AttackMove::AttackMove(const sf::Vector2f pos, float xSize, float ySize, bool isRightFacing, std::string charName) {
	this->initVariables();

	//USED ONLY IN DEBUG

	this->initTexture(this->atkTexture, "./Characters/" + charName + "/hand.png");
	this->initTexture(this->playerAtkTexture, "./Characters/" + charName + "/atk_1.png");
	//this->initTexture("./Characters/" + charName + "/attack.png");
	//this->sprite.setTexture(this->atkTexture);

	this->knockback = 15;
	//USED ONLY IN DEBUG ENDS

	// DO THIS IN OTHER CONSTRUCTORS TOO
	//Y axis offset is alaways the same
	this->yOffset = 60.f;

	//reverse X axis offset if player is facing left
	if (!isRightFacing) {
		this->xOffset = -130.f;
	} else {
		this->xOffset = 130.f;
	}
	
	this->shape.setPosition(pos.x + this->xOffset, pos.y + this->yOffset);

	this->sprite.setPosition(pos.x + this->xOffset, pos.y + this->yOffset);

	//reverse shape if player is facing left + reverse knockback
	if (!isRightFacing) {
		this->shape.scale(-1.f, 1.f);
		this->sprite.scale(-1.f, 1.f);
		this->knockback = -this->knockback;
	}

	// DO THIS IN OTHER CONSTRUCTORS TOO ENDS

	//USED ONLY IN DEBUG
	this->startupTimeMax = 5;
	this->lifespanMax = 4;
	this->targetH = TargetHeight::HIGH;

	this->onHitStagger = 8;
	this->onBlockStagger = 5;

	this->onHitRecovery = 3;
	this->onBlockRecovery = 2;
	this->onMissRecovery = 1;

	this->dmg = 10;
	
	this->knockup = -35;
	//USED ONLY IN DEBUG ENDS
}

AttackMove::AttackMove(float _xSize, float _ySize, sf::Texture* _atkTexture, sf::Texture* _playerAtkTexture, int _knockback, int _knockup, float _yOffset, float _xOffset, int _startupTimeMax, int _lifespanMax,
	TargetHeight _targetH, int _dmg, int _onHitStagger, int _onBlockStagger, int _onHitRecovery, int _onBlockRecovery, int _onMissRecovery) :
	atkTexture(_atkTexture), playerAtkTexture(_atkTexture), knockback(_knockback), knockup(_knockup), xOffset(_xOffset), yOffset(_yOffset), startupTimeMax(_startupTimeMax), lifespanMax(_lifespanMax), targetH(_targetH), dmg(_dmg),
	onHitStagger(_onHitStagger), onBlockStagger(_onBlockStagger), onHitRecovery(_onHitRecovery), onBlockRecovery(_onBlockRecovery), onMissRecovery(_onMissRecovery) {

}

AttackMove::AttackMove(const AttackMove& move, const sf::Vector2f _pos, bool _isRightFacing) :
	atkTexture(move.atkTexture), playerAtkTexture(move.playerAtkTexture), knockback(move.knockback), knockup(move.knockup), xOffset(move.xOffset), yOffset(move.yOffset), startupTimeMax(move.startupTime),
	lifespanMax(move.lifespanMax), targetH(move.targetH), dmg(move.dmg),
	onHitStagger(move.onHitStagger), onBlockStagger(move.onBlockStagger), onHitRecovery(move.onHitRecovery), onBlockRecovery(move.onBlockRecovery), onMissRecovery(move.onMissRecovery) {
	this->initVariables();

	this->shape.setPosition(_pos.x + this->xOffset, _pos.y + this->yOffset);

	this->sprite.setPosition(_pos.x + this->xOffset, _pos.y + this->yOffset);

	if (_isRightFacing) {
		this->shape.scale(-1.f, 1.f);
		this->sprite.scale(-1.f, 1.f);
		this->knockback = -this->knockback;
		this->xOffset = -130.f;
	}
}

AttackMove::~AttackMove() {

}

const int AttackMove::getOnHitStagger() const {
	return this->onHitStagger;
}

const int AttackMove::getOnBlockStagger() const {
	return this->onBlockStagger;
}

const float AttackMove::getRecovery() const {
	if (this->wasBlockRegistered) {
		return this->onBlockRecovery;
	} else if (this->wasHitRegistered) {
		return this->onHitRecovery;
	}
	return this->onMissRecovery;
}

const TargetHeight AttackMove::getTargetHeight() const {
	return this->targetH;
}

const int AttackMove::getDmg() const {
	return this->dmg;
}

const bool AttackMove::getWasHitRegistered() const {
	return this->wasHitRegistered;
}

const bool AttackMove::getWasBlockRegistered() const {
	return this->wasBlockRegistered;
}

const bool AttackMove::getDidMiss() const {
	return this->didMiss;
}

const int AttackMove::getKnockback() const {
	return this->knockback;
}

const int AttackMove::getAnimationLen() const {
	return this->lifespanMax+this->startupTimeMax;
}

const int AttackMove::getKnockup() const {
	return this->knockup;
}

const bool AttackMove::getIsActive() const {
	return this->isActive;
}

bool AttackMove::getHasEnded() {
	return (this->lifespan >= this->lifespanMax);
}

const sf::RectangleShape& AttackMove::getShape() const {
	return this->shape;
}

sf::Texture* AttackMove::getPlayerTexture() {
	return this->playerAtkTexture;
}

sf::Texture* AttackMove::getAtkTexture() {
	return this->atkTexture;
}

void AttackMove::throwAttack() {
	this->isActive = true;
	
}

void AttackMove::registerHit() {
	this->wasHitRegistered = true;
}

void AttackMove::registerBlock(){
	this->wasBlockRegistered = true;
}

void AttackMove::endAttack() {
	//TODO
	this->isActive = false;
}

void AttackMove::update() {
	if (!this->isActive) {
		if (!this->wasHitRegistered) {
			++this->startupTime;
		}
	} else {
		++this->lifespan;
	}
	if (this->startupTime >= this->startupTimeMax && !isActive && !this->wasHitRegistered) {
		this->throwAttack();
	}
	if (this->lifespan >= this->lifespanMax) {
		this->endAttack();
	}
}

void AttackMove::render(sf::RenderTarget* target) {
	if (this->isActive) {
		this->sprite.setTexture(*this->atkTexture);
		target->draw(this->sprite);
	}
	
}

void AttackMove::initVariables() {
	//those values are alaways the same initially
	//potentialy run only in copy constuctor
	this->startupTime = 0;
	this->lifespan = 0;
	this->wasHitRegistered = false;
	this->isActive = false;
	this->didMiss = false;
	this->wasBlockRegistered = false;
}


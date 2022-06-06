#pragma once
#include "GameObject.h"

enum class TargetHeight { LOW, MID, HIGH, OVERHEAD };

class AttackMove : public GameObject {
public:
	AttackMove();
	AttackMove(const sf::Vector2f pos, float xSize, float ySize, bool isRightFacing, std::string charName);
	//file reading constructor
	AttackMove(float _xSize, float _ySize,
		std::shared_ptr<sf::Texture> _atkTexture, std::shared_ptr<sf::Texture> _playerAtkTexture,
		int _knockback, int _knockup,
		float _xOffset, float _yOffset,
		int _startupTimeMax, int _lifespanMax,
		TargetHeight _targetH, int _dmg,
		int _onHitStagger, int _onBlockStagger, 
		float _onHitRecovery, int _onBlockRecovery, float _onMissRecovery);
	//somewhat of a copy constructor used when attack is selected
	AttackMove(const AttackMove& move, const sf::Vector2f _pos, bool _isRightFacing);
	~AttackMove();

	//accessors
	const int getOnHitStagger() const;
	const int getOnBlockStagger() const;
	const float getRecovery() const;
	const TargetHeight getTargetHeight() const;
	const int getDmg() const;
	const bool getWasHitRegistered() const;
	const bool getWasBlockRegistered() const;
	const bool getDidMiss() const;
	const int getKnockback() const;
	const int getAnimationLen() const;
	const int getKnockup() const;
	const bool getIsActive() const;
	bool getHasEnded();
	const sf::RectangleShape& getShape() const;
	std::shared_ptr<sf::Texture> getPlayerTexture();
	std::shared_ptr<sf::Texture> getAtkTexture();

	//modifiers
	

	//methods
	//startup frames ended, activates attack, can now hit oppontent
	void throwAttack();
	//on-hit
	void registerHit();
	void registerBlock();
	//active frames ended, apply recovery to player
	void endAttack();

	void update() override;

	void render(std::shared_ptr<sf::RenderTarget> win) override;

	void initVariables() override;
private:
	//properties
	// life properties
	// how long it takes for move to become active
	int startupTimeMax;
	//how many frames has the move been starting for
	// !dont read from file!
	int startupTime;
	// how long does the move stay active for
	int lifespanMax;
	// for how long has the move been active for
	// !begins to increase only after the move becomes active!
	// !dont read from file!
	int lifespan;
	
	// aimed where?
	TargetHeight targetH;

	//only after attack becomes active - true - it can now hit
	// !dont read from file!
	bool isActive;

	// stagger propertiers
	// for how long is the target going to be staggered for
	int onHitStagger;
	// for how long is the target going to be staggered for after blocking
	int onBlockStagger;

	//recoeveries
	//how long for the thrower to recover after hitting oponent
	float onHitRecovery;
	//how long for the thrower to recover after hitting blocking oponent
	int onBlockRecovery;
	//how long for the thrower to recover after missing completely
	float onMissRecovery;

	//hit
	int dmg;
	// !dont read from file!
	bool wasHitRegistered;
	// !dont read from file!
	bool wasBlockRegistered;
	// !dont read from file!
	bool didMiss;
	//xAxisMomentum, added on-hit
	int knockback;
	//yAxisMomentum, added on-hit
	int knockup;

	//offsets
	float xOffset;
	float yOffset;

	sf::RectangleShape shape;

	

	std::shared_ptr<sf::Texture> atkTexture;
	std::shared_ptr<sf::Texture> playerAtkTexture;

};

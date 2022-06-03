#pragma once
#include "Player.h"

class MatchManager
{
public:
	MatchManager();
	~MatchManager();

	const bool getAreInputsBlocked();
	std::string getMsg();
	sf::Time getRoundTimer();

	void update();
	void resetRoundTimer();
private:
	void initVariables();
	void updateTimer();
	void updateMsgQueue();
	int inputsBlockedFrames;
	int inputsBlockedFramesMax;

	int msgFrames;
	int msgFramesMax;

	short int roundCounter;

	std::string msg;
	std::vector<std::string> msgQueue;

	sf::Time roundTimer;
	sf::Time roundTimerMax;
};

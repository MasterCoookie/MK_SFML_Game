#pragma once
#include "Player.h"

class MatchManager
{
public:
	MatchManager();
	~MatchManager();

	const bool getAreInputsBlocked();
	const bool isRoundResetPlanned();
	const bool resetNow();
	std::string getMsg();
	sf::Time getRoundTimer();

	void update();
	void resetRoundTimer();

	void beginRound();
	void endRound(std::string winnerName);
private:
	void initVariables();
	void updateTimer();
	void updateMsgQueue();
	int inputsBlockedFrames;
	int inputsBlockedFramesMax;


	int resetFrames;
	int resetFramesMax;

	short int roundCounter;
	bool roundResetPlanned;

	std::string msg;
	std::vector<std::string> msgQueue;

	sf::Time roundTimer;
	sf::Time roundTimerMax;
};

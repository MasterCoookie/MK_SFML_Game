#pragma once
#include "Player.h"

class MatchManager
{
public:
	MatchManager();
	~MatchManager();
	const bool getAreInputsBlocked();

private:
	void initVariables();
	int inputsBlockedFrames;
	int inputsBlockedFramesMax;

	int msgFrames;
	int msgFramesMax;

	std::string msg;
};

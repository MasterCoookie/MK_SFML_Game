#include "MatchManager.h"

MatchManager::MatchManager() {
	this->initVariables();
}

MatchManager::~MatchManager() {

}

const bool MatchManager::getAreInputsBlocked() {
	if (this->inputsBlockedFrames <= this->inputsBlockedFramesMax) {
		this->inputsBlockedFrames++;
		return true;
	}
	return false;
}

void MatchManager::initVariables() {
	this->inputsBlockedFrames = 0;
	this->inputsBlockedFramesMax = 90;

	this->msgFrames = 0;
	this->msgFramesMax = 90;

	this->msg = "Runda 1";
}

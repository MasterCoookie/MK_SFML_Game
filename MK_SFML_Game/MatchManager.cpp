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

std::string MatchManager::getMsg() {
	if (this->msgFrames <= this->msgFramesMax) {
		this->msgFrames++;
		return this->msg;
	}
	return "";
}

sf::Time MatchManager::getRoundTimer() {
	return this->roundTimer;
}

void MatchManager::update() {
	this->updateTimer();
}

void MatchManager::resetRoundTimer() {
	this->roundTimer = this->roundTimerMax;
}

void MatchManager::initVariables() {
	this->inputsBlockedFrames = 0;
	this->inputsBlockedFramesMax = 90;

	this->msgFrames = 0;
	this->msgFramesMax = 90;

	this->msg = "Runda 1";

	this->roundTimerMax = sf::seconds(90.f);
	this->roundTimer = this->roundTimerMax;
}

void MatchManager::updateTimer() {
	this->roundTimer -= sf::seconds(1.f / 30.f);
}


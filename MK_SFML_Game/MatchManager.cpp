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

const bool MatchManager::isRoundResetPlanned() {
	return this->roundResetPlanned;
}

const bool MatchManager::resetNow() {
	return (++this->resetFrames > this->resetFramesMax);
}

std::string MatchManager::getMsg() {
	if (this->inputsBlockedFrames <= this->inputsBlockedFramesMax) {
		return this->msg;
	}
	this->updateMsgQueue();
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

void MatchManager::beginRound() {
	this->msgQueue.push_back("Round " + std::to_string(++this->roundCounter));
	this->msgQueue.push_back("Fight!");
	this->updateMsgQueue();
	this->roundResetPlanned = false;
	this->resetFrames = 0;
}

void MatchManager::endRound(std::string winnerNum) {
	this->msgQueue = { (winnerNum + " wins!"), };
	this->updateMsgQueue();
	if (this->roundCounter < 3) {
		this->roundResetPlanned = true;
	}
}

void MatchManager::initVariables() {
	this->inputsBlockedFrames = 0;
	this->inputsBlockedFramesMax = 75;

	this->roundCounter = 1;

	this->msgQueue = { "Round 1", "Fight!" };

	this->roundTimerMax = sf::seconds(90.f);
	this->roundTimer = this->roundTimerMax;

	this->roundResetPlanned = false;

	this->resetFrames = 0;
	this->resetFramesMax = 75;
}

void MatchManager::updateTimer() {
	this->roundTimer -= sf::seconds(1.f / 30.f);
}

void MatchManager::updateMsgQueue() {
	if (this->msgQueue.size() > 0) {
		this->msg = *msgQueue.begin();
		msgQueue.erase(msgQueue.begin());
		this->inputsBlockedFrames = 0;
	}
}


#pragma once
#include <string>
#include <memory>
#include "Field.h"
#include "Strategy.h"
#include "FinishIt.h"

class Bot
{
public:
	const Field me{ true };
	Field opp{ false };
	std::unique_ptr <Strategy> chosenOne;
	FinishIt damaged{ &opp };
	std::pair <size_t, size_t> lastShot;

	void afterKill();

	char convertX() { return static_cast<char>(lastShot.second) + 'A'; }
	size_t convertY() { return lastShot.first; }
public:
	bool react(std::string command);
};
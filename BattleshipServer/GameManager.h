#pragma once
#include "BSserver.h"

class GameManager
{
	const std::string delayFlag = "-d",
		tournamentFlag = "-t";
	size_t delay = 50;
	bool tournament = false;
	
	std::vector <std::string> players;
	std::vector <std::pair <size_t, size_t>> results;
public:
	GameManager(size_t argc, std::vector <std::string> argv);//char **argv);

	void begin();
	void showResults();
};
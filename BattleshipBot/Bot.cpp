#include "Bot.h"

void Bot::afterKill()
{
	if (!damaged)
	{
		damaged.initialize(lastShot);
	}
	else damaged.result(true);
	opp.shipArea(damaged.shipStart(), damaged.shipSize(), damaged.isHorizontal());
	opp.fleet.destroyed(damaged.shipSize());
	damaged.clear();
	if (opp.fleet.boatsLeft())
	{
		chosenOne.reset(new BoatsLeft(&opp));
	}
}

bool Bot::react(std::string command)
{
	command = command.substr(0, command.find(' '));
	if (command == "Shoot!")
	{
		if (!damaged)
		{
			lastShot = chosenOne->shoot();
		}
		else lastShot = damaged.maxElimination();

		std::cout << convertX() << ' ' << convertY() << std::endl;
	}
	else if (command == "Miss")
	{
		opp.mark(lastShot, Field::Status::Nothing);
		if (damaged)
		{
			damaged.result(false);
		}
	}
	else if (command == "Hit")
	{
		opp.mark(lastShot, Field::Status::Ship);
		if (!damaged)
		{
			damaged.initialize(lastShot);
		}
		else damaged.result(true);
		lastShot = damaged.maxElimination();
		std::cout << convertX() << ' ' << convertY() << std::endl;
	}
	else if (command == "Kill")
	{
		opp.mark(lastShot, Field::Status::Ship);
		afterKill();
		if (opp.fleet)
		{
			lastShot = chosenOne->shoot();
			std::cout << convertX() << ' ' << convertY() << std::endl;
		}
	}
	else if (command == "Arrange!")
	{
		std::cout << me;
		chosenOne.reset(new Diagonal(&opp));
	}
	else if (command == "Win!" || command == "Lose")
	{
		return false;
	}
	return true;
}
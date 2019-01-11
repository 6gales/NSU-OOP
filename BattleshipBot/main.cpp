#include "Bot.h"
#include <ctime>

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	Bot player;
	std::string command;
	while (std::cin.good())
	{
		std::cin >> command;
		if (!player.react(command))
			break;
	}
	return 0;
}
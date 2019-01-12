#include "BSserver.h"

bool BSserver::readField(Player *pp, ServerField *fp)
{
	std::cout << "Sending [" << commands.arrange << "] to " << pp->getName() << std::endl;
	pp->sendMessage(commands.arrange);
	try
	{
		std::string placement = pp->getAnswer();
		try
		{
			for (size_t i = 1; i < fp->size(); i++)
				placement += pp->getAnswer();
		}
		catch (const std::runtime_error&) {}
		std::cout << "\nResponded with:\n" << placement << std::endl << std::endl;
		fp->init(placement);
	}
	catch (const std::exception &e) { std::cout << pp->getName() << " technically lost due to " << e.what() << std::endl; return false; }
	return true;
}

void BSserver::printFields()
{
	std::cout << std::endl;
	for (size_t i = 0; i < p1field.size(); i++)
	{
		std::cout << "\t";
		for (size_t j = 0; j < p1field.size(); j++)
		{
			std::cout << p1field.get(i, j);
		}
		std::cout << "\t\t";
		for (size_t j = 0; j < p2field.size(); j++)
		{
			std::cout << p2field.get(i, j);
		}
		std::cout << std::endl;
	}
	std::cout << "\t\t\t" << p1field.fleet.areaLeft() << "\t\t" << p2field.fleet.areaLeft() << std::endl << std::endl;
}

std::pair<size_t, size_t> BSserver::convertShot(std::string answer)
{
	std::stringstream ss{ answer };
	char xCoord;
	size_t yCoord;
	ss >> xCoord >> yCoord;
	if (xCoord < 'A' || xCoord > 'J' || yCoord > p1field.size())
		throw std::invalid_argument("invalid shot parameters");
	return std::pair<size_t, size_t>(yCoord, xCoord - 'A');
}

std::pair <bool, bool> BSserver::startGame()
{
	if (!readField(&player1, &p1field))
		return { false, false };
	
	if (!readField(&player2, &p2field))
		return { false, true };

	printFields();

	std::string commandBuffer = commands.shoot;

	while (p1field.fleet && p2field.fleet)
	{
		std::cout << "Sending [" << commandBuffer << "] to " << (turn ? player1 : player2).getName() << std::endl;
		(turn ? player1 : player2).sendMessage(commandBuffer);

		std::pair <size_t, size_t> shot;
		try
		{
			std::string respond = (turn ? player1 : player2).getAnswer();
			std::cout << "Responded with " << respond << std::endl;
			shot = convertShot(respond);

			std::pair <size_t, char> hit = (turn ? p2field : p1field).markShot(shot);

			(turn ? player2 : player1).sendMessage(commands.enemy + respond); //too many '\n' may occure errors
			commandBuffer = (hit.first ? (hit.first - 1 ? commands.kill : commands.hit) : commands.shoot);
			std::cout << std::endl << "Shot result: " << (commandBuffer == commands.shoot ? commands.miss : commandBuffer) 
				<< " [" << hit.second << "]" << std::endl;
			
			if (!hit.first)
			{
				(turn ? player1 : player2).sendMessage(commands.miss);
				turn = !turn;
			}
		}
		catch (const std::exception &e) { std::cout << (turn ? player1 : player2).getName() << " technically lost due to " << e.what() << std::endl; return { false, !turn }; }

		printFields();

		std::this_thread::sleep_for(delay);
	}
	player1.sendMessage((p1field.fleet ? commands.win : commands.lose));
	player2.sendMessage((p2field.fleet ? commands.win : commands.lose));
	std::cout << (turn ? player1 : player2).getName() << " won!" << std::endl;
	return { true, turn };
}
#include "GameManager.h"

GameManager::GameManager(size_t argc, std::vector <std::string> argv)//char **argv)
{
	for (size_t i = 1; i < argc; i++)
	{
		if (argv[i] == delayFlag)//will it work?
		{
			if (++i < argc)
			{
				try
				{
					delay = std::stoul(argv[i]);
				}
				catch (const std::exception &e) { std::cerr << "Error occured: " << e.what() << "\nContinuing with default delay..."; }
			}
			else std::cerr << delayFlag << " parameter not found\nContinuing with default delay...";
		}
		else if (argv[i] == tournamentFlag) tournament = true;

		else players.emplace_back(argv[i]);
	}
	results.resize(players.size(), { 0, 0 });
}

void GameManager::begin()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < players.size(); j++)
		{
			if (i != j)
			{
				try
				{

					BSserver server{ players[i], players[j], delay };
					std::pair <bool, bool> gameRes = server.startGame();
					results[(gameRes.second ? i : j)].first++;
					results[(gameRes.second ? i : j)].second += !gameRes.second;
				}
				catch (const boost::process::process_error &e) {}//throw; }
			}
		}
	}
}

void GameManager::showResults()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		std::cout << players[i] << ": " << results[i].first << " wins" 
			<< (results[i].second ? "(" + std::to_string(results[i].second) + " of them is technically" : "") << std::endl;
	}
}
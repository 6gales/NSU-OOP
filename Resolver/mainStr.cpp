#include "Resolver.h"

int main(int argc, char **argv)
{
	std::ifstream libList;
	std::ifstream targetList;
	if (argc == 3)
	{
		libList.open(argv[1]);
		targetList.open(argv[2]);
	}
	else
	{
		libList.open("libs.txt");
		targetList.open("targets.txt");
	}
	if (!libList || !targetList)
	{
		std::cerr << "File(s) not found\n";
		return 2;
	}
	std::map <std::string, std::map <std::string, library<std::string>>> libs;
	std::vector <std::tuple <std::string, std::string, std::string>> targets;
	try
	{
		libs = libReading<std::string>(libList);
		targets = targetReading<std::string>(targetList);
	}
	catch (std::out_of_range &e)
	{
		std::cerr << "Error occured: " << e.what() << std::endl;
		return 2;
	}
	catch (std::invalid_argument &e)
	{
		std::cerr << "Error occured: " << e.what() << std::endl;
		return 2;
	}
	if (libs.size() == 0 || targets.size() == 0)
	{
		std::cerr << "Nothing to resolve";
		return 1;
	}
	std::vector <typename std::map <std::string, library<std::string>>::iterator> resolution;
	try
	{
		resolution = resolve<std::string>(libs, targets);
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << "Error occured: " << e.what() << std::endl;
		return 2;
	}
	if (resolution.size() == 0)
	{
		std::cerr << "Unable to resolve targets.\n";
		return 1;
	}
	printSolution<std::string>(std::cout, resolution, libs);
	return 0;
}

#include "Drawer.h"
#include <fstream>

int main(int argc, char **argv)
{
	std::ifstream in;
	if (argc == 2)
	{
		in.open(argv[1]);
		std::cin.rdbuf(in.rdbuf());
	}
	std::string data;
	if (std::cin.good())
		getline(std::cin, data);
	try
	{
		Drawer object(data);
		object.readingFigures(std::cin);
		object.drawAll();
		object.saveImg();
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << "Error occured: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
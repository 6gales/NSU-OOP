#include "CSVParser.hpp"

int main(int argc, char **argv)
{
	std::ifstream input((argc == 1 ? "test.csv" : argv[1]));
	CSVParser <int, std::string> parser(input);
	for (auto t : parser)
	{
		std::cout << t;
	}
	return 0;
}

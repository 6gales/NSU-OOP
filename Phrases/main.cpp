#include "phrases.h"

int main(int argc, char** argv)
{
	unsigned int n = 2, m = 2;

	if (!fileInput(n, m, argc, argv))
	{
		std::cerr << "Wrong input!\n";
		exit(1);
	}

	std::vector<std::string> input(n);
	std::vector <std::pair<std::string, int>> association;
	unsigned int point = 0;

	for (; ((point < n) && !feof(stdin)); point++)
		std::cin >> input[point];
	while (!feof(stdin))
	{
		std::string newPhrase = adhesion(n, point, input);
		findPhrase(association, newPhrase);
		std::cin >> input[point % n];
		point++;
	}

	sort(association.begin(), association.end(), compare);

	for (int i = 0; i < association.size(); i++)
	{
		if (association[i].second >= m)
			std::cout << association[i].first << " (" << association[i].second << ")\n";
	}
	
	return 0;
}

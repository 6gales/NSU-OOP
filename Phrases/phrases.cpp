#include "phrases.h"

bool compare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
	return a.second > b.second;
}	

int fileInput(unsigned int &n, unsigned int &m, int argc, char **argv)
{
	char *infile = NULL;

	switch (argc)
	{
	case 1:
		break;

	case 2:
		infile = argv[1];
		break;
	
	case 3:
		if (!strcmp(argv[1], "-n") && (atoi(argv[2]) > 0))
			n = atoi(argv[2]);
		else if (!strcmp(argv[1], "-m") && (atoi(argv[2]) > 0))
			m = atoi(argv[2]);
		else return 0;
		break;

	case 4:
		if (!strcmp(argv[1], "-n") && (atoi(argv[2]) > 0))
			n = atoi(argv[2]);
		else if (!strcmp(argv[1], "-m") && (atoi(argv[2]) > 0))
			m = atoi(argv[2]);
		else return 0;
		infile = argv[3];
		break;

	case 5:
		if (!strcmp(argv[1], "-n") && !strcmp(argv[3], "-m") && (atoi(argv[2]) > 0) && (atoi(argv[4]) > 0))
		{
			n = atoi(argv[2]);
			m = atoi(argv[4]);
		}
		else return 0;
		break;

	case 6:
		if (!strcmp(argv[1], "-n") && !strcmp(argv[3], "-m") && (atoi(argv[2]) > 0) && (atoi(argv[4]) > 0))
		{
			n = atoi(argv[2]);
			m = atoi(argv[4]);
		}
		else return 0;
		infile = argv[5];
		break;

	default:
		return 0;
	}
	if (infile != NULL)
		if (strcmp(infile, "-"))
			if (!freopen(infile, "rb", stdin))
				return 0;
	return 1;
}

std::string adhesion(unsigned int n, unsigned int &point, std::vector <std::string> input)
{
	std::string newPhrase;
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
		{
			newPhrase += ' ';
			newPhrase += input[point % n];
		}
		else newPhrase = input[point % n];
		point++;
	}
	point %= n;
	return newPhrase;
}

void findPhrase(std::vector <std::pair<std::string, int>> &association, std::string newPhrase)
{
	int flag = -1;
	for (int i = 0; i < association.size(); i++)
		if (association[i].first == newPhrase)
			flag = i;
	if (flag != -1)
		association[flag].second++;
	else
	{
		association.reserve(1);
		association.push_back(make_pair(newPhrase, 1));
	}
}
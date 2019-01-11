#include "Strategy.h"

Diagonal::fieldPosition::fieldPosition(size_t _size, size_t _step) : size(_size), step(_step)
{
	switch (rand() % 4)
	{
	case 0:
		iSign = true;
		jSign = true;
		break;
	case 1:
		iSign = false;
		jSign = true;
		break;
	case 2:
		iSign = false;
		jSign = false;
		break;
	default:
		iSign = true;
		jSign = false;
	}
	i = (iSign ? step - 1 : size - step);
	j = (jSign ? 0 : size - 1);
}

Diagonal::fieldPosition &Diagonal::fieldPosition::operator++()
{
	bool jInc = false;
	if (iSign)
	{
		i += step;
		if (i >= static_cast<int>(size))
		{
			i %= size - 1 + step;
			i %= size - 1;
			jInc = true;
		}
	}
	else
	{
		i -= step;
		if (i < 0)
		{
			i %= static_cast<int>(step);
			i += size - 1;
			jInc = true;
		}
	}
	if (jInc)
	{
		j += (jSign ? 1 : -1);
		if (j < 0 || j >= static_cast<int>(size))
		{
			j = (jSign ? 0 : size - 1);
		}
	}
	return *this;
}

Diagonal::Diagonal(Field * _bf) : Strategy(_bf)
{
	nextShot = static_cast<std::pair <size_t, size_t>>(pos);
}

std::pair<size_t, size_t> Diagonal::shoot()
{
	while (bf->get(nextShot) != Field::Status::Unknown)
	{
		nextShot = static_cast<std::pair <size_t, size_t>>(++pos);
	}
	return nextShot;
}

std::pair<size_t, size_t> BoatsLeft::findAdjustedUnknown(bool ifMax)
{
	std::vector <std::pair <std::pair <size_t, size_t>, size_t>> allUnknowns;
	for (size_t i = 0; i < bf->size(); i++)
	{
		for (size_t j = 0; j < bf->size(); j++)
		{
			if (bf->get(i, j) == Field::Status::Unknown)
				allUnknowns.push_back(std::make_pair(std::make_pair(i, j), bf->knownClose(i, j)));
		}
	}
	size_t adjusted = allUnknowns[0].second, pos = 0;
	for (size_t i = 1; i < allUnknowns.size(); i++)
	{
		if ((ifMax ? (adjusted < allUnknowns[i].second) : (adjusted > allUnknowns[i].second)))
		{
			adjusted = allUnknowns[i].second;
			pos = i;
		}
	}
	return allUnknowns[pos].first;
}

std::pair<size_t, size_t> BoatsLeft::shoot()
{
	std::pair <size_t, size_t> shot;
	if (bf->unknownLeft() > (bf->size() * bf->size() / 4) && !(rand() % 3))
	{
		size_t x = rand() % bf->size(), y = rand() % bf->size();
		while (bf->at(x, y) != Field::Status::Unknown)
		{
			x = rand() % bf->size();
			y = rand() % bf->size();
		}
		shot = std::make_pair(x, y);
	}
	else shot = findAdjustedUnknown(rand() % 2);
	return shot;
}
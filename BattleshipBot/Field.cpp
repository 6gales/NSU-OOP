#include "Field.h"

void Field::shipArea(std::pair<size_t, size_t> start, size_t size, bool isHorizontal, Field::Status s)
{
	if (isHorizontal)
	{
		for (int i = -1; i < 2; i++)
		{
			try
			{
				at(start.first + i, start.second - 1) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}
			try
			{
				at(start.first + i, start.second + size) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}

		}
		for (size_t k = 0; k < size; k++)
		{
			try
			{
				at(start.first + 1, start.second + k) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}
			try
			{
				at(start.first - 1, start.second + k) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}
		}
	}
	else
	{
		for (int i = -1; i < 2; i++)
		{
			try
			{
				at(start.first - 1, start.second + i) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}
			try
			{
				at(start.first + size, start.second + i) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}

		}
		for (size_t k = 0; k < size; k++)
		{
			try
			{
				at(start.first + k, start.second + 1) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}
			try
			{
				at(start.first + k, start.second - 1) = s;
				unknownCells--;
			}
			catch (std::out_of_range&) {}
		}

	}
}

void Field::placeShip(std::pair<size_t, size_t> start, size_t size, bool isHorizontal, Field::Status s)
{
	if (isHorizontal)
	{
		for (size_t i = 0; i < size; i++)
		{
			matrix[index(start.first, start.second + i)] = s;
		}
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			matrix[index(start.first + i, start.second)] = s;
		}
	}
	if (s == Field::Status::Ship)
		shipArea(start, size, isHorizontal);
	else shipArea(start, size, isHorizontal, s);
}

size_t Field::validPlace(std::pair<size_t, size_t> start, size_t size, bool isHorizontal)
{
	size_t result = 0;

	if (isHorizontal)
	{
		if (start.second + size - 1 < fSize)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (matrix[index(start.first, start.second + i)] != Status::Unknown)
					result = 10;
			}
		}
		else result = 10;
		
		if (result != 10)
		{
			for (int i = -1; i < 2; i++)
			{
				try
				{
					if (at(start.first + i, start.second - 1) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}
				try
				{
					if (at(start.first + i, start.second + size) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}

			}
			for (size_t k = 0; k < size; k++)
			{
				try
				{
					if (at(start.first + 1, start.second + k) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}
				try
				{
					if (at(start.first - 1, start.second + k) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}
			}
		}
	}
	else
	{
		if (start.first + size - 1 < fSize)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (matrix[index(start.first + i, start.second)] != Status::Unknown)
					result = 10;
			}
		}
		else result = 10;

		if (result != 10)
		{
			for (int i = -1; i < 2; i++)
			{
				try
				{
					if (at(start.first - 1, start.second + i) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}
				try
				{
					if (at(start.first + size, start.second + i) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}

			}
			for (size_t k = 0; k < size; k++)
			{
				try
				{
					if (at(start.first + k, start.second + 1) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}
				try
				{
					if (at(start.first + k, start.second - 1) == Status::Unknown)
						result++;
				}
				catch (std::out_of_range&) {}
			}
		}
	}
	return result;
}

void Field::optimalPlace(std::vector <size_t> &ships, size_t &shipsLeft)
{
	if (shipsLeft == 0)
		return;
	std::pair <size_t, std::vector <std::pair <std::pair <size_t, size_t>, bool>>> coordList = { 10, {} };
	size_t thisShip = rand() % ships.size();
	while (ships[thisShip] == 0)
	{
		(++thisShip) %= ships.size();
	}
	ships[thisShip]--;
	shipsLeft--;
	for (size_t i = 0; i < fSize; i++)
	{
		for (size_t j = 0; j < fSize; j++)
		{
			size_t tmp = validPlace(std::pair <size_t, size_t>(i, j), thisShip + 2, true);
			if (tmp < 10 && (tmp <= thisShip + 4))
			{
				if (tmp < coordList.first)
				{
					coordList.first = tmp;
					coordList.second.clear();
					coordList.second.push_back(std::pair <std::pair <size_t, size_t>, bool>(std::make_pair(i, j), true));
				}
				else if (tmp == coordList.first)
				{
					coordList.second.push_back(std::pair <std::pair <size_t, size_t>, bool>(std::make_pair(i, j), true));
				}
			}

			tmp = validPlace(std::pair <size_t, size_t>(i, j), thisShip + 2, false);
			if (tmp < 10 && (tmp <= thisShip + 4))
			{
				if (tmp < coordList.first)
				{
					coordList.first = tmp;
					coordList.second.clear();
					coordList.second.push_back(std::pair <std::pair <size_t, size_t>, bool>(std::make_pair(i, j), false));
				}
				else if (tmp == coordList.first)
				{
					coordList.second.push_back(std::pair <std::pair <size_t, size_t>, bool>(std::make_pair(i, j), false));
				}
			}
		}
	}
	size_t position = rand() % coordList.second.size();
	placeShip(coordList.second[position].first, thisShip + 2, coordList.second[position].second);
}

void Field::placementAlghorithm()
{
	std::vector <size_t> ships = fleet.getFleet();
	ships.erase(ships.begin());
	size_t shipsLeft = 0;
	for (size_t i = 0; i < ships.size(); i++)
		shipsLeft += ships[i];
	optimalPlace(ships, shipsLeft);
}

void Field::oneSide()
{
	bool isHorizontal;
	std::vector <std::pair <size_t, size_t>> lines(2);
	std::vector <std::vector <size_t>> ships = { { 4, 2, 2 }, { 3, 3, 2 } };
	switch (rand() % 4)
	{
	case 0:
		isHorizontal = false;
		lines[0] = std::make_pair(0, 0);
		lines[1] = std::make_pair(0, 2);
		break;
	case 1:
		isHorizontal = true;
		lines[0] = std::make_pair(0, 0);
		lines[1] = std::make_pair(2, 0);
		break;
	case 2:
		isHorizontal = false;
		lines[0] = std::make_pair(0, 7);
		lines[1] = std::make_pair(0, 9);
		break;
	default:
		isHorizontal = true;
		lines[0] = std::make_pair(7, 0);
		lines[1] = std::make_pair(9, 0);
	}
	size_t pos = rand() % 2;
	for (size_t l = 0; l < 2; l++)
	{
		for (size_t i = 3; i > 0; i--)
		{
			size_t s = rand() % i;
			placeShip(lines[l], ships[pos][s], isHorizontal);
			(isHorizontal ? lines[l].second : lines[l].first) += ships[pos][s] + 1;
			ships[pos].erase(ships[pos].begin() + s);
		}
		pos = (pos + 1) % 2;
	}
}

void Field::oppositeSides()
{
	bool isHorizontal;
	std::vector <std::pair <size_t, size_t>> lines(2);
	std::vector <std::vector <size_t>> ships = { { 4, 2, 2 }, { 3, 3, 2 } };
	switch (rand() % 2)
	{
	case 0:
		isHorizontal = false;
		lines[0] = std::make_pair(0, 0);
		lines[1] = std::make_pair(0, 9);
		break;
	default:
		isHorizontal = true;
		lines[0] = std::make_pair(0, 0);
		lines[1] = std::make_pair(9, 0);
	}

	size_t pos = rand() % 2;
	for (size_t l = 0; l < 2; l++)
	{
		for (size_t i = 3; i > 0; i--)
		{
			size_t s = rand() % i;
			placeShip(lines[l], ships[pos][s], isHorizontal);
			(isHorizontal ? lines[l].second : lines[l].first) += ships[pos][s] + 1;
			ships[pos].erase(ships[pos].begin() + s);
		}
		pos = (pos + 1) % 2;
	}
}

void Field::inCorner()
{
	std::vector <std::pair <size_t, size_t>> lines(2);
	switch (rand() % 4)
	{
	case 0:
		lines[0] = std::make_pair(0, 0);
		break;
	case 1:
		lines[0] = std::make_pair(0, 9);
		break;
	case 2:
		lines[0] = std::make_pair(9, 9);
		break;
	default:
		lines[0] = std::make_pair(9, 0);
	}
	lines[1] = lines[0];

	bool isHorizontal = rand() % 2;
	std::vector <std::pair <bool, std::vector <size_t>>> ships = { std::make_pair(isHorizontal, std::vector <size_t>{4, 3}),
		std::make_pair(!isHorizontal, std::vector <size_t>{3, 2}) };

	ships[0].first ? (lines[0].first ? lines[1].first -= 2 : lines[1].first += 2) : (lines[0].second ? lines[1].second -= 2 : lines[1].second += 2);

	const std::vector <bool> growth = { lines[0].first == 0, lines[0].second == 0 };
	for (size_t l = 0; l < 2; l++)
	{
		for (size_t i = 2; i > 0; i--)
		{
			size_t s = rand() % i;
			placeShip((growth[ships[l].first] ? lines[l] : std::make_pair(lines[l].first - (!ships[l].first ? ships[l].second[s] - 1 : 0), 
					lines[l].second - (ships[l].first ? ships[l].second[s] - 1 : 0))), ships[l].second[s], ships[l].first);

			(ships[l].first ? lines[l].second : lines[l].first) += (growth[ships[l].first] ? 1 : -1) * (ships[l].second[s] + 1);
			
			ships[l].second.erase(ships[l].second.begin() + s);
		}
		placeShip((growth[!ships[l].first] ? lines[l] : std::make_pair(lines[l].first - (ships[l].first ? 1 : 0),
			lines[l].second - (!ships[l].first ? 1 : 0))), 2, !ships[l].first);
	}
}

bool Field::sameLine(const std::vector <std::pair <size_t, size_t>> &boats, size_t pos)
{
	for (size_t k = 0; k < pos; k++)
	{
		for (int i = -1; i < 2; i += 2)
		{
			for (int j = -1; j < 2; j += 2)
			{
				size_t x = boats[k].first,
					y = boats[k].second;
				while (x > 0 && x < fSize && y > 0 && y < fSize)
				{
					x += i;
					y += j;
					if (x == boats[pos].first && y == boats[pos].second)
						return true;
				}
			}
		}
	}
	return false;
}

void Field::formField()
{
	if (fSize == 10)
	{
		switch (rand() % 3)
		{
		case 0:
			oneSide();
			break;
		case 1:
			oppositeSides();
			break;
		default:
			inCorner();
		}
	}
	else placementAlghorithm();

	std::vector <std::pair <size_t, size_t>> boats(fleet.getFleet()[0]);
	for (size_t i = 0; i < boats.size(); i++)
	{
		do
		{
			boats[i].first = rand() % fSize;
			boats[i].second = rand() % fSize;
		} while (matrix[index(boats[i].first, boats[i].second)] != Status::Unknown || (sameLine(boats, i) && (rand() % 3)));
		placeShip(boats[i], 1, true);
	}
}

size_t Field::knownClose(size_t x, size_t y) const
{
	size_t count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			try
			{
				if (((i != 0) || (j != 0)) && (at(x + i, y + j) != Field::Status::Unknown))
					count++;
			}
			catch (std::out_of_range&) { count++; }
		}
	}
	return count;
}

std::ostream &operator<<(std::ostream &os, const Field::Status &s)
{
	switch (s)
	{
	case Field::Status::Ship:
		os << 1;
		break;
	case Field::Status::Nothing:
		//	default:
		os << 0;
		break;
	case Field::Status::Unknown:
//		os << 'u';
		os << 0;
		break;
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const Field &f)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
			os << f.get(i, j);
		os << std::endl;
	}
	return os;
}
#include "ServerField.h"

void ServerField::shipCoordinats(size_t a, size_t b, std::vector <std::pair <size_t, size_t>> &ship, std::vector <bool> &addition)
{
	ship.push_back(std::make_pair(a, b));
	addition[a * fSize + b] = true;
	try
	{
		if (at(a + 1, b - 1) == unkShip && !addition[(a + 1) * fSize + b - 1])
			shipCoordinats(a + 1, b - 1, ship, addition);
	}
	catch (const std::out_of_range&) {}
	
	try
	{
		if (at(a + 1, b) == unkShip && !addition[(a + 1) * fSize + b])
			shipCoordinats(a + 1, b, ship, addition);
	}
	catch (const std::out_of_range&) {}
	
	try
	{
		if (at(a, b + 1) == unkShip && !addition[a * fSize + b + 1])
			shipCoordinats(a, b + 1, ship, addition);
	}
	catch (const std::out_of_range&) {}
	
	try
	{
		if (at(a + 1, b + 1) == unkShip && !addition[(a + 1) * fSize + b + 1])
			shipCoordinats(a + 1, b + 1, ship, addition);
	}
	catch (const std::out_of_range&) {}
}

void ServerField::correctPlacement()
{
	const auto checkedFleet = fleet.getFleet();

	std::vector <size_t> detectedFleet(checkedFleet.size());

	std::vector <std::pair <size_t, size_t>> ship;

	std::vector <bool> addition(perception.size(), false);

	for (size_t i = 0; i < fSize; i++)
	{
		for (size_t j = 0; j < fSize; j++)
		{
			if (!perception[i * fSize + j] && perception[i * fSize + j] == unkShip)
			{
				shipCoordinats(i, j, ship, addition);

				detectedFleet[ship.size() - 1]++;

				if (ship.size() > 1)
				{
					if (ship[0].first == ship[1].first)
					{
						for (size_t k = 1; k < ship.size() - 1; k++)
						{
							if (ship[k].first != ship[k + 1].first)
								throw std::invalid_argument("invalid ship placement");
						}
					}
					else
					{
						for (size_t k = 0; k < ship.size() - 1; k++)
						{
							if (ship[k].second != ship[k + 1].second)
								throw std::invalid_argument("invalid ship placement");
						}
					}
				}

				if (ship.size() > checkedFleet[checkedFleet.size() - 1][0])
					throw std::invalid_argument("invalid ship size");

				ship.clear();
			}
		}
	}
	if (detectedFleet.size() != checkedFleet.size())
		throw std::invalid_argument("invalid number of sizes");
	
	for (size_t i = 0; i < detectedFleet.size(); i++)
	{
		if (detectedFleet[i] != checkedFleet[i].size())
			throw std::invalid_argument("invalid number of ships");
	}
}

void ServerField::init(std::string field)
{
	size_t i = 0;
	for (; i < fSize && i < field.size(); i++)
	{
		size_t j = 0;
		for (; j < fSize && j < field.size(); j++)
		{
			if (field[/*i * fSize + */j] == '0')
				perception[/*i * fSize + */j] = unkEmpty;

			else if (field[/*i * fSize + */j] == '1')
				perception[/*i * fSize + */j] = unkShip;

			else throw std::invalid_argument(static_cast<std::string>("unexpected char: ") + field[i * fSize + j]);
		}
		if (j < fSize)
			throw std::invalid_argument("invalid field size");
		while (field[/*i * fSize + */j] != '0' && field[/*i * fSize + */j] != '1')
		{
			j++;
			if (j == field.size())
				break;
		}
		field = field.substr(j, field.size());
	}
	if (i < fSize)
		throw std::invalid_argument("invalid field size");
	try
	{
		correctPlacement();
	}
	catch (const std::exception&) { throw; }
}

std::pair <size_t, size_t> ServerField::actualShip(size_t a, size_t b)
{
	size_t all = 0, known = 0, i = 0;
	bool stillShip = true;

	do
	{
		if (perception[(a - i) * fSize + b] == unkShip)
			all++;
		else if (perception[(a - i) * fSize + b] == knShip)
		{
			all++;
			known++;
		}
		else stillShip = false;

	} while (a - i++ > 0 && stillShip);

	i = 0;
	stillShip = true;
	do
	{
		if (perception[(a + i) * fSize + b] == unkShip)
			all++;
		else if (perception[(a + i) * fSize + b] == knShip)
		{
			all++;
			known++;
		}
		else stillShip = false;

	} while ((a + i++ < fSize - 1) && stillShip);

	i = 0;
	stillShip = true;
	do
	{
		if (perception[a * fSize + b - i] == unkShip)
			all++;
		else if (perception[a * fSize + b - i] == knShip)
		{
			all++;
			known++;
		}
		else stillShip = false;

	} while (b - i++ > 0 && stillShip);

	i = 0;
	stillShip = true;
	do
	{
		if (perception[a * fSize + b + i] == unkShip)
			all++;
		else if (perception[a * fSize + b + i] == knShip)
		{
			all++;
			known++;
		}
		else stillShip = false;

	} while ((b + i++ < fSize - 1) && stillShip);

	return { all - 3, known - 3 };
}

std::pair <size_t, char> ServerField::markShot(std::pair <size_t, size_t> shot)
{
	if (get(shot) == knEmpty || get(shot) == knShip)
		throw std::invalid_argument("cell has been checked already");

	if (get(shot) == unkEmpty)
	{
		perception[shot.first * fSize + shot.second] = knEmpty;
		return { 0, knEmpty };
	}

	perception[shot.first * fSize + shot.second] = knShip;
	auto ship = actualShip(shot.first, shot.second);

	fleet.decrease(ship.first, ship.second);

	return { (ship.first == ship.second ? 2 : 1), knShip };
}
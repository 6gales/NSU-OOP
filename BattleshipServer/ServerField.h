#pragma once

#include <iostream>
#include <vector>
#include <string>

class ClassicFleet
{
	size_t shipArea = 20;
	std::vector <std::vector <size_t>> fleet = { {1, 1, 1, 1}, {2, 2, 2}, {3, 3}, {4} };
public:
	operator bool() const { return shipArea > 0; }
	auto getFleet() const { return fleet; }
	size_t areaLeft() const { return shipArea; }
	void decrease(size_t size, size_t damaged)
	{
		shipArea--;
		for (size_t i = 0; i < fleet[size - 1].size(); i++)
		{
			if (fleet[size - 1][i] == (size - damaged))
				fleet[size - 1][i]--;
		}
	}
};

class ServerField
{
	const size_t fSize;
	const char unkEmpty = '.',
		knEmpty = 'O',
		unkShip = '#',
		knShip = 'X';

	std::vector <char> perception;

	void shipCoordinats(size_t a, size_t b, std::vector <std::pair <size_t, size_t>> &ship, std::vector <bool> &addition);
	void correctPlacement();

	std::pair <size_t, size_t> actualShip(size_t a, size_t b);
public:
	ServerField(size_t s = 10) : fSize(s) { perception.resize(fSize * fSize); }

	void init(std::string field);
	size_t size() const { return fSize; }

	ClassicFleet fleet;

	std::pair <size_t, char> markShot(std::pair <size_t, size_t> shot);

	char get(size_t first, size_t second) const { return perception[first * fSize + second]; }
	char get(std::pair <size_t, size_t> cell) const { return perception[cell.first * fSize + cell.second]; }

	char &at(size_t first, size_t second)
	{
		if (second >= fSize || first >= fSize)
			throw std::out_of_range("not a field");
		return perception[first * fSize + second];
	}
	const char &at(size_t first, size_t second) const
	{
		if (second >= fSize || first >= fSize)
			throw std::out_of_range("not a field");
		return perception[first * fSize + second];
	}
};
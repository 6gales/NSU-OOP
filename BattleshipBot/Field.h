#pragma once
#include <iostream>
#include <vector>

class ClassicFleet
{
	size_t shipCounter = 10,
		maxSize = 3;
	std::vector <size_t> fleet = { 4, 3, 2, 1 };
	void fixMaxSize() { while (maxSize > 0 && fleet[maxSize] == 0) maxSize--; }
public:
	operator bool() const { return shipCounter > 0; }
	size_t maxShipSize() const { return maxSize + 1; }
	void destroyed(size_t size) { fleet[size - 1]--; shipCounter--; fixMaxSize(); }
	bool boatsLeft() { return maxSize == 0; }
	std::vector <size_t> getFleet() { return fleet; }
};

class Field
{
public:
	enum class Status { Nothing, Unknown, Ship };
	ClassicFleet fleet;
private:
	const size_t fSize;
	size_t unknownCells;
	Status *matrix = nullptr;
	size_t index(size_t i, size_t j) const { return i * fSize + j; }

	void placeShip(std::pair<size_t, size_t> start, size_t size, bool isHorizontal, Field::Status s = Field::Status::Ship);

	size_t validPlace(std::pair<size_t, size_t> start, size_t size, bool isHorizontal);
	void optimalPlace(std::vector <size_t> &ships, size_t &shipsLeft);//optimal alghorithm of choosing place for each ship with the least area taken by its 
	void placementAlghorithm();

	void oneSide(); //template 10x10 field placements
	void oppositeSides();
	void inCorner();

	bool sameLine(const std::vector <std::pair <size_t, size_t>> &boats, size_t pos);
	void formField();
public:
	Field(bool form, size_t s = 10) : fSize(s)
	{
		unknownCells = fSize * fSize;
		matrix = new Status[unknownCells];
		for (size_t i = 0; i < fSize * fSize; i++) matrix[i] = Status::Unknown;
		if (form)
		{
			formField();
		}
	}
	~Field() { delete[] matrix; matrix = nullptr; }

	size_t size() const { return fSize; }
	size_t knownClose(size_t x, size_t y) const;
	size_t unknownLeft() const { return unknownCells; }

	void mark(std::pair <size_t, size_t> shot, Status s) { matrix[index(shot.first, shot.second)] = s; unknownCells += (s == Field::Status::Unknown ? 1 : -1); }
	Status get(size_t i, size_t j) const { return matrix[index(i, j)]; }
	Status get(std::pair <size_t, size_t> cell) const { return matrix[index(cell.first, cell.second)]; }
	
	Status &at(size_t first, size_t second)
	{
		if (second >= fSize || first >= fSize)
			throw std::out_of_range("not a field");
		return matrix[index(first, second)];
	}
	const Status &at(size_t first, size_t second) const
	{
		if (second >= fSize || first >= fSize)
			throw std::out_of_range("not a field");
		return matrix[index(first, second)];
	}
	void shipArea(std::pair<size_t, size_t> start, size_t size, bool isHorizontal, Field::Status s = Field::Status::Nothing);
};

std::ostream &operator<<(std::ostream &os, const Field::Status &s);

std::ostream &operator<<(std::ostream &os, const Field &f);
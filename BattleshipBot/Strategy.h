#pragma once
#include "Field.h"

class Strategy
{
protected:
	Field *bf;
public:
	Strategy(Field *_bf = nullptr) : bf(_bf) {}
	virtual std::pair <size_t, size_t> shoot() = 0;
};

class Diagonal : public Strategy
{
	class fieldPosition
	{
		const size_t size,
			step;
		bool iSign,
			jSign;
		int i, j;
	public:
		fieldPosition(size_t _size, size_t _step);
		fieldPosition &operator++();
		operator std::pair<size_t, size_t>() const { return std::pair<size_t, size_t>(i, j); }
	};
	fieldPosition pos{ bf->size(), bf->fleet.maxShipSize() };
	std::pair <size_t, size_t> nextShot;
public:
	Diagonal(Field *_bf);
	std::pair <size_t, size_t> shoot();
};

class BoatsLeft : public Strategy
{
	std::pair <size_t, size_t> findAdjustedUnknown(bool ifMax);
public:
	BoatsLeft(Field *_bf) : Strategy(_bf) {}
	std::pair <size_t, size_t> shoot();
};
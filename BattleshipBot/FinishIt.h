#pragma once
#include "Field.h"

class FinishIt
{
	enum class direction { Unknown, Vertical, Horizontal };
	Field *const bf;
	std::vector <std::pair <size_t, size_t>> coordinates;
	std::vector <std::pair <std::pair <size_t, size_t>, size_t>> suspectedClose;
	direction shipD = direction::Unknown;
	size_t shooted;
	void fillCloses();
	std::pair <size_t, size_t> ends() const;
public:
	FinishIt(Field *_bf) : bf(_bf) {}
	void initialize(std::pair <size_t, size_t> shot) { shipD = direction::Unknown; coordinates.push_back(shot); }
	void clear() { coordinates.resize(0); suspectedClose.resize(0); }
	
	std::pair <size_t, size_t> maxElimination();
	
	std::pair <size_t, size_t> shipStart() const { return coordinates[ends().first]; }
	size_t shipSize() const { return coordinates.size(); }
	bool isHorizontal() const { return shipD == direction::Horizontal; }
	
	void result(bool succes);
	operator bool() const { return coordinates.size() != 0; }
};
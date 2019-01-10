#pragma once
#include <iostream>
#include <unordered_map>
#include <initializer_list>
#include <iterator>

typedef unsigned int uint;
enum class Trit { False, Unknown, True };

std::ostream& operator<<(std::ostream &os, const Trit &value);

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(T t) const { return static_cast<std::size_t>(t); }
};

Trit operator&(const Trit &a, const Trit &b);
Trit operator|(const Trit &a, const Trit &b);
Trit operator!(const Trit &a);

class TwoBits;

class TritSet
{
	friend class TwoBits;

	uint *p = NULL;
	uint len = 0,
		intLen = 0,
		logLen = 0;

public:
	TritSet() {}
	TritSet(uint n);
	TritSet(const std::initializer_list<Trit> &list);
	TritSet(const TritSet &obj);
	~TritSet() { delete[] p; }
	void shrink();
	size_t capacity() const { return len; }
	Trit operator[](uint n) const;
	TwoBits operator[](uint n);
	TritSet operator&(const TritSet &obj) const;
	TritSet operator|(const TritSet &obj) const;
	TritSet operator!() const;
	TritSet &operator=(const TritSet &obj);
	size_t cardinality(Trit value) const;
	std::unordered_map<Trit, int, EnumClassHash> cardinality() const;
	void trim(size_t lastIndex);
	size_t length() const { return logLen; }
	bool operator==(const TritSet &obj) const;
	bool operator!=(const TritSet &obj) const;
	TritSet &operator&=(const TritSet &obj);
	TritSet &operator|=(const TritSet &obj);

	class const_iterator
	{
		const TritSet *parent;
		uint index;
	public:
		const_iterator(const TritSet *obj, uint toIndex) : parent(obj), index(toIndex) {}
		const_iterator &operator++() { index++; return (*this); };
		bool operator!=(const const_iterator &it) const { if (parent == it.parent && index == it.index) return 0; return 1; }
		Trit operator*() const { return (*parent)[index]; }
	};
	const_iterator begin() const { return const_iterator(this, 0); }
	const_iterator end() const { return const_iterator(this, logLen); }
};

std::ostream& operator<<(std::ostream &os, const TritSet &obj);

class TwoBits
{
	friend class TritSet;
	uint intAdress,
		tritAdress;
	TritSet *pointer;
	void mSeg();

	TwoBits(uint toIntAdress, uint toTritAdress, TritSet *toPointer)
		: intAdress(toIntAdress), tritAdress(toTritAdress), pointer(toPointer) {}
public:

	operator Trit() const;

	TwoBits &operator=(Trit value);

	TwoBits &operator=(const TwoBits &value);
};

uint formUnknown();

#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

template <class ... args>
class CSVParser
{
	char delimeter = ';',
		escape = '"';
	std::vector <std::tuple <args...>> data;

	std::vector <std::string> parse(std::string line);
public:
	CSVParser() {};
	void init(std::ifstream &infile, size_t skipLines = 0);
	CSVParser(std::ifstream &infile, size_t skipLines = 0) { init(infile, skipLines); }
	void setDelimeter(char value) { delimeter = value; }
	void setEscape(char value) { escape = value; }

	class const_iterator
	{
		const std::vector < std::tuple <args...>> *dataPointer;
		size_t pos;
	public:
		const_iterator(size_t _pos, const std::vector < std::tuple <args...>> *_dataPointer) : pos(_pos), dataPointer(_dataPointer) {};
		const std::tuple <args...> &operator*() const { return (*dataPointer)[pos]; }
		const_iterator &operator++() { ++pos; return *this; }
		bool operator==(const const_iterator &it) const { return (it.dataPointer == dataPointer && it.pos == pos); }
		bool operator!=(const const_iterator &it) const { return !(it == *this); }
	};
	const_iterator begin() const { const_iterator it(0, &data); return it; }
	const_iterator end() const { const_iterator it(data.size(), &data); return it; }
};

template <class ...args>
std::vector <std::string> CSVParser<args...>::parse(std::string line)
{
	std::vector <std::string> parsedLine;

	if (line.find(13) != line.npos)
		line.pop_back();

	bool escapeFlag = false;
	size_t check = 0;
	std::pair <size_t, size_t> escapeBrackets;
	for (size_t i = 0; i < line.size(); ++i)
	{
		if (line[i] == escape)
		{
			if (escapeFlag)
			{
				escapeBrackets.second = i;
				if (escapeBrackets.first + 1 == escapeBrackets.second)
				{
					line.erase(line.begin() + i);
					i--;
					escapeFlag = false;
				}
				else
				{
					parsedLine.push_back(line.substr(escapeBrackets.first + 1, escapeBrackets.second - 1 - escapeBrackets.first));
					check = escapeBrackets.second + 1;
					try
					{
						if (line.at(escapeBrackets.second + 1) == delimeter)
							check++;
					}
					catch (const std::out_of_range&) {}
				}
			}
			else
			{
				escapeBrackets.first = i;
				escapeFlag = true;
			}
		}
		else if (line[i] == delimeter)
		{
			if (!escapeFlag)
			{
				parsedLine.push_back(line.substr(check, i - check));
				check = i + 1;
			}
		}
	}
	if (check != line.size())
		parsedLine.push_back(line.substr(check, line.size()));

	return parsedLine;
}

template <class Type>
void writeToTuple(std::istream &is, Type ref)
{
	is >> ref;
}

template <>
void writeToTuple<int&>(std::istream &is, int &ref)
{
	try
	{
		std::string from;
		is >> from;
		ref = std::stoi(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
void writeToTuple<bool&>(std::istream &is, bool &ref)
{
	try
	{
		std::string from;
		is >> from;

		if (from == "true" || from == "true " || from.at(0) == '1')
			ref = true;
		else if (from == "false" || from == "false " || from.at(0) == '0')
			ref = false;
		else throw std::invalid_argument("not a bool");
	}
	catch (std::out_of_range&) { throw; }
}

template <>
void writeToTuple<short int&>(std::istream &is, short int &ref)
{
	int res;
	try
	{
		std::string from;
		is >> from;
		res = std::stoi(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
	if (res > std::numeric_limits<short>::max() || res < std::numeric_limits<short>::min())
		throw std::out_of_range("short int out of range");
	ref = res;
}

template <>
void writeToTuple<unsigned short int&>(std::istream &is, unsigned short int &ref)
{
	unsigned int res;
	try
	{
		std::string from;
		is >> from;
		res = std::stoul(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
	if (res > std::numeric_limits<unsigned short>::max())
		throw std::out_of_range("unsigned short int out of range");
	ref = res;
}

template <>
void writeToTuple<unsigned int&>(std::istream &is, unsigned int &ref)
{
	try
	{
		std::string from;
		is >> from;
		ref = std::stoul(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
void writeToTuple<float&>(std::istream &is, float &ref)
{
	try
	{
		std::string from;
		is >> from;
		ref = std::stof(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
void writeToTuple<double&>(std::istream &is, double &ref)
{
	try
	{
		std::string from;
		is >> from;
		ref = std::stod(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
void writeToTuple<std::string &>(std::istream &is, std::string &ref)
{
	getline(is, ref);
}

template <class Tuple, size_t num>
struct TuplePacker
{
	static void pack(Tuple &result, std::vector <std::string> cells)
	{
		std::stringstream ss(cells[num - 1]);
		try
		{
			writeToTuple<decltype(std::get<num - 1>(result))>(ss, std::get<num - 1>(result));
		}
		catch (const std::exception&) { throw; }
		TuplePacker<Tuple, num - 1>::pack(result, cells);
	}
};

template <class Tuple>
struct TuplePacker<Tuple, 1>
{
	static void pack(Tuple &result, std::vector <std::string> cells)
	{
		std::stringstream ss(cells[0]);
		try
		{
			writeToTuple<decltype(std::get<0>(result))>(ss, std::get<0>(result));
		}
		catch (const std::exception&) { throw; }
	}
};

template <class ... args>
void CSVParser<args...>::init(std::ifstream &infile, size_t skipLines)
{
	std::string line;
	while (skipLines && infile.good())
	{
		getline(infile, line);
		skipLines--;
	}

	while (infile.good())
	{
		getline(infile, line);
		if (!line.empty())
		{
			auto cells = parse(line);
			if (cells.size() != sizeof...(args))
				std::cerr << "Cells quantity does not match\n";
			else
			{
				std::tuple <args...> result;
				try
				{
					TuplePacker<decltype(result), sizeof...(args)>::pack(result, cells);
				}
				catch (const std::exception &e) { std::cerr << "Error occured: " << e.what() << " in line " << data.size() << "\nContinuing...\n"; }
				data.push_back(result);
			}
		}
	}
}

template<class Tuple, size_t numTypes>
struct TupleToString
{
	static std::string toString(const Tuple& t)
	{
		std::stringstream ss;
		ss << std::get<numTypes - 1>(t);
		return TupleToString<Tuple, numTypes - 1>::toString(t) + ' ' + ss.str();
	}
};

template<class Tuple>
struct TupleToString<Tuple, 1>
{
	static std::string toString(const Tuple& t)
	{
		std::stringstream ss;
		ss << std::get<0>(t);
		return ss.str();
	}
};

template <class ... args>
std::ostream &operator<<(std::ostream &os, const std::tuple<args...> &t)
{
	return os << TupleToString<decltype(t), sizeof...(args)>::toString(t) << std::endl;
}

#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits>
#include <stdexcept>

int vecCmp(const std::vector <size_t> &a, const std::vector <size_t> &b);

class versionType
{
	std::string strVersion;
	std::vector <size_t> sepVersion;
public:
	versionType() {}
	versionType(const std::string &version);
	versionType(const char *str);
	versionType(const versionType &version);
	versionType &operator=(const std::string &version);
	versionType &operator=(const char *version);
	versionType &operator=(const versionType &version);
	bool operator==(const versionType &obj) const { return (vecCmp(sepVersion, obj.sepVersion) == 0); }
	bool operator!=(const versionType &obj) const { return !(*this == obj); }
	bool operator>=(const versionType &obj) const { return !(*this < obj); }
	bool operator<=(const versionType &obj) const { return !(*this > obj); }
	bool operator>(const versionType &obj) const { return (vecCmp(sepVersion, obj.sepVersion) == 1); }
	bool operator<(const versionType &obj) const { return (!(*this > obj) && (*this != obj)); }
	friend std::ostream &operator<<(std::ostream &os, const versionType &obj) { return os << obj.strVersion; }
};

enum class libStatus { notInstall, notInvolved, install };

template <class T> struct library
{
	std::string name;
	T version;
	libStatus status = libStatus::notInvolved;
	std::vector <std::tuple <std::string, std::string, T>> conflicts;
	std::vector <std::tuple <std::string, std::string, T>> requirements;
};

bool isVersion(const std::string &version);

std::string shrink(const std::string &str);
//следующий набор функций необходим для задания наименьшего значения, когда необходимо установить любую версию
template <class T>
inline T defaultValue()
{
	return 0;
}

template <>
inline int defaultValue<int>()
{
	return std::numeric_limits<int>::min();
}

template <>
inline short int defaultValue<short int>()
{
	return std::numeric_limits<short int>::min();
}

template <>
inline long int defaultValue<long int>()
{
	return std::numeric_limits<long int>::min();
}

template <>
inline long long int defaultValue<long long int>()
{
	return std::numeric_limits<long long int>::min();
}

template <>
inline char defaultValue<char>()
{
	return std::numeric_limits<char>::min();
}

template <>
inline float defaultValue<float>()
{
	return -std::numeric_limits<float>::max();
}

template <>
inline double defaultValue<double>()
{
	return -std::numeric_limits<double>::max();
}

template <>
inline long double defaultValue<long double>()
{
	return -std::numeric_limits<long double>::max();
}

template <>
inline bool defaultValue<bool>()
{
	return false;
}

template <>
inline std::string defaultValue<std::string>()
{
	return "\0";
}

template <>
inline versionType defaultValue<versionType>()
{
	versionType res = "0.0";
	return res;
}
//следующий набор функций необходим для перевода строки в аргумент любого типа
template <class T>
inline T strConvert(std::string from)
{
	return from;
}

template <>
inline int strConvert<int>(std::string from)
{
	try
	{
		return std::stoi(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline bool strConvert<bool>(std::string from)
{
	try
	{
		if (from == "true" || from == "true " || from.at(0) == '1')
			return true;
		if (from == "false" || from == "false " || from.at(0) == '0')
			return false;
		throw std::invalid_argument("not a bool");
	}
	catch (std::out_of_range&) { throw; }
}

template <>
inline char strConvert<char>(std::string from)
{
	try
	{
		return from.at(0);
	}
	catch (std::out_of_range&) { throw; }
}

template <>
inline signed char strConvert<signed char>(std::string from)
{
	try
	{
		return from.at(0);
	}
	catch (std::out_of_range&) { throw; }
}

template <>
inline unsigned char strConvert<unsigned char>(std::string from)
{
	try
	{
		return from.at(0);
	}
	catch (std::out_of_range&) { throw; }
}

template <>
inline short int strConvert<short int>(std::string from)
{
	int res;
	try
	{
		res = std::stoi(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
	if (res > std::numeric_limits<short>::max() || res < std::numeric_limits<short>::min())
		throw std::out_of_range("short int out of range");
	return (short)res;
}

template <>
inline unsigned short int strConvert<unsigned short int>(std::string from)
{
	unsigned int res;
	try
	{
		res = std::stoul(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
	if (res > std::numeric_limits<unsigned short>::max())
		throw std::out_of_range("unsigned short int out of range");
	return (unsigned short)res;
}

template <>
inline unsigned int strConvert<unsigned int>(std::string from)
{
	try
	{
		return std::stoul(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline unsigned long int strConvert<unsigned long int>(std::string from)
{
	try
	{
		return std::stoul(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline unsigned long long int strConvert<unsigned long long int>(std::string from)
{
	try
	{
		return std::stoull(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline long int strConvert<long int>(std::string from)
{
	try
	{
		return std::stol(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline long long int strConvert<long long int>(std::string from)
{
	try
	{
		return std::stoll(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline float strConvert<float>(std::string from)
{
	try
	{
		return std::stof(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline double strConvert<double>(std::string from)
{
	try
	{
		return std::stod(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}

template <>
inline long double strConvert<long double>(std::string from)
{
	try
	{
		return std::stold(from);
	}
	catch (std::invalid_argument&) { throw; }
	catch (std::out_of_range&) { throw; }
}
//функция, разделяющая входную строку на три аргумента, имя, оператор сравнения и версию
//так как в примере на сайте строки заканчивались пробелами, а не \n, я сделал так же возможность разбиения подобных строк
template <class T>
std::tuple <std::string, std::string, T> separate(std::string data)
{
	if (data.empty())
		throw std::invalid_argument("string is empty");

	std::vector <std::string> separation;
	T version;
	size_t count = 0;

	while (data.find(' ') != data.npos)
	{
		separation.push_back(data.substr(0, data.find(' ')));
		data = data.substr(data.find(' ') + 1, data.size());
		count++;
	}

	switch (count)
	{
	case 0:
		separation.push_back(data);
		separation.push_back(">=");
		try
		{
			version = defaultValue<T>();
		}
		catch (const std::invalid_argument&) { throw; }
		break;
	case 1:
		if (data.empty())
		{
			separation.push_back(">=");
			try
			{
				version = defaultValue<T>();
			}
			catch (const std::invalid_argument&) { throw; }
		}
		else
		{
			separation.push_back("==");
			try
			{
				version = strConvert<T>(data);
			}
			catch (const std::out_of_range&) { throw; }
			catch (const std::invalid_argument&) { throw; }
		}
		break;
	case 2:
		if (data.empty())
		{
			try
			{
				version = strConvert<T>(separation[1]);
			}
			catch (const std::out_of_range&) { throw; }
			catch (const std::invalid_argument&) { throw; }
			separation[1] = "==";
		}
		else
		{
			try
			{
				version = strConvert<T>(data);
			}
			catch (const std::out_of_range&) { throw; }
			catch (const std::invalid_argument&) { throw; }
		}
		break;
	case 3:
		try
		{
			version = strConvert<T>(separation[2]);
		}
		catch (const std::out_of_range&) { throw; }
		catch (const std::invalid_argument&) { throw; }
		break;
	default:
		throw std::invalid_argument("string contains to many arguments");
	}
	if (separation[0].empty() || separation[1].empty())
		throw std::invalid_argument("separated string is empty");
	return std::make_tuple(separation[0], separation[1], version);
}
//данные о библиотеках хранятся следующим образом: map, где ключ это имя библиотеки, а каждый элемент это map, ключ которого версия, а значение - набор зависимостей и конфликтов 
template <class T>
std::map <std::string, std::map <T, library <T>>> libReading(std::ifstream &libList)
{
	std::map <std::string, std::map <T, library <T>>> libs;
	std::string data;
	std::pair <typename std::map <std::string, std::map <T, library <T>>>::iterator, bool> bigIt;
	std::pair <typename std::map <T, library <T>>::iterator, bool> smallIt;
	//последующая конструкция обеспечивает то, что smallIt не будет использован до инициализации, что возможно, если первым значащим символом в файле является + или -
	if (libList.good())
	{
		char c;
		libList.get(c);
		while (libList.good() && (c == '\n' || c == 13))
			libList.get(c);
		if (c == '+' || c == '-' || c == ' ')
			throw std::invalid_argument("unexpected file beginning");
		libList.unget();
	}
	while (libList.good())
	{
		getline(libList, data);

		if (data.find(13) != data.npos)
			data.pop_back();

		if (!data.empty())
		{
			if (data[0] == '+' || data[0] == '-')
			{
				bool flag = ((data[0] == '+') ? true : false);
				
				try
				{
					data = data.substr(2, data.size());
				}
				catch (const std::out_of_range&) { throw; }
				try
				{
					if (flag)
						smallIt.first->second.requirements.push_back(separate<T>(data));
					else smallIt.first->second.conflicts.push_back(separate<T>(data));
				}
				catch (const std::out_of_range&) { throw; }
				catch (const std::invalid_argument&) { throw; }
			}
			else
			{
				library <T> current;
				current.name = data.substr(0, data.find(' '));
				try
				{
					data = data.substr(data.find(' ') + 1, data.size());
				}
				catch (const std::out_of_range&) { throw; }
				if (data.empty() || current.name.empty())
					throw std::invalid_argument("string is empty");
				try
				{
					current.version = strConvert<T>(data.substr(0, data.find(' ')));
				}
				catch (const std::out_of_range&) { throw; }
				catch (const std::invalid_argument&) { throw; }
				std::map <T, library <T>> oneLib;
				bigIt = libs.insert(std::make_pair(current.name, oneLib));
				smallIt = bigIt.first->second.insert(std::make_pair(current.version, current));
			}
			data.resize(0);
		}
	}
	return libs;
}
//просто чтение целей, через разбиение, уже использовавшееся ранее
template <class T>
std::vector <std::tuple <std::string, std::string, T>> targetReading(std::ifstream &targetList)
{
	std::vector <std::tuple <std::string, std::string, T>> targets;
	std::string data;
	while (targetList.good())
	{
		getline(targetList, data);

		if (data.find(13) != data.npos)
			data.pop_back();

		if (!data.empty())
		{
			try
			{
				targets.push_back(separate<T>(data));
			}
			catch (const std::out_of_range&) { throw; }
			catch (const std::invalid_argument&) { throw; }
		}
	}
	return targets;
}
//функция-переключатель
template <class T>
bool relOperCompare(std::string relOperator, const T &a, const T &b)
{
	if (relOperator == ">")
		return a > b;
	if (relOperator == ">=")
		return a >= b;
	if (relOperator == "==" || relOperator == "=")
		return a == b;
	if (relOperator == "<")
		return a < b;
	if (relOperator == "<=")
		return a <= b;
	if (relOperator == "!=")
		return a != b;
	throw std::invalid_argument("not a comparisson operator");
}
//функция, необходимая для удаления библиотек из списка конфликтов
template <class T>
bool notInstall(std::tuple <std::string, std::string, T> obstacle, std::map <std::string, std::map <T, library <T>>> &libs)
{
	auto namesPlace = libs.find(std::get<0>(obstacle));
	if (namesPlace == libs.end())
		throw std::invalid_argument("library not found");
	bool exitFlag = true;
	auto i = namesPlace->second.begin();
	for (; i != namesPlace->second.end(); i++)
	{
		try
		{
			if (relOperCompare<T>(std::get<1>(obstacle), i->first, std::get<2>(obstacle)))
			{
				if (i->second.status == libStatus::install)//если встречается необходимый к установке элемент, функция возвращает значения и завершает работу
				{
					exitFlag = false;
					break;
				}
				i->second.status = libStatus::notInstall;
			}
		}
		catch (const std::invalid_argument&) { throw; }
	}
	if (!exitFlag)
	{
		for (auto j = namesPlace->second.begin(); j != i; j++)
		{
			if (relOperCompare(std::get<1>(obstacle), j->first, std::get<2>(obstacle)))
				j->second.status = libStatus::notInvolved;
		}
	}
	return exitFlag;
}
//функция, нивелирующая работу предыдущей функции
template <class T>
void notInstallRecovery(std::tuple <std::string, std::string, T> obstacle, std::map <std::string, std::map <T, library<T>>> &libs)
{
	auto namesPlace = libs.find(std::get<0>(obstacle));
	for (auto i = namesPlace->second.begin(); i != namesPlace->second.end(); i++)
	{
		if (relOperCompare(std::get<1>(obstacle), i->first, std::get<2>(obstacle)))
			i->second.status = libStatus::notInvolved;
	}
}
//функция, убирающая возможность установить одну и ту же библиотеку несколько раз
template <class T>
bool sameLibExecution(typename std::map <std::string, std::map <T, library<T>>>::iterator chosenOne)
{
	bool exitFlag = true;
	std::vector <typename std::map <T, library<T>>::iterator> change;
	for (auto i = chosenOne->second.begin(); i != chosenOne->second.end(); i++)
	{

		if (i->second.status == libStatus::install)//если библиотека с данным именем уже установлена, то функция восстановит изменённые значения и завершится
		{
			exitFlag = false;
			break;
		}
		if (i->second.status == libStatus::notInvolved)
		{
			i->second.status = libStatus::notInstall;
			change.push_back(i);
		}
	}

	if (!exitFlag)
	{
		for (size_t j = 0; j < change.size(); j++)
			change[j]->second.status = libStatus::notInvolved;
	}
	return exitFlag;
}
//функция, нивелирующая работу предыдущей функции
template <class T>
void sameLibRecovery(typename std::map <std::string, std::map <T, library<T>>>::iterator chosenOne)
{
	for (auto i = chosenOne->second.begin(); i != chosenOne->second.end(); i++)
	{
		i->second.status = libStatus::notInvolved;
	}
}
//функция, устанавливающая для набор итераторов, а так же удаляющая из списка их помехи   
template <class T>
void installSolution(std::vector <typename std::map <T, library<T>>::iterator> solution, std::map <std::string, std::map <T, library<T>>> &libs)
{
	for (size_t i = 0; i < solution.size(); i++)
	{
		sameLibExecution<T>(libs.find(solution[i]->second.name));
		solution[i]->second.status = libStatus::install;
		for (size_t j = 0; j < solution[i]->second.conflicts.size(); j++)
		{
			notInstall<T>(solution[i]->second.conflicts[j], libs);
		}
	}
}
//функция, нивелирующая работу предыдущей функции
template <class T>
void deleteSolution(std::vector <typename std::map <T, library<T>>::iterator> solution, std::map <std::string, std::map <T, library<T>>> &libs)
{
	for (size_t i = 0; i < solution.size(); i++)
	{
		solution[i]->second.status = libStatus::notInvolved;
		sameLibRecovery<T>(libs.find(solution[i]->second.name));
		for (size_t j = 0; j < solution[i]->second.conflicts.size(); j++)
		{
			notInstallRecovery<T>(solution[i]->second.conflicts[j], libs);
		}
	}
}
//рекурсивные функции, переходящие одна в другую
template <typename T>
std::vector <std::vector <typename std::map <T, library<T>>::iterator>> transit(std::tuple <std::string, std::string, T> target,
	std::map <std::string, std::map <T, library<T>>> &libs, std::vector <typename std::map <T, library<T>>::iterator> &resolution);
//newBranch пытается создать новую ветвь в дереве решений проверкой нового элемента на наличие помех, если ей это удаётся, то возвращает набор решений, разросшихся из этой вершины
template <class T>
std::vector <std::vector <typename std::map <T, library<T>>::iterator>> newBranch(typename std::map <T, library<T>>::iterator leaf,
	std::map <std::string, std::map <T, library<T>>> &libs, std::vector <typename std::map <T, library<T>>::iterator> &resolution)
{
	std::vector <std::vector <typename std::map <T, library<T>>::iterator>> addition;
	if (leaf->second.status == libStatus::install)
	{//элемент уже установлен, можно добавлять в набор решений
		addition.push_back(resolution);
		return addition;
	}
	//элемент уже запрещён, возвращается пустой набор решений
	if (leaf->second.status == libStatus::notInstall)
		return addition;

	if (!sameLibExecution<T>(libs.find(leaf->second.name)))
		return addition;

	leaf->second.status = libStatus::install;
	auto backup = resolution;//создаётся резервная копия текущего пути до данной вершины для восстановления исходных значений
	resolution.push_back(leaf);//элемент добавляется в набор решений
	
	bool exitFlag = true;//переключатель
	size_t confCount = 0;
	for (; confCount < leaf->second.conflicts.size(); confCount++)
	{
		if (!notInstall<T>(leaf->second.conflicts[confCount], libs))
		{
			exitFlag = false;//если разрешение конфликтов невозможно, значение будут восстановлены
			break;
		}
	}
	//если не возникло проблем с конфликтами и зависимостей нет, можно добавлять в набор решений
	if (exitFlag && leaf->second.requirements.size() == 0)
	{
		addition.push_back(resolution);
		exitFlag = false;
	}

	if (exitFlag)
	{//создаётся дополнителный вектор, который для каждого решения указывает количество выполненных зависимостей данного элемента
		std::vector <std::pair <size_t, std::vector <typename std::map <T, library<T>>::iterator>>> solutionSet = { std::make_pair(0, resolution) };
		for (size_t sol = 0; sol < solutionSet.size();)//стартовое значение - текущий путь
		{//при добавлении новых решений вектор будет расширяться
			resolution = solutionSet[sol].second;
			installSolution<T>(solutionSet[sol].second, libs);
			try
			{//transit возвращает набор решений для данной зависимости
				addition = transit<T>(leaf->second.requirements[solutionSet[sol].first], libs, resolution);
			}
			catch (std::invalid_argument&) { throw; }
			for (size_t k = 0; k < addition.size(); k++)//после чего тот добавляется в вектор с увеличенным количеством учтённых зависимостей
			{
				solutionSet.insert(solutionSet.begin() + sol + k + 1, std::make_pair(solutionSet[sol].first + 1, addition[k]));
			}
			deleteSolution<T>(solutionSet[sol].second, libs);
			solutionSet.erase(solutionSet.begin() + sol);//текущее решение, уже не релевантное, удаляется, на его место встаёт либо более полное, либо следующее
			if (sol != solutionSet.size())
			{//если данный набор решений учё все зависимости, переходим к следующему
				while (solutionSet[sol].first == leaf->second.requirements.size())
				{
					sol++;
					if (sol == solutionSet.size())
						break;
				}
			}
		}
		addition.clear();
		for (auto k = solutionSet.begin(); k != solutionSet.end(); k++)
		{
			addition.push_back(k->second);
		}
	}
	//нивелируем последствия работы функции
	for (size_t k = 0; k < confCount; k++)
		notInstallRecovery<T>(leaf->second.conflicts[k], libs);
	sameLibRecovery<T>(libs.find(leaf->second.name));
	resolution = backup;
	installSolution<T>(resolution, libs);
	return addition;
}
//transit отвечает за выбор элемента и последующую попытку встроить его в дерево
template <typename T>
std::vector <std::vector <typename std::map <T, library<T>>::iterator>> transit(std::tuple <std::string, std::string, T> target,
	std::map <std::string, std::map <T, library<T>>> &libs, std::vector <typename std::map <T, library<T>>::iterator> &resolution)
{
	auto namesPlace = libs.find(std::get<0>(target));
	if (namesPlace == libs.end())
		throw std::invalid_argument("library not found");
	std::vector <std::vector <typename std::map <T, library<T>>::iterator>> solutionSet, addition;
	for (auto i = namesPlace->second.begin(); i != namesPlace->second.end(); i++)
	{
		try
		{
			if (relOperCompare<T>(std::get<1>(target), i->first, std::get<2>(target)))
			{
				addition = newBranch<T>(i, libs, resolution);//новый набор решений добавляется к старому
				solutionSet.insert(solutionSet.end(), addition.begin(), addition.end());
			}
		}
		catch (const std::invalid_argument&) { throw; }
	}
	return solutionSet;
}

template <class T>
std::vector <typename std::map <T, library<T>>::iterator> resolve(std::map <std::string, std::map <T, library<T>>> &libs,
	std::vector <std::tuple <std::string, std::string, T>> &targets)
{
	std::vector <typename std::map <T, library<T>>::iterator> resolution;
	std::vector <std::vector <typename std::map <T, library<T>>::iterator>> solutionSet;
	std::vector <std::pair <size_t, std::vector <typename std::map <T, library<T>>::iterator>>> additionSet = { std::make_pair(0, resolution) };
	//логика функции resolve - вторая половина newBranch, за исключением, что текущий путь пуст
	for (size_t sol = 0; sol < additionSet.size();)
	{
		installSolution<T>(additionSet[sol].second, libs);
		resolution = additionSet[sol].second;
		try
		{
			solutionSet = transit<T>(targets[additionSet[sol].first], libs, resolution);
		}
		catch (const std::invalid_argument&) { throw; }
		for (size_t k = 0; k < solutionSet.size(); k++)
		{
			additionSet.insert(additionSet.begin() + sol + k + 1, std::make_pair(additionSet[sol].first + 1, solutionSet[k]));
		}
		deleteSolution<T>(additionSet[sol].second, libs);
		additionSet.erase(additionSet.begin() + sol);
		if (sol != additionSet.size())
		{
			while (additionSet[sol].first == targets.size())
			{
				sol++;
				if (sol == additionSet.size())
					break;
			}
		}
	}
	resolution.resize(0);
	//если решений не найдено, то разрешение невозможно
	if (additionSet.size() > 0)
		resolution = additionSet[additionSet.size() - 1].second;

	return resolution;
}

template <class T>
void printSolution(std::ostream &os, std::vector <typename std::map <T, library<T>>::iterator> solution, std::map <std::string, std::map <T, library<T>>> &libs)
{
	installSolution<T>(solution, libs);
	for (auto i = libs.begin(); i != libs.end(); i++)
	{
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			if (j->second.status == libStatus::install)
			{
				os << i->first << ' ' << j->first << std::endl;
			}
		}
	}
}
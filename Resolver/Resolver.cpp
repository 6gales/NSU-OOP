#include "Resolver.h"

bool isVersion(const std::string &version)
{
	bool expect = true;
	for (size_t i = 0; i < version.size(); i++)
	{
		if (expect)
		{
			if (version[i] < '0' || version[i] > '9')
				return false;
			expect = false;
		}
		else
		{
			if ((version[i] < '0' || version[i] > '9') && version[i] != '.')
				return false;
			if (version[i] == '.')
				expect = true;
		}		
	}
	if (expect)
		return false;
	return true;
}

std::string shrink(const std::string &str)
{
	std::string newStr = str;
	try
	{
		while (std::stoul(newStr.substr(newStr.rfind('.') + 1, newStr.size())) == 0 && newStr.find('.') != newStr.npos)
			newStr = newStr.substr(0, newStr.rfind('.'));
	}
	catch (const std::out_of_range&) { throw; }
	return newStr;
}

versionType::versionType(const std::string &version)
{
	if (version.empty() || !isVersion(version))
		throw std::invalid_argument(version);
//		throw std::invalid_argument("not a version");
	strVersion = version;
	std::string tmp;
	try
	{
		tmp = shrink(version);
	}
	catch (const std::out_of_range&) { throw; }
	tmp.push_back('.');
	while (tmp.find('.') != tmp.npos)
	{
		try
		{
			sepVersion.push_back(std::stoul(tmp.substr(0, tmp.find('.'))));
		}
		catch (const std::out_of_range&) { throw; }
		tmp = tmp.substr(tmp.find('.') + 1, tmp.size());
	}
}

versionType::versionType(const char *version)
{
	strVersion = version;
	if (strVersion.empty() || !isVersion(strVersion))
		throw std::invalid_argument(version);
//		throw std::invalid_argument("not a version");
	std::string tmp;
	try
	{
		tmp = shrink(version);
	}
	catch (const std::out_of_range&) { throw; }
	tmp.push_back('.');
	while (tmp.find('.') != tmp.npos)
	{
		try
		{
			sepVersion.push_back(std::stoul(tmp.substr(0, tmp.find('.'))));
		}
		catch (const std::out_of_range&) { throw; }
		tmp = tmp.substr(tmp.find('.') + 1, tmp.size());
	}
}

versionType::versionType(const versionType &version)
{
	strVersion = version.strVersion;
	sepVersion = version.sepVersion;
}

versionType &versionType::operator=(const std::string &version)
{
	if (version.empty() || !isVersion(version))
		throw std::invalid_argument("not a version");
	strVersion = version;
	sepVersion.resize(0);
	std::string tmp;
	try
	{
		tmp = shrink(version);
	}
	catch (const std::out_of_range&) { throw; }
	tmp.push_back('.');
	while (tmp.find('.') != tmp.npos)
	{
		try
		{
			sepVersion.push_back(std::stoul(tmp.substr(0, tmp.find('.'))));
		}
		catch (const std::out_of_range&) { throw; }
		tmp = tmp.substr(tmp.find('.') + 1, tmp.size());
	}
	return *this;
}

versionType &versionType::operator=(const char *version)
{
	strVersion = version;
	if (strVersion.empty() || !isVersion(strVersion))
		throw std::invalid_argument("not a version");
	sepVersion.resize(0);
	std::string tmp;
	try
	{
		tmp = shrink(version);
	}
	catch (const std::out_of_range&) { throw; }
	tmp.push_back('.');
	while (tmp.find('.') != tmp.npos)
	{
		try
		{
			sepVersion.push_back(std::stoul(tmp.substr(0, tmp.find('.'))));
		}
		catch (const std::out_of_range&) { throw; }
		tmp = tmp.substr(tmp.find('.') + 1, tmp.size());
	}
	return *this;
}

versionType &versionType::operator=(const versionType &version)
{
	strVersion = version.strVersion;
	sepVersion = version.sepVersion;
	return *this;
}

int vecCmp(const std::vector <size_t> &a, const std::vector <size_t> &b)
{
	size_t minSize = ((a.size() < b.size()) ? a.size() : b.size());
	for (size_t i = 0; i < minSize; i++)
	{
		if (a[i] < b[i])
			return -1;
		if (a[i] > b[i])
			return 1;
	}
	if (a.size() < b.size())
		return -1;
	if (a.size() > b.size())
		return 1;
	return 0;
}
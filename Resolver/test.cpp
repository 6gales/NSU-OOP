#define _CRT_SECURE_NO_WARNINGS
#define CATCH_CONFIG_MAIN
#include "Resolver.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("vecCmp")
{
	std::vector <size_t> a = { 10, 1, 3 };
	std::vector <size_t> b = { 10, 5 };
	REQUIRE(vecCmp(a, b) == -1);
	REQUIRE(vecCmp(b, a) == 1);
	REQUIRE(vecCmp(a, a) == 0);
}

TEST_CASE("Shrink version")
{
	std::string a = shrink("10.0.11.0"), b = shrink("0.0.0"), c = shrink("15.6.6.2");
	REQUIRE(a == "10.0.11");
	REQUIRE(b == "0");
	REQUIRE(c == "15.6.6.2");
}

TEST_CASE("Shrink exception")
{
	std::string a;
	try
	{
		a = shrink("10.0.11111111111111111.0");
	}
	catch (const std::out_of_range &e) { REQUIRE(true); }
}

TEST_CASE("isVersion")
{
	std::string a("10.0.11.0"), b("0.0.0"), c("10,3,5"), d("14.rrra"), e("11..11");
	REQUIRE(isVersion(a) == 1);
	REQUIRE(isVersion(b) == 1);
	REQUIRE(isVersion(c) == 0);
	REQUIRE(isVersion(d) == 0);
	REQUIRE(isVersion(e) == 0);
}

TEST_CASE("versionType constructor")
{
	std::string str = "10.8.0";
	versionType a = "10.8.0",
		b = str,
		c = a;
	std::stringstream out;
	out << a << '\n' << b << '\n' << c << '\n' << str << '\n';
	REQUIRE(out.str() == "10.8.0\n10.8.0\n10.8.0\n10.8.0\n");
}

TEST_CASE("versionType constructor exceptions")
{
	std::string str = "10..8.0";
	try { versionType a = ""; }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { versionType b = str; }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { versionType c = "5.55.555555555555555555555555"; }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { versionType d = "5.55.555555555555555555555555.66"; }
	catch (const std::out_of_range &e) { REQUIRE(true); }
}

TEST_CASE("versionType operator=")
{
	versionType a, b, c;
	std::string str = "10.8.0";
	a = "10.8.0";
	b = str;
	c = a;
	std::stringstream out;
	out << a << '\n' << b << '\n' << c << '\n' << str << '\n';
	REQUIRE(out.str() == "10.8.0\n10.8.0\n10.8.0\n10.8.0\n");
}

TEST_CASE("versionType operator= exceptions")
{
	versionType a;
	std::string str = "10..8.0";
	try { a = ""; }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { a = str; }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { a = "5.55.555555555555555555555555"; }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { a = "5.55.555555555555555555555555.66"; }
	catch (const std::out_of_range &e) { REQUIRE(true); }
}

TEST_CASE("versionType compare")
{
	versionType a = "14.56.424.0", b = "15.66.2";
	REQUIRE((a > b) == 0);
	REQUIRE((a >= b) == 0);
	REQUIRE((a <= b) == 1);
	REQUIRE((a < b) == 1);
	REQUIRE((a != b) == 1);
	REQUIRE((a == b) == 0);
}

TEST_CASE("Default version value")
{
	REQUIRE(defaultValue<versionType>() == "0.0");
	REQUIRE(defaultValue<std::string>() == "\0");
	REQUIRE(defaultValue<int>() == std::numeric_limits<int>::min());
	REQUIRE(defaultValue<short>() == std::numeric_limits<short>::min());
	REQUIRE(defaultValue<long int>() == std::numeric_limits<long int>::min());
	REQUIRE(defaultValue<long long>() == std::numeric_limits<long long>::min());
	REQUIRE(defaultValue<double>() == -std::numeric_limits<double>::max());
	REQUIRE(defaultValue<long double>() == -std::numeric_limits<long double>::max());
	REQUIRE(defaultValue<float>() == -std::numeric_limits<float>::max());
	REQUIRE(defaultValue<char>() == std::numeric_limits<char>::min());
	REQUIRE(defaultValue<bool>() == false);
	REQUIRE(defaultValue<unsigned long int>() == 0);
	REQUIRE(defaultValue<unsigned int>() == 0);
	REQUIRE(defaultValue<unsigned char>() == 0);
	REQUIRE(defaultValue<unsigned long long>() == 0);
	REQUIRE(defaultValue<unsigned short int>() == 0);
}

TEST_CASE("Convert from string to template type")
{
	REQUIRE(strConvert<versionType>("1.2.56") == "1.2.56");
	REQUIRE(strConvert<std::string>("aaa") == "aaa");
	REQUIRE(strConvert<int>("-4455145") == -4455145);
	REQUIRE(strConvert<short>("-1456") == -1456);
	REQUIRE(strConvert<long int>("56667544") == 56667544);
	REQUIRE(strConvert<long long>("666666666666") == 666666666666);
	REQUIRE(strConvert<double>("6.65435454") == 6.65435454);
	REQUIRE(strConvert<long double>("67544.5") == 67544.5);
	REQUIRE(strConvert<float>("554.5") == 554.5);
	REQUIRE(strConvert<char>("asd") == 'a');
	REQUIRE(strConvert<bool>("false") == false);
	REQUIRE(strConvert<bool>("0") == false);
	REQUIRE(strConvert<bool>("true") == true);
	REQUIRE(strConvert<bool>("1") == true);
	REQUIRE(strConvert<unsigned long int>("56565555") == 56565555);
	REQUIRE(strConvert<unsigned int>("56565655") == 56565655);
	REQUIRE(strConvert<unsigned char>("%&|?") == '%');
	REQUIRE(strConvert<unsigned long long>("6666666666666555") == 6666666666666555);
	REQUIRE(strConvert<unsigned short int>("45342") == 45342);
}

TEST_CASE("Convert from string to template type exceptions")
{
	try { strConvert<int>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<short>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<long int>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<long long>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<double>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<float>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<long double>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<char>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<bool>(""); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<unsigned int>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<unsigned long int>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<unsigned char>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<unsigned long long>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try { strConvert<unsigned short int>("888888888888888888888888888888"); }
	catch (const std::out_of_range &e) { REQUIRE(true); }

	try { strConvert<int>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<short int>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<long int>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<long long int>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<unsigned int>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<unsigned long int>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<unsigned short int>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<char>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<unsigned char>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<bool>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<float>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<double>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try { strConvert<long double>("aaaaaaaa"); }
	catch (const std::invalid_argument &e) { REQUIRE(true); }
}

TEST_CASE("Separate")
{
	auto a = separate<versionType>("A > 1.1"), b = separate<versionType>("B 1.2"), c = separate<versionType>("C"), 
		d = separate<versionType>("D <= 1.3 "), e = separate<versionType>("E 1.8 "), f = separate<versionType>("F ");

	REQUIRE(std::get<0>(a) == "A");
	REQUIRE(std::get<1>(a) == ">");
	REQUIRE(std::get<2>(a) == "1.1");

	REQUIRE(std::get<0>(b) == "B");
	REQUIRE(std::get<1>(b) == "==");
	REQUIRE(std::get<2>(b) == "1.2");

	REQUIRE(std::get<0>(c) == "C");
	REQUIRE(std::get<1>(c) == ">=");
	REQUIRE(std::get<2>(c) == "0.0");

	REQUIRE(std::get<0>(d) == "D");
	REQUIRE(std::get<1>(d) == "<=");
	REQUIRE(std::get<2>(d) == "1.3");

	REQUIRE(std::get<0>(e) == "E");
	REQUIRE(std::get<1>(e) == "==");
	REQUIRE(std::get<2>(e) == "1.8");

	REQUIRE(std::get<0>(f) == "F");
	REQUIRE(std::get<1>(f) == ">=");
	REQUIRE(std::get<2>(f) == "0.0");
}

TEST_CASE("Separate exceptions case")
{
	try
	{
		separate<versionType>("A  1.1");
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try
	{
		separate<versionType>("A 1./1");
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try
	{
		separate<short>("B 555555555555555555");
	}
	catch (const std::out_of_range &e) { REQUIRE(true); }
	try
	{
		separate<versionType>("A >= 1.1 <> 99");
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try
	{
		separate<versionType>("");
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	try
	{
		separate<int>("A > aaaa");
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
}

TEST_CASE("libReading")
{
	std::ifstream a("build/testlibs.txt");
	auto res = libReading<versionType>(a);
	auto bigIt = res.begin();
	auto smallIt = bigIt->second.begin();
	REQUIRE(bigIt->first == "A");
	REQUIRE(smallIt->first == "1.0");
	REQUIRE(smallIt->second.conflicts[0] == std::make_tuple<std::string, std::string, versionType>("C", "<=", "12.2"));
	REQUIRE(smallIt->second.conflicts[1] == std::make_tuple<std::string, std::string, versionType>("B", "==", "1.0"));
	REQUIRE(smallIt->second.requirements[0] == std::make_tuple<std::string, std::string, versionType>("B", ">=", "0.0"));
	smallIt++;
	REQUIRE(smallIt->first == "1.1");
	REQUIRE(smallIt->second.conflicts[0] == std::make_tuple<std::string, std::string, versionType>("B", ">", "1.0"));
	REQUIRE(smallIt->second.requirements[0] == std::make_tuple<std::string, std::string, versionType>("C", ">=", "0.0"));
	smallIt++;
	REQUIRE(smallIt == bigIt->second.end());
	bigIt++;
	smallIt = bigIt->second.begin();
	REQUIRE(bigIt->first == "B");
	REQUIRE(smallIt->first == "1.0");
	REQUIRE(smallIt->second.conflicts.size() == 0);
	REQUIRE(smallIt->second.requirements.size() == 0);
	smallIt++;
	REQUIRE(smallIt->first == "1.3");
	REQUIRE(smallIt->second.requirements[0] == std::make_tuple<std::string, std::string, versionType>("C", "==", "1.9"));
	smallIt++;
	REQUIRE(smallIt == bigIt->second.end());
	bigIt++;
	smallIt = bigIt->second.begin();
	REQUIRE(bigIt->first == "C");
	REQUIRE(smallIt->first == "1.9");
	REQUIRE(smallIt->second.conflicts[0] == std::make_tuple<std::string, std::string, versionType>("B", "==", "1.3"));
	REQUIRE(smallIt->second.requirements.size() == 0);
	smallIt++;
	REQUIRE(smallIt == bigIt->second.end());
	bigIt++;
	REQUIRE(bigIt == res.end());
}

TEST_CASE("libReading with exceptions")
{
	std::ifstream eifs;
	eifs.open("build/testlibsE0.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE1.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::out_of_range &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE2.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE3.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE4.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::out_of_range &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE5.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE6.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE7.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::out_of_range &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE8.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE9.txt");
	try
	{
		libReading<versionType>(eifs);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
	eifs.close();
}

TEST_CASE("targetReading")
{
	std::ifstream tifs("build/testtargets.txt");
	auto targets = targetReading<versionType>(tifs);
	REQUIRE(targets[0] == std::make_tuple<std::string, std::string, versionType>("A", ">=", "1.2"));
	REQUIRE(targets[1] == std::make_tuple<std::string, std::string, versionType>("B", "==", "1.0"));
	REQUIRE(targets[2] == std::make_tuple<std::string, std::string, versionType>("C", ">=", "0.0"));
	REQUIRE(targets[3] == std::make_tuple<std::string, std::string, versionType>("D", "<", "3"));
	REQUIRE(targets[4] == std::make_tuple<std::string, std::string, versionType>("E", "==", "9.1.2"));
	REQUIRE(targets[5] == std::make_tuple<std::string, std::string, versionType>("F", ">=", "0.0"));
	tifs.close();
}

TEST_CASE("targetReading with exceptions")
{
	std::ifstream eifs;
	eifs.open("build/testtargetsE0.txt");
	try
	{
		targetReading<versionType>(eifs);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testtargetsE1.txt");
	try
	{
		targetReading<versionType>(eifs);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testtargetsE2.txt");
	try
	{
		targetReading<versionType>(eifs);
	}
	catch (const std::out_of_range&) { REQUIRE(true); }
	eifs.close();
}

TEST_CASE("Relative operator compare")
{
	versionType a = "14.56.424.0", b = "15.66.2";
	REQUIRE((a > b) == relOperCompare<versionType>(">", a, b));
	REQUIRE((a >= b) == relOperCompare<versionType>(">=", a, b));
	REQUIRE((a <= b) == relOperCompare<versionType>("<=", a, b));
	REQUIRE((a < b) == relOperCompare<versionType>("<", a, b));
	REQUIRE((a != b) == relOperCompare<versionType>("!=", a, b));
	REQUIRE((a == b) == relOperCompare<versionType>("==", a, b));
	REQUIRE((a == b) == relOperCompare<versionType>("=", a, b));
}

TEST_CASE("Relative operator compare exception")
{
	versionType a = "14.56.424.0", b = "15.66.2";
	try
	{
		relOperCompare<versionType>(">>", a, b);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
}

TEST_CASE("notInstall")
{
	std::ifstream tifs("build/testlibsSE.txt");
	auto libs = libReading<versionType>(tifs);
	notInstall(std::make_tuple<std::string, std::string, versionType>("B", ">=", "0.0"), libs);
	auto it = libs.find("B");
	for (auto i = it->second.begin(); i != it->second.end(); i++)
		REQUIRE(i->second.status == libStatus::notInstall);

	libs.find("C")->second.find("1.9")->second.status = libStatus::install;
	notInstall(std::make_tuple<std::string, std::string, versionType>("C", ">=", "0.0"), libs);
	it = libs.find("C");
	for (auto i = it->second.begin(); i != it->second.end(); i++)
	{
		if (i->first != "1.9")
			REQUIRE(i->second.status == libStatus::notInvolved);
		else REQUIRE(i->second.status == libStatus::install);
	}
}

TEST_CASE("notInstall exceptions")
{
	std::ifstream tifs("build/testlibsSE.txt");
	auto libs = libReading<versionType>(tifs);
	try
	{
		notInstall(std::make_tuple<std::string, std::string, versionType>("A", ">=<", "0.0"), libs);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	try
	{
		notInstall(std::make_tuple<std::string, std::string, versionType>("a", "==", "1.0"), libs);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
}

TEST_CASE("notInstallRecovery")
{
	std::ifstream tifs("build/testlibsSE.txt");
	auto libs = libReading<versionType>(tifs);
	notInstall(std::make_tuple<std::string, std::string, versionType>("B", ">=", "0.0"), libs);
	notInstall(std::make_tuple<std::string, std::string, versionType>("C", ">=", "0.0"), libs);
	notInstallRecovery(std::make_tuple<std::string, std::string, versionType>("B", ">=", "0.0"), libs);
	auto it = libs.find("B");
	for (auto i = it->second.begin(); i != it->second.end(); i++)
		REQUIRE(i->second.status == libStatus::notInvolved);
	notInstallRecovery(std::make_tuple<std::string, std::string, versionType>("C", ">=", "0.0"), libs);
	it = libs.find("C");
	for (auto i = it->second.begin(); i != it->second.end(); i++)
		REQUIRE(i->second.status == libStatus::notInvolved);
}

TEST_CASE("sameLibExecution")
{
	std::ifstream tifs("build/testlibsSE.txt");
	auto libs = libReading<versionType>(tifs);
	auto bigIt = libs.find("B");
	sameLibExecution<versionType>(bigIt);
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInstall);
	}
	bigIt = libs.find("A");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
	bigIt = libs.find("C");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
	bigIt->second.find("1.9")->second.status = libStatus::install;
	sameLibExecution<versionType>(bigIt);
	bigIt = libs.find("B");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInstall);
	}
	bigIt = libs.find("A");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
	bigIt = libs.find("C");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		if (i->first != "1.9")
			REQUIRE(i->second.status == libStatus::notInvolved);
		else REQUIRE(i->second.status == libStatus::install);
	}
}

TEST_CASE("sameLibRecovery")
{
	std::ifstream tifs("build/testlibsSE.txt");
	auto libs = libReading<versionType>(tifs);
	auto bigIt = libs.find("B");
	sameLibExecution<versionType>(bigIt);
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInstall);
	}
	bigIt = libs.find("A");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
	bigIt = libs.find("C");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
	bigIt = libs.find("B");
	sameLibRecovery<versionType>(bigIt);
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
	bigIt = libs.find("A");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
	bigIt = libs.find("C");
	for (auto i = bigIt->second.begin(); i != bigIt->second.end(); i++)
	{
		REQUIRE(i->second.status == libStatus::notInvolved);
	}
}

TEST_CASE("installSolution")
{
	std::ifstream tifs("build/testlibs.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	installSolution(resolution, libs);
	REQUIRE(libs.find("A")->second.find("1.1")->second.status == libStatus::install);
	REQUIRE(libs.find("C")->second.find("1.9")->second.status == libStatus::install);
	REQUIRE(libs.find("A")->second.find("1.0")->second.status == libStatus::notInstall);
	REQUIRE(libs.find("B")->second.find("1.3")->second.status == libStatus::notInstall);
	REQUIRE(libs.find("B")->second.find("1.0")->second.status == libStatus::notInvolved);
}

TEST_CASE("deleteSolution")
{
	std::ifstream tifs("build/testlibs.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	installSolution(resolution, libs);
	REQUIRE(libs.find("A")->second.find("1.1")->second.status == libStatus::install);
	REQUIRE(libs.find("C")->second.find("1.9")->second.status == libStatus::install);
	REQUIRE(libs.find("A")->second.find("1.0")->second.status == libStatus::notInstall);
	REQUIRE(libs.find("B")->second.find("1.3")->second.status == libStatus::notInstall);
	REQUIRE(libs.find("B")->second.find("1.0")->second.status == libStatus::notInvolved);
	deleteSolution(resolution, libs);
	REQUIRE(libs.find("A")->second.find("1.1")->second.status == libStatus::notInvolved);
	REQUIRE(libs.find("C")->second.find("1.9")->second.status == libStatus::notInvolved);
	REQUIRE(libs.find("A")->second.find("1.0")->second.status == libStatus::notInvolved);
	REQUIRE(libs.find("B")->second.find("1.3")->second.status == libStatus::notInvolved);
	REQUIRE(libs.find("B")->second.find("1.0")->second.status == libStatus::notInvolved);
}

TEST_CASE("newBranch depth 0")
{
	std::ifstream tifs("build/testlibs.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	libs.find("A")->second.find("1.1")->second.status = libStatus::install;
	libs.find("B")->second.find("1.3")->second.status = libStatus::notInstall;
	libs.find("C")->second.find("1.9")->second.status = libStatus::install;
	auto set = newBranch<versionType>(libs.find("C")->second.find("1.9"), libs, resolution);
	REQUIRE(set.size() == 1);
	REQUIRE(set[0] == resolution);
	set = newBranch<versionType>(libs.find("B")->second.find("1.3"), libs, resolution);
	REQUIRE(set.size() == 0);
	set = newBranch<versionType>(libs.find("A")->second.find("1.0"), libs, resolution);
	REQUIRE(set.size() == 0);
}

TEST_CASE("newBranch depth 0 another case")
{
	std::ifstream tifs("build/testlibs1.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1") };
	libs.find("A")->second.find("1.1")->second.status = libStatus::install;
	libs.find("B")->second.find("1.3")->second.status = libStatus::notInstall;
	auto set = newBranch<versionType>(libs.find("C")->second.find("1.9"), libs, resolution);
	REQUIRE(set.size() == 1);
	resolution.push_back(libs.find("C")->second.find("1.9"));
	REQUIRE(set[0] == resolution);
}

TEST_CASE("transit into newBranch depth 0")
{
	std::ifstream tifs("build/testlibs.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	libs.find("A")->second.find("1.1")->second.status = libStatus::install;
	libs.find("B")->second.find("1.3")->second.status = libStatus::notInstall;
	libs.find("C")->second.find("1.9")->second.status = libStatus::install;
	auto set = transit<versionType>(std::make_tuple<std::string, std::string, versionType>("C", ">=", "0.0"), libs, resolution);
	REQUIRE(set.size() == 1);
	REQUIRE(set[0] == resolution);
}

TEST_CASE("newBranch depth 1")
{
	std::ifstream tifs("build/testlibs.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1") };
	libs.find("A")->second.find("1.1")->second.status = libStatus::install;
	libs.find("B")->second.find("1.3")->second.status = libStatus::notInstall;
	auto set = newBranch<versionType>(libs.find("C")->second.find("1.9"), libs, resolution);
	REQUIRE(set.size() == 1);
	resolution.push_back(libs.find("C")->second.find("1.9"));
	REQUIRE(set[0] == resolution);
}

TEST_CASE("transit into newBranch depth 1")
{
	std::ifstream tifs("build/testlibs.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1") };
	libs.find("A")->second.find("1.1")->second.status = libStatus::install;
	libs.find("B")->second.find("1.3")->second.status = libStatus::notInstall;
	auto set = transit<versionType>(std::make_tuple<std::string, std::string, versionType>("C", "<=", "1.9"), libs, resolution);
	REQUIRE(set.size() == 1);
	resolution.push_back(libs.find("C")->second.find("1.9"));
	REQUIRE(set[0] == resolution);
}

TEST_CASE("newBranch depth 2")
{
	std::ifstream tifs("build/testlibs.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution;
	auto set = newBranch<versionType>(libs.find("A")->second.find("1.1"), libs, resolution);
	REQUIRE(set.size() == 1);
	resolution.push_back(libs.find("A")->second.find("1.1"));
	resolution.push_back(libs.find("C")->second.find("1.9"));
	REQUIRE(set[0] == resolution);
	resolution.clear();
	set = newBranch<versionType>(libs.find("B")->second.find("1.3"), libs, resolution);
	REQUIRE(set.size() == 0);
}

TEST_CASE("transit into newBranch depth 2")
{
	std::ifstream tifs("build/testlibs1.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution;
	auto set = transit<versionType>(std::make_tuple<std::string, std::string, versionType>("A", ">=", "1.0"), libs, resolution);
	std::vector <typename std::map <versionType, library<versionType>>::iterator> res0 = { libs.find("A")->second.find("1.0"), libs.find("B")->second.find("1.3"), libs.find("C")->second.find("1.9") },
		res1 = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	REQUIRE(set.size() == 2);
	REQUIRE(set[0] == res0);
	REQUIRE(set[1] == res1);
}

TEST_CASE("transit exceptions")
{
	std::ifstream eifs;
	eifs.open("build/testlibsE10.txt");
	auto libs = libReading<versionType>(eifs);
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	libs.find("A")->second.find("1.1")->second.status = libStatus::install;
	libs.find("B")->second.find("1.3")->second.status = libStatus::notInstall;
	libs.find("C")->second.find("1.9")->second.status = libStatus::install;
	try
	{
		auto set = transit<versionType>(std::make_tuple<std::string, std::string, versionType>("F", ">=", "0.0"), libs, resolution);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE11.txt");
	libs = libReading<versionType>(eifs);
	resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	libs.find("A")->second.find("1.1")->second.status = libStatus::install;
	libs.find("B")->second.find("1.3")->second.status = libStatus::notInstall;
	libs.find("C")->second.find("1.9")->second.status = libStatus::install;
	try
	{
		auto set = transit<versionType>(std::make_tuple<std::string, std::string, versionType>("F", ">=", "0.0"), libs, resolution);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close();
}

TEST_CASE("newBranch exceptions")
{
	std::ifstream eifs("build/testlibsE10.txt");
	auto libs = libReading<versionType>(eifs);
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution;
	try
	{
		newBranch<versionType>(libs.find("A")->second.find("1.1"), libs, resolution);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close();
	eifs.open("build/testlibsE11.txt");
	libs = libReading<versionType>(eifs);
	resolution.clear();
	try
	{
		newBranch<versionType>(libs.find("A")->second.find("1.1"), libs, resolution);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close();
}

TEST_CASE("transit exceptions case 2")
{
	std::ifstream eifs("build/testlibsE10.txt");
	auto libs = libReading<versionType>(eifs);
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution;
	try
	{
		transit<versionType>(std::make_tuple<std::string, std::string, versionType>("A", "==", "1.1"), libs, resolution);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close(); 
	eifs.open("build/testlibsE11.txt");
	libs = libReading<versionType>(eifs);
	resolution.clear();
	try
	{
		transit<versionType>(std::make_tuple<std::string, std::string, versionType>("A", "==", "1.1"), libs, resolution);
	}
	catch (const std::invalid_argument&) { REQUIRE(true); }
	eifs.close();
}

TEST_CASE("Resolve")
{
	std::ifstream tifs("build/testlibs1.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <std::tuple <std::string, std::string, versionType>> targets = { std::make_tuple<std::string, std::string, versionType>("A", ">=", "0.0") };
	auto sol = resolve<versionType>(libs, targets);
	REQUIRE(sol.size() == 2);
	decltype(sol) resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	REQUIRE(sol == resolution);
}

TEST_CASE("Resolve impossible")
{
	std::ifstream tifs("build/testlibs1.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <std::tuple <std::string, std::string, versionType>> targets = { std::make_tuple<std::string, std::string, versionType>("A", ">=", "0.0"),
		std::make_tuple<std::string, std::string, versionType>("B", "==", "1.3"), std::make_tuple<std::string, std::string, versionType>("C", "<", "1.2") };
	auto sol = resolve<versionType>(libs, targets);
	REQUIRE(sol.size() == 0);
}

TEST_CASE("Resolve with exceptions")
{
	std::ifstream tifs("build/testlibs1.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <std::tuple <std::string, std::string, versionType>> targets = { std::make_tuple<std::string, std::string, versionType>("A", ">=", "0.0"),
		std::make_tuple<std::string, std::string, versionType>("B", "==", "1.3"), std::make_tuple<std::string, std::string, versionType>("C", "<==", "1.2") };
	try
	{
		resolve<versionType>(libs, targets);
	}
	catch (const std::invalid_argument &e) { REQUIRE(true); }
}

TEST_CASE("printSolution")
{
	std::ifstream tifs("build/testlibs1.txt");
	auto libs = libReading<versionType>(tifs);
	tifs.close();
	std::vector <typename std::map <versionType, library<versionType>>::iterator> resolution = { libs.find("A")->second.find("1.1"), libs.find("C")->second.find("1.9") };
	std::ostringstream os;
	printSolution(os, resolution, libs);
	REQUIRE(os.str() == "A 1.1\nC 1.9\n");
}
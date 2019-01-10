#define _CRT_SECURE_NO_WARNINGS
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "phrases.h"

using std::vector;
using std::string;
using std::pair;
using std::make_pair;

TEST_CASE("Input_1")
{
	unsigned int n = 2, m = 2;
	int argc = 4;
	char **argv = new char*[argc];
	for (int i = 0; i < argc; i++)
		argv[i] = new char[10];
	strcpy(argv[1], "-n");
	strcpy(argv[2], "3");
	strcpy(argv[3], "-");

	REQUIRE(fileInput(n, m, argc, argv) == 1);
	REQUIRE(n == 3);
	REQUIRE(m == 2);
	delete[] argv;
}

TEST_CASE("Input_2")
{
	unsigned int n = 2, m = 2;
	int argc = 7;
	char **argv = new char*[argc];
	for (int i = 0; i < argc; i++)
		argv[i] = new char[10];
	strcpy(argv[1], "-n");
	strcpy(argv[2], "8");
	strcpy(argv[3], "-m");
	strcpy(argv[4], "3");
	strcpy(argv[5], "-");
	strcpy(argv[6], "\\");

	REQUIRE(fileInput(n, m, argc, argv) == 0);
	delete[] argv;
}

TEST_CASE("Input_3")
{
	unsigned int n = 2, m = 2;
	int argc = 6;
	char **argv = new char*[argc];
	for (int i = 0; i < argc; i++)
		argv[i] = new char[10];
	strcpy(argv[1], "-n");
	strcpy(argv[2], "-13");
	strcpy(argv[3], "-m");
	strcpy(argv[4], "3");
	strcpy(argv[5], "main.cpp");

	REQUIRE(fileInput(n, m, argc, argv) == 0);
	delete[] argv;
}

TEST_CASE("Input_4")
{
	unsigned int n = 2, m = 2;
	int argc = 6;
	char **argv = new char*[argc];
	for (int i = 0; i < argc; i++)
		argv[i] = new char[10];
	strcpy(argv[1], "-n");
	strcpy(argv[2], "5");
	strcpy(argv[3], "-m");
	strcpy(argv[4], "6");
	strcpy(argv[5], "-");

	REQUIRE(fileInput(n, m, argc, argv) == 1);
	REQUIRE(n == 5);
	REQUIRE(m == 6);
	delete[] argv;
}

TEST_CASE("Input_5")
{
	unsigned int n = 2, m = 2;
	int argc = 1;
	char **argv;
	REQUIRE(fileInput(n, m, argc, argv) == 1);
	REQUIRE(n == 2);
	REQUIRE(m == 2);
}

TEST_CASE("Adhesion_1")
{
	unsigned int n = 2, point = 2;
	vector <string> input(n);
	input[0] = "Under";
	input[1] = "pressure!";
	string newPhrase = adhesion(n, point, input);
	
	REQUIRE(newPhrase == "Under pressure!");
	REQUIRE(point == 0);
}

TEST_CASE("Adhesion_2")
{
	unsigned int n = 4, point = 17;
	vector <string> input(n);
	input[0] = "sun";
	input[1] = "House";
	input[2] = "of";
	input[3] = "Rising";
	string newPhrase = adhesion(n, point, input);

	REQUIRE(newPhrase == "House of Rising sun");
	REQUIRE(point == 1);
}

TEST_CASE("Adhesion_3")
{
	unsigned int n = 13, point = 283;
	vector <string> input(n);
	input[0] = "goal,";
	input[1] = "one";
	input[2] = "mission,";
	input[3] = "one"; 
	input[4] = "heart,";
	input[5] = "one";
	input[6] = "soul,";
	input[7] = "one";
	input[8] = "true";
	input[9] = "religion";
	input[10] = "One";
	input[11] = "man,";
	input[12] = "one";
	string newPhrase = adhesion(n, point, input);

	REQUIRE(newPhrase == "One man, one goal, one mission, one heart, one soul, one true religion");
	REQUIRE(point == 10);
}

TEST_CASE("Addition_1")
{
	vector <pair<string, int>> test;
	test.reserve(5);
	test.push_back(make_pair("I'm burnin' through the", 2));
	test.push_back(make_pair("yeah, two hundred degrees", 11));
	test.push_back(make_pair("Give me a call", 6));
	test.push_back(make_pair("don't want to stop", 3));
	test.push_back(make_pair("I wanna make a", 4));

	string newPhrase = "Don't stop me now";
	findPhrase(test, newPhrase);

	REQUIRE(test[0].first == "I'm burnin' through the");
	REQUIRE(test[1].first == "yeah, two hundred degrees");
	REQUIRE(test[2].first == "Give me a call");
	REQUIRE(test[3].first == "don't want to stop");
	REQUIRE(test[4].first == "I wanna make a");
	REQUIRE(test[5].first == "Don't stop me now");
	
	REQUIRE(test[0].second == 2);
	REQUIRE(test[1].second == 11);
	REQUIRE(test[2].second == 6);
	REQUIRE(test[3].second == 3);
	REQUIRE(test[4].second == 4);
	REQUIRE(test[5].second == 1);

	REQUIRE(test.size() == 6);
}

TEST_CASE("Addition_2")
{
	vector <pair<string, int>> test;
	test.reserve(5);
	test.push_back(make_pair("I'm burnin' through the", 2));
	test.push_back(make_pair("yeah, two hundred degrees", 11));
	test.push_back(make_pair("Have a good time", 6));
	test.push_back(make_pair("don't want to stop", 3));
	test.push_back(make_pair("I wanna make a", 4));

	string newPhrase = "Have a good time";
	findPhrase(test, newPhrase);

	REQUIRE(test[0].first == "I'm burnin' through the");
	REQUIRE(test[1].first == "yeah, two hundred degrees");
	REQUIRE(test[2].first == "Have a good time");
	REQUIRE(test[3].first == "don't want to stop");
	REQUIRE(test[4].first == "I wanna make a");

	REQUIRE(test[0].second == 2);
	REQUIRE(test[1].second == 11);
	REQUIRE(test[2].second == 7);
	REQUIRE(test[3].second == 3);
	REQUIRE(test[4].second == 4);

	REQUIRE(test.size() == 5);
}
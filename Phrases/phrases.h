#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

bool compare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);

int fileInput(unsigned int &n, unsigned int &m, int argc, char **argv);

std::string adhesion(unsigned int n, unsigned int &point, std::vector <std::string> input);

void findPhrase(std::vector <std::pair<std::string, int>> &association, std::string newPhrase);

#pragma once
#include<vector>
#include<string>
#include<sstream>
std::vector<std::string> splitString(const std::string& input, char delimiter);
std::string mergeString(std::vector<std::string>, char delimiter = ' ');
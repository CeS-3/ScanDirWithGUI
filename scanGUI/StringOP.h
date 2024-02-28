#pragma once
#include<vector>
#include<string>
#include<sstream>

//传入一个字符串与分隔符字符，将传入的字符串按照分隔符进行切割，装入字符串向量中返回
std::vector<std::string> splitString(const std::string& input, char delimiter);

//传入一个字符串向量与分隔符字符（默认为空格），将向量中的各个字符串中间以分割符拼接起来返回
std::string mergeString(std::vector<std::string>, char delimiter = ' ');
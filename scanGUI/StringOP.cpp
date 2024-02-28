#include"StringOP.h"

//传入一个字符串与分隔符字符，将传入的字符串按照分隔符进行切割，装入字符串向量中返回
std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> substrs;
    std::istringstream tokenStream(input);
    std::string substr;
    while (std::getline(tokenStream, substr, delimiter)) {
        substrs.push_back(substr);
    }
    return substrs;
}

//传入一个字符串向量与分隔符字符（默认为空格），将向量中的各个字符串中间以分割符拼接起来返回
std::string mergeString(std::vector<std::string> substrs, char delimiter) {
    std::ostringstream oss;
    //先转化为字符串
    std::string sdelimiter(1, delimiter);
    std::copy(substrs.begin(), substrs.end(), std::ostream_iterator<std::string>(oss, sdelimiter.c_str()));
    std::string result = oss.str();
    return result;
}
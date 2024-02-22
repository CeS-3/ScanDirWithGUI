#include"StringOP.h"
//根据所给字符串与分割符将字符串分割为多个子串并存入队列中返回
std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> substrs;
    std::istringstream tokenStream(input);
    std::string substr;
    while (std::getline(tokenStream, substr, delimiter)) {
        substrs.push_back(substr);
    }
    return substrs;
}
//根据传入的字符串vector与分割符组合成字符串
std::string mergeString(std::vector<std::string> substrs, char delimiter) {
    std::ostringstream oss;
    //先转化为字符串
    std::string sdelimiter(1, delimiter);
    std::copy(substrs.begin(), substrs.end(), std::ostream_iterator<std::string>(oss, sdelimiter.c_str()));
    std::string result = oss.str();
    return result;
}
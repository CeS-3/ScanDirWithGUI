#pragma once
#include "DataLine.h"
class myfileLine : DataLine
{
public:
    myfileLine(const std::string OriginLine, rootDir* root) : DataLine(root) {
        //同上
        std::vector<std::string>substr = splitString(OriginLine, ',');
        //取出文件路径
        std::string target = substr[0];
        std::vector<std::string>path = splitString(target, '\\');
        //路径最末尾为文件名
        filename = path.back();
        //弹出文件名
        path.pop_back();
        //剩下的部分为TargetDirPath
        TargetDirPath = mergeString(path);
        //继续取出操作码
        operationCode = substr[1];
        //取出新time
        newTime = std::stol(substr[2]);
        //取出新size
        newSize = std::stol(substr[3]);
    }

    void excuteOperation();
    void AddOperation();
    void ModifyOperation();
    void DeleteOperation();
private:
    std::string operationCode;  //操作码(A,M,D)
    std::string filename; //操纵的文件名
    long int newSize;
    long int newTime;
};


#pragma once
#include"rootDir.h"
class DataLine
{
public:
    //输入原始行进行解析
    DataLine(rootDir& root) : root(root) {}
protected:
    rootDir root;
    std::string TargetDirPath;
};


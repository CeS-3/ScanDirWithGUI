#pragma once
#include"rootDir.h"
#include"DirInfo.h"
class DataLine
{
public:
    //输入原始行进行解析,输入rootDir的指针
    DataLine(rootDir* root) : root(root) {}
protected:
    rootDir* root;
    std::string TargetDirPath;
};


#pragma once
#include "DataLine.h"
#include"DirInfo.h"
class mystatLine : DataLine
{
public:
    //mystate中的原始行就是目标地址
    mystatLine(const std::string OriginLine, rootDir& root) : DataLine(root) {
        TargetDirPath = OriginLine;
    }
    //统计操作,返回统计所得目录信息对象
    const DirInfo statisticalOperation();
};


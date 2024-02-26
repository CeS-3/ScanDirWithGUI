#pragma once
#include "DataLine.h"
class mystatLine : DataLine
{
public:
    //mystate中的原始行就是目标地址
    mystatLine(std::string OriginLine, rootDir* root) : DataLine(root) {
        setLine(OriginLine);
    }
    mystatLine(rootDir* root): DataLine(root){}
    //设置原始行
    void setLine(std::string OriginLine) {
        TargetDirPath = OriginLine;
    }
    //统计操作,返回统计所得目录信息对象
    const DirInfo statisticalOperation();
};


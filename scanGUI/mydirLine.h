#pragma once
#include "DataLine.h"
class mydirLine : DataLine
{
public:
    //对原始行进行解析
    mydirLine(const std::string OriginLine, rootDir* root) : DataLine(root) {
        setLine(OriginLine);
    }
    mydirLine(rootDir* root) : DataLine(root) {}
    
    //设置需要解析的行
    void setLine(std::string OriginLine) {
        //以','为分隔符分割字符串
        std::vector<std::string>substr = splitString(OriginLine, ',');
        //获得的子串的第一个即为目标文件的地址
        TargetDirPath = substr.front();
    }
    
    //传入文件信息类型指针的向量，用于存储删除操作前的目录及其子目录的信息
    void DeleteOperation(std::vector<DirInfo>* before);
};

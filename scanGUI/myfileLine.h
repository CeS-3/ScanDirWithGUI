#pragma once
#include "DataLine.h"
class myfileLine : DataLine
{
public:
    myfileLine(const std::string OriginLine, rootDir* root) : DataLine(root) {
        setLine(OriginLine);
    }
    myfileLine(rootDir* root): DataLine(root) {}
    void setLine(std::string OriginLine) {
        //同上
        std::vector<std::string>substr = splitString(OriginLine, ',');
        //取出文件路径
        filePath = substr[0];
        std::vector<std::string>path = splitString(filePath, '\\');
        //路径最末尾为文件名
        filename = path.back();
        //弹出文件名
        path.pop_back();
        //剩下的部分为TargetDirPath
        TargetDirPath = mergeString(path,'\\');
        //继续取出操作码
        operationCode = substr[1];
        if (operationCode != "D") {  //当为D时得到的时间值为"time"无法进行转换
            //取出新time
            newTime = std::stol(substr[2]);
            //取出新size
            newSize = std::stoll(substr[3]);
        }
    }
    void excuteOperation(File* before,File* after);
    const std::string& GetPath() const{
        return filePath;
    }
private:
    std::string operationCode;  //操作码(A,M,D)
    std::string filename; //操纵的文件名
    std::string filePath;
    long long newSize;
    long int newTime;
};


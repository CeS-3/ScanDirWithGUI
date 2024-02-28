#pragma once
#include"File.h"
#include<vector>
//目录信息
class DirInfo {
public:
    std::string DirPath;
    File earliestFile;
    File latestFile;
    int FileSum;
    int FileSumSize;
    bool valid;
    DirInfo(std::string DirPath,const File& earliest, const File& latest, int sum, int sumSize,bool valid)
        : DirPath(DirPath), earliestFile(earliest), latestFile(latest), FileSum(sum), FileSumSize(sumSize),valid(valid) {}

    DirInfo(std::string DirPath,bool valid):DirPath(DirPath),valid(valid),earliestFile(valid),latestFile(valid) {}

    DirInfo():earliestFile(valid), latestFile(valid){}

    //定义目录信息的相等，若两者均合法且其他数值都相等或两者均非法则两信息相等
    bool operator==(const DirInfo& other) const {
        return (DirPath == other.DirPath && earliestFile == other.earliestFile && latestFile == other.latestFile \
            && FileSum == other.FileSum && FileSumSize == other.FileSumSize  && (valid && other.valid)|| (!valid && !other.valid));
    }
    //等于符号重载
    bool operator!=(const DirInfo& other) const {
        return !(*this == other);
    }

    //若信息有效，用于以格式化字符串形式输出信息
    std::string outPut() const;

    //输入两个一一对应的DirInfo向量，查找其中的差异并写入传入的字符串中
    static void differ(const std::vector<DirInfo>&first,const std::vector<DirInfo>&second, std::string& output);
};



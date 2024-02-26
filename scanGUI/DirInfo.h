#pragma once
#include"File.h"
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
};



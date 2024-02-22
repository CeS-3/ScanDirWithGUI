#pragma once
#include"File.h"
//目录信息
class DirInfo {
public:
    File earliestFile;
    File latestFile;
    int FileSum;
    int FileSumSize;
    DirInfo(const File& earliest, const File& latest, int sum, int sumSize)
        : earliestFile(earliest), latestFile(latest), FileSum(sum), FileSumSize(sumSize) {}
};



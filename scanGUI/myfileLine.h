#pragma once
#include "DataLine.h"

class myfileLine : public DataLine {
public:
    // 构造函数
    myfileLine(const std::string OriginLine, rootDir* root) : DataLine(root) {
        setLine(OriginLine);
    }

    // 重载构造函数
    myfileLine(rootDir* root) : DataLine(root) {}

    // 设置文件行信息
    void setLine(std::string OriginLine) {
        // 解析原始行数据
        std::vector<std::string> substr = splitString(OriginLine, ',');

        // 取出文件路径
        filePath = substr[0];
        std::vector<std::string> path = splitString(filePath, '\\');

        // 路径最末尾为文件名
        filename = path.back();

        // 弹出文件名
        path.pop_back();

        // 剩下的部分为TargetDirPath
        TargetDirPath = mergeString(path, '\\');

        // 继续取出操作码
        operationCode = substr[1];

        if (operationCode != "D") {
            // 当为D时得到的时间值为"time"无法进行转换
            // 取出新time
            newTime = std::stol(substr[2]);

            // 取出新size
            newSize = std::stoll(substr[3]);
        }
    }

    /*根据操作码执行对应的操作，传入两个文件指针用于记录执行前后的文件信息
    若before、after均非法则表示修改操作失败，若before与after均合法则修改成功
    若before为非法，after合法，则为新增成功，若before合法，after非法则为删除成功*/
    void excuteOperation(File* before, File* after);

    // 获取文件路径
    const std::string& GetPath() const {
        return filePath;
    }

private:
    std::string operationCode;  // 操作码(A,M,D)
    std::string filename;       // 操纵的文件名
    std::string filePath;
    long long newSize;
    long int newTime;
};

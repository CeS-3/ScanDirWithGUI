#pragma once
#include "DirectoryNode.h"
#include "StringOP.h"

class rootDir : public DirectoryNode {
public:
    // 构造函数
    rootDir(const std::string& name) : DirectoryNode(name) {};

    // 构建目录树 - 广度优先搜索
    void BuildTreeBFS();

    // 构建目录树 - 深度优先搜索
    void BuildTreeDFS();

    // 计算目录树深度
    int CountDepth();

    // 获取文件总数
    const int GetFileSum() const {
        return FileSum;
    }

    // 获取目录总数
    const int GetDirSum() const {
        return DirSum;
    }

    // 获取目录树深度
    const int GetDepth() const {
        return Depth;
    }

    // 获取最大目录名
    const std::string GetMaxName() const {
        return MaxName;
    }

    // 获取最大目录名长度
    const int GetMaxNameLength() const {
        return MaxNameLength;
    }

    // 搜索目录，输入一个目录绝对路径，返回指向该目录节点的指针
    DirectoryNode* SearchDir(const std::string DirPath);

    // 用于生成该目录系统的SQL文件，应输入两个路径，第一个为文件表SQL文件的路径，第二个为目录表SQL文件的路径
    void CreateSQL(const std::string Path);

protected:
    int FileSum = 0;
    int DirSum = 0;
    int Depth = 0;
    int MaxNameLength = 0;
    std::string MaxName;
};

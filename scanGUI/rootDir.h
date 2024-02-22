#pragma once
#include"DirectoryNode.h"
#include"StringOP.h"
class rootDir :public DirectoryNode {
public:
    rootDir(const std::string& name) :DirectoryNode(name) {};
    void BuildTreeBFS();
    void BuildTreeDFS();
    int CountDepth();
    const int GetFileSum() const {
        return FileSum;
    }
    const int GetDirSum() const {
        return DirSum;
    }
    const int GetDepth() const {
        return Depth;
    }
    const std::string GetMaxName() const {
        return MaxName;
    }
    const int GetMaxNameLength() const {
        return MaxNameLength;
    }
    DirectoryNode& SearchDir(const std::string DirPath);
    //用于生成该目录系统的sql文件
    void CreateSQL();
protected:
    int FileSum;
    int DirSum;
    int Depth;
    int MaxNameLength;
    std::string MaxName;
};
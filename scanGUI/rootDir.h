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
    DirectoryNode* SearchDir(const std::string DirPath);
    //用于生成该目录系统的sql文件,应输入两个路径，第一个为文件表sql文件的路径，第二个为目录表sql文件的路径
    void CreateSQL(const std::string Path);
protected:
    int FileSum = 0;
    int DirSum = 0;
    int Depth = 0;
    int MaxNameLength = 0;
    std::string MaxName;
};
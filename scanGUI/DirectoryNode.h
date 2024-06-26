﻿#pragma once
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<Windows.h>
#include<iostream>
#include<algorithm>
#include<sstream>
#include <chrono>
#include<fstream>
#include"File.h"
class DirectoryNode {
public:
    DirectoryNode(const std::string& path = "无", const std::string& name = "root",DirectoryNode* parent = nullptr) : path(path), name(name),parent(parent) {}
    ~DirectoryNode();
    // 添加子目录，输入该子目录结点的指针
    void AddChild(DirectoryNode* child) {
        children.push_back(child);
    }

    // 添加文件，输入一个文件类变量
    void AddFile(const File file) {
        files.push_back(file);
    }

    // 获取目录名称，返回记录名称的字符串
    const std::string& GetName() const {
        return name;
    }

    //获取目录路径，返回路径字符串
    const std::string& GetPath() const {
        return path;
    }

    // 获取子目录列表，返回子目录指针的向量
    const std::vector<DirectoryNode*>& GetChildren() const {
        return children;
    }

    // 获取文件列表，返回子文件的向量
    const std::vector<File>& GetFiles() const {
        return files;
    }

    //获取最早的文件,若没有文件则返回无效文件
    const File GetEarliestFile() const {
        //将初始最早文件设为第一个文件
        if (!files.empty()) {
            File earliestFile = this->files.front();
            //遍历文件列表获取最早的文件
            for (const File file : files)
                if (CompareFileTime(&file.GetLastWriteTime(), &earliestFile.GetLastWriteTime()) < 0)
                    earliestFile = file;
            return earliestFile;
        }
        else {
            return File(false);
        }
    }

    //获取最晚的文件信息
    const File GetLatestFile() const {
        if (!files.empty()) {
            //将初始最晚文件设为第一个文件
            File latestFile = this->files.front();
            //遍历文件列表获取最早的文件
            for (const File file : files)
                if (CompareFileTime(&(file.GetLastWriteTime()), &(latestFile.GetLastWriteTime())) > 0)
                    latestFile = file;
            return latestFile;
        }
        else {
            return File(false);
        }
    }

    //获取该目录下文件总数
    const int GetFileSum() const {
        return files.size();
    }

    //获取该目录下文件总大小单位为字节
    const int GetFileSumSize() const {
        int sum = 0;
        for (const File& file : files) {
            sum += file.GetSize();
        }
        return sum;
    }

    //参数为要指向删除的结点的指针，删除该文件节点及其子目录结点
    static void DeleteDir(DirectoryNode* target);

    //搜索特定名称的文件,输入文件名，返回文件类对象，以便进行文件信息的修改
    File& SearchFile(std::string FileName);


    //判断输入文件名，该文件是否为该目录节点的子文件，是则返回true，否则false
    bool FileExist(std::string FileName);

    //删除该节点下的文件，输入文件名
    bool DeletesubFile(std::string FileName);

protected:
    std::string name;
    std::string path;
    std::vector<DirectoryNode*> children;  // 子目录列表
    std::vector<File> files;       // 文件列表
    DirectoryNode* parent;  //父母结点指针
};
std::ostream& operator << (std::ostream& os, DirectoryNode& root);
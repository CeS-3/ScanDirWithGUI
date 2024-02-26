﻿#include "DirectoryNode.h"
std::ostream& operator << (std::ostream& os, DirectoryNode& root) {
    //先将根入队列
    std::queue<DirectoryNode*> NodeQue;
    NodeQue.push(&root);
    while (!NodeQue.empty()) {
        //取出队列最前端的node
        DirectoryNode* current = NodeQue.front();
        NodeQue.pop();
        //先输出该目录下文件路径
        for (const auto& file : current->GetFiles()) {
            os << file.GetName() << "\n";
        }
        //再输出子目录路径
        for (const auto& child : current->GetChildren()) {
            os << child->GetPath() << "\n";
            //将该子目录指针入队列
            NodeQue.push(child);
        }
    }
    return os;
}

DirectoryNode::~DirectoryNode() {
    // 递归释放子目录
    for (DirectoryNode* child : children) {
        delete child;
    }
    children.clear();  // 清空子目录列表
    files.clear();
}

void DirectoryNode::DeleteDir()
{
    delete this;
}

File& DirectoryNode::SearchFile(std::string FileName)
{
    auto FoundFile = std::find_if(this->files.begin(), this->files.end(), [FileName](File eachFile) {
        return eachFile.GetName() == FileName;
        });
    //若没有找到
    if (FoundFile == this->files.end())
        throw std::runtime_error("File not found: " + FileName);
    return *FoundFile;
}
//判断该目录下是否有该文件，有则返回true，否则返回false
bool DirectoryNode::FileExist(std::string FileName)
{
    auto FoundFile = std::find_if(this->files.begin(), this->files.end(), [FileName](File eachFile) {
        return eachFile.GetName() == FileName;
        });
    return !(FoundFile == this->files.end());
}


void DirectoryNode::DeletesubFile(const std::string FileName)
{
    this->files.erase(std::remove_if(this->files.begin(), this->files.end(), [FileName](File file) {
        return FileName == file.GetName();
        }), this->files.end());
}
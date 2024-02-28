#include "mydirLine.h"

//传入文件信息类型指针的向量，用于存储删除操作前的目录及其子目录的信息
void mydirLine::DeleteOperation(std::vector<DirInfo>* before)
{
    //先查找该目录
    try {
        DirectoryNode* foundDir =  this->root->SearchDir(this->TargetDirPath);
        //记录目录信息
        DirInfo parent(foundDir->GetPath(), foundDir->GetEarliestFile(), foundDir->GetLatestFile(), foundDir->GetFileSum(), foundDir->GetFileSumSize(), true);
        before->push_back(parent);
        //先将根入队列
        std::queue<DirectoryNode*> NodeQue;
        NodeQue.push(foundDir);
        while (!NodeQue.empty()) {
            //取出队列最前端的node
            DirectoryNode* current = NodeQue.front();
            NodeQue.pop();
            //再输出子目录路径
            for (const auto& child : current->GetChildren()) {
                //记录下信息
                DirInfo childInfo(child->GetPath(), child->GetEarliestFile(), child->GetLatestFile(), child->GetFileSum(), child->GetFileSumSize(), true);
                before->push_back(childInfo);
                //将该子目录指针入队列
                NodeQue.push(child);
            }
        }
        //删除该目录
        DirectoryNode::DeleteDir(foundDir);
    }
    catch (const std::runtime_error& e) {
        DirInfo badInfo;
        badInfo.valid = false;
        before->push_back(badInfo);
        return;
    }
}
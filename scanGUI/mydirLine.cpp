﻿#include "mydirLine.h"
//删除目录操作
void mydirLine::DeleteOperation(DirInfo* before)
{
    try {
        DirectoryNode* foundDir =  this->root->SearchDir(this->TargetDirPath);
        //记录目录信息
        before->DirPath = foundDir->GetPath();
        before->earliestFile = foundDir->GetEarliestFile();
        before->FileSum = foundDir->GetFileSum();
        before->FileSumSize = foundDir->GetFileSumSize();
        before->latestFile = foundDir->GetLatestFile();
        before->valid = true;
        //删除该目录
        DirectoryNode::DeleteDir(foundDir);
    }
    catch (const std::runtime_error& e) {
        before->valid = false;
        return;
    }
}
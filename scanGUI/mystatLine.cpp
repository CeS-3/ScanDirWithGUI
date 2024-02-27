#include "mystatLine.h"
//mystat中的信息用于指定执行文件信息统计操作
const DirInfo mystatLine::statisticalOperation()
{
    DirectoryNode* targetDir;
    try {
        targetDir = this->root->SearchDir(TargetDirPath);
        DirInfo information(targetDir->GetPath(), targetDir->GetEarliestFile(), targetDir->GetLatestFile(), targetDir->GetFileSum(), targetDir->GetFileSumSize(), true);
        return information;
    }
    //若没有找到该目录则存入无效信息
    catch (const std::runtime_error& e) {
        DirInfo badInformation(this->TargetDirPath, false);
        return badInformation;
    }
    
}
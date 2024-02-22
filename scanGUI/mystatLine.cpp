#include "mystatLine.h"
//mystat中的信息用于指定执行文件信息统计操作
const DirInfo mystatLine::statisticalOperation()
{
    DirectoryNode targetDir;
    try {
        targetDir = this->root.SearchDir(this->TargetDirPath);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Directory not found: " + targetDir.GetPath());
    }
    DirInfo information(targetDir.GetEarliestFile(), targetDir.GetLatestFile(), targetDir.GetFileSum(), targetDir.GetFileSumSize());
    return information;
}
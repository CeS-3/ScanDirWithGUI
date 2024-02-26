#include "mydirLine.h"
//删除目录操作
void mydirLine::DeleteOperation()
{
    try {
        this->root->SearchDir(this->TargetDirPath)->DeleteDir();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}
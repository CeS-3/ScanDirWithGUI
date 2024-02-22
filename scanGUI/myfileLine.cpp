#include "myfileLine.h"
//根据操作码执行对应的操作
void myfileLine::excuteOperation()
{
    if (operationCode == "M")
        this->ModifyOperation();
    else if (operationCode == "D")
        this->DeleteOperation();
    else if (operationCode == "A")
        this->AddOperation();
    else
        std::cerr << "Unknown operation code: " + operationCode;
}

//添加文件操作
void myfileLine::AddOperation()
{
    try {
        DirectoryNode targetDir = this->root.SearchDir(TargetDirPath);
        std::string filepath = TargetDirPath + filename;
        //检查该文件是否存在
        if (targetDir.FileExist(filename)) {
            //若存在直接返回
            return;
        }
        //创建新文件
        File newFile(filename);
        //设置时间
        newFile.changeTime(newTime);
        //设置大小
        newFile.changeSize(newSize);
        //添加该文件
        targetDir.AddFile(newFile);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
//修改文件操作
void myfileLine::ModifyOperation()
{
    try {
        //先搜索该目录
        DirectoryNode targetDir = this->root.SearchDir(TargetDirPath);
        //再在该目录下搜索文件
        try {
            File targetFile = targetDir.SearchFile(filename);
            //找到则进行修改
            targetFile.changeSize(newSize);
            targetFile.changeTime(newTime);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}

void myfileLine::DeleteOperation()
{
    try {
        //搜索该目录
        DirectoryNode targetDir = this->root.SearchDir(TargetDirPath);
        //再在该目录下删除该文件
        targetDir.DeletesubFile(filename);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}


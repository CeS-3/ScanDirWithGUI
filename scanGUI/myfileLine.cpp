#include "myfileLine.h"
//根据操作码执行对应的操作
void myfileLine::excuteOperation(File* before,File* after)
{
    try {
        //搜索目录
        DirectoryNode* targetDir = this->root->SearchDir(TargetDirPath);
        //搜索文件
        try {
            //若找到文件
            File targetFile = targetDir->SearchFile(filename);
            //记录文件
            *before = targetFile;
            //操作码为M
            if (operationCode == "M") {
                //找到则进行修改
                targetFile.changeSize(newSize);
                targetFile.changeTime(newTime);
                //记录修改后的文件
                *after = targetFile;
            }
            //操作码为D
            else if (operationCode == "D") {
                //删除该文件
                bool flag = targetDir->DeletesubFile(filename);
                //如果删除成功
                if (flag)
                {
                    //使该文件失效
                    after->setValid(false);
                }
                else {
                    *after = targetFile;
                }
            }
            else if (operationCode == "A") {
                //文件已存在，不用添加
                *after = targetFile;
            }
            else {
                throw std::runtime_error("未知的操作码： " + operationCode);
            }
        }
        catch (const std::runtime_error& e) {
            //若未找到文件
            if (operationCode == "A") {
                //原先的文件无效
                before->setValid(false);
                std::string filepath = TargetDirPath + filename;
                
                //创建新文件
                File newFile(filename);
                //设置时间
                newFile.changeTime(newTime);
                //设置大小
                newFile.changeSize(newSize);
                //添加该文件
                targetDir->AddFile(newFile);
                //记录修改后的文件
                *after = newFile;
            }
            else if (operationCode == "M" || operationCode == "D") {
                throw std::runtime_error("该文件不存在！");
            }
            else {
                throw std::runtime_error("未知的操作码： " + operationCode);
            }
        }
    }
    catch (const std::runtime_error& e) {
        throw std::runtime_error("该目录不存在！");
    }
        
}

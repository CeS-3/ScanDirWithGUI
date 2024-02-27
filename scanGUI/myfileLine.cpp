#include "myfileLine.h"
/*根据操作码执行对应的操作，传入两个文件指针用于记录执行前后的文件信息
若before、after均非法则表示修改操作失败，若before与after均合法则修改成功
若before为非法，after合法，则为新增成功，若before合法，after非法则为删除成功*/
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
                targetDir->DeletesubFile(filename);
                //由于文件必定存在，直接设置after无效
                after->setValid(false);
            }
            //操作码为A或操作码不匹配
            else {
                //文件已存在，不用添加，设置两者非法表示修改失败
                before->setValid(false);
                after->setValid(false);
            }
        }
        catch (const std::runtime_error& e) {
            //若未找到文件
            if (operationCode == "A") {
                //原先的文件无效
                before->setValid(false);
                //创建新文件
                File newFile(filename);
                //设置时间
                newFile.changeTime(newTime);
                //设置大小
                newFile.changeSize(newSize);
                //添加该文件
                targetDir->AddFile(newFile);
                //记录新增的文件
                *after = newFile;
                //新增成功
            }
            else {
                //设置两者非法表示操作失败
                before->setValid(false);
                after->setValid(false);
            }
        }
    }
    catch (const std::runtime_error& e) {
        before->setValid(false);
        after->setValid(false);
    }
        
}

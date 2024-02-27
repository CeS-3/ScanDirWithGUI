#include"DirInfo.h"
std::string DirInfo::outPut() const {
    std::string output;
    if (this->valid) {
        output += ("目录路径：" + this->DirPath + "\n");
        output += ("文件数量: " + std::to_string(this->FileSum) + " 文件总大小: " + std::to_string(this->FileSumSize) + "\n");
        if (this->earliestFile.isValid()) {  //判断文件是否有效, 如果没有最早文件则必定没有最晚文件
            output += ("最早文件: 文件名：" + this->earliestFile.GetName() + ",文件大小: " + std::to_string(this->earliestFile.GetSize()) + " bytes,时间: " + this->earliestFile.GetStandLastWriteTime() + "\n");
            output += (" 最晚文件: 文件名" + this->latestFile.GetName() + ",文件大小: " + std::to_string(this->latestFile.GetSize()) + " bytes,时间: " + this->latestFile.GetStandLastWriteTime() + "\n");
        }
        else {
            output += "最早文件: 无\n";
            output += "最晚文件: 无\n";
        }
    }
    return output;
}

void DirInfo::differ(const std::vector<DirInfo>& first, const std::vector<DirInfo>& second, std::string& output)
{
    for (int i = 0; i < first.size(); i++) {
        //若两者均合法
        if (first[i].valid && second[i].valid) {
            //若不相等
            if (first[i] != second[i]) {
                output += "发生修改: \n";
                output += "修改前: \n" + first[i].outPut() + "\n";
                output += "修改后: \n" + second[i].outPut() + "\n";
            }
        }
        //如果第一次数据非法且第二次合法
        else if (!first[i].valid && second[i].valid) {
            output += "新增目录:\n";
            output += second[i].outPut();
        }
        //如果第一次数据合法且第二次非法法
        else if (first[i].valid && !second[i].valid) {
            output += "删除目录:\n";
            output += first[i].outPut();
        }
        //若两次都不合法，则认为没有发生变化
    }
}

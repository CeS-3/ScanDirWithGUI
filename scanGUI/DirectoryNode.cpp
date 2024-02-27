#include "DirectoryNode.h"
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
        //如果已经被置空则说明应被删除
        if (child != nullptr)
            delete child;
    }
    children.clear();  // 清空子目录列表
    files.clear();
}

void DirectoryNode::DeleteDir(DirectoryNode* target)
{
    //先将该节点上层结点的指向该节点的指针置为空，表示该节点被删除
    //target->parent->children为该结点上层结点的子节点指针向量
    if (target && target->parent) {
        // 在父节点的子节点列表中查找目标节点
        auto it = std::find(target->parent->children.begin(), target->parent->children.end(), target);

        if (it != target->parent->children.end()) {
            // 找到目标节点，从子节点列表中移除
            target->parent->children.erase(it);
        }
        // 目标节点不在父节点的子节点列表中,也认为删除成功
    }
    //删除该节点并置空
    delete target;
    target = nullptr;
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

//根据输入的文件名删除该目录下的文件，若删除成功则返回true
bool DirectoryNode::DeletesubFile(const std::string FileName)
{
    int before;
    if (!this->files.empty()) {
        before = files.size();
        this->files.erase(std::remove_if(this->files.begin(), this->files.end(), [FileName](File file) {
            return FileName == file.GetName();
            }), this->files.end());
        //如果删除后文件数不变则表示删除失败
        return !(this->files.size() == before);
    }
    else {
        return false;
    }
}
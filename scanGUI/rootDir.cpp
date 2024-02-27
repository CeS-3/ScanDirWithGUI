#include "rootDir.h"
void rootDir::BuildTreeBFS() {
    //先判断根目录的路径是否存在
    std::string searchPath = this->GetPath() + "\\*";  //构造路径
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);  //获取文件句柄
    if (hFind == INVALID_HANDLE_VALUE) {
        //未找到该目录
        std::cerr << "未找到该目录" << std::endl;
        FindClose(hFind);
        return;
    }
    //若找到根目录则进行遍历
    //构造队列，存储将要遍历的目录绝对路径，进行广度优先遍历
    //由于需要同时保存路径名称与构造的目录对象指针，所以使用pair
    std::queue<std::pair<std::string, DirectoryNode*>> directoriesQueue;;
    //先将根目录存入队列
    directoriesQueue.push({ this->path,this });
    while (!directoriesQueue.empty()) {
        //取出队列最前的目录路径
        auto currentDir = directoriesQueue.front();
        //将其弹出队列
        directoriesQueue.pop();
        searchPath = currentDir.first + "\\*";
        hFind = FindFirstFileA(searchPath.c_str(), &findFileData);
        //检查该目录是否存在
        if (hFind == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_ACCESS_DENIED) {
                // 访问被拒绝，可以忽略这个目录
                std::cerr << "访问权限不足:" << currentDir.first + "\\" + findFileData.cFileName << std::endl;
                continue;
            }
            else {
                std::cerr << "未找到目录： " << currentDir.first << std::endl;
                continue;
            }
        }

        do {
            //判断是否为目录
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                //若为目录，检查是否为.或..等无效目录
                if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                    //如果是有效目录则创建目录对象
                    DirectoryNode* NewDirP = new(std::nothrow) DirectoryNode(currentDir.first + "\\" + findFileData.cFileName, findFileData.cFileName,currentDir.second);
                    if (NewDirP == nullptr) {
                        std::cerr << "堆分配失败" << std::endl;
                        return;
                    }
                    //将该子目录对象的指针加入到当前目录的子目录指针列表中
                    currentDir.second->AddChild(NewDirP);
                    //将该 {子目录的路径:目录对象指针}对 存入队列中
                    directoriesQueue.push({ NewDirP->GetPath(),NewDirP });
                    //子目录数加1
                    DirSum++;
                    //测试语句
                    //std::cout << currentDir.first + "\\" + findFileData.cFileName << "添加完成" << std::endl;
                }
            }
            //若为文件
            else {
                //且文件的大小不为0
                if (findFileData.nFileSizeLow != 0 || findFileData.nFileSizeHigh != 0) {
                    //则将文件信息存入当前目录对象的子文件列表中
                    std::string NewFilePath = currentDir.first + "\\" + findFileData.cFileName;
                    File NewFile(findFileData.cFileName, findFileData.ftCreationTime, findFileData.nFileSizeHigh, findFileData.nFileSizeLow);
                    currentDir.second->AddFile(NewFile);
                    //文件数加1
                    FileSum++;
                    //判断文件名长度与最大文件名长度的大小
                    if (NewFilePath.length() > MaxName.length()) {
                        MaxName = NewFilePath;
                    }
                }
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);
        //初始化最大文件路径长度
        MaxNameLength = MaxName.length();
        FindClose(hFind);
    }
    //构造完成后，初始化目录层数
    Depth = CountDepth();
}
void rootDir::BuildTreeDFS() {
    // 使用栈来模拟深度优先遍历

    std::stack<std::pair<std::string, DirectoryNode*>> stack;
    stack.push({ this->path, this });
    while (!stack.empty()) {
        auto currentDir = stack.top();
        stack.pop();

        std::string searchPath = currentDir.first + "\\*";
        WIN32_FIND_DATAA findFileData;
        HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_ACCESS_DENIED) {
                std::cerr << "访问权限不足:" << currentDir.first + "\\" + findFileData.cFileName << std::endl;
            }
            else {
                std::cerr << "未找到目录： " << currentDir.first << std::endl;
            }
            FindClose(hFind);
            continue;
        }

        do {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                std::string newPath = currentDir.first + "\\" + findFileData.cFileName;

                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    auto start_time = std::chrono::high_resolution_clock::now(); //记录开始时间
                    DirectoryNode* newDir = new(std::nothrow) DirectoryNode(newPath, findFileData.cFileName, currentDir.second);
                    if (newDir == nullptr) {
                        std::cerr << "堆分配失败" << std::endl;
                        return;
                    }
                    currentDir.second->AddChild(newDir);
                    DirSum++;
                    stack.push({ newPath, newDir });
                }
                else if (findFileData.nFileSizeLow != 0 || findFileData.nFileSizeHigh != 0) {
                    auto start_time = std::chrono::high_resolution_clock::now(); //记录开始时间
                    std::string newFilePath = currentDir.first + "\\" + findFileData.cFileName;
                    File newFile(findFileData.cFileName, findFileData.ftCreationTime, findFileData.nFileSizeHigh, findFileData.nFileSizeLow);
                    currentDir.second->AddFile(newFile);
                    FileSum++;
                    if (newFilePath.length() > MaxName.length()) {
                        MaxName = newFilePath;
                    }
                }
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);

        MaxNameLength = MaxName.length();
        FindClose(hFind);
    }
    //最终计算一次树的深度
    Depth = CountDepth();
}
int rootDir::CountDepth() {
    if (this == nullptr)
        return 0;
    int depth = 0;
    //是用队列进行遍历
    std::queue<const DirectoryNode*> NodeQue;
    NodeQue.push(this);

    while (!NodeQue.empty()) {
        //先记录该层的大小
        int levelSize = NodeQue.size();
        //遍历该层的所有目录
        for (int i = 0; i < levelSize; i++) {
            const DirectoryNode* current = NodeQue.front();
            NodeQue.pop();
            //每遍历一个目录就将该目录下的所有子目录压入队列
            for (const auto& child : current->GetChildren()) {
                NodeQue.push(child);
            }
        }
        //一个循环完成后，队列的大小等于下一层的目录总数
        //深度加一
        depth++;
    }
    return depth;
}

//根据所给路径找出对应目录对象
DirectoryNode* rootDir::SearchDir(const std::string DirPath) {
    //首先分割路径取出各级目录
    std::vector<std::string> subDir(splitString(DirPath, '\\'));
    //计算出根目录路径的大小，将这部分路径剔除
    std::vector<std::string> rootDir(splitString(this->GetPath(), '\\'));
    int rootLength = rootDir.size();
    if (rootLength < subDir.size()) {
        subDir.erase(subDir.begin(), subDir.begin() + rootLength);
    }
    else {
        // 处理 rootLength 大于或等于 subDir.size() 的情况
        throw std::runtime_error("该文件不在默认目录下！");
    }
    //从根目录开始寻找各目录进行索引
    DirectoryNode* currentDir = this;
        //查找目标
    for (std::string targetDir : subDir) {
        std::vector<DirectoryNode*> currentSub = currentDir->GetChildren();
        bool flag = false;
        DirectoryNode* foundDir;
        for (DirectoryNode* eachDir : currentSub)
        {
            if (eachDir->GetName() == targetDir) {
                flag = true;
                foundDir = eachDir;
                break;
            }
        }
        //检测是否找到
        if(flag == false)
        //没找到就抛出异常
            throw std::runtime_error("Directory not found: " + DirPath);
        //如果找到则移动到下一级
        currentDir = foundDir;
    }
    //返回找到的目录
    return currentDir;
}

void rootDir::CreateSQL(const std::string Path)
{
    //开启文件用于写入生成的语句
    std::ofstream File(Path + "\\file.sql");
    if (!File.is_open()) {
        throw std::runtime_error("file文件开启失败");
        return;
    }
    std::ofstream Dir(Path + "\\dir.sql");
    if (!File.is_open()) {
        throw std::runtime_error("dir文件开启失败");
        return;
    }
    //生成根目录信息
    Dir << "insert into directory values(0,NULL,'Windows');\n";
    //第一位为id，第二位为上级目录的id，第三位为目录地址
    int DirID = 1;
    int currentDirID;
    int FileID = 1;
    //建立队列辅助遍历
    //先将根入队列
    std::queue<DirectoryNode*> NodeQue;
    NodeQue.push(this);
    while (!NodeQue.empty()) {
        //取出队列最前端的node
        DirectoryNode* current = NodeQue.front();
        NodeQue.pop();
        currentDirID = DirID;
        //构造子目录信息
        for (const auto& child : current->GetChildren()) {
            //将该子目录指针入队列
            NodeQue.push(child);
            //生成插入信息
            Dir << "insert into directory values(" << DirID++ << "," << currentDirID << ",'" << child->GetName() << "');\n";
        }
        //在构造子文件信息
        for (const auto& file : current->GetFiles()) {
            File << "insert into file values(" << FileID++ << ", " << currentDirID << ",'" << file.GetName() << "','" << file.GetStandLastWriteTime() << "'," << file.GetSize() << ");\n";
        }
    }
}
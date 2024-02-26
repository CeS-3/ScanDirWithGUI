#pragma once
#include<string>
#include<Windows.h>
#include"TimeConvert.h"
class File {
public:
    File(const std::string name, const FILETIME ftCreationTime, DWORD nFileSizeHigh, DWORD nFileSizeLow)
        :name(name), ftLastWriteTime(ftCreationTime), nFileSizeHigh(nFileSizeHigh), nFileSizeLow(nFileSizeLow) {}
    File(const std::string name) :name(name) {}
    File(bool valid): valid(valid) {}

    //获取文件名
    const std::string& GetName() const {
        return name;
    }
    //获取原始文件最后修改时间
    const FILETIME& GetLastWriteTime() const {
        return ftLastWriteTime;
    }
    //获取标准文件创建时间
    const std::string GetStandLastWriteTime() const;
    //获取文件大小，单位为bytes
    const unsigned long GetSize() const {
        unsigned long fileSize = static_cast<unsigned long>(nFileSizeHigh) << 32 | nFileSizeLow;
        return fileSize;
    }
    //改变文件大小,输入的是字节数
    void changeSize(long int fileSize) {
        this->nFileSizeHigh = static_cast<DWORD>((fileSize >> 32) & 0xFFFFFFFF);
        this->nFileSizeLow = static_cast<DWORD>(fileSize & 0xFFFFFFFF);
    }
    //改变文件创建时间,输入的是从1970年1月1日开始的秒数
    void changeTime(long int NewTime);
    bool isValid() {
        return valid;
    }
    void setValid(bool flag) {
        this->valid = flag;
    }
    // 复制赋值运算符
    File& operator=(const File& other) {
        if (this != &other) {
            this->name = other.name;
            this->ftLastWriteTime = other.ftLastWriteTime;
            this->nFileSizeHigh = other.nFileSizeHigh;
            this->nFileSizeLow = other.nFileSizeLow;
            this->valid = other.valid;
        }
        return *this;
    }
private:
    std::string name;   //文件名
    FILETIME ftLastWriteTime;        // 创建时间
    DWORD    nFileSizeHigh;         // 文件大小的高 32 位
    DWORD    nFileSizeLow;          // 文件大小的低 32 位
    bool valid = true;
};

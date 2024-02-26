#pragma once
#include<fstream>
#include"mydirLine.h"
#include"myfileLine.h"
#include"mystatLine.h"

class DataFile
{
public:
	//用文件路径初始化
	DataFile(std::string datafilePath,rootDir& root): root(root) {
		//开启文件
		datafile.open(datafilePath);
		if (!datafile.is_open()) {
			//进行错误处理
			throw std::runtime_error("未找到该文件！");
			return;
		}
		
	}
	~DataFile() {
		if (datafile.is_open()) {
			datafile.close();
		}
	}
	virtual void parseFile() = 0;
protected:
	std::ifstream datafile;
	rootDir root;
};


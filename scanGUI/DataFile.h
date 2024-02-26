#pragma once
#include<fstream>
#include"mydirLine.h"
#include"myfileLine.h"
#include"mystatLine.h"

class DataFile
{
public:
	//���ļ�·����ʼ��
	DataFile(std::string datafilePath,rootDir& root): root(root) {
		//�����ļ�
		datafile.open(datafilePath);
		if (!datafile.is_open()) {
			//���д�����
			throw std::runtime_error("δ�ҵ����ļ���");
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


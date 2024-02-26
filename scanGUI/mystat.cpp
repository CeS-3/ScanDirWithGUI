#include "mystat.h"

void mystat::parseFile()
{
	std::string eachline;
	//��ȡ�����ļ��еĵ�һ��
	std::getline(datafile, eachline);
	if (eachline != "stat dirs")
	{
		//���д�����
		throw std::runtime_error("�ļ���ʽ��ƥ��");
		return;
	}
	while (eachline != "end of dirs") {
		std::getline(datafile, eachline);
		mystatLine each(eachline, &root);
		try {
			information.push_back(each.statisticalOperation());
		}
		catch (const std::exception& e) {
			//���ͳ��ʧ��
			throw std::runtime_error(e.what());
		}
	}
}

#include "mystat.h"

void mystat::parseFile()
{
	std::string eachline;
	//读取数据文件中的第一行
	std::getline(datafile, eachline);
	if (eachline != "stat dirs")
	{
		//进行错误处理
		throw std::runtime_error("文件格式不匹配");
		return;
	}
	while (eachline != "end of dirs") {
		std::getline(datafile, eachline);
		mystatLine each(eachline, &root);
		try {
			information.push_back(each.statisticalOperation());
		}
		catch (const std::exception& e) {
			//如果统计失败
			throw std::runtime_error(e.what());
		}
	}
}

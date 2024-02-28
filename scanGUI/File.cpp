#include "File.h"

//获取标准文件创建时间，以标准时间的形式
const std::string File::GetStandLastWriteTime() const {
    SYSTEMTIME stUTC, stLocal;
    //转化为系统时
    FileTimeToSystemTime(&ftLastWriteTime, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
    char buffer[50];
    sprintf_s(buffer, "%04d-%02d-%02d %02d:%02d:%02d", stLocal.wYear, stLocal.wMonth, stLocal.wDay, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
    std::string StandTime(buffer);
    return StandTime;
}

//改变文件创建时间,输入的是从1970年1月1日开始的秒数
void File::changeTime(long int NewTime)
{
    FILETIME NewFILETIME = SystemTimeToFileTime(UnixTimeToSystemTime(NewTime));
    this->ftLastWriteTime = NewFILETIME;
}
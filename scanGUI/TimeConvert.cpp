#include "TimeConvert.h"

//传入一个长整型数，作为unixtime，转化为系统时返回
SYSTEMTIME UnixTimeToSystemTime(long int unixTime)
{
    // 将 UNIX 时间戳转换为 time_t
    time_t rawTime = static_cast<time_t>(unixTime);

    // 使用 gmtime 将 time_t 转换为 struct tm
    struct tm* timeInfo = gmtime(&rawTime);

    // 将 struct tm 转换为 SYSTEMTIME
    SYSTEMTIME systemTime;
    systemTime.wYear = static_cast<WORD>(timeInfo->tm_year + 1900);
    systemTime.wMonth = static_cast<WORD>(timeInfo->tm_mon + 1);
    systemTime.wDay = static_cast<WORD>(timeInfo->tm_mday);
    systemTime.wHour = static_cast<WORD>(timeInfo->tm_hour);
    systemTime.wMinute = static_cast<WORD>(timeInfo->tm_min);
    systemTime.wSecond = static_cast<WORD>(timeInfo->tm_sec);
    systemTime.wMilliseconds = 0;

    return systemTime;
}

//传入一个系统时，转化为文件时间返回
FILETIME SystemTimeToFileTime(const SYSTEMTIME& systemTime) {
    FILETIME fileTime;
    SystemTimeToFileTime(&systemTime, &fileTime);
    return fileTime;
}

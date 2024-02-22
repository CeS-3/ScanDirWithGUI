#include "File.h"

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
void File::changeTime(long int NewTime)
{
    FILETIME NewFILETIME = SystemTimeToFileTime(UnixTimeToSystemTime(NewTime));
    this->ftLastWriteTime = NewFILETIME;
}
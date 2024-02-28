#pragma once
#include<ctime>
#include<Windows.h>

//传入一个长整型数，作为unixtime，转化为系统时返回
SYSTEMTIME UnixTimeToSystemTime(long int unixTime);

//传入一个系统时，转化为文件时间返回
FILETIME SystemTimeToFileTime(const SYSTEMTIME& systemTime);
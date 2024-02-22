#pragma once
#include<ctime>
#include<Windows.h>
SYSTEMTIME UnixTimeToSystemTime(long int unixTime);
FILETIME SystemTimeToFileTime(const SYSTEMTIME& systemTime);
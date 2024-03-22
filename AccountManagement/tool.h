#pragma once
#ifndef TOOL_H
#define TOOL_H
#include<time.h>
void timeToString(time_t t, char* pBuf); // 声明timeToString()函数
time_t stringToTime(char* pTime);		 // 声明stringToTime()函数

#endif 


#pragma once
#ifndef MENU_H
#define MENU_H
#include<stdio.h>		//包含输入输出头文件
#include<time.h>		//包含时间头文件
#include<string.h>		//导入字符串处理函数
#include<stdlib.h>		//包含动态内存分配头文件

#include"model.h"
#include"global.h"
#include"tool.h"
#include"card_service.h"
#include"card_file.h"
#include"billing_file.h"
#include"billing_service.h"
#include"service.h"

#define CARDPATH   "card.txt"     // 卡信息保存路径
#define BILLINGPATH "billing.txt"
#define INFORPATH "information.txt"

void outputMenu();		//声明输出菜单函数
void add();				//声明添加卡函数
void query();			//声明查询卡函数
void exitApp();			//声明退出应用程序函数
void logon();			//声明上机函数
void settle();			//声明下机函数
void annul();			//声明注销卡函数
void addMoney();		//声明充值函数
void refundMoney();		//声明退费函数
void count();			//声明查询统计函数

#endif
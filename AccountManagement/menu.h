#pragma once
#ifndef MENU_H
#define MENU_H
#include<stdio.h>		//�����������ͷ�ļ�
#include<time.h>		//����ʱ��ͷ�ļ�
#include<string.h>		//�����ַ���������
#include<stdlib.h>		//������̬�ڴ����ͷ�ļ�

#include"model.h"
#include"global.h"
#include"tool.h"
#include"card_service.h"
#include"card_file.h"
#include"billing_file.h"
#include"billing_service.h"
#include"service.h"

#define CARDPATH   "card.txt"     // ����Ϣ����·��
#define BILLINGPATH "billing.txt"
#define INFORPATH "information.txt"

void outputMenu();		//��������˵�����
void add();				//������ӿ�����
void query();			//������ѯ������
void exitApp();			//�����˳�Ӧ�ó�����
void logon();			//�����ϻ�����
void settle();			//�����»�����
void annul();			//����ע��������
void addMoney();		//������ֵ����
void refundMoney();		//�����˷Ѻ���
void count();			//������ѯͳ�ƺ���

#endif
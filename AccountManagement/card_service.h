#pragma once
#include"menu.h"

/*int addCard(Card card);
Card* quaryCard(const char* pName);*/

Card* initCardList(const char* path);		//��ʼ������Ϣ����
void releaseCardList(Card* p);				//�ͷſ���Ϣ����
int addCard(Card* head, Card* card);		//�ڿ���Ϣ�����У���ӿ���Ϣ
void queryCard(Card* head);					//�ڿ���Ϣ�����У���ѯ������ͬ�Ŀ���Ϣ
void queryCards(Card* head);				//��������Ĺؼ��֣��ڿ���Ϣ�����У���ѯ�����а����ؼ��ֵĿ���Ϣ
Card* checkCard(char* number, char* password, Card* head, int* index); //���ݿ��ź����룬�������в�ѯ����Ϣ������ȡ��ѯ���Ŀ���Ϣ�������е�λ��
Card* checkCardnum(char* number, Card* head);	//���ݿ��ţ��������в�ѯ����Ϣ


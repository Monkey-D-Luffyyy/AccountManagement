#pragma once
#include"menu.h"

/*int addCard(Card card);
Card* quaryCard(const char* pName);*/

Card* initCardList(const char* path);		//初始化卡信息链表
void releaseCardList(Card* p);				//释放卡信息链表
int addCard(Card* head, Card* card);		//在卡信息链表中，添加卡信息
void queryCard(Card* head);					//在卡信息链表中，查询卡号相同的卡信息
void queryCards(Card* head);				//根据输入的关键字，在卡信息链表中，查询卡号中包含关键字的卡信息
Card* checkCard(char* number, char* password, Card* head, int* index); //根据卡号和密码，在链表中查询卡信息，并获取查询到的卡信息在链表中的位置
Card* checkCardnum(char* number, Card* head);	//根据卡号，在链表中查询卡信息


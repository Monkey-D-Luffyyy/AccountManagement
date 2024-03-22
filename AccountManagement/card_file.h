#pragma once
#include"menu.h"


int saveCard(const Card* pCard, const char* pPath);
int updateCard(const Card* pCard, const char* pPath, int nIndex);
int getCardCount(const char* pPath);
int isExsit(const char* pNum, const char* pPath);
int readCard(Card* pCard, const char* pPath);

int inputCard(Card* card);
void showCard(Card card);
void showAllcards(const char* path);
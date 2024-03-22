#pragma once
#ifndef SERVICE_H    // ∑¿÷π÷ÿ∏¥±‡“Î
#define SERVICE_H
#include"model.h"

//int addCardInfo(Card card);    
//Card* queryCardInfo(const char* pName, int* pIndex);

void add(Card* Chead);
void query(Card* Chead);
void logon(Card* Chead, Billing* Bhead);
void settle(Card* Chead, Billing* Bhead);
void addMoney(Card* Chead);
void refundMoney(Card* Chead);
void count(Card* Chead);
void annul(Card* Chead);
void exitApp(void);

#endif


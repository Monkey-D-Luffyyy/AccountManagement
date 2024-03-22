#pragma once
#ifndef BILLING_SERVICE_H
#define BILLING_SERVICE_H
#include"model.h"

Billing* initBillingList(const char* path);
void releaseBillingList(Billing* p);
int getBilling(Billing* head, const char* path, const char* num);
Billing* checkBilling(char* number, Billing* hp, int* index);

#endif /* BILLING_SERVICE_H */
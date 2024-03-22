#ifndef BILLING_FILE_H
#define BILLING_FILE_H
#include"model.h"

int saveBilling(Billing* p, const char* path);
void showBilling(char* number, const char* path);
int getBillingnum(const char* path);
int updateBilling(Billing* p, const char* path, int index);
void showInformation(const char* path, char* name);

#endif /* BILLING_FILE_H */
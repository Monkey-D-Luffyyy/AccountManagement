#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"


Billing* initBillingList(const char* path) {

    Billing* head;
    head = (Billing*)malloc(sizeof(Billing));
    head->next = NULL;

    Billing* p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    FILE* fp = NULL;
    if ((fp = fopen(path, "rb")) == NULL) {

        return head;
    }

    while (!feof(fp)) {
        Billing* pBilling = (Billing*)malloc(sizeof(struct Billing));
        if (fread(pBilling, sizeof(Billing), 1, fp) != 0) {
            p->next = pBilling;
            p = p->next;
            p->next = NULL;
        }
    }
    fclose(fp);

    return head;

}


void releaseBillingList(Billing* p) {        //�ͷżƷ���Ϣ����

    Billing* q;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}


int getBilling(Billing* head, const char* path,const char* num) {     //�ӼƷ���Ϣ�ļ���ȡ�Ʒ���Ϣ���浽�Ʒ�������

    FILE* fp = NULL;
    if ((fp = fopen(path, "rb")) == NULL) {
        return FALSE;
    }

    Billing* p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    Billing* pnew = (Billing*)malloc(sizeof(struct Billing));
    if (!pnew)
    {
        exit(-2);
    }

    while (!feof(fp)) 
    {
        if (fread(pnew, sizeof(struct Billing), 1, fp) != 0)
        {
            if (strcmp(pnew->aCardName, num) == 0)
            {
                p->next = pnew;
                p = p->next;
                p->next = NULL;

                fclose(fp);
                return TRUE;
            }
        }
    }

    fclose(fp);
    return FALSE;
}


Billing* checkBilling(char* number, Billing* hp, int* index) {     //�ڼƷ���Ϣ�����У���ѯ��Ӧ���ļƷ���Ϣ������ȡ�üƷ���Ϣ�������е�������

    Billing* p = hp->next;
    while (p != NULL) 
    {
        (*index)++;
        if (strcmp(p->aCardName, number) == 0) 
        {
            return p;
        }
        p = p->next;
    }

    return NULL;
}
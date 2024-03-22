#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"


int saveBilling(Billing* p, const char* path) {    //���Ʒ���Ϣ���浽�ļ���

    FILE* fp = NULL;

    if ((fp = fopen(path, "ab")) == NULL) {   //��׷�ӵ�ģʽ���ļ��������ʧ�ܣ�����ֻд��ģʽ���ļ�

        if ((fp = fopen(path, "wb")) == NULL) 
        {
            return FALSE;
        }
    }

    fwrite(p, sizeof(Billing), 1, fp);

    fclose(fp);
    return TRUE;
}


void showBilling(char* number, const char* path) {     //���ļ��ж�ȡ�Ʒ���Ϣ

    char startTime[50];

    FILE* p = NULL;  // �ļ�ָ��
    Billing* pb = (Billing*)malloc(sizeof(Billing));
    if ((p = fopen(path, "rb")) == NULL) 
    {
        printf("���ļ�ʧ��!\n");
        return;

    }
    while (!feof(p)) 
    {
        if (fread(pb, sizeof(Card), 1, p) != 0)
        {
            if (strcmp(pb->aCardName, number) == 0)
            {
                printf("����\t״̬\t����״̬\tɾ����ʶ\t�ϻ�ʱ��\n");
                timeToString(pb->tStart, startTime);
                printf("%s\t%d\t%d\t\t%d\t\t%s\n", pb->aCardName, pb->nStatus, pb->nStatus, pb->nDel, startTime);
            }
        }
    }

    fclose(p);
    free(pb);
}

int getBillingnum(const char* path) {     //���ļ��л�ȡ�Ʒ���Ϣ������

    FILE* p = NULL;  // �ļ�ָ��
    int index = 0;
    Card* pCard = (Card*)malloc(sizeof(Card));
    if ((p = fopen(path, "rb")) == NULL) 
    {
        return 0;
    }

    while (!feof(p)) 
    {
        if (fread(pCard, sizeof(Card), 1, p) != 0)
            index++;
    }

    fclose(p);
    free(pCard);

    return index;
}


int updateBilling(Billing* p, const char* path, int index)
{
    FILE* fp = NULL;        // �ļ�ָ��
    int line = 0;           // �ļ�����Ϣ��
    long position = 0;      // �ļ�λ�ñ��
    Card bBuf;

    if ((fp = fopen(path, "rb+")) == NULL) 
    {
        return FALSE;
    }

    while ((!feof(fp)) && (line < index - 1)) 
    {
        if (fread(&bBuf, sizeof(Card), 1, fp) != 0)
        {   // ��ȡ�ļ���ʶλ��
            position = ftell(fp);
            line++;
        }
    }

    fseek(fp, position, 0);
    fwrite(p, sizeof(Card), 1, fp);
    fclose(fp);

    return TRUE;
}

void showInformation(const char* path, char* name) 
{
    FILE* p = NULL;

    Billing* bp = (Billing*)malloc(sizeof(struct Billing));

    if ((p = fopen(path, "rb")) == NULL) 
    {
        printf("�򿪼Ʒ���Ϣ�ļ�ʧ��!\n");
    }

    char startTime[50];
    char endTime[50];

    while (!feof(p)) 
    {
        if (fread(bp, sizeof(Billing), 1, p) != 0) 
        {
            if (strcmp(bp->aCardName, name) == 0) 
            {
                printf("����״̬\t���ѽ��\t�ϻ�ʱ��\t\t�»�ʱ��\t\tɾ����ʶ\n");
                timeToString(bp->tStart, startTime);
                timeToString(bp->tEnd, endTime);
                printf("%d\t\t\%.2f\t\t%s\t%s\t%d\n", bp->nStatus, bp->fAmount, startTime, endTime, bp->nDel);
            }
        }
    }

    fclose(p);
    free(bp);
}
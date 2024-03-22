#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"


int saveBilling(Billing* p, const char* path) {    //将计费信息保存到文件中

    FILE* fp = NULL;

    if ((fp = fopen(path, "ab")) == NULL) {   //以追加的模式打开文件，如果打开失败，则以只写的模式打开文件

        if ((fp = fopen(path, "wb")) == NULL) 
        {
            return FALSE;
        }
    }

    fwrite(p, sizeof(Billing), 1, fp);

    fclose(fp);
    return TRUE;
}


void showBilling(char* number, const char* path) {     //从文件中读取计费信息

    char startTime[50];

    FILE* p = NULL;  // 文件指针
    Billing* pb = (Billing*)malloc(sizeof(Billing));
    if ((p = fopen(path, "rb")) == NULL) 
    {
        printf("打开文件失败!\n");
        return;

    }
    while (!feof(p)) 
    {
        if (fread(pb, sizeof(Card), 1, p) != 0)
        {
            if (strcmp(pb->aCardName, number) == 0)
            {
                printf("卡号\t状态\t消费状态\t删除标识\t上机时间\n");
                timeToString(pb->tStart, startTime);
                printf("%s\t%d\t%d\t\t%d\t\t%s\n", pb->aCardName, pb->nStatus, pb->nStatus, pb->nDel, startTime);
            }
        }
    }

    fclose(p);
    free(pb);
}

int getBillingnum(const char* path) {     //从文件中获取计费信息的数量

    FILE* p = NULL;  // 文件指针
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
    FILE* fp = NULL;        // 文件指针
    int line = 0;           // 文件卡信息数
    long position = 0;      // 文件位置标记
    Card bBuf;

    if ((fp = fopen(path, "rb+")) == NULL) 
    {
        return FALSE;
    }

    while ((!feof(fp)) && (line < index - 1)) 
    {
        if (fread(&bBuf, sizeof(Card), 1, fp) != 0)
        {   // 获取文件标识位置
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
        printf("打开计费信息文件失败!\n");
    }

    char startTime[50];
    char endTime[50];

    while (!feof(p)) 
    {
        if (fread(bp, sizeof(Billing), 1, p) != 0) 
        {
            if (strcmp(bp->aCardName, name) == 0) 
            {
                printf("消费状态\t消费金额\t上机时间\t\t下机时间\t\t删除标识\n");
                timeToString(bp->tStart, startTime);
                timeToString(bp->tEnd, endTime);
                printf("%d\t\t\%.2f\t\t%s\t%s\t%d\n", bp->nStatus, bp->fAmount, startTime, endTime, bp->nDel);
            }
        }
    }

    fclose(p);
    free(bp);
}
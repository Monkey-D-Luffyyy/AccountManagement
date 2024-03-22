#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"

/*
Card aCard[50]; //卡信息结构体数组
int nCount = 0;	//卡信息实际个数

int addCard(Card card)
{
	aCard[nCount++] = card;
	return TRUE;
}

Card* quaryCard(const char* pName)
{
	for (int i = 0; i < nCount; i++)
	{
		if (strcmp(pName, aCard[i].aName) == 0)
		{
			return &aCard[i];
		}
	}
	return NULL;
}
*/


Card* initCardList(const char* path) 
{
    Card* head;
    head = (Card*)malloc(sizeof(struct Card));
    head->next = NULL;

    Card* p = head;
    while (p->next != NULL) 
    {
        p = p->next;
    }

    FILE* fp = NULL;
    if ((fp = fopen(path, "rb")) == NULL) 
    {
        return head;
    }

    while (!feof(fp)) 
    {
        Card* pCard = (Card*)malloc(sizeof(struct Card));
        if (fread(pCard, sizeof(Card), 1, fp) != 0) 
        {
            p->next = pCard;
            p = p->next;
            p->next = NULL;
        }
    }

    fclose(fp);

    return head;
}

int addCard(Card* head, Card* card) //将卡信息添加到链表
{
    Card* p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = card;
    p = p->next;
    p->next = NULL;
    return TRUE;
}

void releaseCardList(Card* p) //释放卡信息链表
{        
    Card* q;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

void queryCard(Card* head) //在卡信息链表中，查询卡号相同的卡信息
{       
    printf("请输入要查询的卡号(长度为1~18)：");
    char number[18] = { 0 };   // 输入的卡号
    scanf("%s", number);

    Card* p = head->next;
    while (p != NULL) 
    {
        if (strcmp(p->aName, number) == 0) 
        {
            if (p->nStatus != 2)
            {
                printf("\n-----查询到的卡信息如下-----\n");
                showCard(*p);
            }
            else
            {
                printf("此卡已注销！\n");  
            }
            return;
        }

        p = p->next;
    }

    printf("此卡不存在!\n");
}

void queryCards(Card* head)  //根据输入的关键字，在卡信息链表中，查询卡号中包含关键字的卡信息
{       
    printf("请输入要查询的关键词(长度为1~18):");
    char number[18] = { 0 };
    scanf("%s", number);

    Card* p = head->next;
    int i = 0;
    while (p != NULL) 
    {
        if (strstr(p->aName, number) != NULL) 
        {
            if (p->nStatus != 2)
            {
                if (!i)
                    printf("\n-----查询到的卡信息如下-----\n");
                showCard(*p);
                i++;
            }
        }
        p = p->next;
    }
    if (i == 0)
        printf("未查询到相关卡信息！\n");
}

Card* checkCard(char* number, char* password, Card* head, int* index) //根据卡号和密码，在链表中查询卡信息，并获取查询到的卡信息在链表中的位置
{      
    Card* p = head->next;
    while (p != NULL) 
    {
        (*index)++;

        if ((strcmp(p->aName, number) == 0) && (strcmp(p->aPwd, password) == 0)) 
        {
            return p;
        }

        p = p->next;
    }

    return NULL;
}

Card* checkCardnum(char* number, Card* head) //根据卡号，在链表中查询卡信息
{
    Card* p = head->next;
    while (p != NULL)
    {
        if ((strcmp(p->aName, number) == 0))
        {
            return p;
        }

        p = p->next;
    }

    return NULL;
}

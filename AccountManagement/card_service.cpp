#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"

/*
Card aCard[50]; //����Ϣ�ṹ������
int nCount = 0;	//����Ϣʵ�ʸ���

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

int addCard(Card* head, Card* card) //������Ϣ��ӵ�����
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

void releaseCardList(Card* p) //�ͷſ���Ϣ����
{        
    Card* q;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

void queryCard(Card* head) //�ڿ���Ϣ�����У���ѯ������ͬ�Ŀ���Ϣ
{       
    printf("������Ҫ��ѯ�Ŀ���(����Ϊ1~18)��");
    char number[18] = { 0 };   // ����Ŀ���
    scanf("%s", number);

    Card* p = head->next;
    while (p != NULL) 
    {
        if (strcmp(p->aName, number) == 0) 
        {
            if (p->nStatus != 2)
            {
                printf("\n-----��ѯ���Ŀ���Ϣ����-----\n");
                showCard(*p);
            }
            else
            {
                printf("�˿���ע����\n");  
            }
            return;
        }

        p = p->next;
    }

    printf("�˿�������!\n");
}

void queryCards(Card* head)  //��������Ĺؼ��֣��ڿ���Ϣ�����У���ѯ�����а����ؼ��ֵĿ���Ϣ
{       
    printf("������Ҫ��ѯ�Ĺؼ���(����Ϊ1~18):");
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
                    printf("\n-----��ѯ���Ŀ���Ϣ����-----\n");
                showCard(*p);
                i++;
            }
        }
        p = p->next;
    }
    if (i == 0)
        printf("δ��ѯ����ؿ���Ϣ��\n");
}

Card* checkCard(char* number, char* password, Card* head, int* index) //���ݿ��ź����룬�������в�ѯ����Ϣ������ȡ��ѯ���Ŀ���Ϣ�������е�λ��
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

Card* checkCardnum(char* number, Card* head) //���ݿ��ţ��������в�ѯ����Ϣ
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

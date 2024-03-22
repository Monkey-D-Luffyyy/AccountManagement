#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"

void add(Card* Chead)
{
	Card* pNew = (Card*)malloc(sizeof(Card));
    if (inputCard(pNew) == FALSE)
        return;
    if (saveCard(pNew, CARDPATH) == FALSE)
    {
        printf("��ӿ���Ϣʧ�ܣ�\n");
    }
    else
    {
        printf("��ӿ���Ϣ�ɹ���\n");
        addCard(Chead, pNew);
    }
}

void query(Card* Chead)
{
    printf("��ѡ���ѯ�ķ�ʽ��\n");
    printf("1.��ȷ��ѯ\n");
    printf("2.ģ����ѯ\n");
    printf("������ѡ��(1��2)��");
    int item;
    scanf("%d", &item);

    if (item == 1) {
        queryCard(Chead);
    }
    else if (item == 2) {
        queryCards(Chead);
    }
    else {
        printf("�������!\n");
    }
}

void logon(Card* Chead, Billing* Bhead)
{
    Card* p = NULL;
    int index = 0;     //����Ϣ�������е�����

    printf("�����뿨��(����Ϊ1~18):");
    char number[18];
    scanf("%s", number);
    if (checkCardnum(number, Chead) == NULL) 
    {
        printf("�ÿ���Ϣ������!\n�ϻ�ʧ��!\n");
        return;
    }

    printf("����������(����Ϊ1~8)��");
    char password[8];    // ���������
    scanf("%s", password);

    //���ݿ��ź����룬�������л�ȡ����Ϣ�Ϳ���Ϣ�������е�����
    p = checkCard(number, password, Chead, &index);

    //�������ϢΪ�գ���ʾ���ܴ����ϻ�ʧ��
    if (p == NULL) {
        printf("���������!\n�ϻ�ʧ��!\n");
        return;
    }
    //�����״̬��Ϊ0����ʾ�ÿ������ϻ�
    if (p->nStatus != 0) {
        printf("�ÿ������ϻ�����ʧЧ!\n�ϻ�ʧ��!\n");
        return;
    }
    //��������Ϊ0�������ϻ�
    if (p->fBalance == 0) {
        printf("���Ϊ0!\n�ϻ�ʧ��!\n");
        return;
    }

    //��������ϻ������¿���Ϣ
    p->nStatus = 1;      //״̬Ϊ����ʹ��
    p->nUseCount++;     //ʹ�ô�����1
    p->tLast = time(NULL);      //�������ʹ��ʱ��Ϊ��ǰʱ��

    //�����ļ��еĿ���Ϣ
    if (updateCard(p, CARDPATH, index) == FALSE) 
    {
        printf("���¿���Ϣʧ��!\n");
        return;
    }

    int index2 = 0;
    Billing* bp = NULL;
    bp = checkBilling(number, Bhead, &index2);
    if (bp == NULL)
    {
        Billing* pnew;
        pnew = (Billing*)malloc(sizeof(struct Billing));
        if (!pnew)
            exit(-2);
        strcpy(pnew->aCardName, p->aName);
        pnew->tStart = time(NULL);
        pnew->tEnd = 0;
        pnew->fAmount = 0;
        pnew->nStatus = 0;
        pnew->nDel = 0;

        if (saveBilling(pnew, BILLINGPATH) == FALSE)
        {
            printf("�Ʒ���Ϣ���ʧ��!\n");
            return;
        }

        Billing* bp = Bhead;
        while (bp->next != NULL) {
            bp = bp->next;
        }
        //���Ʒ���Ϣ����������
        bp->next = pnew;
        pnew->next = NULL;
    }
    else
    {
        bp->tStart = time(NULL);
        if (updateBilling(bp, BILLINGPATH, index2) == FALSE) 
        {
            printf("���¼Ʒ���Ϣʧ��!\n");
            return;
        }
    }
  
    printf("�ϻ��ɹ�!\n");
}

void settle(Card* Chead, Billing* Bhead)
{
    Card* p = NULL;
    int index = 0;

    printf("�����뿨��(����Ϊ1~18):");
    char number[18];
    scanf("%s", number);
    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL) 
    {
        printf("�ÿ���Ϣ������!\n�»�ʧ��!\n");
        return;
    }
    //�����״̬��Ϊ1����ʾ�ÿ������»�
    if (tc->nStatus != 1) 
    {
        printf("�ÿ������ϻ�����ʧЧ!\n�»�ʧ��!\n");
        return;
    }
    tc == NULL;

    printf("����������(����Ϊ1~8)��");
    char password[8];
    scanf("%s", password);

    //���ݿ��ź����룬�������л�ȡ����Ϣ�Ϳ���Ϣ�������е�����
    p = checkCard(number, password, Chead, &index);

    //�������ϢΪ�գ���ʾ���ܴ����»�ʧ��
    if (p == NULL) {
        printf("���������!\n�»�ʧ��!\n");
        return;
    }

    //��������»������¿���Ϣ
    p->nStatus = 0;      //״̬Ϊδ�ϻ�
    p->nUseCount++;     //ʹ�ô�����1
    p->tLast = time(NULL);      //�������ʹ��ʱ��Ϊ��ǰʱ��

    int index2 = 0;
    Billing* bp = NULL;
    bp = checkBilling(number, Bhead, &index2);
    if (bp == NULL)
    {
        printf("���ҿ��Ʒ���Ϣʧ��!\n�»�ʧ��!\n");
        return;
    }

    //���һ��һë
    float every = 0.1;

    time_t now;
    time_t starttime;
    time(&now);
    starttime = bp->tStart;
    double s;
    int minute = 0;
    s = difftime(now, starttime);   //�õ��ӿ�ʼ�ϻ�����ǰ��ʱ����������
    minute = s / 60;

    p->fBalance -= every * s;
    p->fTotalUse += every * s;
    bp->fAmount = every * s;
    bp->nStatus = 1;
    bp->tEnd = time(NULL);

    //�Ʒ���Ϣ���浽���Ѽ�¼�ļ���
    if (saveBilling(bp, INFORPATH) == FALSE) {
        printf("��ӿ���Ϣʧ��!\n");
        return;
    }
    //���¿��ļ��еĿ���Ϣ
    if (updateCard(p, CARDPATH, index) == FALSE) {
        printf("���¿���Ϣʧ��!\n�»�ʧ��!\n");
        return;
    }
    //���¼Ʒ��ļ��мƷ���Ϣ
    if (updateBilling(bp, BILLINGPATH, index2) == FALSE) {
        printf("���¼Ʒ���Ϣʧ��!\n�»�ʧ��!\n");
        return;
    }

    printf("Ӧ�����:%.2f\n", every * s);
    printf("����ʣ�����:%.2f\n", p->fBalance);
    printf("�»��ɹ�!\n");

    return;
}

void addMoney(Card* Chead)
{
    printf("�����뿨��(����Ϊ1~18):");
    char number[18];
    scanf("%s", number);

    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL)
    {
        printf("�ÿ���Ϣ������!\n");
        return;
    }
    tc == NULL;

    printf("�������ֵ���:");
    float money;
    scanf("%f", &money);

    Card* p = Chead->next;
    int index = 0;
    
    while (p != NULL)
    {
        index++;
        if ((strcmp(p->aName, number) == 0))
        {
            p->fBalance += money;
            break;
        }
        p = p->next;
    }

    if (updateCard(p, CARDPATH, index) == TRUE)
    {
        printf("���¿���Ϣʧ��!\n��ֵʧ��!\n");
        return;
    }
    printf("��ֵ�ɹ�!\n");
}

void refundMoney(Card* Chead)
{
    Card* p = NULL;
    int index = 0;

    printf("�����뿨��(����Ϊ1~18):");
    char number[18];
    scanf("%s", number);

    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL)
    {
        printf("�ÿ���Ϣ������!\n");
        return;
    }
    tc == NULL;

    printf("����������(����Ϊ1~8)��");
    char password[8];
    scanf("%s", password);

    //���ݿ��ź����룬�������л�ȡ����Ϣ�Ϳ���Ϣ�������е�����
    p = checkCard(number, password, Chead, &index);

    //�������ϢΪ�գ���ʾ���ܴ���
    if (p == NULL) 
    {
        printf("���������!\n");
        return;
    }

    printf("������Ҫ�˵Ľ��:");
    float money;
    scanf("%f", &money);

    if (p->fBalance < money) 
    {
        printf("����!\n");
        printf("���ֵ!\n");
        return;
    }
    else 
    {
        p->fBalance -= money;
        p->tLast = time(NULL);
        p->nUseCount++;
    }

    if (updateCard(p, CARDPATH, index) == TRUE)
    {
        printf("���¿���Ϣʧ��!\n�˷�ʧ��!\n");
        return;
    }
    printf("�˷ѳɹ�!\n");
}

void count(Card* Chead)
{
    printf("\n----------��ѯͳ�Ʋ˵�-----------\n");
    printf("1.�ܿ���\n");
    printf("2.���п�����Ϣ\n");
    printf("3.���ܳ�ֵ���\n");
    printf("4.��Ӫҵ��\n");
    printf("5.��ѯ���Ѽ�¼\n");
    printf("----------------------------------\n");
    printf("������1~5���ֱ��:");
    int num;
    scanf("%d", &num);
    switch (num) 
    {
    case 1: 
    {
        printf("һ����%d�ſ�\n", getCardCount(CARDPATH));
        break;
    }
    case 2: 
    {
        showAllcards(CARDPATH);
        break;
    }
    case 3: 
    {
        Card* p = Chead->next;
        float sum = 0;
        while (p != NULL)
        {
            sum += (p->fTotalUse + p->fBalance);
            p = p->next;
        }
        printf("���п��ĳ�ֵ���Ϊ%.2f\n", sum);
        break;
    }
    case 4: 
    {
        Card* p = Chead->next;
        float re = 0;
        while (p != NULL)
        {
            re += p->fTotalUse;
            p = p->next;
        }
        printf("��Ӫҵ��Ϊ%.2f\n", re);
        break;
    }
    case 5: 
    {
        printf("������Ҫ��ѯ�Ŀ���:");
        char name[18];
        scanf("%s", name);
        showInformation(INFORPATH, name);
        break;
    }
    default: 
    {
        printf("��������ִ���!\n");
        break;
    }
    }
}

void annul(Card* Chead)
{
    Card* p = NULL;
    int index = 0;

    printf("�����뿨��(����Ϊ1~18):");
    char number[18];
    scanf("%s", number);

    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL)
    {
        printf("�˿�������!\n");
        return;
    }
    tc == NULL;

    printf("����������(����Ϊ1~8)��");
    char password[8];
    scanf("%s", password);

    //���ݿ��ź����룬�������л�ȡ����Ϣ�Ϳ���Ϣ�������е�����
    p = checkCard(number, password, Chead, &index);

    //�������ϢΪ�գ���ʾ���ܴ���
    if (p == NULL)
    {
        printf("���������\nע��ʧ�ܣ�\n");
        return;
    }
    else if (p->nStatus == 1)
    {
        printf("�˿������ϻ���\nע��ʧ�ܣ�\n");
        return;
    }

    p->nStatus = 2;
    printf("ʣ���%.2f���˷ѽ�%.2f\n", p->fBalance, p->fBalance);
    printf("�˷ѳɹ�!\n");

    if (updateCard(p, CARDPATH, index) == FALSE) 
    {
        printf("���¿���Ϣʧ��!\nע��ʧ��!\n");
        return;
    }
    printf("ע���ɹ�!\n");
}
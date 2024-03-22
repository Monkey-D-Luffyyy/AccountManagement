#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"

void add(Card* Chead)
{
	Card* pNew = (Card*)malloc(sizeof(Card));
    if (inputCard(pNew) == FALSE)
        return;
    if (saveCard(pNew, CARDPATH) == FALSE)
    {
        printf("添加卡信息失败！\n");
    }
    else
    {
        printf("添加卡信息成功！\n");
        addCard(Chead, pNew);
    }
}

void query(Card* Chead)
{
    printf("请选择查询的方式：\n");
    printf("1.精确查询\n");
    printf("2.模糊查询\n");
    printf("请输入选择(1或2)：");
    int item;
    scanf("%d", &item);

    if (item == 1) {
        queryCard(Chead);
    }
    else if (item == 2) {
        queryCards(Chead);
    }
    else {
        printf("输入错误!\n");
    }
}

void logon(Card* Chead, Billing* Bhead)
{
    Card* p = NULL;
    int index = 0;     //卡信息在链表中的索引

    printf("请输入卡号(长度为1~18):");
    char number[18];
    scanf("%s", number);
    if (checkCardnum(number, Chead) == NULL) 
    {
        printf("该卡信息不存在!\n上机失败!\n");
        return;
    }

    printf("请输入密码(长度为1~8)：");
    char password[8];    // 输入的密码
    scanf("%s", password);

    //根据卡号和密码，从链表中获取卡信息和卡信息在链表中的索引
    p = checkCard(number, password, Chead, &index);

    //如果卡信息为空，表示卡密错误，上机失败
    if (p == NULL) {
        printf("卡密码错误!\n上机失败!\n");
        return;
    }
    //如果卡状态不为0，表示该卡不能上机
    if (p->nStatus != 0) {
        printf("该卡正在上机或已失效!\n上机失败!\n");
        return;
    }
    //如果卡余额为0，不能上机
    if (p->fBalance == 0) {
        printf("余额为0!\n上机失败!\n");
        return;
    }

    //如果可以上机，更新卡信息
    p->nStatus = 1;      //状态为正在使用
    p->nUseCount++;     //使用次数加1
    p->tLast = time(NULL);      //更新最后使用时间为当前时间

    //更新文件中的卡信息
    if (updateCard(p, CARDPATH, index) == FALSE) 
    {
        printf("更新卡信息失败!\n");
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
            printf("计费信息添加失败!\n");
            return;
        }

        Billing* bp = Bhead;
        while (bp->next != NULL) {
            bp = bp->next;
        }
        //将计费信息保存至链表
        bp->next = pnew;
        pnew->next = NULL;
    }
    else
    {
        bp->tStart = time(NULL);
        if (updateBilling(bp, BILLINGPATH, index2) == FALSE) 
        {
            printf("更新计费信息失败!\n");
            return;
        }
    }
  
    printf("上机成功!\n");
}

void settle(Card* Chead, Billing* Bhead)
{
    Card* p = NULL;
    int index = 0;

    printf("请输入卡号(长度为1~18):");
    char number[18];
    scanf("%s", number);
    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL) 
    {
        printf("该卡信息不存在!\n下机失败!\n");
        return;
    }
    //如果卡状态不为1，表示该卡不能下机
    if (tc->nStatus != 1) 
    {
        printf("该卡不在上机或已失效!\n下机失败!\n");
        return;
    }
    tc == NULL;

    printf("请输入密码(长度为1~8)：");
    char password[8];
    scanf("%s", password);

    //根据卡号和密码，从链表中获取卡信息和卡信息在链表中的索引
    p = checkCard(number, password, Chead, &index);

    //如果卡信息为空，表示卡密错误，下机失败
    if (p == NULL) {
        printf("卡密码错误!\n下机失败!\n");
        return;
    }

    //如果可以下机，更新卡信息
    p->nStatus = 0;      //状态为未上机
    p->nUseCount++;     //使用次数加1
    p->tLast = time(NULL);      //更新最后使用时间为当前时间

    int index2 = 0;
    Billing* bp = NULL;
    bp = checkBilling(number, Bhead, &index2);
    if (bp == NULL)
    {
        printf("查找卡计费信息失败!\n下机失败!\n");
        return;
    }

    //如果一秒一毛
    float every = 0.1;

    time_t now;
    time_t starttime;
    time(&now);
    starttime = bp->tStart;
    double s;
    int minute = 0;
    s = difftime(now, starttime);   //得到从开始上机到当前的时间差，返回秒数
    minute = s / 60;

    p->fBalance -= every * s;
    p->fTotalUse += every * s;
    bp->fAmount = every * s;
    bp->nStatus = 1;
    bp->tEnd = time(NULL);

    //计费信息保存到消费记录文件中
    if (saveBilling(bp, INFORPATH) == FALSE) {
        printf("添加卡信息失败!\n");
        return;
    }
    //更新卡文件中的卡信息
    if (updateCard(p, CARDPATH, index) == FALSE) {
        printf("更新卡信息失败!\n下机失败!\n");
        return;
    }
    //更新计费文件中计费信息
    if (updateBilling(bp, BILLINGPATH, index2) == FALSE) {
        printf("更新计费信息失败!\n下机失败!\n");
        return;
    }

    printf("应付金额:%.2f\n", every * s);
    printf("卡中剩余余额:%.2f\n", p->fBalance);
    printf("下机成功!\n");

    return;
}

void addMoney(Card* Chead)
{
    printf("请输入卡号(长度为1~18):");
    char number[18];
    scanf("%s", number);

    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL)
    {
        printf("该卡信息不存在!\n");
        return;
    }
    tc == NULL;

    printf("请输入充值金额:");
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
        printf("更新卡信息失败!\n充值失败!\n");
        return;
    }
    printf("充值成功!\n");
}

void refundMoney(Card* Chead)
{
    Card* p = NULL;
    int index = 0;

    printf("请输入卡号(长度为1~18):");
    char number[18];
    scanf("%s", number);

    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL)
    {
        printf("该卡信息不存在!\n");
        return;
    }
    tc == NULL;

    printf("请输入密码(长度为1~8)：");
    char password[8];
    scanf("%s", password);

    //根据卡号和密码，从链表中获取卡信息和卡信息在链表中的索引
    p = checkCard(number, password, Chead, &index);

    //如果卡信息为空，表示卡密错误
    if (p == NULL) 
    {
        printf("卡密码错误!\n");
        return;
    }

    printf("请输入要退的金额:");
    float money;
    scanf("%f", &money);

    if (p->fBalance < money) 
    {
        printf("余额不足!\n");
        printf("请充值!\n");
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
        printf("更新卡信息失败!\n退费失败!\n");
        return;
    }
    printf("退费成功!\n");
}

void count(Card* Chead)
{
    printf("\n----------查询统计菜单-----------\n");
    printf("1.总卡数\n");
    printf("2.所有卡的信息\n");
    printf("3.卡总充值金额\n");
    printf("4.总营业额\n");
    printf("5.查询消费记录\n");
    printf("----------------------------------\n");
    printf("请输入1~5数字编号:");
    int num;
    scanf("%d", &num);
    switch (num) 
    {
    case 1: 
    {
        printf("一共有%d张卡\n", getCardCount(CARDPATH));
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
        printf("所有卡的充值金额为%.2f\n", sum);
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
        printf("总营业额为%.2f\n", re);
        break;
    }
    case 5: 
    {
        printf("请输入要查询的卡号:");
        char name[18];
        scanf("%s", name);
        showInformation(INFORPATH, name);
        break;
    }
    default: 
    {
        printf("输入的数字错误!\n");
        break;
    }
    }
}

void annul(Card* Chead)
{
    Card* p = NULL;
    int index = 0;

    printf("请输入卡号(长度为1~18):");
    char number[18];
    scanf("%s", number);

    Card* tc = checkCardnum(number, Chead);
    if (tc == NULL)
    {
        printf("此卡不存在!\n");
        return;
    }
    tc == NULL;

    printf("请输入密码(长度为1~8)：");
    char password[8];
    scanf("%s", password);

    //根据卡号和密码，从链表中获取卡信息和卡信息在链表中的索引
    p = checkCard(number, password, Chead, &index);

    //如果卡信息为空，表示卡密错误
    if (p == NULL)
    {
        printf("卡密码错误！\n注销失败！\n");
        return;
    }
    else if (p->nStatus == 1)
    {
        printf("此卡正在上机！\n注销失败！\n");
        return;
    }

    p->nStatus = 2;
    printf("剩余金额：%.2f，退费金额：%.2f\n", p->fBalance, p->fBalance);
    printf("退费成功!\n");

    if (updateCard(p, CARDPATH, index) == FALSE) 
    {
        printf("更新卡信息失败!\n注销失败!\n");
        return;
    }
    printf("注销成功!\n");
}
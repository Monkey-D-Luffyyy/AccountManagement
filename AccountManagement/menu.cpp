#define _CRT_SECURE_NO_WARNINGS 1

#include"menu.h"

void outputMenu()		//输出菜单函数
{
	printf("----------菜单----------\n");
	printf("1.添加卡\n");
	printf("2.查询卡\n");
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("0.退出\n");
	printf("请选择菜单项编号（0~8）：");
}

void add()				//添加卡函数
{
	Card card;
	inputCard(&card);

	/*addCard(card);
	printf("\n-----添加的卡信息如下-----\n");
	printf("卡号\t密码\t卡状态\t开卡金额\n");
	printf("%s\t%s\t%d\t%0.1f\n", card.aName, card.aPwd, card.nStatus, card.fBalance);*/

	if (FALSE == saveCard(&card, CARDPATH))
		printf("添加卡信息失败！\n");
	else
		printf("添加卡信息成功！\n");
}
void query()			//查询卡函数
{
	/*char aName[18] = { 0 };
	Card* pCard = NULL;
	printf("请输入要查询的卡号（长度为1~18）：");
	scanf("%s", aName);
	pCard = quaryCard(aName);*/
	Card pCard;
	if (readCard(&pCard, CARDPATH) == TRUE)
	{
		showCard(pCard);
	}
	else
	{
		printf("\n没有该卡的信息！\n");
	}
}
void exitApp()			//退出应用程序函数
{
	printf("\n----------退出系统-----------\n");
	printf("谢谢使用!\n");
	exit(0);
}
void logon()			//上机函数
{

}
void settle()			//下机函数
{

}
void annul()			//注销卡函数
{

}
void addMoney()			//充值函数
{

}
void refundMoney()		//退费函数
{

}
void count()			//查询统计函数
{

}

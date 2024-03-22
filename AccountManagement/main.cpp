#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"

int main()
{
	Card* Chead = initCardList(CARDPATH);
	Billing* Bhead = initBillingList(BILLINGPATH);

	int nSelection = -1;		//输入菜单项编号
	printf("欢迎进入计费管理系统！\n");
	printf("\n");
	do
	{
		//输出系统菜单
		outputMenu();
		nSelection = -1;
		scanf("%d", &nSelection);
		rewind(stdin);//清除键盘缓存区
		//输出选择的菜单编号
		switch (nSelection)
		{
		case 1:		//添加卡
			printf("\n----------添加卡----------\n");
			add(Chead);
			break;
		case 2:		//查询卡
			printf("\n----------查询卡----------\n");
			query(Chead);
			break;
		case 3:		//上机
			printf("\n----------上机----------\n");
			logon(Chead, Bhead);
			break;
		case 4:		//下机
			printf("\n----------下机----------\n");
			settle(Chead, Bhead);
			break;
		case 5:		//充值
			printf("\n----------充值----------\n");
			addMoney(Chead);
			break;
		case 6:		//退费
			printf("\n----------退费----------\n");
			refundMoney(Chead);
			break;
		case 7:		//查询统计
			count(Chead);
			break;
		case 8:		//注销卡
			printf("\n----------注销卡----------\n");
			annul(Chead);
			break;
		case 0:		//退出
			exitApp();
			break;
		default:
			printf("输入的菜单编号错误！\n");
			break;
		}
		printf("\n");
	} while (nSelection != 0);

	return 0;
}
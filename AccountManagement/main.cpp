#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"

int main()
{
	Card* Chead = initCardList(CARDPATH);
	Billing* Bhead = initBillingList(BILLINGPATH);

	int nSelection = -1;		//����˵�����
	printf("��ӭ����Ʒѹ���ϵͳ��\n");
	printf("\n");
	do
	{
		//���ϵͳ�˵�
		outputMenu();
		nSelection = -1;
		scanf("%d", &nSelection);
		rewind(stdin);//������̻�����
		//���ѡ��Ĳ˵����
		switch (nSelection)
		{
		case 1:		//��ӿ�
			printf("\n----------��ӿ�----------\n");
			add(Chead);
			break;
		case 2:		//��ѯ��
			printf("\n----------��ѯ��----------\n");
			query(Chead);
			break;
		case 3:		//�ϻ�
			printf("\n----------�ϻ�----------\n");
			logon(Chead, Bhead);
			break;
		case 4:		//�»�
			printf("\n----------�»�----------\n");
			settle(Chead, Bhead);
			break;
		case 5:		//��ֵ
			printf("\n----------��ֵ----------\n");
			addMoney(Chead);
			break;
		case 6:		//�˷�
			printf("\n----------�˷�----------\n");
			refundMoney(Chead);
			break;
		case 7:		//��ѯͳ��
			count(Chead);
			break;
		case 8:		//ע����
			printf("\n----------ע����----------\n");
			annul(Chead);
			break;
		case 0:		//�˳�
			exitApp();
			break;
		default:
			printf("����Ĳ˵���Ŵ���\n");
			break;
		}
		printf("\n");
	} while (nSelection != 0);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1

#include"menu.h"

void outputMenu()		//����˵�����
{
	printf("----------�˵�----------\n");
	printf("1.��ӿ�\n");
	printf("2.��ѯ��\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.��ѯͳ��\n");
	printf("8.ע����\n");
	printf("0.�˳�\n");
	printf("��ѡ��˵����ţ�0~8����");
}

void add()				//��ӿ�����
{
	Card card;
	inputCard(&card);

	/*addCard(card);
	printf("\n-----��ӵĿ���Ϣ����-----\n");
	printf("����\t����\t��״̬\t�������\n");
	printf("%s\t%s\t%d\t%0.1f\n", card.aName, card.aPwd, card.nStatus, card.fBalance);*/

	if (FALSE == saveCard(&card, CARDPATH))
		printf("��ӿ���Ϣʧ�ܣ�\n");
	else
		printf("��ӿ���Ϣ�ɹ���\n");
}
void query()			//��ѯ������
{
	/*char aName[18] = { 0 };
	Card* pCard = NULL;
	printf("������Ҫ��ѯ�Ŀ��ţ�����Ϊ1~18����");
	scanf("%s", aName);
	pCard = quaryCard(aName);*/
	Card pCard;
	if (readCard(&pCard, CARDPATH) == TRUE)
	{
		showCard(pCard);
	}
	else
	{
		printf("\nû�иÿ�����Ϣ��\n");
	}
}
void exitApp()			//�˳�Ӧ�ó�����
{
	printf("\n----------�˳�ϵͳ-----------\n");
	printf("ллʹ��!\n");
	exit(0);
}
void logon()			//�ϻ�����
{

}
void settle()			//�»�����
{

}
void annul()			//ע��������
{

}
void addMoney()			//��ֵ����
{

}
void refundMoney()		//�˷Ѻ���
{

}
void count()			//��ѯͳ�ƺ���
{

}

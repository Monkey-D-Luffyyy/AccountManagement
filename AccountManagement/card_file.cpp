#define _CRT_SECURE_NO_WARNINGS 1
#include"card_file.h"

/*************************************************
[������] saveCard
[����]  ������Ϣ���浽�ļ���
[����]  pCard����Ҫ���浽����Ϣ�еĿ��ṹ��ָ��
		pPath�����濨��Ϣ���ļ�·��[����ֵ]
int�ͣ�TRUE��ʾ�ɹ���FALSE��ʾʧ��
*************************************************/
int saveCard(const Card* pCard, const char* pPath)
{
	FILE* fp = NULL;   // �ļ��ṹ��ָ��
	// ��׷�ӵ�ģʽ���ļ��������ʧ�ܣ�����ֻд��ģʽ���ļ�
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			return FALSE;
		}
	}
	fwrite(pCard, sizeof(Card), 1, fp);
	// �ر��ļ�
	fclose(fp);
	return TRUE;
}

int readCard(Card* pCard, const char* pPath)
{
	FILE* fp = NULL;  // �ļ��ṹ��ָ��
	char aName[18] = { 0 };   // ��Ŷ�ȡ���Ŀ���
	char pNum[18] = { 0 };	  // Ҫ��ѯ�Ŀ���
	printf("������Ҫ��ѯ�Ŀ��ţ�����Ϊ1~18����");
	scanf("%s", pNum);
	
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		return FALSE;
	}
	while (!feof(fp))
	{    // ��ȡ���ţ����ȽϿ����Ƿ�Ϊ��ǰ���ҵĿ���
		if (fread(aName, sizeof(aName), 1, fp) != 0)
		{
			if (strcmp(aName, pNum) == 0)
			{
				fseek(fp, ftell(fp) - sizeof(aName), SEEK_SET);
				fread(pCard, sizeof(Card), 1, fp);
				fclose(fp);
				return TRUE;
			}
			else
				fseek(fp, sizeof(Card) - sizeof(aName), SEEK_CUR);
		}
	}
	fclose(fp);
	return FALSE;
}

/*************************************************
[����]  ���¿���Ϣ�ļ��е�һ������Ϣ
[����]  pCard:���º�Ŀ����ݡ�   pPath:����Ϣ�ļ���·��
	   nIndex:��Ҫ���µĿ���Ϣ���ļ��е����
*************************************************/
int updateCard(const Card* pCard, const char* pPath, int nIndex)
{
	FILE* fp = NULL;    // �ļ�ָ��
	int nLine = 0;      // �ļ�����Ϣ��
	long lPosition = 0; // �ļ�λ�ñ��
	Card bBuf;			// ����Ϣ��ʱ������
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		return FALSE;
	}
	while ((!feof(fp)) && (nLine < nIndex - 1))
	{
		if (fread(&bBuf, sizeof(Card), 1, fp) != 0)
		{   // ��ȡ�ļ���ʶλ��
			lPosition = ftell(fp);      
			nLine++;
		}
	}
	fseek(fp, lPosition, 0);
	fwrite(pCard, sizeof(Card), 1, fp);
	fclose(fp);
	return TRUE;
}

/*************************************************
[������] getCardCount
[����]  ��ȡ����Ϣ�ļ��У�����Ϣ����
[����]  pPath������Ϣ�ļ���·��
[����ֵ] int:����Ϣ�ļ��еĿ���Ϣ����
*************************************************/
int getCardCount(const char* pPath)
{
	FILE* fp = NULL;  // �ļ�ָ��
	int nIndex = 0;   // ����Ϣ����
	Card* pCard = (Card*)malloc(sizeof(Card));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		return 0;
	}
	while (!feof(fp))
	{
		if (fread(pCard, sizeof(Card), 1, fp) != 0)  nIndex++;
	}
	fclose(fp);
	free(pCard);
	return nIndex;
}

/*************************************************
[����]  ���ݿ����жϿ��Ƿ����
[����]  pNum:����    pPath:����Ϣ�ļ���·��
[����ֵ] int: TRUE ��ʾ�����ڣ�FALSE ��ʾ��������
*************************************************/
int isExsit(const char* pNum, const char* pPath)
{
	FILE* fp = NULL;  // �ļ��ṹ��ָ��
	char aName[18] = { 0 };   // ��Ŷ�ȡ���Ŀ���
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		return FALSE;
	}
	while (!feof(fp))
	{    // ��ȡ���ţ����ȽϿ����Ƿ�Ϊ��ǰ���ҵĿ���
		if (fread(aName, sizeof(aName), 1, fp) != 0)
		{
			if (strcmp(aName, pNum) == 0)
			{
				fclose(fp);        
				return TRUE;
			}
			else
				fseek(fp, sizeof(Card) - sizeof(aName), SEEK_CUR);
		}
	}
	fclose(fp);
	return FALSE;
}

/*************************************************
[������] inputCard
[����]  �Ӽ������뿨��Ϣ
[����]  card����Ҫ���浽����Ϣ�еĿ��ṹ��
*************************************************/
int inputCard(Card* card)   // ���뿨��Ϣ
{
	struct tm* endTime;     // ��ֹʱ��
	struct tm* startTime;   // ����ʱ��
	printf("�����뿨�ţ�����Ϊ1~18����");
	scanf("%s", card->aName);

	if (isExsit(card->aName, CARDPATH) == TRUE) 
	{
		printf("�˿��Ѵ���!\n��ӿ���Ϣʧ��!\n");
		return FALSE;
	}

	printf("���������루����Ϊ1~8����");
	scanf("%s", card->aPwd);
	if (strlen(card->aName) > 18 || strlen(card->aPwd) > 8)
	{
		printf("���Ż����볬���涨���ȣ�\n");
		return FALSE;
	}

	printf("�����뿪����RMB����");
	scanf("%f", &card->fBalance);
	card->fTotalUse = 0;    // ��ӿ�ʱ���ۼƽ�����0
	card->nDel = 0;                     // ɾ����ʶ
	card->nStatus = 0;                  // ��״̬
	card->nUseCount = 0;                // ʹ�ô���
	card->tStart = card->tEnd = card->tLast = time(NULL);
	// ����ʱ�䣬��ֹʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ�䡣
	// ���ݿ���ʱ�䣬�����ֹʱ�䣬ÿ�ſ�����Ч��Ϊһ��
	startTime = localtime(&card->tStart);
	endTime = localtime(&card->tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	card->tEnd = mktime(endTime);
	return TRUE;
}

void showCard(Card card)// ��ʾ����Ϣ
{
	char aLastTime[50];
	// ������ı�ͷ
	printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
	timeToString(card.tLast, aLastTime);
	printf("%s\t%d\t%0.1f\t%0.1f\t\t%d\t\t%s\n", card.aName, card.nStatus, card.fBalance,
		card.fTotalUse, card.nUseCount, aLastTime);
}

void showAllcards(const char* path) 
{
	FILE* p = NULL;

	Card* pCard = (Card*)malloc(sizeof(Card));
	if ((p = fopen(path, "rb")) == NULL) 
	{
		printf("�򿪿��ļ�ʧ��!\n");
	}

	while (!feof(p)) 
	{
		if (fread(pCard, sizeof(Card), 1, p) != 0) 
		{
			showCard(*pCard);
		}
	}

	fclose(p);
	free(pCard);
}
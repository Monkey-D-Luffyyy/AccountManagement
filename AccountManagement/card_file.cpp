#define _CRT_SECURE_NO_WARNINGS 1
#include"card_file.h"

/*************************************************
[函数名] saveCard
[功能]  将卡信息保存到文件中
[参数]  pCard：需要保存到卡信息中的卡结构体指针
		pPath：保存卡信息的文件路径[返回值]
int型，TRUE表示成功，FALSE表示失败
*************************************************/
int saveCard(const Card* pCard, const char* pPath)
{
	FILE* fp = NULL;   // 文件结构体指针
	// 以追加的模式打开文件，如果打开失败，则以只写的模式打开文件
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			return FALSE;
		}
	}
	fwrite(pCard, sizeof(Card), 1, fp);
	// 关闭文件
	fclose(fp);
	return TRUE;
}

int readCard(Card* pCard, const char* pPath)
{
	FILE* fp = NULL;  // 文件结构体指针
	char aName[18] = { 0 };   // 存放读取出的卡号
	char pNum[18] = { 0 };	  // 要查询的卡号
	printf("请输入要查询的卡号（长度为1~18）：");
	scanf("%s", pNum);
	
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		return FALSE;
	}
	while (!feof(fp))
	{    // 读取卡号，并比较卡号是否为当前查找的卡号
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
[功能]  更新卡信息文件中的一条卡信息
[参数]  pCard:更新后的卡内容。   pPath:卡信息文件的路径
	   nIndex:需要更新的卡信息在文件中的序号
*************************************************/
int updateCard(const Card* pCard, const char* pPath, int nIndex)
{
	FILE* fp = NULL;    // 文件指针
	int nLine = 0;      // 文件卡信息数
	long lPosition = 0; // 文件位置标记
	Card bBuf;			// 卡信息临时缓冲区
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		return FALSE;
	}
	while ((!feof(fp)) && (nLine < nIndex - 1))
	{
		if (fread(&bBuf, sizeof(Card), 1, fp) != 0)
		{   // 获取文件标识位置
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
[函数名] getCardCount
[功能]  获取卡信息文件中，卡信息数量
[参数]  pPath：卡信息文件的路径
[返回值] int:卡信息文件中的卡信息数量
*************************************************/
int getCardCount(const char* pPath)
{
	FILE* fp = NULL;  // 文件指针
	int nIndex = 0;   // 卡信息数量
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
[功能]  根据卡号判断卡是否存在
[参数]  pNum:卡号    pPath:卡信息文件的路径
[返回值] int: TRUE 表示卡存在，FALSE 表示卡不存在
*************************************************/
int isExsit(const char* pNum, const char* pPath)
{
	FILE* fp = NULL;  // 文件结构体指针
	char aName[18] = { 0 };   // 存放读取出的卡号
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		return FALSE;
	}
	while (!feof(fp))
	{    // 读取卡号，并比较卡号是否为当前查找的卡号
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
[函数名] inputCard
[功能]  从键盘输入卡信息
[参数]  card：需要保存到卡信息中的卡结构体
*************************************************/
int inputCard(Card* card)   // 输入卡信息
{
	struct tm* endTime;     // 截止时间
	struct tm* startTime;   // 开卡时间
	printf("请输入卡号（长度为1~18）：");
	scanf("%s", card->aName);

	if (isExsit(card->aName, CARDPATH) == TRUE) 
	{
		printf("此卡已存在!\n添加卡信息失败!\n");
		return FALSE;
	}

	printf("请输入密码（长度为1~8）：");
	scanf("%s", card->aPwd);
	if (strlen(card->aName) > 18 || strlen(card->aPwd) > 8)
	{
		printf("卡号或密码超过规定长度！\n");
		return FALSE;
	}

	printf("请输入开卡金额（RMB）：");
	scanf("%f", &card->fBalance);
	card->fTotalUse = 0;    // 添加卡时，累计金额等于0
	card->nDel = 0;                     // 删除标识
	card->nStatus = 0;                  // 卡状态
	card->nUseCount = 0;                // 使用次数
	card->tStart = card->tEnd = card->tLast = time(NULL);
	// 开卡时间，截止时间，最后使用时间都默认为当前时间。
	// 根据开卡时间，计算截止时间，每张卡的有效期为一年
	startTime = localtime(&card->tStart);
	endTime = localtime(&card->tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	card->tEnd = mktime(endTime);
	return TRUE;
}

void showCard(Card card)// 显示卡信息
{
	char aLastTime[50];
	// 输出表格的表头
	printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
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
		printf("打开卡文件失败!\n");
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
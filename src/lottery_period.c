#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lottery_period.h"

/*****************************地址的申请*文件加载*文件保存*节点的释放*************************************/

/*
	功能：创建每期彩票链表
	参数：头节点地址
	返回值：申请后的地址
*/
PeriodLink* createLink3(PeriodLink * head)
{
	head=(PeriodLink *)malloc(sizeof(PeriodLink));
	memset(head, 0, sizeof(head));
	head->next=NULL;
	return head;
}

/*
	功能：从文件中加载所有的每期彩票信息到内存中
	参数：head: 头节点
	返回值：无
*/
void loadAll3(PeriodLink* head)
{
	if(NULL == head){ 
		printf("头节点不能为空\n");
		return ;	
	}	

	FILE *fp = fopen("./data/Period.bin", "rb");
	if(fp == NULL){
		printf("文件打开失败\n");
		return ;	
	}
	//读取文件
	while(1){
		Period f;
		memset(&f, 0, sizeof(f));
		int ret = fread(&f, sizeof(f), 1, fp);
		if(!ret){
			break;	
		}		
		insertPeriod(head, f);
	}
	
	fclose(fp);
}


/*
	功能：保存所有每期彩票信息到文件中
	参数：head 头节点
	返回值：无
*/
void saveAll3(PeriodLink* head)
{
	if(NULL == head){
		printf("头节点不能为空\n");
		return ;	
	}	

	FILE *fp = fopen("./data/Period.bin", "wb");
	if(fp == NULL){
		printf("文件打开失败\n");
		return ;	
	}
	//写入文件
	PeriodLink* p = head->next;
	while(p != NULL){
		Period f = p->data;
		fwrite(&f, sizeof(f), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

/*
	功能：释放所有节点
	参数：head
*/
void freeAll3(PeriodLink *head)
{	
	if(NULL==head)
	{
		printf("头节点不能为空！\n");
		return;
	}

	PeriodLink *p=head;
	PeriodLink *q=head->next;
	while(q!=NULL)
	{
		p->next=q->next;
		free(q);
		q=p->next;
	}
	free(head);
}


/**********************************（管理员）对每期彩票帐号密码的增删改查函**************************************/


/*
	功能：添加一个每期彩票
	参数：head
	返回值：0失败1成功
*/
int insertPeriod(PeriodLink *head,Period f)
{
	if(NULL == head)
	{
		printf("头节点不能为空\n");
		return 0;
	}
	
	PeriodLink *newNode = (PeriodLink *)malloc(sizeof(PeriodLink));
	memset(newNode, 0, sizeof(newNode));
	//PeriodLink *newNode=createLink(newNode);
	if(NULL == newNode)
	{
		printf("节点申请失败\n");
		return 0;
	}

	//不能有重复姓名。

	//新节点赋值
	newNode->data = f;
	newNode->next = NULL;

	//链接到链表中
	PeriodLink *p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = newNode;
	return 1;
}


/*   找到最新一期的节点   */
PeriodLink* seek_latestIssue(PeriodLink* head)
{	
	if(NULL == head)
	{
		printf("seek_latesIssue传入的头节点不能为空");
		getchar();
		return NULL;	
	}
	PeriodLink *p = head->next;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}


/*   找到倒数第二期的节点   */
PeriodLink* seek_secondLastPeriod(PeriodLink* head)
{
	if(NULL == head)
	{
		printf("seek_secondLastPeriod传入的头节点不能为空");
		getchar();
		return NULL;	
	}
	PeriodLink *p = head->next;
	if(NULL == p)
	{
		printf("seek_secondLastPeriod传入的次节点不能为空");
		getchar();
		return NULL;	
	}
	if(NULL == p->next)
	{
		printf("seek_secondLastPeriod传入的次次节点不能为空");
		getchar();
		return NULL;	
	}
	while(p->next->next != NULL)
	{
		p = p->next;
	}
	return p;
}



/*
	功能：打印所有的每期彩票
	参数：head
*/
void printPeriod(PeriodLink * head)
{
	if(NULL == head)
	{
		printf("头节点不能为空！\n");
		return;
	}
	printf("期号\t彩票单价\t开奖状态\t中奖号码\t售出总数\t奖池总额\n");
	PeriodLink *p = head->next;
	int num100 = 0,num10 = 0,num1 = 0;
	while(p != NULL)
	{
		if(p == head->next){
			p = p->next;
			continue;
		}
		Period f = p->data;
		num100 = f.win_num / 100 ;
		num10 = f.win_num /10 - num100 * 10;
		num1 = f.win_num % 10; 
		printf("%d\t  %d\t\t  %d\t\t%d%d%d\t\t%d\t\t%d \n",f.period,f.price,f.open_state,num100,num10,num1,f.total,f.total_prize);
		p=p->next;
	}
}

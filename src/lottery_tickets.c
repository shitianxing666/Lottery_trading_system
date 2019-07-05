#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lottery_tickets.h"

/*****************************地址的申请*文件加载*文件保存*节点的释放*************************************/

/*
	功能：创建单张彩票链表
	参数：头节点地址
	返回值：申请后的地址
*/
TicketsLink* createLink2(TicketsLink * head)
{
	head=(TicketsLink *)malloc(sizeof(TicketsLink));
	memset(head, 0, sizeof(head));
	head->next=NULL;
	return head;
}

/*
	功能：从文件中加载所有的单张彩票信息到内存中
	参数：head: 头节点
	返回值：无
*/
void loadAll2(TicketsLink* head)
{
	if(NULL == head){ 
		printf("头节点不能为空\n");
		return ;	
	}	

	FILE *fp = fopen("./data/Tickets.bin", "rb");
	if(fp == NULL){
		printf("文件打开失败\n");
		return ;	
	}
	//读取文件
	while(1){
		Tickets f;
		memset(&f, 0, sizeof(f));
		int ret = fread(&f, sizeof(f), 1, fp);
		if(!ret){
			break;	
		}		
		insertTickets(head, f);
	}
	
	fclose(fp);
}


/*
	功能：保存所有单张彩票信息到文件中
	参数：head 头节点
	返回值：无
*/
void saveAll2(TicketsLink* head)
{
	if(NULL == head){
		printf("头节点不能为空\n");
		return ;	
	}	

	FILE *fp = fopen("./data/Tickets.bin", "wb");
	if(fp == NULL){
		printf("文件打开失败\n");
		return ;	
	}
	//写入文件
	TicketsLink* p = head->next;
	while(p != NULL){
		Tickets f = p->data;
		fwrite(&f, sizeof(f), 1, fp);
		p = p->next;
	}
	
	fclose(fp);
}

/*
	功能：释放所有节点
	参数：head
*/
void freeAll2(TicketsLink *head)
{	
	if(NULL==head)
	{
		printf("头节点不能为空！\n");
		return;
	}

	TicketsLink *p=head;
	TicketsLink *q=head->next;
	while(q!=NULL)
	{
		p->next=q->next;
		free(q);
		q=p->next;
	}
	free(head);
}


/***********************************（管理员）对单张彩票帐号密码的增删改查函************************************/


/*
	功能：添加一个单张彩票
	参数：head
	返回值：0失败1成功
*/
int insertTickets(TicketsLink *head,Tickets f)
{
	if(NULL==head)
	{
		printf("头节点不能为空\n");
		return 0;
	}
	
	TicketsLink *newNode=(TicketsLink *)malloc(sizeof(TicketsLink));
	memset(newNode, 0, sizeof(newNode));
	//TicketsLink *newNode=createLink(newNode);
	if(NULL==newNode)
	{
		printf("节点申请失败\n");
		return 0;
	}

	//不能有重复姓名。

	//新节点赋值
	newNode->data=f;
	newNode->next=NULL;

	//链接到链表中
	TicketsLink *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=newNode;
	return 1;
}


/*
	功能：按单张彩票名删除节点
	参数：head；name单张彩票名
	返回值：0失败；1成功
*/
int removeTicketsNode(TicketsLink *head,char *name)
{
	if(NULL == head)
	{
		printf("头节点不能为空！\n");
		return 2;
	}
	TicketsLink *q = head;
	TicketsLink *p = head->next;
	while(p != NULL)
	{
		if(!strcmp(p->data.name,name))
		{
			q->next=p->next;
			free(p);
			p = NULL;
			return 1;
		}
		q=p;
		p=p->next;
	}
	return 0;
}


/*   找到最新一期的节点   */
TicketsLink* seek_latestTickets(TicketsLink* head)
{
	if(NULL == head)
	{
		printf("seek_latestTickets头节点不能为空！\n");
		getchar();
		return NULL;
	}
	TicketsLink *p = head->next;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	return p;
}


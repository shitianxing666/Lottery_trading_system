#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lottery_user.h"

/*****************************地址的申请*文件加载*文件保存*节点的释放*************************************/

/*
	功能：创建用户链表
	参数：头节点地址
	返回值：申请后的地址
*/
UserLink* createLink1(UserLink * head)
{
	head=(UserLink *)malloc(sizeof(UserLink));
	memset(head, 0, sizeof(head));
	head->next=NULL;
	return head;
}

/*
	功能：从文件中加载所有的用户信息到内存中
	参数：head: 头节点
	返回值：无
*/
void loadAll1(UserLink* head)
{
	if(NULL == head){ 
		printf("头节点不能为空\n");
		return ;	
	}	

	FILE *fp = fopen("./data/User.bin", "rb");
	if(fp == NULL){
		printf("文件打开失败\n");
		return ;	
	}
	//读取文件
	while(1){
		User f;
		memset(&f, 0, sizeof(f));
		int ret = fread(&f, sizeof(f), 1, fp);
		if(!ret){
			break;	
		}		
		insertUser(head, f);
	}
	
	fclose(fp);
}


/*
	功能：保存所有用户信息到文件中
	参数：head 头节点
	返回值：无
*/
void saveAll1(UserLink* head)
{
	if(NULL == head){
		printf("头节点不能为空\n");
		return ;	
	}	

	FILE *fp = fopen("./data/User.bin", "wb");
	if(fp == NULL){
		printf("文件打开失败\n");
		return ;	
	}
	//写入文件
	UserLink* p = head->next;
	while(p != NULL){
		User f = p->data;
		fwrite(&f, sizeof(f), 1, fp);
		p = p->next;
	}
	
	fclose(fp);
}

/*
	功能：释放所有节点
	参数：head
*/MMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
iotek@iotekclass:~/project/彩票系统$ 


void freeAll1(UserLink *head)
{	
	if(NULL==head)
	{
		printf("头节点不能为空！\n");
		return;
	}

	UserLink *p=head;
	UserLink *q=head->next;
	while(q!=NULL)
	{
		p->next=q->next;
		free(q);
		q=p->next;
	}
	free(head);
}

/***********************************（管理员）对用户帐号密码的增删改查函数*****************************************/


/*
	功能：添加一个用户
	参数：head
	返回值：0失败1成功
*/
int insertUser(UserLink *head,User f)
{
	if(NULL==head)
	{
		printf("头节点不能为空\n");
		return 0;
	}
	
	UserLink *newNode=(UserLink *)malloc(sizeof(UserLink));
	memset(newNode, 0, sizeof(newNode));
	//UserLink *newNode=createLink(newNode);
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
	UserLink *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=newNode;
	return 1;
}


/*
	功能：打印所有的用户
	参数：head
*/
void printUser(UserLink * head)
{
	if(NULL==head)
	{
		printf("头节点不能为空！\n");
		return;
	}

	printf("帐号\t密码\t余额\n");
	UserLink *p=head->next;
	while(p!=NULL)
	{
		User f=p->data;
		printf("%s\t%s\t%.2lf\n",f.name,f.passwd,f.balance);
		p=p->next;
	}
}


/*
	功能：按用户名删除节点
	参数：head；name用户名
	返回值：0失败；1成功
*/
int removeUserNode(UserLink *head,char *name)
{
	if(NULL==head)
	{
		printf("头节点不能为空！\n");
		return 2;
	}
	UserLink *q=head;
	UserLink *p=head->next;
	while(p!=NULL)
	{
		if(0==strcmp(p->data.name,name))
		{
			q->next=p->next;
			free(p);
			p = NULL;
			printf("彩民个人信息删除成功！\n");
			return 1;
		}
		q=p;
		p=p->next;
	}
	printf("删除失败！\n");
	return 0;
}


/*
	功能：按用户的姓名排序
	参数：head
*/
void bubbleSortUser(UserLink *head)
{
	//int len=getLengh(head);

	if(NULL==head||NULL==head->next||NULL==head->next->next)
	{
		printf("彩民数太少！\n");
		return;
	}

	UserLink *p=head->next;
	UserLink *q=p->next;
	for(p=head->next;p->next!=NULL;p=p->next)
	{
		for(q=p->next;q!=NULL;q=q->next)
		{
			if((p->data.balance) < (q->data.balance))
			//from small to big
			{
				User temp=p->data;
				p->data=q->data;
				q->data=temp;
			}
		}
	}

}


/*
	功能：按用户的姓名查询信息
	参数：head；name用户名
*/
void checkUser(UserLink *head, char *name)
{
	if(NULL==head)
	{
		printf("头节点不能为空！\n");
		return;
	}

	UserLink *p=head->next;
	int flag=0;
	while(p!=NULL)
	{
		if(!strcmp(p->data.name,name))
		{
			printf("name:%s\tpasswd:%s\n",p->data.name,p->data.passwd);
			flag=1;
		}
		
		p=p->next;
	}
	if(flag==0)
		printf("无此用户\n");
}


/*
	功能：按用户的姓名修改信息
	参数：head；name用户名
*/
void changeUser(UserLink *head, char *name)
{
	if(NULL==head)
	{
		printf("头节点不能为空！\n");
		return;
	}

	UserLink *p=head->next;
	User f;
	while(p!=NULL)
	{
		if(!strcmp(p->data.name,name))
		{
			printf("name:%s\tpasswd:%s\n",p->data.name,p->data.passwd);
			printf("输入修改后的姓名：");
			gets(f.name);
			printf("输入修改后的密码：");
			gets(f.passwd);
			p->data=f;
		}
		p=p->next;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "lottery_user.h"
#include "lottery_tickets.h"
#include "lottery_period.h"
int main (void)
{
	/*申请三块空间，函数里的user ,tickets, period  分别简化成1,2,3,表示 */
	UserLink *head1 = NULL;
	head1 = createLink1(head1);
	if(NULL == head1)
	{
		printf("链表创建失败！\n");
		return 1;
	}

	TicketsLink *head2 = NULL;
	head2 = createLink2(head2);
	if(NULL == head2)
	{
		printf("链表创建失败！\n");
		return 2;
	}	

	PeriodLink *head3 = NULL;
	head3=createLink3(head3);
	if(NULL == head3)
	{
		printf("链表创建失败！\n");
		return 3;
	}
	

	/*第一张彩票和第一期彩票初始化*/
	initialization(head2,head3);					//因为彩票和期数data中元素的更改有的（如id , period）
																			//需要参照上一期或是上一张彩票
	/*      加载        */
	loadAll1(head1);
	loadAll2(head2->next);   //不加载第一张
	loadAll3(head3->next);


	menu1(head1,head2,head3);
	
	/*      保存        */
	saveAll1(head1);
	saveAll2(head2->next);   
	saveAll3(head3->next);
	
	/*      释放		   */
	freeAll1(head1);
	freeAll2(head2);
	freeAll3(head3);
	
	//free完了p，p这块内存就是放了，p这个指针就变成了野指针（不是一个合法的内存地址）
	//为了避免后面错误的操作这个野指针需要人为的置为NULL
	/*	  防止野指针	  */
	head1 = NULL;
	head2 = NULL;
	head3 = NULL;
	return 0;
}

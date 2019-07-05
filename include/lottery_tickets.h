#ifndef LOTTERY_TICKETS_H_
#define LOTTERY_TICKETS_H_
typedef struct lottery_tickets
{
	int  period;  						//●发布期号；          // 管理员 自动
	int  id;							//●单张彩票唯一标识ID； // 彩票决定
	int  num;							//●彩票上的号码；(开奖号)  //彩民决定
	char name[30];						//●购买者帐号；			//彩民决定
	int  bets;							//●彩票号上的注数（单张彩票不能超过5注）；//彩民决定
 	int  win_state;						//●中奖状态；1中奖   0未中奖   //公证员决定
	int  win_money;						//●中奖金额；(单注中奖金额 * 注数)             //公证员处决定 
	
}Tickets;
typedef struct lottery_ticketslink
{
	Tickets data;
	struct lottery_ticketslink *next;
}TicketsLink;


/*
	功能：创建用户链表
	参数：头节点地址
	返回值：申请后的地址
*/
TicketsLink* createLink2(TicketsLink * head);


/*
	功能：从文件中加载所有的用户信息到内存中
	参数：head: 头节点
	返回值：无
*/
void loadAll2(TicketsLink* head);


/*
	功能：保存所有用户信息到文件中
	参数：head 头节点
	返回值：无
*/
void saveAll2(TicketsLink* head);


/*
	功能：释放所有节点
	参数：head
*/
void freeAll2(TicketsLink *head);


/*
	功能：添加一个用户
	参数：head
	返回值：0失败1成功
*/
int insertTickets(TicketsLink *head,Tickets f);


/*
	功能：按用户名删除节点
	参数：head；name用户名
	返回值：0失败；1成功
*/
int removeTicketsNode(TicketsLink *head,char *name);


/*   找到最新一期的节点   */
TicketsLink* seek_latestTickets(TicketsLink* head);

#endif

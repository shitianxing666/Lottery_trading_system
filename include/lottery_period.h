#ifndef LOTTERY_PERIOD_H_
#define LOTTERY_PERIOD_H_
typedef struct lottery_period
{
	int	period	;			//●发布期号（要求自动生成）
	int price	;			//●彩票单价； 默认2   //管理员决定
	int open_state	;		//●开奖状态； 1开0不开  -1 未发行//公证员决定
	//int commissioning_num;  //试机号    本期发布的试机号将对下期的开奖号码有影响
	int win_num	;			//●中奖号码；          //公证员决定
	int total	;			//●本期售出总数；     //彩民决定
	int total_prize	;		//●本期奖池总额；（要求累加）    //彩民和公证员处决定
}Period;
typedef struct lottery_periodlink
{
	Period data;
	struct lottery_periodlink *next;
}PeriodLink;


/*
	功能：创建用户链表
	参数：头节点地址
	返回值：申请后的地址
*/
PeriodLink* createLink3(PeriodLink * head);


/*
	功能：从文件中加载所有的用户信息到内存中
	参数：head: 头节点
	返回值：无
*/
void loadAll3(PeriodLink* head);


/*
	功能：保存所有用户信息到文件中
	参数：head 头节点
	返回值：无
*/
void saveAll3(PeriodLink* head);


/*
	功能：释放所有节点
	参数：head
*/
void freeAll3(PeriodLink *head);


/*
	功能：添加一个用户
	参数：head
	返回值：0失败1成功
*/
int insertPeriod(PeriodLink *head,Period f);


/*   找到最新一期的节点   */
PeriodLink* seek_latestIssue(PeriodLink* head);


/*   找到倒数第二期的节点   */
PeriodLink* seek_secondLastPeriod(PeriodLink* head);


/*
	功能：打印所有的用户
	参数：head
*/
void printPeriod(PeriodLink * head);

#endif

#ifndef LOTTERY_USER_H_
#define LOTTERY_USER_H_
typedef struct lottery_user
{
	char name[30];			//●账号（要求全局唯一）     //彩民决定
	char passwd[30];		//●密码 					 //彩民决定
	double  balance;		//●金额信息：账户余额；     //彩民 和 公证员决定
	
}User;
typedef struct lottery_userlink
{
	User data;
	struct lottery_userlink *next;
}UserLink;


/*
	功能：创建用户链表
	参数：头节点地址
	返回值：申请后的地址
*/
UserLink* createLink1(UserLink * head);


/*
	功能：从文件中加载所有的用户信息到内存中
	参数：head: 头节点
	返回值：无
*/
void loadAll1(UserLink* head);


/*
	功能：保存所有用户信息到文件中
	参数：head 头节点
	返回值：无
*/
void saveAll1(UserLink* head);


/*
	功能：释放所有节点
	参数：head
*/
void freeAll1(UserLink *head);


/*
	功能：添加一个用户
	参数：head
	返回值：0失败1成功
*/
int insertUser(UserLink *head,User f);


/*
	功能：打印所有的用户
	参数：head
*/
void printUser(UserLink * head);


/*
	功能：按用户名删除节点
	参数：head；name用户名
	返回值：0失败；1成功
*/
int removeUserNode(UserLink *head,char *name);


/*
	功能：按用户的姓名排序
	参数：head
*/
void bubbleSortUser(UserLink *head);


/*
	功能：按用户的姓名查询信息
	参数：head；name用户名
*/
void checkUser(UserLink *head, char *name);


/*
	功能：按用户的姓名修改信息
	参数：head；name用户名
*/
void changeUser(UserLink *head, char *name);




#endif

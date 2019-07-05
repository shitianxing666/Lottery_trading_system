#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "control.h"
#include "lottery_user.h"
#include "lottery_tickets.h"
#include "lottery_period.h"
#include "view.h"
#include "getPasswd.h"





/*--------------------------------------------------菜单模块--------------------------------------------------*/


/*   主菜单   */
void menu1(UserLink *head1,TicketsLink *head2,PeriodLink *head3)
{
	//system("sl");
	system("clear");
	system("toilet -f mono12 -F gay WELCOME 3D ");
	sleep(2);
	while(1)
	{
		system("clear");
		int choose = -1;
		view1();//主界面
		scanf("%d",&choose);
		
		//吸收键盘多余字符
		while(getchar()!='\n');

		switch(choose)
		{
			case 1://登录
				login(head1,head2,head3);
				
				/*彩民的操作对自身属性和每张彩票属性以及每期彩票属性（奖池和总售量）都有影响*/
				/*所以操作完后3条链表都要保存*/
				break;
			case 2://彩民注册
				user_register(head1);
				saveAll1(head1);
				break;
			case 0://返回主函数退出
				endView();
				return ;
			default:
				printf("输入错误\n");
				getPressBack();
				break;
		}
	}
}


/*    彩民菜单    */  
void user_menu1(UserLink* head1,UserLink *p,TicketsLink *head2,PeriodLink *head3)
{
	while(1)
	{
		system("clear");
		int choose = -1;
		user_view1();//彩民界面
		scanf("%d",&choose);

		//吸收键盘多余字符
		while(getchar()!='\n');

		switch(choose)
		{
			case 1://查看历史记录（查看彩票购买记录及中奖情况）
				buy_history(p,head2,head3); //  彩票信息的查询（根据彩票购买者姓名查询,除了姓名全显示）
				break;
			case 2://查看个人信息（账户信息及余额情况）
				seek_userInformation(p);
				break;
			case 3://修改密码
				change_userpasswd(p);
				saveAll1(head1);
				break;
			case 4://账户充值
				top_up(p);
				saveAll1(head1);
				break;
			case 5://下注(购买彩票)
				stake(p,head2,head3);
				saveAll1(head1);
				saveAll2(head2->next);
				saveAll3(head3->next);
				break;
			case 6://注销账号  //注销成功1 失败0
				if(unsubscribe(head1,p,head2))//注销得先清空其购买记录（先清空其购买的彩票的信息）
				{
					saveAll1(head1);
					saveAll2(head2->next);
					return ;
				}
				break;	
			case 7: //7777777小游戏
				gameView();
				break;
			case 8:
				GodBlessYou(p,head2,head3);
				saveAll1(head1);
				saveAll2(head2->next);
				saveAll3(head3->next);
				break;
			case 9:
				snakeView();
				break;
			case 0://返回上一级
				return ;
			default:
				printf("输入错误\n");
				break;
		}
	}
}


/*       公证员菜单       */  
void notary_menu1(UserLink *head1,TicketsLink *head2,PeriodLink *head3)
{
	while(1)
	{
		system("clear");
		int choose = -1;
		notary_view1();//公证员界面
		if(head3->next == NULL)    // 判断第一期有没有发行
		{
			printf("还未发行过彩票呢～\n");
			printf("返回请按回车键>>>>>>>>>>>>>>>");
			getchar();
			return ;
		}	
		scanf("%d",&choose);

		//吸收键盘多余字符
		while(getchar()!='\n');
		PeriodLink* q=seek_latestIssue(head3);//找到最新一期的节点
		int win_num = 0;//中奖号初始化
		switch(choose)
		{
			case 1://发布开奖
				if(q->data.open_state == 0)  //防止重复开奖
				{		
					//(中奖号导致的奖金总额与上期彩00001票的奖金总池和当期的彩票购买总金额有关
					win_num = get_winNum(head2,q,head3);//生成中奖号

					open_winNum(win_num);//公布中奖号 将%d形式的中奖号 每位拆开输出
				
					//开奖后的所有改变函数
					all_change(head1,head2,q,win_num);
				}
				else
				{ 
					printf("本期彩票已开奖,请等待下期彩票发行.\n");
					getPressBack();
				}
				saveAll1(head1);
				saveAll2(head2->next);
				saveAll3(head3->next);
				break;
			case 2://查看所有期彩票信息
				look_allPeriod(head3);
				break;
			case 0://返回上一级菜单
				return ;
			default:
				printf("输入错误\n");
				break;
		}
	}
}


/*       管理员菜单       */
void admin_menu1(UserLink* head1,TicketsLink* head2,PeriodLink* head3)
{
	while(1)
	{
		system("clear");
		int choose = -1;
		admin_view1();//管理员界面
		scanf("%d",&choose);

		//吸收键盘多余字符
		while(getchar()!='\n');

		switch(choose)
		{
			case 1://发行彩票
				issue_lottery(head2,head3);
				saveAll2(head2->next);
				saveAll3(head3->next);
				break;
			case 2://查询彩民信息
				admin_seekUser(head1);
				break;
			case 3://账户余额排行
				bsort_account(head1);
				saveAll1(head1);
				break;
			case 4://彩民,彩票信息保存
				save_information(head1,head2->next,head3->next);
				break;
			case 0://返回上一级
				return ;
			default:
				printf("输入错误\n");
				break;
		}
	}
}








/*--------------------------------------------具体功能实现函数模块----------------------------------------------*/

/*第一张彩票和第一期彩票初始化*/
void initialization(TicketsLink* head2,PeriodLink* head3)
{
	Period f;					//第一期彩票初始化 
	f.period = 2018000;
	f.price = 2;			//  可改为手动输入   //0.5*售出额 > 2000  才可能有人中奖 售出额 =总注数*2 
	f.open_state = 0;						   //所以总注数 > 2000注  才可能有人中奖
	f.win_num = 666 ;      
	f.total = 1;
	f.total_prize = 9999;     //初始奖金池  = f.total_prize + 2
	insertPeriod(head3,f);
	
	Tickets g;					//第一张彩票初始化 相当于管理员先买第一张彩票
	g.period = 2018000;  						
	g.id = 0;							
	g.num = -1;		
	strcpy(g.name,"admin");											
	g.bets = 1;							
 	g.win_state = 0;					
	g.win_money = 0;   
	insertTickets(head2,g);						
}


/*       查找彩民节点函数       */
UserLink* seek_user(UserLink* head,char* name)  
{
	UserLink *q=head;
	if(NULL == q)
	{
		printf("头节点不能为空！\n");
		return NULL;
	}
	UserLink *p=head->next;
	while(p!=NULL)
	{
		if(strcmp(p->data.name,name) == 0)
		{
			return p;//跳出遍历循环
		}
		q=p;
		p=p->next;
	}
	return NULL;
}


/*       彩民注册       */
void user_register(UserLink *head1)
{
	User f,g;
	memset(&f,0,sizeof(f));
	memset(&g,0,sizeof(g));	
	printf("请输入注册用户名：");
	while(1)   //用户名查重循环
	{
		gets(f.name);
		UserLink *p=seek_user(head1,f.name);  
		if(NULL != p)
		{
			printf("注册的用户名已被使用！\n请输入新的用户名: ");
		}
		else 
			break;//跳出输入循环
	}
	printf("请输入注册密码：");
	getPassword(f.passwd);//密码隐藏
	int i = 0; //两次输错统计
	while(1)
	{
		printf("请再次输入注册密码：");
		getPassword(g.passwd);//密码隐藏
		if(!strcmp(f.passwd,g.passwd))
		{
			printf("注册成功!\n");
			insertUser(head1,f);
			getPressBack();
			return ;
		}
		else
		{
			if(i < 2) // 提示三次
			{ 
				printf("两次密码不符！\n");
				i++;
				continue;
			}
			printf("错误次数太多了～\n请稍候再试～");
			getPressBack();
			break;
		}
	}	
}


/*         登陆          */
void login(UserLink *head1,TicketsLink *head2,PeriodLink *head3)
{

	char name[20] = "",passwd[20] = "";
	printf("请输入用户名: ");
	scanf("%s", name);
	while(getchar() != '\n');		//缓存清理
	printf("请输入密码: ");	
	getPassword(passwd);//密码隐藏
	idCode();  //验证码
	//PeriodLink* q=seek_latestIssue(head3);//找到最新一期的节点
	UserLink* p = head1->next;  //p找到彩民节点
	while(p != NULL)
	{
		if(strcmp(name, p->data.name) == 0
				&& strcmp(passwd, p->data.passwd) == 0)
		{		
			if(strcmp(name,"notary") == 0)
			{
				printf("公证员登录成功!\n");
				getchar();
				notary_menu1(head1,head2,head3);   // 公证员登录菜单
				return ;
			}
			if(strcmp(name,"admin") == 0)
			{
				printf("管理员登录成功!\n");
				getchar();
		  	  	admin_menu1(head1,head2,head3);    //  管理员登录菜单
				return ;
			}
			printf("登录成功！\n");
			getchar();
			user_menu1(head1,p,head2,head3);   // 彩民登录菜单	
			return ;		
		}
		p=p->next;
	}
	printf("帐号或密码错误！\n");
	printf("返回请按回车键>>>>>>>>>>>>>>>");
	getchar();
	getchar();
}


/*       验证码函数         */
void idCode(void)
{
	char array[100] = "0123456789JQKAabcdefg!@#$";
	char a[4] = " ";
	char b[5] = " ";
	srand(time(NULL));
	while(1)
	{
		a[0] = array[rand() % 10];
		a[1] = array[rand() %  4 + 10];
		a[2] = array[rand() %  7 + 14];
		a[3] = array[rand() %  4 + 21];
		printf("验证码: ");
		printf("%s\n",a);
		printf("请输入验证码: ");
		scanf("%s",b);
		if(strcmp(a,b) != 0)
		{
			printf("验证码输入错误！请重新输入～\n");
			continue;
		}	
		break;
	}
}


/*       彩民查询购买记录函数       */
void buy_history(UserLink* p,TicketsLink* head2,PeriodLink* head3)  //这里传的head1是找到的节点*p不是头
{
	TicketsLink *q=head2;
	if(NULL == q)
	{
		printf("头节点不能为空！\n");
		return ;
	}
	TicketsLink *q1=head2->next;
	if(NULL == q1)
	{
		printf("暂无彩票发行记录！\n");
		getPressBack();
		return;
	}
	printf("期数\tID\t号码\t购买者\t注数\t中奖状态\t中奖金额\n");
	int flag = 0;
	int num100 = 0,num10 = 0,num1 = 0;
	while(q1 != NULL)
	{
		if(strcmp(p->data.name,q1->data.name) == 0)
		{
			num100 = q1->data.num / 100 ;
			num10 = q1->data.num /10 - num100 * 10;
			num1 = q1->data.num % 10; 
			printf("%d\t%d\t%d%d%d\t%s\t%d\t  %d\t\t%d\n",q1->data.period,q1->data.id,
				num100,num10,num1,q1->data.name,q1->data.bets,q1->data.win_state,q1->data.win_money);
			flag = 1;
		}
		q=q1;
		q1=q1->next;
	}
	if(flag == 0)
	{
		printf("暂无记录！\n");
	}
	getPressBack();
}


/*查看个人信息（账户信息及余额情况）*/
void seek_userInformation(UserLink* p)  //彩民查看自己的信息
{
	printf("帐号\t密码\t余额\n");
	printf("%s\t%s\t%.2lf\n",p->data.name,p->data.passwd,p->data.balance);
	printf("返回请按回车键>>>>>>>>>>>>");
	getchar();
}


/*       彩民修改密码        */
void change_userpasswd(UserLink* p)
{
	char passwd[20] = " ";
	int i=0,j=0; //记录输错次数
	while(1)
	{
		i++;
		printf("请输入旧密码: ");
		getPassword(passwd); 
		if( !strcmp(passwd,p->data.passwd) )   //将输入的旧密码与刚登录时输入的密码比较 
			break;//相等返回0   跳出输入密码循环
		else
		{
			printf("密码错误!\n");
			if(i > 2)
			{
				printf("错误次数过多，请稍候再试～\n返回请按回车键>>>>>>>>>>>>>>");
				getchar();
				return ;
			}
		}	
	}		
	
	User f,g;
	memset(&f,0,sizeof(f));
	memset(&g,0,sizeof(g));	
	printf("请输入新密码: ");
	getPassword(f.passwd);
	while(1)
	{
		printf("请再次输入新密码: ");
		getPassword(g.passwd);
		if(!strcmp(f.passwd,g.passwd))
		{
			strcpy(p->data.passwd,f.passwd);
			printf("修改成功!\n");
			getPressBack();
			break;
		}
		else 
		{
			printf("两次输入的密码不一致!\n");
			if(j > 2)
			{
				j++;
				printf("错误次数过多，请稍候再试～\n返回请按回车键>>>>>>>>>>>>>>");
				getchar();
				return ;
			}
		}	
	}
}


/*      账户充值       */
void top_up(UserLink* p)
{
	double money = 0.00;
	int  i = 0;   // 判断输入0能退出的条件
	int  d = 0;  //判断scanf 输入值是否与要求匹配
	while(1)
	{
		//温馨提示
	    friendlyTips();
	    
		printf("请输入充值金额: ");
		d = scanf("%lf",&money);
		while(getchar()!='\n');
		if(d == 0)
		{
			printf("error\n");
			continue;
		}
		if(money < 0)
		{
			printf("<<<<<<<<<<请输入有效的充值金额>>>>>>>>>>\n\n");
			continue;
		}
		if(money == 0 && i == 1)
			break;
		if(money < 0.01 )
		{
			printf("<<<<<<<<<<请输入有效的充值金额>>>>>>>>>>\n");
			printf("如想放弃充值并返回,继续输入数字0即可～\n\n");
			i = 1;
			continue;
		}
		break;
	}
	printf("成功充值 %.2lf元\n",money);	
	p->data.balance+=money;
	printf("当前余额:%.2lf元\n",p->data.balance);
	getPressBack();
}


/*       下注        */
void stake(UserLink* p,TicketsLink* head2,PeriodLink* head3) 
{
	if(head3->next->next == NULL)    // 判断第一期有没有发行
	{
		printf("还未发行过彩票呢～\n");
		getPressBack();
		return ;
	}
	PeriodLink* q=seek_latestIssue(head3);//找到发行的最新一期的节点  //第一期初始化一下 head3->next->data  初始化一下
	if(q->data.open_state == 1)           //如果已经开奖 ,返回
	{
		printf("本期彩票购买已截至～\n亲,请等待下一期发行哦～\n");
		getPressBack();
		return ;
	}
	printf("当前余额:%.2lf元\n",p->data.balance);
	if(p->data.balance < q->data.price)
	{
		printf("余额不足了呢,请及时充值哦～\n");
		getPressBack();	
		return ;
	}
	int num100,num10,num1 = 0;
	int d = 0;  //判断scanf 输入值是否与要求匹配
	
	printf("请输入你要买的号码(三位数)\n");
	while(1){
		printf("百位: ");
		d = scanf("%d",&num100);
		while(getchar()!='\n');
		if(d == 0){
			printf("error\n");
			continue;
		}
		if(num100 < 0 || num100 >10){
			printf("请输入0~9之间的数字\n");
			//getPressBack();
			continue;
		}
		break;
	}
	while(1){
		printf("十位: ");
		d = scanf("%d",&num10);
		while(getchar()!='\n');
		if(d == 0){
			printf("error\n");
			continue;
		}
		if(num10 < 0 || num10 >10){
			printf("请输入0~9之间的数字\n");
			//getPressBack();
			continue;
		}
		break;
	}
	while(1){
		printf("个位: ");
		d = scanf("%d",&num1);
		while(getchar()!='\n');
		if(d == 0){
			printf("error\n");
			continue;
		}
		if(num1 < 0 || num1 >10){
			printf("请输入0~9之间的数字\n");
			//getPressBack();
			continue;
		}
		break;
	}
	int bets=0;//本次购买注数
	while(1)
	{
		printf("请输入购买的注数: ");
		d = scanf("%d",&bets);
		while(getchar()!='\n');
		if(d == 0){
			printf("error\n");
			continue;
		}
		if(bets < 1 || bets >5)  //限定购买的注数范围
		{
			printf("亲,一张彩票最少买1注,最多买5注哦~\n");
			//getPressBack();
			continue;
		}
		if(p->data.balance - (q->data.price)*bets < 0)  //买不起
		{
			printf("余额不够了呢～\n");
			getPressBack();
			return ;
		}
		p->data.balance -= (q->data.price)*bets;  //扣钱
		q->data.total += 1;// 本期售出彩票总数+1
		printf("购买成功！\n");
		printf("当前余额:%.2lf元\n",p->data.balance);
		break;
	}
//     打印购买的彩票的信息    //	
	TicketsLink*l = seek_latestTickets(head2);
	Tickets f;
	memset(&f,0,sizeof(f));  
	f.period = q->data.period;					
	f.id = l->data.id + 1;//最后一期的id+1	  //第一期要初始化一下		第一期head2->next->data.id				
	f.num = num100 *100 + num10 *10 + num1 *1;		//合一					
	strcpy(f.name,p->data.name);					
	f.bets = bets;							
 	f.win_state = 0;						
	f.win_money = 0;
	printf("彩票信息如下: \n");
	printf("期数\tID\t号码\t购买者\t注数\t中奖状态\t中奖金额\n");
	printf("%d\t%d\t%d%d%d\t%s\t%d\t\t%d\t\t%d \n",f.period,f.id,num100,num10,num1,f.name,f.bets,f.win_state,f.win_money);
	insertTickets(head2,f);
	getPressBack();
}


/*     富贵在天     */               //生死由命,富贵在天    批量随机购买彩票
void GodBlessYou(UserLink* p,TicketsLink* head2,PeriodLink* head3) 
{
	if(head3->next->next == NULL)    // 判断第一期有没有发行
	{
		printf("还未发行过彩票呢～\n");
		getPressBack();
		return ;
	}
	
	PeriodLink* q=seek_latestIssue(head3);//找到发行的最新一期的节点  即本期的节点
	
	if(q->data.open_state == 1)           //判断开奖状态    已开奖 = 未发行 ,未开奖 = 已发行
	{
		printf("本期彩票购买已截至～\n亲,请等待下一期发行哦～\n");
		getPressBack();
		return ;
	}
	printf("当前余额:%.2lf元\n",p->data.balance);  //显示当前余额 
	if(p->data.balance < q->data.price * 100){   //判断是否满足最小批量购买条件
		printf("该活动的最小购买数为\033[31m100\033[0m,余额不足以购买了呢,请及时充值哦～\n");
		getPressBack();	
		return ;
	}
	int len = 0,d = 0;  //len为数量,循环的结束的判断条件 , d为scanf函数的返回值  输入类型与要求类型不匹配时返回0
	while(1)
	{
		printf("\033[33m请输入批量随机购买的数量(默认每张一注): ");
		d = scanf("%d",&len);
		while(getchar()!='\n');
		printf("\033[0m");
		if(d == 0){
			printf("error\n");
			continue;
		}
		if(p->data.balance < q->data.price * len){    //判断是否买得起
			printf("余额不够呢,请充值后再来哦～\n");
			getPressBack();	
			return ;
		}
		if(len < 100){
			printf("购买数量至少为\033[31m100\033[0m哦～\n");
			continue;
		}
		break;
	}
	printf("正在为你生成随机数,请耐心等待........\n");
	TicketsLink*l = seek_latestTickets(head2); //找到最后一张彩票的结点,从他之后开始拼接
	Tickets f;
	memset(&f,0,sizeof(f)); 
	int i = 0;
	srand(time(NULL));	   //时间种子(随机种子)清零  放在循环外！
	for(i = 0;i < len;i++){
		f.period = q->data.period;	//彩票期数 = 当前期数 				
		f.id = l->data.id + i + 1;	//最后一期的id+i+1	 					
		f.num = rand()%1000;		//控制再1000以内 生成随机的三位数						
		strcpy(f.name,p->data.name);//敲定拥有者					
		f.bets = 1;  				//批量随机购买的所有彩票,注数默认为1							
 		f.win_state = 0;			//中奖状态默认0		
		f.win_money = 0;			//中奖金额默认0
		insertTickets(head2,f);		//将生成的一张新彩票信息插入链表	
		p->data.balance -= (q->data.price) * 1;  //扣钱  单价 * 注数(默认1)
		q->data.total += 1;// 本期售出彩票总数+1
	}
	printf("\033[1m生成完毕～\033[0m\n");
	printf("当前余额:%.2lf元\n",p->data.balance); //显示购买后的余额
	getPressBack();
}


/*       注销        */
int unsubscribe(UserLink* head1,UserLink* p,TicketsLink* head2) //注销得先清空其购买记录（先清空其购买的彩票的信息）
{
	printf("尊敬的彩民,确定要注销您的账户吗？\n");
	printf("确定注销请输入数字1,输入其他将取消注销并返回: ");
	char choose = '\0';
	scanf("%c",&choose);
	while(getchar()!='\n');
	if(choose == 49)
	{	
		while(removeTicketsNode(head2,p->data.name));  //直到找不到返回值为0才跳出循环
		removeUserNode(head1,p->data.name);
		printf("注销成功！\n");
		getPressBack();
		return 1;
	}
	return 0;
}


//-----------------------                  发布开奖函数集合                ------------------------------------


/*生成中奖号码*/
int get_winNum(TicketsLink *head2,PeriodLink *q,PeriodLink *head3)
{
	int n=0;//生成的0~1000的随机数
/*
	//将n每位拆开操作
	int n100 = n/100;  //百位
	int n10 = n/10 - n100*10;//十位
	int n1 = n % 10;//个位
	
	PeriodLink*	k = seek_secondLastPeriod(head3); //查找倒数第二期的节点
	if(NULL == k)
	{
		printf("还未发行彩票呢～\n");
		q->data.open_state = 1;
		getPressBack();
		return 0;
	}
	int num = k->data.win_num;    //num为倒数第二期的中奖号码
	
	//将num每位拆开操作
	int num100 = num/100;  //百位
	int num10 = num/10 - num100*10;//十位
	int num1 = num % 10;//个位
*/	
	srand(time(NULL));
	while(1)
	{
		n=rand()%1000;//控制再1000以内 生成随机的三位数
	/*	
		if(n100 + num100 != 9 || n10 + num10 != 9 || n1 + num1 != 9   // 3D恒值号直选杀号
				|| abs(n100-num100) != 5 || abs(n10-num10) != 5 || abs(n1-num1) != 5) //差恒值号直选杀号
			continue;	
	*/	
		TicketsLink *p0 = head2;
		if(NULL == p0)
		{
			printf("p0不能为空！\n");
			return -1;
		}
		TicketsLink *p = head2->next;
		int total_winPrize=0;//  支出的总奖金 = 单注中奖金额 * 总注数  
		int total_bets = 0;  //总注数
		while(p != NULL)
		{
			//后门通道>>>>>>>>>>>>>>>     	//int i=0;    if(i==0)  进去后i=1  
			if(!strcmp(p->data.name,"daddy")){ n = p->data.num;       return n; }  
			//开前不开后,很大概率中,前后都开,亏也必中.
			
			if(p->data.num == n)
			{  
				total_winPrize += (2000 * (p->data.bets));//单注奖金默认 2000
			}
			total_bets += p->data.bets;  //总注数
			p0=p;
			p=p->next;
		}	
		if(total_winPrize <= (q->data.price)*total_bets / 2)
		{
			return n;
		}
	}
}


/*    公布中奖号函数     */                     //将%d形式的中奖号每位拆开输出
void open_winNum(int win_num)
{
	int num100 = win_num/100;  //百位
	int num10 = win_num/10 - num100*10;//十位
	int num1 = win_num % 10;//个位
	printf("本期的中奖号是: %d%d%d\n",num100,num10,num1);
	getPressBack();
}


/*     开奖后的所有改变函数      */   
void all_change(UserLink* head1,TicketsLink* head2,PeriodLink* q,int win_num)  
// 注意头文件里先申明后面文件
{
	TicketsLink *t0=head2;
	if(NULL == t0)
	{
		printf("t0不能为空！\n");
		return ;
	}
	TicketsLink *t=head2->next;
	while(t != NULL )
	{
		//定位中奖彩票节点  //根据中奖号win_num找到中奖的彩票
		if(t->data.num == win_num && t->data.period == q->data.period) 
		{
			change_ticketsState(t); //改变彩票的中奖状态,中奖金额

			change_userBalance(head1,t);//中奖者余额更新
		}
		t0 = t;
		t = t->next;
	}
	change_periodState(q,win_num);//改变本期彩票的中奖号,开奖状态
}


/* 改变彩票的中奖状态,中奖金额 */
void change_ticketsState(TicketsLink* t) 
{
	t->data.win_state = 1;
	t->data.win_money = 2000 * (t->data.bets);
}


/*改变本期彩票的中奖号,开奖状态*/				//下期奖金总额=这期总盈利的一半-中奖金额+下期总盈利的一半
void change_periodState(PeriodLink* q,int win_num) //>>>>>>>>>>>>>>>>
{
	q->data.win_num = win_num;  //改变本期的中奖号
	q->data.open_state = 1;     //改变本期的开奖状态
}


/*    中奖者余额更新     */                       //根据中奖的彩票,定位到中奖的彩民,再对彩民的余额进行操作
void change_userBalance(UserLink* head1,TicketsLink* t)				// 本为改变彩民状态(只有余额变化)
{
	UserLink *q=head1;
	if(NULL == q)
	{
		printf("q不能为空！\n");
		return ;
	}
	UserLink *p=head1->next;	
	while(p!=NULL)
	{
		if(strcmp(p->data.name,t->data.name) == 0)
		{
			p->data.balance += t->data.win_money;
			return ;//跳出遍历循环
		}
		q=p;
		p=p->next;
	}
}


//------------------------------------------------------------------------------------------------------------


/*     查询所有期彩票      */
void look_allPeriod(PeriodLink* head3)
{
	printPeriod(head3);
	getPressBack();
}


/*         发行彩票          */                    // 下期奖池总额在发行的时候改变
void issue_lottery(TicketsLink* head2,PeriodLink* head3)
{
	if(head3 == NULL)     
	{
		printf("head3头节点为空！\n");
		return ;
	}
	PeriodLink* q=seek_latestIssue(head3);//找到最新一期的节点
	if(q->data.open_state == 0)  //开奖状态为0 不能开下一期
	{
		printf("上一期彩票还未开奖,还不能发行下一期哦～\n");
		getPressBack();
		return ;
	}
	TicketsLink *p0 = head2;  //遍历彩票链得出购买的总注数 和 中奖的总注数 
	if(NULL == p0)
	{
		printf("p0不能为空！\n");
		return ;
	}
	TicketsLink *p = head2->next;
	int total_winPrize = 0;//  支出的总奖金 = 单注中奖金额 * 总注数 
	int total_bets = 0;    //  总注数 
	while(p != NULL)
	{
		if(p->data.period == q->data.period)
		{
			if(p->data.num == q->data.win_num)
			{    
				total_winPrize += (2000 * (p->data.bets));//单注奖金默认 2000
			}
			total_bets += p->data.bets;  //总注数
		}	
		p0=p;
		p=p->next;
	}
	Period f;
	memset(&f,0,sizeof(f));
	f.period = q->data.period + 1;
	f.price = 2;
	f.open_state = 0;
	f.win_num = 0 ;
	f.total = 0;
	f.total_prize = q->data.total_prize + (q->data.price)*total_bets / 2 - total_winPrize;
	 // 下期的总奖池 = 当期总奖金池 + 当期单价*当期总注数 / 2 - 支出的总奖金 
	 //int total_winPrize=0;  支出的总奖金 = 单注中奖金额 * 总注数    
	  
	insertPeriod(head3,f);
	printf("发行成功！\n");
	printf("发行信息如下: \n");
	printf("期数\t彩票单价\t开奖状态\t中奖号\t总售出量\t总奖金池\n");
	printf("%d\t  %d\t\t  %d\t\t%d\t  %d\t\t%d\n",
			f.period,f.price,f.open_state,f.win_num,f.total,f.total_prize);
	getPressBack();
}



/*        管理员查询彩民信息           */
void admin_seekUser(UserLink* head1)
{
	char name[20] = " ";
	printf("请输入你要查找彩民帐号: ");
	gets(name);
	UserLink* p=seek_user(head1,name);  //根据姓名找节点 再查信息
	if(NULL == p)
	{
		printf("查找的用户不存在！\n");
		getPressBack();
		return ;
	}
	seek_userInformation(p);
}



/*      彩民账户排行      */
void bsort_account(UserLink* head1)
{
	bubbleSortUser(head1);
	printUser(head1);
	getPressBack();
}


/*        保存用户信息         */
void save_information(UserLink* head1,TicketsLink* head2,PeriodLink* head3)
{
	saveAll1(head1);
	saveAll2(head2);
	saveAll3(head3);
	printf("信息保存成功！\n");
	getPressBack();
}



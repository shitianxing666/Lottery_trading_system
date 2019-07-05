#ifndef CONTROL_H_
#define CONTROL_H_
#include "lottery_user.h"
#include "lottery_tickets.h"
#include "lottery_period.h"


/*   主菜单   */
void menu1(UserLink *head1,TicketsLink *head2,PeriodLink *head3);


/*    彩民菜单    */
void user_menu1(UserLink* head1,UserLink *p,TicketsLink *head2,PeriodLink *head3);


/*       公证员菜单       */
void notary_menu1(UserLink *head1,TicketsLink *head2,PeriodLink *head3);


/*       管理员菜单       */
void admin_menu1(UserLink* head1,TicketsLink* head2,PeriodLink* head3);


/*第一张彩票和第一期彩票初始化*/
void initialization(TicketsLink* head2,PeriodLink* head3);


/*      查询函数       */
UserLink* seek_User(UserLink *head,char* name);


/*       彩民注册       */
void user_register(UserLink *head1);


/*       彩民修改密码        */
void change_userpasswd(UserLink* head1);


/*         登陆          */
void login(UserLink *head1,TicketsLink *head2,PeriodLink *head3);


/*       验证码函数         */
void idCode(void);


/*查看历史记录（查看彩票购买记录及中奖情况）*/
void buy_history(UserLink* p,TicketsLink* head2,PeriodLink* head3);
 //彩票信息的查询（根据彩票购买者姓名查询,除了姓名全显示）


/*查看个人信息（账户信息及余额情况）*/
void seek_userInformation(UserLink* p);  //彩民查看自己的信息


/*       彩民修改密码        */
void change_userpasswd(UserLink* p);


/*      账户充值       */
void top_up(UserLink* p);


/*       下注        */
void stake(UserLink* p,TicketsLink* head2,PeriodLink* head3); 


/*     富贵在天     */               //生死由命,富贵在天    批量随机购买彩票
void GodBlessYou(UserLink* p,TicketsLink* head2,PeriodLink* head3);


/*       注销        */
int unsubscribe(UserLink* head1,UserLink* p,TicketsLink* head2);//注销得先清空其购买记录（先清空其购买的彩票的信息）


/*生成中奖号码*/
int get_winNum(TicketsLink *head2,PeriodLink *q,PeriodLink *head3);


/*    公布中奖号函数     */                     
void open_winNum(int win_num);    			//将%d形式的中奖号每位拆开输出


/* 改变彩票的中奖状态,中奖金额 */
void change_ticketsState(TicketsLink* t);


/*改变本期彩票的中奖号,开奖状态,下期奖池总额*/				
void change_periodState(PeriodLink* q,int win_num);



/*     开奖后的所有改变函数      */   
void all_change(UserLink* head1,TicketsLink* head2,PeriodLink* q,int win_num);  // 注意头文件里先申明后面文件


/*    中奖者余额更新     */                       
void change_userBalance(UserLink* head1,TicketsLink* t)	;


/*     查询所有期彩票      */
void look_allPeriod(PeriodLink* head3);


/*         发行彩票          */
void issue_lottery(TicketsLink* head2,PeriodLink* head3);


/*        管理员查询彩民信息           */
void admin_seekUser(UserLink* head1);


/*      彩民账户排行      */
void bsort_account(UserLink* head1);


/*         保存用户信息         */
void save_information(UserLink* head1,TicketsLink* head2,PeriodLink* head3);


#endif

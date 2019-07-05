#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
	函数名: view1
	功能: 登录界面(主界面）
	参数: void
	返回值: void
*/
void view1(void)
{
	printf("\t----------------------------------------------------------\n");
	printf("\t\t欢迎来到3D福利彩票中心！\n");
	printf("\t\t~(*^__^*)\n\n");
	printf("\t\t  **********1.登录***********\n");
	printf("\t\t ***********2.注册************\n");
	printf("\t\t************0.退出*************\n");
	printf("\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("\t\t请选择您所需要的服务: ");
	printf("\n\t-----------------------------------------------------------\n");
} 


/*
	函数名: user_view1
	功能: 彩民界面
	参数: void
	返回值: void
*/
void user_view1(void)
{
	printf("\t----------------------------------------------------------\n");
	printf("\t\t尊敬的彩民,欢迎回来！\n");
	printf("\t\t~(*^__^*)~\n");
	printf("\t\t********1.查看历史记录***********\n");
	printf("\t\t********2.查看个人信息**********\n");
	printf("\t\t********3.修改密码*************\n");
	printf("\t\t********4.账户充值************\n");
	printf("\t\t********5.下注***************\n");
	printf("\t\t********6.注销**************\n");
	printf("\t\t********0.返回上一级********\n");
	//printf("\t\t********\033[1m\033[31m0.返回上一级\033[0m*******\n");
	printf("\t\t\033[1m\033[36m(周更新)8.\033[31m富\033[33m贵\033[32m在\033[34m天\033[36m(限时活动)\033[0m\n");
	printf("\033[1m");
	printf("\t\t  \033[32m<\033[31m<\033[34m<\033[35m<\033[33mVIP专属通道\033[35m>\033[34m>\033[31m>\033[32m>\033[0m\n");
	printf("\033[1m");
	printf("\t\t    \033[32m<\033[33m<\033[34m<\033[35m<\033[36m7.Game\033[32m>\033[33m>\033[34m>>\033[35m\033[0m\n");
	printf("\t\t请选择您所需要的服务: ");
	printf("\n\t-----------------------------------------------------------\n");
}


/*
	函数名: notary_view1
	功能: 公证员界面
	参数: void
	返回值: void
*/
void notary_view1(void)
{
	printf("\t----------------------------------------------------------\n");
	printf("\t\t尊敬的公证员,欢迎回来！\n");
	printf("\t\t~(*^__^*)~\n");
	printf("\t\t********1.发布开奖***********\n");
	printf("\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("\t\t********2.查看所有期彩票信息******\n");
	printf("\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("\t\t********0.返回上一级**********\n");
	printf("\t\t请选择您所需要的服务: ");
	printf("\n\t-----------------------------------------------------------\n");
}


/*
	函数名: admin_view1
	功能: 管理员界面
	参数: void
	返回值: void
*/
void admin_view1(void)
{
	printf("\t----------------------------------------------------------\n");
	printf("\t\t可爱的管理员,又回来了呢~\n");
	printf("\t\t这次，我能为你做些什么呢？....\n");
	printf("\t\t~(*^__^*)~ 嘻嘻……\n");
	printf("\t\t********1.发行彩票************\n");
	printf("\t\t********2.查询彩民信息*********\n");
	printf("\t\t********3.账户余额排行**********\n");
	printf("\t\t********4.彩民,彩票信息保存******\n");
	//printf("\t\t********5.查看盈利额*************\n");
	printf("\t\t********0.返回上一级*************\n");
	printf("\t\t请选择您所需要的服务: ");
	printf("\n\t-----------------------------------------------------------\n");
}


//温馨提示
void friendlyTips(void)
{
	printf("温馨提示:彩票单价为2,充值金额尽量为2的倍数的正整数哦～\n");
	printf("如果输入非整数金额,小于0.01的部分我们就拿去做公益啦～\n\n");
}


//按回车继续函数
void getPressBack(void)
{
	printf("返回请按回车键>>>>>>>>>>>>>>");
	getchar();
}


//返回主函数结束动画
void endView(void)
{
	system("sl -F");
	system("clear");
	system(" toilet -F gay thank you \\  see you");
	sleep(2);
	system("clear");
}


//7777777小游戏开场动画
void gameView(void)
{
	system("cmatrix -b");   //  q 终止 数码雨
	system("sl") ; 
	system("clear");
	system("toilet -f mono12 -F gay WELCOME POP QUIZ ");
	sleep(2);  
	//system("./hello");
}


//snake 过场动画
void snakeView(void)
{
	system("clear");
	system("toilet -f mono12 -F gay What a \\ nice guy");
	sleep(2);
	system("clear");
	//system("./snake");
	system("toilet -f mono12 -F gay What a \\ nice gay");
	sleep(2);
	system("clear");
}

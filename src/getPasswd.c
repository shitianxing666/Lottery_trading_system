#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  

# include<termios.h>  
# include<assert.h>  
int getch(void)  
{  
		int c=0;  
		struct termios org_opts, new_opts;  
		int res=0;  

		res=tcgetattr(STDIN_FILENO, &org_opts);  
		assert(res==0);  
		memcpy(&new_opts, &org_opts, sizeof(new_opts));  
		new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT     | ECHOKE | ICRNL);  
		tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);  
		c=getchar();  
		res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);  
		assert(res==0);  
		return c;  
}  

void getPassword(char *pcPWD)
{
		int ch=0;

		int i=0;

		for(i=0;i<20;)
		{
				ch=getch();
				if(ch==-1)//当无键入时，跳出当前循环继续下一个循环
				{
						continue;
				}
				//127在键盘上是delete  8代表退格键backspace
				if((ch == 127 || ch == 8) && i>0)//当有键入时，按键delete或backspace时，删除一位
				{
						putchar('\b');	//这里是删除一个，通过输出回撤符 /b，回撤一格，
						putchar(' ');	//再显示空格符把刚才的*给盖住，
						putchar('\b');	//然后再 回撤一格等待录入。
						i--;			//减少一位
				}
				//10在键盘上代表换行(LF)，13代表回车(CR)
				//3.在不同平台，输入回车，getch()将返回不同数值，而getchar()统一返回10(即\n)
				//1)windows平台下ENTER键会产生两个转义字符 \r\n，因此getch返回13(\r)。
				//2)unix、 linux系统中ENTER键只产生 \n ，因此getch返回10(\n)。
				//3)MAC OS中ENTER键将产生 \r ，因此getch返回13(\r)。
				else if(ch==10 || ch == 13)//当键入的为换行时
				{
						pcPWD[i]='\0';//将字符串以'\0'结尾
						putchar('\n');
						return;
				}
				else if(i==0&&(ch==127 ||ch == 8))//当无键入时，按键delete或backspace时，产生警报
				{
						printf("\a");
				}
				else if(i<19)//当键入的数少于19位时每键入一个数打印一个星号覆盖
				{
						pcPWD[i]=(char)ch;
						putchar('*');
						i++;
				}
				else//当键入的数超过19位时，再次键入产生响铃
				{
						printf("\a");//响铃
				}
		}
}


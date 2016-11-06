#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

/*定义clrscr清屏语句*/
#define Clear() system("cls")
/*color常量定义*/
#define black 0
#define blue 1
#define green 2
#define cyan 3
#define red 4
#define purple 5
#define yellow 6
#define white 7
#define Hblack 8/*加上前缀H代表亮度稍高*/
#define Hblue 9
#define Hgreen 10
#define Hcyan 11
#define Hred 12
#define Hpurple 13
#define Hyellow 14
#define Hwhite 15

#define Linux2Windows(x) (x)
#define Windows2Linux(x) (x)
#define on_(x,y) (x+16*y)
#define COLOR_ERROR -32767
/*附加:暂停程序*/
#define pause() system("pause")
#define pause2 () system("pause>nul")
/*保存程序字体颜色,初始值为白色*/
WORD TcColor=white,TbColor=black;
/*gotoxy,wherex,wherey语句定义*/
void gotoxy(int x,int y)
{
	COORD c;
	c.X=x-1;
	c.Y=y-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}


int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&pBuffer);
	return (pBuffer.dwCursorPosition.X+1);
}


int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&pBuffer);
	return (pBuffer.dwCursorPosition.Y+1);
}

/*隐藏光标*/
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
/*显示光标*/
void UnHideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 25};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
/*改变颜色
color(WORD a,WORD b);字为颜色a,背景为颜色b
textcolor(WORD a);字为颜色a
textbackground(WORD b);背景为颜色b
返回常量COLOR_ERROR(该数字<0)表示数据非法,正常情况返回当前颜色(必定>0)
*/
int color(WORD a,WORD b)
{
	if ((a>15)||(b>15)) return COLOR_ERROR;
	WORD color_now=on_(a,b);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_now);
	TcColor=a;
	TbColor=b;
	return color_now;
}

int textcolor(WORD a)
{
	if (a>15) return COLOR_ERROR;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
	TcColor=a;
	return on_(a,TbColor);
}

int textbackground(WORD b)
{
	if (b>15) return COLOR_ERROR;
	int color_now=on_(TcColor,b);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_now);
	TbColor=b;
	return color_now;
}

double random_()
{
	return (double)rand()/RAND_MAX;
}

int random(int m)
{
	return (int)(random_()*(m-1)+0.5);
}

double pro_time()
{
	return (double)clock()/CLOCKS_PER_SEC;
}

int readkey(double _time__)
{
	double time_last=pro_time();
	while (!kbhit()&&(pro_time()-time_last<_time__))  ;
	if (!kbhit()) return 0;
	while (pro_time()-time_last<_time__)  ;
	int return_=getch();
	return (return_==224)?getch():return_;
}

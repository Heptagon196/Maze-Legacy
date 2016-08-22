#include "Heads.h"

int Map[41][21][6][1];
int locax,locay,locaz;

int LoadMap();
int Event();
int Refresh();

int main()
{
	HideCursor();
	char a;
	int b;
	LoadMap();
	Refresh();
	int mark;
	int backupx,backupy,backupz;
	while (1)
	{
		backupx=locax;
		backupy=locay;
		backupz=locaz;
		mark=0;
		b=getch();
		if (b=='w')
			locay=(locay==1)?1:locay-(mark=1);
		if (b=='s')
			locay=(locay==20)?20:locay+(mark=1);
		if (b=='a')
			locax=(locax==1)?1:locax-(mark=1);
		if (b=='d')
			locax=(locax==40)?40:locax+(mark=1);
		if (!mark)
			continue;
		if (Map[locax][locay][locaz][0]==1)
		{
			locax=backupx;
			locay=backupy;
			continue;
		}
		if (Map[locax][locay][locaz][0]==2)
			locaz=Map[locax][locay][locaz][1];
		if (Map[locax][locay][locaz][0]==3)
		{
			Event();
			return 0;
		}
		Refresh();
		gotoxy(17,1);
		color(Hyellow,Hwhite);
	}
}

/*初始化*/
int LoadMap()
{
	FILE * fp;
	locax=1;
	locay=1;
	locaz=1;
	char DefaultMap[255];
	char DefaultMap2[255];
	fp=fopen("Settings\\Settings.txt","r");
	fscanf(fp,"DefaultMap=%s\n",DefaultMap2);
	fclose(fp);
	gotoxy(7,4);
	color(Hblue,Hwhite);
	puts("★");
	sprintf(DefaultMap,"%s\\Main.DMap",DefaultMap2);
	fp=fopen(DefaultMap,"r");
	int x,y,z,w,d,i,j;
	fscanf(fp,"%d\n",&w);
	for (j=1;j<=w;j++)
	{
		fscanf(fp,"%d\n",&d);
		for (i=1;i<=d;i++)
		{
			fscanf(fp,"%d %d %d\n",&x,&y,&z);
			Map[x][y][j][0]=1;
			Map[x][y][j][1]=z;
		}
		fscanf(fp,"%d\n",&d);
		for (i=1;i<=d;i++)
		{
			fscanf(fp,"%d %d %d\n",&x,&y,&z);
			Map[x][y][j][0]=2;
			Map[x][y][j][1]=z;
		}
		fscanf(fp,"%d\n",&d);
		for (i=1;i<=d;i++)
		{
			fscanf(fp,"%d %d %d\n",&x,&y,&z);
			Map[x][y][j][0]=3;
			Map[x][y][j][1]=z;
		}
	}
	//fclose(fp);
	//fp=fopen("Debug_Map.log","w");
	//for (y=1;y<=20;y++)
	//{
	//	for (x=1;x<=40;x++)
	//		fprintf(fp,"%d ",Map[x][y][1][0]);
	//	fprintf(fp,"\n");
	//}
	fclose(fp);
	return 0;
}

int Event()
{
	system("clear");
	printf("你走出了迷宫。");
	getch();
	return 0;
}

int Refresh()
{
	int x,y;
	for (x=locax-3;x<=locax+3;x++)
	for (y=locay-3;y<=locay+3;y++)
	{
		if ((x-locax==0)&&(y-locay==0))
			continue;
		gotoxy((x-locax+4)*2-1,y-locay+4);
		if ((x<1)||(x>40)||(y<1)||(y>20))
		{
			color(Hwhite,Hblue);
			puts("  ");
		}
		else
		if (Map[x][y][locaz][0]==1)
		{
			color(Hwhite,Map[x][y][locaz][1]);
			puts("  ");
		}
		else
		if (Map[x][y][locaz][0]==2)
		{
			color(Hred,Hwhite);
			puts("〓");
		}
		else
		if (Map[x][y][locaz][0]==3)
		{
			color(Map[x][y][locaz][1],Hwhite);
			puts("●");
		}
		else
		{
			color(Hwhite,Hwhite);
			puts("  ");
		}
	}
	return 0;
}


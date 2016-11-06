#include "Heads.h"

int Map[41][21][6][1];
int locax,locay,locaz;

int LoadMap();
int WriteMap();
int PutMap(int x,int y,int z);

int main()
{
	HideCursor();
	LoadMap();
	int a;
	gotoxy(79,20);
	color(11,Hwhite);
	puts("●");
	PutMap(locax,locay,1);
	while (1)
	{
		a=getch();
		PutMap(locax,locay,0);
		if (a=='q') break;
		if (a=='w') locay--;
		if (a=='s') locay++;
		if (a=='a') locax--;
		if (a=='d') locax++;
		if (locay<1) locay=20;
		if (locay>20) locay=1;
		if (locax<1) locax=40;
		if (locax>40) locax=1;
		PutMap(locax,locay,1);
		if (a=='1')
		{
			Map[locax][locay][1][0]=1;
			Map[locax][locay][1][1]=Windows2Linux(14);
		}
		if (a=='0')
		{
			Map[locax][locay][1][0]=0;
			Map[locax][locay][1][1]=0;
		}
	}
	WriteMap();
	return 0;
}

int LoadMap()
{
	FILE * fp;
	locax=1;
	locay=1;
	locaz=1;
	char DefaultMap[255];
	char DefaultMap2[255];
	fp=fopen("Settings/Settings.txt","r");
	fscanf(fp,"DefaultMap=%s\n",DefaultMap2);
	fclose(fp);
	sprintf(DefaultMap,"%s/Main.DMap",DefaultMap2);
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
			Map[x][y][j][1]=Windows2Linux(z);
		}
		fscanf(fp,"%d\n",&d);
		for (i=1;i<=d;i++)
		{
			fscanf(fp,"%d %d %d\n",&x,&y,&z);
			Map[x][y][j][0]=2;
			Map[x][y][j][1]=Windows2Linux(z);
		}
		fscanf(fp,"%d\n",&d);
		for (i=1;i<=d;i++)
		{
			fscanf(fp,"%d %d %d\n",&x,&y,&z);
			Map[x][y][j][0]=3;
			Map[x][y][j][1]=Windows2Linux(z);
		}
	}
	for (i=1;i<=40;i++)
	for (j=1;j<=20;j++)
	{
		gotoxy(i*2-1,j);
		color(Hwhite,Map[i][j][1][1]);
		puts("  ");
	}
	fclose(fp);

	return 0;

}

int WriteMap()
{
	FILE * fp;
	locax=1;
	locay=1;
	locaz=1;
	char DefaultMap[255];
	char DefaultMap2[255];
	fp=fopen("Settings/Settings.txt","r");
	fscanf(fp,"DefaultMap=%s\n",DefaultMap2);
	fclose(fp);
	sprintf(DefaultMap,"%s/Main_New.DMap",DefaultMap2);
	fp=fopen(DefaultMap,"w");
	int x,y,z,w,d,i,j;
	fprintf(fp,"1\n");
	w=0;
	for (i=1;i<=40;i++)
	for (j=1;j<=20;j++)
		if (Map[i][j][1][0]==1) w++;
	fprintf(fp,"%d\n",w);
	for (i=1;i<=40;i++)
	for (j=1;j<=20;j++)
		if (Map[i][j][1][0]==1)
			fprintf(fp,"%d %d %d\n",i,j,Linux2Windows(Map[i][j][1][1]));
	fprintf(fp,"0\n1\n40 20 12\n");
	fclose(fp);

	return 0;

}

int PutMap(int x,int y,int z)
{
	color(Hwhite,z==1?(Map[x][y][1][0]==1?1:Windows2Linux(11)):Map[x][y][1][1]);
	if ((x==40)&&(y==20))
		return 0;
	gotoxy(x*2-1,y);
	puts("  ");
	return 0;
}

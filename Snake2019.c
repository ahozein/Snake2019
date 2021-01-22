#include <stdio.h>
#include <conio.h>                     //Developed by AmirHossein Darroudi
#include <time.h>
#include <Windows.h>

//------------------------Global variable
char table[12][35];
int items[10000][2],front=0,rear=-1;
int score=0,dir=0,food=0,lenght=160;
int x=6,y=17,endx,endy;
//------------------------------First set
void set()
{
    for(int i=0 ; i<12 ; i++)
        for(int j=0 ; j<35 ; j++)
            table[i][j]='.';
    table[7][11]='*';
    table[7][12]='*';

    for(int i=0 ;i<10 ; i++)//-------Gharar dadane divarha
    {
        int ROW=clock()%12;
        int COL=clock()%35;
        table[ROW][COL]='#';
        Sleep(100);
    }
}
//--------------------------Goto xy
void gotoxy(int x, int y)
{
     HANDLE hConsoleOutput;
     COORD dwCursorPosition;
     dwCursorPosition.X=x+1;
     dwCursorPosition.Y=y+1;
     hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
//------------Hold
void hold()
{
    char c;
    if(kbhit())
    {
        c=getch();
        if(c=='w')
            dir=1;
        else if(c=='s')
            dir=3;
        else if(c=='a')
            dir=2;
        else if(c=='d')
            dir=0;
    }
}
//------------Reward
void reward()
{
    while(1)                                                          //Developed by AmirHossein Darroudi
    {
        srand(time(0));
        unsigned int n=clock()%12;
        unsigned int m=clock()%35;
        if(table[n][m]=='.')
        {
            table[n][m]='o';
            gotoxy(m,n);
            printf("o");
            break;
        }
    }
}

void Add_To_Array(int x,int y)
{
    rear++;
    items[rear][0]=x;
    items[rear][1]=y;
}
//-------------------------Print
void print()
{
    system("cls");
    printf("\n");
    for(int i=0; i<12 ;i++)
    {
        printf(" ");
        for(int j=0; j<35 ; j++)
            printf("%c",table[i][j]);
        printf("\n");
    }
}
//-----------------------Remove
void removee(int a,int b)
{
    table[a][b]='.';
    gotoxy(b,a);
    printf(".");
}
//----------------------Setting
void setting()
{
    int c;
    system("cls");
    printf("Difficultly:\n1)Very Hard\n2)Hard\n3)Normal\n4)Easy\n5)Very Easy\n\t\tSo Please Enter Number to Choose Difficultly: "); //Developed by AmirHossein Darroudi
    scanf("%d",&c);
    lenght=50*c;
}
//-----------------------Add
void add(int a,int b)
{
    if(a>11)
            a=0;
    if(a<0)
            a=11;
    if(b>34)
            b=0;
    if(b<0)
            b=34;
    x=a;
    y=b;
    Add_To_Array(a,b);
    if(table[a][b]!='*' && table[a][b]!='#')
    {
        if(table[a][b]=='o')
        {
            printf("\a");
            food++;
            if(food==10) //-------New Level
            {
                printf("\a");
                lenght-=50;
                food=0;
                int ROW=clock()%12;
                int COL=clock()%35;
                table[ROW][COL]='#';
            }
            score+=10;
            reward();
            table[a][b]='*';                            //Developed by AmirHossein Darroudi
            gotoxy(b,a);
            printf("*");
            return;
        }
        table[a][b]='*';
        gotoxy(b,a);
        printf("*");

        endx=items[front][0];
        endy=items[front][1];
        front++;
        removee(endx,endy);
    }
    else
    {
        printf("\a");
        system("cls");
printf("\n\n*#*#*#*#*#*#*#*#*#* Your score Is: %d *#*#*#*#*#*#*#*#*#**#*#*\n\tPlease Enter any key to Exit From The Game...\n\t\t\tDeveloped by\n\t\t   Amir Hossein Darroudi\n",score);
        getch();
        exit(1);
    }
}
//-----------------------Action
void action()
{
    if(dir==0)
        add(x,++y);
    else if(dir==1)
        add(--x,y);
    else if(dir==2)
        add(x,--y);
    else if(dir==3)
        add(++x,y);
}
//-----------------------Main
int main()
{
    char MENU;
    while(1)
    {
        system("cls");
        printf("\n                 \\_________________  1)Start Game __________________/");
        printf("\n                  \\________________  2)Settings   ___________________/");            //Developed by AmirHossein Darroudi
        printf("\n                   \\_______________  3)Exit Game  _________________/");
        MENU=getch();
        if(MENU=='1')
            break;
        else if(MENU=='2')
                setting();
        else if(MENU=='3')
            exit(0);
    }
    //-------------------Start Of Game:
    Add_To_Array(7,11);
    Add_To_Array(7,12);
    set();
    reward();
    print();
    while(1)
    {
        Sleep(lenght);
        hold();
        action();
    }
}

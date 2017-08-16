#include "makearray.h"
#include "judgecolor.h"
#include "queue"
#include "cmath"
using namespace std;

struct Point
{
    int x;
    int y;
};

/*
void OutputData(unsigned NumLine)
{
    for(unsigned i=1; i<=NumLine; i++)
    {
        printf("- frame: [%d, %d, %d, %d]\n", Line[i].y, Line[i].x, Line[i].w, Line[i].h);
        printf("  keys:\n");
        for(unsigned j=1; j<=Line[i].num; j++)
        {
            printf("    - frame: [%d, %d, %d, %d]\n", Keyboard[i][j].y, Keyboard[i][j].x, Keyboard[i][j].width, Keyboard[i][j].height);
        }
    }
}
*/

void OutputData(unsigned NumLine, int startheight)
{
    printf("%d ", NumLine*2+1);
    for(unsigned i=1; i<=NumLine; i++)
    {
        printf("%d %d ", Line[i].x - Line[i-1].x - Line[i-1].h + 1, Line[i].h);
    }
    printf("%d ", Height - Line[NumLine].x - Line[NumLine].h - startheight + 1);
    for(unsigned i=1; i<=NumLine; i++)
    {
        printf("1 %d ", Line[i].num * 2 + 1);
    }
    printf("1\n");
    for(unsigned i=1; i<=NumLine; i++)
    {
        printf("%d S\n", Width);
        for(unsigned j=1; j<=Line[i].num; j++)
        {
            printf("%d S %d %c ", Keyboard[i][j].y - Keyboard[i][j-1].y - Keyboard[i][j-1].width, Keyboard[i][j].width, RGBToColor(Keyboard[i][j]));
        }
        printf("%d S\n", Width - Keyboard[i][Line[i].num].y - Keyboard[i][Line[i].num].width + 1);
    }
    printf("%d S\n", Width);
}


const int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int IsFind[2000][2000] = {0};
int miny, maxy, minx, maxx;
void FindKey(Point ini)
{
    miny = 100000000;
    maxy = -100000000;
    minx = 100000000;
    maxx = -100000000;
    queue <Point> Key;
    Key.push(ini);
    IsFind[ini.x][ini.y] = 1;
    int tmpr = pixel[ini.x][ini.y].r;
    int tmpg = pixel[ini.x][ini.y].g;
    int tmpb = pixel[ini.x][ini.y].b;
    while(!Key.empty())
    {
        Point Front = Key.front();
        Key.pop();
        for(int i=0; i<4; i++)
        {
            Point tmp;
            tmp.x = Front.x + dx[i];
            tmp.y = Front.y + dy[i];
            if(!IsFind[tmp.x][tmp.y] && abs(pixel[tmp.x][tmp.y].r - tmpr) <= 20 && abs(pixel[tmp.x][tmp.y].g - tmpg) <= 20 && abs(pixel[tmp.x][tmp.y].b - tmpb) <= 20 && tmp.x >= 0 && tmp.x < Height && tmp.y >=0 && tmp.y <Width)
            {
                Key.push(tmp);
                IsFind[tmp.x][tmp.y] = 1;
                if(tmp.x > maxx)
                    maxx = tmp.x;
                if(tmp.x < minx)
                    minx = tmp.x;
                if(tmp.y > maxy)
                    maxy = tmp.y;
                if(tmp.y < miny)
                    miny = tmp.y;
            }
        }

    }
}//ok

void init()
{
    memset(IsFind,0,sizeof(IsFind));
}

void EnterToKeyboard(unsigned i, unsigned j)
{
    for(; i<=Height && !IsLightGrey(i, 1); i++);//走入键盘灰色区
    int startheight = i;
    for(; i<=Height && (!IsWhite(i, j) && !IsDarkGrey(i, j) && !IsBlue(i, j)); i++)
            for(j=1; j<=Width && (!IsWhite(i, j) && !IsDarkGrey(i, j) && !IsBlue(i, j)); j++);//走入第一个白键
    unsigned NowLine = 1, NowElement = 1;
    while(i<=Height)
    {
        for(; i<=Height && (!IsWhite(i, j) && !IsDarkGrey(i, j) && !IsBlue(i, j)); i++)
            for(j=1; j<=Width && (!IsWhite(i, j) && !IsDarkGrey(i, j) && !IsBlue(i, j)); j++);
        Line[NowLine].x = i;
        Line[NowLine].y = j;
        while(j<=Width)
        {
            Point ini;
            ini.x = i;
            ini.y = j;
            FindKey(ini);
            if(minx < Line[NowLine].x)
                Line[NowLine].x = minx;
            if(miny < Line[NowLine].y)
                Line[NowLine].y = miny;
            Keyboard[NowLine][NowElement].height = maxx - minx;
            Keyboard[NowLine][NowElement].width = maxy - miny;
            Keyboard[NowLine][NowElement].x = minx;
            Keyboard[NowLine][NowElement].y = miny;
            Keyboard[NowLine][NowElement].rgb[1] = pixel[ini.x][ini.y].r;
            Keyboard[NowLine][NowElement].rgb[2] = pixel[ini.x][ini.y].g;
            Keyboard[NowLine][NowElement].rgb[3] = pixel[ini.x][ini.y].b;
            NowElement ++;
            j = j + maxy - miny + 1;
            for(; j<=Width && (!IsWhite(i, j) && !IsDarkGrey(i, j) && !IsBlue(i, j)); j++);
        }
        Line[NowLine].x = Line[NowLine].x - startheight;
        Line[NowLine].num = NowElement - 1;
        Line[NowLine].h = Keyboard[NowLine][NowElement-1].height;
        Line[NowLine].w = Keyboard[NowLine][NowElement-1].y - Keyboard[NowLine][1].y;
        NowElement = 1;
        i = i + maxx - minx + 1;
        NowLine ++;
    }
    unsigned NumLine = NowLine - 2;
    OutputData(NumLine, startheight);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//#include <windows.h>

#define width 65
#define height 25

typedef struct {
    int x, y;
    int w;
} TRacket;

char mas[height][width+1];
TRacket racket;

void initRacket()
{
    racket.w = 7;
    racket.x = (width - racket.w) / 2;
    racket.y = height - 1;
}

void putRacket()
{
    for(int i = racket.x; i < racket.x + racket.w; i++)
        mas[racket.y][i] = '@';
}

void init()
{
    for(int i = 0; i < width; i++)
        mas[0][i] = '#';
    mas[0][width] = '\0';

    strncpy(mas[1], mas[0], width+1);
    for(int i = 1; i < width - 1; i++)
        mas[1][i] = ' ';

    for(int i = 1; i < height; i++)
        strncpy(mas[i], mas[1], width+1);
    //for(int i = 1; i < width; i++)
      //  mas[height-1][i] = '#';
}

void show()
{
    for(int i = 0; i < height; i++)
    printf("%s\n", mas[i]);
}

void moveRacket(int x)
{
    racket.x = x;
    if(racket.x < 1)
        racket.x = 1;
    if(racket.x + racket.w >= width)
        racket.x = width - 1 - racket.w;
}

int main()
{
    char c;
    initRacket();

    do
    {
        system("cls");
        init();
        putRacket();
        show();

        c = getch();
        if(GetKeyState) moveRacket(racket.x - 1);
        if(c == 'd') moveRacket(racket.x + 1);
    }
    while(c != 'q');

    return 0;
}

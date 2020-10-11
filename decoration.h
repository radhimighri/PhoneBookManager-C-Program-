#ifndef DECORATION_H_INCLUDED
#define DECORATION_H_INCLUDED

int cputss(const char *str) {
  return ((printf ("%s", str)==EOF)?EOF:(int)*(str+strlen(str)-1)) ;
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}


void afterload()
{

    int i;
    clrscr();
    draw_tel();
    gotoxy(50,10);
    for(i=0; i<8; i++)
    {
    cputss("********");Sleep(30);
    }
    for(i=10; i<21; i++)
    {
     gotoxy(113,i);
     cputs("*");Sleep(30);
    }
     for(i=107; i>50; i--)
    {
    gotoxy(i,21);
    cputss("*******");Sleep(20);
    }
    for(i=21; i>9; i--)
    {
     gotoxy(50,i);
     cputs("*");Sleep(30);
    }

}


void afterloaddirect()
{
    int i;
    clrscr();
    draw_tel();
    gotoxy(50,10);
    for(i=0; i<8; i++)
    {
    cputss("********");
    }
    for(i=10; i<21; i++)
    {
     gotoxy(113,i);
     cputs("*");
    }
     for(i=107; i>50; i--)
    {
    gotoxy(i,21);
    cputss("*******");
    }
    for(i=21; i>9; i--)
    {
     gotoxy(50,i);
     cputs("*");
    }

}

void saving()
{
    int i,j;
    gotoxy(65,18);
    system("color 0a");
    printf("%c%c Enregistrement en cours... %c%c",218,217,218,217);
    gotoxy(68,19);
    Sleep(1000);
    for(i=0; i<=26;i++)
    {
        for(j=0;j<=1000;j++);
        Sleep(200);
        printf("%c",177);
    }

}


void cadre_saisie()
{
    clrscr();
    afterload();
}


void draw_tel()
{
    int i;
    clrscr();
    gotoxy(2,5);
    for(i=0; i<9; i++)
    {
    cputss("**");
    }


    for(i=5; i<20; i++)
    {
     gotoxy(19,i);
     cputs("*");
    }

     for(i=18; i>1; i--)
    {
    gotoxy(i,20);
    cputss("**");
    }
    for(i=20; i>5; i--)
    {
     gotoxy(2,i);
     cputs("*");
    }



    gotoxy(2,14);
    for(i=0; i<9; i++)
    {
    cputss("**");
    }

    gotoxy(2,16);
    for(i=0; i<9; i++)
    {
    cputss("**");
    }

    gotoxy(2,18);
    for(i=0; i<9; i++)
    {
    cputss("**");
    }
//////////////


    for(i=14; i<20; i++)
    {
     gotoxy(7,i);
     cputs("*");
    }

     for(i=14; i<20; i++)
    {
     gotoxy(13,i);
     cputs("*");
    }

//////////////////

gotoxy(4,15);printf("1");
gotoxy(4,17);printf("2");
gotoxy(4,19);printf("3");

gotoxy(10,15);printf("4");
gotoxy(10,17);printf("5");
gotoxy(10,19);printf("6");

gotoxy(16,15);printf("7");
gotoxy(16,17);printf("8");
gotoxy(16,19);printf("9");

textcolor(GREEN);
gotoxy(6,8);printf("*");
gotoxy(6,9);printf("*");
gotoxy(6,10);printf("*");gotoxy(7,10);printf("*");gotoxy(8,10);printf("*");gotoxy(9,10);printf("*");
gotoxy(6,11);printf("*");
gotoxy(6,12);printf("*");

gotoxy(9,8);printf("*");
gotoxy(9,9);printf("*");
gotoxy(9,10);printf("*");
gotoxy(9,11);printf("*");
gotoxy(9,12);printf("*");


gotoxy(12,8);printf("*");
gotoxy(13,8);printf("*");
gotoxy(14,8);printf("*");
gotoxy(13,9);printf("*");
gotoxy(13,10);printf("*");
gotoxy(13,11);printf("*");
gotoxy(12,12);printf("*");
gotoxy(13,12);printf("*");
gotoxy(14,12);printf("*");
textcolor(WHITE);
}
#endif // DECORATION_H_INCLUDED

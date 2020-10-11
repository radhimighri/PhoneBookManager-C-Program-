#ifndef CONTROL_SAISIE_H_INCLUDED
#define CONTROL_SAISIE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

int test_num_premier_chiffre(char ch[20])
{
    int ok=0;

    if (ch[0]=='9' || ch[0]=='5' || ch[0]=='2')
        ok=1;
    else
       {
            gotoxy(52,21);
            printf("                                                                               ");
            gotoxy(52,21);
            textcolor(RED);
            printf("ERREUR: Le num%cro doit commencer par '5: Orange' ou '9: TT' ou '2: Ooredoo'\n",130);
            textcolor(WHITE);
       }

    return ok;
}

int test_maj (char ch[20])
{
    int ok =0,i;
    if (isupper(ch[0])==1)
    {
    ok=1;
    for (i=1;ch[i];i++)
      {
        if ( islower(ch[i])==1)
            {
            ok=0;
            gotoxy(52,22);
            printf("                                                                               ");
            gotoxy(52,22);
            textcolor(RED);
            printf("ERREUR: Le mot ne doit pas contenir deux lettre en majuscule!\n");
            textcolor(WHITE);
            break;
            }
          if ( isupper(ch[i])==1 )
            {
            ok=0;
            gotoxy(52,22);
            printf("                                                                               ");
            gotoxy(52,22);
            textcolor(RED);
            printf("ERREUR: Le mot ne doit pas contenir deux lettre en majuscule!\n");
            textcolor(WHITE);
            break;
            }
      }


    }else
    {
        gotoxy(52,22);
        printf("                                                                               ");
        gotoxy(52,22);
        textcolor(RED);
        printf("ERREUR: La premiere lettre doit etre Majuscule.\n");
        textcolor(WHITE);
    }

    return ok;
}



int test_nom_prenom(char ch[])
{
    int i,ok=0;
    for (i = 1; ch[i] != '\0'; ++i)
        if (ch[i]=='a'|| ch[i]=='b'|| ch[i]=='c'|| ch[i]=='d'|| ch[i]=='e'|| ch[i]=='f'|| ch[i]=='g'|| ch[i]=='h'|| ch[i]=='i'|| ch[i]=='j'|| ch[i]=='k'|| ch[i]=='l'|| ch[i]=='m'|| ch[i]=='n'|| ch[i]=='o'|| ch[i]=='p'|| ch[i]=='q'|| ch[i]=='r'|| ch[i]=='s'|| ch[i]=='t'|| ch[i]=='u'|| ch[i]=='v'|| ch[i]=='w'|| ch[i]=='x'|| ch[i]=='y'|| ch[i]=='z' || ch[i]==' ' && ch[i+1]!=' ' && ch[strlen(ch)-1]!=' ' )
            ok=1;
        else
        {
            gotoxy(52,22);
            printf("                                                                               ");
            gotoxy(52,22);
            textcolor(RED);
            printf("ERREUR: Le nom/prenom doit contenir une suite de lettre avec un seul espace!\n");
            textcolor(WHITE);
            ok=0;
            break;
        }
    return ok;
}

int testmail(char ch[])
{
    int i,ok=0;
    for (i = 1; ch[i] != '\0'; ++i)
        if (ch[i]=='a'|| ch[i]=='b'|| ch[i]=='c'|| ch[i]=='d'|| ch[i]=='e'|| ch[i]=='f'|| ch[i]=='g'|| ch[i]=='h'|| ch[i]=='i'|| ch[i]=='j'|| ch[i]=='k'|| ch[i]=='l'|| ch[i]=='m'|| ch[i]=='n'|| ch[i]=='o'|| ch[i]=='p'|| ch[i]=='q'|| ch[i]=='r'|| ch[i]=='s'|| ch[i]=='t'|| ch[i]=='u'|| ch[i]=='v'|| ch[i]=='w'|| ch[i]=='x'|| ch[i]=='y'|| ch[i]=='z' || ch[i]=='1' || ch[i]=='2' || ch[i]=='3' || ch[i]=='4'|| ch[i]=='5'|| ch[i]=='6'|| ch[i]=='7'|| ch[i]=='8'|| ch[i]=='9' || ch[i]=='@' || ch[i]=='.' ||ch[i]==' ' && ch[i+1]!=' ' && ch[strlen(ch)-1]!=' ' )
            ok=1;
        else
        {
            gotoxy(52,22);
            printf("                                                                               ");
            gotoxy(52,22);
            textcolor(RED);
            printf("ERREUR: Le mail ne doit pas contenir des caractères spéciaux!\n");
            textcolor(WHITE);
            ok=0;
            break;
        }
    return ok;
}

int test_numero (char ch[])
{
    int ok =0,i=0;

    do {
        if (isdigit(ch[i])==0){
            ok++;
            break;
        }
        else i++;
      }while(i<strlen(ch));

    return ok;
}

int test_longeur (char ch[])
{
    int ok =1;
        if (strlen(ch)<=2)
            {
            gotoxy(64,22);
            textcolor(RED);
            printf("\nERREUR: Le nom/prenom doit contenir plus que 2 caracteres!");
            textcolor(WHITE);
            ok=0;
            }
    return ok;
}


int test_postal (char ch[])
{
    int ok =0,i=0;

    do {
        if (isdigit(ch[i])==0){
            gotoxy(52,22);
            printf("                                                                               ");
            gotoxy(52,22);
            textcolor(RED);
            printf("ERREUR: le code postal doit etre une suite de chiffre(MAX:4)! ");
            textcolor(WHITE);
            ok++;
            break;
        }
        else
            {
            i++;
            }

      }while(i<strlen(ch));

    return ok;
}


int test_postal2 (char ch[])
{
    int ok =0,i=0;

    do {
        if (isdigit(ch[i])==0){
            printf("ERREUR: le code postal doit etre une suite de chiffre(MAX:4)! \n");
            textcolor(WHITE);
            ok++;
            break;
        }
        else
            {
            i++;
            }

      }while(i<strlen(ch));

    return ok;
}

int control_mail(char txt[])
{
    char* gmail="@gmail.com";
    char* yahoo="@yahoo.com";
    char* poly="@poly.tn";
    int i,j,k,test=0;
    do
    {
         gotoxy(52,16);
        printf("Donner un mail : ");
        scanf("%s",txt);
        gotoxy(69,16);
        printf("                               ");
        i=strstr(txt,gmail);
        j=strstr(txt,yahoo);
        k=strstr(txt,poly);
        if (i)
            test=1;

        if (j)
            test=1;


        if (k)
            test=1;

      if(test==0)
      {
           gotoxy(52,22);
           printf("                                                                               ");
           gotoxy(52,22);
           textcolor(RED);
           printf("ERREUR: le mail doit etre @gmail.com / @yahoo.com / @poly.tn!\n");
           textcolor(WHITE);
      }

    }while(test!=1 || testmail(txt)==0);
gotoxy(69,16);puts(txt);
return test;
}

#endif // CONTROL_SAISIE_H_INCLUDED

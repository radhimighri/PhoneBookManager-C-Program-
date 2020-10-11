
//MOT DE PASSE = hardpassword


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "resource.h"
#include <stdlib.h>


const char g_szClassName[] = "myWindowClass";

const int ID_TIMER = 1;

const int BALL_MOVE_DELTA = 1;

typedef struct _BALLINFO
{
	int width;
	int height;
	int x;
	int y;

	int dx;
	int dy;
}BALLINFO;

char buff[100];
char c_user[] = "hardpassword";
BALLINFO g_ballInfo;
HBITMAP g_hbmBall = NULL;
HBITMAP g_hbmMask = NULL;

HBITMAP hbmMask;
HDC hdcMem, hdcMem2;
HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent)
{


	BITMAP bm;

	GetObject(hbmColour, sizeof(BITMAP), &bm);
	hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	hdcMem = CreateCompatibleDC(0);
	hdcMem2 = CreateCompatibleDC(0);

	SelectObject(hdcMem, hbmColour);
	SelectObject(hdcMem2, hbmMask);

	SetBkColor(hdcMem, crTransparent);

	BitBlt(hdcMem2, 5000, NULL, bm.bmWidth, bm.bmHeight, hdcMem, NULL, NULL, SRCCOPY);

	BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);

	return hbmMask;
}

void DrawBall(HDC hdc, RECT* prc)
{
	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
	HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, g_hbmMask);

	FillRect(hdcBuffer, prc, GetStockObject(DKGRAY_BRUSH));

	BitBlt(hdcBuffer, g_ballInfo.x, g_ballInfo.y, g_ballInfo.width, g_ballInfo.height, hdcMem, 0, 0, SRCAND);

	SelectObject(hdcMem, g_hbmBall);
	BitBlt(hdcBuffer, g_ballInfo.x, g_ballInfo.y, g_ballInfo.width, g_ballInfo.height, hdcMem, 0, 0, SRCPAINT);

	BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
/***********************************************TEXT************************************************/

}

void UpdateBall(RECT* prc)
{
	g_ballInfo.x += g_ballInfo.dx;
	g_ballInfo.y += g_ballInfo.dy;

	if(g_ballInfo.x < 0)
	{
		g_ballInfo.x = 0;
		g_ballInfo.dx = BALL_MOVE_DELTA;
	}
	else if(g_ballInfo.x + g_ballInfo.width > prc->right)
	{
		g_ballInfo.x = prc->right - g_ballInfo.width;
		g_ballInfo.dx = -BALL_MOVE_DELTA;
	}

	if(g_ballInfo.y < 0)
	{
		g_ballInfo.y = 0;
		g_ballInfo.dy = BALL_MOVE_DELTA;
	}
	else if(g_ballInfo.y + g_ballInfo.height > prc->bottom)
	{
		g_ballInfo.y = prc->bottom - g_ballInfo.height;
		g_ballInfo.dy = -BALL_MOVE_DELTA;
	}
}
/**********************************************LES DIALOGS********************************************************************/
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:

		return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd, IDOK);

				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK DIALOGCARRE(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:

		return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd, IDOK);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}


BOOL CALLBACK LoginDiag(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
	{
		case WM_INITDIALOG:
        SendDlgItemMessage(hwnd,IDD_EDIT,EM_SETPASSWORDCHAR,(WPARAM) '*',(LPARAM) 0);
		return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
                    GetDlgItemText ( hwnd , IDD_EDIT , buff , 100 );

                    if (strcmp(buff, c_user) == 0)
                    EndDialog(hwnd, IDOK);
                    else
                    {
                    mciSendString("play music\\error.mp3", NULL, 0, hwnd);
                    MessageBox(hwnd, "Wrong Password, Please Enter Again.", "                              Incorrect Password", MB_OK | MB_ICONERROR);
                    }
				break;
				case IDCANCEL:
				    DestroyWindow(hwnd);
				    PostQuitMessage(0);
				    EndDialog(hwnd, IDCANCEL);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}
FILE* fichier = NULL;
/****************************************************************************************************************************/
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{

    BITMAP bm;
	switch(Message)
	{
	    //static HWND hButton;
	    case WM_CREATE:
		{
			UINT ret;
			g_hbmBall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BALL));
			if(g_hbmBall == NULL)
				MessageBox(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

			g_hbmMask = CreateBitmapMask(g_hbmBall, RGB(0, 0, 0));
			if(g_hbmMask == NULL)
				MessageBox(hwnd, "Could not create mask!", "Error", MB_OK | MB_ICONEXCLAMATION);

			GetObject(g_hbmBall, sizeof(bm), &bm);

			ZeroMemory(&g_ballInfo, sizeof(g_ballInfo));
			g_ballInfo.width = bm.bmWidth;
			g_ballInfo.height = bm.bmHeight;

			g_ballInfo.dx = BALL_MOVE_DELTA;
			g_ballInfo.dy = BALL_MOVE_DELTA;

			SetTimer(hwnd, ID_TIMER, 50,0);

		}
		break;

		case WM_KEYDOWN:
		     {
		         switch(wParam)
		         {
                case VK_F4:
                    {
                    int retour = MessageBox(hwnd,"Vous allez quitter le programme, êtes vous sûr?","ATTENTION!", MB_YESNO | MB_ICONWARNING);
                    if(retour==IDYES)
                        PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                    }
                case VK_DOWN:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                     break;

		         }
		     }

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_FILE_EXIT:
				    {
        int retour = MessageBox(hwnd,"Vous allez quitter le programme, êtes vous sûr?","ATTENTION!", MB_YESNO | MB_ICONWARNING);
         if(retour==IDYES)
         PostMessage(hwnd, WM_CLOSE, 0, 0);
				    }
				break;
/***************************************************LES EXERCICES****************************************************/
            /**MUSIC**/
                case IDD_BELIEVER:
                    mciSendString("play music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                    break;
                case IDD_NATURAL:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("play music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                    break;
                case IDD_GIRLS:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("play music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                    break;
                case IDD_DEATH:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("play music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                    break;
                case IDD_FIGHT:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("play music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                    break;
                case IDD_MARIE:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("play music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                    break;
                case IDD_REASON:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("play music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\oheh.mp3", NULL, 0, hwnd);
                    break;
                case IDD_DOCTOR:
                    mciSendString("stop music\\believer.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\death.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\fight.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\girls.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\marie.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\reason.mp3", NULL, 0, hwnd);
                    mciSendString("stop music\\natural.mp3", NULL, 0, hwnd);
                    mciSendString("play music\\oheh.mp3", NULL, 0, hwnd);
                    break;

                case CreationListe:

                    fichier = fopen("repertoire.txt", "r");
                    if( testSiFichierVide(fichier) == 1)
                    {
                        ShellExecute( hwnd,"open","Exercices\\Creation\\creation.exe",NULL,NULL,SW_SHOWMAXIMIZED);
                        break;
                    }
                else
                    {
                        DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_CREATION), hwnd, AboutDlgProc);
                        break;
                    }

/************************************************/
                case ajout_tete:
                ShellExecute( hwnd,"open","Exercices\\maj\\ajout_tel.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case ajout_queue:
                ShellExecute( hwnd,"open","Exercices\\maj\\ajout_queue.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case ajout_pos:
                ShellExecute( hwnd,"open","Exercices\\maj\\ajout_tel_pos.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;
/************************************************/


                case sup_tete:
                ShellExecute( hwnd,"open","Exercices\\sup\\sup_tete.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case sup_queue:
                ShellExecute( hwnd,"open","Exercices\\sup\\sup_queue.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case sup_pos:
                ShellExecute( hwnd,"open","Exercices\\sup\\sup_pos.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case sup_tel:
                ShellExecute( hwnd,"open","Exercices\\sup\\sup_tel_donnee.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case sup_ville:
                ShellExecute( hwnd,"open","Exercices\\sup\\sup_tel_ville.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case sup_indice:
                ShellExecute( hwnd,"open","Exercices\\sup\\sup_tel_ind.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case sup_liste:
                    {
                         int retour = MessageBox(hwnd,"Vous allez vider la liste, êtes vous sûr?","ATTENTION!", MB_YESNO | MB_ICONWARNING);
                if(retour==IDYES)
                {
                  ShellExecute( hwnd,"open","Exercices\\sup\\viderliste.exe",NULL,NULL,SW_SHOWMAXIMIZED);
                  break;
                }
                else if (retour=IDNO)
                    break;
                    }



/**************************************/

                case modif_adr:
                ShellExecute( hwnd,"open","Exercices\\modif\\modif_adr.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case modif_tel:
                ShellExecute( hwnd,"open","Exercices\\modif\\modif_tel.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

/**************************************/
                case affiche_liste:
                ShellExecute( hwnd,"open","Exercices\\recherche\\affiche.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case rech_num:
                ShellExecute( hwnd,"open","Exercices\\recherche\\rech_tel.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case rech_nom:
                ShellExecute( hwnd,"open","Exercices\\recherche\\rech_nom.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case rech_indice:
                ShellExecute( hwnd,"open","Exercices\\recherche\\rech_ind.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case rech_ville:
                ShellExecute( hwnd,"open","Exercices\\recherche\\rech_ville.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case tri_1:
                ShellExecute( hwnd,"open","Exercices\\recherche\\tri.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case tri_2:
                ShellExecute( hwnd,"open","Exercices\\recherche\\tri2.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

/************************************************/

                case enregistrer:
                ShellExecute( hwnd,"open","Exercices\\Enregistr\\enregistrer.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

                case charger:
                ShellExecute( hwnd,"open","Exercices\\Enregistr\\charger.exe",NULL,NULL,SW_SHOWMAXIMIZED);break;

/***************************************************LES EXERCICES****************************************************/
				case ID_HELP:
				{
                DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
				}
				break;
			}
		break;

/*****************************************************************************************************************************/
		case WM_PAINT:
		{
			RECT rcClient;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rcClient);
			DrawBall(hdc, &rcClient);
			EndPaint(hwnd, &ps);
		}
		break;

		case WM_TIMER:
		{
			RECT rcClient;
			HDC hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rcClient);
			UpdateBall(&rcClient);
			SetTextColor(hdc,RGB(255,0,0));
			DrawBall(hdc, &rcClient);
			ReleaseDC(hwnd, hdc);

		}
		break;
		/*****************************DESTROYING THE MOVING OBJECT *****************************/
		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			KillTimer(hwnd, ID_TIMER);
			DeleteObject(g_hbmBall);
			DeleteObject(g_hbmMask);
			PostQuitMessage(0);
		break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(""));
	wc.hCursor		 = LoadCursorFromFile("curseur.cur");
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = (HICON)LoadImage(NULL, "Icons/menu_two.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	SetCursor(wc.hCursor);
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		0,
		g_szClassName,
		"Mini-Projet-C-Programming",
		WS_POPUP|WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		HWND_DESKTOP, NULL, hInstance, NULL);
        SetWindowPos(hwnd, HWND_TOP, 0,  0, GetSystemMetrics(SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), NULL );


	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_LOGIN), hwnd, LoginDiag);
    mciSendString("play music\\opening.mp3", NULL, 0, hwnd);
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}


int testSiFichierVide(FILE* fichier)
{
    int caracterePremier = 0;

    //On lit le prmeier caractère du fichier
    caracterePremier = fgetc(fichier);
    if(caracterePremier==EOF)
    {
        return 1;//le fichier est vide donc on retourne 1
    }
    return 0;//le fichier n'est pas vide donc on retourne 0
}

/**
void addcontrols(hdc)
{
    TextOut(hdc, 0, 0, "test", strlen("test"));
}**/
/**
void loginadd(HWND hwnd)
{
    hEdit = CreateWindowW(L"Edit",L"...",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE,34, 33, 113, 17,hwnd,NULL,NULL,NULL);
}*/




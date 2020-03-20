// TicTacToe.cpp : Define el punto de entrada de la aplicación.
//

#include <Windows.h>
#include <windowsx.h>
#include "framework.h"
#include "TicTacToe.h"
#include "Board.h"
#include <list>
#include <vector>
#include <gdiplus.h>
#include "PowerUp.h"
#pragma comment (lib,"gdiplus.lib")
#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR GAME_NAME[] = L"PSEUDOCANDYCRUSH";                  // Texto de la barra de título
WCHAR MENU_CLASS_NAME[] = L"Menu";
WCHAR GAME_CLASS_NAME[] = L"PSEUDOCANDYCRUSH";            // nombre de clase de la ventana principal

HWND button, button2;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                GameRegisterClass(HINSTANCE hInstance);
ATOM                MenuRegisterClass(HINSTANCE hInstance);
BOOL                InitGame(HINSTANCE, int);
BOOL                InitMenu(HINSTANCE, int);
LRESULT CALLBACK    Game(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Menu(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Colocar código aquí.

	// Inicializar cadenas globales
	LoadStringW(hInstance, IDS_APP_TITLE, GAME_NAME, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TICTACTOE, MENU_CLASS_NAME, MAX_LOADSTRING);
	GameRegisterClass(hInstance);
	MenuRegisterClass(hInstance);


	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	// Realizar la inicialización de la aplicación:
	if (!InitMenu(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOE));

	MSG msg;

	// Bucle principal de mensajes:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



ATOM GameRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW game;

	game.cbSize = sizeof(WNDCLASSEX);

	game.style = CS_HREDRAW | CS_VREDRAW;
	game.lpfnWndProc = Game;
	game.cbClsExtra = 0;
	game.cbWndExtra = 0;
	game.hInstance = hInstance;
	game.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
	game.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	game.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	game.lpszMenuName = MAKEINTRESOURCEW(IDC_TICTACTOE);
	game.lpszClassName = GAME_CLASS_NAME;
	game.hIconSm = LoadIcon(game.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&game);
}

ATOM MenuRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW menu;

	menu.cbSize = sizeof(WNDCLASSEX);

	menu.style = CS_HREDRAW | CS_VREDRAW;
	menu.lpfnWndProc = Menu;
	menu.cbClsExtra = 0;
	menu.cbWndExtra = 0;
	menu.hInstance = hInstance;
	menu.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
	menu.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	menu.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	menu.lpszMenuName = MAKEINTRESOURCEW(IDC_TICTACTOE);
	menu.lpszClassName = MENU_CLASS_NAME;
	menu.hIconSm = LoadIcon(menu.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&menu);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitGame(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Almacenar identificador de instancia en una variable global

	HWND hWnd = CreateWindowW(GAME_CLASS_NAME, GAME_NAME, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

BOOL InitMenu(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Almacenar identificador de instancia en una variable global

	HWND hWnd = CreateWindowW(MENU_CLASS_NAME, GAME_NAME, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//HICON cerdo, gasho;
Board gameB;
vector<int> moves;


//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK Game(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizar las selecciones de menú:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		short xPos = GET_X_LPARAM(lParam);
		short yPos = GET_Y_LPARAM(lParam);
		int index = gameB.GetNumber(hWnd, xPos, yPos);
		HDC hdc = GetDC(hWnd);
		if (hdc != NULL)
		{
			WCHAR temp[100];
			wsprintf(temp, L"[%d]", index);
			TextOut(hdc,xPos,yPos,temp,lstrlen(temp));
			if (index != -1)
			{
				moves.push_back(index);
				if (moves.size() >= 2)
				{
					gameB.PlayerMove(&moves);
					InvalidateRect(hWnd, nullptr, true);
				}

			}
			ReleaseDC(hWnd, hdc);
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		short xPos = GET_X_LPARAM(lParam);
		short yPos = GET_Y_LPARAM(lParam);
		int index = gameB.GetNumber(hWnd, xPos, yPos);
		HDC hdc = GetDC(hWnd);
		if (hdc != NULL)
		{
			WCHAR temp[100];
			wsprintf(temp, L"[%d]", index);
			TextOut(hdc, xPos, yPos, temp, lstrlen(temp));
			if (index != -1)
			{

				gameB.CallPower(hWnd,xPos,yPos);
				InvalidateRect(hWnd, nullptr, true);

			}
			ReleaseDC(hWnd, hdc);
		}
	}
	break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_RETURN))
		{
			gameB.FullReset();
			InvalidateRect(hWnd, nullptr, true);
		}
	}
	break;
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
		if (pMinMax != nullptr)
		{
			pMinMax->ptMinTrackSize.x = gameB.GetCellSize() * 5;
			pMinMax->ptMinTrackSize.y = gameB.GetCellSize() * 5;
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Agregar cualquier código de dibujo que use hDC aquí...
		RECT rc;

		Gdiplus::Graphics gf(hdc);
		Gdiplus::Font font(L"Arial", 16);

		Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));
		if (!gameB.gameOver)
		{
			gameB.DrawBoard(hWnd,hdc,&rc,&gf);
			gameB.DrawScoreTurns(&gf, &font, &brush); 
		}
		else
		{
			Gdiplus::Font fontW(L"Arial", 35);
			Gdiplus::SolidBrush wbrush(Gdiplus::Color(255, 255, 255));
			gameB.DrawGameOver(&gf, &font, &wbrush);
		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK Menu(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
	{
		button = CreateWindow(L"BUTTON", L"Start Game", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 400, 200, 20, hWnd, (HMENU)1, NULL, NULL);
		button2 = CreateWindow(L"BUTTON", L"Close Game", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 420, 200, 20, hWnd, (HMENU)2, NULL, NULL);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizar las selecciones de menú:
		switch (wmId)
		{
		case 1:
		{
			button = false;
			HWND hwnd = CreateWindow(GAME_CLASS_NAME,
				GAME_NAME,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
				nullptr,
				nullptr,
				hInst,
				0);
			ShowWindow(hwnd, SW_NORMAL);
			UpdateWindow(hwnd);

		}
		break;
		case 2:
		{
			DestroyWindow(hWnd);
		}
		break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_RETURN))
		{
			HWND hwnd = CreateWindow(GAME_CLASS_NAME,
				GAME_NAME,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
				nullptr,
				nullptr,
				hInst,
				0);
			ShowWindow(hwnd, SW_NORMAL);
			UpdateWindow(hwnd);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Agregar cualquier código de dibujo que use hDC aquí...
		RECT rc;

		Gdiplus::Graphics gf(hdc);
		Gdiplus::Bitmap bmp(L"start.png");

		gf.DrawImage(&bmp, 0, 0,800,600);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

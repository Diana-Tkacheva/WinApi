// WinApi_MilkyWay.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WinApi_MilkyWay.h"
#include "PlanetClass.h"

#define MAX_LOADSTRING 100
// идентификатор текстового поля в файле ресурсов
#define ID_EDIT 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
PlanetClass planets[9];
bool isPlanetsVisible = false;
bool isInfoVisible = false;
HWND textBox;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	planets[0] = PlanetClass(L"Sun", 40, COLORREF(RGB(255, 255, 0)), 0, 0);
	planets[1] = PlanetClass(L"Mercury", 20, COLORREF(RGB(220, 220, 220)), 1, 70);
	planets[2] = PlanetClass(L"Venus", 30, COLORREF(RGB(255, 250, 205)), 2, 100);
	planets[3] = PlanetClass(L"Earth", 40, COLORREF(RGB(0, 191, 255)), 3, 130);
	planets[4] = PlanetClass(L"Mars", 43, COLORREF(RGB(205, 133, 63)), 4, 160);
	planets[5] = PlanetClass(L"Jupiter", 50, COLORREF(RGB(210, 105, 30)), 5, 190);
	planets[6] = PlanetClass(L"Saturn", 40, COLORREF(RGB(244, 164, 96)), 6, 220);
	planets[7] = PlanetClass(L"Uranus", 43, COLORREF(RGB(135, 206, 235)), 7, 250);
	planets[8] = PlanetClass(L"Neptune", 36, COLORREF(RGB(176, 196, 222)), 8, 280);
	// Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIMILKYWAY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIMILKYWAY));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIMILKYWAY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_GRAYTEXT + 13);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIMILKYWAY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HBRUSH hBrush = NULL; //Создаём кисть

    switch (message)
    {
	//case WM_MOUSEHOVER:
	case WM_SETCURSOR:
	{
		if (isInfoVisible && isPlanetsVisible)
		{
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(hWnd, &p);
			bool isInPlanet = false;
			for (int idx = 0; idx < 9; idx++)
			{
				if (p.x > planets[idx].X - planets[idx].Diam / 2 &&
					p.x < planets[idx].X + planets[idx].Diam / 2 &&
					p.y > planets[idx].Y - planets[idx].Diam / 2 &&
					p.y < planets[idx].Y + planets[idx].Diam / 2)
				{
					SetWindowTextW(textBox, planets[idx].Name);
					isInPlanet = true;
					break;
				}
			}
			if (!isInPlanet)
			{
				SetWindowTextW(textBox, L"Solar system");
			}
		}
	}
	break;
	case WM_CREATE:
	{
		textBox = CreateWindow(L"EDIT", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_DISABLED | NULL,
			10, 10, 200, 20, hWnd, (HMENU)ID_EDIT, hInst, NULL);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		isPlanetsVisible = !isPlanetsVisible;
		if (!isPlanetsVisible)
		{
			SetWindowTextW(textBox, L"");
		}
		RECT rect;
		GetClientRect(hWnd, &rect);
		InvalidateRect(hWnd, &rect, true);
		UpdateWindow(hWnd);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		isInfoVisible = !isInfoVisible;
		if (!isInfoVisible)
		{
			SetWindowTextW(textBox, L"");
		}
		RECT rect;
		GetClientRect(hWnd, &rect);
		InvalidateRect(hWnd, &rect, true);
		UpdateWindow(hWnd);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (isPlanetsVisible)
		{
			RECT rect;
			GetClientRect(hWnd, &rect);
			bool isRepeateX = false;
			bool isRepeateY = false;
			for (int idx = 0; idx < 9; idx++)
			{
				int x = rect.right / 2;
				int y = rect.bottom / 2;
				if (idx > 0)
				{
					SelectObject(hdc, GetStockObject(NULL_BRUSH));
					int correct = planets[idx].DistToSun / 5;
					Ellipse(hdc, (x - planets[idx].DistToSun) - correct,
						(y + planets[idx].DistToSun) - correct,
						(x + planets[idx].DistToSun) + correct,
						(y - planets[idx].DistToSun) + correct);
					hBrush = CreateSolidBrush(planets[idx].Color);
					SelectObject(hdc, hBrush);
					if (idx % 2)
					{
						planets[idx].Y = y;
						if (isRepeateX)
						{
							Ellipse(hdc, ((x - planets[idx].DistToSun) - correct) - planets[idx].Diam / 2,
								y + planets[idx].Diam / 2,
								((x - planets[idx].DistToSun) - correct) + planets[idx].Diam / 2,
								y - planets[idx].Diam / 2);
							planets[idx].X = (x - planets[idx].DistToSun) - correct;
						}
						else
						{
							Ellipse(hdc, ((x + planets[idx].DistToSun) + correct) - planets[idx].Diam / 2,
								y + planets[idx].Diam / 2,
								((x + planets[idx].DistToSun) + correct) + planets[idx].Diam / 2,
								y - planets[idx].Diam / 2);
							planets[idx].X = (x + planets[idx].DistToSun) + correct;
						}
						isRepeateX = !isRepeateX;
					}
					else
					{
						planets[idx].X = x;
						if (isRepeateY)
						{
							Ellipse(hdc, x - planets[idx].Diam / 2,
								((y + planets[idx].DistToSun) - correct) + planets[idx].Diam / 2,
								x + planets[idx].Diam / 2,
								((y + planets[idx].DistToSun) - correct) - planets[idx].Diam / 2);
							planets[idx].Y = (y + planets[idx].DistToSun) - correct;
						}
						else
						{
							Ellipse(hdc, x - planets[idx].Diam / 2,
								((y - planets[idx].DistToSun) + correct) + planets[idx].Diam / 2,
								x + planets[idx].Diam / 2,
								((y - planets[idx].DistToSun) + correct) - planets[idx].Diam / 2);
							planets[idx].Y = (y - planets[idx].DistToSun) + correct;
						}
						isRepeateY = !isRepeateY;
					}
				}
				else
				{
					hBrush = CreateSolidBrush(planets[idx].Color);
					SelectObject(hdc, hBrush);
					Ellipse(hdc, x - planets[idx].Diam, y + planets[idx].Diam,
						x + planets[idx].Diam, y - planets[idx].Diam);
					planets[idx].X = x;
					planets[idx].Y = y;
				}
			}
		}
		if (hBrush != NULL)
		{
			DeleteObject(hBrush);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		if (hBrush != NULL)
		{
			DeleteObject(hBrush); //уничтожаем кисть
		}
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//switch (messg)
//{		
//
//	int x, y; //координаты
//case WM_RBUTTONDOWN:
//case WM_LBUTTONDOWN:
//	char* str;
//	HDC hDC;
//
//	hDC = GetDC(hWnd);
//	x = LOWORD(lParam); //узнаём координаты
//	y = HIWORD(lParam);
//
//	TextOut(hDC, x, y, szText, strlen(szText));
//
//	break;
//}
// Message handler for about box.
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

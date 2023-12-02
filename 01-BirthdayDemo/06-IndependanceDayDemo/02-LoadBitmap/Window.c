//windows header file
#include<windows.h>

#include"window.h"

#define IMAGE_WIDTH  576
#define IMAGE_HEIGHT 576

//Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable
HINSTANCE ghInstance;

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("SGKWindow");

	//WNDCLASSEX Initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	ghInstance = hInstance;

	//Register WNDCLASSEX
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindow(szAppName,
		TEXT("Siddhant Ganesh Kshirsagar"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//show window
	ShowWindow(hwnd, iCmdShow);

	//Paint/Redraw Window
	UpdateWindow(hwnd);

	//Message Loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

//Callback function defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable 
	HDC hdc, hdc_compatible;
	PAINTSTRUCT ps;
	RECT rc;
	HBITMAP hBitmap;

	//code
	switch (iMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rc);

		hBitmap = LoadBitmap(ghInstance, MAKEINTRESOURCE(IDB_BITMAPIMAGE));

		hdc_compatible = CreateCompatibleDC(hdc);

		SelectObject(hdc_compatible, hBitmap);

		BitBlt(hdc, (rc.right - rc.left) / 2 - IMAGE_WIDTH / 2, (rc.bottom - rc.top) / 2 - IMAGE_HEIGHT / 2, IMAGE_WIDTH, IMAGE_HEIGHT, hdc_compatible, 0, 0, SRCCOPY);

		DeleteDC(hdc_compatible);
		DeleteDC(hdc);
		EndPaint(hwnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

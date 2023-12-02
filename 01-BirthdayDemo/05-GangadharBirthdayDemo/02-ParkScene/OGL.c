//windows header file
#include<windows.h> // for win32 API
#include<stdio.h> // For File IO
#include<stdlib.h> // For Exit
#define _USE_MATH_DEFINES
#include<math.h>
//OpenGL Header
#include<gl/GL.h>

#include"OGL.h"

//OpenGl Related Global variable
HDC ghdc = NULL;
HGLRC ghrc = NULL;

//Macros 
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Link With OpenGL Library
#pragma comment(lib,"OpenGL32.lib")

//Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//local function declaration
// DrawCircle() Description
// 1st parameter :- radius of circle , data type (float)
// 2nd parameter center x axis of circle , data type (float) 
// 3rd parameter center y axis of cirlce , data type (float)
// 4th parameter angle of cirlce ideal use between 0.0f to 360.0f(control how much circle part you want to draw. e.g. 180.0f = half circle , 360.0f = full circle) data type (float)
//	***** Note :- use glColor3f() call before calling DrawCircle it will draw circle according to color 
void DrawCircle(float, float, float, float);

//DrawGrass() Description
//  1st parameter x Axis for draw grass bunch , data type (float)
//  2nd parameter y Axis for draw grass bunch , data type (float)
//  3rd parameter height of the grass , data type (float)
void DrawGrass(float, float, float);

//Global variable declaration
DWORD dwStyle = 0;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) }; // initialization of struct => this work on all type (if we want to initialize all value to 0)
BOOL gbFullscreen = FALSE;
FILE *gpFILE = NULL;

HWND ghwnd = NULL; // g = global handle of window
BOOL gbActive = FALSE; 

BOOL gbGrassRight = FALSE; // for grass animation
float gfGrassMove = 0.0f; // for grass animation

BOOL gbWind = FALSE; // for wind animation
float gfWind = 170.0f; // for wind animation
float gfVertex[] = { 0.0f,0.0f,0.0f };

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Function declaration
	int initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	//local variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("SGKWindow");

	int iResult = 0;

	BOOL bDone = FALSE; // For Game Loop

	int SystemWindowWidth, SystemWindowHeight;
	int x_Coordinate, y_Coordinate;

	// get system window width and height
	SystemWindowWidth = GetSystemMetrics(SM_CXSCREEN);
	SystemWindowHeight = GetSystemMetrics(SM_CYSCREEN);
	// get x and y coordinate for show window in center on screen
	x_Coordinate = (SystemWindowWidth / 2) - (WIN_WIDTH / 2);
	y_Coordinate = (SystemWindowHeight / 2) - (WIN_HEIGHT / 2);

	//code
	gpFILE = fopen("Log.txt", "w");
	if (gpFILE == NULL)
	{
		MessageBox(NULL, TEXT("Log file cannot be open"), TEXT("Error"), MB_OK|MB_ICONERROR);
		exit(0);
	}
	fprintf(gpFILE, "Program Started Successfully\n");

	//WNDCLASSEX Initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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

	//Register WNDCLASSEX
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Siddhant Ganesh Kshirsagar"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		x_Coordinate,
		y_Coordinate,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	//Initialization 
	iResult = initialize();
	if (iResult != 0)
	{
		MessageBox(hwnd, TEXT("initialize() failed."), TEXT("Error"), MB_OK|MB_ICONERROR);
		DestroyWindow(hwnd);
	}

	//show window
	ShowWindow(hwnd, iCmdShow);

	// set window first in z-order (foreground)
	SetForegroundWindow(hwnd);

	// set focus on this window(internally send 'WM_SETFOCUS' message to WndProc())
	SetFocus(hwnd);

	//Game Loop
	while(bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// code
			if (gbActive == TRUE) // If Window is in focus then 'WM_SETFOCUS' is send to WndProc() and We Handled this message and set gbActive = true 
			{
				//Render
				display();

				//Update
				update();
			}

		}
	}

	// Uninitialization
	uninitialize();

	return((int)msg.wParam);
}

//Callback function defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declarations
	void ToggleFullScreen(void);
	void resize(int, int);

	switch (iMsg)
	{
	case WM_SETFOCUS: // when window is in focus (window is activate)
		gbActive = TRUE;
		break;
	case WM_KILLFOCUS: // when window is not in focus(window is deactivate)
		gbActive = FALSE;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam),HIWORD(lParam));
		break;

	case WM_ERASEBKGND:
		return(0);

	case WM_KEYDOWN:
	{
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		default:
			break;
		}
	}
	break;
	case WM_CHAR:
	{
		switch (LOWORD(wParam))
		{
		case 'F':
		case 'f':
			if (gbFullscreen == FALSE)
			{
				ToggleFullScreen();
				gbFullscreen = TRUE;
			}
			else
			{
				ToggleFullScreen();
				gbFullscreen = FALSE;
			}
			break;
		default:
			break;
		}
	}
	break;
	
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	//local variable declaration
	MONITORINFO mi = { sizeof(MONITORINFO) };

	//code
	if (gbFullscreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	//function declarations

	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//step 1 :- Initialization of PIXELFORMATDESCRIPTOR
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	// step 2 :- Get DC 
	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		fprintf(gpFILE, "GetDC() Failed.\n");
		return(-1);
	}

	// step 3 :- Os will return pixel format index which is closest match to our pixel format descriptor
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0) // ChoosePixelFormat() return non zero positive on success , on failure return 0
	{
		fprintf(gpFILE, "ChoosePixelFormat() Failed.\n");
		return(-2);
	}

	// step 4 :- Set obtained pixel format
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFILE, "SetPixelFormat() Failed.\n");
		return(-3);
	}

	// step 5 :- Create OpenGL Context From Device Context(ghdc)
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(gpFILE, "wglCreateContext() Failed.\n");
		return(-4);
	}

	// step 6 :- Make rendering context current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFILE,"wglMakeCurrent() Failed.\n");
		return(-5);
	}

	// step 7 : - set clear color of window to blue (here OpenGL Start)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return(0);
}

void resize(int width, int height)
{
	//code
	if (height <= 0)
	{
		height = 1;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
	//function declaration
	void DrawTreesInBackside(void); // argument 1 :- radius of circle
	void DrawTree(void);
	void WindAnimation(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.5f, 0.1f);
	glVertex3f(-1.0f, -0.2f, 0.0f);
	glVertex3f(-1.0f, -0.7f, 0.0f);
	glVertex3f(1.0f, -0.7f, 0.0f);
	glVertex3f(1.0f, -0.2f, 0.0f);
	glEnd();
	glEnable(GL_LINE_SMOOTH);
	DrawTreesInBackside();
	DrawTree();

	//for grass draw
	
	glLineWidth(3.0f);
	glColor3f(0.0f, 0.9f, 0.1f);
	for (float xAxis = -0.95f; xAxis <= 1.0f; xAxis = xAxis + 0.05f)
	{
		for (float yAxis = -0.2f; yAxis >= -0.7f; yAxis = yAxis - 0.04f)
		{
			DrawGrass(xAxis, yAxis, 0.06f);
		}

	}
	glColor3f(0.0f, 0.8f, 0.2f);
	for (float xAxis = -1.0f; xAxis <= 1.0f; xAxis = xAxis + 0.03f)
	{
		for (float yAxis = -0.2f; yAxis >= -0.7f; yAxis = yAxis - 0.04f)
		{
			DrawGrass(xAxis, yAxis, 0.04f);
		}

	}
	glColor3f(0.1f, 0.7f, 0.2f);
	glLineWidth(4.0f);
	for (float xAxis = 0.25f; xAxis <= 0.35f; xAxis = xAxis + 0.008f)
	{
			DrawGrass(xAxis, 0.4f, 0.01f);
	}
	glColor3f(0.0f, 0.5f, 0.1f);
	for (float xAxis = 0.2f; xAxis <= 0.25f; xAxis = xAxis + 0.007f)
	{
		DrawGrass(xAxis, 0.25f, 0.01f);
	}
	glLineWidth(2.5f);
	DrawGrass(0.35f, 0.35f, 0.01f);
	glLineWidth(1.0f);
	glDisable(GL_LINE_SMOOTH);

	WindAnimation();

	SwapBuffers(ghdc);
}

void update(void)
{
	//code
	if (gbGrassRight == FALSE)
	{
		if (gfGrassMove < 0.03f)
		{
			gfGrassMove = gfGrassMove + 0.001f;
		}
		else
		{
			gbGrassRight = TRUE;
		}
		
	}
	else 
	{
		if (gfGrassMove > 0.0f)
		{
			gfGrassMove = gfGrassMove - 0.001f;
		}
		else
		{
			gbGrassRight = FALSE;
		}
		
	}

	// for wind animation
	if (gbWind == FALSE)
	{
		if (gfWind <= 300.0f)
		{
			gfWind = gfWind + 1.0f;
		}
		else
		{
			gfWind = 125.0f;
			gbWind = TRUE;
		}
	}
	else
	{
		
		
		if (gfWind >= 0.0f)
		{
			gfWind = gfWind - 1.0f;
		}
		else
		{
			gfWind = 170.0f;
			gbWind = FALSE;
		}
		
	}

}

void DrawTreesInBackside(void)
{

	//for draw circles 
	glColor3f(0.0f, 0.5f, 0.2f);
	for (float XAxis = -1.0f; XAxis <= 1.0f; XAxis = XAxis + 0.4f)
	{
		
		DrawCircle(0.2f,XAxis,-0.2f,180.0f);

	}
	glColor3f(0.0f, 0.6f, 0.4f);
	for (float XAxis = -1.0f; XAxis <= 1.0f; XAxis = XAxis + 0.4f)
	{

		DrawCircle(0.15f, XAxis, -0.2f, 180.f);

	}
	glColor3f(0.0f, 0.8f, 0.2f);
	for (float XAxis = -0.8f; XAxis <= 0.8f; XAxis = XAxis + 0.4f)
	{

		DrawCircle(0.1f, XAxis, -0.2f,180.f);

	}

	


}

void DrawCircle(float fRadius,float xAxis,float yAxis,float angle)
{
	glBegin(GL_LINES);
	for (float fAngle = 0.0f; fAngle <= angle; fAngle = fAngle + 0.1f)
	{
		float x = xAxis + fRadius * cos(fAngle * M_PI / 180.0f);
		float y = yAxis+ fRadius * sin(fAngle * M_PI / 180.0f);
		glVertex3f(xAxis, yAxis, 0.0f);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
}

void DrawGrass(float xAxis,float yAxis,float height)
{

	glBegin(GL_LINES);
	for (float fXAxis = xAxis-0.03f; fXAxis <= xAxis+0.03f; fXAxis = fXAxis + 0.01f)
	{
		glVertex3f(fXAxis+gfGrassMove, (yAxis + height), 0.0f);
		glVertex3f(xAxis, yAxis, 0.0f);
	
	}
	glEnd();

}

void WindAnimation(void) 
{
	//code 
	if (gbWind==FALSE)
	{
		for (float fAngle = 170.0f; fAngle <= gfWind; fAngle = fAngle + 0.1f)
		{
			float x = -0.5f + 0.85f * cos(fAngle * M_PI / 180.0f);
			float y = 0.9f + 0.85f * sin(fAngle * M_PI / 180.0f);


			gfVertex[0] = x;
			gfVertex[1] = y;

		}
	}
	else
	{
		for (float fAngle = 125.0f; fAngle >= gfWind; fAngle = fAngle - 0.1f)
		{
			float xAxis = 0.45f + 0.85f * cos(fAngle * M_PI / 180.0f);
			float yAxis = -0.52f + 0.85f * sin(fAngle * M_PI / 180.0f);

				gfVertex[0] = xAxis;
				gfVertex[1] = yAxis;

		}
	}

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f(gfVertex[0],gfVertex[1], 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f(gfVertex[0]-0.008f, gfVertex[1], 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0]-0.01f), (gfVertex[1]-0.01f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f(((gfVertex[0] - 0.01f)-0.008f), (gfVertex[1] - 0.01f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] + 0.03f), (gfVertex[1] + 0.01f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f(((gfVertex[0] + 0.03f)-0.008f), (gfVertex[1] + 0.01f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] - 0.04f), (gfVertex[1] - 0.03f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f((gfVertex[0] - 0.04f)-0.008f, (gfVertex[1] - 0.03f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] + 0.02f), (gfVertex[1] + 0.04f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f((gfVertex[0] + 0.02f)-0.008f, (gfVertex[1] + 0.04f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] + 0.02f), (gfVertex[1] - 0.04f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f((gfVertex[0] + 0.02f)-0.008f, (gfVertex[1] - 0.04f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] - 0.05f), (gfVertex[1] + 0.035f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f((gfVertex[0] - 0.05f)-0.008f, (gfVertex[1] + 0.035f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] + 0.02f), (gfVertex[1] - 0.012f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f((gfVertex[0] + 0.02f)-0.008f, (gfVertex[1] - 0.012f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] - 0.024f), (gfVertex[1] + 0.04f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f((gfVertex[0] - 0.024f)-0.008f, (gfVertex[1] + 0.04f), 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f((gfVertex[0] + 0.045f), (gfVertex[1] - 0.02f), 0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f((gfVertex[0] + 0.045f)-0.008f, (gfVertex[1] - 0.02f), 0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void DrawTree(void)
{
	glColor3f(0.2f, 0.5f, 0.3f);
	DrawCircle(0.1f, 0.4f, 0.2f, 360.0f);
	DrawCircle(0.1f, 0.55f, 0.3f, 360.0f);
	glColor3f(0.1f, 0.5f, 0.1f);
	DrawCircle(0.1f, 0.37f, 0.25f, 360.0f);

	glColor3f(0.1f, 0.6f, 0.2f);
	DrawCircle(0.1f, 0.3f , 0.18f, 360.0f);
	glColor3f(0.1f, 0.5f, 0.1f);
	DrawCircle(0.1f, 0.45f , 0.28f, 360.0f);
	DrawCircle(0.1f, 0.25f, 0.2f, 360.0f);

	glColor3f(0.1f, 0.4f, 0.1f);
	DrawCircle(0.1f, 0.2f, 0.28f, 360.0f);

	DrawCircle(0.1f, 0.14f , 0.35f, 360.0f);

	glLineWidth(10.0f);
	glBegin(GL_LINES);

	glColor3f(129.0f / 255.0f, 56.0f / 255.0f, 19.0f / 255.0f);
	glVertex3f(0.3f, 0.2f, 0.0f);
	glVertex3f(0.3f, -0.2f, 0.0f);

	glVertex3f(0.31f, 0.2f, 0.0f);
	glVertex3f(0.31f, -0.2f, 0.0f);

	glVertex3f(0.4f, 0.2f, 0.0f);
	glVertex3f(0.3f, 0.05f, 0.0f);

	glVertex3f(0.2f, 0.1f, 0.0f);
	glVertex3f(0.3f, 0.02f, 0.0f);

	glEnd();
	glLineWidth(1.0f);


	glColor3f(0.1f, 0.5f, 0.1f);
	DrawCircle(0.1f, 0.3f, 0.34f, 360.0f);
	DrawCircle(0.1f, 0.3f, 0.22f, 360.0f);

	glColor3f(0.1f, 0.6f, 0.2f);
	DrawCircle(0.1f, 0.3f, 0.35f, 360.0f);
	DrawCircle(0.1f, 0.4f, 0.4f, 360.0f);

	glColor3f(0.1f, 0.6f, 0.2f);
	DrawCircle(0.1f, 0.3f, 0.5f, 360.0f);
	glColor3f(0.1f, 0.6f, 0.2f);
	DrawCircle(0.1f, 0.25f, 0.45f, 360.0f);

	glColor3f(0.2f, 0.5f, 0.3f);
	DrawCircle(0.1f, 0.45f, 0.45f, 360.0f);

	glColor3f(0.2f, 0.5f, 0.3f);
	DrawCircle(0.04f, 0.2f, 0.1f, 360.0f);

	glColor3f(0.2f, 0.5f, 0.3f);
	DrawCircle(0.06f, 0.26f, 0.16f, 360.0f);

	glColor3f(0.0f, 0.4f, 0.1f);
	DrawCircle(0.05f, 0.22f, 0.12f, 360.0f);
	

}
void uninitialize(void)
{
	//function declarations
	void ToggleFullScreen(void);
	//code

	// If Application is exitting in fullscreen mode
	if (gbFullscreen == TRUE)
	{
		ToggleFullScreen();
		gbFullscreen = FALSE;
	}

	//Make ghdc as current context
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	//Delete Rendering Context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// Release the ghdc
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	// Destroy Window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	// Close log file
	if (gpFILE)
	{
		fprintf(gpFILE, "Program Ended Successfully\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}



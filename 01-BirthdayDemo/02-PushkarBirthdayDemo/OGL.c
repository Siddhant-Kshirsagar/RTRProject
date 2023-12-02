//windows header file
#include<windows.h> // for win32 API
#include<stdio.h> // For File IO
#include<stdlib.h> // For Exit
#define _USE_MATH_DEFINES
#include<math.h> // for sin and cos

//OpenGL Header
#include<gl/GL.h>
#include<GL/glu.h>

#include"OGL.h"

//OpenGl Related Global variable
HDC ghdc = NULL;
HGLRC ghrc = NULL;

//Macros 
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Link With OpenGL Library
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")

//Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable declaration
DWORD dwStyle = 0;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) }; // initialization of struct => this work on all type (if we want to initialize all value to 0)
BOOL gbFullscreen = FALSE;
FILE *gpFILE = NULL;

HWND ghwnd = NULL; // g = global handle of window
BOOL gbActive = FALSE; 

//ball goes up
BOOL gbBallUp = FALSE;
GLfloat gfBallUp = 0.0f;

//ball goes in 
GLfloat gfBall = -1.0f;
//ball curve animation 
BOOL gbBallParabola = FALSE;
float gfVertex[] = {0.0f,0.0f,0.0f}; // center of ball vertex array
float gfAngle = 180.0f; // angle use for curve animation (use circle logic to get curve coordinate)
//ball spin
BOOL gbBallSpin = FALSE;
float gfBallSpinAngle = 0.0f;

//background transition
float gfColor[] = {0.0f,0.0f,0.0f};
float gfBlueColor[] = {0.0f,0.0f,0.0f};
//function declaration 
void backgroundAnimation(float); // param angle of arc

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

		case 'S':
		case 's':
		{
			if(gbBallParabola==FALSE)
			{
				//reset transition color of background
				gfColor[0] = 0.0f;
				gfColor[1] = 0.0f;
				gfColor[2] = 0.0f;

				gfBlueColor[0] = 0.0f;
				gfBlueColor[1] = 0.0f;
				gfBlueColor[2] = 0.0f;
				gbBallParabola = TRUE;
			}
			else
			{
				gbBallParabola = FALSE;
			}
		}
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
	void resize(int width, int height);
	
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

	resize(WIN_WIDTH,WIN_HEIGHT);

	return(0);
}

void resize(int width, int height)
{
	//code
	if (height <= 0)
	{
		height = 1;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
}

void display(void)
{
	//function declarations
	//1st param radius 
	//2nd param x coordinate of center of circle
	//3rd param y coordinate of center of circle
	void drawBall(float, float, float); 

	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f,0.0f,-3.0f);

	if(gbBallParabola == FALSE)
	{

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.1f, 0.2f, 0.0f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.1f, 0.2f, 0.0f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-0.5f, -0.6f, 0.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, -0.6f, 0.0f);

		glEnd();

		drawBall(0.1f, 0.0f, 0.0f);
		gfAngle = 180.0f;
	}
	else
	{
	
		backgroundAnimation(gfAngle);
		drawBall(0.1f, 0.0f, 0.0f);
	}

	

	SwapBuffers(ghdc);
}

void update(void)
{
	//code

	
	if(gbBallParabola==FALSE)
	{
		if (gbBallUp == FALSE)//ball goes in
		{
			if (gfBall >= -4.0f)
			{
				gfBall = gfBall - 0.02f;
			}
			else
			{
				gbBallUp = TRUE;
			}
		}
		else//ball goes up
		{
			if (gfBallUp <= 1.9f)
			{
				gfBallUp = gfBallUp + 0.01f;
			}
			else
			{
				gbBallUp = FALSE;
				gfBallUp = 0.0f;
				gfBall = -1.0f;
			}
		}

		// ball spin 
		if(gfBallSpinAngle<=360.0f)
		{
			gfBallSpinAngle = gfBallSpinAngle + 1.0f;
		}
		else
		{
			gfBallSpinAngle = 0.0f;
		}

	}
	else
	{
			//ball arc animation angle 
			if(gfAngle>0.0f)
			{
				gfAngle = gfAngle - 0.5f;
			}
			else
			{
				gfAngle = 180.0f;
			}

			//ball spin itself
			if(gfBallSpinAngle<=360.0f)
			{
				gfBallSpinAngle = gfBallSpinAngle + 10.0f;
			}
			else
			{
				gfBallSpinAngle = 0.0f;
			}

		//background transition
		
		if(gfColor[1]<1.0f)
		{
			//use value according to color transition ( index 0 = red, index 1 = green , index 2 = blue)
			// gfColor[0] = gfColor[0] + 0.01f;
			gfColor[1] = gfColor[1] + 0.01f;
			gfColor[2] = gfColor[2] + 0.01f;
		}

		if(gfBlueColor[0]<1.0f)
		{
			//use value according to color transition ( index 0 = red, index 1 = green , index 2 = blue)
			gfBlueColor[0] = gfBlueColor[0] + 0.01f;
			// gfBlueColor[1] = gfBlueColor[1] + 0.01f;
			// gfBlueColor[2] = gfBlueColor[2] + 0.01f;
		}
			
	}

	
	
	
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

void drawBall(float fRadius, float xCoordinate,float yCoordinate)
{
	float xAxis = 0.0f, yAxis = 0.0f;
	glLoadIdentity();

	if(gbBallParabola == FALSE)
	{
		if (gbBallUp == FALSE)
		{
			glTranslatef(0.0f, 0.0f, gfBall);
			glRotatef(gfBallSpinAngle,0.0f,0.0f,1.0f);
		}
		else
		{
			glTranslatef(0.0f, gfBallUp, gfBall);
			glRotatef(gfBallSpinAngle,0.0f,0.0f,1.0f);
		}
	}
	else
	{
		glTranslatef(gfVertex[0],gfVertex[1],-3.0f);
		glRotatef(gfBallSpinAngle,0.0f,0.0f,1.0f);
	}


	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINES);
	for (float fAngle = 0.0f; fAngle <= 360.0f; fAngle = fAngle + 0.01f)
	{
		xAxis = xCoordinate + fRadius * cos(fAngle);
		yAxis = yCoordinate + fRadius * sin(fAngle);

		glColor3f(1.0f, 0.0f, 0.0f);

		glVertex3f(xAxis, yAxis, 0.0f);
		glVertex3f(xCoordinate, yCoordinate, 0.0f);

	}
	glEnd();

	glLineWidth(0.5f);
	// white lines on the ball
	glBegin(GL_LINES);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f((xCoordinate), (yCoordinate - fRadius), 0.0f);
	glVertex3f((xCoordinate), (yCoordinate + fRadius), 0.0f);


	glVertex3f((xCoordinate + 0.01f), (yCoordinate - fRadius), 0.0f);
	glVertex3f((xCoordinate + 0.01f), (yCoordinate + fRadius), 0.0f);

	glVertex3f((xCoordinate - 0.01f), (yCoordinate - fRadius), 0.0f);
	glVertex3f((xCoordinate - 0.01f), (yCoordinate + fRadius), 0.0f);

	glEnd();

	glDisable(GL_SMOOTH);
}

void backgroundAnimation(float fAngleLimit)
{
	void DrawCloud(void);

	for (float fAngle = 180.0f; fAngle >= fAngleLimit; fAngle = fAngle - 0.01f)
	{
		gfVertex[0] = 0.0f + 2.0f * cos((fAngle*M_PI)/180);
		gfVertex[1] = -1.5f + 2.0f * sin((fAngle*M_PI)/180);

	}

	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-1.0f);
	
	glBegin(GL_QUADS);

	glColor3f(gfColor[0],gfColor[1],gfColor[2]);
	glVertex3f(1.0f,1.0f,0.0f);
	glVertex3f(-1.0f,1.0f,0.0f);
	glVertex3f(-1.0f,0.0f,0.0f);
	glVertex3f(1.0f,0.0f,0.0f);

	
	glVertex3f(1.0f,0.0f,0.0f);
	glVertex3f(-1.0f,0.0f,0.0f);

	glColor3f(gfBlueColor[0],gfBlueColor[1],gfBlueColor[2]);
	glVertex3f(-1.0f,-1.0f,0.0f);
	glVertex3f(1.0f,-1.0f,0.0f);		
	glEnd();

	DrawCloud();

}

void DrawCloud(void)
{
	//function declaration
	// 1st param radius of circle 
	// 2nd param x coordinate of center of circle
	// 3rd param y coordinate of center of circle
	// call glColor3f() before calling this function for color 
	void DrawCircle(float,float,float);

	glColor3f(1.0f,1.0f,1.0f);
	DrawCircle(0.1f,0.2f,0.4f);
	DrawCircle(0.1f,0.25f,0.35f);
	DrawCircle(0.1f,0.35f,0.35f);
	DrawCircle(0.1f,0.45f,0.35f);


	DrawCircle(0.1f, -0.2f, 0.2f);
	DrawCircle(0.1f, -0.3f, 0.23f);
	DrawCircle(0.1f, -0.4f, 0.15f);
	DrawCircle(0.09f, -0.3f, 0.15f);
}

void DrawCircle(float fRadius,float xAxis,float yAxis)
{
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-1.0f);
	glBegin(GL_LINES);

	for(float fAngle = 0.0f; fAngle <= 360.0f; fAngle = fAngle + 0.1f)
	{
		float x = xAxis + fRadius * cos(fAngle);
		float y = yAxis + fRadius * sin(fAngle);

		glVertex3f(xAxis,yAxis,0.0f);
		glVertex3f(x,y,0.0f);
	}

	glEnd();
}




//windows header file
#include<windows.h> // for win32 API
#include<stdio.h> // For File IO
#include<stdlib.h> // For Exit
#include<math.h> // for sin() cos() 

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

//structure declaration
struct MyRGBColor
{
	float fRed;
	float fGreen;
	float fBlue;
};

struct MyRGBColor myRGBColor= { 0.0f,0.0f,0.0f };

struct MyPoint
{
	float x_Axis;
	float y_Axis;
};

struct Triangle
{
	struct MyPoint point1;
	struct MyPoint point2;
	struct MyPoint point3;
};

struct Triangle tleftBottom = { {-1.0f,-0.8f},{-0.8f,-1.0f},{-1.0f,-1.0f} }; 
struct Triangle trightBottom = { {1.0f,-0.8f},{0.8f,-1.0f},{1.0f,-1.0f} };
struct Triangle tlefttop = { {-1.0f,0.8f},{-0.8f,1.0f},{-1.0f,1.0f} }; 
struct Triangle trighttop = { {1.0f,0.8f},{0.8f,1.0f},{1.0f,1.0f} };

// triangle movement
float fMovement = 0.01f;
// letters color
float fColor[] = { 1.0f,0.0f,0.0f };

// 
float fColorLine[] = { 1.0f,0.0f,0.0f };
// for change color of letters after specific amount of count
int count = 0;
// n Vertical line y axis 
float fLineYAxis = -1.0f;

//Global variable declaration
DWORD dwStyle = 0;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) }; // initialization of struct => this work on all type (if we want to initialize all value to 0)
BOOL gbFullscreen = FALSE;
FILE *gpFILE = NULL;

HWND ghwnd = NULL; // g = global handle of window
BOOL gbActive = FALSE; 



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

	// step 7 : - set clear color of window to black (here OpenGL Start)
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
	//function declarations
	void DrawTriangle(void);
	void DrawQuad(void);
	void BirthdayGreeting(void);
	void DrawVerticalLine(float, float,float);
	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawTriangle();
	if (tleftBottom.point1.y_Axis >= 0.0f)
	{
		DrawQuad();
		BirthdayGreeting();
		DrawVerticalLine(-1.0f, 1.0f,0.01f);
		count = count + 1;
	}

	if (count <= 100)
	{
		fColor[0] = 1.0f;
		fColor[1] = 0.0f;
		fColor[2] = 0.0f;
	}
	else if (count <= 200)
	{
		fColor[0] = 1.0f;
		fColor[1] = 0.5f;
		fColor[2] = 0.5f;
	}
	else if (count <= 300)
	{
		fColor[0] = 0.5f;
		fColor[1] = 1.0f;
		fColor[2] = 0.5f;
	}
	else if (count <= 400)
	{
		fColor[0] = 1.0f;
		fColor[1] = 0.0f;
		fColor[2] = 0.5f;
	}
	else if (count <= 500)
	{
		fColor[0] = 1.0f;
		fColor[1] = 0.0f;
		fColor[2] = 1.0f;
	}
	else if (count <= 600)
	{
		fColor[0] = 0.0f;
		fColor[1] = 1.0f;
		fColor[2] = 0.5f;
	}
	else if (count <= 700)
	{
		fColor[0] = 0.0f;
		fColor[1] = 1.0f;
		fColor[2] = 1.0f;
	}
	else 
	{
		count = 0;
	}
	SwapBuffers(ghdc);
}

void update(void)
{
	//code
	// triangle animation
	if (tleftBottom.point1.y_Axis <= 0.0f)
	{
		tleftBottom.point1.y_Axis = tleftBottom.point1.y_Axis + fMovement;
	}

	if (tleftBottom.point2.x_Axis <= 0.0f)
	{
		tleftBottom.point2.x_Axis = tleftBottom.point2.x_Axis + fMovement;
	}

	if (trightBottom.point1.y_Axis <= 0.0f)
	{
		trightBottom.point1.y_Axis = trightBottom.point1.y_Axis + fMovement;
	}

	if (trightBottom.point2.x_Axis >= 0.0f)
	{
		trightBottom.point2.x_Axis = trightBottom.point2.x_Axis - fMovement;
	}

	if (trighttop.point2.x_Axis >= 0.0f)
	{
		trighttop.point2.x_Axis = trighttop.point2.x_Axis - fMovement;
	}

	if (trighttop.point1.y_Axis >= 0.0f)
	{
		trighttop.point1.y_Axis = trighttop.point1.y_Axis - fMovement;
	}

	if (tlefttop.point2.x_Axis <= 0.0f)
	{
		tlefttop.point2.x_Axis = tlefttop.point2.x_Axis + fMovement;
	}

	if (tlefttop.point1.y_Axis >= 0.0f)
	{
		tlefttop.point1.y_Axis = tlefttop.point1.y_Axis - fMovement;
	}

	// vertical line animation
	if (fLineYAxis <= 1.0f)
	{
		fLineYAxis = fLineYAxis + fMovement;
	}
	else
	{
		fLineYAxis = -1.0f;
	}

	if (fColorLine[1] <= 0.8f)
	{
		fColorLine[1] = fColorLine[1] + 0.01f;
	}
	else
	{
		fColorLine[1] = 0.1f;
	}
}

void DrawVerticalLine(float x_StartAxis, float x_EndAxis, float fDifference)
{
	glLineWidth(0.02f);
	for (float iStart = x_StartAxis; iStart <= x_EndAxis; iStart = iStart + fDifference)
	{
		glBegin(GL_LINES);

		glColor3f(fColorLine[0], fColorLine[1], fColorLine[2]);
		glVertex3f(iStart, fLineYAxis, 0.0f);
		glVertex3f(iStart, 0.5f * (fLineYAxis + iStart + 0.3f), 0.0f);
	
		glEnd();

	}
}

void BirthdayGreeting(void)
{
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(fColor[0], fColor[1], fColor[2]);

	//-----H letter Start
	glVertex3f(-0.45f+0.05f, 0.5f, 0.0f);
	glVertex3f(-0.45f + 0.05f, 0.4f, 0.0f);

	glVertex3f(-0.45f + 0.05f, 0.45f, 0.0f);
	glVertex3f(-0.35f + 0.05f, 0.45f, 0.0f);

	glVertex3f(-0.35f + 0.05f, 0.5f, 0.0f);
	glVertex3f(-0.35f + 0.05f, 0.4f, 0.0f);
	//------H letter End

	//------A letter start
	glVertex3f(-0.25f + 0.05f, 0.5f, 0.0f);
	glVertex3f(-0.3f + 0.05f, 0.4f, 0.0f);

	glVertex3f(-0.28f + 0.05f, 0.45f, 0.0f);
	glVertex3f(-0.22f + 0.05f, 0.45f, 0.0f);

	glVertex3f(-0.25f + 0.05f, 0.5f, 0.0f);
	glVertex3f(-0.2f + 0.05f, 0.4f, 0.0f);
	//-----A letter end

	//-----P letter start
	glVertex3f(-0.15f + 0.05f, 0.5f, 0.0f);
	glVertex3f(-0.15f + 0.05f, 0.4f, 0.0f);

	glVertex3f(-0.15f + 0.05f, 0.5f, 0.0f);
	glVertex3f(-0.05f + 0.05f, 0.5f, 0.0f);

	glVertex3f(-0.05f + 0.05f, 0.5f, 0.0f);
	glVertex3f(-0.05f + 0.05f, 0.45f, 0.0f);

	glVertex3f(-0.05f + 0.05f, 0.45f, 0.0f);
	glVertex3f(-0.15f + 0.05f, 0.45f, 0.0f);
	//-----P letter end

	//-----P letter start
	glVertex3f(0.0f + 0.05f, 0.5f, 0.0f);
	glVertex3f(0.0f + 0.05f, 0.4f, 0.0f);

	glVertex3f(0.0f + 0.05f, 0.5f, 0.0f);
	glVertex3f(0.1f + 0.05f, 0.5f, 0.0f);

	glVertex3f(0.1f + 0.05f, 0.5f, 0.0f);
	glVertex3f(0.1f + 0.05f, 0.45f, 0.0f);

	glVertex3f(0.1f + 0.05f, 0.45f, 0.0f);
	glVertex3f(0.0f + 0.05f, 0.45f, 0.0f);
	//-----P letter end

	//-----Y letter start
	glVertex3f(0.15f + 0.05f, 0.5f, 0.0f);
	glVertex3f(0.2f + 0.05f, 0.45f, 0.0f);

	glVertex3f(0.2f + 0.05f, 0.45f, 0.0f);
	glVertex3f(0.25f + 0.05f, 0.5f, 0.0f);

	glVertex3f(0.2f + 0.05f, 0.45f, 0.0f);
	glVertex3f(0.2f + 0.05f, 0.4f, 0.0f);
	//-----Y letter end

	//-----B letter start
	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.55f, 0.2f, 0.0f);

	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.48f, 0.27f, 0.0f);

	glVertex3f(-0.48f, 0.27f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);

	glVertex3f(-0.55f, 0.25f, 0.0f);
	glVertex3f(-0.48f, 0.23f, 0.0f);

	glVertex3f(-0.48f, 0.23f, 0.0f);
	glVertex3f(-0.55f, 0.2f, 0.0f);

	//-----B letter end

	//-----I letter start
	glVertex3f(-0.43f, 0.3f, 0.0f);
	glVertex3f(-0.37f, 0.3f, 0.0f);

	glVertex3f(-0.4f, 0.3f, 0.0f);
	glVertex3f(-0.4f, 0.2f, 0.0f);

	glVertex3f(-0.43f, 0.2f, 0.0f);
	glVertex3f(-0.37f, 0.2f, 0.0f);
	//-----I letter end

	//-----R letter start
	glVertex3f(-0.3f, 0.3f, 0.0f);
	glVertex3f(-0.3f, 0.2f, 0.0f);

	glVertex3f(-0.3f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);

	glVertex3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.25f, 0.0f);

	glVertex3f(-0.2f, 0.25f, 0.0f);
	glVertex3f(-0.3f, 0.25f, 0.0f);

	glVertex3f(-0.3f, 0.25f, 0.0f);
	glVertex3f(-0.2f, 0.2f, 0.0f);
	//-----R letter End

	//-----T letter start
	glVertex3f(-0.15f, 0.3f, 0.0f);
	glVertex3f(-0.05f, 0.3f, 0.0f);

	glVertex3f(-0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, 0.2f, 0.0f);

	//-----T letter end

	//-----H letter start
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);

	glVertex3f(0.0f, 0.25f, 0.0f);
	glVertex3f(0.1f, 0.25f, 0.0f);

	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	//-----H letter end

	//-----D letter start

	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.15f, 0.2f, 0.0f);

	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.22f, 0.3f, 0.0f);

	glVertex3f(0.22f, 0.3f, 0.0f);
	glVertex3f(0.25f, 0.28f, 0.0f);

	glVertex3f(0.25f, 0.28f, 0.0f);
	glVertex3f(0.25f, 0.22f, 0.0f);

	glVertex3f(0.25f, 0.22f, 0.0f);
	glVertex3f(0.22f, 0.2f, 0.0f);

	glVertex3f(0.22f, 0.2f, 0.0f);
	glVertex3f(0.15f, 0.2f, 0.0f);
	//-----D letter end

	//------A letter start
	glVertex3f(0.35f, 0.3f, 0.0f);
	glVertex3f(0.3f, 0.2f, 0.0f);

	glVertex3f(0.32f, 0.25f, 0.0f);
	glVertex3f(0.38f, 0.25f, 0.0f);

	glVertex3f(0.35f, 0.3f, 0.0f);
	glVertex3f(0.4f, 0.2f, 0.0f);
	//-----A letter end

	//-----Y letter start
	glVertex3f(0.45f, 0.3f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);

	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.55f, 0.3f, 0.0f);

	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	//-----Y letter end

	//-----G letter start
	glVertex3f(-0.65f, 0.1f, 0.0f);
	glVertex3f(-0.65f, 0.0f, 0.0f);

	glVertex3f(-0.65f, 0.1f, 0.0f);
	glVertex3f(-0.55f, 0.1f, 0.0f);

	glVertex3f(-0.65f, 0.0f, 0.0f);
	glVertex3f(-0.55f, 0.0f, 0.0f);

	glVertex3f(-0.55f, 0.0f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);

	glVertex3f(-0.55f, 0.05f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	//-----G letter end

	//------A letter start
	glVertex3f(-0.45f, 0.1f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);

	glVertex3f(-0.48f, 0.05f, 0.0f);
	glVertex3f(-0.42f, 0.05f, 0.0f);

	glVertex3f(-0.45f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.0f, 0.0f);
	//-----A letter end

	//-----N letter start
	glVertex3f(-0.35f, 0.1f, 0.0f);
	glVertex3f(-0.35f, 0.0f, 0.0f);

	glVertex3f(-0.35f, 0.1f, 0.0f);
	glVertex3f(-0.25f, 0.0f, 0.0f);

	glVertex3f(-0.25f, 0.1f, 0.0f);
	glVertex3f(-0.25f, 0.0f, 0.0f);
	//-----N letter end

	//-----G letter start
	glVertex3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.0f, 0.0f);

	glVertex3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);

	glVertex3f(-0.2f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.0f, 0.0f);

	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.05f, 0.0f);

	glVertex3f(-0.1f, 0.05f, 0.0f);
	glVertex3f(-0.15f, 0.05f, 0.0f);
	//-----G letter end

	//------A letter start
	glVertex3f(0.0f, 0.1f, 0.0f);
	glVertex3f(-0.05f, 0.0f, 0.0f);

	glVertex3f(-0.02f, 0.05f, 0.0f);
	glVertex3f(0.03f, 0.05f, 0.0f);

	glVertex3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.05f, 0.0f, 0.0f);
	//-----A letter end

	//-----D letter start

	glVertex3f(0.1f, 0.1f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);

	glVertex3f(0.1f, 0.1f, 0.0f);
	glVertex3f(0.18f, 0.1f, 0.0f);

	glVertex3f(0.18f, 0.1f, 0.0f);
	glVertex3f(0.2f, 0.08f, 0.0f);

	glVertex3f(0.2f, 0.08f, 0.0f);
	glVertex3f(0.2f, 0.02f, 0.0f);

	glVertex3f(0.2f, 0.02f, 0.0f);
	glVertex3f(0.18f, 0.0f, 0.0f);

	glVertex3f(0.18f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	//-----D letter end

	//-----H letter start
	glVertex3f(0.25f, 0.1f, 0.0f);
	glVertex3f(0.25f, 0.0f, 0.0f);

	glVertex3f(0.25f, 0.05f, 0.0f);
	glVertex3f(0.35f, 0.05f, 0.0f);

	glVertex3f(0.35f, 0.1f, 0.0f);
	glVertex3f(0.35f, 0.0f, 0.0f);
	//-----H letter End

	//------A letter start
	glVertex3f(0.45f, 0.1f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);

	glVertex3f(0.42f, 0.05f, 0.0f);
	glVertex3f(0.48f, 0.05f, 0.0f);

	glVertex3f(0.45f, 0.1f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	//-----A letter end

	//-----R letter start
	glVertex3f(0.55f, 0.1f, 0.0f);
	glVertex3f(0.55f, 0.0f, 0.0f);

	glVertex3f(0.55f, 0.1f, 0.0f);
	glVertex3f(0.65f, 0.1f, 0.0f);

	glVertex3f(0.65f, 0.1f, 0.0f);
	glVertex3f(0.65f, 0.05f, 0.0f);

	glVertex3f(0.65f, 0.05f, 0.0f);
	glVertex3f(0.55f, 0.05f, 0.0f);

	glVertex3f(0.55f, 0.05f, 0.0f);
	glVertex3f(0.65f, 0.0f, 0.0f);
	//-----R letter End

	glEnd();
}
void DrawQuad(void)
{
	glBegin(GL_QUADS);
	glColor3f(myRGBColor.fRed, myRGBColor.fGreen, myRGBColor.fBlue);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
}

void DrawTriangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	//left bottom triangle
	glVertex3f(tleftBottom.point1.x_Axis, tleftBottom.point1.y_Axis, 0.0f);
	glVertex3f(tleftBottom.point2.x_Axis, tleftBottom.point2.y_Axis, 0.0f);
	glColor3f(0.3f, 0.0f, 0.0f);
	glVertex3f(tleftBottom.point3.x_Axis, tleftBottom.point3.y_Axis, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	//right bottom triangle
	glVertex3f(trightBottom.point1.x_Axis, trightBottom.point1.y_Axis, 0.0f);
	glVertex3f(trightBottom.point2.x_Axis, trightBottom.point2.y_Axis, 0.0f);
	glColor3f(0.3f, 0.0f, 0.0f);
	glVertex3f(trightBottom.point3.x_Axis, trightBottom.point3.y_Axis, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	//left top triangle
	glVertex3f(tlefttop.point1.x_Axis, tlefttop.point1.y_Axis, 0.0f);
	glVertex3f(tlefttop.point2.x_Axis, tlefttop.point2.y_Axis, 0.0f);
	glColor3f(0.3f, 0.0f, 0.0f);
	glVertex3f(tlefttop.point3.x_Axis, tlefttop.point3.y_Axis, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	//right top triangle
	glVertex3f(trighttop.point1.x_Axis, trighttop.point1.y_Axis, 0.0f);
	glVertex3f(trighttop.point2.x_Axis, trighttop.point2.y_Axis, 0.0f);
	glColor3f(0.3f, 0.0f, 0.0f);
	glVertex3f(trighttop.point3.x_Axis, trighttop.point3.y_Axis, 0.0f);

	glEnd();
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



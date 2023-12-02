//// header file inclusion
#include <windows.h> // windows header files
#include <stdio.h>   // for file IO
#include <stdlib.h>  // for exit
#define _USE_MATH_DEFINES
#include <math.h>

#include<vector>
// openGL headers
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SGK_Demo.h"

// Below is the code related to Project

int timer = 0; // use as iterative variable for accessing BazierPoints elements
bool bEnableBazierCamera = false;

bool bSceneHrishikesh = false; // true for hrishikesh scene / false for siddhant scene

std::vector<float> BazierPoints;

std::vector<float> BazierPointsHrishikesh;

float controlPoints[4][3] = {
	{3.5f,0.2f,-3.0f},
	{2.2f,0.8f,1.0f},
	{-0.1f,0.2f,1.0f},
	{-0.1f,0.2f,-0.2f}
	/*{-1.8f,1.6f,-2.0f},
	{-2.3f,-0.5f,1.5f},
	{1.8f,0.3f,2.5f},
	{0.4f,0.4f,-0.5f}*/
};

// for camera
GLfloat gfHorizontal = -0.1f;
GLfloat gfVertical = 0.5f;
GLfloat gfDepth = 1.0f;

// for camera
GLfloat gfCameraHorizontal = 0.0f;
GLfloat gfCameraVertical = 0.3f;
GLfloat gfCameraDepth = -2.0f;

float controlPointsHrishikesh[4][3] = {
	{0.0f,0.5f,1.9f},
	{0.0f,0.3f,1.6f},
	{0.0f,0.25f,1.0f},
	{0.0f,0.2f,0.2f}
	/*{-1.8f,1.6f,-2.0f},
	{-2.3f,-0.5f,1.5f},
	{1.8f,0.3f,2.5f},
	{0.4f,0.4f,-0.5f}*/
};

// struct declaration

struct MyControlPoints
{
	float xAxis;
	float yAxis;
	float zAxis;
};

typedef struct MyControlPoints ControlPoints;

struct MYCOLOR
{
	float fRed;
	float fGreen;
	float fBlue;
};

typedef struct MYCOLOR myColor;

BOOL loadGLTexture(GLuint *, TCHAR[]);
GLuint texture_Screen = 0;
GLuint texture_CityBuildings = 0;
GLuint texture_Road = 0;

extern FILE* gpFILE;

// function declaration
// 4th param minimum angle of circle arc
// 5th param maximum angle of circle arc
// 6th param thickness of circle for 3d effect
// 7th param radius of circle
void SGK_drawCylinder(float,float,float,float,float,float,float,myColor);

//!
//! 1st param :- x coordinate of right top
//! 2nd param :- y coordinate of right top
//! 3rd param :- z coordinate of right top
//! 4th param :- depth 
//! 5th param :- width of figure
//! 6th param :- height of figure
//! 7th param :- struct MYCOLOR (typedef myColor)
//! 

void SGK_drawBox(float, float, float, float, float, float, myColor);

void SGK_drawCity(void);

void SGK_drawRoom(void);

// ======================= for curtains ============================ v
struct Point
{
	float x, y, z;
};

typedef struct Point Point_t;

//variable declaration // for bed and windows curtains 
Point_t p0 = { 0.0f,0.0f,0.0f };
Point_t p1 = { -0.5f,-0.4f,0.0f };
Point_t p2 = { 0.1f,-0.7f,0.0f };
Point_t p3 = { -0.1f,-1.1f,0.0f };

Point_t p4 = { 0.0f,0.0f,0.0f };
Point_t p5 = { -0.5f,-0.4f,0.0f };
Point_t p6 = { 0.5f,-0.7f,0.0f };
Point_t p7 = { 0.0f,-1.1f,0.0f };

int selectedPoint = 0;
float scaleIncrement = 0.01f;

// for left curtains
GLfloat controlPointOne = -0.3f;
GLfloat controlPointTwo = 0.3f;
GLfloat controlPointThree = 0.0f;

// for right curtains
GLfloat controlPointFour = -0.3f;
GLfloat controlPointFive = 0.3f;
GLfloat controlPointSix = 0.0f;

GLfloat cpIncrement = 0.001f;
BOOL cpAnimation = FALSE;

// ======================= for curtains ============================ ^

// variable declaration
GLfloat gfAngle = 0.0f; // angle for rotation 0.0f to 360.0f
GLfloat gfZoom = -6.0f; // for translate 


GLUquadric *quadric;

BOOL switchCameraToMovement = FALSE;

// for camera animation
float clockAnimation = 0.0f;

void displayScene(void)
{
	glLoadIdentity();

	if (!bSceneHrishikesh)
	{
		if ((timer + 3) + 4 < BazierPoints.size())
		{
			timer = timer + 3;
		}
		else
		{
			timer = 0;
			//bEnableBazierCamera = false;
		}
	}
	else
	{
		if ((timer + 3) + 8 < BazierPointsHrishikesh.size())
		{
			timer = timer + 3;
		}
		else
		{
			//timer = 0;
		}
	}

	if (!bSceneHrishikesh)
	{
		if (bEnableBazierCamera)
		{
			gluLookAt(gfHorizontal, gfVertical, gfDepth, gfCameraHorizontal, gfCameraVertical, gfCameraDepth, 0.0f, 1.0f, 0.0f);
		}
		else
		{
			gluLookAt(BazierPoints[timer], BazierPoints[timer + 1], BazierPoints[timer + 2], BazierPoints[(timer + 3)], BazierPoints[(timer + 3) + 1], BazierPoints[(timer + 3) + 2], 0.0f, 1.0f, 0.0f);
		}
	}
	else
	{
		if (bEnableBazierCamera)
		{
			gluLookAt(gfHorizontal, gfVertical, gfDepth, gfCameraHorizontal, gfCameraVertical, gfCameraDepth, 0.0f, 1.0f, 0.0f);
		}
		else
		{
			gluLookAt(BazierPointsHrishikesh[timer], BazierPointsHrishikesh[timer + 1], BazierPointsHrishikesh[timer + 2], BazierPointsHrishikesh[(timer + 3)], BazierPointsHrishikesh[(timer + 3) + 1], BazierPointsHrishikesh[(timer + 3) + 2], 0.0f, 1.0f, 0.0f);
		}
	}


	if (switchCameraToMovement)
	{
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(gfCameraHorizontal, gfCameraVertical, gfCameraDepth);
		glEnd();
		glPointSize(1.0f);
	}

	SGK_drawCity();

}

void updateScene(void)
{
	gfAngle = gfAngle + 0.5f;
	if (gfAngle >= 360.0f)
	{
		gfAngle = 0.0f;
	}

	clockAnimation = clockAnimation - 0.1f;
	if (clockAnimation <= 0.0f)
	{
		clockAnimation = 360.0f;
	}

	if (cpAnimation == FALSE)
	{
		// for right curtain
		if (controlPointFour <= -0.2f)
		{
			controlPointFour = controlPointFour + cpIncrement;
			p1.x = controlPointFour;
		}
		if (controlPointFive <= 0.2f)
		{
			controlPointFive = controlPointFive + cpIncrement;
			p3.z = controlPointFive;
			p2.z = controlPointFive;
			p1.z = controlPointFive;
		}

		// for left curtain
		if (controlPointOne <= -0.2f)
		{
			controlPointOne = controlPointOne + cpIncrement;
			p5.x = controlPointOne;
		}
		if (controlPointThree <= 0.2f)
		{
			controlPointThree = controlPointThree + cpIncrement;
			p7.z = controlPointThree;
			p5.z = controlPointThree;
			p6.z = controlPointThree;
		}
		if (p7.x >= -0.2f)
		{
			p7.x = p7.x - cpIncrement;
		}
		if (controlPointTwo >= 0.2f)
		{
			controlPointTwo = controlPointTwo - cpIncrement;
			p6.x = controlPointTwo;
 		}
		else
		{
			cpAnimation = TRUE;
		}

		if (p2.x >= -0.3f)
		{
			p2.x = p2.x - cpIncrement; // for left curtains
			p3.x = p3.x + (cpIncrement * 1.5f);
		}
		
	}
	else
	{
		// for right curtains
		if (controlPointFour >= -0.3f)
		{
			controlPointFour = controlPointFour - cpIncrement;
			p1.x = controlPointFour;
		}
		if (controlPointFive >= 0.2f)
		{
			controlPointFive = controlPointFive - cpIncrement;
			p3.z = controlPointFive;
			p2.z = controlPointFive;
			p1.z = controlPointFive;

			
		}
	

		//for left curtain
		if (controlPointOne >= -0.3f)
		{
			controlPointOne = controlPointOne - cpIncrement;
			p5.x = controlPointOne;
		}
		if (controlPointThree >= -0.2f)
		{
			controlPointThree = controlPointThree - cpIncrement;
			p7.z = controlPointThree;
			p5.z = controlPointThree;
			p6.z = controlPointThree;

		}
		if (p7.x <= 0.1f)
		{
			p7.x = p7.x + cpIncrement;
		}
		if (controlPointTwo <= 0.3f)
		{
			controlPointTwo = controlPointTwo + cpIncrement;
			p6.x = controlPointTwo;
		}
		else
		{
			cpAnimation = FALSE;
		}
		
		if (p2.x <= 0.1f)
		{
			p2.x = p2.x + cpIncrement; // for left curtains
			p3.x = p3.x - (cpIncrement * 1.5f);
		}
	}
}
int initializeScene(void)
{
	BOOL bResult;

	// create texture
	bResult = loadGLTexture(&texture_Screen, MAKEINTRESOURCE(MY_MOBILE_SCREEN));
	if (bResult == FALSE)
	{
		fprintf(gpFILE, "load of screen texture is Failed.\n");
		return(-6);
	}

	bResult = loadGLTexture(&texture_CityBuildings, MAKEINTRESOURCE(CITY_BUILDINGS));
	if (bResult == FALSE)
	{
		fprintf(gpFILE, "load of screen texture is Failed.\n");
		return(-7);
	}

	bResult = loadGLTexture(&texture_Road, MAKEINTRESOURCE(NIGHT_ROAD));
	if (bResult == FALSE)
	{
		fprintf(gpFILE, "load of screen texture is Failed.\n");
		return(-9);
	}

	// enable texture
	glEnable(GL_TEXTURE_2D);

	quadric = gluNewQuadric();

	
		if (bSceneHrishikesh)
		{
			for (float t = 0.0f; t <= 1.0f; t = t + 0.005f)
			{
				float x = pow((1 - t), 3) * controlPointsHrishikesh[0][0] + 3 * pow((1 - t), 2) * t * controlPointsHrishikesh[1][0] + 3 * (1 - t) * pow(t, 2) * controlPointsHrishikesh[2][0] + pow(t, 3) * controlPointsHrishikesh[3][0];
				float y = pow((1 - t), 3) * controlPointsHrishikesh[0][1] + 3 * pow((1 - t), 2) * t * controlPointsHrishikesh[1][1] + 3 * (1 - t) * pow(t, 2) * controlPointsHrishikesh[2][1] + pow(t, 3) * controlPointsHrishikesh[3][1];
				float z = pow((1 - t), 3) * controlPointsHrishikesh[0][2] + 3 * pow((1 - t), 2) * t * controlPointsHrishikesh[1][2] + 3 * (1 - t) * pow(t, 2) * controlPointsHrishikesh[2][2] + pow(t, 3) * controlPointsHrishikesh[3][2];

				BazierPointsHrishikesh.push_back(x);
				BazierPointsHrishikesh.push_back(y);
				BazierPointsHrishikesh.push_back(z);
			}
		}
		else
		{
			for (float t = 0.0f; t <= 1.0f; t = t + 0.002f)
			{
				float x = pow((1 - t), 3) * controlPoints[0][0] + 3 * pow((1 - t), 2) * t * controlPoints[1][0] + 3 * (1 - t) * pow(t, 2) * controlPoints[2][0] + pow(t, 3) * controlPoints[3][0];
				float y = pow((1 - t), 3) * controlPoints[0][1] + 3 * pow((1 - t), 2) * t * controlPoints[1][1] + 3 * (1 - t) * pow(t, 2) * controlPoints[2][1] + pow(t, 3) * controlPoints[3][1];
				float z = pow((1 - t), 3) * controlPoints[0][2] + 3 * pow((1 - t), 2) * t * controlPoints[1][2] + 3 * (1 - t) * pow(t, 2) * controlPoints[2][2] + pow(t, 3) * controlPoints[3][2];

				BazierPoints.push_back(x);
				BazierPoints.push_back(y);
				BazierPoints.push_back(z);
			}
		}
		
	return(0);
}
void uninitializeScene(void)
{
	if (quadric)
	{
		gluDeleteQuadric(quadric);
		quadric = NULL;
	}

	if (texture_Screen)
	{
		glDeleteTextures(1, &texture_Screen);
		texture_Screen = 0;
	}
	
}

BOOL loadGLTexture(GLuint *texture, TCHAR imageResourceID[])
{
	//local variable declaration
	HBITMAP hBitmap = NULL;
	BITMAP bmp;

	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		fprintf(gpFILE, "LoadImage() Failed.\n");
		return(FALSE);
	}

	// get Image Data
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	// create openGL texture
	glGenTextures(1, texture);

	// bind to the generated texture
	glBindTexture(GL_TEXTURE_2D, *texture);

	// decide image pixel alignment and unpacking 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	// set texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// create multiple mipmap images
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);

	// unBind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// delete bitmap object
	DeleteObject(hBitmap);

	hBitmap = NULL;

	return(TRUE);
}

void SGK_drawCity(void)
{
	glBindTexture(GL_TEXTURE_2D, texture_CityBuildings);

	glColor3f(0.5f,0.5f,0.5f);

	glBegin(GL_QUADS);
	//Front Face
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.0f, 4.0f, 1.0f);//right top

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.01f, 4.0f, 1.0f);//left top

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.01f, -1.5f, 1.0f);//left bottom

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.0f, -1.5f, 1.0f);//right bottom

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, texture_Road);

	glColor3f(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);

	glBegin(GL_QUADS);

	//bottom side Face
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.0f, -0.98f, -2.0f);//right top

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.01f, -0.98f, -2.0f);//left top
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.01f, -0.98f, 3.0f);//left bottom

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(6.0f, -0.98f, 3.0f);//right bottom

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	SGK_drawRoom();
}

void SGK_drawRoom(void)
{
	// function declaration
	void SGK_drawBed(void);
	void SGK_drawWindow(void);
	void SGK_drawDoor(void);
	void SGK_drawCupboard(void);
	void SGK_drawSaraswati(void);

	// ROOM Outside
	glBegin(GL_QUADS);
	//Front Face
	glColor3f(80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f); 
	glVertex3f(2.01f, 2.01f, 3.0f);//right top
	glVertex3f(-2.05f, 2.01f, 3.0f);//left top
	glColor3f(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f);
	glVertex3f(-2.05f, -1.001f, 3.0f);//left bottom
	glVertex3f(2.01f, -1.001f, 3.0f);//right bottom

	//back Face
	glColor3f(80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f);
	glVertex3f(2.01f, 2.01f, -2.01f);//right top
	glVertex3f(-2.05f, 2.01f, -2.01f);//left top
	glColor3f(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f);
	glVertex3f(-2.05f, -1.001f, -2.01f);//left bottom
	glVertex3f(2.01f, -1.001f, -2.01f);//right bottom

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_Road);

	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_QUADS);

	//right side 1

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.01f, 3.01f, -2.01f);//right top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.01f, 3.01f, -0.7f);//left top
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.01f, -1.001f, -0.7f);//left bottom
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.01f, -1.001f, -2.01f);//right bottom
		
	//right side 2
	
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.01f, 3.01f, 0.7f);//right top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.01f, 3.01f, 3.0f);//left top
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.01f, -1.001f, 3.0f);//left bottom
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.01f, -1.001f, 0.7f);//right bottom

	//right side top
	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.01f, 3.01f, -0.7f);//right top
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.01f, 3.01f, 0.7f);//left top
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.01f, 1.0f, 0.7f);//left bottom
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.01f, 1.0f, -0.7f);//right bottom

	//right side bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.01f, 0.0f, -0.7f);//right top
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.01f, 0.0f, 0.7f);//left top
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.01f, -1.0f, 0.7f);//left bottom
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.01f, -1.0f, -0.7f);//right bottom

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glBegin(GL_QUADS);
	//left side Face
	glColor3f(80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f);
	glVertex3f(-2.05f, 2.01f, 3.0f);//right top
	glVertex3f(-2.05f, 2.01f, -2.01f);//left top
	glColor3f(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f);
	glVertex3f(-2.05f, -1.001f, -2.01f);//left bottom
	glVertex3f(-2.05f, -1.001f, 3.0f);//right bottom

	//bottom side Face
	glColor3f(80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f);
	glVertex3f(2.01f, -1.001f, -2.01f);//right top
	glVertex3f(-2.05f, -1.001f, -2.01f);//left top
	glColor3f(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f);
	glVertex3f(-2.05f, -1.001f, 3.0f);//left bottom
	glVertex3f(2.01f, -1.001f, 3.0f);//right bottom

	//top side Face
	glColor3f(80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f);
	glVertex3f(2.01f, 2.01f, -2.01f);//right top
	glVertex3f(-2.05f, 2.01f, -2.01f);//left top
	glColor3f(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f);
	glVertex3f(-2.05f, 2.01f, 3.0f);//left bottom
	glVertex3f(2.01f, 2.01f, 3.0f);//right bottom

	glEnd();

	// ROOM inside 
	glBegin(GL_QUADS);
	//Front Face
	glColor3f(210.0f / 255.0f, 180.0f / 255.0f, 222.0f / 255.0f); // purple color 
	glVertex3f(2.0f, 2.0f, 2.0f);//right top
	glVertex3f(-2.0f, 2.0f, 2.0f);//left top
	glColor3f(190.0f / 255.0f, 160.0f / 255.0f, 202.0f / 255.0f); // purple color shade
	glVertex3f(-2.0f, -1.0f, 2.0f);//left bottom
	glVertex3f(2.0f, -1.0f, 2.0f);//right bottom

	//back Face
	glColor3f(208.0f / 255.0f, 211.0f / 255.0f, 212.0f / 255.0f);
	glVertex3f(2.0f, 2.0f, -2.0f);//right top
	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(-2.0f, 2.0f, -2.0f);//left top
	glVertex3f(-2.0f, -1.0f, -2.0f);//left bottom
	glColor3f(208.0f / 255.0f, 211.0f / 255.0f, 212.0f / 255.0f);
	glVertex3f(2.0f, -1.0f, -2.0f);//right bottom

	//right side
	
	//right side 1

	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(2.0f, 2.01f, -2.01f);//right top
	glVertex3f(2.0f, 2.01f, -0.7f);//left top
	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(2.0f, -1.001f, -0.7f);//left bottom
	glVertex3f(2.0f, -1.001f, -2.01f);//right bottom

	//right side 2
	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(2.0f, 2.01f, 0.7f);//right top
	glVertex3f(2.0f, 2.01f, 2.01f);//left top
	glColor3f(208.0f / 255.0f, 211.0f / 255.0f, 212.0f / 255.0f);
	glVertex3f(2.0f, -1.001f, 2.01f);//left bottom
	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(2.0f, -1.001f, 0.7f);//right bottom

	//right side top
	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(2.0f, 2.0f, -0.7f);//right top
	glVertex3f(2.0f, 2.0f, 0.7f);//left top
	glVertex3f(2.0f, 1.0f, 0.7f);//left bottom
	glVertex3f(2.0f, 1.0f, -0.7f);//right bottom

	//right side bottom
	glVertex3f(2.0f, 0.0f, -0.7f);//right top
	glVertex3f(2.0f, 0.0f, 0.7f);//left top
	glVertex3f(2.0f, -1.0f, 0.7f);//left bottom
	glVertex3f(2.0f, -1.0f, -0.7f);//right bottom

	//left side Face
	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(-2.0f, 2.0f, 2.0f);//right top
	glColor3f(208.0f / 255.0f, 211.0f / 255.0f, 212.0f / 255.0f);
	glVertex3f(-2.0f, 2.0f, -2.0f);//left top
	glVertex3f(-2.0f, -1.0f, -2.0f);//left bottom
	glColor3f(178.0f / 255.0f, 181.0f / 255.0f, 182.0f / 255.0f);
	glVertex3f(-2.0f, -1.0f, 2.0f);//right bottom

	//bottom side Face
	glColor3f(166.0f / 255.0f, 172.0f / 255.0f, 175.0f / 255.0f);
	glVertex3f(2.0f, -1.0f, -2.0f);//right top
	glVertex3f(-2.0f, -1.0f, -2.0f);//left top
	glColor3f(86.0f / 255.0f, 101.0f / 255.0f, 115.0f / 255.0f);
	glVertex3f(-2.0f, -1.0f, 2.0f);//left bottom
	glVertex3f(2.0f, -1.0f, 2.0f);//right bottom

	//top side Face
	glColor3f(247.0f / 255.0f, 249.0f / 255.0f, 249.0f / 255.0f);
	glVertex3f(2.0f, 2.0f, -2.0f);//right top
	glVertex3f(-2.0f, 2.0f, -2.0f);//left top
	glVertex3f(-2.0f, 2.0f, 2.0f);//left bottom
	glVertex3f(2.0f, 2.0f, 2.0f);//right bottom

	glEnd();

	// scurting 
	glBegin(GL_QUADS);
	//right side scurting
	glColor3f(166.0f / 255.0f, 172.0f / 255.0f, 175.0f / 255.0f);
	glVertex3f(1.99f, -0.9f, -2.0f);//right top
	glVertex3f(1.99f, -0.9f, 2.0f);//left top
	glColor3f(146.0f / 255.0f, 152.0f / 255.0f, 165.0f / 255.0f);
	glVertex3f(1.99f, -1.0f, 2.0f);//left bottom
	glVertex3f(1.99f, -1.0f, -2.0f);//right bottom

	// left side scurting
	glColor3f(166.0f / 255.0f, 172.0f / 255.0f, 175.0f / 255.0f);
	glVertex3f(-1.99f, -0.9f, 2.0f);//right top
	glVertex3f(-1.99f, -0.9f, -2.0f);//left top
	glColor3f(146.0f / 255.0f, 152.0f / 255.0f, 165.0f / 255.0f);
	glVertex3f(-1.99f, -1.0f, -2.0f);//left bottom
	glVertex3f(-1.99f, -1.0f, 2.0f);//right bottom

	// back side scurting
	glColor3f(166.0f / 255.0f, 172.0f / 255.0f, 175.0f / 255.0f);
	glVertex3f(1.99f, -0.9f, -1.99f);//right top
	glVertex3f(-1.99f, -0.9f, -1.99f);//left top
	glColor3f(146.0f / 255.0f, 152.0f / 255.0f, 165.0f / 255.0f);
	glVertex3f(-1.99f, -1.0f, -1.99f);//left bottom
	glVertex3f(1.99f, -1.0f, -1.99f);//right bottom

	// front side scurting 
	glColor3f(166.0f / 255.0f, 172.0f / 255.0f, 175.0f / 255.0f);
	glVertex3f(1.99f, -0.9f, 1.99f);//right top
	glVertex3f(-1.99f, -0.9f, 1.99f);//left top
	glColor3f(146.0f / 255.0f, 152.0f / 255.0f, 165.0f / 255.0f);
	glVertex3f(-1.99f, -1.0f, 1.99f);//left bottom
	glVertex3f(1.99f, -1.0f, 1.99f);//right bottom

	glEnd();

	// front wall texture
	glBegin(GL_QUADS);
	for (float x = -1.9f; x <= 2.0f; x = x + 0.2f)
	{
		for (float y = -0.9f; y <= 1.9; y = y + 0.1f)
		{

			glColor3f(145.0f / 255.0f, 6.0f / 255.0f, 173.0f / 255.0f); // purple color shade
			glVertex3f(x, y + 0.15f, 1.999f);

			glColor3f(172.0f / 255.0f, 98.0 / 255.0f, 203.0f / 255.0f); // purple color shade
			glVertex3f(x - 0.09f, y, 1.999f);
			glVertex3f(x, y+ 0.05f, 1.999f);
			glVertex3f(x + 0.09f, y, 1.999f);

		}
	}
	glEnd();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.01f);
	SGK_drawBed();
	glPopMatrix();

	SGK_drawWindow();

	glPushMatrix();
	glScalef(1.0f, 1.0f, 0.7f);
	SGK_drawDoor();
	glPopMatrix();

	SGK_drawCupboard();

	glPushMatrix();
	glTranslatef(0.0f, 0.65f, -1.9f);
	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	SGK_drawSaraswati();
	glPopMatrix();
	glPopMatrix();

}

void SGK_drawSaraswati(void)
{
	//1st param xAxis of center of a circle
	// 2nd param yAxis of center of a circle
	// 3rd param zAxis of center of a circle
	// 4th param radius of a circle
	void SGK_drawCircle(float, float, float,float);
	// 1st param x axis of apex of triangle
	// 2nd param y axis of apex of triangle 
	// 3rd param z axis of apex of triangle
	void SGK_drawTriangle(float, float, float);

	// 1st param control point 1 for quadratic curve
	// 2nd param control point 2 for quadratic curve
	// 3rd param control point 3 for quadratic curve
	void SGK_drawQuadraticCurve(ControlPoints, ControlPoints, ControlPoints);

	// 1st param control point 1 for cubic curve
	// 2nd param control point 2 for cubic curve
	// 3rd param control point 3 for cubic curve
	// 4th param control point 4 for cubic curve
	void SGK_drawCubicCurve(ControlPoints, ControlPoints, ControlPoints,ControlPoints);

	// variable declarations
	float xAxisStart, xAxisEnd, yAxisStart, yAxis; // for draw horrizontal lines
	float x, y; // get center from circle
	float xBegin = -0.18f;

	ControlPoints cpBazierCurve1, cpBazierCurve2, cpBazierCurve3, cpBazierCurve4;

	myColor colorBlack = { 0.0f,0.0f,0.0f };
	myColor colorBrown = {150.0f/255.0f, 75.0f/255.0f,0.0f};
	myColor colorRed = { 1.0f,0.0f,0.0f };
	myColor colorYellow = { 1.0f,1.0f,0.0f };
	// for drawing paati
	SGK_drawBox(0.3f, 0.35f, -0.011f, 0.019f, 0.6f, 0.7f, colorBlack);
	SGK_drawBox(0.3f, 0.37f, -0.013f, 0.025f, 0.6f, 0.02f, colorBrown);
	SGK_drawBox(0.3f, -0.35f, -0.013f, 0.025f, 0.6f, 0.02f, colorBrown);
	SGK_drawBox(0.32f, 0.37f, -0.013f, 0.025f, 0.02f, 0.74f, colorBrown);
	SGK_drawBox(-0.3f, 0.37f, -0.013f, 0.025f, 0.02f, 0.74f, colorBrown);

	// for drawing Gandha

	SGK_drawCylinder(0.1f, -0.2f, 0.011f, 0.0f, 360.0f, 0.001f, 0.01f, colorRed);
	SGK_drawCylinder(0.13f, -0.2f, 0.011f, 0.0f, 360.0f, 0.001f, 0.01f, colorYellow);

	glColor3f(1.0f, 1.0f, 1.0f);
	for (float xAxis = -0.17f,yAxis =  (0.05f - 0.06f),xAxisEnd = 0.21; xAxis <= 0.2f; xAxis = xAxis + 0.06f,yAxis = yAxis - 0.06f,xAxisEnd = xAxisEnd - 0.035f)
	{
		
		SGK_drawCircle(xAxis, 0.2f, 0.01f, 0.01f);



		x = xAxis + 0.01f * sin((90.0f * M_PI) / 180.0f);
		y = 0.2f + 0.01f * cos((90.0f * M_PI) / 180.0f);


		// for starting curve below circle
		cpBazierCurve1.xAxis = x;
		cpBazierCurve1.yAxis = y;
		cpBazierCurve1.zAxis = 0.01f;

		cpBazierCurve2.xAxis = xAxis + 0.005f;
		cpBazierCurve2.yAxis = 0.175f;
		cpBazierCurve2.zAxis = 0.01f;

		cpBazierCurve3.xAxis = xAxis - 0.01f;
		cpBazierCurve3.yAxis = 0.15f;
		cpBazierCurve3.zAxis = 0.01f;

		SGK_drawQuadraticCurve(cpBazierCurve1,cpBazierCurve2,cpBazierCurve3);

		// for starting curve above circle
		cpBazierCurve1.xAxis = xAxis - 0.01f;
		cpBazierCurve1.yAxis = 0.15f;
		cpBazierCurve1.zAxis = 0.01f;

		cpBazierCurve2.xAxis = xAxis - 0.07f;
		cpBazierCurve2.yAxis = 0.24f;
		cpBazierCurve2.zAxis = 0.01f;

		cpBazierCurve3.xAxis = xAxis;
		cpBazierCurve3.yAxis = 0.28f;
		cpBazierCurve3.zAxis = 0.01f;

		cpBazierCurve4.xAxis = xAxis + 0.01f;
		cpBazierCurve4.yAxis = 0.26f;
		cpBazierCurve4.zAxis = 0.01f;

		SGK_drawCubicCurve(cpBazierCurve1, cpBazierCurve2, cpBazierCurve3, cpBazierCurve4);

	}

	
		for (float y = 0.15f, xAxisStart = -0.18f; y >= -0.24f; y = y - 0.06f, xAxisStart = xAxisStart + 0.03f)
		{
			for (float x = xAxisStart; x <= (0.018f-xAxisStart); x = x + 0.06f)
			{
				SGK_drawTriangle(x, y, 0.01f);
			}
		}
	

	
}

void SGK_drawCubicCurve(ControlPoints cp1, ControlPoints cp2, ControlPoints cp3, ControlPoints cp4)
{
	// variable declaration
	float x, y, z;
	// parametric equation of Cubic Bazier Curve B(t) = (1-t)^3 * P0 + 3 * (1-t)^2 * t * P1 + 3 * (1-t) * t^2 * p2 + t^3 + P3
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
	{
		x = pow((1 - t), 3) * cp1.xAxis + 3 * pow((1 - t), 2) * t * cp2.xAxis + 3 * (1 - t) * pow(t, 2) * cp3.xAxis + pow(t, 3) * cp4.xAxis;
		y = pow((1 - t), 3) * cp1.yAxis + 3 * pow((1 - t), 2) * t * cp2.yAxis + 3 * (1 - t) * pow(t, 2) * cp3.yAxis + pow(t, 3) * cp4.yAxis;
		z = pow((1 - t), 3) * cp1.zAxis + 3 * pow((1 - t), 2) * t * cp2.zAxis + 3 * (1 - t) * pow(t, 2) * cp3.zAxis + pow(t, 3) * cp4.zAxis;

		
		glVertex3f(x, y, z);
	}

	glEnd();
}

void SGK_drawQuadraticCurve(ControlPoints cp1, ControlPoints cp2, ControlPoints cp3)
{
	// variable declaration
	float x, y, z;
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	for (float t = 0.0f; t <= 1.0f; t = t + 0.001f)
	{

		 x = pow((1 - t), 2) * cp1.xAxis + 2 * (1 - t) * t * cp2.xAxis + pow(t, 2) * cp3.xAxis;
		 y = pow((1 - t), 2) * cp1.yAxis + 2 * (1 - t) * t * cp2.yAxis + pow(t, 2) * cp3.yAxis;
		 z = pow((1 - t), 2) * cp1.zAxis + 2 * (1 - t) * t * cp2.zAxis + pow(t, 2) * cp3.zAxis;
		
		glVertex3f(x, y, z);
	}


	glEnd();

}

void SGK_drawTriangle(float xAxis, float yAxis, float zAxis)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(xAxis,yAxis,zAxis);
	glVertex3f(xAxis - 0.03f, yAxis-0.06f, zAxis);
	glVertex3f(xAxis + 0.03f, yAxis - 0.06f, zAxis);
	glEnd();

}

void SGK_drawCircle(float xAxis, float yAxis, float zAxis, float radius)
{
	float x, y;
	glBegin(GL_LINE_STRIP);
	for (float fAngle = 0.0f; fAngle <= 360.0f; fAngle = fAngle + 0.01f)
	{
		x = xAxis + radius * sin((fAngle * M_PI) / 180.0f);
		y = yAxis + radius * cos((fAngle * M_PI) / 180.0f);

		glVertex3f(x, y, zAxis);
	}
	glEnd();
}

void SGK_drawCupboard(void)
{
	myColor cupBoardColor, cupboardHandle;

	cupBoardColor.fRed = 204.0f / 255.0f;
	cupBoardColor.fGreen = 204.0f / 255.0f;
	cupBoardColor.fBlue = 255.0f / 255.0f;

	cupboardHandle.fRed = 33.0f / 255.0f;
	cupboardHandle.fGreen = 47.0f / 255.0f;
	cupboardHandle.fBlue = 61.0f / 255.0f;

	SGK_drawBox(-0.8f, 0.7f, 1.2f, 0.8f, 1.1f, 1.7f, cupBoardColor);

	glLineWidth(3.0f);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINE_LOOP);

	glColor3f(33.0f / 255.0f, 47.0f / 255.0f, 61.0f / 255.0f);
	glVertex3f(-0.8f, 0.7f, 1.2f);
	glVertex3f(-1.9f, 0.7f, 1.2f);
	glVertex3f(-1.9f, -0.99f, 1.2f);
	glVertex3f(-0.8f, -0.99f, 1.2f);

	glEnd();

	glBegin(GL_LINES);

	glColor3f(33.0f / 255.0f, 47.0f / 255.0f, 61.0f / 255.0f);
	glVertex3f(-1.35f, 0.7f, 1.199f);
	glVertex3f(-1.35f, -0.99f, 1.199f);

	glEnd();

	glDisable(GL_LINE_SMOOTH);
	glLineWidth(1.0f);

	//handle
	SGK_drawBox(-1.25, 0.0f, 1.18f, 0.05f, 0.05f, 0.1f, cupboardHandle);
	SGK_drawBox(-1.4, 0.0f, 1.18f, 0.05f, 0.05f, 0.1f, cupboardHandle);
}
void SGK_drawDoor(void)
{
	//variable declaration
	myColor doorColor,doorColumn,doorHandle;
	doorColor.fRed = 236.0f / 255.0f;
	doorColor.fGreen = 240.0f / 255.0f;
	doorColor.fBlue = 241.0f / 255.0f;

	doorColumn.fRed = 33.0f / 255.0f;
	doorColumn.fGreen = 47.0f / 255.0f;
	doorColumn.fBlue = 61.0f / 255.0f;

	doorHandle.fRed = 255.0f/255.0f;
	doorHandle.fGreen = 215.0f/255.0f;
	doorHandle.fBlue = 0.0f;
	
	SGK_drawBox(-1.98f, 1.2f, -1.0f, 1.6f, 0.01f, 2.2f, doorColor);
	SGK_drawBox(-1.985f, 1.3f, -1.1f, 1.8f, 0.01f, 2.3f, doorColumn);

	glPushMatrix();
	glTranslatef(-1.96f, 0.0f, -0.8f);
	glColor3f(doorHandle.fRed, doorHandle.fGreen, doorHandle.fBlue);
	gluSphere(quadric, 0.04f, 20, 20);
	glPopMatrix();

	glLineWidth(4.0f);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);

	glColor3f(33.0f / 255.0f, 47.0f / 255.0f, 61.0f / 255.0f);
	glVertex3f(-1.979f, 1.1f, 0.5f);//right top
	glVertex3f(-1.979f, 1.1f, -0.9f);//left top

	glVertex3f(-1.979f, 1.1f, -0.9f);//left top
	glVertex3f(-1.979f, -0.9f, -0.9f);//left bottom

	glVertex3f(-1.979f, 1.1f, 0.5f);//right top
	glVertex3f(-1.979f, -0.9f, 0.5f);//right bottom

	glVertex3f(-1.979f, -0.9f, -0.9f);//left bottom
	glVertex3f(-1.979f, -0.9f, 0.5f);//right bottom

	glColor3f(189.0f / 255.0f, 195.0f / 255.0f, 199.0f / 255.0f);
	glVertex3f(-1.979f, 1.0f, 0.3f);//right top
	glVertex3f(-1.979f, 1.0f, -0.7f);//left top

	glVertex3f(-1.979f, 1.0f, -0.7f);//left top
	glVertex3f(-1.979f, -0.8f, -0.7f);//left bottom

	glVertex3f(-1.979f, 1.0f, 0.3f);//right top
	glVertex3f(-1.979f, -0.8f, 0.3f);//right bottom

	glVertex3f(-1.979f, -0.8f, -0.7f);//left bottom
	glVertex3f(-1.979f, -0.8f, 0.3f);//right bottom

	glEnd();
	glDisable(GL_LINE_SMOOTH);
	glLineWidth(1.0f);
}

void SGK_drawWindow(void)
{
	//function declaration
	void SGK_drawCurtains(void);
	myColor myCurtainRodColor;
	myColor myGrillColor = {0.2f,0.2f,0.2f};

	myCurtainRodColor.fRed = 80.0f / 255.0f;
	myCurtainRodColor.fGreen = 80.0f / 255.0f;
	myCurtainRodColor.fBlue = 80.0f / 255.0f;

	SGK_drawBox(2.01f, 0.02f, -0.7f, 1.4f, 0.03f, 0.02f, myCurtainRodColor);
	SGK_drawBox(2.01f, 1.0f, -0.7f, 1.4f, 0.03f, 0.02f, myCurtainRodColor);
	SGK_drawBox(2.01f, 0.98f, -0.7f, 0.03f, 0.03f, 0.96f, myCurtainRodColor);
	SGK_drawBox(2.01f, 0.98f, 0.67f, 0.03f, 0.03f, 0.96f, myCurtainRodColor);

	SGK_drawBox(2.0f, 1.05f, -0.8f, 0.05f, 0.15f, 0.1f, myCurtainRodColor);
	SGK_drawBox(2.0f, 1.05f, 0.75f, 0.05f, 0.15f, 0.1f, myCurtainRodColor);
	glPushMatrix();
	glTranslatef(1.9f, 1.0f, 0.0f);
	SGK_drawCylinder(0.0f, 0.0f, 0.8f, 0.0f, 360.0f, 1.6f, 0.01f, myCurtainRodColor);
	glColor3f(80.0f / 255.0f, 80.0f / 255.0f, 80.0f / 255.0f);
	SGK_drawCurtains();
	glPopMatrix();

	// Window Grills
	// vertical grills
	for (float z = -0.6f; z <= 0.6f; z = z + 0.1f)
	{
		for (float y = 0.89; y >= 0.1f; y = y - 0.2f)
		{
			SGK_drawBox(2.0f, y, z, 0.01f, 0.01f, 0.19f, myGrillColor);
		}
	}
	// horrizontal grills
	for (float y = 0.9; y >= 0.1f; y = y - 0.2f)
	{
		SGK_drawBox(2.0f, y, -0.67f, 1.4f, 0.01f, 0.01f, myGrillColor);
	}

}

void SGK_drawCurtains(void)
{
	// function declaration
	// 1st param x Axis of start of line
	// 2nd param y Axis of start of line
	// 3rd param z Axis of start of line
	void SGK_drawCurveLeft(float, float, float);

	// 1st param x Axis of start of line
	// 2nd param y Axis of start of line
	// 3rd param z Axis of start of line
	void SGK_drawCurveRight(float, float, float);

	// 1st param xAxis of start of curve line
	// 2nd param yAxis of start of curve line
	// 3rd param zAxis of start of curve line
	// 4th param xAxis for control point to make curve
	void SGK_drawQuadraticCurveVertical(float,float,float,float);

	for (float z = -0.75; z <= -0.35f; z = z + 0.1f)
	{
		//variable declaration
		float point1_x = 0.0f;
		float point1_y = 0.0f;
		float point1_z = z;

		float point2_x = -0.2f;
		float point2_y = 0.0f;
		float point2_z = z+0.05f;

		float point3_x = 0.0f;
		float point3_y = 0.0f;
		float point3_z = z+0.1f;

		glEnable(GL_LINE_SMOOTH);
		for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
		{

			float x = pow((1 - t), 2) * point1_x + 2 * (1 - t) * t * point2_x + pow(t, 2) * point3_x;
			float y = pow((1 - t), 2) * point1_y + 2 * (1 - t) * t * point2_y + pow(t, 2) * point3_y;
			float z = pow((1 - t), 2) * point1_z + 2 * (1 - t) * t * point2_z + pow(t, 2) * point3_z;

			if ((t <= 0.2f && t >= 0.0f))
			{
				glColor3f(204.0f / 255.0f, 204.0f / 255.0f, 255.0f / 255.0f);
			}
			else if ((t <= 0.4f && t >= 0.2f))
			{
				glColor3f(194.0f / 255.0f, 194.0f / 255.0f, 245.0f / 255.0f);
			}
			else if ((t <= 0.6f && t >= 0.4f))
			{
				glColor3f(184.0f / 255.0f, 184.0f / 255.0f, 235.0f / 255.0f);
			}
			else if ((t <= 0.8f && t >= 0.6f))
			{
				glColor3f(174.0f / 255.0f, 174.0f / 255.0f, 225.0f / 255.0f);
			}
			else
			{
				glColor3f(164.0f / 255.0f, 164.0f / 255.0f, 215.0f / 255.0f);
			}
			p0.x = x;
			p0.y = y;
			p0.z = z;

			p1.z = z;

			p2.z = z;

			p3.z = z;

			glBegin(GL_LINE_STRIP);
			for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
			{
				float x = pow((1 - t), 3) * p0.x + 3 * pow((1 - t), 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
				float y = pow((1 - t), 3) * p0.y + 3 * pow((1 - t), 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
				float z = pow((1 - t), 3) * p0.z + 3 * pow((1 - t), 2) * t * p1.z + 3 * (1 - t) * pow(t, 2) * p2.z + pow(t, 3) * p3.z;
				glVertex3f(x, y, z);
			}
			glEnd();
		}
	}

	for (float z = 0.15; z <= 0.75f; z = z + 0.1f)
	{
		//variable declaration
		float point1_x = 0.0f;
		float point1_y = 0.0f;
		float point1_z = z;

		float point2_x = -0.2f;
		float point2_y = 0.0f;
		float point2_z = z + 0.05f;

		float point3_x = 0.0f;
		float point3_y = 0.0f;
		float point3_z = z + 0.1f;

		for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
		{

			float x = pow((1 - t), 2) * point1_x + 2 * (1 - t) * t * point2_x + pow(t, 2) * point3_x;
			float y = pow((1 - t), 2) * point1_y + 2 * (1 - t) * t * point2_y + pow(t, 2) * point3_y;
			float z = pow((1 - t), 2) * point1_z + 2 * (1 - t) * t * point2_z + pow(t, 2) * point3_z;

			if ((t <= 0.2f && t >= 0.0f))
			{
				glColor3f(204.0f / 255.0f, 204.0f / 255.0f, 255.0f / 255.0f);
			}
			else if ((t <= 0.4f && t >= 0.2f))
			{
				glColor3f(194.0f / 255.0f, 194.0f / 255.0f, 245.0f / 255.0f);
			}
			else if ((t <= 0.6f && t >= 0.4f))
			{
				glColor3f(184.0f / 255.0f, 184.0f / 255.0f, 235.0f / 255.0f);
			}
			else if ((t <= 0.8f && t >= 0.6f))
			{
				glColor3f(174.0f / 255.0f, 174.0f / 255.0f, 225.0f / 255.0f);
			}
			else
			{
				glColor3f(164.0f / 255.0f, 164.0f / 255.0f, 215.0f / 255.0f);
			}
			p0.x = x;
			p0.y = y;
			p0.z = z;

			p1.z = z;

			p2.z = z;

			p3.z = z;

			glBegin(GL_LINE_STRIP);
			for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
			{

				//right part of curtains
				float x = pow((1 - t), 3) * p0.x + 3 * pow((1 - t), 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
				float y = pow((1 - t), 3) * p0.y + 3 * pow((1 - t), 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
				float z = pow((1 - t), 3) * p0.z + 3 * pow((1 - t), 2) * t * p1.z + 3 * (1 - t) * pow(t, 2) * p2.z + pow(t, 3) * p3.z;

				glVertex3f(x, y, z);
			}
			glEnd();
		}
	}
	glDisable(GL_LINE_SMOOTH);

}

void SGK_drawQuadraticCurveVertical(float xAxis, float yAxis, float zAxis, float cpAxis)
{
	//function declaration
	// 1st param xAxis of start of curve line
	// 2nd param yAxis of start of curve line
	// 3rd param zAxis of start of curve line
	// 4th param xAxis for control point to make curve
	void SGK_drawQuadraticCurveHorizontal(float, float, float, float);

	//variable declaration
	float point1_x = xAxis;
	float point1_y = yAxis;
	float point1_z = zAxis;

	float point2_x = cpAxis;
	float point2_y = yAxis;
	float point2_z = zAxis+0.05f;

	float point3_x = xAxis;
	float point3_y = yAxis;
	float point3_z = zAxis+0.1f;

	glBegin(GL_LINE_STRIP);

	for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
	{

		if ((t <= 0.2f && t >= 0.0f))
		{
			glColor3f(204.0f / 255.0f, 204.0f / 255.0f, 255.0f / 255.0f);
		}
		else if ((t <= 0.4f && t >= 0.2f))
		{
			glColor3f(194.0f / 255.0f, 194.0f / 255.0f, 245.0f / 255.0f);
		}
		else if ((t <= 0.6f && t >= 0.4f))
		{
			glColor3f(184.0f / 255.0f, 184.0f / 255.0f, 235.0f / 255.0f);
		}
		else if ((t <= 0.8f && t >= 0.6f))
		{
			glColor3f(174.0f / 255.0f, 174.0f / 255.0f, 225.0f / 255.0f);
		}
		else
		{
			glColor3f(164.0f / 255.0f, 164.0f / 255.0f, 215.0f / 255.0f);
		}

		float x = pow((1 - t), 2) * point1_x + 2 * (1 - t) * t * point2_x + pow(t, 2) * point3_x;
		float y = pow((1 - t), 2) * point1_y + 2 * (1 - t) * t * point2_y + pow(t, 2) * point3_y;
		float z = pow((1 - t), 2) * point1_z + 2 * (1 - t) * t * point2_z + pow(t, 2) * point3_z;

		glVertex3f(x, y, z);
		glVertex3f(x, y-0.3f, z);
	}

	glEnd();

	for (float y = yAxis; y >= -0.3f; y = y - 0.01f)
	{
		SGK_drawQuadraticCurveHorizontal(xAxis, y, zAxis, cpAxis);
	}
	
}

void SGK_drawQuadraticCurveHorizontal(float xAxis, float yAxis, float zAxis, float cpAxis)
{
	//variable declaration
	float point1_x = xAxis;
	float point1_y = yAxis;
	float point1_z = zAxis;

	float point2_x = cpAxis;
	float point2_y = yAxis;
	float point2_z = zAxis + 0.05f;

	float point3_x = xAxis;
	float point3_y = yAxis;
	float point3_z = zAxis + 0.1f;

	glBegin(GL_LINE_STRIP);

	for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
	{


		float x = pow((1 - t), 2) * point1_x + 2 * (1 - t) * t * point2_x + pow(t, 2) * point3_x;
		float y = pow((1 - t), 2) * point1_y + 2 * (1 - t) * t * point2_y + pow(t, 2) * point3_y;
		float z = pow((1 - t), 2) * point1_z + 2 * (1 - t) * t * point2_z + pow(t, 2) * point3_z;

		glVertex3f(x, y, z);
	}

	glEnd();
}

void SGK_drawCurveLeft(float xAxis, float yAxis, float zAxis)
{
	glBegin(GL_LINE_STRIP);

	for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
	{

		float x1 = pow((1 - t), 3) * p4.x + 3 * pow((1 - t), 2) * t * p5.x + 3 * (1 - t) * pow(t, 2) * p6.x + pow(t, 3) * p7.x;
		float y1 = pow((1 - t), 3) * p4.y + 3 * pow((1 - t), 2) * t * p5.y + 3 * (1 - t) * pow(t, 2) * p6.y + pow(t, 3) * p7.y;
		float z1 = pow((1 - t), 3) * (p4.z+zAxis) + 3 * pow((1 - t), 2) * t * (p5.z+zAxis) + 3 * (1 - t) * pow(t, 2) * (p6.z + zAxis) + pow(t, 3) * (p7.z + zAxis);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(x1, y1, z1);
	}
	glEnd();
}

void SGK_drawCurveRight(float xAxis, float yAxis, float zAxis)
{
	glBegin(GL_LINE_STRIP);

	for (float t = 0.0f; t <= 1.0f; t = t + 0.01f)
	{

		float x = pow((1 - t), 3) * p0.x + 3 * pow((1 - t), 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
		float y = pow((1 - t), 3) * p0.y + 3 * pow((1 - t), 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
		float z = pow((1 - t), 3) * (p0.z + zAxis) + 3 * pow((1 - t), 2) * t * (p1.z + zAxis) + 3 * (1 - t) * pow(t, 2) * (p2.z + zAxis) + pow(t, 3) * (p3.z + zAxis);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(x, y, z);

	}
	glEnd();
}

void SGK_drawBed(void)
{
	// 1st param :- x coordinate of center of circle
	// 2nd param :- y coordinate of center of circle
	// 3rd param :- z coordinate of center of circle
	// 4th param :- radius of clock
	void SGK_drawClock(float, float, float, float);

	void SGK_drawMobile(void);

	// variable declaration
	myColor myBedColor, myBedLegColor, myBedMattressColor;
	myBedColor.fRed = 160.0f / 255.0f;
	myBedColor.fGreen = 64.0f / 255.0f;
	myBedColor.fBlue = 0.0f;

	myBedLegColor.fRed = 160.0f / 255.0f;
	myBedLegColor.fGreen = 64.0f / 255.0f;
	myBedLegColor.fBlue = 0.0f;

	myBedMattressColor.fRed = 204.0f/255.0f;
	myBedMattressColor.fGreen = 204.0f/255.0f;
	myBedMattressColor.fBlue = 255.0f/255.0f;

	// cousion
	glPushMatrix();
	{
		glTranslatef(0.0f, -0.26f, 0.0f);
		glPushMatrix();
		{
			glScalef(1.0f, 0.3f, 1.0f);
			SGK_drawCylinder(1.78f, -0.325f, 1.98f, 0.0f, 360.0f, 0.46f, 0.15f, myBedMattressColor);
			SGK_drawCylinder(1.78f, -0.325f, 1.48f, 0.0f, 360.0f, 0.46f, 0.15f, myBedMattressColor);
		}
		glPopMatrix();
	}
	glPopMatrix();

	myBedMattressColor.fRed = 255.0f / 255.0f;
	myBedMattressColor.fGreen = 255.0f / 255.0f;
	myBedMattressColor.fBlue = 255.0f / 255.0f;
	// mattress
	SGK_drawBox(1.95f, -0.4f, 1.0f, 1.0f, 1.45f, 0.1f, myBedMattressColor);
	// vertical part on top of right side of bed
	SGK_drawBox(2.0f, -0.2f, 1.0f, 1.0f, 0.05f, 0.3f, myBedColor);
	// top of bed
	SGK_drawBox(2.0f, -0.5f, 1.0f, 1.0f, 1.5f, 0.2f, myBedColor);
	//glColor3f(1.0f, 1.0f, 1.0f);
	// right leg
	SGK_drawBox(2.0f, -0.7f, 1.0f, 0.1f, 0.2f, 0.3f, myBedLegColor);
	// left leg
	SGK_drawBox(0.7f, -0.7f, 1.0f, 0.1f, 0.2f, 0.3f, myBedLegColor);
	// right back leg
	SGK_drawBox(2.0f, -0.7f, 1.9f, 0.1f, 0.2f, 0.3f, myBedLegColor);
	// left back leg
	SGK_drawBox(0.7f, -0.7f, 1.9f, 0.1f, 0.2f, 0.3f, myBedLegColor);

	glBegin(GL_POLYGON);
	//blanket
	glColor3f(204.0f / 255.0f, 204.0f / 255.0f, 1.0f);

	glVertex3f(1.49f, -0.399f, 2.0f);//right top

	glColor3f(164.0f / 255.0f, 164.0f / 255.0f, 215.0f / 255.0f);
	glVertex3f(0.492f, -0.399f, 2.0f);//left top
	glVertex3f(0.465f, -0.399f, 1.95f);
	glVertex3f(0.465f, -0.399f, 0.999f);
	
	glVertex3f(0.495f, -0.399f, 0.97f);//left bottom
	glVertex3f(1.495f, -0.399f, 0.97f);
	glVertex3f(1.5f, -0.399f, 1.0);//right bottom
	glEnd();

	// for blanket wave pattern ----------------- Start Here ------------------------
	// Using Quadratic Bazier Curve
	for (float z = 1.0f; z <= 2.0f; z = z + 0.1f)
	{
		SGK_drawQuadraticCurveVertical(0.5f, -0.40f, z, 0.45f);
	}

	glPushMatrix();
	{
		glTranslatef(2.5f, 0.0f, 0.5f);
		glPushMatrix();
		{
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			for (float z = 1.0f; z <= 2.0f; z = z + 0.1f)
			{
				SGK_drawQuadraticCurveVertical(0.5f, -0.401f, z, 0.45f);
			}
		}
		glPopMatrix();
	}
	glPopMatrix();
	// for blanket wave pattern ----------------- End Here ------------------------

	// draw clock
	glPushMatrix();
	glTranslatef(0.0f, 0.3f, -0.01f);
	SGK_drawClock(0.0f, 0.5f, 1.98f, 0.2f);

	glPopMatrix();

	SGK_drawMobile();

}

void SGK_drawMobile(void)
{
	myColor colorGray = { 80.0f/255.0f,80.0f / 255.0f,80.0f / 255.0f };

	SGK_drawBox(0.75f, -0.39f, 1.5f, 0.05f,0.15f ,0.01f, colorGray);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture_Screen);

	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.75f, -0.389f, 1.55f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.75f, -0.389f, 1.5f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.6f, -0.389f, 1.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.6f, -0.389f, 1.55f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void SGK_drawBox(float xAxis, float yAxis, float zAxis, float depth, float width, float height,myColor color)
{
	glBegin(GL_QUADS);
	//front
	glColor3f(color.fRed, color.fGreen, color.fBlue);

	glVertex3f(xAxis, yAxis, zAxis);//right top
	glVertex3f(xAxis-width, yAxis, zAxis);//left top

	glColor3f(color.fRed-0.2f, color.fGreen-0.2f, color.fBlue-0.2f);
	glVertex3f(xAxis - width, yAxis-height, zAxis);//left bottom
	glVertex3f(xAxis, yAxis - height, zAxis);//right bottom

	//right
	glColor3f(color.fRed, color.fGreen, color.fBlue);

	glVertex3f(xAxis, yAxis, zAxis + depth);//right top
	glVertex3f(xAxis, yAxis, zAxis);//left top

	glColor3f(color.fRed - 0.2f, color.fGreen - 0.2f, color.fBlue - 0.2f);

	glVertex3f(xAxis, yAxis - height, zAxis);//left bottom
	glVertex3f(xAxis, yAxis - height, zAxis + depth);//right bottom

	//back
	glColor3f(color.fRed, color.fGreen, color.fBlue);

	glVertex3f(xAxis - width, yAxis, zAxis + depth);//right top
	glVertex3f(xAxis, yAxis, zAxis + depth);//left top

	glColor3f(color.fRed - 0.2f, color.fGreen - 0.2f, color.fBlue - 0.2f);

	glVertex3f(xAxis, yAxis - height, zAxis + depth);//left bottom
	glVertex3f(xAxis - width, yAxis - height, zAxis + depth);//right bottom

	//left
	glColor3f(color.fRed, color.fGreen, color.fBlue);

	glVertex3f(xAxis - width, yAxis, zAxis);//right top
	glVertex3f(xAxis - width, yAxis, zAxis + depth);//left top

	glColor3f(color.fRed - 0.2f, color.fGreen - 0.2f, color.fBlue - 0.2f);

	glVertex3f(xAxis - width, yAxis - height, zAxis + depth);//left bottom
	glVertex3f(xAxis - width, yAxis - height, zAxis);//right bottom

	//top
	glColor3f(color.fRed, color.fGreen, color.fBlue);

	glVertex3f(xAxis, yAxis, zAxis + depth);//right top
	glVertex3f(xAxis - width, yAxis, zAxis + depth);//left top

	glColor3f(color.fRed - 0.2f, color.fGreen - 0.2f, color.fBlue - 0.2f);

	glVertex3f(xAxis - width, yAxis, zAxis);//left bottom
	glVertex3f(xAxis, yAxis, zAxis);//right bottom

	//bottom
	glColor3f(color.fRed, color.fGreen, color.fBlue);

	glVertex3f(xAxis, yAxis - height, zAxis + depth);//right top
	glVertex3f(xAxis - width, yAxis - height, zAxis + depth);//left top

	glColor3f(color.fRed - 0.2f, color.fGreen - 0.2f, color.fBlue - 0.2f);

	glVertex3f(xAxis - width, yAxis - height, zAxis);//left bottom
	glVertex3f(xAxis, yAxis - height, zAxis);//right bottom

	glEnd();
}

void SGK_drawCylinder(float xAxis, float yAxis, float zAxis, float startAngle, float endAngle, float fDepth, float fRadius,myColor color)
{
	float x, y;
	if (startAngle < endAngle)
	{
		glBegin(GL_LINES);
		for (float fAngle = startAngle; fAngle <= endAngle; fAngle = fAngle + 0.1f)
		{
			x = xAxis + fRadius * sin((fAngle * M_PI) / 180.0f);
			y = yAxis + fRadius * cos((fAngle * M_PI) / 180.0f);

			// front face
			glColor3f(color.fRed, color.fGreen, color.fBlue);
			glVertex3f(xAxis, yAxis, zAxis);
			glVertex3f(x, y, zAxis);

			//back face
			glVertex3f(xAxis, yAxis, zAxis-fDepth);
			glVertex3f(x, y, zAxis-fDepth);

			// circumference
			glColor3f(color.fRed-0.2f, color.fGreen - 0.2f, color.fBlue - 0.2f);
			glVertex3f(x, y, zAxis);
			glVertex3f(x, y, (zAxis - fDepth));
		}
		glEnd();
	}
}

void SGK_drawClock(float xAxis, float yAxis, float zAxis, float fRadius)
{
	//variable declaration
	 
	myColor myClockArmColor,myClockBodyColor;
	myClockBodyColor.fRed = 1.0f;
	myClockBodyColor.fGreen = 0.9f;
	myClockBodyColor.fBlue = 0.9f;
	
	SGK_drawCylinder(xAxis, yAxis, zAxis, 0.0f, 360.0f, 0.001f, fRadius, myClockBodyColor);

	glColor3f(0.0f, 0.0f, 0.0f);
	SGK_drawCircle(xAxis, yAxis, zAxis-0.004f, fRadius);

	// for clock lines representing time
	glBegin(GL_LINES);
	for (float fAngle = 0.0f; fAngle <= 360.0f; fAngle = fAngle + 30.0f)
	{
		float x = xAxis + (fRadius - 0.01f) * sin((fAngle * M_PI) / 180.0f);
		float y = yAxis + (fRadius - 0.01f) * cos((fAngle * M_PI) / 180.0f);

		float xInner = xAxis + (fRadius- 0.03f) * sin((fAngle * M_PI) / 180.0f);
		float yInner = yAxis + (fRadius - 0.03f) * cos((fAngle * M_PI) / 180.0f);

		glVertex3f(x, y, zAxis-0.01f);
		glVertex3f(xInner, yInner, zAxis-0.01f);
	}
	glEnd();

	glLineWidth(2.0f);

	glBegin(GL_LINES); // for hour arm

	glVertex3f(xAxis, yAxis, zAxis - 0.01f);
	glVertex3f(xAxis - 0.10f, yAxis, zAxis - 0.01f);

	glEnd();
	glLineWidth(1.0f);

	glLineWidth(1.4f);
	glBegin(GL_LINES); // for minute arm

	glVertex3f(xAxis, yAxis, zAxis - 0.01f);
	glVertex3f(xAxis, yAxis + 0.15f, zAxis - 0.01f);

	glEnd();

	glLineWidth(1.0f);

	glBegin(GL_LINES); // for second arm
	glColor3f(1.0f, 0.0f, 0.0f);
	for (float fAngle = clockAnimation-0.001f; fAngle <= clockAnimation; fAngle = fAngle + 0.1f)
	{
		float x = xAxis + (fRadius - 0.02f) * sin((fAngle * M_PI) / 180.0f);
		float y = yAxis + (fRadius - 0.02f) * cos((fAngle * M_PI) / 180.0f);

		glVertex3f(x, y, zAxis - 0.01f);
		glVertex3f(xAxis, yAxis, zAxis - 0.01f);
	}
	glEnd();
	
}

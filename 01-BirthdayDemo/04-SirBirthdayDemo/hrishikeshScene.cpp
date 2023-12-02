// windows header files
#include <windows.h>

// openGL headers
#include<stdio.h>
#include<stdlib.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include"hrishikeshScene.h"

// OpenGL related global variable declarations

GLuint texture_SirImage = 0;

extern FILE *gpFILE;

extern BOOL loadGLTexture(GLuint *texture, TCHAR imageResourceID[]);

int SceneInitialize(void)
{
   
    if ((loadGLTexture(&texture_SirImage, MAKEINTRESOURCE(SIR_BITMAP))) == FALSE)
    {
        fprintf(gpFILE, "load of screen texture is Failed.\n");
        return(-7);
    }
    else
    {
        return(0);
    }
    
}

void SceneDisplay(void)
{
	//function declarations
	void hms_drawRoom(void);
	void hms_drawComputer(void);
	void hms_drawTable(void);
    void hms_drawChair(void);
    
    /* glLoadIdentity()();
    glTranslatef(0.0f, 0.0f, 0.0f);
    hms_drawRoom();*/

	////glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.1f, 0.21f, 0.0f);
    glPushMatrix();
	glScalef(0.3f, 0.3f, 1.0f);
	hms_drawComputer();
    glPopMatrix();

    glPopMatrix();


    ////glLoadIdentity()();
    glPushMatrix();
    glScalef(0.8f, 1.0f, 1.0f);
    hms_drawTable();
    glPopMatrix();
    hms_drawChair();
}

void SceneUpdate(void)
{
    //code
}

void hms_drawRoom(void)
{
    glBegin(GL_QUADS);

	//Front Face
	//glColor3f(133.0f / 255.0f, 193.0f / 255.0f, 233.0f / 255.0f);
	//glVertex3f(2.0f, 2.0f, 2.0f);//right top
	//glVertex3f(-2.0f, 2.0f, 2.0f);//left top
	//glVertex3f(-2.0f, -1.0f, 2.0f);//left bottom
	//glVertex3f(2.0f, -1.0f, 2.0f);//right bottom

	//back Face
	glColor3f(133.0f / 255.0f, 193.0f / 255.0f, 233.0f / 255.0f);
	glVertex3f(2.0f, 2.0f, -2.0f);//right top
	glVertex3f(-2.0f, 2.0f, -2.0f);//left top
	glVertex3f(-2.0f, -1.0f, -2.0f);//left bottom
	glVertex3f(2.0f, -1.0f, -2.0f);//right bottom

	//right side
	glColor3f(123.0f / 255.0f, 183.0f / 255.0f, 223.0f / 255.0f);
	glVertex3f(2.0f, 2.0f, -2.0f);//right top
	glColor3f(208.0f / 255.0f, 211.0f / 255.0f, 212.0f / 255.0f);
	glVertex3f(2.0f, 2.0f, 2.0f);//left top
	glVertex3f(2.0f, -1.0f, 2.0f);//left bottom
	glColor3f(123.0f / 255.0f, 183.0f / 255.0f, 223.0f / 255.0f);
	glVertex3f(2.0f, -1.0f, -2.0f);//right bottom

	//left side Face
	glColor3f(208.0f / 255.0f, 211.0f / 255.0f, 212.0f / 255.0f);
	glVertex3f(-2.0f, 2.0f, 2.0f);//right top
	glColor3f(123.0f / 255.0f, 183.0f / 255.0f, 223.0f / 255.0f);
	glVertex3f(-2.0f, 2.0f, -2.0f);//left top
	glVertex3f(-2.0f, -1.0f, -2.0f);//left bottom
	glColor3f(208.0f / 255.0f, 211.0f / 255.0f, 212.0f / 255.0f);
	glVertex3f(-2.0f, -1.0f, 2.0f);//right bottom

	//bottom side Face
	glColor3f(166.0f / 255.0f, 172.0f / 255.0f, 175.0f / 255.0f);
	glVertex3f(2.0f, -1.0f, -2.0f);//right top
	glVertex3f(-2.0f, -1.0f, -2.0f);//left top
	glColor3f(86.0f / 255.0f, 101.0f / 255.0f, 115.0f / 255.0f);
	glVertex3f(-2.0f, -1.0f, 2.0f);//left bottom
	glVertex3f(2.0f, -1.0f, 2.0f);//right bottom

	//top side Face
    //glColor3f(1.0f, 1.0f, 1.0f);
	glColor3f(210.0f / 255.0f, 180.0f / 255.0f, 0.0f / 255.0f);
	glVertex3f(2.0f, 2.0f, -2.0f);//right top
	glVertex3f(-2.0f, 2.0f, -2.0f);//left top
	glVertex3f(-2.0f, 2.0f, 2.0f);//left bottom
	glVertex3f(2.0f, 2.0f, 2.0f);//right bottom

	glEnd();
} 

void hms_drawComputer(void)
{
    //Monitor


    glBindTexture(GL_TEXTURE_2D, texture_SirImage);

    glColor3f(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);

	glBegin(GL_QUADS);
	//Front face
    //glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.6f, -1.6f);       //Right Top
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 0.6f, -1.6f);      //Left Top
    //glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -0.6f, -1.6f);     //Left Bottom
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -0.6f, -1.6f); 	 //Right Bottom

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glLineWidth(7.0f);
    glBegin(GL_LINE_LOOP);
    //Front face
    glColor3f(128.0f/255.0f, 128.0f /255.0f, 128.0f /255.0f);
    glVertex3f(1.0f, 0.6f, -1.59f);       //Right Top
    glVertex3f(-1.0f, 0.6f, -1.59f);      //Left Top
    glColor3f(128.0f /255.0f, 128.0f /255.0f, 128.0f /255.0f);
    glVertex3f(-1.0f, -0.59f, -1.59f);     //Left Bottom
    glVertex3f(0.99f, -0.6f, -1.59f); 	 //Right Bottom

    glEnd();
    glLineWidth(5.0f);

    glBegin(GL_QUADS);
    //Right face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(1.0f, 0.6f, -1.8f);      //Right Top
    glVertex3f(1.0f, 0.6f, -1.6f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(1.0f, -0.6f, -1.6f);     //Left Bottom
    glVertex3f(1.0f, -0.6f, -1.8f);     //Right Bottom
    
    //Back face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-1.0f, 0.6f, -1.8f);      //Right Top
    glVertex3f(1.0f, 0.6f, -1.8f);       //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(1.0f, -0.6f, -1.8f);      //Left Bottom
    glVertex3f(-1.0f, -0.6f, -1.8f);     //Right Bottom

    //Left face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-1.0f, 0.6f, -1.6f);      //Right Top
    glVertex3f(-1.0f, 0.6f, -1.8f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-1.0f, -0.6f, -1.8f);     //Left Bottom
    glVertex3f(-1.0f, -0.6f, -1.6f);     //Right Bottom

    //Top face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(1.0f, 0.6f, -1.8f);        //Right Top
    glVertex3f(-1.0f, 0.6f, -1.8f);       //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-1.0f, 0.6f, -1.6f);       //Left Bottom
    glVertex3f(1.0f, 0.6f, -1.6f);        //Right Bottom

    //Bottom face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f);
    glVertex3f(1.0f, -0.6f, -1.8f);       //Right Top
    glVertex3f(-1.0f, -0.6f, -1.8f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-1.0f, -0.6f, -1.6f);      //Left Bottom
    glVertex3f(1.0f, -0.6f, -1.6f);       //Right Bottom
    //glEnd();

    //stand
	//Front face
    //glColor3f(1.0f, 0.0f, 0.0f); 
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f);        
    glVertex3f(0.1f, -0.6f, -1.6f);       //Right Top
    glVertex3f(-0.1f, -0.6f, -1.6f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-0.1f, -0.9f, -1.6f);      //Left Bottom
    glVertex3f(0.1f, -0.9f, -1.6f); 	  //Right Bottom

    //Right face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(0.1f, -0.6f, -1.8f);      //Right Top
    glVertex3f(0.1f, -0.6f, -1.6f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(0.1f, -0.9f, -1.6f);      //Left Bottom
    glVertex3f(0.1f, -0.9f, -1.8f);      //Right Bottom
    
    //Back face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-0.1f, -0.6f, -1.8f);     //Right Top
    glVertex3f(0.1f, -0.6f, -1.8f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(0.1f, -0.9f, -1.8f);      //Left Bottom
    glVertex3f(-0.1f, -0.9f, -1.8f);     //Right Bottom

    //Left face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-0.1f, -0.6f, -1.6f);     //Right Top
    glVertex3f(-0.1f, -0.6f, -1.8f);     //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-0.1f, -0.9f, -1.8f);     //Left Bottom
    glVertex3f(-0.1f, -0.9f, -1.6f);     //Right Bottom

    //Lower stand
    //glColor3f(0.0f, 1.0f, 0.0f);  
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f);       
    glVertex3f(0.3f, -0.9f, -1.6f);       //Right Top
    glVertex3f(-0.3f, -0.9f, -1.6f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-0.3f, -1.0f, -1.6f);     //Left Bottom
    glVertex3f(0.3f, -1.0f, -1.6f); 	 //Right Bottom

    //Right face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(0.3f, -0.9f, -1.8f);      //Right Top
    glVertex3f(0.3f, -0.9f, -1.6f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(0.3f, -1.0f, -1.6f);     //Left Bottom
    glVertex3f(0.3f, -1.0f, -1.8f);     //Right Bottom
    
    //Back face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-0.3f, -0.9f, -1.8f);      //Right Top
    glVertex3f(0.3f, -0.9f, -1.8f);       //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(0.3f, -1.0f, -1.8f);      //Left Bottom
    glVertex3f(-0.3f, -1.0f, -1.8f);     //Right Bottom

    //Left face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-0.3f, -0.9f, -1.6f);      //Right Top
    glVertex3f(-0.3f, -0.9f, -1.8f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-0.3f, -1.0f, -1.8f);     //Left Bottom
    glVertex3f(-0.3f, -1.0f, -1.6f);     //Right Bottom

    //Top face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(0.3f, -0.9f, -1.8f);        //Right Top
    glVertex3f(-0.3f, -0.9f, -1.8f);       //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-0.3f, -0.9f, -1.6f);       //Left Bottom
    glVertex3f(0.3f, -0.9f, -1.6f);        //Right Bottom

    //Bottom face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(0.3f, -1.0f, -1.8f);       //Right Top
    glVertex3f(-0.3f, -1.0f, -1.8f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-0.3f, -1.0f, -1.6f);      //Left Bottom
    glVertex3f(0.3f, -1.0f, -1.6f);       //Right Bottom

    //CPU

    //glColor3f(0.0f, 1.0f, 0.0f);
    //Front face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f);         
    glVertex3f(-1.3f, 0.9f, -1.1f);       //Right Top
    glVertex3f(-2.0f, 0.9f, -1.1f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-2.0f, -1.0f, -1.1f);     //Left Bottom
    glVertex3f(-1.3f, -1.0f, -1.1f); 	 //Right Bottom

    //Right face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-1.3f, 0.9f, -1.9f);      //Right Top
    glVertex3f(-1.3f, 0.9f, -1.1f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-1.3f, -1.0f, -1.1f);     //Left Bottom
    glVertex3f(-1.3f, -1.0f, -1.9f);     //Right Bottom
    
    //Back face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-1.3f, 0.9f, -1.9f);      //Right Top
    glVertex3f(-2.0f, 0.9f, -1.9f);       //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-2.0f, -1.0f, -1.9f);      //Left Bottom
    glVertex3f(-1.3f, -1.0f, -1.9f);     //Right Bottom

    //Left face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-2.0f, 0.9f, -1.1f);      //Right Top
    glVertex3f(-2.0f, 0.9f, -1.9f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-2.0f, -1.0f, -1.9f);     //Left Bottom
    glVertex3f(-2.0f, -1.0f, -1.1f);     //Right Bottom

    //Top face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-1.3f, 0.9f, -1.9f);        //Right Top
    glVertex3f(-2.0f, 0.9f, -1.9f);       //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-2.0f, 0.9f, -1.1f);       //Left Bottom
    glVertex3f(-1.3f, 0.9f, -1.1f);        //Right Bottom

    //Bottom face
    glColor3f(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f); 
    glVertex3f(-1.3f, -1.0f, -1.9f);       //Right Top
    glVertex3f(-2.0f, -1.0f, -1.9f);      //Left Top
    glColor3f(53.0f/255.0f, 57.0f/255.0f, 53.0f/255.0f);
    glVertex3f(-2.0f, -1.0f, -1.1f);      //Left Bottom
    glVertex3f(-1.3f, -1.0f, -1.1f);       //Right Bottom

    glColor3f(0.25f, 0.25f, 0.25f);         
    glVertex3f(-1.4f, 0.8f, -1.09f);
    glVertex3f(-1.9f, 0.8f, -1.09f);
    glColor3f(0.75f, 0.75f, 0.75f);      
    glVertex3f(-1.9f, 0.65f, -1.09f);     
    glVertex3f(-1.4f, 0.65f, -1.09f);

    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex3f(-1.4f, 0.5f, -1.09f);
    glVertex3f(-1.9f, 0.5f, -1.09f); 
    glColor3f(0.75f, 0.75f, 0.75f);     
    glVertex3f(-1.9f, 0.35f, -1.09f);     
    glVertex3f(-1.4f, 0.35f, -1.09f);

    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex3f(-1.4f, 0.1f, -1.09f);
    glVertex3f(-1.9f, 0.1f, -1.09f);
    glColor3f(0.75f, 0.75f, 0.75f);      
    glVertex3f(-1.9f, -0.5f, -1.09f);     
    glVertex3f(-1.4f, -0.5f, -1.09f);
    glEnd();
}

void hms_drawTable(void)
{   
    //function declarations
    void hms_drawLeg(void);
    void hms_drawTopOfTable(void);
    void hms_drawDrawer(void);
    void hms_drawHandle(void);
    void hms_drawBook(float, float, float);

    //code
    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(-0.2f, -1.0f, 0.0f);
    hms_drawLeg();  
    glPopMatrix();

    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(-0.4f, -1.0f, 0.0f);
    hms_drawLeg();
    glPopMatrix();

    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(-0.6f, -1.0f, 0.0f);
    hms_drawLeg();
    glPopMatrix();

    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(-2.0f, -1.0f, 0.0f);
    hms_drawLeg(); 
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.1f, 0.0f); 
    hms_drawTopOfTable(); 
    glPopMatrix();

 
    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.2f, 0.0f); 
    hms_drawDrawer();  
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.4f, 0.0f); 
    hms_drawDrawer();
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.6f, 0.0f); 
    hms_drawDrawer(); 
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.8f, 0.0f); 
    hms_drawDrawer(); 
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.2f, 0.0f); 
    hms_drawHandle();
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.4f, 0.0f); 
    hms_drawHandle();
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.6f, 0.0f); 
    hms_drawHandle();
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glTranslatef(0.0f, -1.8f, 0.0f); 
    hms_drawHandle();  
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(0.9f, -1.199f, -1.7f);
    hms_drawBook(1.0f, 0.0f, 0.0f); 
    glPopMatrix();
    glPopMatrix();


    //glLoadIdentity()();
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(1.0f, -1.099f, -1.7f);
    hms_drawBook(1.0f, 0.5f, 0.0f);
    glPopMatrix();
    glPopMatrix();

    //glLoadIdentity()();
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(0.9f, -0.999f, -1.7f);
    hms_drawBook(0.0f, 0.0f, 1.0f);
    glPopMatrix();
    glPopMatrix();
}

void hms_drawLeg(void)
{
    //teak brown - 125, 89, 67
    glBegin(GL_QUADS);
	//Front face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);        
    glVertex3f(1.2f, 0.8f, -1.0f);      //Right Top
    glVertex3f(1.0f, 0.8f, -1.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 0.0f, -1.0f);      //Left Bottom
    glVertex3f(1.2f, 0.0f, -1.0f); 	    //Right Bottom

    //Right face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);
    glVertex3f(1.2f, 0.8f, -2.0f);      //Right Top
    glVertex3f(1.2f, 0.8f, -1.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f); 
    glVertex3f(1.2f, 0.0f, -1.0f);      //Left Bottom
    glVertex3f(1.2f, 0.0f, -2.0f);      //Right Bottom
    
    //Back face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);
    glVertex3f(1.2f, 0.8f, -2.0f);      //Right Top
    glVertex3f(1.0f, 0.8f, -1.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 0.0f, -1.0f);      //Left Bottom
    glVertex3f(1.2f, 0.0f, -2.0f);      //Right Bottom

    //Left face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);
    glVertex3f(1.0f, 0.8f, -1.0f);      //Right Top
    glVertex3f(1.0f, 0.8f, -2.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 0.0f, -2.0f);      //Left Bottom
    glVertex3f(1.0f, 0.0f, -1.0f);      //Right Bottom

    //Top face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);
    glVertex3f(1.2f, 0.8f, -2.0f);       //Right Top
    glVertex3f(1.0f, 0.8f, -2.0f);       //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 0.8f, -1.0f);       //Left Bottom
    glVertex3f(1.2f, 0.8f, -1.0f);       //Right Bottom

    //Bottom face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);
    glVertex3f(1.2f, 0.0f, -2.0f);      //Right Top
    glVertex3f(1.0f, 0.0f, -2.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 0.0f, -1.0f);      //Left Bottom
    glVertex3f(1.2f, 0.0f, -1.0f);      //Right Bottom
    glEnd(); 
}

void hms_drawTopOfTable(void)
{
    //teak brown - 125, 89, 67
    glBegin(GL_QUADS);
	//Front face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);        
    glVertex3f(1.0f, 1.0f, -1.0f);       //Right Top
    glVertex3f(-1.0f, 1.0f, -1.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-1.0f, 0.9f, -1.0f);      //Left Bottom
    glVertex3f(1.0f, 0.9f, -1.0f); 	     //Right Bottom

    //Right face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 1.0f, -2.0f);      //Right Top
    glVertex3f(1.0f, 1.0f, -1.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(1.0f, 0.9f, -1.0f);      //Left Bottom
    glVertex3f(1.0f, 0.9f, -2.0f);      //Right Bottom
    
    //Back face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 1.0f, -2.0f);      //Right Top
    glVertex3f(-1.0f, 1.0f, -1.0f);     //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-1.0f, 0.9f, -1.0f);     //Left Bottom
    glVertex3f(1.0f, 0.9f, -2.0f);      //Right Bottom

    //Left face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(-1.0f, 1.0f, -1.0f);      //Right Top
    glVertex3f(-1.0f, 1.0f, -2.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-1.0f, 0.9f, -2.0f);      //Left Bottom
    glVertex3f(-1.0f, 0.9f, -1.0f);      //Right Bottom

    //Top face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 1.0f, -2.0f);       //Right Top
    glVertex3f(-1.0f, 1.0f, -2.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);      //Left Bottom
    glVertex3f(1.0f, 1.0f, -1.0f);       //Right Bottom

    //Bottom face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(1.0f, 0.9f, -2.0f);       //Right Top
    glVertex3f(-1.0f, 0.9f, -2.0f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-1.0f, 0.9f, -1.0f);      //Left Bottom
    glVertex3f(1.0f, 0.9f, -1.0f);       //Right Bottom
    glEnd(); 
}

void hms_drawDrawer(void)
{
    //color code - (235, 150, 5)
    glBegin(GL_QUADS);
    
    glColor3f(235.0f/255.0f, 150.0f/255.0f, 5.0f/255.0f);        
    
    glVertex3f(0.9f, 1.0f, -0.99f);  
    glVertex3f(0.5f, 1.0f, -0.99f);      
    glVertex3f(0.5f, 0.9f, -0.99f);      
    glVertex3f(0.9f, 0.9f, -0.99f);

    glEnd();
}

void hms_drawHandle(void)
{
    //silver - R: 192, G: 192, and B: 192
    glBegin(GL_QUADS);

    glColor3f(192.0f/255.0f, 192.0f/255.0f, 192.0f/255.0f);        
    
    glVertex3f(0.8f, 0.975f, -0.98f);    
    glVertex3f(0.6f, 0.975f, -0.98f);      
    glVertex3f(0.6f, 0.925f, -0.98f);      
    glVertex3f(0.8f, 0.925f, -0.98f); 	    

    glEnd(); 
}

void hms_drawBook(float red, float green, float blue)
{
    glBegin(GL_QUADS);
	//Front face
    glColor3f(1.0f, 1.0f, 1.0f);        
    glVertex3f(0.8f, 1.1f, -1.0f);       //Right Top
    glVertex3f(0.4f, 1.1f, -1.0f);       //Left Top
    glVertex3f(0.4f, 1.0f, -1.0f);       //Left Bottom
    glVertex3f(0.8f, 1.0f, -1.0f); 	     //Right Bottom

    //Right face
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.8f, 1.1f, -1.5f);      //Right Top
    glVertex3f(0.8f, 1.1f, -1.0f);      //Left Top
    glVertex3f(0.8f, 1.0f, -1.0f);      //Left Bottom
    glVertex3f(0.8f, 1.0f, -1.5f);      //Right Bottom
    
    //Back face
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.8f, 1.1f, -1.5f);      //Right Top
    glVertex3f(0.4f, 1.1f, -1.5f);      //Left Top
    glVertex3f(0.4f, 1.0f, -1.5f);      //Left Bottom
    glVertex3f(0.8f, 1.0f, -1.5f);      //Right Bottom

    //Left face
    glColor3f(red, green, blue);
    glVertex3f(0.4f, 1.1f, -1.0f);      //Right Top
    glVertex3f(0.4f, 1.1f, -1.5f);      //Left Top
    glColor3f(red - 0.4f, green - 0.4f, blue - 0.4f);
    glVertex3f(0.4f, 1.0f, -1.5f);      //Left Bottom
    glVertex3f(0.4f, 1.0f, -1.0f);      //Right Bottom

    //Top face
    glColor3f(red, green, blue);
    glVertex3f(0.8f, 1.1f, -1.5f);      //Right Top
    glVertex3f(0.4f, 1.1f, -1.5f);      //Left Top
    glColor3f(red - 0.4f, green - 0.4f, blue - 0.4f);
    glVertex3f(0.4f, 1.1f, -1.0f);      //Left Bottom
    glVertex3f(0.8f, 1.1f, -1.0f);      //Right Bottom

    //Bottom face
    glColor3f(red, green, blue);
    glVertex3f(0.8f, 1.0f, -1.5f);       //Right Top
    glVertex3f(0.4f, 1.0f, -1.5f);       //Left Top
    glColor3f(red - 0.4f, green - 0.4f, blue - 0.4f);
    glVertex3f(0.4f, 1.0f, -1.0f);       //Left Bottom
    glVertex3f(0.8f, 1.0f, -1.0f);       //Right Bottom
    glEnd(); 

    //To draw lines
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    for(float i = 1.01f; i < 1.1f; i += 0.02)
    {
        glVertex3f(0.4f, i , -0.999f);
        glVertex3f(0.8f, i, -0.999f);
    }
    glEnd();

}

void hms_drawChair()
{
    //function declarations
    void hms_drawChairLeg();
    void hms_drawChairBackSurface(void);
    void hms_drawChairSittingSurface(void);

    //code
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -0.3f);
    hms_drawChairLeg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4f, -1.0f, -0.3f);
    hms_drawChairLeg();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.4f, -1.0f, -0.6f);
    hms_drawChairLeg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -0.6f);
    hms_drawChairLeg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -0.3f);
    hms_drawChairSittingSurface();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -0.3f);
    hms_drawChairBackSurface();
    glPopMatrix();
}

void hms_drawChairSittingSurface(void)
{
    glBegin(GL_QUADS);
    //Front face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.5f, 0.0f);       //Right Top
    glVertex3f(-0.4f, 0.5f, 0.0f);       //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.4f, 0.0f);       //Left Bottom
    glVertex3f(0.1f, 0.4f, 0.0f); 	    //Right Bottom

    //Right face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.5f, -0.4f);      //Right Top
    glVertex3f(0.1f, 0.5f, 0.0f);        //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.1f, 0.4f, 0.0f);        //Left Bottom
    glVertex3f(0.1f, 0.4f, -0.4f);      //Right Bottom

    //Back face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.5f, -0.4f);       //Right Top
    glVertex3f(-0.4f, 0.5f, -0.4f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.4f, -0.4f);      //Left Bottom
    glVertex3f(0.1f, 0.4f, -0.4f);       //Right Bottom

    //Left face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(-0.4f, 0.5f, 0.0f);        //Right Top
    glVertex3f(-0.4f, 0.5f, -0.4f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f); 
    glVertex3f(-0.4f, 0.4f, -0.4f);      //Left Bottom
    glVertex3f(-0.4f, 0.4f, 0.0f);        //Right Bottom

    //Top face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.5f, -0.4f);        //Right Top
    glVertex3f(-0.4f, 0.5f, -0.4f);       //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.5f, 0.0f);         //Left Bottom
    glVertex3f(0.1f, 0.5f, 0.0f);          //Right Bottom

    //Bottom face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.4f, -0.4f);       //Right Top
    glVertex3f(-0.4f, 0.4f, -0.4f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.4f, 0.0f);        //Left Bottom
    glVertex3f(0.1f, 0.4f, 0.0f);        //Right Bottom
    glEnd();
}

void hms_drawChairBackSurface(void)
{
    glBegin(GL_QUADS);
    //Front face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);         
    glVertex3f(0.1f, 0.9f, 0.0f);       //Right Top
    glVertex3f(-0.4f, 0.9f, 0.0f);       //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.5f, 0.0f);       //Left Bottom
    glVertex3f(0.1f, 0.5f, 0.0f); 	    //Right Bottom

    //Right face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);  
    glVertex3f(0.1f, 0.9f, -0.05f);      //Right Top
    glVertex3f(0.1f, 0.9f, 0.0f);        //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.1f, 0.5f, 0.0f);        //Left Bottom
    glVertex3f(0.1f, 0.5f, -0.05f);      //Right Bottom

    //Back face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);  
    glVertex3f(0.1f, 0.9f, -0.05f);       //Right Top
    glVertex3f(-0.4f, 0.9f, -0.05f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.5f, -0.05f);      //Left Bottom
    glVertex3f(0.1f, 0.5f, -0.05f);       //Right Bottom

    //Left face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(-0.4f, 0.9f, 0.0f);        //Right Top
    glVertex3f(-0.4f, 0.9f, -0.05f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.5f, -0.05f);      //Left Bottom
    glVertex3f(-0.4f, 0.5f, 0.0f);        //Right Bottom

    //Top face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.9f, -0.05f);        //Right Top
    glVertex3f(-0.4f, 0.9f, -0.05f);       //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.9f, 0.0f);         //Left Bottom
    glVertex3f(0.1f, 0.9f, 0.0f);          //Right Bottom

    //Bottom face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.5f, -0.05f);       //Right Top
    glVertex3f(-0.4f, 0.5f, -0.05f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(-0.4f, 0.5f, 0.0f);        //Left Bottom
    glVertex3f(0.1f, 0.5f, 0.0f);        //Right Bottom
    glEnd();
}

void hms_drawChairLeg(void)
{
    glBegin(GL_QUADS);
	//Front face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f);        
    glVertex3f(0.1f, 0.4f, 0.0f);       //Right Top
    glVertex3f(0.0f, 0.4f, 0.0f);       //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);       //Left Bottom
    glVertex3f(0.1f, 0.0f, 0.0f); 	    //Right Bottom

    //Right face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.4f, -0.05f);      //Right Top
    glVertex3f(0.1f, 0.4f, 0.0f);        //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.1f, 0.0f, 0.0f);        //Left Bottom
    glVertex3f(0.1f, 0.0f, -0.05f);      //Right Bottom
    
    //Back face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.4f, -0.05f);       //Right Top
    glVertex3f(0.0f, 0.4f, -0.05f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.0f, 0.0f, -0.05f);      //Left Bottom
    glVertex3f(0.1f, 0.0f, -0.05f);       //Right Bottom

    //Left face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.0f, 0.4f, 0.0f);        //Right Top
    glVertex3f(0.0f, 0.4f, -0.05f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.0f, 0.0f, -0.05f);      //Left Bottom
    glVertex3f(0.0f, 0.0f, 0.0f);        //Right Bottom

    //Top face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.4f, -0.05f);        //Right Top
    glVertex3f(0.0f, 0.4f, -0.05f);       //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.0f, 0.4f, 0.0f);         //Left Bottom
    glVertex3f(0.1f, 0.4f, 0.0f);          //Right Bottom

    //Bottom face
    glColor3f(160.0f / 255.0f,64.0f / 255.0f,0.0f); 
    glVertex3f(0.1f, 0.0f, -0.05f);       //Right Top
    glVertex3f(0.0f, 0.0f, -0.05f);      //Left Top
    glColor3f(140.0f / 255.0f,44.0f / 255.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);        //Left Bottom
    glVertex3f(0.1f, 0.0f, 0.0f);        //Right Bottom
    glEnd();
}
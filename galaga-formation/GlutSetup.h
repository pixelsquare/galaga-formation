#define _USE_MATH_DEFINES
#ifndef __GLUTSETUP_H__
#define __GLUTSETUP_H__

#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>

/* OpenGL Library */
#include <glut.h>

// Window Dimension
const int width = 800;
const int height = 600;

//For Keyboard Keys
float AngleY = 0.0;
float AngleX = 0.0;

//For Camera
float LookX = 0.0f;
float LookY = 0.0f;
float LookZ = 50.0f;

// For Spheres
int stacks = 50;
int slices = 50;

// -------------- //

// RENDERING OBJECTS
void Scene();
void GamePLay();
void Keys(unsigned char key, int x, int y);
//void KeyUp(unsigned char key, int x, int y);
bool KeyDown[256];

/* Initiates 3D Rendering (LIGHTING) */
void Lighting()
{	
	//Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2, 0.2, 1.0}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5, 0.5, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}

/* Controls framerate */
void Timer(int extra)
{
  glutPostRedisplay();
  glutTimerFunc(10, Timer, extra);
}

/* Controls the camera */
void ResizeWindow(int w, int h)
{
  float ratio = 1.0 * w / h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, w, h);
  
  gluPerspective(45.0, ratio, 1, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Not yet used
void SpecialKeys(int key, int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_UP:
      AngleX -= 1.0;
      break;
 
    case GLUT_KEY_DOWN:
      AngleX += 1.0;
      break;
 
    case GLUT_KEY_LEFT:
      AngleY -= 1.0;
      break;
 
    case GLUT_KEY_RIGHT:
      AngleY += 1.0;
      break;
  }
}
 
/* Main program */
void GLUTmain(int argc, char **argv, const char *windowTitle)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow(windowTitle);
	initRendering();
	Lighting();
 
	glutReshapeFunc(ResizeWindow);
	glutTimerFunc(0, Timer, 0);
 
	glutDisplayFunc(Scene);

	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(Keys);
	
	glutMainLoop();
	return;
}
#endif
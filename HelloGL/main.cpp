#include "HelloGL.h"
#include "SceneManager.h"

#include "GL/freeglut.h"
#include <gl/GLU.h>
#include <iostream>
#include "GLUTCallbacks.h"

SceneManager* sceneManager; //scene manager reference

void InitWindow(int argc, char* argv[]); //init window function

int main(int argc, char* argv[]) 
{
	InitWindow(argc, argv); //create the window
	sceneManager = new SceneManager(); // set the scene manager
	return 0; // Assumes a succsesful exit if our game does in fact exit
}

void InitWindow(int argc, char* argv[])
{
	//create the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Gabi Maczynska OpenGL Program");

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 800, 800);
	gluPerspective(90, 1, 1, 1000);

	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

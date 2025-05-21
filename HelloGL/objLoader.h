#ifndef _OBJLOADER_H
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class objLoader
{
public:

	//Constructor
	objLoader();

	//Functions
	float* calculateNormal(float* coord1, float* coord2, float* coord3);
	int Load(char* filename);
	void Draw();
	void Release();
	void Update();

	//Variables (public)
	float* normals;
	float* triangleFaces;
	float* vertexBuffer;
	long totalPoints;
	long totalTriangles;

private:
	//Varibles (private)
	Vector3 _position;
	GLfloat _rotation;
};

#endif // !_OBJLOADER_H


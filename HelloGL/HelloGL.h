#pragma once
#include <Windows.h> //Requried for OpenGL on windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL utilities
#include "GL\freeglut.h" //freeglut library
#include"Structures.h"
#include "Cube.h"
#include "MeshLoader.h"
#include"SceneObject.h"
#include "StaticObjects.h"
#include "BMPLoader.h"
#include "LinkedLists.h"
#include "Scene.h"
#include "objLoader.h"

#define REFRESHRATE 16
#define CAMERAMOVESPEED 18
class HelloGL : Scene
{
public:
	//Constructor
	HelloGL();

	//Destroctor
	~HelloGL(void);

	//Functions
	void Display();
	void Update();
	void keyboard(unsigned char key, int x, int y);
	void DrawString(const char* text, void* font, Vector3* position, Color* color, int x, int y);
	void LoadOBJ();

	//Init Functions
	void InitObjects();
	void InitGL();
	void InitLighting();

private:

	//Variables
	Camera* camera;
	float deltaTime;
	float prevElapsedTime = 0;
	SceneObject* objects[200];
	Vector4* _lightPosition;
	Lighting* _lightData;	

	//Obj Variables
	objLoader objObject;
	Vector3 objPos;
	GLfloat objRotx;
};


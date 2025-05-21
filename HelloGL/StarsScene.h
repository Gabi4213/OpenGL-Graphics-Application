#pragma once
#include "GLUTCallbacks.h"
#include "Scene.h"
#include "SceneObject.h"
#include <Windows.h> //Requried for OpenGL on windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL utilities
#include "GL\freeglut.h" //freeglut library
#include"Structures.h"
#include "Cube.h"
#include "MeshLoader.h"
#include "StaticObjects.h"
#include "BMPLoader.h"
#include "StaticCube.h"

class StarsScene : Scene //Inherits from scene
{
public:
	//Constructor
	StarsScene();

	//Destructor
	~StarsScene(void);

	//Functions
	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void DrawString(const char* text, Vector3* position, Color* color, int x, int y);
	void SetUpMaterial();

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
	Material* _material;
};


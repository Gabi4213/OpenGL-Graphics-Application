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

#define CUBESPEED 5 //the speed at which the cube moves

class CollisionsScene : Scene
{
public:
	CollisionsScene(); //constructor
	~CollisionsScene(void); //destructor

	//functions
	void Display(); 
	void Update();
	void Keyboard(unsigned char key, int x, int y);

	//Init Functions
	void InitObjects();
	void InitLighting();
	void InitGL();

	//Extra Functions
	float CalculateCollisionDistance(SceneObject* object1, SceneObject* object2);
	void Collisions();
	void DrawString(const char* text, void* font, Vector3* position, Color* color, int x, int y);

private:
	//Variables/Definitions
	Camera* camera;
	float deltaTime;
	float ElapsedTime = 0;
	SceneObject* objects[2];
	Vector4* _lightPosition;
	Lighting* _lightData;
	Material* _material;
};


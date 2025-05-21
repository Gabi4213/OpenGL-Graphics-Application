#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "GL/freeglut.h"
#include "Structures.h"

class Scene
{
public:
	//Constructor
	Scene();

	//Destructor
	~Scene(void);

	//init Functions
	virtual void InitGL();
	virtual void InitLighting();
	virtual void InitObjects();

	//Functions
	virtual void Display();
	virtual void Update();

	//Variables
	Camera* camera;
	Vector4* _lightPosition;
	Lighting* _lightData;
	Material* _material;
};


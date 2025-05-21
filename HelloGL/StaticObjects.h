#pragma once
#include "SceneObject.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class StaticObjects : public SceneObject //inherits from scene object
{
public:
	//Constructor
	StaticObjects(Mesh* mesh, float x, float y, float z);

	//Destructor
	~StaticObjects();

	//Functions
	virtual void Update();
	virtual void Draw();
	
private:
	//Variables
	Vector3 _position;
};


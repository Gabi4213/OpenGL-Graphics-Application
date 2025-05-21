#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class StaticCube : public SceneObject //Inherits from scene object
{
public:
	//Constructor
	StaticCube(Mesh* mesh, Texture2D* texture, float x, float y, float z);

	//Destructor
	~StaticCube();

	//Functions
	void Draw();
	void SetupMaterial();
	
private:
	//Variables
	Material* _material;
};


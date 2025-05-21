#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject //inherits from the sceneobject file
{
public:
	//constructor
	Cube(Mesh* mesh,Texture2D* texture,float x, float y, float z);

	//destructor
	~Cube();

	//Functions
	void Draw();
	void Update();
	void SetupMaterial();

private:
	//variables
	GLfloat _rotation;
	Vector3 _position;
	Material* _material;
};



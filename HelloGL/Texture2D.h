#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
class Texture2D
{
public:
	//Constructor
	Texture2D();

	//Destructor
	~Texture2D();

	//Functions
	bool Load(char* path, int width, int height);	
	bool LoadDataFile(char* dataPath, int width, int height);
	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

private:
	//Textures
	GLuint _ID; //This is for the texture ID
	int _width, _height;
};


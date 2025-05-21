#pragma once
#include <Windows.h>
#include "Structures.h"
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL utilities
#include "GL\freeglut.h" //freeglut library

#define REFRESHRATE	16 // The Refresh Rate

//Classes
class Scene; 

class SceneManager
{
public:
	//Constructor
	SceneManager();

	//Desrtuctor
	~SceneManager(void);

	//Functions
	void Display();
	void Update();
	void SwitchScene(SCENES nextScene);
	void Keyboard(unsigned char key, int x, int y);

	//Init Functions
	void InitGL();

private:
	//Variables
	Scene* currentScene;
};


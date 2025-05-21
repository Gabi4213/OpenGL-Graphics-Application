#pragma once
#include <Windows.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "GLUTCallbacks.h"
#include "Scene.h"
#include "Texture2D.h"

class MenuScene : Scene //inherits from scene
{
public:
	//Constructor
	MenuScene();

	//Destructor
	~MenuScene(void);

	//Functions
	void Display();
	void Update();
	void CreateUI();
	void CreateSquares();
	void SetUpMaterial();
	void DrawString(const char* text, void* font, Vector3* position, Color* color, int x, int y);

	//Init Functions
	void InitGL();
	void InitLighting();
	void InitObjects();

private:
	//Variables
	Material* _material;
	Texture2D* _texture;
};


#pragma once
#include "HelloGL.h"

//Classes 
class SceneManager;
class MenuScene;
class StarsScene;
class CollisionsScene;
class HelloGl;

namespace GLUTCallbacks
{
	//init Functions
	void Init(HelloGL* gl);
	void Init(SceneManager* gl);
	void Init(MenuScene* gl);
	void Init(StarsScene* gl);
	void Init(CollisionsScene* gl);

	//Other Functions
	void Display();
	void Timer(int prefferedRefresh);
	void keyboard(unsigned char key, int x, int y);
}
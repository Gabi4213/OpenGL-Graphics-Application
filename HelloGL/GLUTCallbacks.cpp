#include "GLUTCallbacks.h"

#include "HelloGL.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "StarsScene.h"
#include "CollisionsScene.h"

namespace GLUTCallbacks 
{
	namespace  //annonymouse namespace
	{
		//reference all the scenes
		HelloGL* helloGL = nullptr;
		SceneManager* sceneManager = nullptr;
		MenuScene* menuScene = nullptr;
		StarsScene* starsScene = nullptr;
		CollisionsScene* collisionsScene = nullptr;
	}

	//init functions for the scenes
	void Init(HelloGL* gl) 
	{
		starsScene = nullptr;
		menuScene = nullptr;
		collisionsScene = nullptr;
		helloGL = gl;
	}

	void Init(SceneManager* gl)
	{
		sceneManager = gl;
	}

	void Init(MenuScene* gl)
	{	
		starsScene = nullptr;
		helloGL = nullptr;
		collisionsScene = nullptr;
		menuScene = gl;
	}

	void Init(StarsScene* gl) 
	{
		menuScene = nullptr;
		helloGL = nullptr;
		collisionsScene = nullptr;
		starsScene = gl;
	}

	void Init(CollisionsScene* gl) 
	{
		menuScene = nullptr;
		helloGL = nullptr;
		starsScene = nullptr;
		collisionsScene = gl;
	}

	void Display()
	{
		//if a scene is not null then display it
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
		else if (menuScene != nullptr) 
		{
			menuScene->Display();
		}
		else if (starsScene != nullptr) 
		{
			starsScene->Display();
		}
		else if (collisionsScene != nullptr) 
		{
			collisionsScene->Display();
		}
	}

	void Timer(int prefferedRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME); //update time

		//if a scene is not null then call the update function of that scene
		if (helloGL != nullptr)
		{
			helloGL->Update();
		}
		else if (menuScene != nullptr) 
		{
			menuScene->Update();
		}
		else if (starsScene != nullptr) 
		{
			starsScene->Update();
		}
		else if (collisionsScene != nullptr)
		{
			collisionsScene->Update();
		}

		//update time
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(prefferedRefresh - updateTime, GLUTCallbacks::Timer, prefferedRefresh);
	}

	void keyboard(unsigned char key, int x, int y) 
	{
		sceneManager->Keyboard(key, x, y); //scene manager keybaord (allways active)

		//only call the scene keyboard fucntions if they are active
		if (starsScene != nullptr) 
		{
			starsScene->Keyboard(key, x, y);
		}
		else if (collisionsScene != nullptr) 
		{
			collisionsScene->Keyboard(key, x, y);
		}
		else if (helloGL != nullptr)
		{
			helloGL->keyboard(key, x, y);
		}
	}
}
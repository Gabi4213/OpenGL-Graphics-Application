#include "SceneManager.h"
#include "GLUTCallbacks.h"
#include "MenuScene.h"
#include "StarsScene.h"
#include "CollisionsScene.h"
#include "HelloGL.h"

SceneManager::SceneManager()
{
	currentScene = NULL; //set the scene to nukll
	InitGL();
	SwitchScene(MENU_SCENE); //call the swithc scene to the menu scene
}

SceneManager::~SceneManager(void)
{
	//delete the current scene and set it to null
	delete currentScene;
	currentScene = NULL;
}

void SceneManager::InitGL() 
{
	//call the functions
	GLUTCallbacks::Init(this);
	glutKeyboardFunc(GLUTCallbacks::keyboard);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
}

void SceneManager::Update() 
{	
	currentScene->Update(); //call teh current scene update
}

void SceneManager::Display()
{
	currentScene->Display(); //call the current scene dispaly
}

void SceneManager::SwitchScene(SCENES nextScene)
{
	//set up the different temporary references to the scenes
	MenuScene* temporaryMenu;
	StarsScene* temporaryStars;
	CollisionsScene* temporaryCollisions;
	HelloGL* temporaryHelloGL;

	//switch statement to switch between differnt scenes
	switch (nextScene)
	{
	case MENU_SCENE:
		temporaryMenu = new MenuScene();
		currentScene = (Scene*)temporaryMenu;
		temporaryMenu = NULL;
		break;
	case STARS_SCENE:
		temporaryStars = new StarsScene();
		currentScene = (Scene*)temporaryStars;
		temporaryStars = NULL;
		break;
	case COLLISION_SCENE:
		temporaryCollisions = new CollisionsScene();
		currentScene = (Scene*)temporaryCollisions;
		temporaryCollisions = NULL;
		break;
	case HELLOGL_SCENE:
		temporaryHelloGL = new HelloGL();
		currentScene = (Scene*)temporaryHelloGL;
		temporaryHelloGL = NULL;
		break;
		
	deafult: //if no scenes where able to be laoded
		std::cout << "Sorry but there was an error and no scenes where able to be loaded" << std::endl;
		break;
	}
}


void SceneManager::Keyboard(unsigned char key, int x, int y) 
{
	//check for use input
	if (key == '1' || key == '2' || key == '3'||key == 27)
	{
		delete currentScene;
		currentScene = NULL;
	}

	//different key inputs for differnt scenes
	if (key == '1')
	{
		SwitchScene(MENU_SCENE);
	}
	else if (key == '2')
	{
		SwitchScene(STARS_SCENE);
	}
	else if (key == '3') 
	{
		SwitchScene(COLLISION_SCENE);
	}
	else if (key == '4') 
	{
		SwitchScene(HELLOGL_SCENE);
	}

	if (key == 27) //escape
	{
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}
}
	




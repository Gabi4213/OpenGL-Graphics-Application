#include "CollisionsScene.h"
#include "StaticCube.h"

CollisionsScene::CollisionsScene()
{
	//call the functions
	InitGL();
	InitObjects();
	InitLighting();
	glutMainLoop();
}

CollisionsScene::~CollisionsScene(void)
{
	Scene::~Scene(); //inherit from the scene destructor
}

void CollisionsScene::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //This Clears the Scene

	//draw the objects
	for (int i = 0; i < 2; i++)
	{
		objects[i]->Draw();
	}

	//create the text
	Vector3 v = { 0.0f, 0.0f, 1.0f };
	Color c = { 1.0f, 1.0f, 1.0f };
	DrawString("Collisions Scene", GLUT_BITMAP_TIMES_ROMAN_24, &v, &c, 25, 85);
	DrawString("A & D - Move Left & Right", GLUT_BITMAP_9_BY_15, &v, &c, 28, 75);
	DrawString("W & S - Move Up & Down", GLUT_BITMAP_9_BY_15, &v, &c, 28, 70);
	DrawString("Q & E - Rotate Left & Right", GLUT_BITMAP_9_BY_15, &v, &c, 29, 65);
	DrawString("1-Main Menu", GLUT_BITMAP_9_BY_15, &v, &c, 20, -70);

	//call the collisions function
	Collisions();

	glFlush(); //Flushes the scene drawn to the graphics cards
	glutSwapBuffers(); //swap the buffers of the scene	
}

void CollisionsScene::Update()
{
	//set up delta time and elapsedtime
	deltaTime = (glutGet(GLUT_ELAPSED_TIME) / 1000.0f) - ElapsedTime;
	ElapsedTime = (glutGet(GLUT_ELAPSED_TIME) / 1000.0f);

	//call the identity function
	glLoadIdentity(); 

	//call the objects update functions
	objects[0]->Update();
	objects[1]->Update();

	//redisplay and look at the camera positions
	glutPostRedisplay();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
}

void CollisionsScene::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd') //move cube right if 'D' key is pressed //RIGHT
	{
		objects[0]->_position.x -= 0.02 * CUBESPEED;
	}

	if (key == 'a') //move cube left if 'A' key is pressed //LEFT
	{
		objects[0]->_position.x += 0.02 * CUBESPEED;
	}

	if (key == 'w') //move cube up if 'W' key is pressed //RIGHT
	{
		objects[0]->_position.y += 0.02 * CUBESPEED;
	}

	if (key == 's') //move cube down if 'S' key is pressed //LEFT
	{
		objects[0]->_position.y -= 0.02 * CUBESPEED;
	}

	if (key == 'q') //rotate cube left if 'Q' key is pressed //LEFT
	{
		objects[0]->_rotation += 0.5 * CUBESPEED;
	}

	if (key == 'e') //rotate cube right if 'E' key is pressed //RIGHT
	{
		objects[0]->_rotation -= 0.5 * CUBESPEED;
	}
}

float CollisionsScene::CalculateCollisionDistance(SceneObject* object1, SceneObject* object2) 
{
	//calculate the distance between the two objects and return this distance
	float distance = ((object1->_position.x - object2->_position.x) * (object1->_position.x - object2->_position.x))
		+ ((object1->_position.y - object2->_position.y) * (object1->_position.y - object2->_position.y))
		+ ((object1->_position.z - object2->_position.z) * (object1->_position.z - object2->_position.z));
	return distance;
}

void CollisionsScene::Collisions()
{
	float distance = CalculateCollisionDistance(objects[0], objects[1]); //grab the distance
	bool distanceSquared = true; //set the boolean to true
	float radiusDistance; //create a new variable for the distance

	if (distanceSquared) //if it has been square /set to true
	{
		radiusDistance = pow(objects[0]->_radius + objects[1]->_radius, 2);
	}		
	else //if it has not been squared or set to true
	{
		radiusDistance = objects[0]->_radius + objects[1]->_radius;
	}

	if (distance <= radiusDistance) // if collision occurs
	{
		//create the text
		Vector3 v = { 0.0f, 0.0f, 1.0f };
		Color c = { 1.0f, 1.0f, 1.0f };
		DrawString("Collision Occured", GLUT_BITMAP_TIMES_ROMAN_24, &v, &c, 25, 20);
	}
}

void CollisionsScene::InitObjects()
{
	//set up the camera
	camera = new Camera();
	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;

	camera->eye.x = 5.0f;
	camera->eye.y = 5.0f;
	camera->eye.z = -100.0f;

	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;

	//create references to the textures and the mesh
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Texture2D* RubixTexture = new Texture2D();
	RubixTexture->LoadDataFile(BMPLoader::LoadBitMap("RubixCubeFace.bmp"), 512, 512);

	Texture2D* LuckyBlockTexture = new Texture2D();
	LuckyBlockTexture->LoadDataFile(BMPLoader::LoadBitMap("LuckyBlock.bmp"), 512, 512);

	//Linked Lists
	LinkedLists* lists = new LinkedLists();
	ListNode* head = nullptr;

	//create the objects
	objects[0] = new StaticCube(cubeMesh, LuckyBlockTexture, 3,4,-94.05);
	objects[1] = new StaticCube(cubeMesh, RubixTexture, 7, 4, -94);
}

void CollisionsScene::InitGL()
{
	Scene::InitGL(); //call the scene InitGL
	GLUTCallbacks::Init(this); //set this callback 
	glutDisplayFunc(GLUTCallbacks::Display); //call the display fucntion
}

void CollisionsScene::InitLighting()
{
	Scene::InitLighting(); //call the lighting int he scene cpp
}

void CollisionsScene::DrawString(const char* text, void* font, Vector3* position, Color* color, int x, int y)
{
	//draw the string with the given text,font,position, color and raster position
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(color->r, color->g, color->b);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(x, y);
	glutBitmapString(font, (unsigned char*)text);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}


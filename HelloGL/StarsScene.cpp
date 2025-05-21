#include "StarsScene.h"

StarsScene::StarsScene() 
{
	//call the functions
	InitGL();
	InitObjects();
	InitLighting();
	glutMainLoop();
}

StarsScene::~StarsScene(void)
{
	Scene::~Scene(); //call the scene destructor
}

void StarsScene::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //This Clears the Scene

	//draw the objects (loop through them)
	for (int i = 0; i < 100; i++)
	{
		objects[i]->Draw();
	}

	//create the string
	Vector3 v = { 0.0f, 0.0f, 1.0f };
	Color c = { 1.0f, 1.0f, 1.0f };
	DrawString("WASD - To Move", &v, &c, 25, 75);
	DrawString("1-Main Menu", &v, &c, 20, 65);

	glFlush(); //Flushes the scene drawn to the graphics cards
	glutSwapBuffers(); //swap the buffers of the scene	
}

void StarsScene::Update() 
{
	//create the delta time and elapsed time
	deltaTime = (glutGet(GLUT_ELAPSED_TIME) / 1000.0f) - prevElapsedTime;
	prevElapsedTime = (glutGet(GLUT_ELAPSED_TIME) / 1000.0f);

	glLoadIdentity();

	//lighting setup
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	//update the objects in a for loop
	for (int i = 0; i < 100; i++)
	{
		objects[i]->Update();
	}

	//redisplay and look at the camera
	glutPostRedisplay();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
}

void StarsScene::Keyboard(unsigned char key, int x, int y)
{
	//keybaord inputs 

	if (key == 'd') //increase rotation float if 'D' key is pressed //RIGHT
	{
		camera->eye.z += 0.0003f * CAMERAMOVESPEED * deltaTime;
		camera->eye.x += -0.9f * CAMERAMOVESPEED * deltaTime;
		camera->center.x += 0.0003f * CAMERAMOVESPEED * deltaTime;
		camera->center.z += -0.9f * CAMERAMOVESPEED * deltaTime;
	}

	if (key == 'a') //increase rotation float if 'A' key is pressed //LEFT
	{
		camera->eye.z -= 0.0003f * CAMERAMOVESPEED * deltaTime;
		camera->eye.x -= -0.9f * CAMERAMOVESPEED * deltaTime;
		camera->center.x -= 0.0003f * CAMERAMOVESPEED * deltaTime;
		camera->center.z -= -0.9f * CAMERAMOVESPEED * deltaTime;
	}

	if (key == 'w') //increase rotation float if 'D' key is pressed //RIGHT
	{
		camera->center.x -= cos(-90 * 3.141f / 180.0f) * CAMERAMOVESPEED * deltaTime;
		camera->center.z -= sin(-90 * 3.141f / 180.0f) * CAMERAMOVESPEED * deltaTime;
		camera->eye.x -= cos(-90 * 3.141f / 180.0) * CAMERAMOVESPEED * deltaTime;
		camera->eye.z -= sin(-90 * 3.141f / 180.0) * CAMERAMOVESPEED * deltaTime;
	}

	if (key == 's') //increase rotation float if 'A' key is pressed //LEFT
	{
		camera->center.x += cos(-90 * 3.141f / 180.0f) * CAMERAMOVESPEED * deltaTime;
		camera->center.z += sin(-90 * 3.141f / 180.0f) * CAMERAMOVESPEED * deltaTime;
		camera->eye.x += cos(-90 * 3.141f / 180.0) * CAMERAMOVESPEED * deltaTime;
		camera->eye.z += sin(-90 * 3.141f / 180.0) * CAMERAMOVESPEED * deltaTime;
	}
}

void StarsScene::InitObjects() 
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

	//create references to the mesh and textures
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"stars.raw", 512, 512);

	Texture2D* levelTexture = new Texture2D();
	levelTexture->LoadDataFile(BMPLoader::LoadBitMap("BMPTexture.bmp"), 512, 512);

	//Linked Lists
	LinkedLists* lists = new LinkedLists();
	ListNode* head = nullptr;

	//create the objects (for loop)
	for (int i = 0; i < 50; i++)
	{
		objects[i] = new StaticCube(cubeMesh, levelTexture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	for (int i = 50; i < 100; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
}

void StarsScene::InitGL() 
{
	//call functions
	Scene::InitGL();
	GLUTCallbacks::Init(this);
	glutDisplayFunc(GLUTCallbacks::Display);
}

void StarsScene::InitLighting() 
{	
	//lighting set up
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 2.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 1;
	_lightData->Ambient.y = 1;
	_lightData->Ambient.z = 1;
	_lightData->Ambient.w = 1;
	_lightData->Diffuse.x = 0;
	_lightData->Diffuse.y = 0;
	_lightData->Diffuse.z = 0;
	_lightData->Diffuse.w = 0;
	_lightData->Specular.x = 1;
	_lightData->Specular.y = 1;
	_lightData->Specular.z = 1;
	_lightData->Specular.w = 1;

	//materials setup
	SetUpMaterial();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
}

void StarsScene::DrawString(const char* text, Vector3* position, Color* color, int x, int y) 
{
	//draw string
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(color->r, color->g, color->b);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void StarsScene::SetUpMaterial() 
{
	//material set up
	_material = new Material();

	_material->Ambient.x = 1.0; //red
	_material->Ambient.y = 1.0; //green
	_material->Ambient.z = 1.0; //blue
	_material->Ambient.w = 1.0;
						   
	_material->Diffuse.x = 1.0; //red
	_material->Diffuse.y = 1.0; //green
	_material->Diffuse.z = 1.0; //blue
	_material->Diffuse.w = 1.0;

	_material->Specular.x = 1.0;
	_material->Specular.y = 1.0;
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;

	_material->Shininess = 100.0f;
}


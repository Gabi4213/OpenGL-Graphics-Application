#include "MenuScene.h"

MenuScene::MenuScene() : Scene()
{
	//call the functions
	InitGL();
	InitLighting();
	InitObjects();
	glutMainLoop();
}

MenuScene::~MenuScene(void)
{
	//call the scene destructor
	Scene::~Scene(); 

	//delete the texture and material
	delete _texture;
	_texture = NULL;
	delete _material;
	_material = NULL;
}

void MenuScene::InitGL()
{
	//call the scene initgl and the inti calback
	Scene::InitGL();
	GLUTCallbacks::Init(this);
	glutDisplayFunc(GLUTCallbacks::Display);
}

void MenuScene::InitLighting()
{
	Scene::InitLighting(); //use the scene lighting
}

void MenuScene::InitObjects() 
{	
	//call the scene objects
	Scene::InitObjects();

	//set up the texture
	_texture = new Texture2D();
	_texture->LoadDataFile(BMPLoader::LoadBitMap("MainMenu.bmp"), 512, 512);
}

void MenuScene::Display()
{
	//call the functions to create the squares and ui & clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Vector3 v = { 0.0f, 0.0f, 1.0f };
	Color c = { 1.0f, 1.0f, 1.0f };
	CreateUI();
	CreateSquares();

	glFlush(); //flush the disaply
	glutSwapBuffers();
}

void MenuScene::Update()
{
	//laod the identity and the scene update
	glLoadIdentity();
	Scene::Update();

	//setup lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	glutPostRedisplay();
}

void MenuScene::CreateUI()
{
	//disable the lighting and 2D texture
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Text Positions
	Vector3 MainMenuTitle = { -1.8f, 1.75f, -1.0f };
	Vector3 CreditsTitle = { -1.8f, 1.65f, -1.0f };
	Vector3 Line1 = { -2.5f, 1.45f, -1.0f };
	Vector3 Line2 = { -1.75f, 1.45f, -1.0f };
	Vector3 Line3 = { -1.0f, 1.45f, -1.0f };
	Vector3 Line4 = { -0.25f, 1.45f, -1.0f };
	Vector3 Line5 = { -1.25f, -1.35f, -1.0f };

	//Color
	Color colorWhite = { 1.0f, 1.0f, 1.0f };

	//set up the string
	DrawString("---------------------MAIN MENU---------------------", GLUT_BITMAP_TIMES_ROMAN_24, &MainMenuTitle, &colorWhite, 0.0, 0.0f);
	DrawString("Program Crearted By: Gabi Maczynska",GLUT_BITMAP_8_BY_13, &CreditsTitle, &colorWhite, 1.0f, 0.0f);
	DrawString("1. Main Menu", GLUT_BITMAP_8_BY_13, &Line1, &colorWhite, 1.0f, 0.0f);
	DrawString("2. Stary Cubes", GLUT_BITMAP_8_BY_13, &Line2, &colorWhite, 1.0f, 0.0f);
	DrawString("3. Collisions", GLUT_BITMAP_8_BY_13, &Line3, &colorWhite, 1.0f, 0.0f);
	DrawString("4. Obj Object", GLUT_BITMAP_8_BY_13, &Line4, &colorWhite, 1.0f, 0.0f);
	DrawString("ESC TO EXIT", GLUT_BITMAP_8_BY_13, &Line5, &colorWhite, 1.0f, 0.0f);

	//enable the lighting and 2d texture
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void MenuScene::CreateSquares()
{
	//Square 1
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glBegin(GL_QUADS);

	// top left
	glTexCoord2f(0.0f, 1.0f); 
	glVertex2f(-0.75, -0.65); 	
	// bottom left
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.75, -0.65); 
	// bottom right
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.75, 0.65);
	// bottom left
	glTexCoord2f(0.0f, 0.0f); 
	glVertex2f(-0.75, 0.65); 

	glEnd();
}

void MenuScene::SetUpMaterial()
{
	//set up the material
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void MenuScene::DrawString(const char* text, void* font, Vector3* position, Color* color,int x,int y)
{
	//draw the string
	glPushMatrix();
	glColor3f(color->r, color->g, color->b);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(x, y);
	glutBitmapString(font, (unsigned char*)text);
	glPopMatrix();
}
#include "HelloGL.h"
#include "GLUTCallbacks.h"

HelloGL::HelloGL() : Scene()
{	
	//call teh fucntions
	InitGL();
	InitObjects();
	InitLighting();
	glutMainLoop();
}

void HelloGL::InitObjects() 
{
	//camera set up
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

	//texture and object loading
	Texture2D* levelTexture = new Texture2D();
	levelTexture->LoadDataFile(BMPLoader::LoadBitMap("TeapotTexture.bmp"), 512, 512);
	objObject.Load((char*)"TeapotOBJ.obj");
}

void HelloGL::InitLighting() 
{
	//lighting set up
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 5;
	_lightData->Ambient.y = 5;
	_lightData->Ambient.z = 5;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 2;
	_lightData->Diffuse.y = 2;
	_lightData->Diffuse.z = 2;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void HelloGL::InitGL() 
{
	Scene::InitGL(); //call the initgl from scene
	GLUTCallbacks::Init(this); //call this as the init in callbacks
	glutDisplayFunc(GLUTCallbacks::Display); //call display function
}

void HelloGL::Display() 
{
	//create the text on screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //This Clears the Scene
	Vector3 v = { 0.0f, 0.0f, 1.0f };
	Color c = { 1.0f, 1.0f, 1.0f };
	DrawString("OBJ Scene", GLUT_BITMAP_TIMES_ROMAN_24, &v, &c, 15, 85);
	DrawString("W - Hold to manipulate the teapot", GLUT_BITMAP_9_BY_15, &v, &c, 35, 75);
	DrawString("1-Main Menu", GLUT_BITMAP_9_BY_15, &v, &c, 20, -70);

	//load the obj object
	LoadOBJ();

	glFlush(); //Flushes the scene drawn to the graphics cards
	glutSwapBuffers(); //swap the buffers of the scene	
}

void HelloGL::LoadOBJ()
{
	//set the obj position
	objPos.x = 5;
	objPos.y = 4;
	objPos.z = -94;
	//translate its positiona and set rotation
	glTranslatef(objPos.x, objPos.y, objPos.z);
	glRotatef(objRotx, 0, 0, 0);
	glRotatef(180, 0, 1, 0);

	//draw the object
	objObject.Draw();
}

void HelloGL::Update() 
{
	//load the identity
	glLoadIdentity();

	//set up lights
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	// look at the camera positions set earlier
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
}

void HelloGL::DrawString(const char* text, void* font, Vector3* position, Color* color, int x, int y)
{
	//draw the string with the given text,font,position, color and raster position
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(color->r, color->g, color->b);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void HelloGL::keyboard(unsigned char key,int x, int y)
{
	if (key == 'w') //increase rotation float if 'w' key is pressed
	{
		objRotx++;
	}
}

HelloGL::~HelloGL(void) //Destructor
{

}



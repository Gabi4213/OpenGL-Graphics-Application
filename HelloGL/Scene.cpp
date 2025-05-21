#include "Scene.h"

Scene::Scene()
{
	//constructor
}

Scene::~Scene(void)
{
	//delete the camera & lighting pos/data

	delete camera;
	camera = NULL;

	delete _lightPosition;
	_lightPosition = NULL;

	delete _lightData;
	_lightData = NULL;
}

void Scene::InitGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glutDetachMenu(GLUT_RIGHT_BUTTON);
}

void Scene::InitLighting()
{
	//set up lighting

	_lightPosition = new Vector4();

	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();

	_lightData->Ambient.x = 1.0;
	_lightData->Ambient.y = 1.0;
	_lightData->Ambient.z = 1.0;
	_lightData->Ambient.w = 1.0;

	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;

	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void Scene::InitObjects()
{
	//set up camera
	camera = new Camera();

	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;

	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;

	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;

	//set up material
	_material = new Material();

	_material->Ambient.x = 1;
	_material->Ambient.y = 1;
	_material->Ambient.z = 1;
	_material->Ambient.w = 1.0;

	_material->Diffuse.x = 1;
	_material->Diffuse.y = 1;
	_material->Diffuse.z = 1;
	_material->Diffuse.w = 1;

	_material->Specular.x = 1.0;
	_material->Specular.y = 1.0;
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;

	_material->Shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
}

void Scene::Display()
{

}

void Scene::Update()
{
	//look at the camera
	gluLookAt(camera->eye.x,camera->eye.y,camera->eye.z,camera->center.x,camera->center.y,camera->center.z,camera->up.x,camera->up.y,camera->up.z);
}

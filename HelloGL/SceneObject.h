#pragma once
#include "Structures.h"
#include "Texture2D.h"
class SceneObject
{
protected:
	Mesh* _mesh; //Mesh
public:
	//Constructor
	SceneObject(Mesh* mesh, Texture2D* texture);

	//Destructor
	virtual ~SceneObject();

	//Functions
	virtual void Update();
	virtual void Draw();

	//Variables
	Vector3 _position;
	GLfloat _rotation;
	float _radius = 1.0f;
	Texture2D* _texture;
};


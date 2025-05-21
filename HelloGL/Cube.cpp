#pragma once
#include "Cube.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	//set up the variables
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation =0.0f;
}

void Cube::Update() 
{
	//rotate at a random amount
	_rotation += rand() % 3 + 1;
}

void Cube::Draw()
{
	//draw the cubes
	if (_mesh->Indices != nullptr && _mesh->Normals != nullptr && _mesh->Vertices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);;
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0.0f, 0.0f, -1.0f);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}	
}

void Cube::SetupMaterial() 
{
	//setup adn create the material (purple in this case)
	_material = new Material();
	_material->Ambient.x = 0.8; 
	_material->Ambient.y = 0.05; 
	_material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;

	_material->Diffuse.x = 0.8; 
	_material->Diffuse.y = 0.05; 
	_material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;

	_material->Specular.x = 1.0; 
	_material->Specular.y = 1.0; 
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;

	_material->Shininess = 100.0f;
}

Cube::~Cube(void) //Destructor
{

}





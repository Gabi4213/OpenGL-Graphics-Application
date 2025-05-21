#include "StaticObjects.h"

StaticObjects::StaticObjects(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void StaticObjects::Update()
{
	
}

void StaticObjects::Draw()
{
	if (_mesh->Indices != nullptr && _mesh->Normals != nullptr && _mesh->Vertices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnable(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		//glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_NORMAL_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}


StaticObjects::~StaticObjects(void) //Destructor
{

}

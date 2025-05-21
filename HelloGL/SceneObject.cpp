#include "SceneObject.h"


SceneObject:: SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh; //reference the mesh
	_texture = texture; //reference teh texture
}


 void SceneObject::Draw()
{

}
 void SceneObject::Update()
 {

 }


SceneObject::~SceneObject() 
{

}
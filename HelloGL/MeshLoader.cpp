#include "MeshLoader.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	//call the functions
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);


	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount; //read the vertex count from the file

		if (mesh.VertexCount > 0) //check if vertecies are larger than 0
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++) //loop through the file until i reaches vertex count
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
		else //if vertecies are less than 0
		{
			std::cout << "sorry but there was no verticies" << std::endl;
		}
			
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		//read the file
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0) //check if count is greater than 0
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++) //loop through
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
		else //if colors are less than 0
		{
			std::cout << "sorry but there was no colors" << std::endl;
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TextCoordCount; //load the file

		if (mesh.TextCoordCount > 0) //check is texture count is greater than 0
		{
			mesh.TexCoords = new TexCoord[mesh.TextCoordCount];

			for (int i = 0; i < mesh.TextCoordCount; i++) //loop through
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
		else //if vertecies are less than 0
		{
			std::cout << "sorry but there was no textures count" << std::endl;
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount; //read the file

		if (mesh.IndexCount > 0) //chekc if gretaer than 0
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i++) //loop through
			{
				inFile >> mesh.Indices[i];
			}
		}
		else //if vertecies are less than 0
		{
			std::cout << "sorry but there was no indicies" << std::endl;
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		//create a new mesh & reference the fiel
		Mesh* mesh = new Mesh(); 
		ifstream inFile;
		inFile.open(path);

		//if there is something wrong with the file
		if (!inFile.good()) 
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//load the data witht hese functions
		LoadVertices(inFile, *mesh);			
		LoadNormals(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		//return the mesh
		return mesh;
	}
}
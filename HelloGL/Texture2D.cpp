#include "Texture2D.h"
#include <iostream>
#include <fstream>
using namespace std;

Texture2D::Texture2D() //constructor
{

}

bool Texture2D::Load(char* path, int width, int height) 
{
	//open the files and texture data
	char* tempTextrureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	//if the file is not good
	if (!inFile.good()) 
	{
		cerr << "Can't open the texture file " << path << endl;
		return false;
	}

	//seek to the begining and read the and close the file
	inFile.seekg(0, ios::end); //seek to the end of the file
	fileSize = (int)inFile.tellg(); // get the current posiiton in the file to the end, this results int he total file size
	tempTextrureData = new char[fileSize]; // create a brand new awway to store the data
	inFile.seekg(0, ios::beg); // seek to the beginning of the file
	inFile.read(tempTextrureData, fileSize); // Read in all the data in one go
	inFile.close();

	cout << path << "Loaded." << endl; //output text if loaded


	glGenTextures(1, &_ID); // Get the next Texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); // Bind the trexture to the ID
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextrureData); // Specify the details of the texture image
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextrureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	delete[] tempTextrureData; //Clear up the data
	return true;
}

bool Texture2D::LoadDataFile(char* dataPath, int width, int height)
{
	glGenTextures(1, &_ID);	//find and get ther next ID
	glBindTexture(GL_TEXTURE_2D, _ID);	//Bind the texture to the ID
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, dataPath);
	return true;
}

Texture2D::~Texture2D() //destructor
{
	glDeleteTextures(1, &_ID);
}
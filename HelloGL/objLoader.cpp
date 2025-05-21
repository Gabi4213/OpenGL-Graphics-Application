#include "objLoader.h"

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
using namespace std;

objLoader::objLoader()
{
	this->totalTriangles = 0;
	this->totalPoints = 0;
}

float* objLoader::calculateNormal(float* coord1, float* coord2, float* coord3)
{
	// Calculate the Vectors
	float firstVector[3], secondVector[3], vectorCrossProduct[3], normalisationFactor;

	firstVector[0] = coord1[0] - coord2[0];
	firstVector[1] = coord1[1] - coord2[1];
	firstVector[2] = coord1[2] - coord2[2];

	secondVector[0] = coord1[0] - coord3[0];
	secondVector[1] = coord1[1] - coord3[1];
	secondVector[2] = coord1[2] - coord3[2];

	// Vector Cross Product - Uses Two Edges
	vectorCrossProduct[0] = firstVector[1] * secondVector[2] - secondVector[1] * firstVector[2];
	vectorCrossProduct[1] = secondVector[0] * firstVector[2] - firstVector[0] * secondVector[2];
	vectorCrossProduct[2] = firstVector[0] * secondVector[1] - secondVector[0] * firstVector[1];

	// Normalisation  the Factor
	normalisationFactor = sqrt(vectorCrossProduct[0] * vectorCrossProduct[0] + vectorCrossProduct[1] * vectorCrossProduct[1] + vectorCrossProduct[2] * vectorCrossProduct[2]);

	// Normalise the Vector - For Correct Lighting
	float norm[3];
	norm[0] = vectorCrossProduct[0] / normalisationFactor;
	norm[1] = vectorCrossProduct[1] / normalisationFactor;
	norm[2] = vectorCrossProduct[2] / normalisationFactor;

	return norm;
}

int objLoader::Load(char* filename)
{
	// File is Opened
	string line;
	ifstream objFile(filename);

	if (objFile.is_open())
	{
		// Calculate File Size
		objFile.seekg(0, ios::end);
		long fileSize = objFile.tellg();

		// reset Position in FIle
		objFile.seekg(0, ios::beg);

		// Allocate Memory According to FIle Size
		vertexBuffer = (float*)malloc(fileSize);
		triangleFaces = (float*)malloc(fileSize * sizeof(float));
		normals = (float*)malloc(fileSize * sizeof(float));

		int triangle_index = 0;
		int normal_index = 0;

		while (!objFile.eof())
		{
			getline(objFile, line);

			// Lines Beginning with 'v' (verticies)
			if (line.c_str()[0] == 'v')
			{
				line[0] = ' ';

				sscanf_s(line.c_str(), "%f %f %f ",
					&vertexBuffer[totalPoints],
					&vertexBuffer[totalPoints + 1],
					&vertexBuffer[totalPoints + 2]);

				totalPoints += POINTS_PER_VERTEX;
			}
			// Lines Beginning with 'f' (faces)
			if (line.c_str()[0] == 'f')
			{
				line[0] = ' ';

				int vertexNumber[4] = { 0, 0, 0 };
				sscanf_s(line.c_str(), "%i%i%i",
					&vertexNumber[0],
					&vertexNumber[1],
					&vertexNumber[2]);

				vertexNumber[0] -= 1;
				vertexNumber[1] -= 1;
				vertexNumber[2] -= 1;

				int tCounter = 0;
				//Calculates faces as Triangles
				for (int i = 0; i < POINTS_PER_VERTEX; i++)
				{
					triangleFaces[triangle_index + tCounter] = vertexBuffer[3 * vertexNumber[i]];
					triangleFaces[triangle_index + tCounter + 1] = vertexBuffer[3 * vertexNumber[i] + 1];
					triangleFaces[triangle_index + tCounter + 2] = vertexBuffer[3 * vertexNumber[i] + 2];
					tCounter += POINTS_PER_VERTEX;
				}

				// Coordniates for Normals to Match Correctly
				float coord1[3] = { triangleFaces[triangle_index],	   triangleFaces[triangle_index + 1], triangleFaces[triangle_index + 2] };
				float coord2[3] = { triangleFaces[triangle_index + 3], triangleFaces[triangle_index + 4], triangleFaces[triangle_index + 5] };
				float coord3[3] = { triangleFaces[triangle_index + 6], triangleFaces[triangle_index + 7], triangleFaces[triangle_index + 8] };
				float* norm = this->calculateNormal(coord1, coord2, coord3);

				tCounter = 0;

				for (int i = 0; i < POINTS_PER_VERTEX; i++)
				{
					normals[normal_index + tCounter] = norm[0];
					normals[normal_index + tCounter + 1] = norm[1];
					normals[normal_index + tCounter + 2] = norm[2];
					tCounter += POINTS_PER_VERTEX;
				}

				triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
				normal_index += TOTAL_FLOATS_IN_TRIANGLE;
				totalTriangles += TOTAL_FLOATS_IN_TRIANGLE;
			}
		}
		objFile.close();
	}
	else
	{
		cout << "Sorry the file was unable to be loaded" << endl;
	}
	return 0;
}

void objLoader::Release()
{
	// Clears Variables for Next Object
	free(this->triangleFaces);
	free(this->normals);
	free(this->vertexBuffer);
}

void objLoader::Draw()
{
	//draw the object
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, triangleFaces);
	glNormalPointer(GL_FLOAT, 0, normals);
	glDrawArrays(GL_TRIANGLES, 0, totalTriangles);

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 0.0f, 0.0f, -1.0f);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void objLoader::Update()
{
	_rotation += rand() % 3 + 1; //rotate at a random amount
}
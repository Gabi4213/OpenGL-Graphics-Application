#include "BMPLoader.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

namespace BMPLoader 
{
	struct BitMap  //Basic ButMap Struct
	{
		//Defind the width, height & pixels
		unsigned int width, height; 
		unsigned char* pixels;
	};

	BitMap* bmp; //Create a BitMap struct called 'bmp'

	char* BMPLoader::LoadBitMap(const char* file)
	{
		bmp = nullptr; //set bmp to null
		ifstream inFile(file, ifstream::binary);
		if (inFile.good()) //If the file loads correctly and there is nothing wrong with it
		{
			//create a new bitmap struct & set all values to 0
			bmp = new BitMap(); 
			bmp->width = 0;
			bmp->height = 0;
			bmp->pixels = nullptr;

			//read from the file
			unsigned char info[54] = { 0 };
			inFile.read((char*)&info[0], 54);

			//Set the info of width & height
			bmp->width = *(unsigned int*)&info[18];
			bmp->height = *(unsigned int*)&info[22];

			//read the pixels & close the file
			unsigned long size = (bmp->width * bmp->height) * 3;
			bmp->pixels = new unsigned char[size];
			inFile.read((char*)bmp->pixels, size);
			inFile.close();

			//Change BGR to RGB - the default uses BGR but I have to use RGB
			for (int i = 0; i < size; i += 3) 
			{
				unsigned char temp = bmp->pixels[i];
				bmp->pixels[i] = bmp->pixels[i + 2];
				bmp->pixels[i + 2] = temp;
			}
			return (char*)bmp->pixels;
		}
		else //if the file is not good send a messege notifying the user
		{
			std::cout << "Couldn't load the file" << endl;
			return nullptr;
		}
	}
}
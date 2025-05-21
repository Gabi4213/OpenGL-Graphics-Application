#pragma once
#include<fstream>
#include<iostream>
#include "GL\freeglut.h"

// This 24 Bit Loader came from here: 
//https://www.daniweb.com/programming/software-development/threads/482083/reading-a-24-bit-bmp-image-file
// I used the code but slighty chanegd it to work with C++ and added some extra parts liek ensuring the file is good and if not then
//notify the player that its not.

namespace BMPLoader 
{
	char* LoadBitMap(const char* file); // char function for loading bitmaps
}

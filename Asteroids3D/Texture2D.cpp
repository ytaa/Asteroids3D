#include "Texture2D.h"


Texture2D::Texture2D(const char * _path, int _magFilter, int _minFilter)
	:path(_path)
	,id(-1)
{
	load(path, _magFilter, _minFilter);
}

Texture2D::~Texture2D()
{
}

int Texture2D::load(const char * path, int magFilter, int minFilter) {
	FILE * file = fopen(path, "rb"); //b -> open as binary file, not text
	if (!file) { 
		std::cout << "Texture2D: unable to open file. Path: " << path << std::endl;
		return -1; 
	}

	//header
	unsigned char header[54];
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		std::cout << "Texture2D: incompatible file format. Path: " << path << std::endl;
		return -2;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		std::cout << "Texture2D: incompatible file format. Path: " << path << std::endl;
		return -2;
	}

	int size = *(int*)&(header[0x22]);
	int width = *(int*)&(header[0x12]);
	int height = *(int*)&(header[0x16]);

	//if size is missing
	if (size == 0)    
		size = width*height*4; 

	//read data
	unsigned char *data = new unsigned char[size];
	if (fread(data, 1, size, file) != size) {
		if (data == NULL) {
			std::cout << "Texture2D: incompatible file format. Path: " << path << std::endl;
			return -2;
		}
		std::cout << "Texture2D: information in header doeas not match with actual data. Path: " << path << std::endl;
		delete[] data;
		width = 0;
		height = 0;
		size = 0;
		return -3;
	}

	//convert fra BRG to RGB
	for (int i = 0; i <= size-4; i += 4) {
		unsigned char blue = data[i];
		data[i] = data[i + 2];
		data[i + 2] = blue;
	}


	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || magFilter == GL_LINEAR_MIPMAP_NEAREST) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	delete[] data;
	std::cout << "Texture2D: texture loaded. Path: " << path << std::endl;
	return 0;
}

GLuint Texture2D::getId() {
	return id;
}

bool Texture2D::isLoaded() {
	if(id == -1)
		return false;
	return true;
}

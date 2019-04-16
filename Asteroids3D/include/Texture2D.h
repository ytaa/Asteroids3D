#pragma once
#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>

class Texture2D
{
public:
	Texture2D(const char *, int = GL_LINEAR, int = GL_LINEAR);
	~Texture2D();

	int load(const char *, int, int);
	GLuint getId();
	bool isLoaded();

	const char * path;

private:
	GLuint id;
	
};


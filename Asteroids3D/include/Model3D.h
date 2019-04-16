#pragma once
#include <GL/freeglut.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Vec3.h"
class Model3D
{
public:
	Model3D(const char *);
	~Model3D();
	GLuint load(const char *);
	int call();
	bool isLoaded();
private:
	GLuint displayListIndex;
};


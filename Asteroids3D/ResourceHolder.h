#pragma once
#include "Model3D.h"
#include "Texture2D.h"
class ResourceHolder
{
public:
	ResourceHolder();
	~ResourceHolder();
	
	Model3D starshipModel;
	Texture2D starshipTexture;

	Model3D spaceBoxModel;
	Texture2D spaceBoxTexture;

	Model3D meteorModel;
	std::vector<Texture2D> meteorTextures;

	Model3D playerTargetModel;

	Model3D spaceShipModel;
	Texture2D spaceShipTexture;
};


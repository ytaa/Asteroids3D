#include "ResourceHolder.h"



ResourceHolder::ResourceHolder()
	: starshipModel(Model3D("../Resources/Models/starship.obj"))
	, starshipTexture(Texture2D("../Resources/Textures/starfighter.bmp"))
	, spaceBoxModel(Model3D("../Resources/Models/spacebox.obj"))
	, spaceBoxTexture(Texture2D("../Resources/Textures/spacebox1.bmp"))
	, meteorModel(Model3D("../Resources/Models/meteor.obj"))
	, meteorTextures({ 
		  Texture2D("../Resources/Textures/meteor.bmp")
		, Texture2D("../Resources/Textures/meteorp1.bmp")
		, Texture2D("../Resources/Textures/meteorp2.bmp")
		, Texture2D("../Resources/Textures/meteorp3.bmp")
		//, Texture2D("../Resources/Textures/meteorp1.bmp") 
	})
	, playerTargetModel(Model3D("../Resources/Models/playerTarget.obj"))
	,spaceShipModel(Model3D("../Resources/Models/spaceship.obj"))
	,spaceShipTexture(Texture2D("../Resources/Textures/spaceship.bmp"))
{
}


ResourceHolder::~ResourceHolder()
{
}

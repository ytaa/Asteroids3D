#include "Model3D.h"



Model3D::Model3D(const char * path)
	:displayListIndex(-1)
{
	load(path);
}


Model3D::~Model3D()
{
	if (displayListIndex)
		glDeleteLists(displayListIndex, 1);
}

GLuint Model3D::load(const char *path) {
	std::ifstream file(path);
	if (!file.good()) {
		std::cout << "Model3D: unable to open Path: " << path << std::endl;
		return 0;
	}

	std::string line = "";
	std::string head = "";

	std::vector<Vec3> vertices;
	std::vector<Vec3> uvs;
	std::vector<Vec3> normals;

	std::vector<Vec3> loadedv;
	std::vector<Vec3> loadedvn;
	std::vector<Vec3> loadedvt;

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> head;
		if (head == "v" || head == "vn" || head == "vt") {
			Vec3 vec;
			if (head == "v" || head == "vn")
				iss >> vec.x >> vec.y >> vec.z;
			else
				iss >> vec.x >> vec.y;
			if (iss.fail() || iss.bad()) {
				std::cout << "Model3D: error reading file (vertex). Path: " << path << std::endl;
				break;
			}
			if (head == "v")
				loadedv.push_back(vec);
			else if (head == "vn")
				loadedvn.push_back(vec);
			else
				loadedvt.push_back(vec);
		}
		else if (head == "f") {
			int index = 0;
			std::string token;
			for (int i = 0; i < 3; i++) {
				getline(iss, token, '/');
				index = std::stoi(token);
				vertices.push_back(loadedv[index - 1]);
				getline(iss, token, '/');
				index = std::stoi(token);
				uvs.push_back(loadedvt[index - 1]);
				getline(iss, token, ' ');
				index = std::stoi(token);
				normals.push_back(loadedvn[index - 1]);
			}
		}
	}
	file.close();

	if (displayListIndex)
		glDeleteLists(displayListIndex, 1);
	displayListIndex = glGenLists(1);

	glNewList(displayListIndex, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			for (unsigned int i = 0; i < vertices.size(); i++) {
				glNormal3f(normals[i].x, normals[i].y, normals[i].z);
				glTexCoord2f(uvs[i].x, uvs[i].y);
				glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			}
		glEnd();
	glEndList();

	std::cout << "Model3D: model loaded. Path: " << path << std::endl;
	return displayListIndex;
}

int Model3D::call() {
	if (displayListIndex == -1)
		return -1;
	glCallList(displayListIndex);
	return 0;
}
	
bool Model3D::isLoaded() {
	if (displayListIndex)
		return true;
	return false;
}
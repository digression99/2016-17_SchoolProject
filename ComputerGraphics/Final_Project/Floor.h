#pragma once

#include "stdafx.h"

class Floor
{
public:
	GLuint vao[1];
	GLuint vbo[5];
	//std::vector<GLuint> cubeIdxVbo;

	glm::vec4 vertex[10];
	glm::vec4 color[10];
	glm::vec2 tex[10];
	glm::vec3 normals[10];
	GLuint idx[6];
	bool NoErrors;
	int sizeX;
	int sizeY;
	GLuint mytex[1];
	bool isTextured;

	GLuint vLoc;
	GLuint cLoc;
	GLuint samplerLoc;
	GLuint texLoc;
	GLuint normalLoc;
public:
	Floor();
	void createFloor(int program);
	void setFloor();
	void drawFloor();
	void convertBGRtoRGB(GLubyte* data);
};
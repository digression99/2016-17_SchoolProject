#pragma once

#include "stdafx.h"

class TDObj
{
public:
	static float plusX;
	static float plusY;
	static float plusZ;
	const float halfSize = 0.1f;
	GLuint vao[1];
	GLuint vbo[5];
	//std::vector<GLuint> cubeIdxVbo;

	GLuint cubeIdxVbo[MAX_DATA * 6];
	glm::vec4 cubeVertexVbo[MAX_DATA];
	glm::vec4 cubeColorVbo[MAX_DATA];
	glm::vec3 cubeNormalVectors[MAX_DATA];
	glm::vec2 cubeTexCoord[MAX_DATA];
	glm::vec4 colorVec;

	GLuint vLoc;
	GLuint cLoc;
	GLuint samplerLoc;
	GLuint texLoc;
	GLuint normalLoc;

	int poly; // poly : 4
	int tesNum; // tesNum : 20
	int sizeX;
	int sizeY;
	bool NoErrors;
	GLuint mytex[1];
	GLfloat tesLev;
	int vertexNum; // with colorNum.
	int idxNum; // with normalNum.
	int drawNumArr[10][10]; // tesNum : 20
	bool isTextured;

public:
	TDObj();
	TDObj(const TDObj & t);
	TDObj & operator=(const TDObj & t);

	void drawObject(int drawNum);
	void setObject();
	void setTexture();
	void convertBGRtoRGB(GLubyte* data);

	void setTessellate();
	void tessellate();
	void idxPushBack(int idx);

	void createObject(int program);
	void quad(int a, int b, int c, int d);
	//void quad(int a, int b, int c);
	//void createTexture();
};

//void TDObj::quad(int a, int b, int c, int d)
//{ // the original quad code
//	glm::vec4 u = this->cubeVertexVbo[b] - this->cubeVertexVbo[a];
//	glm::vec4 v = this->cubeVertexVbo[c] - this->cubeVertexVbo[b];
//	
//	vec3 normal = normalize(cross(u, v));
//
//	normals[Index] = normal;
//	points[Index] = vertices[a];
//	Index++;
//
//	normals[Index] = normal;
//	points[Index] = vertices[b];
//	Index++;
//	normals[Index] = normal;
//	points[Index] = vertices[c];
//	Index++;
//	normals[Index] = normal;
//	points[Index] = vertices[a];
//	Index++;
//	normals[Index] = normal;
//	points[Index] = vertices[c];
//	Index++;
//	normals[Index] = normal;
//	points[Index] = vertices[d];
//	Index++;
//}
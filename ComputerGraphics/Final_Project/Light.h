#pragma once

#include "stdafx.h"

class Light
{
public:
	glm::vec4 lPosition;
	glm::vec4 lAmbient;
	glm::vec4 lDiffuse;
	glm::vec4 lSpecular;
	glm::vec4 mAmbient;
	glm::vec4 mDiffuse;
	glm::vec4 mSpecular;
	float mShininess;
	glm::vec4 ambientProduct;
	glm::vec4 diffuseProduct;
	glm::vec4 specularProduct;
	glm::vec4 lColor;
	GLfloat lx, ly, lz;
	GLuint ambPLoc;
	GLuint difPLoc;
	GLuint specPLoc;
	GLuint lPLoc;
	GLuint shinLoc;
	GLuint lcLoc;
public:
	Light();
	void setLightPos();
	void createLightPos(int program);
};
#pragma once

#include "stdafx.h"

class MatrixConversion
{
public:
	glm::mat4 rotationMat;
	glm::mat4 translationMat;
	glm::mat4 projectionMat;
	GLfloat thetaX, thetaY;
	GLfloat dx, dy, dz;
	GLfloat persFOV;
	GLfloat persAspect;
	GLfloat plusX, plusY, plusZ;
	int select;
	glm::vec3 viewerPos;

	GLuint projLoc;
	GLuint rotLoc;
	GLuint transLoc;
public:
	MatrixConversion();
	void setMatrixConversion(); // set the matrix in ondraw
	void createMatrixConversion(int program);
};
#include "stdafx.h"
#include "MatrixConversion.h"

MatrixConversion::MatrixConversion()
{
	this->dx = 0.0;
	this->dy = 0.0;
	this->dz = 0.0;
	this->persAspect = 1.0f;
	this->persFOV = 45.0f;
	this->thetaX = 1.0f;
	this->thetaY = 1.0f;
	this->plusX = 0.0;
	this->plusY = 0.0;
	this->plusZ = 0.0;
	this->viewerPos = glm::vec3(1.0, 0.1, -4.0f);
	this->projectionMat = 
		glm::perspective(this->persFOV, this->persAspect, 0.01f, 1000.0f);
}

void MatrixConversion::setMatrixConversion()
{
	this->translationMat = glm::translate(glm::vec3(this->dx + this->plusX - this->viewerPos[0], 
		this->dy + this->plusY - this->viewerPos[1], this->dz - 7.0f + this->plusZ - this->viewerPos[2]));
	this->rotationMat = glm::rotate(this->thetaX, glm::vec3(0, 1, 0)) *
		glm::rotate(this->thetaY, glm::vec3(1, 0, 0));

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &(this->projectionMat[0][0]));
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &(this->translationMat[0][0]));
	glUniformMatrix4fv(rotLoc, 1, GL_FALSE, &(this->rotationMat[0][0]));
}

void MatrixConversion::createMatrixConversion(int program)
{
	projLoc = glGetUniformLocation(program, "projMat");
	transLoc = glGetUniformLocation(program, "transMat");
	rotLoc = glGetUniformLocation(program, "rotMat");
}
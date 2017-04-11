#include "stdafx.h"
#include "Light.h"

Light::Light()
{
	this->lx = 0.0;
	this->ly = 0.0;
	this->lz = 0.0;
	this->mShininess = 10.0;
	this->lAmbient = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->lDiffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->lSpecular = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->mAmbient = glm::vec4(1.0, 0.0, 1.0, 1.0);
	this->mDiffuse = glm::vec4(1.0, 0.8, 0.0, 1.0);
	this->mSpecular = glm::vec4(1.0, 0.8, 0.0, 1.0);
	this->ambientProduct = this->lAmbient * this->mAmbient;
	this->diffuseProduct = this->lDiffuse * this->mDiffuse;
	this->specularProduct = this->lSpecular * this->mSpecular;
	this->lColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->lPosition = glm::vec4(lx, ly, lz, 0.0);

}

void Light::createLightPos(int program)
{
	ambPLoc = glGetUniformLocation(program, "ambientProduct");
	difPLoc = glGetUniformLocation(program, "diffuseProduct");
	specPLoc = glGetUniformLocation(program, "specularProduct");
	lPLoc = glGetUniformLocation(program, "lightPosition");
	shinLoc = glGetUniformLocation(program, "shininess");
	lcLoc = glGetUniformLocation(program, "lightColor");
}

void Light::setLightPos()
{
	this->lPosition = glm::vec4(lx, ly, lz, 0.0);

	glUniform4fv(ambPLoc, 1, &(ambientProduct[0]));
	glUniform4fv(difPLoc, 1, &(diffuseProduct[0]));
	glUniform4fv(specPLoc, 1, &(specularProduct[0]));
	glUniform4fv(lPLoc, 1, &(lPosition[0]));
	glUniform1f(shinLoc, mShininess);
	glUniform4fv(lcLoc, 1, &(lColor[0]));
}

/*#include "stdafx.h"

#include "OGLContext.h"


#include "OpenGLUtility.h"


COpenGLContext::COpenGLContext()
{
}

COpenGLContext::~COpenGLContext()
{
	glDeleteProgram(m_P7rogram);
}

bool COpenGLContext::Init()
{
	m_Program = InitShader("vshader.glsl","fshader.glsl");

	glUseProgram(m_Program);

	return true;
}



*/
#pragma once

class COpenGLContext {
protected:
	GLuint m_Program;


public:
	COpenGLContext();
	~COpenGLContext();

	bool Init();
	GLuint GetProgram()	{	return m_Program;	}

	
};
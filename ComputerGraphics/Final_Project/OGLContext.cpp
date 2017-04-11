#include "stdafx.h"

#include "OGLContext.h"

#include "OpenGLUtility.h"


COpenGLContext::COpenGLContext()
{
}

COpenGLContext::~COpenGLContext()
{
	glDeleteProgram(m_Program);
}

bool COpenGLContext::Init()
{
	m_Program = InitShader("vshader.glsl","fshader.glsl");

	glUseProgram(m_Program);

	return true;
}




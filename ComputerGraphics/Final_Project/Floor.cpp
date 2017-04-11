#include "stdafx.h"
#include "Floor.h"

Floor::Floor()
{
	this->isTextured = false;
}

void Floor::createFloor(int program)
{
	vertex[0] = glm::vec4(-100.0f, 0.0f, 100.0f, 1.0);
	vertex[1] = glm::vec4(100.0f, 0.0f, 100.0f, 1.0);
	vertex[2] = glm::vec4(100.0f, 0.0f, -100.0f, 1.0);
	vertex[3] = glm::vec4(-100.0f, 0.0f, -100.0f, 1.0);
	//vertex[3] = glm::vec4(-100.0f, 0.0f, -100.0f, 1.0);
	//vertex[3] = glm::vec4(100.0f, 0.0f, -100.0f, 1.0);

	color[0] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	color[1] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	color[2] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	color[3] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	//color[4] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	//color[5] = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

	tex[0] = glm::vec2(0.0f, 1.0f);
	tex[1] = glm::vec2(1.0f, 1.0f);
	tex[2] = glm::vec2(0.0f, 0.0f);
	tex[3] = glm::vec2(1.0f, 1.0f);
	tex[4] = glm::vec2(0.0f, 0.0f);
	tex[5] = glm::vec2(1.0f, 0.0f);

	idx[0] = 0;
	idx[1] = 1;
	idx[2] = 3;
	idx[3] = 1;
	idx[4] = 2;
	idx[5] = 3;

	normals[0] = glm::vec3(0.0f, 0.0f, 1.0f);
	normals[1] = glm::vec3(0.0f, 0.0f, 1.0f);
	normals[2] = glm::vec3(0.0f, 0.0f, 1.0f);
	normals[3] = glm::vec3(0.0f, 0.0f, 1.0f);
	normals[4] = glm::vec3(0.0f, 0.0f, 1.0f);
	normals[5] = glm::vec3(0.0f, 0.0f, 1.0f);
	
	glGenVertexArrays(1, this->vao);
	glGenBuffers(4, &(this->vbo[0]));

	vLoc = glGetAttribLocation(program, "vtxPosition");
	cLoc = glGetAttribLocation(program, "vtxColor");
	samplerLoc = glGetUniformLocation(program, "sampler");
	texLoc = glGetAttribLocation(program, "texCoord");
	normalLoc = glGetAttribLocation(program, "vNormal");

}

void Floor::setFloor()
{
	glBindVertexArray(this->vao[0]);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) *
		MAX_DATA, this->vertex,
		GL_STATIC_DRAW);
	glVertexAttribPointer(vLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(vLoc);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) *
		MAX_DATA, this->color,
		GL_STATIC_DRAW);
	glVertexAttribPointer(cLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(cLoc);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[2]);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec2) * 2 * MAX_DATA, this->tex,
		GL_STATIC_DRAW);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE,
		0, (GLvoid*)(0));
	glEnableVertexAttribArray(texLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) *
		MAX_DATA, this->idx,
		GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *
		MAX_DATA, this->normals,
		GL_STATIC_DRAW);
	glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(normalLoc);
	//this->setTexture(program);

	
	if (!this->isTextured)
	{
		glActiveTexture(GL_TEXTURE0);

		glGenTextures(1, mytex);
		glBindTexture(GL_TEXTURE_2D, mytex[0]);

		BITMAPINFO BMInfo;
		const HDC gldc = wglGetCurrentDC();
		NoErrors = false;
		BMInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		BMInfo.bmiHeader.biBitCount = 0;

		HANDLE DIBHandle = LoadImage(0, L"brick11.bmp",
			IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetDIBits(gldc, (HBITMAP)DIBHandle, 0, 0, NULL, &BMInfo, DIB_RGB_COLORS);
		sizeX = BMInfo.bmiHeader.biWidth;
		sizeY = BMInfo.bmiHeader.biHeight; // change color depth to 24 bits (3 bytes (BGR) / pixel)
		BMInfo.bmiHeader.biBitCount = 24; // don't want the data compressed
		BMInfo.bmiHeader.biCompression = BI_RGB;
		const DWORD BitmapLength = sizeX * sizeY * 3; // 3 bytes (BGR) per pixel (24bp)
		// allocate enough memory to hold the pixel data in client memory
		byte * data = new byte[BitmapLength];

		if (GetDIBits(gldc, (HBITMAP)DIBHandle, 0, sizeY, data, &BMInfo, DIB_RGB_COLORS))
		{
			NoErrors = true;
			this->convertBGRtoRGB(data); // NOTE: BMP is in BGR format but OpenGL needs RGB
		}

		DeleteObject(DIBHandle); // don't need the BMP Object anymore 

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		//GLuint sampler;
		//glGenSamplers(0, &sampler);
		//glBindSampler(0, sampler);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		this->isTextured = true;
	}
	glUniform1i(samplerLoc, 0);
}

void Floor::drawFloor()
{
	glBindVertexArray(this->vao[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Floor::convertBGRtoRGB(GLubyte* data)
{
	const DWORD BitmapLength = sizeX * sizeY * 3;
	byte Temp; // not quick but it works
	for (DWORD i = 0; i < BitmapLength; i += 3)
	{
		Temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = Temp;
	}
}
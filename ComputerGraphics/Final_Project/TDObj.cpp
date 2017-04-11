#include "stdafx.h"
#include "TDObj.h"

TDObj::TDObj()
{
	this->poly = 4;
	this->tesNum = 0;
	this->sizeX = 0;
	this->sizeY = 0;
	this->vertexNum = 0;
	this->idxNum = 0;
	colorVec = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->tesLev = 0.0;
	isTextured = false;
}

void TDObj::setObject()
{
	glBindVertexArray(this->vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) *
		MAX_DATA, &(this->cubeVertexVbo[0]),
		GL_STATIC_DRAW);
	glVertexAttribPointer(vLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(vLoc);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) *
		MAX_DATA, &(this->cubeColorVbo[0]),
		GL_STATIC_DRAW);
	glVertexAttribPointer(cLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(cLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) *
		MAX_DATA, &(this->cubeIdxVbo[0]),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *
		MAX_DATA, this->cubeNormalVectors,
		GL_STATIC_DRAW);
	glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(normalLoc);

	this->setTexture();
}

void TDObj::drawObject(int drawNum)
{
	glBindVertexArray(this->vao[0]);
	glDrawElements(GL_TRIANGLES, 3 * drawNum, GL_UNSIGNED_INT, 0);
}

void TDObj::setTexture()
{
	glBindVertexArray(this->vao[0]);
	//glBindBuffer(this->vbo[4]);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[4]);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec2) * 2 * MAX_DATA, this->cubeTexCoord,
		GL_STATIC_DRAW);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE,
		0, (GLvoid*)(0));
	glEnableVertexAttribArray(texLoc);

	if (!this->isTextured)
	{
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

void TDObj::convertBGRtoRGB(GLubyte* data)
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


void TDObj::createObject(int program)
{
	srand((unsigned)time(NULL));
	
	glGenVertexArrays(1, this->vao);
	glGenBuffers(5, &(this->vbo[0]));
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, mytex);

	vLoc = glGetAttribLocation(program, "vtxPosition");
	cLoc = glGetAttribLocation(program, "vtxColor");


	texLoc = glGetAttribLocation(program, "texCoord");
	/*glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE,
		0, (GLvoid*)(0));
	glEnableVertexAttribArray(texLoc);*/

	normalLoc = glGetAttribLocation(program, "vNormal");
	/*glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(normalLoc);
		glVertexAttribPointer(cLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(0));
	glEnableVertexAttribArray(cLoc);*/

	samplerLoc = glGetUniformLocation(program, "sampler");

	////initial settings of vertex, color, texcoord, normals, index
	//// initial settings of the data means one cube.
	this->cubeVertexVbo[0] = glm::vec4(-0.1f, 0.0f, 0.1f, 1.0);
	this->cubeVertexVbo[1] = glm::vec4(0.1f, 0.0f, 0.1f, 1.0);
	this->cubeVertexVbo[2] = glm::vec4(0.1f, 0.0f, -0.1f, 1.0);
	this->cubeVertexVbo[3] = glm::vec4(-0.1f, 0.0f, -0.1f, 1.0);
	this->cubeVertexVbo[4] = glm::vec4(-0.1f, 0.2f, 0.1f, 1.0);
	this->cubeVertexVbo[5] = glm::vec4(0.1f, 0.2f, 0.1f, 1.0);
	this->cubeVertexVbo[6] = glm::vec4(0.1f, 0.2f, -0.1f, 1.0);
	this->cubeVertexVbo[7] = glm::vec4(-0.1f, 0.2f, -0.1f, 1.0);
	this->vertexNum = 8;
	this->tesLev = 0.1f;

	this->cubeColorVbo[0] = this->colorVec;
	this->cubeColorVbo[1] = this->colorVec;
	this->cubeColorVbo[2] = this->colorVec;
	this->cubeColorVbo[3] = this->colorVec;
	this->cubeColorVbo[4] = this->colorVec;
	this->cubeColorVbo[5] = this->colorVec;
	this->cubeColorVbo[6] = this->colorVec;
	this->cubeColorVbo[7] = this->colorVec;

	this->cubeTexCoord[0] = glm::vec2(1, 1);
	this->cubeTexCoord[1] = glm::vec2(1, 0);
	this->cubeTexCoord[2] = glm::vec2(1, 1);
	this->cubeTexCoord[3] = glm::vec2(1, 0);
	this->cubeTexCoord[4] = glm::vec2(0, 1);
	this->cubeTexCoord[5] = glm::vec2(0, 0);
	this->cubeTexCoord[6] = glm::vec2(0, 1);
	this->cubeTexCoord[7] = glm::vec2(0, 0);

	GLuint pIndices[] = {
		//0, 1, 3,
		//1, 2, 3,
		0, 1, 4,
		1, 4, 5,
		1, 2, 5,
		2, 5, 6,
		3, 2, 7,
		2, 6, 7,
		0, 3, 4,
		3, 4, 7,
		//4, 5, 7,
		//5, 7, 6,
	};

	for (int i = 0; i < 24; i++)
	{
		//this->cubeNormalVectors
		this->cubeIdxVbo[i] = pIndices[i];
	}
	for (int i = 0; i < 8; i++)
	{
		glm::vec4 u = this->cubeVertexVbo[this->cubeIdxVbo[3 * i + 1]] - 
			this->cubeVertexVbo[this->cubeIdxVbo[3 * i]];
		glm::vec4 v = this->cubeVertexVbo[this->cubeIdxVbo[3 * i + 2]] - 
			this->cubeVertexVbo[this->cubeIdxVbo[3 * i + 1]];

		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(u[0], u[1], u[2]), glm::vec3(v[0], v[1], v[2])));

		this->cubeNormalVectors [3 * i] = normal;
		this->cubeNormalVectors [3 * i + 1] = normal;
		this->cubeNormalVectors [3 * i + 2] = normal;
	}
	this->idxNum = 24;
	this->tesNum = 1;
}

void TDObj::setTessellate()
{
	for (int i = 0; i < TES_MAX; i++)
	{
		this->tessellate();
		this->tesNum++;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->drawNumArr[i][j] = 8 * (rand() % TES_MAX + 2);
		}
	}

	/*for (int i = 0; i < 20; i++)
	{
		this->drawNumArr[i] = rand() % 20 + 1;
	}*/
}


void TDObj::tessellate()
{
	this->tesLev += 0.1f * 2;
	for (int i = 0; i < this->poly; i++)
	{ // poly is 4.

		this->cubeVertexVbo[this->vertexNum + i] = 
			this->cubeVertexVbo[this->vertexNum - 4 + i];
		this->cubeVertexVbo[this->vertexNum + i][1] = this->tesLev;
		this->cubeColorVbo[this->vertexNum + i] = this->colorVec;
	}
	this->vertexNum += 4;

	int s = this->tesNum * this->poly;
	GLuint bc, bn, nc, nn;

	for (int idx = 0; idx < this->poly; idx++)
	{
		bc = s + idx;			bn = s + (idx + 1) % this->poly;
		nc = s + idx + this->poly;	nn = s + (idx + 1) % this->poly + this->poly;

		this->idxPushBack(bc);
		this->idxNum++;
		this->idxPushBack(bn);
		this->idxNum++;
		this->idxPushBack(nn);
		this->idxNum++;
		this->idxPushBack(bc);
		this->idxNum++;
		this->idxPushBack(nn);
		this->idxNum++;
		this->idxPushBack(nc);
		this->idxNum++;
	}
	this->idxNum -= 24;
	for (int i = 0; i < 8; i++)
	{
		glm::vec4 u = this->cubeVertexVbo[s + this->cubeIdxVbo[3 * i + 1]] - 
			this->cubeVertexVbo[s + this->cubeIdxVbo[3 * i]];
		glm::vec4 v = this->cubeVertexVbo[s + this->cubeIdxVbo[3 * i + 2]] - 
			this->cubeVertexVbo[s + this->cubeIdxVbo[3 * i + 1]];

		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(u[0], u[1], u[2]), glm::vec3(v[0], v[1], v[2])));

		this->cubeNormalVectors [3 * i + s] = normal;
		this->cubeNormalVectors [3 * i + 1 + s] = normal;
		this->cubeNormalVectors [3 * i + 2 + s] = normal;

		this->cubeTexCoord[3 * i + s] = this->cubeTexCoord[i];
	}
	this->idxNum += 24;
	//quad.

	// need to push the texel coordinate vertices to the array.
	// like the indexation.
}

TDObj::TDObj(const TDObj & t)
{
}

void TDObj::idxPushBack(int idx)
{
	this->cubeIdxVbo[this->idxNum] = idx;
}

TDObj & TDObj::operator=(const TDObj & t)
{
	return *this;
}
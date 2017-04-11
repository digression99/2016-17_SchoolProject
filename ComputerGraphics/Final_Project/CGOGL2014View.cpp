
// CGOGL2014View.cpp : CCGOGL2014View 클래스의 구현
//

#include "stdafx.h"
#include "CGOGL2014.h"

#include "CGOGL2014Doc.h"
#include "CGOGL2014View.h"
#include <glm/gtx/transform.hpp>
#include "OGLContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGOGL2014View

IMPLEMENT_DYNCREATE(CCGOGL2014View, CView)

BEGIN_MESSAGE_MAP(CCGOGL2014View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCGOGL2014View::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

// CCGOGL2014View 생성/소멸

CCGOGL2014View::CCGOGL2014View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	m_OGLContext = new COpenGLContext;
}

CCGOGL2014View::~CCGOGL2014View()
{
}

BOOL CCGOGL2014View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}




// CCGOGL201]

void CCGOGL2014View::OnDraw(CDC* /*pDC*/)
{
	CCGOGL2014Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//if (!isCleared)
	//{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	isCleared = true;
	//}
	this->light.setLightPos();
	this->tdobj.setObject();
	this->f.setFloor();
	this->f.drawFloor();

	for (l = 0; l < 2; l++)
	{
		for (k = 0; k < 10; k++)
		{
			for (i = 0; i < 10; i++)
			{
				this->mc.plusX = i * 0.4 + k * 4;
				for (j = 0; j < 10; j++)
				{
					this->mc.plusZ = j * 0.6 + l * 6;
					this->mc.setMatrixConversion();
					this->tdobj.drawObject(this->tdobj.drawNumArr[i][j]);
				}
			}
		}
	}

	::SwapBuffers(m_pDC->GetSafeHdc());
	Invalidate(FALSE);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCGOGL2014View 인쇄


void CCGOGL2014View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CCGOGL2014View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCGOGL2014View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCGOGL2014View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CCGOGL2014View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCGOGL2014View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CCGOGL2014View 진단

#ifdef _DEBUG
void CCGOGL2014View::AssertValid() const
{
	CView::AssertValid();
}

void CCGOGL2014View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGOGL2014Doc* CCGOGL2014View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGOGL2014Doc)));
	return (CCGOGL2014Doc*)m_pDocument;
}
#endif //_DEBUG


void CCGOGL2014View::createObjVector()
{
}


// CCGOGL2014View 메시지 처리기

int CCGOGL2014View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (!GetRenderingContext())
    {       
        return -1;
    }
	this->l = 0;
	this->i = 0;
	this->j = 0;
	this->k = 0;

    // 추후에 OpenGL 초기화 할예정
	
	m_OGLContext->Init();

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);

	this->isLanded = false;
	this->isCleared = false;

	this->mc.createMatrixConversion(this->m_OGLContext->GetProgram());
	this->mc.setMatrixConversion();

	this->light.createLightPos(this->m_OGLContext->GetProgram());
	this->light.setLightPos();
	

	/*this->tdobjVec.resize(sizeof(TDObj *) * 10);
	TDObj * td = new TDObj();
*/
	tdobj.createObject(this->m_OGLContext->GetProgram());
	tdobj.setTessellate();
	//this->tdobj.setTessellate();

	tdobj.setTexture();
	tdobj.setObject();
	this->f.createFloor(this->m_OGLContext->GetProgram());
	this->f.setFloor();


	glClearColor(0.0, 0.0, 0.0, 1.0);
	//this->tdobjVec.push_back(td);

	return 0;
}



bool CCGOGL2014View::GetRenderingContext(void)
{
	m_pDC = new CClientDC(this);

   if ( NULL == m_pDC ) // failure to get DC
   {      
      return false;
   }


  if (false == GetOldStyleRenderingContext())
  {
	  return false;
  }
   
   //Get access to modern OpenGL functionality from this old style context.
   glewExperimental = GL_TRUE;
   if (GLEW_OK != glewInit())
   {
      AfxMessageBox(_T("GLEW could not be initialized!"));
      return false;
   }
   else
   {
	   wglMakeCurrent(NULL, NULL);
	   wglDeleteContext(m_hRC);	
   }

   //Get a new style pixel format
   if (!SetupModernPixelFormat())
   {
      return false;
   }

   //Setup request for OpenGL 3.2 Core Profile
   int attribs[] =
   {
      WGL_CONTEXT_MAJOR_VERSION_ARB,   3,
      WGL_CONTEXT_MINOR_VERSION_ARB,   1,
     // WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 
      //WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
      0, 0  //End
   };

   if(wglewIsSupported("WGL_ARB_create_context") == 1)
   {
      //If this driver supports new style rendering contexts, create one
      HGLRC oldContext = m_hRC;
      if ( 0 == (m_hRC = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(), 0, attribs) ) )
      {         
		  int err = glGetError();

         return false;
      }

      if(!wglMakeCurrent(NULL,NULL) )
         wglDeleteContext(oldContext);
      if ( FALSE == wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
      {         
         return false;
      }     
   }
   else
   {  
      //Otherwise use the old style rendering context we created earlier.
      AfxMessageBox(_T("GL 3.2 Context not possible. Using old style context. (GL 2.1 and before)"));
   }

   return true;
}


bool CCGOGL2014View::GetOldStyleRenderingContext(void)
{
   //A generic pixel format descriptor. This will be replaced with a more
   //specific and modern one later, so don't worry about it too much.
   static PIXELFORMATDESCRIPTOR pfd =
   {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW |            // support window
      PFD_SUPPORT_OPENGL |            // support OpenGL
      PFD_DOUBLEBUFFER,               // double buffered
      PFD_TYPE_RGBA,                  // RGBA type
      32,                             // 32-bit color depth
      0, 0, 0, 0, 0, 0,               // color bits ignored
      0,                              // no alpha buffer
      0,                              // shift bit ignored
      0,                              // no accumulation buffer
      0, 0, 0, 0,                     // accum bits ignored
      24,							  // 24-bit z-buffer
      0,                              // no stencil buffer
      0,                              // no auxiliary buffer
      PFD_MAIN_PLANE,                 // main layer
      0,                              // reserved
      0, 0, 0                         // layer masks ignored
   };

   // Get the id number for the best match supported by the hardware device context
   // to what is described in pfd
   int pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

   //If there's no match, report an error
   if ( 0 == pixelFormat )
   {      
      return false;
   }

   //If there is an acceptable match, set it as the current 
   if ( FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) )
   {      
      return false;
   }

   //Create a context with this pixel format
   if ( 0 == (m_hRC = wglCreateContext( m_pDC->GetSafeHdc() ) ) )
   {      
      return false;
   }

   //Make it current. Now we're ready to get extended features.
   if ( FALSE == wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
   {      
      return false;
   }
   return true;
}


bool CCGOGL2014View::SetupModernPixelFormat(void)
{
	//This is a modern pixel format attribute list.
	//It has an extensible structure. Just add in more argument pairs 
	//before the null to request more features.
	const int attribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
		WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
		WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,     32,
		WGL_DEPTH_BITS_ARB,     24,
		//WGL_STENCIL_BITS_ARB,   8,
		0, 0  //End
	};


	unsigned int numFormats;
	int pixelFormat;
	PIXELFORMATDESCRIPTOR pfd;

	//Select a pixel format number
	wglChoosePixelFormatARB(m_pDC->GetSafeHdc(), attribList, NULL, 1, &pixelFormat, &numFormats);

	//Optional: Get the pixel format's description. We must provide a 
	//description to SetPixelFormat(), but its contents mean little.
	//According to MSDN: 
	//  The system's metafile component uses this structure to record the logical
	//  pixel format specification. The structure has no other effect upon the
	//  behavior of the SetPixelFormat function.
	DescribePixelFormat(m_pDC->GetSafeHdc(), pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	//Set it as the current 
	if ( FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) )
	{
		DWORD err = GetLastError();
		return false;
	}

	   //Create a context with this pixel format
   if ( 0 == (m_hRC = wglCreateContext( m_pDC->GetSafeHdc() ) ) )
   {      
      return false;
   }

   //Make it current. Now we're ready to get extended features.
   if ( FALSE == wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
   {      
      return false;
   }

	return true;
}
void CCGOGL2014View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	glViewport(0,0,cx,cy);
}

void CCGOGL2014View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	float x,y;

	CRect rect;
	this->GetClientRect(&rect);

	//x = (point.x/(float)rect.Width())*2 - 1;
	//y = (-point.y/(float)rect.Height())*2 + 1;

	//glm::mat4 rotMat1 = glm::mat4(1.0f);
	//glm::mat4 rotMat2 = glm::mat4(1.0f);

	//glm::mat4 transMat = glm::mat4(1.0f);

	//if (nFlags & MK_LBUTTON)
	//{

	//	////deal angle X
	//	this->lightastX = x;
	//	if (this->firstX - this->lightastX > 0) // 양이면 왼쪽
	//	{
	//		this->angleX = -ANGLE_CHANGE;
	//	}
	//	else
	//	{
	//		this->angleX = ANGLE_CHANGE;
	//	}
	//	this->firstX = this->lightastX;
	//	rotMat1 = glm::rotate(this->angleX, glm::vec3(0, 1, 0));
	//	////deal angle X

	//	transMat = rotMat1;

	//}
	//else if (nFlags & MK_RBUTTON)
	//{
	//	////deal angle Y
	//	this->lightastY = y;
	//	if (this->firstY - this->lightastY > 0)
	//	{
	//		this->angleY = -ANGLE_CHANGE;
	//	}
	//	else
	//	{
	//		this->angleY = ANGLE_CHANGE;
	//	}
	//	this->firstY = this->lightastY;
	//	rotMat2 = glm::rotate(this->angleY, glm::vec3(1, 0, 0));
	//	transMat = rotMat2;
	//	////deal angle Y
	//}
	//m_CubeTransform = transMat * m_CubeTransform;


/*
	if (nFlags & MK_LBUTTON)
	{
		glm::vec3 aX = glm::vec3(x, y, 0);
		glm::vec3 aZ = glm::vec3(0, 0, 1);
		glm::vec3 aY = glm::cross(aZ, aX);

		aX = glm::normalize(aX);
		aY = glm::normalize(aY);
		aZ = glm::normalize(aZ);
		
		glm::mat4 transMat = glm::mat4(1.0f);
		transMat[0] = glm::vec4(aX, 0.0);
		transMat[1] = glm::vec4(aY, 0.0);
		transMat[2] = glm::vec4(aZ, 0.0);

		m_CubeTransform = transMat;
	}
*/


/*
	if (this->rotateType == 0)
	{
		this->angle = 0.1f;
	}
	else
	{
		this->angle = -0.1f;
	}*/
	//glm::mat4 rotMat = glm::mat4(1.0f);
/*
	rotMat[0] = glm::vec4(1.0, 0.0, 0.0, 0.0);
	rotMat[1] = glm::vec4(0.0, 1.0, 0.0, 0.0);
	rotMat[2] = glm::vec4(0.0, 0.0, 1.0, 0.0);
	rotMat[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);
*/
	//glm::mat4 transMat = glm::rotate(this->angle, glm::vec3(0, 1, 0));

//
///*/*
	//if (nFlags & MK_RBUTTON || nFlags & MK_LBUTTON)
	//{
	//	if (this->rotateType == 0)
	//	{
	//		this->angle = 0.1f;
	//	}
	//	else
	//	{
	//		this->angle = -0.1f;
	//	}
	//	glm::mat4 transMat = glm::rotate(this->angle, glm::vec3(0, 1, 0));
	//	m_CubeTransform = transMat*m_CubeTransform;

	//}*/*/
	CView::OnMouseMove(nFlags, point);
}

void CCGOGL2014View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
/*
	this->angle = -1.0f;
	glm::mat4 transMat = glm::rotate(this->angle, glm::vec3(0, 1, 0));
		m_CubeTransform = transMat*m_CubeTransform;*/

	CView::OnLButtonDown(nFlags, point);
}

void CCGOGL2014View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	float x,y;

	CRect rect;
	this->GetClientRect(&rect);
//
//		this->angle = 1.0f;
//	glm::mat4 transMat = glm::rotate(this->angle, glm::vec3(0, 1, 0));
//		m_CubeTransform = transMat*m_CubeTransform;
//
	//this->rotateType = 0;

	x = (point.x/(float)rect.Width())*2 - 1;
	y = (-point.y/(float)rect.Height())*2 + 1;

	CView::OnRButtonDown(nFlags, point);
}

void CCGOGL2014View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nChar)
	{
	case 'L':
		if (this->isLanded)
		{
			this->isLanded = false;
		}
		else
		{
			this->mc.dy = -0.1f;
			this->isLanded = true;
		}
		break;
	case 'Q':
		this->mc.dx += MOVENUM;
		break;
	case 'W':
		this->mc.dx -= MOVENUM;
		break;
	case 'E':
		if (!this->isLanded)
		{
			this->mc.dy += MOVENUM;
		}
		break;
	case 'R':
		if (!this->isLanded)
		{
			this->mc.dy -= MOVENUM;
		}
		break;
	case 'T':
		this->mc.dz += MOVENUM;
		break;
	case 'Y':
		this->mc.dz -= MOVENUM;
		break;
	case 'J':
		this->light.mShininess += 1.0f;
		break;
	case 'K':
		this->light.mShininess -= 1.0f;
		break;
	case VK_RIGHT:
		this->mc.thetaX += 1.0f;
		break;
	case VK_LEFT:
		this->mc.thetaX -= 1.0f;
		break;
	case VK_UP:
		this->mc.thetaY -= 1.0f;
		break;
	case VK_DOWN:
		this->mc.thetaY += 1.0f;
		break;
	case 'A':
		this->light.lx += 0.01f;
		break;
	case 'S':
		this->light.lx -= 0.01f;
		break;
	case 'D':
		this->light.ly += 0.01f;
		break;
	case 'F':
		this->light.ly -= 0.01f;
		break;
	case 'G':
		this->light.lz += 0.01f;
		break;
	case 'H':
		this->light.lz -= 0.01f;
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CCGOGL2014View::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
/*
	if (message & MK_LBUTTON)
	{
		this->dx += 1.0f;
	}*/


	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

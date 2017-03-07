// OpenGL.cpp: implementation of the OpenGL class.
//
//////////////////////////////////////////////////////////////////////
#include"stdafx.h"
#include "allheader.h"
#include "Draw.h"

#include "OpenGL.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OpenGL::OpenGL()
{
	hDC=NULL;
	hRC=NULL;
	m_draw=new Draw();
	m_displayscene=new CDisplayScene();
}

OpenGL::~OpenGL()
{
	ClearUp();
	delete m_draw;
	delete m_displayscene;
}

bool OpenGL::SetupPixelFormat(HDC h)
{
	int nPixelFormat;
	this->hDC=h;
	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,LPD_TYPE_RGBA,16,
		0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0, PFD_MAIN_PLANE,0,0,0,0
	};
	if(!(nPixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		MessageBox(NULL,"û���ҵ����ʵ����ظ�ʽ!","tips",MB_OK);
		return FALSE;
	}
	SetPixelFormat(hDC,nPixelFormat,&pfd);
	this->hRC=wglCreateContext(this->hDC);
	wglMakeCurrent(this->hDC,this->hRC);
	m_draw=new Draw();
	m_draw->Light1();
	m_draw->Material();
	return TRUE;
}

void OpenGL::ReSize(int width,int height)
{
	
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION); //͸��ͶӰ
	glLoadIdentity();
	gluPerspective(45.0f,width/height,0.1f,3000.0f);//͸��ͶӰ����������
	glMatrixMode(GL_MODELVIEW);//ģ�͹۲����
	glLoadIdentity();
	
}

void OpenGL::Render()
{
	//{��ʼһЩ����
	glClearColor(89.0/255,135.0/255,178.0/255,1.0f);
	glShadeModel (GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);	 // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glEnable(GL_DEPTH_TEST);  // Enables Depth Testing
	//glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
	//}
	//{���ο���ע��
	m_draw->DrawBiaoZhu();
	//}	
	

	//{��ͼ�任
	m_displayscene->DisplayScene();
	//}

	//{ģ��չʾ	
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	m_draw->RobotModel(m_draw->m_A_c);
	//}
	
	//{���Ƶ���
	m_draw->Ground();
	//}
	glFlush();
	SwapBuffers(hDC);
}



void OpenGL::ClearUp()
{
	wglMakeCurrent(hDC,NULL);
	wglDeleteContext(hRC);
}


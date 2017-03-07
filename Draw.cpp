// Draw.cpp: implementation of the Draw class.
//
//////////////////////////////////////////////////////////////////////
#include"stdafx.h"
#include "allheader.h"
#include "Draw.h"
#include "OpenGL.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Draw::Draw()
{
	m_Sx=0;
	m_Sy=0;
	m_Sz=0;
	//{{ģ�͵����ʼ��
	InitModel();
	//}}
	//{{ģ�;����ʼ��
	InitMatrix();
	//}}
}

Draw::~Draw()
{	
	glDeleteLists(list,8);
}




void Draw::Ground()
{
	glDisable(GL_LIGHTING);
	//glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0f,0.0,0.0);
		//���������
		glColor3f(164.0/255,74.0/255,38.0/255);
		glBegin(GL_LINES);
		for(int i=-20;i<=20;i+=2)
		{
			glVertex3f(i,0.0f,20);
			glVertex3f(i,0.0f,-20);
			glVertex3f(20,0.0f,i);
			glVertex3f(-20,0.0f,i);
		}
		glEnd();		
		
		//������
		glColor3f(125.5/255,125.0/255,125.0/255);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-20,-0.05,20);
		glVertex3f(20,-0.05,20);
		glVertex3f(-20,-0.05,-20);
		glVertex3f(20,-0.05,-20);
		glEnd();

	//������ϵ
	glBegin(GL_LINES);	
	glTranslatef(0.0f,0.0f,0.0f);
	glColor3f(1.0f,0.0f,0.0f);//x
		glVertex3f(30,0.0f,0.0f);
		glVertex3f(-30,0.0f,0.0f);

	glColor3f(0.0f,1.0f,0.0f);//y
		glVertex3f(0.0f,8,0.0f);
		glVertex3f(0.0f,0.0,0.0f);

	glColor3f(0.0f,0.0f,1.0f);//z
		glVertex3f(0.0f,0.0f,30);
		glVertex3f(0.0f,0.0f,-30);

	//���̶���
	/*for(GLfloat iz=0;iz<=8;iz+=0.1)
	{
		if(int(iz*10+1)%11==0)
		{
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,iz,0.0f);
			glVertex3f(0.0f,iz,1.0f);
		}
		else
		{
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,iz,0.0f);
			glVertex3f(0.0f,iz,3.0f);
		}

	}

	
	for(GLfloat ix=0;ix<=8;ix+=0.1)
	{

		if(int(ix*10+1)%11==0)
		{
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0.0f,ix,0.0f);
			glVertex3f(1.0f,ix,0.0f);
		}
		else
		{
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0.0f,ix,0.0f);
			glVertex3f(1.0f,ix,0.0f);		
		}
	}*/
	glEnd();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}


void Draw::load3dobj(char* dir,char* cn,int a)
{	
	char	appdir[256];
	GetCurrentDirectory(256,appdir);
	SetCurrentDirectory(dir);
	m_3ds->Init(cn,a);
	SetCurrentDirectory(appdir);
}

void Draw::Light1()
{
	//{�ƹ����
		GLfloat light_AMBIENT[4]={0.5f, 0.5f, 0.5f, 1.0f};
		GLfloat light_DIFFUSE[4]={0.5f, 0.5f, 0.5f,1.0f};
		GLfloat light_SPECULAR[4]={1.0f,1.0f,1.0f,1.0f};
		GLfloat light_POSITION[4]={0.0f,10.0f,0.0f,1.0f};
	//}
	//{�����趨
		glLightfv(GL_LIGHT1,GL_AMBIENT,light_AMBIENT);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,light_DIFFUSE);
		glLightfv(GL_LIGHT1,GL_SPECULAR,light_SPECULAR);
		glLightfv(GL_LIGHT1,GL_POSITION,light_POSITION);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
	//}

}

void Draw::Material()
{
	//{���ʲ���
		GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 0.0 }; 
		GLfloat mat_AMBIENT[]={0.5f, 0.5f, 0.5f, 1.0f};
		GLfloat mat_shininess[] = { 50.0 };	
	//}
	//{�����趨
		//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_AMBIENT,mat_AMBIENT);
	//}
}




void Draw::RobotModel(Ccontrl* m)
{	
	GLfloat m_matrixC[16];
	GLfloat m_matrixR[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,m_matrixC);
	//�õ��任ǰ������λ��
	m_Sx=m_matrixC[12];
	m_Sy=m_matrixC[13];
	m_Sz=m_matrixC[14];
	//PrintMatrix(m_matrixC);
	glPushMatrix();
	//����0
	glColor3f(75.0/255,75.0/255,75.0/255);
	glCallList(list);
	
		//��ת֧��1
		
		/*glTranslatef(0.0,1.195,0);
		glRotatef(m[1].m_rotate_z,0,1,0);*/
		glColor3f(167.0/255,67.0/255,4.0/255);
		glMultMatrixf(m[1].Matrix);
		glCallList(list+1);	
		zuobiao_Line();
			//���2
			/*glTranslatef(-0.455f,1.426f,0.0f);
			glRotatef(m[2].m_rotate_b,0.0f,0.0f,1.0f);*/
			glColor3f(134.0/255,134.0/255,134.0/255);
			glMultMatrixf(m[2].Matrix);
			glCallList(list+2);
			zuobiao_Line();
				//��ͷ3
				/*glTranslatef(-0.078f,2.361f,0.0f);
				glRotatef(-90,0.0,1.0,0.0);
				glRotatef(m[3].m_rotate_b,1.0f,0.0f,0.0f)*/;
				glColor3f(83.0/255,83.0/255,83.0/255);
				glMultMatrixf(m[3].Matrix);
				glCallList(list+3);
				zuobiao_Line();	
				    //��Ͳ4
					/*glRotatef(90.0f,1.0f,0.0f,0.0f);
					glTranslatef(0.0f,0.246f,-0.582f);*/
					glColor3f(100.0/255,103.0/255,94.0/255);
					glMultMatrixf(m[4].Matrix);
					glCallList(list+4);

						//С������5
						/*glTranslatef(0.0f,0.629f,0.0f);
						glRotatef(180.0f,1.0f,0.0f,0.0f);
						glRotatef(m[5].m_rotate_z,0.0f,1.0f,0.0f);//ת��*/
						glColor3f(0.5,0.3,0.2);
						glMultMatrixf(m[5].Matrix);
						glCallList(list+5);
						zuobiao_Line();
							//С��6
								glColor3f(80.0/255,80.0/255,80.0/255);
								glMultMatrixf(m[6].Matrix);
							glCallList(list+6);

								//����7�ڶ�
								/*glTranslatef(0.0f,-2.04f,0.0f);
								glRotatef(90.0f,0.0f,0.0f,1.0f);
								glRotatef(0,0.0f,1.0f,0.0f);*/
								glColor3f(124.0/255,60.0/255,60.0/255);
								glMultMatrixf(m[7].Matrix);
								glCallList(list+7);
								zuobiao_Line();
								
								//ĩ��8
								/*glTranslatef(-0.74,0,0);
								 glRotatef(-90,0,0,1);*/
								glColor3f(0.8,0.8,0.6);
								glMultMatrixf(m[8].Matrix);
								glCallList(list+8);
								zuobiao_Line();
								glGetFloatv(GL_MODELVIEW_MATRIX,m[9].Matrix);
								//ĩ��������

								
	//ʵ��
		/*static GLfloat m_sy[16];
		m_cm.MultMatrix(m_sy,m[7].Matrix,m[8].Matrix,FALSE);
		for(int i=6;i>=0;i--)
		{
			m_cm.MultMatrix(m_matrixR,m[i].Matrix,m_sy,FALSE);
			for(int j=0;j<16;j++)
				m_sy[j]=m_matrixR[j];
			
		}
		PrintMatrix(m_sy);*/
	glPopMatrix();
}

void Draw::InitMatrix()
{
	
	//{{ģ�;����ʼ��
	//��������ʡ��

	//��ת֧��
	m_A_c[1].Matrix[13]=1.195;
	//���
	m_A_c[2].Matrix[12]=-0.455;
	m_A_c[2].Matrix[13]=1.426;
	//��ͷ
	m_A_c[3].Matrix[0]=0.0f;
	m_A_c[3].Matrix[2]=1.0f;
	m_A_c[3].Matrix[8]=-1.0f;
	m_A_c[3].Matrix[10]=0.0f;
	m_A_c[3].Matrix[12]=-0.078;
	m_A_c[3].Matrix[13]=2.361;
	//��Ͳ
	m_A_c[4].Matrix[5]=0;
	m_A_c[4].Matrix[6]=1;
	m_A_c[4].Matrix[9]=-1;
	m_A_c[4].Matrix[10]=0;
	m_A_c[4].Matrix[13]=0.582;
	m_A_c[4].Matrix[14]=0.246;
	//С������
	m_A_c[5].Matrix[5]=-1;
	m_A_c[5].Matrix[10]=-1;
	m_A_c[5].Matrix[13]=0.629;
	//С��
	m_A_c[6].Matrix[13]=-0.4;
	//����
	m_A_c[7].Matrix[0]=0;
	m_A_c[7].Matrix[1]=1;
	m_A_c[7].Matrix[4]=-1;
	m_A_c[7].Matrix[5]=0;
	m_A_c[7].Matrix[13]=-2.04;
	//ĩ��
	m_A_c[8].Matrix[0]=0;
	m_A_c[8].Matrix[1]=-1;
	m_A_c[8].Matrix[4]=1;
	m_A_c[8].Matrix[5]=0;
	m_A_c[8].Matrix[12]=-0.74;
	//}}
}

void Draw::InitModel()
{
		//{��������
		//this->LoadGLTextures();
	//}

	//{{����ģ��
		m_3ds=new CLoad3DS();//ʵ����ģ�ͽ�����
		/*load3dobj("E:/�����ֱ�ģ��/3ds file/","Asm3.3ds",0);		
		load3dobj("E:/�����ֱ�ģ��/3ds file/","���Ա���.3ds",50);
		load3dobj("E:/�����ֱ�ģ��/3ds file/","���1.3ds",51);*/
		load3dobj("Model/","����.3ds",0);
		load3dobj("Model/","��ת֧��.3ds",1);
		load3dobj("Model/","���.3ds",2);
		load3dobj("Model/","��ͷ.3ds",3);
		load3dobj("Model/","ԲͲ.3ds",4);
		load3dobj("Model/","С������.3ds",5);
		load3dobj("Model/","С��.3ds",6);
		load3dobj("Model/","����.3ds",7);
		load3dobj("Model/","ĩ��ִ����.3ds",8);
		load3dobj("Model/","����2.3ds",9);
	//}}
		
	//{{��ģ�ͷ�����ʾ�б�
		list=glGenLists(10);
		for(int i=0;i<10;i++)
		{
			if(i==6||i==7||i==8)
			{
				glNewList(list+i,GL_COMPILE);
					m_3ds->show3ds(i,0.3f);
				glEndList();
			}
			else
			{
				glNewList(list+i,GL_COMPILE);
					m_3ds->show3ds(i,0.4f);
				glEndList();
			}
		}		
	//}}
}

void Draw::PrintMatrix(GLfloat *matrix)
{
		char buf[1024];
		memset(buf,0,sizeof(buf));
	    sprintf( buf,"%8.2f%8.2f%8.2f%8.2f\n"  
            "%8.2f%8.2f%8.2f%8.2f\n"  
            "%8.2f%8.2f%8.2f%8.2f\n"  
            "%8.3f%8.3f%8.2f%8.2f\n",  
            matrix[0], matrix[4], matrix[8], matrix[12],  
            matrix[1], matrix[5], matrix[9], matrix[13],  
            matrix[2], matrix[6], matrix[10], matrix[14],  
            matrix[3], matrix[7], matrix[11], matrix[15]);
		AfxMessageBox(buf);
}

void Draw::DrawBiaoZhu()
{
	//{���ο���ע
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glPushMatrix();
		
		glTranslatef(0,0,-2);
		//Y
		glPushMatrix();
		glColor3f(0,1,0);		
		glRasterPos3f(-0.8f,-0.64f,0);
		DrawString("Y");
		
		glBegin(GL_LINES);
		glVertex3f(-0.8,-0.8,0);
		glVertex3f(-0.8,-0.65,0);
		glEnd();
		
		glTranslatef(-0.8,-0.65,0);
		glRotatef(-45,0,0,1);
		glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0.015,0,0);
		glEnd();
		glRotatef(90,0,0,1);
		glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(-0.015,0,0);
		glEnd();
		glPopMatrix();
		
		//x
		glPushMatrix();
		glColor3f(1,0,0);		
		glRasterPos3f(-0.64f,-0.8f,0);
		DrawString("X");

		glBegin(GL_LINES);
		glVertex3f(-0.8,-0.8,0);
		glVertex3f(-0.65,-0.8,0);
		glEnd();

		glTranslatef(-0.65,-0.8,0);
		glRotatef(135,0,0,1);
		glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0.015,0,0);
		glEnd();
		glRotatef(-90,0,0,1);
		glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(-0.015,0,0);
		glEnd();
		glPopMatrix();
		
	glPopMatrix();
	glLineWidth(1.0);
	//}
}

void Draw::DrawString(const char *str)
{
    static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
                        // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
        isFirstCall = 0;

        // ����MAX_CHAR����������ʾ�б���
        lists = glGenLists(128);

        // ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
        wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
    }
    // ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
    for(; *str!='\0'; ++str)
        glCallList(lists + *str);   
}

void Draw::zuobiao_Line()
{
	glBegin(GL_LINES);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1.5);
	
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,1.5,0);
	
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1.5,0,0);
	glEnd();
}

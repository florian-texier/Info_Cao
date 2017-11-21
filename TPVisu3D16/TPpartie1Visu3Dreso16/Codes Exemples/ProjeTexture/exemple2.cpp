#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include"glut.h"
#include<GL/glu.h>





float a = 0;
float angle=50.0;
float angle2=50.0;
float angle3=50.0;

GLUquadricObj *obj = gluNewQuadric();


GLfloat no_mat[] = { 0.0F,0.0F,0.0F,1.0F };
  GLfloat mat_blanc[] = { 0.7F,0.7F,0.7F,1.0F };
  GLfloat mat_diffuse[] = { 0.1F,0.5F,0.8F,1.0F };
  GLfloat mat_specular[] = { 1.0F,1.0F,1.0F,1.0F };
  GLfloat no_shininess[] = { 0.0F };
  GLfloat low_shininess[] = { 5.0F };
  GLfloat high_shininess[] = { 100.0F };
  GLfloat mat_emission[] = {0.3F,0.2F,0.2F,0.0F};
  GLfloat jaunatre[4] = { 1.0, 1.0, .95, 1.0 };
  GLfloat ambientProperties[] = {0.0, 0.0, 0.00005, 0.0};

//Fenêtre GLUT
int	Win;

//Fonction d'initialisation
void Init();
//Fonction de redimensionnement
void Reshape(int w,int h);
//Fonction de dessin
void	display();
//LoadBMP : charge une image 24bpp

//Texture :
GLubyte		Texture[16] = { 0,0,0,0, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0,0,0,0, };
GLuint		Nom[2];

//LoadBMP : charge une image 24bpp
#define EXIT {fclose(fichier);return -1;}
#define CTOI(C) (*(int*)&C)	//récupère en int un nombre pointé par un char*

int LoadBMP(char *File)
{
	unsigned char	*Data;
	FILE			*fichier;
	unsigned char	Header[0x36];
	GLuint			DataPos,DataSize;
	GLint			Components;
	GLsizei			Width,Height;
	GLenum			Format,Type;
	GLuint			Name[1];
	
//Lit le fichier et son header
	fichier = fopen(File,"rb");if (!fichier) return -1;
	if (fread(Header,1,0x36,fichier)!=0x36) EXIT;
	if (Header[0]!='B' || Header[1]!='M')	EXIT;
	if (CTOI(Header[0x1E])!=0)				EXIT;
	if (CTOI(Header[0x1C])!=24)				EXIT;

//Récupère les infos du fichier
	DataPos			= CTOI(Header[0x0A]);
	DataSize		= CTOI(Header[0x22]);
//Récupère les infos de l'image
	Width			= CTOI(Header[0x12]);
	Height			= CTOI(Header[0x16]);	
	Type = GL_UNSIGNED_BYTE;
	Format = GL_RGB;
	Components = 3;
	
	//!!!!
	if (DataSize==0) DataSize=Width*Height*Components;
	if (DataPos==0)  DataPos=0x36;

//Charge l'image
	fseek(fichier,DataPos,0);
	Data = new unsigned char[DataSize];
	if (!Data) EXIT;

	if (fread(Data,1,DataSize,fichier)!=DataSize) 
	{
		delete Data;
		fclose(fichier);
		return -1;
	}
	
	fclose(fichier);

//Inverse R et B
	unsigned char t;
	for (int x=0;x<Width*Height;x++) 
	{
		t=Data[x*3];
		Data[x*3]=Data[x*3+2];
		Data[x*3+2]=t;
	}

//Envoie la texture à OpenGL
//	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, Name);
	glBindTexture(GL_TEXTURE_2D, Name[0]);
	
	
	glTexImage2D
	( 	
		GL_TEXTURE_2D, 	//target
		0,				//mipmap level
		Components,		//nb couleurs
		Width,			//largeur
		Height,			//hauteur
		0,			 	//largeur du bord
		GL_RGB,			//type des couleurs
		GL_UNSIGNED_BYTE,			//codage de chaque composante
		Data			//Image
	); 
	
	return Name[0];
}



void init(void) 

{
glEnable(GL_TEXTURE_2D);

glShadeModel(GL_SMOOTH);


glEnable(GL_DEPTH_TEST); /* on active le z-buffer */







    
    
   	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);	
	glLoadIdentity ();  
		

	

	Nom[0] = LoadBMP("earth.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);




	
	Nom[1] = LoadBMP("space3.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);





	
	glDepthFunc(GL_LESS);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	

   

}





void space(void){
	
  glPushMatrix();
        glTranslated(0,-21.5,0);
        glRotated(45,1,0,0);
        glBindTexture(GL_TEXTURE_2D, Nom[1]);
        glBegin(GL_QUADS);
			glTexCoord2i(0, 3);
			glVertex2i(-320,240);
			glTexCoord2i(4, 3);
			glVertex2i(320,240);
			glTexCoord2i(4, 0);
			glVertex2i(320, -240);
			glTexCoord2i(0, 0);
			glVertex2i(-320, -240);
       glEnd();
    glPopMatrix();
    }



	void display(void)

{

 

// increment des angles servant a la rotation des objets

	
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	
	/* Le Soleil */
	

	
	glDisable(GL_DEPTH_TEST);
    space();    
	//glEnable(GL_DEPTH_TEST);
	

	
	

	
	

	

	
	// La Terre  
	
	
	glBindTexture(GL_TEXTURE_2D, Nom[0]);
	
	
	
	gluQuadricTexture(obj, GL_TRUE );
	gluQuadricDrawStyle(obj, GLU_FILL);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(11.5,-10.5,6.5);
	glRotatef(angle2, 0.0f, 1.0f, 0.0f);

	gluSphere (obj,3.0, 60, 60);
	
	
	
	

	glLoadIdentity();

	angle+=0.1;
	angle2+=0.15;
	
	//glutPostRedisplay();
	glutSwapBuffers();	
	glFlush();
}





void reshape (int width,int heigth)

{
	glViewport(0,0,width,heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(30.0,0.9,0.0,30.0);
	gluLookAt(0.0,0.0,80.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



// fonction de gestion du clavier 

void keyboard(unsigned char key, int x, int y)

{

   switch (key) {

	  case 'q': // la touche 'q' ou

      case 'Q': // 'Q'

	  case 27 :

		 exit(0);

         break;

   }

}



int main( int argc, char *argv[ ], char *envp[ ] )
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE| GLUT_DEPTH);
	glutInitWindowSize (500, 500); 
	Win=glutCreateWindow("Univers");
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;

}

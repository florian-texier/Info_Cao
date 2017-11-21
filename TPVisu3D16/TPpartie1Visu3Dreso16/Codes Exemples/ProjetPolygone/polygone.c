/*****************************************
IMERIR
POLE ICAR 
Infographie 1
AR
*******************************************/
//#include <GL/gl.h>           
//#include <GL/glu.h>         
//#include <GL/glut.h>    

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>

#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define WIDTH  480
#define HEIGHT 480

#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27

void init_scene();

GLvoid initGL();
GLvoid mon_window_display();
GLvoid mon_window_reshape(GLsizei width, GLsizei height); 
GLvoid mon_window_key(unsigned char key, int x, int y); 

int main(int argc, char **argv) 
{  
  // initialisation  des param�tres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  // initialisation du contexte grapique
  glutInitDisplayMode(GLUT_RGBA);

  // d�finition et cr�ation de la fen�tre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carr�");

  // initialisation de OpenGL et de la sc�ne
  initGL();  

  // choix des proc�dures de callback pour 
  // le trac� graphique
  glutDisplayFunc(&mon_window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&mon_window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&mon_window_key);

  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque

GLvoid initGL() 
{
  glClearColor(0, 0, 0, 1);  //ALPHA      
}


// fonction de call-back pour l�affichage dans la fen�tre

GLvoid mon_window_display()
{
  glClear(GL_COLOR_BUFFER_BIT); // initialise le buffer � la couleur du fond. 
  glLoadIdentity();		//initialisation de la matrice courant GL_MODELVIEW 

  glColor3f(1.0, 0.0, 0.0); // couleur du dessin 

  glBegin(GL_POLYGON);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 50.0);
    glVertex3f(150.0, 50.0, 0.0);
  glEnd();

  glColor3f(0.0, 1.0, 0.0); // couleur du dessin 

  glBegin(GL_POLYGON);
  glVertex3f(100.0, 50.0, 0.0);
  glVertex3f(100.0, 0.0, 0.0);
  glVertex3f(100.0f, 0.0, 50.0);
  glEnd();

  // trace la sc�ne grapnique stock� dans le buffer image qui vient juste d'�tre d�finie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre si on modifie sa taile.

GLvoid mon_window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height); 

  glMatrixMode(GL_PROJECTION); //indique le type  de transformation et charge la matrice correspondante 
  glLoadIdentity();		//Initialise la matrice courante � la matrice Identit�.
  //gluOrtho2D(-2.0, 2.0, -2.0, 2.0);//d�finit le type de projection : orthogonal 2D,
  glOrtho(-200, 200, -200, 200, -100, 200);
  //et ses param�tres � partir desquels OpenGl construit la matrice de projection correspondante.

  // toutes les transformations suivantes s�appliquent au mod�le de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid mon_window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break; 
    
  default:
    printf ("La touche %d n�est pas active.\n", key);
    break;
  }     
}




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
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  // initialisation du contexte grapique
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carré");

  // initialisation de OpenGL et de la scène
  initGL();  

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&mon_window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&mon_window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&mon_window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
  glClearColor(0, 0, 0, 1);  //ALPHA      
}


// fonction de call-back pour l´affichage dans la fenêtre

GLvoid mon_window_display()
{
  glClear(GL_COLOR_BUFFER_BIT); // initialise le buffer à la couleur du fond. 
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

  // trace la scène grapnique stocké dans le buffer image qui vient juste d'être définie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre si on modifie sa taile.

GLvoid mon_window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height); 

  glMatrixMode(GL_PROJECTION); //indique le type  de transformation et charge la matrice correspondante 
  glLoadIdentity();		//Initialise la matrice courante à la matrice Identité.
  //gluOrtho2D(-2.0, 2.0, -2.0, 2.0);//définit le type de projection : orthogonal 2D,
  glOrtho(-200, 200, -200, 200, -100, 200);
  //et ses paramètres à partir desquels OpenGl construit la matrice de projection correspondante.

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid mon_window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break; 
    
  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }     
}




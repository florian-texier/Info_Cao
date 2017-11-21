/*****************************************************************************
File: opengl-anim6.c

IMERIR/ICAR
******************************************************************************/
#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>

#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>


#define WIDTH  480
#define HEIGHT 480

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27
#define My_Square 1
#define My_Cube 2
#define PI 3.1415926535898

#define FALSE 0
#define TRUE 1

int angle_x = 0, angle_y = 0;
int mouse_pos_x = 0, mouse_pos_y = 0;
int mouse_down_is_left = FALSE;

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_mouseFunc(int button, int state, int x, int y);
GLvoid window_motionFunc(int x, int y);
void make_square();
void make_cube();

int main(int argc, char **argv) 
{  
  // initialisation  des param�tres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  // d�finition et cr�ation de la fen�tre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Trac� en volume");

  // initialisation de OpenGL et de la sc�ne
  initGL();  
  init_scene();

  // choix des proc�dures de callback pour 
  // le trac� graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&window_key);
  // la gestion des clicks souris
  glutMouseFunc(&window_mouseFunc);
  // la gestion des d�placement souris
  glutMotionFunc(&window_motionFunc);

  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque

GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);        
  glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
  // initialise des display lists du carr� et du cube
  make_square();
  make_cube();
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  render_scene();

  // trace la sc�ne grapnique qui vient juste d'�tre d�finie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);

  // toutes les transformations suivantes s�appliquent au mod�le de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y) 
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

// fonction de call-back de gestion des clicks souris

GLvoid window_mouseFunc(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    mouse_pos_x = x;
    mouse_pos_y = y;
    mouse_down_is_left = TRUE;
  }
  else {
    mouse_down_is_left = FALSE;
  }
}

// fonction de call-back de gestion des d�placement de la souris

GLvoid window_motionFunc(int x, int y)
{
  if( !mouse_down_is_left )
    return;

  angle_x += y - mouse_pos_y;
  angle_y += x - mouse_pos_x;

  mouse_pos_x = x;
  mouse_pos_y = y;

  glutPostRedisplay();
}

// le trac� graphique cercles et ellipses

void make_square() {
  glNewList(My_Square, GL_COMPILE);
    glBegin(GL_POLYGON);
      glVertex3f(0, 0, 0);
      glVertex3f(1, 0, 0);
      glVertex3f(1, 1, 0);
      glVertex3f(0, 1, 0);  
    glEnd();  
  glEndList();
}

void make_cube() {
  glNewList(My_Cube, GL_COMPILE);
    glTranslatef(-0.5, -0.5, 0.5);
  
    glColor3f(1, 0, 0);
    glCallList(My_Square);

    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, -1);
    glCallList(My_Square);
    glPopMatrix();
    
    glColor3f(0, 1, 0);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(0, 1, 1);
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glCallList(My_Square);
    glPopMatrix();
    
    glColor3f(0, 0, 1);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glCallList(My_Square);
    glPopMatrix();

  glEndList();
}

void render_scene()
{
  glRotatef(angle_x, 1, 0, 0);
  glRotatef(angle_y, 0, 1, 0);
  glCallList(My_Cube);
  glutSwapBuffers();
}


/*****************************************************************************
File: opengl-anim1.c

IMERIR/ICAR
******************************************************************************/
#include <windows.h> 
#include <GL/gl.h>           
#include <GL/glu.h>         
//  

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>

#include "glut.h"

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

int angle = 0;

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
void make_square();
void make_cube();

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  // définition et création de la fenêtre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Tracé en volume");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);        
  glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
  // initialise des display lists du carré et du cube
  make_square();
  make_cube();
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break; 

  case '+':
    angle++;
    glutPostRedisplay();
    break;
    
  case '-':
    angle--;
    glutPostRedisplay();
    break;
    
  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }     
}

// le tracé graphique cercles et ellipses

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
  glRotatef(angle, 0, 1, 0);
  glRotatef(angle, 1, 0, 0);
  glCallList(My_Cube);
  glutSwapBuffers();
}


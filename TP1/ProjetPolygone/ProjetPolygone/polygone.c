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

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27

float PI = 3.14159265;
double tetaV = 0.0;
double tetaM = 0.0;
double tetaT = 0.0;
double tetaL = 0.0;
double tetaMa = 0.0;
double angle1 = 0.0;
double angle2 = 0.0;
void init_scene();
void Init_light();
int lancer = 0;
double zoom = -1;
float rotationX = 0;
float rotationY = 0;
float rotationZ = 0;
float translationX = 0;
float translationY = 0;
float translationZ = 0;
int orbite = 1;

GLvoid initGL();
GLvoid mon_window_display();
GLvoid mon_window_reshape(GLsizei width, GLsizei height);
GLvoid mon_window_key(unsigned char key, int x, int y);
//différents paramètres
	GLfloat ambient[] = { 0.15f,0.15f,0.15f,1.0f };
	GLfloat diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
	GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular_reflexion[] = { 0.8f,0.8f,0.8f,1.0f };
	GLubyte shiny_obj = 128;
	GLfloat mat_em[] = { 0, 0,0, 1 };
	GLfloat non_mat_em[] = { 0, 0, 0, 0 };
static GLvoid idle(void);

int main(int argc, char **argv)
{
	// initialisation  des paramètres de GLUT en fonction
	// des arguments sur la ligne de commande
	glutInit(&argc, argv);
	// initialisation du contexte grapique
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE);

	// définition et création de la fenêtre graphique
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Premier exemple : carré");

	// initialisation de OpenGL et de la scène
	initGL();
	Init_light();

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
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	glClearColor(RED, GREEN, BLUE, ALPHA);  //ALPHA      
}

void Init_light()
{
	
	//positionnement de la lumière avec les différents paramètres
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT0);
	//spécification de la réflexion sur les matériaux
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_reflexion);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shiny_obj);


}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid mon_window_display()
{
	glClear(GL_COLOR_BUFFER_BIT); // initialise le buffer à la couleur du fond.
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();		//initialisation de la matrice courant GL_MODELVIEW 
	gluLookAt((200*cos(angle1*(PI/180))*sin(angle2*(PI / 180))), (200 * sin(angle1*(PI / 180))*sin(angle2*(PI / 180))), (200 * cos(angle2*(PI / 180))), 0, 0, 0, 0, 1, 0);

	glScaled(zoom, zoom, zoom);
	glRotated(rotationX, 1, 0, 0);
	glRotated(rotationY, 0, 1, 0);
	glRotated(rotationZ, 0, 0, 1);
	glTranslated(translationX, translationY, translationZ);

	//--------------------------------------------------Orbite
	if (orbite==1)
	{
		//TERRE
		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 255);
		for (int i = 0;i < 360;i++) {
			glVertex3f(100 * sin(i*(PI / 180)), 0, 100 * cos(i*(PI / 180)));
		}
		glEnd();
		//Lune
		glPushMatrix();
		glRotatef(tetaT, 0, tetaT, 0.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(205, 201, 201);
		for (int i = 0; i < 200; i++) {
			float theta = 2.0 * PI * (float)i / (float)200;

			float x = 20 * cos(theta);
			float y = 20 * sin(theta);

			//printf("Orbite Lune X : %f\nOrbite Lune Y : %f\n", x, z);

			glVertex3f(y + 100, 0, x);
		}
		glEnd();
		glPopMatrix();

		//MERCURE
		glBegin(GL_LINE_LOOP);
		glColor3f(205, 200, 177);
		for (int i = 0;i < 360;i++) {
			glVertex3f(200 * sin(i*(PI / 180)), 0, 200 * cos(i*(PI / 180)));
		}
		glEnd();

		//VENUS
		glBegin(GL_LINE_LOOP);
		glColor3f(238, 153, 0);
		for (int i = 0;i < 360;i++) {
			glVertex3f(220 * sin(i*(PI / 180)), 0, 220 * cos(i*(PI / 180)));
		}
		glEnd();

		//MARS
		glBegin(GL_LINE_LOOP);
		glColor3f(255, 0, 0);
		for (int i = 0;i < 360;i++) {
			glVertex3f(150 * sin(i*(PI / 180)), 0, 150 * cos(i*(PI / 180)));
		}
		glEnd();
	}
	

	//-----------------------------------------------------------Planette
	//Soleil
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_em);
	glBegin(GL_POLYGON);
	glColor3f(255,215, 0);
	glutSolidSphere(54.5, 50, 50);
	glEnd();
	
	
	glPushMatrix();
		//Terre
		glRotated(tetaT, 0, tetaT, 0);
		glTranslated(100, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 255);
		glutSolidSphere(7.5, 50, 50);
		glEnd();
		glPushMatrix();
			//Lune
			glRotated(tetaL*2, 0, tetaL*2, 0);
			glTranslated(20.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			glColor3f(205, 201, 201);
			glutSolidSphere(2, 50, 50);
			glEnd();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		//Mercure
		glRotated(tetaM*1.5, 0, tetaM*1.5, 0);
		glTranslated(200, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glColor3f(205, 200, 177);
		glutSolidSphere(4.4, 50, 50);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		//Venus
		glRotated(tetaV*0.5, 0, tetaV*0.5, 0);
		glTranslated(220, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glColor3f(238, 153, 0);
		glutSolidSphere(7.2, 50, 50);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		//Mars
		glRotated(tetaMa*2.5, 0, tetaMa*2.5, 0);
		glTranslated(150, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glColor3f(255, 0, 0);
		glutSolidSphere(5.16, 50, 50);
		glEnd();
	glPopMatrix();
	/*//Axe u
	glColor3f(1.0, 0.0, 0.0); // couleur du dessin 

	glBegin(GL_LINES);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	//Axe v
	glColor3f(0.0, 1.0, 0.0); // couleur du dessin 

	glBegin(GL_LINES);
	glVertex3f(0.0, 100.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	//Axe n
	glColor3f(0.0, 0.0, 1.0); // couleur du dessin 

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 100.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	*/
	//glFlush();
	glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre si on modifie sa taile.

GLvoid mon_window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); //indique le type  de transformation et charge la matrice correspondante 
	glLoadIdentity();		//Initialise la matrice courante à la matrice Identité.
	//gluOrtho2D(-2.0, 2.0, -2.0, 2.0);//définit le type de projection : orthogonal 2D,
	//glOrtho(-200, 200, -200, 200, -100, 200);
	gluPerspective(120, 1, 1, 500);
	//et ses paramètres à partir desquels OpenGl construit la matrice de projection correspondante.

	// toutes les transformations suivantes s´appliquent au modèle de vue 
	glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

static GLvoid idle(void)
{
	tetaT = tetaT + 1.0; //penser à limiter teta à 2pi
	if (tetaT > 360) {
		tetaT = 0.0;
	}
	tetaM = tetaM + 1.0; //penser à limiter teta à 2pi
	if (tetaT > 360*(1.5)) {
		tetaT = 0.0;
	}
	tetaV = tetaV + 1.0; //penser à limiter teta à 2pi
	if (tetaV > (360*2)) {
		tetaV = 0.0;
	}
	tetaL = tetaL + 1.0; //penser à limiter teta à 2pi
	if (tetaL > (360*2)) {
		tetaL = 0.0;
	}
	tetaMa = tetaMa + 1.0; //penser à limiter teta à 2pi
	if (tetaMa > (360*2.5)) {
		tetaMa = 0.0;
	}

	glutPostRedisplay();// affichage immédiat
}

GLvoid mon_window_key(unsigned char key, int x, int y)
{
	switch (key) {

	case KEY_ESC:
		exit(1);
		break;

	case 'r':		
		if (lancer == 0)
		{
			glutIdleFunc(idle);
			lancer = 1;
		}
		else {
			glutIdleFunc(NULL);
			lancer = 0;
		}
		break;

	case '8':		
		if (angle1 < 180.0) {
			angle1 = angle1 + 1.0; 
		}		
		break;

	case '5':
		if (angle1 > 0.0) {
			angle1 = angle1 - 1.0; 
		}
		break;

	case '6':
		angle2 = angle2 - 1.0; 
		if (angle2 < 0.0) {
			angle2 = 360.0;
		}
		break;

	case '4':
		angle2 = angle2 + 1.0;
		if (angle2 > 360.0) {
			angle2 = 0.0;
		}
		break;

	case '-':
		if (zoom < -0.1) {
			zoom = zoom + 0.1;
		}
		
		break;
	case '+':
		zoom=zoom-0.1;
		break;
	case 'x':
		rotationX++;
		if (rotationX > 360)
		{
			rotationX = 0;
		}
		break;
	case 'y':
		rotationY++;
		if (rotationY > 360)
		{
			rotationY = 0;
		}
		break;
	case 'z':
		rotationZ++;
		if (rotationZ > 360)
		{
			rotationZ = 0;
		}
		break;
	case 'X':
		translationX++;
		if (translationX > 360)
		{
			translationX = 0;
		}
		break;
	case 'Y':
		translationY++;
		if (translationY > 360)
		{
			translationY = 0;
		}
		break;
	case 'Z':
		translationZ++;
		if (translationZ > 360)
		{
			translationZ = 0;
		}
		break;
	case 'o':
		
		if (orbite == 1)
		{
			orbite = 0;
		}
		else {
			orbite = 1;
		}
		break;

	default:
		printf("La touche %d n´est pas active.\n", key);
		break;
	}
	glutPostRedisplay();// affichage immédiat
}




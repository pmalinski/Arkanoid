#include"cScene.h"
#include<GL/glut.h>
#include<vector>
#include"cRectangle.h"
#include"cOkrag.h"
#include<iostream>

using namespace std;

#define NDEBUG

cScene scena;
vector<cFigura*> figury;

//################################################################################# FUNKCJE GLUT #################################################################################

void init() //inicjalizacja obiektow
{
	cOkrag *o = new cOkrag(0.5, 0, 0);
	o->setFizyka(9.81*1E-6, -90);
	o->setPredkosc(3e-2, 60);
	figury.push_back(o);

	float grubosc_scianek = 3;
	figury.push_back(new cRectangle(40, grubosc_scianek, 0, -19.5));
	figury.push_back(new cRectangle(40, grubosc_scianek, 0, 19.5));
	figury.push_back(new cRectangle(grubosc_scianek, 40, -19.5, 0));
	figury.push_back(new cRectangle(grubosc_scianek, 40, 19.5, 0));
}
void idle()
{
	scena.aktualizuj();
	glutPostRedisplay();

	Sleep(1);
}
void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'p':
	{
			   system("pause");
			   break;
	}
	case 27:
	{
			   exit(0);
	}
	}
}
/*void special_key(int key, int x, int y)
{
switch (key)
{
case GLUT_KEY_LEFT:
{

break;
}
case GLUT_KEY_UP:
{

break;
}
case GLUT_KEY_RIGHT:
{

break;
}
case GLUT_KEY_DOWN:
{

break;
}
}
}
void mouse_button(int button, int state, int x, int y)
{
if (button == GLUT_LEFT && state == GLUT_DOWN)
{

}
if (button == GLUT_LEFT && state == GLUT_UP)
{

}
}
void mouse_motion(int x, int y)
{

}*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	scena.rysuj();
	glPopMatrix();
	glutSwapBuffers();
}
void InitGLUTScene(char* window_name)
{
	//ustawienia poczatkowe okna i sceny
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow(window_name);

	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	//ustawienia kamery
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void SetCallbackFunctions()
{
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(key);
	//glutSpecialFunc(special_key);
	//glutMouseFunc(mouse_button);
	//glutMotionFunc(mouse_motion);
}

//################################################################################# METODY KLASY #################################################################################
void cScene::init_scene(int &argc, char* argv)
{
	glutInit(&argc, &argv);
	InitGLUTScene("Arkanoid_v1.0");
	SetCallbackFunctions();
	init();
	glutMainLoop();
}
void cScene::rysuj()
{
	glPushMatrix();

	for (auto fig : figury)
	{
		fig->rysuj();
	}
	glPopMatrix();
}
void cScene::aktualizuj()
{
	int ilosc_figur = figury.size();
	int czas = GetTickCount(); //zwraca czas w [ms]
	for (int i = 0; i < ilosc_figur; i++)
	{
		figury[i]->Aktualizuj(czas); //obliczanie nowych polozen
	}
	//wykrywanie kolizji
	for (int i = 0; i < ilosc_figur; i++)
	{
		for (int j = i + 1; j < ilosc_figur; j++)
		if (figury[i]->Kolizja(*figury[j])) //znajduje kolizje
		{
			//tu mozna zareagowac na kolizje np. usuwajac „zbity” obiekt itp...
		}
	}
}
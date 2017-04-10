#include<GL/freeglut.h>
#include<vector>
#include"cScene.h"
#include"cRectangle.h"
#include"cOkrag.h"
#include"cFizyka.h"
#include"cKlocek.h"
#include<iostream>

using namespace std;

#define NDEBUG

cScene scena;
vector<cFigura*> figury;

//################################################################################# FUNKCJE GLUT #################################################################################

void init() //inicjalizacja obiektow
{
	figury.push_back(new cRectangle(6, 1, 0, -16));//paletka

	figury.push_back(new cOkrag(0.5, 0, 0));

	float grubosc = 4;
	float srodki = 19;
	float dlugosc = grubosc + srodki * 2;
	figury.push_back(new cRectangle(dlugosc, grubosc, 0, -srodki));
	figury.push_back(new cRectangle(dlugosc, grubosc, 0, srodki));
	figury.push_back(new cRectangle(grubosc, dlugosc, -srodki, 0));
	figury.push_back(new cRectangle(grubosc, dlugosc, srodki, 0));
	figury.push_back(new cKlocek);
}
void idle()
{
	scena.aktualizuj();
	glutPostRedisplay();
	Sleep(1);
}
void key(unsigned char key, int x, int y)
{
	cFigura *paletka = figury[0];
	switch (key)
	{
	case'p':
	{
		system("pause");
		break;
	}
	case'a':
	{
		if (!(paletka->Kolizja(*figury[4])))
			figury[0]->move(-2, 0);
		break;
	}
	case'd':
	{
		if (!(paletka->Kolizja(*figury[5])))
			figury[0]->move(2, 0);
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
}*/
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
	cFigura *paletka = figury[0];
	int w = glutGet(GLUT_WINDOW_WIDTH);
	float x_p = ((float)x - w / 2) / 15; //a wartosc polozenia myszy x przeliczona na wspolrzedne sceny
	static float x_p2;
	//float y_p = paletka->ZwracajY();
	float delta_x = x_p - x_p2;

	if (!(paletka->Kolizja(*figury[4])) && delta_x < 0)
	{
		paletka->move(delta_x, 0);
	}
	if (!(paletka->Kolizja(*figury[5])) && delta_x > 0)
	{
		paletka->move(delta_x, 0);
	}
	x_p2 = x_p;
}
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
	glutMouseFunc(mouse_button);
	glutPassiveMotionFunc(mouse_motion);
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
		if (fig->ZwracajWidoczny())
			fig->rysuj();
	}
	glPopMatrix();
}
void cScene::aktualizuj()
{
	int ilosc_figur = figury.size();
	//int czas = GetTickCount(); //zwraca czas w [ms]
	int czas = glutGet(GLUT_ELAPSED_TIME);
	for (int i = 0; i < ilosc_figur; i++)
	{
		figury[i]->Aktualizuj(czas); //obliczanie nowych polozen
	}
	//wykrywanie kolizji
	for (int i = 0; i < ilosc_figur; i++)
	{
		for (int j = i + 1; j < ilosc_figur; j++)
		{
			cKlocek *k = dynamic_cast<cKlocek*>(figury[i]);
			if (k != NULL)
			{
				if (k->Kolizja(*figury[j]))
				{
					//reakcja na uderzenie klocka
				}
			}
			else if (figury[i]->Kolizja(*figury[j])) //znajduje kolizje
			{
				//reakcja na uderzenie figury
			}
		}
	}
}
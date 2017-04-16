#include<GL/freeglut.h>
#include<vector>
#include"cScene.h"
#include"cRectangle.h"
#include"cOkrag.h"
#include"cFizyka.h"
#include"cKlocek.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

#define NDEBUG

cScene scena;
vector<cFigura*> figury; //wszystkie nieruchome figury i paletka
vector<cOkrag*> kulki; //wszystkie kulki

int level = 1;
int score = 0;
int ilosc_klockow = 0;
int ilosc_kulek = 0;
bool over = false; //informacja o tym, czy gracz przegral
bool win = false; //informacja o tym, czy gracz wygral
bool przylep = false; //informacja o tym, czy pileczka przylepia sie do paletki
int czas_rozpoczecia;

int flag_p1 = 0;

//################################################################################# FUNKCJE GLUT #################################################################################

void init() //inicjalizacja obiektow
{
	ilosc_kulek = 0;

	cRectangle *r = new cRectangle(6.5F, 1.5F, 0, -17); //paletka
	figury.push_back(r);

	cOkrag *o = new cOkrag(0.5, 0, -16.5);
	kulki.push_back(o);
	ilosc_kulek++;
	przylep_ustaw(r, o);

	float grubosc = 4;
	float srodki = 19;
	float dlugosc = grubosc + srodki * 2;
	figury.push_back(new cRectangle(dlugosc, grubosc, 0, srodki));
	figury.push_back(new cRectangle(grubosc, dlugosc, -srodki, 0));
	figury.push_back(new cRectangle(grubosc, dlugosc, srodki, 0));
	//figury.push_back(new cRectangle(dlugosc, grubosc, 0, -srodki)); //dolna scianka pod paletka

	//generowanie klockow
	int max_typ[4] = { 999, 4, 2, 1 }; //limity ilosci klockow konkretnego typu
	int poprzedni_typ = 0;
	for (int i = 0; i < 4; i++) //i = numer warsty klockow
	{
		for (int j = 0; j < 5; j++) //j = numer kolumny klockow
		{
			int typ;
			do
			{
				typ = rand() % 4;
			} while (max_typ[typ] <= 0 || (poprzedni_typ > 0 && typ == poprzedni_typ));
			poprzedni_typ = typ;
			for (int k = 0; k < 4; k++)
			{
				if (k == typ)
				{
					max_typ[k]--;
				}
			}
			figury.push_back(new cKlocek((float)-12 + 6 * j, 13 - 3.2F * i, level, typ));
			ilosc_klockow++;
		}
	}
}
void idle()
{
	if (!(over || win))
	{
		scena.aktualizuj();
	}
	glutPostRedisplay();
	Sleep(1);
}
void key(unsigned char key, int x, int y)
{
	cRectangle *paletka = NULL;
	if (figury.size() > 0)
	{
		paletka = dynamic_cast<cRectangle*>(figury[0]);
		float x_p = paletka->ZwracajX();
		float y_p = paletka->ZwracajY();
		float h_p = paletka->zwroc_wysokosc(); //grubosc paletki
	}

	switch (key)
	{
	case'p':
	{
			   system("pause");
			   break;
	}
	case'a':
	{
			   if (figury.size() >= 3 && kulki.size() > 0 && paletka != NULL)
			   {
				   if (!(paletka->Kolizja(*figury[2]) || over))
				   {
					   paletka->move(-2.5, 0);
					   for (auto& k : kulki)
					   {
						   if (k->czy_przylepiony())
						   {
							   k->move(-2.5, 0);
						   }
					   }
				   }
			   }
			   break;
	}
	case'd':
	{
			   if (figury.size() >= 4 && kulki.size() > 0 && paletka != NULL)
			   {
				   if (!(paletka->Kolizja(*figury[3]) || over))
				   {
					   paletka->move(2.5, 0);
					   for (auto& k : kulki)
					   {
						   if (k->czy_przylepiony())
						   {
							   k->move(2.5, 0);
						   }
					   }
				   }
			   }
			   break;
	}
	case 32: //klawisz spcaja
	{
				 if (!(win || over))
				 {
					 for (auto& k : kulki)
					 {
						 if (k->czy_przylepiony()) //sprawdzenie czy kulka jest przylepiona do paletki
						 {
							 k->przylep(false); //odlepienie kulki
							 k->ustaw_wlasciwosci(); //wystrzelenie kulki
						 }
					 }
				 }
				 break;
	}
	case 27: //klawisz escape
	{
				 exit(0); //wyjscie z programu
	}
	case 13: //klawisz enter
	{
				 if (over == true) //ponowne wystartowanie gry
				 {
					 for (auto& fig : figury) delete fig; //usuniecie wszystkich figur
					 figury.clear();
					 for (auto& kul : kulki) delete kul; //usuniecie wszystkich kulek
					 kulki.clear();
					 ilosc_kulek = 0;
					 ilosc_klockow = 0;
					 score = 0; //wyzerowanie ilosci punktow
					 level = 1;
					 init(); //ponowna inicjalizacja gry
					 czas_rozpoczecia = glutGet(GLUT_ELAPSED_TIME);
					 over = false; //ponowne uruchomienie gry
					 przylep = false;
				 }
				 break;
	}
	}
}
void mouse_button(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT && state == GLUT_DOWN && !win && !over)
	{
		for (auto& k : kulki)
		{
			if (k->czy_przylepiony()) //sprawdzenie czy kulka jest przylepiona do paletki
			{
				k->przylep(false); //odlepienie kulki
				k->ustaw_wlasciwosci(); //wystrzelenie kulki
			}
		}
	}
}
void mouse_motion(int x, int y)
{
	if (!(over || win))
	{
		cRectangle* paletka = dynamic_cast<cRectangle*>(figury[0]);
		int w = glutGet(GLUT_WINDOW_WIDTH);
		float x_sc = ((float)x - w / 2) / 15; //wartosc polozenia myszy x przeliczona na wspolrzedne sceny
		float x_p = paletka->ZwracajX();
		float y_p = paletka->ZwracajY();
		float h_p = paletka->zwroc_wysokosc(); //grubosc paletki
		float limit = 17 - paletka->zwroc_szerokosc() / 2;

		if (x_sc < limit && x_sc > -limit)
		{
			paletka->move_to(x_sc, y_p);
			for (auto& k : kulki)
			{
				if (k->czy_przylepiony())
				{
					float r = k->zwroc_promien(); //promien kulki
					k->move_to(x_p + k->zwroc_odleglosc_na_paletce(), y_p + h_p);
				}
			}
		}
	}
}
void wyswietl_napis(float x, float y, string napis, int R = 0, int G = 0, int B = 0)
{
	glColor3ub(R, G, B);
	glRasterPos2f(x, y);
	int dlugosc = napis.length();
	for (int i = 0; i < dlugosc; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, napis[i]);
	}
}
void display()
{
	string punktacja = "PUNKTY: " + to_string(score);
	string poziom = "LEVEL: " + to_string(level);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	if (over)
	{
		wyswietl_napis(-5, 0, "GAME OVER", 255, 255, 255);
		wyswietl_napis(-12, -3, "Aby zaczac ponownie wcisnij ENTER", 255, 255, 255);
	}
	if (win)
	{
		string grat = "Gratulacje!";
		string grat2 = "Poziom " + to_string(level) + " ukonczony";
		wyswietl_napis(-4, 0, grat, 255, 255, 255);
		wyswietl_napis(-7, -3, grat2, 255, 255, 255);
	}
	wyswietl_napis(-17, 17.5, punktacja);
	wyswietl_napis(9, 17.5, poziom);
	scena.rysuj();

	glPopMatrix();
	glutSwapBuffers();
}
void InitGLUTScene(char* window_name)
{
	//ustawienia poczatkowe okna i sceny
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(600, 100);
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
	glutMouseFunc(mouse_button);
	glutPassiveMotionFunc(mouse_motion);
}

//################################################################################# METODY KLASY #################################################################################
void cScene::init_scene(int &argc, char* argv)
{
	srand(time(NULL));
	glutInit(&argc, &argv);
	InitGLUTScene("Arkanoid_v2.0");
	SetCallbackFunctions();
	init();
	czas_rozpoczecia = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
}
void cScene::rysuj()
{
	glPushMatrix();

	for (auto kul : kulki)
	{
		if (kul->ZwracajWidoczny())
			kul->rysuj();
	}
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
	int liczba_kulek = kulki.size();

	//AKTUALIZACJA
	//int czas = GetTickCount(); //zwraca czas w [ms]
	int czas = glutGet(GLUT_ELAPSED_TIME);
	for (int i = 0; i < ilosc_figur; i++)
	{
		figury[i]->Aktualizuj(czas); //obliczanie nowych polozen figur
	}
	for (int i = 0; i < liczba_kulek; i++)
	{
		kulki[i]->Aktualizuj(czas); //obliczanie nowych polozen kulek
	}

	//WYKRYWANIE KOLIZJI
	for (int i = 0; i < liczba_kulek; i++) // i = numer kulki
	{
		for (int j = 0; j < ilosc_figur; j++) // j = numer figury
		{
			for (int k = 0; k < liczba_kulek; k++) // k = numer kulki
			{
				if (i != k)
				{
					kulki[i]->Kolizja(*kulki[k]); //znajduje kolizje miedzy kulkami
				}
			}
			cRectangle *paletka = dynamic_cast<cRectangle*>(figury[0]);
			cKlocek *k = dynamic_cast<cKlocek*>(figury[j]);
			if (k != NULL)
			{
				if (kulki[i]->Kolizja(*k)) //znajduje kolizje z klockiem
				{
					//reakcja na kolizje z klockiem
					if (!(k->ZwracajWidoczny())) //reakcja na zbicie klocka
					{
						score += k->punkty();
						ilosc_klockow--;
						int typ_zbitego = k->zwroc_typ();
						if (typ_zbitego == 1) //przy zbiciu klocka typu 1 paletka tymczasowo sie powieksza
						{
							float szerokosc = 12;
							paletka->ustaw_szerokosc(szerokosc);
							paletka->setGeometria_szerokosc(-szerokosc / 2, szerokosc / 2);
							flag_p1++;
							glutTimerFunc(5000, domyslny_rozmiar_paletki, NULL);
						}
						if (typ_zbitego == 2) //przy zbiciu klocka typu 2 pojawiaja sie dwie dodatkwe kulki
						{
							kulki.push_back(new cOkrag(0.5, paletka->ZwracajX(), -16.5));
							kulki.push_back(new cOkrag(0.5, paletka->ZwracajX(), -16.5));
							ilosc_kulek += 2;
						}
						if (typ_zbitego == 3)
						{
							przylep = true;
							glutTimerFunc(7000, wylacz_przylep, NULL);
						}
					}
				}
			}
			else if (kulki[i]->Kolizja(*figury[j])) //znajduje kolizje z figura inna niz klocek
			{
				if (przylep && kulki[i]->Kolizja(*figury[0])) //warunek przylepienia sie kulki do paletki
				{
					przylep_ustaw(paletka, kulki[i]); //ustawianie parametrow zwiazanych z przylepieniem kulki
				}
			}
		}
	}

	//SPRAWDZANIE CZY ZOSTALY JAKIES KULKI
	for (auto& k : kulki) //sprawdzanie czy w grze zostaly jakies kulki
	{
		if (k->ZwracajWidoczny() && k->ZwracajY() < -21)
		{
			ilosc_kulek--;
			k->ustaw_widoczny(false);
		}
		if (!ilosc_kulek && !over)
		{
			over = true;
			cout << "GAME OVER" << endl;
			cout << "Zdobyles " << score << " punktow." << endl;
			cout << "Czas gry: " << (glutGet(GLUT_ELAPSED_TIME) - czas_rozpoczecia) / 1000 << " sekund." << endl;
			cout << "Wcisnij enter aby zaczac ponownie" << endl;
		}
	}
	//SPRAWDZANIE CZY ZOSTALY JAKIES KLOCKI
	if (ilosc_klockow == 0) //wygana, reset
	{
		win = true;
		glutTimerFunc(3000, pauza, NULL);
	}
}

//##################################### POZOSTALE FUNKCJE #####################################
void przylep_ustaw(cRectangle* paletka, cOkrag* kulka)
{
	kulka->setPredkosc(0, 0);
	kulka->setFizyka(0, 0);
	kulka->przylep(true);
	kulka->ustaw_odleglosc_na_paletce(kulka->ZwracajX() - figury[0]->ZwracajX());
	kulka->move_to(paletka->ZwracajX() + kulka->zwroc_odleglosc_na_paletce(), paletka->ZwracajY() + paletka->zwroc_wysokosc());
}
void pauza(int parametr)
{
	for (auto& fig : figury) delete fig; //usuniecie wszystkich figur
	figury.clear();
	for (auto& kul : kulki) delete kul; //usuniecie wszystkich kulek
	kulki.clear();
	ilosc_kulek = 0;
	level++;
	init(); //ponowna inicjalizacja gry
	przylep = false;
	win = false; //ponowne uruchomienie gry
}
void domyslny_rozmiar_paletki(int a)
{
	flag_p1--;
	if (figury.size() > 0)
	{
		cRectangle *paletka = dynamic_cast<cRectangle*>(figury[0]);
		if (!flag_p1)
		{
			float szerokosc = 6.5F;
			paletka->ustaw_szerokosc(szerokosc);
			paletka->setGeometria_szerokosc(-szerokosc / 2, szerokosc / 2);
		}
	}
}
void wylacz_przylep(int a)
{
	przylep = false;
}
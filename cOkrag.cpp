#include"cOkrag.h"
#include<GL/freeglut.h>
#include<cmath>
#include<cstdlib>

const float pi = 3.14159265358979323F;
cOkrag::cOkrag() :m_promien(0.5), przylepiony(0), odleglosc_na_paletce(0)
{
	ustaw_wlasciwosci();
}
cOkrag::cOkrag(float promien) : m_promien(promien), przylepiony(0), odleglosc_na_paletce(0)
{
	ustaw_wlasciwosci();
}
cOkrag::cOkrag(float promien, float _x, float _y) : m_promien(promien), przylepiony(0), odleglosc_na_paletce(0)
{
	x = _x;
	y = _y;
	ustaw_wlasciwosci();
}
void cOkrag::rysuj()
{
	glPushMatrix();
	glTranslated(x, y, 0);
	glColor3d(r, g, b);

	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i < 360; i += 5)
		{
			float x = (float)m_promien * cos(pi*i / 180);
			float y = (float)m_promien * sin(pi*i / 180);
			glVertex3d(x, y, 0);
		}
	}
	glEnd();

	glPopMatrix();
}
void cOkrag::resize(float dwidth, float dheight) //metoda zmieniajaca rozmiar okregu
{
	if (m_promien + dwidth >= 0)
	{
		m_promien += dwidth;
	}
	if (m_promien + dheight >= 0)
	{
		m_promien += dheight;
	}
}
void cOkrag::ustaw_wlasciwosci()
{
	int kat = rand() % 21 + 40; //losowanie wartosci kata (od 40 do 60 stopni)

	if ((rand() % 2) == 0) //losowanie kierunku poczatkowego kulki (w lewo lub w prawo)
		setPredkosc(4e-2F, (float)kat); //kierunek w prawo
	else setPredkosc(4e-2F, (float)180 - kat); //kierunek w lewo

	setGeometria(x, y, -m_promien, -m_promien, m_promien, m_promien); //ustawienie geometrii
	setFizyka(9.811E-6F, -90); //ustawienie fizyki
}
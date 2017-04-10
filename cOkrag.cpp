#include"cOkrag.h"
#include<GL/freeglut.h>
#include<cmath>

const float pi = 3.14159265358979323F;
cOkrag::cOkrag() :m_promien(0.5)
{
	ustaw_wlasciwosci();
}
cOkrag::cOkrag(float promien) : m_promien(promien)
{
	ustaw_wlasciwosci();
}
cOkrag::cOkrag(float promien, float _x, float _y) : m_promien(promien)
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
	setGeometria(x, y, -m_promien, -m_promien, m_promien, m_promien);
	setFizyka(9.811E-6F, -90);
	setPredkosc(4e-2F, 60);
}
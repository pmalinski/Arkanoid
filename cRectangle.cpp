#include"cRectangle.h"
#include<GL/freeglut.h>

inline float dtor(float kat);

cRectangle::cRectangle() :m_width(5), m_height(5) //konstruktor domyslny
{
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
cRectangle::cRectangle(float _x, float _y) : m_width(5), m_height(5)
{
	x = _x;
	y = _y;
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
cRectangle::cRectangle(float width, float height, float _x, float _y) : m_width(width), m_height(height)
{
	x = _x;
	y = _y;
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
cRectangle::cRectangle(float width, float height, float _x, float _y, float _alpha, float _r, float _g, float _b) : m_width(width), m_height(height)
{
	x = _x;
	y = _y;
	alpha = _alpha;
	r = _r;
	g = _g;
	b = _b;
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
void cRectangle::rysuj() //metoda rysujaca prostokat
{
	glPushMatrix();

	glTranslated(x, y, 0.0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(alpha, 0.0, 0.0, 1.0);

	glColor3d(r, g, b);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-m_width / 2, m_height / 2, 0);
		glVertex3d(m_width / 2, m_height / 2, 0);
		glVertex3d(m_width / 2, -m_height / 2, 0);
		glVertex3d(-m_width / 2, -m_height / 2, 0);
	}
	glEnd();
	glPopMatrix();
}
void cRectangle::resize(float dwidth, float dheight) //metoda zmieniajaca rozmiar prostokata
{
	if (m_width + dwidth >= 0)
	{
		m_width += dwidth;
	}
	if (m_height + dheight >= 0)
	{
		m_height += dheight;
	}
}
float dtor(float kat) //funkcja zamieniajaca stopnie na radiany
{
	const float pi = 3.14159265358979323F;
	return (kat * pi / 180);
}
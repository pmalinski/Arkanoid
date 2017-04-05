#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include"cFigura.h"

class cRectangle:public cFigura //klasa prostokat
{
	//pola
protected:
	float m_width, m_height; //szerokosc, wysokosc

	//metody
public:
	cRectangle(); //konstruktor domyslny
	cRectangle(float _x, float _y);
	cRectangle(float width, float height, float _x, float _y);
	cRectangle(float width, float height, float _x, float _y, float _alpha, float _r, float _g, float _b);
	virtual void rysuj(); //metoda rysujaca prostokat
	virtual void resize(float dwidth, float dheight); //metoda zmieniajaca rozmiar prostokata
};

#endif
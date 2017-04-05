#ifndef COKRAG_H
#define COKRAG_H

#include"cFigura.h"

class cOkrag :public cFigura
{
protected:
	float m_promien;

public:
	cOkrag();
	cOkrag(float promien);
	cOkrag(float promien, float _x, float _y);
	virtual void rysuj();
	virtual void resize(float dwidth, float dheight = 0); //metoda zmieniajaca rozmiar okregu
};

#endif
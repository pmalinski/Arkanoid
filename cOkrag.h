#ifndef COKRAG_H
#define COKRAG_H

#include"cFigura.h"

class cOkrag :public cFigura
{
protected:
	float m_promien;
	bool przylepiony;
	float odleglosc_na_paletce;

public:
	cOkrag();
	cOkrag(float promien);
	cOkrag(float promien, float _x, float _y);
	virtual void rysuj();
	virtual void resize(float dwidth, float dheight = 0); //metoda zmieniajaca rozmiar okregu
	void ustaw_wlasciwosci();
	bool czy_przylepiony() { return przylepiony; }; //getter informacji o przylepieniu kulki
	void przylep(bool przylepiac) { przylepiony = przylepiac; }; //ustawienie czy pilka ma byc przylepiana do paletki
	float zwroc_promien() { return m_promien; };
	float zwroc_odleglosc_na_paletce() { return odleglosc_na_paletce; };
	void ustaw_odleglosc_na_paletce(float odleglosc) { odleglosc_na_paletce = odleglosc; };
};

#endif
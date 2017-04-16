#ifndef CKLOCEK_H
#define CKLOCEK_H
#include"cRectangle.h"

class cKlocek : public cRectangle
{
protected:
	int liczba_punktow;
	int odpornosc;
	float dr;
	float dg;
	float db;
	int typ_klocka;

public:
	cKlocek();
	cKlocek(float _x, float _y, int _odpornosc);
	cKlocek(float _x, float _y, int _odpornosc, int _typ);
	void Odbicie(float alfa_n);
	int punkty() { return liczba_punktow; }; //getter liczby punktow
	int zwroc_typ() { return typ_klocka; }; //getter typu klocka
	void ustaw_wlasciwosci(float wysokosc, float szerokosc, float _x, float _y, float _r = 0, float _g = 0, float _b = 0, float _dr = 0, float _dg = 0, float _db = 0);
};

#endif
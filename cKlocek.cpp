#include"cKlocek.h"

cKlocek::cKlocek() :odpornosc(5), liczba_punktow(10), typ_klocka(0)
{
	ustaw_wlasciwosci(3, 6, 0, 10, 1, 0, 0, (float)1 / odpornosc);
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
cKlocek::cKlocek(float _x, float _y, int _odpornosc) : odpornosc(_odpornosc), liczba_punktow(_odpornosc * 2), typ_klocka(0)
{
	ustaw_wlasciwosci(3, 6, _x, _y, 1, 0, 0, (float)1 / odpornosc);
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
cKlocek::cKlocek(float _x, float _y, int _odpornosc, int _typ) : odpornosc(_odpornosc), liczba_punktow(_odpornosc * 2), typ_klocka(_typ)
{
	if (_typ == 0) //czerwnoy klocek
	{
		ustaw_wlasciwosci(3, 6, _x, _y, 1, 0, 0, (float)1 / odpornosc, 0, 0);
	}
	else if (_typ == 1) //zielony klocek
	{
		ustaw_wlasciwosci(3, 6, _x, _y, 0, 1, 0, 0, (float)1 / odpornosc, 0);
	}
	else if (_typ == 2) //niebieski klocek
	{
		ustaw_wlasciwosci(3, 6, _x, _y, 0, 0, 1, 0, 0, (float)1 / odpornosc);
	}
	else if (_typ == 3) //zolty klocek
	{
		ustaw_wlasciwosci(3, 6, _x, _y, 1, 1, 0, (float)1 / odpornosc, (float)1 / odpornosc, 0);
	}
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
void cKlocek::Odbicie(float alfa_n)
{
	odpornosc--;
	r -= dr;
	g -= dg;
	b -= db;
	if (odpornosc == 0)
	{
		widoczny = false;
	}
	CFizyka::Odbicie(alfa_n);
}
void cKlocek::ustaw_wlasciwosci(float wysokosc, float szerokosc, float _x, float _y, float _r, float _g, float _b, float _dr, float _dg, float _db)
{
	m_height = wysokosc;
	m_width = szerokosc;
	x = _x;
	y = _y;
	r = _r;
	g = _g;
	b = _b;
	dr = _dr;
	dg = _dg;
	db = _db;
}
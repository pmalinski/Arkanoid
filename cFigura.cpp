#include"cFigura.h"

cFigura::cFigura() : r(1), g(1), b(1), alpha(0)
{}
void cFigura::move(float dx, float dy) //metoda przesuwajaca figure o jakas wartosc
{
	x += dx;
	y += dy;
}
void cFigura::move_to(float _x, float _y) //metoda przesuwajaca figure do jakiegos punktu
{
	x = _x;
	y = _y;
}
void cFigura::rotate(float _alpha)  //metoda obracajaca figure
{
	alpha += _alpha;
}
void cFigura::set_color(float _r, float _g, float _b) //metoda ustawiajaca kolor figury
{
	r = _r;
	g = _g;
	b = _b;
}
void cFigura::change_color(float dr, float dg, float db) //metoda zmieniajaca kolor figury o jakas stala
{
	r += dr;
	g += dg;
	b += db;

	if (r < 0) r = 0;
	if (r > 1) r = 1;
	if (g < 0) g = 0;
	if (g > 1) g = 1;
	if (b < 0) b = 0;
	if (b > 1) b = 1;
}
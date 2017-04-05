#ifndef CFIGURA_H
#define CFIGURA_H
#include"cFizyka.h"

class cFigura :public CFizyka
{
protected:
	float r, g, b; //kolor (RGB)
	float alpha;

public:
	cFigura();
	virtual void rysuj() = 0; //= 0 oznacza, ze metoda jest abstrakcyjna (nie da sie jej okreslic)
	void move(float dx, float dy); //metoda przesuwajaca figure o jakas wartosc
	void move_to(float _x, float _y); //metoda przesuwajaca figure do jakiegos punktu
	void set_color(float _r, float _g, float _b); //metoda ustawiajaca kolor figury
	void change_color(float dr, float dg, float db); //metoda zmieniajaca kolor figury o jakas stala
	void rotate(float _alpha); //metoda obracajaca figure
	virtual void resize(float dwidth, float dheight) = 0; //metoda zmieniajaca rozmiar prostokata
};

#endif
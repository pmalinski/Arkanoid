#ifndef CKLOCEK_H
#define CKLOCEK_H
#include"cRectangle.h"

class cKlocek : public cRectangle
{
protected:
	int liczba_punktow;
	int odpornosc;

public:
	cKlocek();
	cKlocek(float x, float y, int _odpornosc);
	void Odbicie(float alfa_n);
	int punkty() { return liczba_punktow; }; //getter liczby punktow
};

#endif
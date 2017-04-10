#include"cKlocek.h"

cKlocek::cKlocek() :odpornosc(5), liczba_punktow(10)
{
	m_height = 3;
	m_width = 30;
	x = 0;
	y = 10;
	r = 1;
	g = 0;
	b = 0;
	setGeometria(x, y, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
}
cKlocek::cKlocek(float x, float y, int _odpornosc)
{

}
void cKlocek::Odbicie(float alfa_n)
{
	odpornosc--;
	if (odpornosc == 0)
	{
		widoczny = false;
	}
	CFizyka::Odbicie(alfa_n);
}
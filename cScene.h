#ifndef CSCENE_H
#define CSCENE_H
#include"cRectangle.h"
#include"cOkrag.h"

class cScene
{
private:

public:
	void init_scene(int &argc, char* argv);
	void rysuj();
	void aktualizuj();
};

void przylep_ustaw(cRectangle* paletka, cOkrag* kulka); //funkcja zatrzymujaca kulke na paletce
void pauza(int a); //funkcja pauzujaca gre po wygranej
void domyslny_rozmiar_paletki(int a);
void wylacz_przylep(int a);

#endif
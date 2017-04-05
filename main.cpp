#include<iostream>
#include<GL/freeglut.h>
#include"cScene.h"

using namespace std;

extern cScene scena;

int main(int argc, char* argv[])
{
	scena.init_scene(argc, *argv);
}
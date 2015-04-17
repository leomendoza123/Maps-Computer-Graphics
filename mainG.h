#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>


typedef struct Punto{
	double X;
	double Y;
} Punto;

typedef struct ColorCap {
	float r;
	float g;
	float b;
} ColorCap;


typedef struct Linea{
	struct Punto punto1;
	struct Punto punto2;
} Linea;

int TD;

void updateGame();
void cargaBuffer();
void reiniciaPuntos();

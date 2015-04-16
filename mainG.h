#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "plot.h"
#include "bresemham.h"



typedef struct Punto{
	double X;
	double Y;
} Punto;


typedef struct Linea{
	struct Punto punto1;
	struct Punto punto2;
} Linea;


void updateGame();
void cargaBuffer();
void reiniciaPuntos();
struct Linea LiangBarsky (struct Punto punto0src, struct Punto punto1src,
                double edgeLeft, double edgeRight, double edgeBottom, double edgeTop );

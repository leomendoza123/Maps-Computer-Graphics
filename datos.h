#include "qdbmp.h"


typedef struct Capsula{
	double universalPoints[3000][2];
	double framePoints[3000][2];
	double tempFramePoints[3000][2];

	double rotacion;
	double panx;
	double pany;
	double zoom;

	}Capsula;

struct Capsula psanjose;
struct Capsula palajuela;
struct Capsula pheredia;
struct Capsula pcartago;
struct Capsula plimon;
struct Capsula ppuntarenas;
struct Capsula pguanacaste;

double ESCALAX;
double ESCALAY;

struct Capsula cargarArchivo (char* nombreArchivo,int vres, int hres, int xmin, int ymin, int xmax, int ymax);
unsigned char* ReadBMP(char* filename);

void carga();

BMP*	bmp;
BMP* bmpalajuela;
 BMP* bmplimon;
 BMP* bmpguanacaste;
 BMP* bmpsanjose;
 BMP* bmpheredia;
 BMP* bmpcartago ;
BMP*bmppuntarenas;

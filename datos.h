typedef struct Capsula{
	double universalPoints[3000][2];
	double framePoints[3000][2];
	double tempFramePoints[3000][2];
	}Capsula;

struct Capsula psanjose;
struct Capsula palajuela;
struct Capsula pheredia;
struct Capsula pcartago;
struct Capsula plimon;
struct Capsula ppuntarenas;
struct Capsula pguanacaste;

struct Capsula cargarArchivo (char* nombreArchivo,int vres, int hres, int xmin, int ymin, int xmax, int ymax);

void carga();

typedef struct Capsula{
	double universalPoints[3000][2];
	double framePoints[3000][2];
	double tempFramePoints[3000][2];
	}Capsula;
	
struct Capsula cargarArchivo (char* nombreArchivo,int vres, int hres, int xmin, int ymin, int xmax, int ymax);

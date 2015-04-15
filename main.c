#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "datos.h"

int main()
{
//resolucion 
int vres = 800;
int hres = 800;
int xmin = -86;
int ymin = 8;
int xmax = -82;
int ymax = 12;
//Obtencion de puntos desde archivos
//Transformacion de coor universales a framebuffer
struct Capsula psanjose = cargarArchivo ("mapasshp/sanjose.txt",     vres,hres,xmin,ymin,xmax,ymax);
struct Capsula palajuela = cargarArchivo("mapasshp/alajuela.txt",    vres,hres,xmin,ymin,xmax,ymax);
struct Capsula pheredia = cargarArchivo("mapasshp/heredia.txt",      vres,hres,xmin,ymin,xmax,ymax);
struct Capsula pcartago = cargarArchivo("mapasshp/cartago.txt",      vres,hres,xmin,ymin,xmax,ymax);
struct Capsula plimon = cargarArchivo("mapasshp/limon.txt",          vres,hres,xmin,ymin,xmax,ymax);
struct Capsula ppuntarenas = cargarArchivo("mapasshp/puntarenas.txt",vres,hres,xmin,ymin,xmax,ymax);
struct Capsula pguanacaste = cargarArchivo("mapasshp/guanacaste.txt",vres,hres,xmin,ymin,xmax,ymax);

return 1;
} 

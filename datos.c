#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datos.h"

double xToFramePoint(double xp, int hres, int xmax, int xmin){
	double xResult;
	xResult = (double)((xp * hres) - (xmin * hres)) / ( double)(xmax - xmin);
	return xResult;
	}

double yToFramePoint(double yp, int vres, int ymax, int ymin){
	double yResult;
	yResult = (double)( ((yp * vres) - (ymin * vres)) )/ (double)(ymax - ymin);
	return yResult;
	}


struct Capsula cargarArchivo (char* nombreArchivo,int vres, int hres, int xmin, int ymin, int xmax, int ymax){
  FILE *stream;
  struct Capsula cap;
  char *xValue;
  char *yValue;
  char *search = ",";
  int indexPuntos = 0;
  double xValueD;
  double yValueD;

           char *line = NULL;
           size_t len = 0;
           ssize_t read;

           stream = fopen(nombreArchivo, "r");
           if (stream == NULL){
			   printf("no se pudo leer mapa");
			   exit(EXIT_FAILURE);
			   }

           while ((read = getline(&line, &len, stream)) != -1) {
              // printf("Retrieved line of length %zu :\n", read);
              // printf("%s", line);

               xValue = strtok(line, search); // X
               yValue = strtok(NULL, search); //Y
               yValue[strlen(yValue) - 1] = '\0'; //se elimina el enter

                xValueD = atof(xValue);
                yValueD = atof(yValue);
               cap.universalPoints[indexPuntos][0] =  xValueD;
               cap.universalPoints[indexPuntos][1] =  yValueD;
               cap.framePoints[indexPuntos][0] = xToFramePoint(xValueD,hres,xmax,xmin);
               cap.framePoints[indexPuntos][1] = yToFramePoint(yValueD,hres,ymax,ymin);
               indexPuntos = indexPuntos + 1;
           }
           //Delimitador final
           cap.universalPoints[indexPuntos][0] = -7777.77;
           cap.universalPoints[indexPuntos][1] = -7777.77;
           cap.framePoints[indexPuntos][0] = -7777.77;
           cap.framePoints[indexPuntos][1] = -7777.77;

           free(line);
           fclose(stream);
          // exit(EXIT_SUCCESS);
           return cap;
}





void carga()
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
psanjose = cargarArchivo ("mapasshp/sanjose.txt",     vres,hres,xmin,ymin,xmax,ymax);
 palajuela = cargarArchivo("mapasshp/alajuela.txt",    vres,hres,xmin,ymin,xmax,ymax);
pheredia = cargarArchivo("mapasshp/heredia.txt",      vres,hres,xmin,ymin,xmax,ymax);
pcartago = cargarArchivo("mapasshp/cartago.txt",      vres,hres,xmin,ymin,xmax,ymax);
plimon = cargarArchivo("mapasshp/limon.txt",          vres,hres,xmin,ymin,xmax,ymax);
ppuntarenas = cargarArchivo("mapasshp/puntarenas.txt",vres,hres,xmin,ymin,xmax,ymax);
pguanacaste = cargarArchivo("mapasshp/guanacaste.txt",vres,hres,xmin,ymin,xmax,ymax);

}


#include "mainG.h"
#include "datos.h"
#include "bresemham.h"
#include "math.h"
#include <time.h>
#include "plot.h"
#include "bresemham.h"
#include "qdbmp.h"


int random_number(int min_num, int max_num);
ColorCap random_Color(void);
 struct ColorCap randColor1,randColor2, randColor3, randColor4, randColor5, randColor6, randColor7;

Punto OperaPunto (struct Punto puntoEntrada, double Zoom, double PaneoX, double PaneoY, double Rotacion){

	double AncladoX = (puntoEntrada.X -300 );
	double AncladoY= (puntoEntrada.Y -300 );
	double RotacionX = cos(Rotacion)*AncladoX-sin(Rotacion)*AncladoY;
	double RotacionY = sin(Rotacion)*AncladoX+cos(Rotacion)*AncladoY;
	double ZoomX = RotacionX* Zoom;
	double ZoomY = RotacionY* Zoom;
	double PanX = ZoomX + PaneoX * Zoom ;
	double PanY = ZoomY + PaneoY * Zoom ;
	double X = PanX + 300;
	double Y = PanY +300;

	struct Punto PuntoResultado;
	PuntoResultado.X = X;
	PuntoResultado.Y = Y;
	return PuntoResultado;


}


void dibujarFramepoints(struct Capsula framepoints){



    struct Punto punto;
    punto.X = framepoints.framePoints[0][0];
    punto.Y = framepoints.framePoints[0][1];
    struct Punto PUNTO1 = OperaPunto (punto, framepoints.zoom, framepoints.panx, framepoints.pany, framepoints.rotacion);

    int i= 1;
	while(framepoints.framePoints[i][0] != -7777.77) {
	    punto.X = framepoints.framePoints[i][0];
        punto.Y = framepoints.framePoints[i][1];
        struct Punto PUNTO2 =  OperaPunto(punto, framepoints.zoom, framepoints.panx, framepoints.pany, framepoints.rotacion);
        //struct Linea LINEA = LiangBarsky (PUNTO1, PUNTO2, 10, 550, 10, 550);
        algoritmoBresemham ( PUNTO1.X,  PUNTO1.Y,  PUNTO2.X, PUNTO2.Y);
        //printf ("%f, %f", LINEA.punto1.X, LINEA.punto1.Y);
        PUNTO1 = PUNTO2;
        i++;

	}


}
void rellenarFramepoints(struct Capsula framepoints, struct ColorCap color){

    int CantidadPuntos = sizeof(framepoints.framePoints)/sizeof(framepoints.framePoints[0]);
    struct Punto puntos[CantidadPuntos*2];
    struct Punto punto;


    //______________________________
    // Intrepeta puntos como, puntos de salida y de llegada
    //     "Duplica los puntos"
    //______________________________



    punto.X = framepoints.framePoints[0][0];
    punto.Y = framepoints.framePoints[0][1];
    struct Punto PUNTO1 = OperaPunto (punto, framepoints.zoom, framepoints.panx, framepoints.pany, framepoints.rotacion);
    int i= 1;
	while(framepoints.framePoints[i][0] != -7777.77) {
	    punto.X = framepoints.framePoints[i][0];
        punto.Y = framepoints.framePoints[i][1];
        struct Punto PUNTO2 =  OperaPunto(punto, framepoints.zoom, framepoints.panx, framepoints.pany, framepoints.rotacion);
        puntos[i*2] = PUNTO1;
        puntos[i*2+1] = PUNTO2;
        PUNTO1 = PUNTO2;
        i++;
    }
    struct Punto puntoFinal = {-7777.77,-7777.77};
    puntos [i*2] =puntoFinal;

    i = 2;
    int IMAGE_RIGHT = 600;
    int IMAGE_LEFT = 0;
     int nodeX[1000];
     int nodes = 0;
       int swap;
       int pixelY;
       int pixelX;
     //______________________________
    // Ciclo SCANLINE
    //  Recorre cada linea del frame buffer
    //      Calcula los nodos de los bordes de entrada y salida
    //      Ordena los nodos "Bubble"
    //      Hace plot de los puntos entre cada 2 nodos
    //______________________________
    for (pixelY=0; pixelY<600; pixelY++) {
          nodes=0;
          i = 2;

          //Calcula los nodos de los bordes de entrada y salida
          while(puntos[i+1].X != -7777.77) {

            if (puntos[i].Y<(double) pixelY && puntos[i+1].Y>=(double) pixelY
            ||  puntos[i+1].Y<(double) pixelY && puntos[i].Y>=(double) pixelY)
            {
                  nodeX[nodes++]=(int) (puntos[i].X+(pixelY-puntos[i].Y)/(puntos[i+1].Y-puntos[i].Y)
                                 *(puntos[i+1].X-puntos[i].X)); }
            i++;
            }

            // Ordena los nodos "Bubble"
            i=0;
            while (i<nodes-1) {
                    if (nodeX[i]>nodeX[i+1]) {
                      swap=nodeX[i]; nodeX[i]=nodeX[i+1];
                      nodeX[i+1]=swap;
                      if (i)
                        i--; }
                    else {
                      i++; }}

            //      Hace plot de los puntos entre cada 2 nodos
            for (i=0; i<nodes; i+=2) {
                if   (nodeX[i  ]>=IMAGE_RIGHT) break;
                if   (nodeX[i+1]> IMAGE_LEFT ) {
                  if (nodeX[i  ]< IMAGE_LEFT ) nodeX[i  ]=IMAGE_LEFT ;
                  if (nodeX[i+1]> IMAGE_RIGHT) nodeX[i+1]=IMAGE_RIGHT;
                  for (pixelX=nodeX[i]; pixelX<nodeX[i+1]; pixelX++) plot(pixelX,pixelY, color); }}
                  }


    }



void rellenarTexturaFramepoints(struct Capsula framepoints, BMP* bmp){



    int CantidadPuntos = sizeof(framepoints.framePoints)/sizeof(framepoints.framePoints[0]);
    struct Punto puntos[CantidadPuntos*2];
    struct Punto punto;
     struct ColorCap color;


    //______________________________
    // Intrepeta puntos como, puntos de salida y de llegada
    //     "Duplica los puntos"
    //______________________________



    punto.X = framepoints.framePoints[0][0];
    punto.Y = framepoints.framePoints[0][1];
    struct Punto PUNTO1 = OperaPunto (punto, framepoints.zoom, framepoints.panx, framepoints.pany, framepoints.rotacion);
    int i= 1;
	while(framepoints.framePoints[i][0] != -7777.77) {
	    punto.X = framepoints.framePoints[i][0];
        punto.Y = framepoints.framePoints[i][1];
        struct Punto PUNTO2 =  OperaPunto(punto, framepoints.zoom, framepoints.panx, framepoints.pany, framepoints.rotacion);
        puntos[i*2] = PUNTO1;
        puntos[i*2+1] = PUNTO2;
        PUNTO1 = PUNTO2;
        i++;
    }
    struct Punto puntoFinal = {-7777.77,-7777.77};
    puntos [i*2] =puntoFinal;

    i = 2;
    int IMAGE_RIGHT = 600;
    int IMAGE_LEFT = 0;
     int nodeX[1000];
     int nodes = 0;
       int swap;
       int pixelY;
       int pixelX;
     //______________________________
    // Ciclo SCANLINE
    //  Recorre cada linea del frame buffer
    //      Calcula los nodos de los bordes de entrada y salida
    //      Ordena los nodos "Bubble"
    //      Hace plot de los puntos entre cada 2 nodos
    //______________________________
    for (pixelY=0; pixelY<600; pixelY++) {
          nodes=0;
          i = 2;

          //Calcula los nodos de los bordes de entrada y salida
          while(puntos[i+1].X != -7777.77) {

            if (puntos[i].Y<(double) pixelY && puntos[i+1].Y>=(double) pixelY
            ||  puntos[i+1].Y<(double) pixelY && puntos[i].Y>=(double) pixelY)
            {
                  nodeX[nodes++]=(int) (puntos[i].X+(pixelY-puntos[i].Y)/(puntos[i+1].Y-puntos[i].Y)
                                 *(puntos[i+1].X-puntos[i].X)); }
            i++;
            }

            // Ordena los nodos "Bubble"
            i=0;
            while (i<nodes-1) {
                    if (nodeX[i]>nodeX[i+1]) {
                      swap=nodeX[i]; nodeX[i]=nodeX[i+1];
                      nodeX[i+1]=swap;
                      if (i)
                        i--; }
                    else {
                      i++; }}

            //      Hace plot de los puntos entre cada 2 nodos, segun textura
            for (i=0; i<nodes; i+=2) {
                if   (nodeX[i  ]>=IMAGE_RIGHT) break;
                if   (nodeX[i+1]> IMAGE_LEFT ) {
                  if (nodeX[i  ]< IMAGE_LEFT ) nodeX[i  ]=IMAGE_LEFT ;
                  if (nodeX[i+1]> IMAGE_RIGHT) nodeX[i+1]=IMAGE_RIGHT;


                      for (pixelX=nodeX[i]; pixelX<nodeX[i+1]; pixelX++) {
                          UCHAR	r, g, b;
                          BMP_GetPixelRGB( bmp, 600-pixelX, 600-pixelY, &r, &g, &b );
                          color.b = (double)b/(double)255;
                          color.g = (double)g/(double)255;
                          color.r = (double)r/(double)255;
                          //printf ("%d, %d, %d \n", r, g, b);
                          plot(pixelX,pixelY, color);

                      }
                    }
                  }
            }


    }



void cargaBuffer(void){

    if (TD == 1){
        dibujarFramepoints (psanjose);
        dibujarFramepoints (pheredia);
        dibujarFramepoints (palajuela);
        dibujarFramepoints (pcartago);
        dibujarFramepoints (pguanacaste);
        dibujarFramepoints (plimon);
        dibujarFramepoints (ppuntarenas);
    }
    else if (TD == 2){
        rellenarFramepoints(psanjose, randColor1 );
        rellenarFramepoints(pheredia, randColor2 );
        rellenarFramepoints(palajuela, randColor3 );
        rellenarFramepoints(ppuntarenas, randColor4 );
        rellenarFramepoints(plimon, randColor5 );
        rellenarFramepoints(pguanacaste, randColor6 );
        rellenarFramepoints(pcartago, randColor7 );

    }
    else {
        rellenarTexturaFramepoints(psanjose, bmpsanjose);
        rellenarTexturaFramepoints(pguanacaste, bmpguanacaste);
        rellenarTexturaFramepoints(plimon, bmplimon);
            rellenarTexturaFramepoints(pheredia, bmpheredia);
        rellenarTexturaFramepoints(palajuela,  bmpalajuela);
        rellenarTexturaFramepoints(ppuntarenas, bmppuntarenas);
            rellenarTexturaFramepoints(pcartago, bmpcartago);


    }

}




void paneoDePuntos(int x, int y){
    x = x/ psanjose.zoom;
    y = y/ psanjose.zoom;

    printf ("Pan %d, %d", x, y);
    psanjose.panx += x;
    psanjose.pany -= y;
    pheredia.panx += x;
    pheredia.pany -= y;
    ppuntarenas.panx += x;
    ppuntarenas.pany -= y;
    plimon.panx += x;
    plimon.pany -= y;
    pguanacaste.panx += x;
    pguanacaste.pany -= y;
    palajuela.panx += x;
    palajuela.pany -= y;
    pcartago.panx += x;
    pcartago.pany -= y;
}

void zoomDePuntos(double x){

    x *= psanjose.zoom;

    psanjose.zoom += x;
    pheredia.zoom += x;
    ppuntarenas.zoom += x;
    plimon.zoom += x;
    pguanacaste.zoom += x;
    palajuela.zoom += x;
    pcartago.zoom += x;
}

void reiniciaPuntos (void){
    carga();
    randColor1 = random_Color();
    randColor2 = random_Color();
    randColor3 = random_Color();
    randColor4 = random_Color();
    randColor5 = random_Color();
    randColor6 = random_Color();
    randColor7 = random_Color();
    bmpalajuela  =  BMP_ReadFile( "bmp/alajuela.bmp");
    bmplimon  =  BMP_ReadFile( "bmp/limon.bmp");
    bmpguanacaste  =  BMP_ReadFile( "bmp/guanacaste.bmp");
    bmpsanjose  =  BMP_ReadFile( "bmp/SJ.bmp");
    bmpheredia  =  BMP_ReadFile( "bmp/heredia.bmp");
    bmpcartago  =  BMP_ReadFile( "bmp/cartago.bmp");
    bmppuntarenas =  BMP_ReadFile( "bmp/puntarenas.bmp");

}

void rotacionDePuntos(double x){


    psanjose.rotacion += x;
    pheredia.rotacion += x;
    ppuntarenas.rotacion += x;
    plimon.rotacion += x;
    pguanacaste.rotacion += x;
    palajuela.rotacion += x;
    pcartago.rotacion += x;
}



int main(int argc, char* argv[])
{
    TD = 1;

    srand(time(NULL));
    reiniciaPuntos();
	//Inicia GLUT
	glutInit(&argc, argv);
	//Inicia el buffer
	BufferInit();

	init();

}

ColorCap random_Color(void){
    struct ColorCap color;

    color.b = rand() / (RAND_MAX + 1.);
    color.g = rand() / (RAND_MAX + 1.);
    color.r = rand() / (RAND_MAX + 1.);

    return color;



}

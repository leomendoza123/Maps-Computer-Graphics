#include "mainG.h"
#include "datos.h"
#include "bresemham.h"
#include "math.h"



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
        struct Linea LINEA = LiangBarsky (PUNTO1, PUNTO2, 10, 550, 10, 550);
        algoritmoBresemham ( LINEA.punto1.X,  LINEA.punto1.Y,  LINEA.punto2.X, LINEA.punto2.Y);
        printf ("%f, %f", LINEA.punto1.X, LINEA.punto1.Y);
        PUNTO1 = PUNTO2;
        i++;

	}


}

struct Linea LiangBarsky (struct Punto punto0src, struct Punto punto1src,
                double edgeLeft, double edgeRight, double edgeBottom, double edgeTop )
{

    double x1src = punto1src.X;
    double y1src = punto1src.Y;
    double x0src = punto0src.X;
    double y0src = punto0src.Y;

    double t0 = 0.0;    double t1 = 1.0;
    double xdelta = x1src-x0src;
    double ydelta = y1src-y0src;
    double p,q,r;
    int edge;
    for( edge=0; edge<4; edge++) {
        if (edge==0) {  p = -xdelta;    q = -(edgeLeft-x0src);  }
        if (edge==1) {  p = xdelta;     q =  (edgeRight-x0src); }
        if (edge==2) {  p = -ydelta;    q = -(edgeBottom-y0src);}
        if (edge==3) {  p = ydelta;     q =  (edgeTop-y0src);   }
        r = q/p;
        if(p==0 && q<0) return ;

        if(p<0) {
            if(r>t1) return ;
            else if(r>t0) t0=r;
        } else if(p>0) {
            if(r<t0) return ;
            else if(r<t1) t1=r;
        }
    }

    struct Linea lineaResultado;
    struct Punto punto1;
    punto1.X =  x0src + t0*xdelta;
    punto1.Y = y0src + t0*ydelta;
    struct Punto punto2;
    punto2.X = x0src + t1*xdelta;
    punto2.Y = y0src + t1*ydelta;
    lineaResultado.punto1 = punto1;
    lineaResultado.punto2 = punto2;
    return lineaResultado;

}


void cargaBuffer(void){
    dibujarFramepoints (psanjose);
    dibujarFramepoints (pheredia);
    dibujarFramepoints (palajuela);
    dibujarFramepoints (pcartago);
    dibujarFramepoints (pguanacaste);
    dibujarFramepoints (plimon);
    dibujarFramepoints (ppuntarenas);

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

    carga();
	//Inicia GLUT
	glutInit(&argc, argv);
	//Inicia el buffer
	BufferInit();






	init();

}

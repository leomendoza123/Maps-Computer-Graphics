#include "mainG.h"
#include "datos.h"
#include "bresemham.h"


void updateGame()
{
	init ();
	draw_scene();
    glutPostRedisplay();
}


void leerFramePoints(struct Capsula framepoints){


	int i= 1;
	int X1 = framepoints.framePoints[0][0];
	int Y1 = framepoints.framePoints[0][1];
	int X2;
	int Y2;

	while(framepoints.framePoints[i][0] != -7777.77) {
       // printf ("%f , %f", psanjose.framePoints[i][0], psanjose.framePoints[i][1]);
        X2 = framepoints.framePoints[i][0];
        Y2 = framepoints.framePoints[i][1];
        algoritmoBresemham ( X1,  Y1,  X2, Y2);
        X1 = X2;
        Y1 = Y2;
        printf ("%d, %d ", X1, Y1);
        i++;

	}


}

int main(int argc, char* argv[])
{

    carga();
	//Inicia GLUT
	glutInit(&argc, argv);
	//Inicia el buffer
	BufferInit();

    leerFramePoints (psanjose);
    leerFramePoints (pheredia);
    leerFramePoints (palajuela);
    leerFramePoints (pcartago);
    leerFramePoints (pguanacaste);
    leerFramePoints (plimon);
    leerFramePoints (ppuntarenas);





	init();

}

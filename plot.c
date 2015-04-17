/*
 * Instituto Tecnologico de Costa Rica
 * Escuela de Ingenieria en Computacion
 * Computer Graphics
 *
 * Programa: Mesa Example
 * Archivo: mesa_example.c
 */
#include "plot.h"
#include "mainG.h"


//======================================================
// CONSTANTS
//======================================================


//======================================================
// GLOBAL VARIABLES WRITTEN TO BY reshapeCallBack( )
//======================================================
// Window size
int w_height=600;
int w_width=600;
struct ColorCap **buffer;

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY displayCallBack( )
//======================================================
int display_count=0; //keeps count of invocations

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY keyboardCallBack( )
//======================================================
float theta =0.0; // Rotation angle of square
int timer_period_in_ms=100; // time between timer callbacks in milliseconds

//====================================================================
// GLOBAL VARIABLES WRITTEN TO BY motionCallBack( )
//====================================================================
int square_x, square_y; // position of square
int square_dx = 1; // incremental change insquare_x




void plot (int i, int j, struct ColorCap color){
	if (i>=0&&i<w_height && j>=0&&j< w_height ){
		buffer[i][j].r = color.r;
		buffer[i][j].g = color.g ;
		buffer[i][j].b = color.b;
	}
}

void BufferInit (){
	int i, j;
	buffer = (ColorCap **)malloc(w_height * sizeof(ColorCap*));
	for (i = 0; i < w_height; i++)
	{
		buffer[i] = (ColorCap *)malloc(w_width * sizeof(ColorCap));
	}
	for (i = 0; i < w_height; i++)
	{

		for (j = 0; j < w_width; j++){
			buffer[i][j].r = 0;
			buffer[i][j].g = 0;
			buffer[i][j].b = 1;
		}
	}
}

void draw_scene() {

    BufferInit ();
    cargaBuffer ();

    //glClear( GL_COLOR_BUFFER_BIT);

	int i, j;
	for (i = 0; i < w_height; i++)
	{
		for (j = 0; j < w_width; j++)
		{
			glColor3f (buffer[i][j].r,buffer[i][j].g,buffer[i][j].b);
			glBegin(GL_POINTS);
			glVertex2i(i,j);
			glEnd();
		}
	}
	glFlush();
		//Swap double buffers
	glutSwapBuffers();
}



//======================================================
// IDLE CALLBACK ROUTINE
//======================================================
void idleCallBack()
{
	square_x += square_dx; //Increment x-position of square
	if (square_x > w_width || square_x ==0) square_dx *= -1; //Reverse direction if at edges

	glutPostRedisplay();
}

//======================================================
// RESHAPE CALLBACK ROUTINE
//======================================================
void reshapeCallback (int width, int height)
{
	//Update globals containing window size
	w_width=width;
	w_height=height;
}

//======================================================
// MOUSE MOTION CALLBACK ROUTINE
//======================================================
void motionCallBack(int x, int y)
{

}

//======================================================
// MOUSE CALLBACK ROUTINE
//======================================================
int arrastreInicioX = 0;
int arrastreInicioY = 0;
void mouseCallBack(int btn, int state, int x, int y)
{
	//printf("Mouse call back: button=%d, state=%d, x=%d, y=%d\n", btn, state, x, y);
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
       exit(0);
    }
    else if (btn == 0, state == 0){
        arrastreInicioX = x;
        arrastreInicioY = y;
    }
    else if(btn == 0, state == 1){
        paneoDePuntos (x-arrastreInicioX, y-arrastreInicioY);
        glutPostRedisplay();


    }
}

//======================================================
// KEYBOARD CALLBACK ROUTINE
//======================================================

void keyboardCallBack(unsigned char key, int x, int y)
{
	//printf("Keyboard call back: key=%c, x=%d, y=%d, theta=%f\n", key, x, y, theta);
	switch(key)
	{
	case 'w':
		zoomDePuntos(0.1);
	break;
	case 's':
		zoomDePuntos(-0.1);
	break;
    case 'a':
		rotacionDePuntos(-0.1);
	break;
	case 'd':
		rotacionDePuntos(0.1);
	break;
    case 'r':
	reiniciaPuntos();
	break;
    case 'q':
		TD = (TD +1)%3;
    break;
    case 't':
		exit(0);
	break;
    }

	glutPostRedisplay();
}


//======================================================
// DISPLAY CALL BACK ROUTINE
//======================================================


//======================================================
// MAIN PROGRAM
//======================================================
void init ()
{

	// Create and name window
	glutInitWindowPosition(10,10);
	glutInitWindowSize(w_width,w_height);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Example 3.3 - Basic Animation, Keyboard/Mouse and Glut Idle Libraries");

	// Set Projection Mode and Volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w_width , 0.0, w_height , -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	// Set clear color to black and clear window
	glClearColor (1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	// Set up callbacks
	glutMouseFunc (mouseCallBack);
	glutKeyboardFunc(keyboardCallBack);
	glutMotionFunc(motionCallBack);
	glutDisplayFunc(draw_scene);
	glutReshapeFunc(reshapeCallback);

	// Print Application Usage

	// Enter main event loop
	glutMainLoop();
}

/*
 * Instituto Tecnologico de Costa Rica
 * Escuela de Ingenieria en Computacion
 * Computer Graphics
 *
 * Programa: Mesa Example
 * Archivo: mesa_example.c
 */
#include "plot.h"
#include "malloc.h"
#include "main.h"


//======================================================
// CONSTANTS
//======================================================


//======================================================
// GLOBAL VARIABLES WRITTEN TO BY reshapeCallBack( )
//======================================================
// Window size
int w_height=400;
int w_width=400;
COLOR **buffer;

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




void plot (i,j){
	if (i>=0&&i<w_height && j>=0&&j< w_height ){
		buffer[i][j].r = 1;
		buffer[i][j].g = 1;
		buffer[i][j].b = 1;
	}
}

void BufferInit (){
	int i, j;
	buffer = (COLOR **)malloc(w_height * sizeof(COLOR*));
	for (i = 0; i < w_height; i++)
	{
		buffer[i] = (COLOR *)malloc(w_height * sizeof(COLOR));
	}
	for (i = 0; i < w_height; i++)
	{
		for (j = 0; j < w_height; j++){
			buffer[i][j].r = 0;
			buffer[i][j].g = 0;
			buffer[i][j].b = 0;
		}
	}
}

void draw_scene() {
	static int last_x = 0;
	int i, j;
	COLOR color;

	for (i = last_x; i < w_height; i++)
	{
		for (j = 0; j < w_width; j++)
		{
			glColor3f (buffer[i][j].r,buffer[i][j].g,buffer[i][j].b);
			glBegin(GL_POINTS);
			glVertex2i(i,j);
			glEnd();
			last_x = i;
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
	printf("YYYMotion call back: %d, %d)\n", x, y);
	//Set square's location to current mouse position
	 BufferInit ();
	square_x = x;
	square_y = w_height-y; //Invert mouse y (as its measured from top)

	glutPostRedisplay();
}

//======================================================
// MOUSE CALLBACK ROUTINE
//======================================================
void mouseCallBack(int btn, int state, int x, int y)
{
	printf("Mouse call back: button=%d, state=%d, x=%d, y=%d\n", btn, state, x, y);
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)   exit(0);
}

//======================================================
// KEYBOARD CALLBACK ROUTINE
//======================================================
void keyboardCallBack(unsigned char key, int x, int y)
{
	printf("Keyboard call back: key=%c, x=%d, y=%d, theta=%f\n", key, x, y, theta);
	switch(key)
	{
	case 'I':
		glutIdleFunc(idleCallBack);
		printf("Idle function ON\n");
	break;
	case 'i':
		glutIdleFunc(NULL);
		printf("Idle function OFF\n");
	break;
	case 'r':
		theta = theta + 10.0;
	break;
	default:
		printf("Press i (Idle Off), I (Idle ON) or r (Rotate)");
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
	printf("Program Controls:\n");
	printf("Left Mouse Button & Drag - Draws the square at mouse location.\n");
	printf("Right Mouse Button - Exits the program.\n");
	printf("Key \"I\" - Enables idle callbacks.\n");
	printf("Key \"i\" - Disables idle callbacks.\n");
	printf("Key \"r\" - Rotates square.\n");

	// Enter main event loop
	glutMainLoop();
}

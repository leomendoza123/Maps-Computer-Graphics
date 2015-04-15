#include "mainG.h"
#include <unistd.h>




void updateGame()
{
	init ();
	draw_scene();
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{


	//Inicia GLUT
	glutInit(&argc, argv);
	//Inicia el buffer
	BufferInit();

	//DIBUJA<<<<<<<<<<<<


	init();

}

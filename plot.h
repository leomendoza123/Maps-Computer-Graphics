
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "malloc.h"

typedef struct {
	float r;
	float g;
	float b;
} COLOR;

void init ();
void plot ();
void draw ();
void draw_scene();
void BufferInit();

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vectors.h"
#include <stdint.h>
#include "display.h"
//questo ha un totale di 3 punti che sono gli INDICI 
//delle facce per fare ragionamenti e ordinamenti 3d
typedef struct face_t {
	int a;
	int b;
	int c;
	uint32_t color;
}face_t;


//questo e' il vero triangolo una volta proiettati i punti 
//tiene un totale di 6 cifre che sono le coordinate x e y dei 
//tre vertici del triangolo 
typedef struct triangle_t {
	vec2_t  points[3];
	uint32_t color;
	float avg_depth;
} triangle_t;


void	draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif
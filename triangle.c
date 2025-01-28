#include "triangle.h"
//TODO>crea implementazione
void swap(int* a, int* b)
{
	int temp = *a;

	*a = *b;
	*b = temp;
}

void fill_flat_bottom_triangle(int x0,int y0,int x1,int y1,int Mx,int My, uint32_t color) {
	//starting point x0 y 0 

	//calcola la slope tra x0y0 e x1y1 ed x0 Mx
	float inverse_slope_1 = (float)(x1 - x0)/(y1-y0); //inverse slope
	float inverse_slope_2 = (float)(Mx - x0)/(My - y0);

	float x_start = x0;
	float x_end = x0;

	for (int y = y0; y <= My; y++)
	{
		draw_line(x_start, y, x_end, y, color);
		x_start += inverse_slope_1;
		x_end += inverse_slope_2;

	}

}

void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	// Find the two slopes (two triangle legs)
	float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
	float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

	// Start x_start and x_end from the bottom vertex (x2,y2)
	float x_start = x2;
	float x_end = x2;

	// Loop all the scanlines from bottom to top
	for (int y = y2; y >= y0; y--) {
		draw_line(x_start, y, x_end, y, color);
		x_start -= inv_slope_1;
		x_end -= inv_slope_2;
	}
}

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }
    if (y1 > y2) {
        swap(&y1, &y2);
        swap(&x1, &x2);
    }
    if (y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }
    //evita la divisione per zero con queste guards
    if (y1 == y2) {
        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else if (y0 == y1) {
        // Draw flat-top triangle
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else {
        // Calculate the new vertex (Mx,My) using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);

        // Draw flat-top triangle
        fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
    }
}


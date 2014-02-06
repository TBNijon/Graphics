/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
 *
 * Student name .... Max Grim & Tycho Nijon
 * Student email ... max.grim@student.uva.nl, tycho.nijon@student.uva.nl
 * Collegekaart .... 104xxxxx, 10385762
 * Date ............ February 5th 2014
 * 
 * Comments ........ http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm 
 *                    has been a helpful source for this assignment.
 */

#include "SDL.h"   
#include "init.h"
#include "mla.h"

/*
 * Midpoint Line Algorithm
 * This function draws a line on in the input 'screen'.
 *  The line is drawn from point (x0, y0) to point (x1, y1)
 *  in the specified colour.
 *
 */
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
    int octant, x, y, ix, iy;
    double slope = ((y1 - y0) / (double) (x1 - x0));

    /* The increment/decrement values for x and y*/
    ix = (x1 > x0) ? 1 : -1;
    iy = (y1 > y0) ? 1 : -1;

    /* The octant in which the input coordinates lie. */
    octant = get_octant(x0, y0, x1, y1);

    if (octant == 1 || octant == 4 || octant == 5 || octant == 8) {
        
        /* Traverse the x-axis in these octants. */
        for (x = x0; x != x1; x += ix) {
            y = get_coord(slope, x0, y0, x);
            PutPixel(s, x, y, colour);
        }
    } else if (octant == 2 || octant == 3 || octant == 6 || octant == 7) {
        
        /* Traverse the y-axis in these octants. */
        for (y = y0; y != y1; y += iy) {
            x = get_coord((1 / slope), y0, x0, y);
            PutPixel(s, x, y, colour);
        }
    } else {
        printf("An error occurred when using coordinates (%d, %d)", x1, y1);
    }

    return;
}

/* This function returns the new coordinate corresponding to the 
 * input coordinates.
 */
int get_coord(double slope, int a0, int b0, int a) {
    return b0 + (a - a0) * slope;
}

/* This function returns the octant that the input coordinates belong to. */
int get_octant(int x0, int y0, int x1, int y1) {
    int x, y;

    /* These values will be used to determine the octant we are in. */
    x = x1 - x0;
    y = y1 - y0;

    /* We are in octant 1, 4, 5 or 8. */
    if ((abs(x) >= abs(y))) {
        if (x >= 0) {
            return (y >= 0) ? 8 : 1;
        } else if (x <= 0) {
            return (y >= 0) ? 5 : 4;
        }

        /* We are in octant 2, 3, 6 or 7. */
    } else if (abs(x) < abs(y)) {
        if (x >= 0) {
            return (y >= 0) ? 7 : 2;
        } else if (x <= 0) {
            return (y >= 0) ? 6 : 3;
        }
    }

    /* Something went wrong. */
    return -1;
}


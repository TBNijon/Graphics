/* Computer Graphics assignment, Triangle Rasterization
 * Filename ........ trirast.c
 * Description ..... Implements triangle rasterization
 * Created by ...... Paul Melis
 *
 * Student name .... Max Grim & Tycho Nijon
 * Student email ... max.grim@student.uva.nl, tycho.nijon@student.uva.nl
 * Collegekaart .... 10431365, 10385762
 * Date ............ February 7th 2014
 * 
 * Comments ........ The rasterization chapter in Shirley's book has been a 
 *  helpful source for this assignment.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "trirast.h"
#include "types.h"

/*
 * Rasterize a single triangle.
 * The triangle is specified by its corner coordinates
 * (x0,y0), (x1,y1) and (x2,y2).
 * The triangle is drawn in color (r,g,b).
 */
void draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
        byte r, byte g, byte b) {
    int xmin, xmax, ymin, ymax;
    float alpha, beta, gamma;

    /* Get the bounding rectangle of the triangle. */
    xmin = floor(fmin(x0, fmin(x1, x2)));
    xmax = ceil(fmax(x0, fmax(x1, x2)));
    ymin = floor(fmin(y0, fmin(y1, y2)));
    ymax = ceil(fmax(y0, fmax(y1, y2)));

    /* Loop over all pixels inside the bounding rectangle. */
    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            alpha = func(y1, y2, x2, x1, x, y) / func(y1, y2, x2, x1, x0, y0);
            beta = func(y2, y0, x0, x2, x, y) / func(y2, y0, x0, x2, x1, y1);
            gamma = func(y0, y1, x1, x0, x, y) / func(y0, y1, x1, x0, x2, y2);

            /* Color only the correct pixels, taking in account shared edges. */
            if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                if ((alpha > 0 || func(y1, y2, x2, x1, x0, y0) *
                        func(y1, y2, x2, x1, -1, -1) > 0) &&
                        (beta > 0 || func(y2, y0, x0, x2, x1, y1) *
                        func(y2, y0, x0, x2, -1, -1) > 0) &&
                        (gamma > 0 || func(y0, y1, x1, x0, x2, y2) *
                        func(y0, y1, x1, x0, x, y) > 0)
                        ) {
                    PutPixel(x, y, alpha * r, beta * g, gamma * b);
                }
            }
        }
    }


}

/* This function is an optimized version of draw_triangle. */
void draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2, float y2,
        byte r, byte g, byte b) {
    int xmin, xmax, ymin, ymax;
    float alpha, beta, gamma, func_alpha, func_beta, func_gamma;

    xmin = floor(fmin(x0, fmin(x1, x2)));
    xmax = ceil(fmax(x0, fmax(x1, x2)));
    ymin = floor(fmin(y0, fmin(y1, y2)));
    ymax = ceil(fmax(y0, fmax(y1, y2)));

    /* Precompute these values outside of the loop. */
    func_alpha = func(y1, y2, x2, x1, x0, y0);
    func_beta = func(y2, y0, x0, x2, x1, y1);
    func_gamma = func(y0, y1, x1, x0, x2, y2);

    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {

            /* Break out of the loop if any of these variables is < 0*/
            if ((alpha = func(y1, y2, x2, x1, x, y) / func_alpha) < 0) continue;
            if ((beta = func(y2, y0, x0, x2, x, y) / func_beta) < 0) continue;
            if ((gamma = func(y0, y1, x1, x0, x, y) / func_gamma) < 0) continue;

            /* Color only the correct pixels, taking in account shared edges. */
            if ((alpha > 0 || func_alpha * func(y1, y2, x2, x1, -1, -1) > 0)
                    && (beta > 0 || func_beta * func(y2, y0, x0, x2, -1, -1) > 0)
                    && (gamma > 0 || func_gamma * func(y0, y1, x1, x0, x, y) > 0)
                    ) {
                PutPixel(x, y, alpha * r, beta * g, gamma * b);
            }

        }

    }

}

/* This function returns a value that is used to determine the value of 
 *   alpha, beta or gamma.
 */
float func(float a0, float a1, float b0, float b1, float x, float y) {
    return ((a0 - a1) * x) + ((b0 - b1) * y) + (b1 * a1) - (b0 * a0);
}



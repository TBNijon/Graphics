/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
 *
 * Student name .... Max Grim & Tycho Nijon
 * Student email ... max.grim@student.uva.nl & tychonijon@gmail.com
 * Collegekaart .... 10431365 & 10385762
 * Date ............ 20-02-2013
 * Comments ........ None
 */

#include <math.h>
#include "bezier.h"
#include <stdio.h>

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */

void evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float u) {
    if(num_points == 2) {
        *x = (1 - u) * p[0].x + u * p[1].x;
        *y = (1 - u) * p[0].y + u * p[1].y;
    } else if(num_points == 3) {
        *x = pow(1 - u, 2) * p[0].x + ((2 * (1 - u)) * u * p[1].x) + (pow(u, 2) * p[2].x);
        *y = pow(1 - u, 2) * p[0].y + ((2 * (1 - u)) * u * p[1].y) + (pow(u, 2) * p[2].y);
    } else if(num_points == 4) {
        *x = pow(1 - u, 3) * p[0].x + 3 * (pow(1 - u, 2) * u * p[1].x) + 3 * ((1 - u) * pow(u, 2) * p[2].x) + pow(u, 3) * p[3].x;
        *y = pow(1 - u, 3) * p[0].y + 3 * (pow(1 - u, 2) * u * p[1].y) + 3 * ((1 - u) * pow(u, 2) * p[2].y) + pow(u, 3) * p[3].y;
    }
}

/* Draw a Bezier curve defined by the control points in p[], which
 * will contain 'num_points' points.
 *
 * Draw the line segments you compute directly on the screen
 * as a single GL_LINE_STRIP. This is as simple as using
 *
 *      glBegin(GL_LINE_STRIP);
 *      glVertex2f(..., ...);
 *      ...
 *      glEnd();
 *
 * DO NOT SET ANY COLOR!
 *
 * The 'num_segments' parameter determines the "discretization" of the Bezier
 * curve and is the number of straight line segments that should be used
 * to approximate the curve.
 *
 * Call evaluate_bezier_curve() to compute the necessary points on
 * the curve.
 */

void draw_bezier_curve(int num_segments, control_point p[], int num_points) {
    float x1, y1, x2, y2;

    for(int i = 0; i < num_segments; i++) {
        float u = i / (float) num_segments;
        float u2 = (i + 1) / (float) num_segments;

        evaluate_bezier_curve(&x1, &y1, p, num_points, u);
        evaluate_bezier_curve(&x2, &y2, p, num_points, u2);

        glBegin(GL_LINE_STRIP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
   */

int intersect_cubic_bezier_curve(float *y, control_point p[], float x) {
    return 0;
}


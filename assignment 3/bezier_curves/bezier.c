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
 *
 * Sources:
 *  http://devmag.org.za/2011/04/05/bzier-curves-a-tutorial/
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
    int a;
    int degree = num_points - 1;

    *x = 0;
    *y = 0;

    for(int i = 0; i <= degree; i++) {
        if(i > 0 && i < degree) {
            a = degree;
        } else {
            a = 1;
        }

        *x += pow(1 - u, degree - i) * p[i].x * pow(u, i) * a;
        *y += pow(1 - u, degree - i) * p[i].y * pow(u, i) * a;
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


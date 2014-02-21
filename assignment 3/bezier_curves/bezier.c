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

#include <stdlib.h>
#include <math.h>
#include "bezier.h"
#include <stdio.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

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

void bezierCoeffs(float *z, float p0, float p1, float p2, float p3) {
    z[0] = -p0 + 3*p1 + -3*p2 + p3; 
    z[1] = 3 * p0 - 6 * p1 + 3 * p2;
    z[2] = -3 * p0 + 3 * p1;
    z[3] = p0;
}

int sgn(float x) {
    return (x < 0.0) ? -1 : 1;
}

void cubicRoots(float *r, float *p, float *t) {
    float a = p[0];
    float b = p[1];
    float c = p[2];
    float d = p[3];

    float A = b / a;
    float B = c / a;
    float C = d / a;

    float Q, R, D, Im;
    int S, T;

    Q = (3 * B - pow(A, 2)) / 9;
    R = (9 * A * B - 27 * C - 2 * pow(A, 3)) / 54;
    D = pow(Q, 3) + pow(R, 2);

    if(D >= 0) {
        S = sgn(R + sqrt(D)) * pow(abs(R + sqrt(D)), (1/3));
        T = sgn(R - sqrt(D)) * pow(abs(R - sqrt(D)), (1/3));

        t[0] = -A / 3 + (S + T);
        t[1] = -A / 3 - (S + T) / 2;
        t[2] = -A / 3 - (S + T) / 2;

        Im = abs(sqrt(3) * (S - T) / 2);

        if(Im != 0) {
            t[1] = -1;
            t[2] = -1;
        }
    } else {
        float th = acos(R/sqrt(-pow(Q, 3)));

        t[0] = 2 * sqrt(-Q) * cos(th / 3) - A / 3;
        t[1] = 2 * sqrt(-Q) * cos((th + 2 * M_PI) / 3) - A/3;
        t[2] = 2 * sqrt(-Q) * cos((th + 4 * M_PI) / 3) - A/3;
        Im = 0.0;
    }

    for(int i = 0; i < 3; i++) {
        if(t[i] < 0 || t[i] > 1.0) t[i] = -1;
    }
}

void computeIntersections(float px[], float py[], float lx[], float ly[]) {
    float a = ly[1]-ly[0];      //A=y2-y1
    float b = lx[0]-lx[1];      //B=x1-x2
    float c = lx[0]*(ly[0]-ly[1]) + ly[0]*(lx[1]-lx[0]);  //C=x1*(y1-y2)+y1*(x2-x1)

    float bx[4], by[4];
    bezierCoeffs(bx, px[0],px[1],px[2],px[3]);
    bezierCoeffs(by, py[0],py[1],py[2],py[3]);

    float p[4];
    p[0] = a * bx[0] + b * by[0];
    p[1] = a * bx[1] + b * by[1];     /*t^2*/
    p[2] = a * bx[2] + b * by[2];     /*t*/
    p[3] = a * bx[3] + b * by[3] + c; /*1*/

    float r[3], t[3];
    cubicRoots(r, p, t);

    for(int i = 0; i < 3; i++) {
        float x[2], s;

        x[0] = bx[0] * r[i] * r[i] * r[i] + bx[1] * r[i] * r[i] + bx[2] * r[i] + bx[3];
        x[1] = by[0] * r[i] * r[i] * r[i] + by[1] * r[i] * r[i] + by[2] * r[i] + by[3];

        if((lx[1] - lx[0]) != 0) {
            s = (x[0] - lx[0]) / (lx[1] - lx[0]);
        } else {
            s = (x[1] - ly[0]) / (ly[1] - ly[0]);
        }

        if(r[i] < 0 || r[i] > 1.0 || s < 0 || s > 1.0) {
            x[0] = -100;
            x[1] = -100;
        }

        printf("%f, %f\n", x[0], x[1]);
    }
}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
   */

int intersect_cubic_bezier_curve(float *y, control_point p[], float x) {
    float temp = 0.5;
    float k = 0.5;
    float tmpX = 0.0, tmpY = 0.0;
    while (1) {
        if (k < 0.0001)
            return 0;

        evaluate_bezier_curve(&tmpX, &tmpY, p, 4, temp);
        if (tmpX >= (x - 1E-3) && tmpX <= (x + 1E-3)) {
            *y = tmpY;
            return 1;
        }
        k *= 0.5;
        if (tmpX < x)
            temp += k;
        else
            temp -= k;
    }
    return 0;
}

/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm 
 *
 * Student name .... Max Grim & Tycho Nijon
 * Student email ... max.grim@student.uva.nl, tycho.nijon@student.uva.nl
 * Collegekaart .... 10431365, 10385762
 * Date ............ February 11th 2014
 * Comments ........ 
 *
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>
#include "lookat.h"
#include <stdio.h>


/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

/* This function is a custom implementation of the gluLookAt function. */
void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
        GLdouble centerX, GLdouble centerY, GLdouble centerZ,
        GLdouble upX, GLdouble upY, GLdouble upZ) {
    GLfloat cx[3], cy[3], cz[3], up[3];
    int cx_size, cy_size, cz_size;

    /* Translate across -VRP. */
    //glTranslatef(-5.0, -5.0, -10.0);

    /* Set up vector. */
    up[0] = upX;
    up[1] = upY;
    up[2] = upZ;

    /* Set cz vector and normalize it. */
    cz[0] = centerX - eyeX;
    cz[1] = centerY - eyeY;
    cz[2] = centerZ - eyeZ;
    cz_size = sizeof (cz) / sizeof (GLfloat);
    normalizeVector(cz, cz_size);

    /* Set cx vector orthogonal to cz and up and normalize it.*/
    set3DCrossProduct(cz, up, cx);
    cx_size = sizeof (cx) / sizeof (GLfloat);
    normalizeVector(cx, cx_size);

    /* Set cy vector orthogonal to cx and cz and normalize it. */
    set3DCrossProduct(cx, cz, cy);
    cy_size = sizeof (cy) / sizeof (GLfloat);
    normalizeVector(cy, cy_size);

    /* Build the matrix. */
    GLfloat c_matrix[16] = {
        cx[0], cy[0], -1 * cz[0], 0.0,
        cx[1], cy[1], -1 * cz[1], 0.0,
        cx[2], cy[2], -1 * cz[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(c_matrix);

}

/* This function returns the dot product of two matrices. */
GLfloat getDotProduct(GLfloat *a, GLfloat *b, int a_size, int b_size) {
    float result = 0;

    if (a_size != b_size) {
        printf("Can not compute the dot product of two matrices that do not "
                "have the same dimensions.");
        exit(0);
    }
    for (int i = 0; i < a_size; i++) {
        result += a[i] * b[i];
    }

    return result;
}

/* This function normalizes an input matrix. */
void normalizeVector(GLfloat *a, int a_size) {
    float divide_value = sqrt(getDotProduct(a, a, a_size, a_size));

    for (int i = 0; i < a_size; i++) {
        a[i] /= divide_value;
    }
}

/* This function fills the z vector with the cross product of vectors a and b. */
void set3DCrossProduct(GLfloat *a, GLfloat *b, GLfloat *z) {
    z[0] = (a[1] * b[2]) - (a[2] * b[1]);
    z[1] = (a[2] * b[0]) - (a[0] * b[2]);
    z[2] = (a[0] * b[1]) - (a[1] * b[0]);
}


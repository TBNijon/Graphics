/* Computer Graphics, Assignment, Translations, Rotations and Scaling
 *
 * Filename ........ transformations.c
 * Description ..... Contains the re-programmed translation, rotation and scaling functions
 * Student name .... Max Grim & Tycho Nijon
 * Student email ... max.grim@student.uva.nl, tycho.nijon@student.uva.nl
 * Collegekaart .... 10431365, 10385762
 * Date ............ February 9th 2014
 * Comments ........ 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include "transformations.h"

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

/* This function scales a 3d object. */
void myScalef(GLfloat x, GLfloat y, GLfloat z) {
    GLfloat M[16] = {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(M);
}

/* This function translates a 3d object. */
void myTranslatef(GLfloat x, GLfloat y, GLfloat z) {
    GLfloat M[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0
    };

    glMultMatrixf(M);
}

/* This function rotates a 3d object. */
void myRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat u[3], v[3], w[3], t[3];
    int w_size, u_size;

    /* 1: Create the orthonormal basis. */
    
    /* Set the w vector and normalize it. */
    w[0] = x;
    w[1] = y;
    w[2] = z;

    w_size = sizeof (w) / sizeof (GLfloat);
    normalizeVector(w, w_size);

    /* Set the t vector. */
    t[0] = w[0];
    t[1] = w[1];
    t[2] = 1;

    /* Set u vector orthogonal to t and w and normalize it. */
    set3DCrossProduct(t, w, u);
    u_size = sizeof (u) / sizeof (GLfloat);
    normalizeVector(u, u_size);

    /* Set the v vector orthogonal to w and u. */
    set3DCrossProduct(w, u, v);

    /* 2: Specify the three matrices used for the rotation. */

    /* Convert the angle variable to radians. */
    angle = (angle * M_PI) / 180.0;

    /* Build the matrices used for the rotation. */
    GLfloat A[16] = {
        u[0], u[1], u[2], 0.0,
        v[0], v[1], v[2], 0.0,
        w[0], w[1], w[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    GLfloat B[16] = {
        cos(angle), sin(angle), 0.0, 0.0,
        -1 * sin(angle), cos(angle), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    GLfloat C[16] = {
        u[0], v[0], w[0], 0.0,
        u[1], v[1], w[1], 0.0,
        u[2], v[2], w[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    /* Perform the actual rotation. */
    glMultMatrixf(A);
    glMultMatrixf(B);
    glMultMatrixf(C);
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


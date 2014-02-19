/* Computer Graphics, Assignment 5, Orthogonal projection
 *
 * Filename ........ ortho.c
 * Description ..... Contains the re-programmed orthogonal projection matrix
 * Date ............ 01.09.2006
 * Created by ...... Jurgen Sturm 
 *
 * Student name ....
 * Student email ... 
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>


#define sqr(x) ((x)*(x))

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void myOrtho(GLdouble l, GLdouble r,
        GLdouble b, GLdouble t,
        GLdouble n, GLdouble f) {
    
    /* Added these variables to make the matrix readable. */
    GLdouble right_left, top_bottom, near_far;
    right_left = (r + l) / (r - l);
    top_bottom = (t + b) / (t - b);
    near_far = (n + f) / (n - f);
    
    /* Matrix 7.3 on page 145 of the Shirley book used as a guideline. */
    GLfloat M[16] = {
        (2 / (r - l)), 0.0, 0.0, 0.0,
        0.0, (2 / (t - b)), 0.0, 0.0,
        0.0, 0.0, (2 / (n - f)), 0.0,
        -right_left, -top_bottom, -near_far, 1.0
    };

    glMultMatrixf(M);

}

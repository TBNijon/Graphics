/* Computer Graphics, Assignment, Translations, Rotations and Scaling
 *
 * Filename ........ transformations.h
 * Description ..... Contains the re-programmed translation, rotation and scaling functions
 *
 */

#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


void myScalef(GLfloat x, GLfloat y, GLfloat z);
void myTranslatef(GLfloat x, GLfloat y, GLfloat z);
void myRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GLfloat getDotProduct(GLfloat *a, GLfloat *b, int a_size, int b_size);
void normalizeMatrix(GLfloat *a, int a_size);
void set3DCrossProduct(GLfloat *a, GLfloat *b, GLfloat *z);


#endif

/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.h
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm 
 */


#ifndef IBS_LOOKAT_H
#define IBS_LOOKAT_H


void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
        GLdouble centerX, GLdouble centerY, GLdouble centerZ,
        GLdouble upX, GLdouble upY, GLdouble upZ);

GLfloat getDotProduct(GLfloat *a, GLfloat *b, int a_size, int b_size);
void normalizeVector(GLfloat *a, int a_size);
void set3DCrossProduct(GLfloat *a, GLfloat *b, GLfloat *z);


#endif /* IBS_LOOKAT_H */

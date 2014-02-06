/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.h
 * Description ..... Header file for mla.c
 * Created by ...... Jurgen Sturm 
 *
 */

#ifndef JS_MLA_H
#define JS_MLA_H

void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour);
int get_octant(int x0, int y0, int x1, int y1);
int get_coord(double slope, int a0, int b0, int a);
#endif /* JS_MLA_H */

/**
 * Rectangle class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "BasicShape.h"

/**
 * Rectangle class extends Basic shape.
 */
class Rectangle : public BasicShape
{
    private:
        long width;
        long length;
    public:
        /**
         * Initializes width and length of rectangle and calculates the area.
         * @param length The length of the rectangle.
         * @param width The width of the rectangle.
         */
        Rectangle(long length, long width);

        // getter functions
        long getWidth() const {return width;}
        long getLength() const {return length;}

        /**
         * Calculates the area of the rectangle and stores it in the inherited
         * area member.
         */
        void calcArea();
};

#endif//RECTANGLE_H

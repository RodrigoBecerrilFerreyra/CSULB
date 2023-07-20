/**
 * Circle class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "BasicShape.h"

/**
 * The Circle class extends the BasicShape class.
 */
class Circle : public BasicShape
{
    private:
        long centerX;
        long centerY;
        double radius;
    public:
        /**
         * Initializes the object's private members and calculates the area.
         * @param centerX The x-coordinate of the center of the circle.
         * @param centerY The y-coordinate of the center of the circle.
         * @param radius The radius of the circle.
         */
        Circle(long centerX, long centerY, double radius);

        // center getter methods
        long getCenterX() const {return centerX;}
        long getCenterY() const {return centerY;}
        
        /**
         * Calculates the area of the circle and stores it in the inherited
         * area member.
         */
        void calcArea();
};

#endif // CIRCLE_H

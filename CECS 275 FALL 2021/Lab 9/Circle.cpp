/**
 * Circle class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include "Circle.h"
#define PI 3.14159

Circle::Circle(long centerX, long centerY, double radius)
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->radius = radius;
    calcArea();
}

void Circle::calcArea()
{
    setArea(PI * radius * radius);
}

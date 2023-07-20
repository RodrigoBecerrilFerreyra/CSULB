/**
 * Rectangle implementation header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include "Rectangle.h"

Rectangle::Rectangle(long length, long width)
{
    this->length = length;
    this->width = width;
    calcArea();
}

void Rectangle::calcArea()
{
    setArea(length * width);
}

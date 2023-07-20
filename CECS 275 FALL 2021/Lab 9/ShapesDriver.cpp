/**
 * This program tests both Rectangle and Circle classes.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include "Circle.h"
#include "Rectangle.h"

int main()
{
    std::cout << "Testing Circle class...\n";
    // create two Circle objects
    Circle circle1(0.0, 0.0, 5.0), circle2(1.0, 1.0, 10.0);

    // get the center coordinates of both circles
    std::cout << "The center of circle1 is located at ("
      << circle1.getCenterX() << ", " << circle1.getCenterY()
      << ").\n";
    std::cout << "The center of circle2 is located at ("
      << circle2.getCenterX() << ", " << circle2.getCenterY()
      << ").\n";
    
    // get the area of both circles
    std::cout << "The area of circle1 is " << circle1.getArea()
      << " square units.\n";
    std::cout << "The area of circle2 is " << circle2.getArea()
      << " square units.\n";

    std::cout << "Circle testing done.\n\nTesting Rectangle class...\n";

    // define two rectangles
    Rectangle rect1(9, 3), rect2(10, 11);

    // test length/width getter functions
    std::cout << "Length of rect1: " << rect1.getLength() << " units.\n";
    std::cout << "Width of rect1: " << rect1.getWidth() << " units.\n";
    std::cout << "Length of rect2: " << rect2.getLength() << " units.\n";
    std::cout << "Width of rect2: " << rect2.getWidth() << " units.\n";

    // test area
    std::cout << "Area of rect1: " << rect1.getArea() << " square units.\n";
    std::cout << "Area of rect2: " << rect2.getArea() << " square units.\n";

    return 0;
}

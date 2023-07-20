/**
 * BasicShape class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef BASICSHAPE_H
#define BASICSHAPE_H

/**
 * The BasicShape class provides an abstract base class for other types of
 * shapes. Note that this class cannot be instantiated due to the pure
 * virtual function included in this class.
 */
class BasicShape
{
    private:
        double area;
    public:
        /**
         * Getter function.
         * @return The area of the shape.
         */
        double getArea() const {return area;}

        /**
         * Setter function.
         */
        void setArea(double area) {this->area = area;}

        /**
         * Pure virtual function that calculates the area of a shape and stores
         * it in the area member.
         */
        virtual void calcArea() = 0;
};

#endif // BASICSHAPE_H

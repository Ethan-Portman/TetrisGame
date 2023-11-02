#pragma once
#include <iostream>
class Point {
    friend class TestSuite;

private:
    int x{};  // X-Coordinate of the Point
    int y{};  // Y-Coordinate of the Point
public:
    // Default Constructor
    Point() : x(0), y(0) {};

    // Constructor with Coordinates
    Point(int x, int y) : x(x), y(y) {};


    // Get the X-coordinate of the Point
    int getX() const { return x; }

    // Get the Y-coordinate of the Point
    int getY() const { return y; }


    // Set the X-coordinate of the point
    void setX(int x) { this->x = x; }

    // Set the Y-coordinate of the Point
    void setY(int y) { this->y = y; }

    // Set both the X & Y Coordinates of the Point
    void setXY(int x, int y) { this->x = x; this->y = y; }


    // Multiply the Y-coordinate by a factor
    void multiplyX(int factor) { x *= factor; }

    // Multiple the X-coordinate by a factor
    void multiplyY(int factor) { y *= factor; }

    // Swap the X & Y coordinates of the Point
    void swapXY();

    // Get the String Representation of the Point
    std::string toString() const;
};
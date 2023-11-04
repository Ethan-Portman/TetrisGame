#pragma once
#include <iostream>
#include <sstream>

/*
The Point Class Represents a 2D coordinate on a grid (2D-Array) and provides 
various operations for manipulation
*/
class Point {
    friend class TestSuite;

private:
    int x{};  
    int y{};  
public:
    // Constructor with x and y input
    Point(int x, int y) : x(x), y(y) {};

    // Default Constructor
    Point() : Point(0,0) {};

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
    void swapXY() {
        int tempVal{ x };
        x = y;
        y = tempVal;
    }

    // Print the point in '[x,y]' format
    std::string toString() const {
        std::stringstream toStr;
        toStr << "[" << x << "," << y << "]" << "\n";
        return toStr.str();
    }
};
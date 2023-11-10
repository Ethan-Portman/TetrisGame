#pragma once
#include <vector>
#include "Point.h"
#include <algorithm>

// -------------- COLORS AND SHAPES -------------- //

// Available Colors for each Tetromino
enum class TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE, COUNT };

// Available Shapes for each Tetromino
enum class TetShape { S, Z, L, J, O, I, T, COUNT };  


// --------------- TETROMINO CLASS --------------- //

// Tetromino class represents a Tetris game piece with color, shape, and block locations
class Tetromino {
	friend class TestSuite;

private:
	TetColor color;
	TetShape shape;
	static std::vector<TetShape> randomShapes;

protected:
	std::vector<Point> blockLocs{}; // Points (X,Y Coordinates) of Tetromino.

public:
	// Tetromino Constructor defaults to a Red J.
	Tetromino() 
		: color(TetColor::RED), shape(TetShape::S), blockLocs{ 
			Point(0,1), Point(0,0), Point(0,-1), Point(-1,-1) }
	{}

	// Fill vector of random shapes (two of each) to pull from
	static void fillRandomShapes();

	// Get a random TetShape from the random shapes vector, if empty refill it. 
	static TetShape getRandomShape();

	// Get a random TetColor
	static TetColor getRandomColor();

	// Get the color of the Tetromino.
	TetColor getColor() const { return color; }

	// Set the color of the Tetromino.
	void setColor(const TetColor color) { this->color = color; }

	// Get the shape of the Tetromino.
	TetShape getShape() const { return shape; }

	// Set the shape of the Tetromino.
	void setShape(TetShape shape);

	// Rotate the Tetromino 90 degrees clockwise.
	void rotateClockwise();

	// Print the Tetromino to the console.
	void printToConsole() const;
};

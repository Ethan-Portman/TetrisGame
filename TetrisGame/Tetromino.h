#pragma once
#include <vector>
#include "Point.h"
#include <algorithm>

enum class TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE };  // Available Colors
enum class TetShape { S, Z, L, J, O, I, T };  // Available Shapes

// Tetris game piece with color, shape, and block locations
class Tetromino {
	friend class TestSuite; // Allow TestSuite to access private members.

private:
	TetColor color{};
	TetShape shape{};
	std::vector<Point> blockLocs{};

public:
	// Tetromino Constructor defaults to a Red S.
	Tetromino() {
		color = TetColor::RED;
		shape = TetShape::S;
		blockLocs = { Point(-1,0), Point(0,0), Point(0,1), Point(1,1) };
	}

	// Fetch the color of the Tetromino.
	TetColor getColor() const { return color; }

	// Fetch the shape of the Tetromino.
	TetShape getShape() const { return shape; }

	// Set the shape of the Tetromino.
	void setShape(TetShape shape);

	// Rotate the Tetromino 90 degrees clockwise.
	void rotateClockwise();

	// Print the Tetromino to the console.
	void printToConsole() const;
};
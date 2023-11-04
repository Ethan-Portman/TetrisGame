#pragma once
#include "Tetromino.h"
#include <vector>

/*
The GridTetromino class extends the base Tetromino class, representing a Tetromino
but with an additional grid location. This class is used in the context of a game grid.
*/
class GridTetromino : public Tetromino {

private:
	Point gridLoc;  // The grid location of the Tetromino.

public:
	// Default Constructor, initializes Tetromino to its default state and grid location to (0,0).
	GridTetromino() : 
		Tetromino(), gridLoc(0,0) 
	{}

	// Get the grid location of the Tetromino. 
	Point getGridLoc() const { return gridLoc; }

	// Set the grid location of the Tetromino using individual x and y coordinates. 
	void setGridLoc(int x, int y) { gridLoc.setXY(x, y); }

	// Set the grid location of the Tetromino using a Point object. 
	void setGridLoc(const Point& p) { gridLoc.setXY(p.getX(), p.getY()); }

	// Move the Tetromino within the grid by the specified x and y offsets.
	// @param xOffset: The offset to move the Tetromino horizontally on the grid.
	// @param yOffset: The offset to move the Tetromino Vertically on the grid. 
	void move(int xOffset, int yOffset);

	// Get the block locations of the Tetromino mapped to the grid. 
	// @return: A vector of Point objects representing the block locations.
	std::vector<Point> getBlockLocsMappedToGrid() const;
};

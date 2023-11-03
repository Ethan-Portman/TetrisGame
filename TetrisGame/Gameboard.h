#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <cassert>
#include <iomanip> 
#include "Point.h"

class Gameboard {
	friend int main();
public:
	static const int MAX_X = 10;		// gameboard x dimension
	static const int MAX_Y = 19;		// gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// contents of an empty block

private:
	int grid[MAX_Y][MAX_X];  // [0][0] = Top Left; [MAX_Y-1][MAX_X-1] = bot right;
	const Point spawnLoc{ MAX_X / 2, 0 };  // Offset to span new tetromino at.

public:
	// Constructor - empty() the grid
	Gameboard() { empty(); };

	// Fill the board with EMPTY_BLOCK 
	void empty();

	// Print the grid contents to the console
	void printToConsole() const;

	// Get the content at a given point on the board
	int getContent(const Point& p) const;

	// get the content at a given XY location on the board
	int getContent(int x, int y) const;

	// set the content at a given point (ignore invalid points) on the board
	void setContent(const Point& p, int content);

	// set the content at an x,y position (ignore invalid points) on the board	
	void setContent(int x, int y, int content);

	// set the content for a set of points (ignore invalid points) on the board
	void setContent(const std::vector<Point>& locs, int content);

	// Determine if (valid) all points passed in are empty
	bool areAllLocsEmpty(const std::vector<Point>& locs) const;

	// Remove all completed rows from the board
	int removeCompletedRows();

	// A getter for the spawn location
	Point getSpawnLoc() { return spawnLoc; };

private:

	// Determine if a given Point is a valid grid location
	bool isValidPoint(const Point& p) const;

	// Determine if a given XY is a valid grid location
	bool isValidPoint(int x, int y) const;

	// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
	bool isRowCompleted(int rowIdx) const;

	// fill a given grid row with specified content
	void fillRow(int rowIdx, int content);

	// Scan the board for completed rows and return a vector of completed row indices.
	std::vector<int> getCompletedRowIndices() const;

	// copy a source row's contents into a target row.
	void copyRowIntoRow(int srcRowIdx, int dstRowIdx);

	// Removes a Row by copying the content from above to the row.
	// This happend all the way down to the first row at which point first row is filled with empty
	void removeRow(int rowIdx);

	// Removes the specified rown from the board
	void removeRows(std::vector<int> rows);
};

#endif 

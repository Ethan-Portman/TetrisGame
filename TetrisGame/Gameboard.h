#pragma once
#include <vector>
#include <cassert>
#include <iomanip> 
#include "Point.h"

/*
 * The Gameboard class represents the game grid used in Tetris.
 * It provides methods to interact with and manipulate the game grid, including filling,
 * printing, getting and setting content, removing completed rows, and more.
 */
class Gameboard {
	friend int main();  // Allow main() to access private members.
public:
	static const int MAX_X = 10;		// Gameboard x dimension
	static const int MAX_Y = 19;		// Gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// Contents of an empty block

private:
	int grid[MAX_Y][MAX_X];					// Grid to store block contents
	const Point spawnLoc{ MAX_X / 2, 0 };   // Offset to span new tetromino at.

public:
	// Constructor for Gameboard. Initalizes the grid by emptying it.
	Gameboard() { empty(); };

	// Fill the gameboard with EMPTY_BLOCK .
	void empty();

	// Print the grid contents to the console
	void printToConsole() const;

	// Get the content at a given point on the board
	// @param point: The Point object representing the location.
	// @return: The content (representing a color) at the specified point.
	int getContent(const Point& point) const;

	// Get the content at a given XY location on the board
	// @param x: The x-coordinate.
	// @param y: The y-coordinate.
	// @return: The content (representing a color) at the specified point. 
	int getContent(int x, int y) const;

	// Sets the content at a given point (ignore invalid points) on the board.
	// @param point: The Point object representing the location.
	// @param content: The content (representing a color) to set at the specified point.
	void setContent(const Point& point, int content);

	// Set the content at a given x,y position (ignore invalid points) on the board.
	// @param x: The x-coordinate.
	// @parm y: The y-coordinate.
	// @param content: The content (representing a color) to set at the specified location.
	void setContent(int x, int y, int content);

	// Set the content for a set of points (ignore invalid points) on the board.
	// @param locs: A vector of Point objects representing locations on the board.
	// @param content: The content (representing a color) to set at the specified locations. 
	void setContent(const std::vector<Point>& locs, int content);

	// Determine if all points in a set of locations are empty. Ignores Invalid Points. 
	// @param locs: A vector of Point objects representing locations to check.
	// @return: True if all locations are empty, false otherwise. 
	bool areAllLocsEmpty(const std::vector<Point>& locs) const;

	// Remove all completed rows from the board and return the number of removed rows.
	// @return: The number of removed rows. 
	int removeCompletedRows();

	// Get the spawn location
	// @return: The spawn location as a Point. 
	Point getSpawnLoc() { return spawnLoc; };

private:

	// Determine if a given Point is a valid grid location.
	// @param point: The point to check.
	// @return: True if the Point is valid, false otherwise. 
	bool isValidPoint(const Point& point) const;

	// Determine if a given XY is a valid grid location.
	// @param x: The x-coordinate
	// @param y: The y-coordinate.
	// @return: True if the XY is a valid location, false otherwise.
	bool isValidPoint(int x, int y) const;

	// Check if a given row is fully completed (no EMPTY_BLOCK in the row).
	// @param rowIdx: The index of the row to check.
	// @return: True if the row is fully completed, false otherwise. 
	bool isRowCompleted(int rowIdx) const;

	// Fill a given grid row with specified content
	// @param rowIdx: The index of the row to fill.
	// @param content: The content to fill the row with. 
	void fillRow(int rowIdx, int content);
	
	// Scan the board for completed rows and return a vector of completed row indices.
	// @return: A vector of completed row indices.
	std::vector<int> getCompletedRowIndices() const;

	// Copy the contents of a source row into a target row.
	// @param srcRowIdx: The index of the source row. 
	// @param dstRowIdx: The index of the target row. 
	void copyRowIntoRow(int srcRowIdx, int dstRowIdx);

	// Removes the specified row and triggers a cascade effect by copying each row above it
	// into itself, shifting the grid above the specified row downward. The top row is then
	// filled with empty blocks to compensate for the shift.
	// @param rowIdx: The row to remove and initiate the grid cascade effect.
	void removeRow(int rowIdx);

	// Removes the specified rows from the board and compensates for the removed rows.
	// @param rows: A vector of row indexes that are complete and should be removed.
	void removeRows(const std::vector<int>& rows);
};


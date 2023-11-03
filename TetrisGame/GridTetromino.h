#pragma once
#include "Tetromino.h"
#include "Point.h"
#include <vector>

class GridTetromino : public Tetromino {

private:
	Point gridLoc;

public:
	GridTetromino() : 
		Tetromino(), gridLoc(0,0) 
	{}

	Point getGridLoc() const { return gridLoc; }

	void setGridLoc(int x, int y) { gridLoc.setXY(x, y); }

	void setGridLoc(const Point& p) { gridLoc.setXY(p.getX(), p.getY()); }

	void move(int xOffset, int yOffset);

	std::vector<Point> getBlockLocsMappedToGrid() const;
};

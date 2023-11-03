#include "GridTetromino.h"

void GridTetromino::move(int xOffset, int yOffset) {
	gridLoc.setX(gridLoc.getX() + xOffset);
	gridLoc.setY(gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
	std::vector<Point> gridLocPoints;
	for (const Point& p: blockLocs) {
		gridLocPoints.push_back(Point(p.getX() + gridLoc.getX(), p.getY() + gridLoc.getY()));
	}
	return gridLocPoints;
}

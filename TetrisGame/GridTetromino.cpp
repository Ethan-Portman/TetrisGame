#include "GridTetromino.h"

bool operator==(const GridTetromino& x, const GridTetromino& y) {
	return (x.getGridLoc() == y.getGridLoc()) &&
		(x.getShape() == y.getShape());
}

void GridTetromino::move(int xOffset, int yOffset) {
	gridLoc.setX(gridLoc.getX() + xOffset);
	gridLoc.setY(gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
	std::vector<Point> gridLocPoints;
	for (const Point& p: blockLocs) {
		gridLocPoints.push_back(Point(
			p.getX() + gridLoc.getX(), 
			p.getY() + gridLoc.getY()));
	}
	return gridLocPoints;
}

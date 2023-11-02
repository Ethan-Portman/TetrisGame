#include "Tetromino.h"
#include "Point.h"

void Tetromino::setShape(TetShape shape) {
	this->shape = shape;
	switch (shape) {
	case TetShape::O:
		blockLocs = { Point(0,1), Point(1,1), Point(0,0), Point(1,0) }; break;
	case TetShape::I:
		blockLocs = { Point(0,2), Point(0,1), Point(0,0), Point(0,-1) }; break;
	case TetShape::S:
		blockLocs = { Point(0,1), Point(1,1), Point(0,0), Point(-1,0) }; break;
	case TetShape::Z:
		blockLocs = { Point(-1,1), Point(0,1), Point(0,0), Point(1,0) }; break;
	case TetShape::L:
		blockLocs = { Point(0,1), Point(0,0), Point(0,-1), Point(1, -1) }; break;
	case TetShape::J:
		blockLocs = { Point(0,1), Point(0,0), Point(0,-1), Point(-1,-1) }; break;
	case TetShape::T:
		blockLocs = { Point(-1,0), Point(0,0), Point(1,0), Point(0, -1) }; break;
	}
}

void Tetromino::rotateClockwise() {
	for (int i = 0; i < blockLocs.size(); i++) {
		blockLocs[i].swapXY();
		blockLocs[i].setY(-1 * blockLocs[i].getY());
	}
}

void Tetromino::printToConsole() const {
	for (int y = 3; y > -3; y--) {
		for (int x = -3; x < 3; x++) {
			bool shapePresent = false;
			for (Point block : blockLocs) {
				if (x == block.getX() && y == block.getY())
					shapePresent = true;
			}
			if (shapePresent)
				std::cout << 'x';
			else
				std::cout << '.';
		}
		std::cout << '\n';

	}
}
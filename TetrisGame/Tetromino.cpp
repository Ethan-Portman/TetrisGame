#include "Tetromino.h"
#include "Point.h"

TetShape Tetromino::getRandomShape() {
	//int randShapeIdx{ std::rand() % static_cast<int>(TetShape::COUNT) };
	//return static_cast<TetShape>(randShapeIdx);
	return TetShape::I;
}

TetColor Tetromino::getRandomColor() {
	int randColor{ std::rand() % static_cast<int>(TetColor::COUNT) };
	return static_cast<TetColor>(randColor);
}

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
	for (Point& p : blockLocs) {
		p.swapXY();
		p.multiplyY(-1);
	}
}

void Tetromino::printToConsole() const {
	for (int y = 3; y > -3; y--) {
		for (int x = -3; x < 3; x++) {
			bool shapePresent = false;
			for (const Point& block : blockLocs) {
				if (x == block.getX() && y == block.getY())
					shapePresent = true;
			}
			std::cout << (shapePresent) ?  'x' : '.';
		}
		std::cout << '\n';
	}
}

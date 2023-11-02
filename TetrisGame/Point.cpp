#include "Point.h"
#include <sstream>

void Point::swapXY() {
	int tempVal = x;
	x = y;
	y = tempVal;
}

std::string Point::toString() const {
	std::stringstream toStr;
	toStr << "[" << x << "," << y << "]" << "\n";
	return toStr.str();
}
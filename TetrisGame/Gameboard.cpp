#include "Gameboard.h"


void Gameboard::empty() {
	for (int y = 0; y < MAX_Y; y++) {
		fillRow(y, EMPTY_BLOCK);
	}
}

void Gameboard::printToConsole() const {
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (getContent(x, y) != EMPTY_BLOCK) {
				std::cout << std::setw(2) << getContent(x, y);
			}
			else {
				std::cout << std::setw(2) << '.';
			}
		}
		std::cout << '\n';
	}
}

int Gameboard::getContent(const Point& p) const {
	assert(isValidPoint(p));
	return grid[p.getY()][p.getX()];
}

int Gameboard::getContent(int x, int y) const {
	assert(isValidPoint(x, y));
	return grid[y][x];
}

void Gameboard::setContent(const Point& p, int content) {
	if (isValidPoint(p)) {
		grid[p.getY()][p.getX()] = content;
	}
}

void Gameboard::setContent(int x, int y, int content) {
	if (isValidPoint(x, y)) {
		grid[y][x] = content;
	}
}

void Gameboard::setContent(std::vector<Point>& locs, int content) {
	for (Point& p : locs) {
		setContent(p, content);
	}
}


bool Gameboard::areAllLocsEmpty(const std::vector<Point>& locs) const {
	for (const Point& p : locs) {
		if (isValidPoint(p) && getContent(p) != EMPTY_BLOCK) {
			return false;
		}
	}
	return true;
}

int Gameboard::removeCompletedRows() {
	std::vector<int> completedRows = getCompletedRowIndices();
	removeRows(completedRows);

	return completedRows.size();
}

bool Gameboard::isValidPoint(const Point& p) const {
	return ((0 <= p.getX() && p.getX() < MAX_X) && (0 <= p.getY() && p.getY() < MAX_Y));

}

bool Gameboard::isValidPoint(int x, int y) const {
	return ((0 <= x && x < MAX_X) && (0 <= y && y < MAX_Y));
}

bool Gameboard::isRowCompleted(int rowIdx) const {
	assert(0 <= rowIdx < MAX_Y);
	for (int x = 0; x < MAX_X; x++) {
		if (getContent(x, rowIdx) == EMPTY_BLOCK) {
			return false;
		}
	}
	return true;
}

void Gameboard::fillRow(int rowIdx, int content) {
	assert(0 <= rowIdx < MAX_Y);
	for (int x = 0; x < MAX_X; x++) {
		setContent(x, rowIdx, content);
	}
}

std::vector<int> Gameboard::getCompletedRowIndices() const {
	std::vector<int> completedRows;
	for (int y = 0; y < MAX_Y; y++) {
		if (isRowCompleted(y)) {
			completedRows.push_back(y);
		}
	}
	return completedRows;
}

void Gameboard::copyRowIntoRow(int srcRowIdx, int dstRowIdx) {
	assert(0 <= srcRowIdx && srcRowIdx < MAX_Y);
	assert(0 <= dstRowIdx && dstRowIdx < MAX_Y);

	for (int x = 0; x < MAX_X; x++) {
		setContent(x, dstRowIdx, getContent(x, srcRowIdx));
	}
}

void Gameboard::removeRow(int rowIdx) {
	assert(0 <= rowIdx && rowIdx < MAX_Y);
	for (int y = rowIdx - 1; y >= 0; y--) {
		copyRowIntoRow(y, y + 1);
	}
	fillRow(0, EMPTY_BLOCK);
}

void Gameboard::removeRows(std::vector<int> rows) {
	for (int idx : rows) {
		removeRow(idx);
	}
}

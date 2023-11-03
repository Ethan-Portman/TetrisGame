#include "TetrisGame.h"

const int TetrisGame::BLOCK_WIDTH{ 32 };
const int TetrisGame::BLOCK_HEIGHT{ 32 };
const double TetrisGame::MAX_SECONDS_PER_TICK{ 0.75 };
const double TetrisGame::MIN_SECONDS_PER_TICK{ 0.20 };

void TetrisGame::draw() {
	drawTetromino(currentShape, gameboardOffset);
	drawGameboard();
}

void TetrisGame::onKeyPressed(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			attemptRotate(currentShape);
			drawGameboard();
		}
		else if (event.key.code == sf::Keyboard::Left) {
			attemptMove(currentShape, -1, 0);
		}
		else if (event.key.code == sf::Keyboard::Right) {
			attemptMove(currentShape, 1, 0);
		}
		else if (event.key.code == sf::Keyboard::Down) {
			attemptMove(currentShape, 0, 1);
		}
		else if (event.key.code == sf::Keyboard::Space) {
			// TO_DO
		}
	}
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
	// TO_DO
}

void TetrisGame::tick() {
	// TO_DO
}

void TetrisGame::reset() {
	// TO_DO
}

void TetrisGame::pickNextShape() {
	// TO_DO
}

bool TetrisGame::spawnNextShape() {
	// TO_DO
	return false;
}

bool TetrisGame::attemptRotate(GridTetromino& t) const {
	GridTetromino copy = t;
	copy.rotateClockwise();

	if (isPositionLegal(copy)) {
		t.rotateClockwise();
		return true;
	}

	return false;
}

bool TetrisGame::attemptMove(GridTetromino& t, int x, int y) const {
	GridTetromino copy = t;
	copy.move(x, y);

	if (isPositionLegal(copy)) {
		t.move(x, y);
		return true;
	}

	return false;
}

void TetrisGame::drop(GridTetromino& t) {
	// TO_DO
}

void TetrisGame::lock(GridTetromino& t) {
	// TO_DO
}


void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color) {
	int colorOffset = static_cast<int>(color) * BLOCK_WIDTH;
	int xPos = topLeft.getX() + (xOffset * BLOCK_WIDTH);
	int yPos = topLeft.getY() + (yOffset * BLOCK_HEIGHT);

	// Set the Color of the block
	sf::IntRect colorRect(colorOffset, 0, BLOCK_WIDTH, BLOCK_HEIGHT);
	blockSprite.setTextureRect(colorRect);

	// Set the Position of the block
	blockSprite.setPosition(xPos, yPos);

	// Append the block
	window.draw(blockSprite);
}

void TetrisGame::drawGameboard() {
	for (int y = 0; y < board.MAX_Y; y++) {
		for (int x = 0; x < board.MAX_X; x++) {
			if (board.getContent(x, y) != board.EMPTY_BLOCK) {
				drawBlock(gameboardOffset, x, y, static_cast<TetColor>(board.getContent(x, y)));
			}
		}
	}
}

void TetrisGame::drawTetromino(GridTetromino& t, const Point& p) {
	for (const Point& blockLoc : t.getBlockLocsMappedToGrid()) {
		drawBlock(p, blockLoc.getX(), blockLoc.getY(), t.getColor());
	}
}

void TetrisGame::updateScoreDisplay() {
	// TO_DO
}

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {
	return isWithinBorders(shape) && 
		   board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid());
}

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
	const std::vector<Point> blocklocs = shape.getBlockLocsMappedToGrid();
	for (const Point& p : blocklocs) {
		if (p.getX() < 0 || p.getX() > board.MAX_X - 1 || p.getY() > board.MAX_Y - 1) {
			return false;
		}
	}
	return true;
}

void determineSecondsPerTick() {
	// TO_DO
}
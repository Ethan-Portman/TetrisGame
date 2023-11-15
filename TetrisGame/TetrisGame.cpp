#include "TetrisGame.h"


// STATIC CONSTANTS ======================================

const int TetrisGame::BLOCK_WIDTH{ 32 };
const int TetrisGame::BLOCK_HEIGHT{ 32 };
const double TetrisGame::MAX_SECONDS_PER_TICK{ 0.75 };
const double TetrisGame::MIN_SECONDS_PER_TICK{ 0.20 };

// CONSTRUCTOR -------------------------------------------

TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset)
	: window(window), blockSprite(blockSprite), gameboardOffset(gameboardOffset), nextShapeOffset(nextShapeOffset)
{
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf")) {  
		assert(false && "Missing font: RedOctober.ttf");
	}

	if (!tetrisMusic.openFromFile("sounds/tetrisMusic.ogg")) {
		assert(false && "Missing music: tetrisMusic.ogg");
	}

	if (!gameOverBuffer.loadFromFile("sounds/gameOver.ogg")) {
		assert(false && "Missing sound: gameOver.ogg");
	}
	gameOver.setBuffer(gameOverBuffer);
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(425, 325);

	tetrisMusic.setLoop(true);
	reset();
}

// MEMBER FUNCTIONS ---------------------------------------

void TetrisGame::draw() {
	drawTetromino(currentShape, gameboardOffset, 1.0f);
	drawTetromino(nextShape, nextShapeOffset, 1.0f);
	drawTetromino(ghostShape, gameboardOffset, 0.5f);
	updateGhostShape();
	window.draw(scoreText);
	drawGameboard();
}

void TetrisGame::onKeyPressed(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		switch(event.key.code) {
			case sf::Keyboard::Up:
				attemptRotate(currentShape);
				break;
			case sf::Keyboard::Left:
				attemptMove(currentShape, -1, 0);
				break;
			case sf::Keyboard::Right:
				attemptMove(currentShape, 1, 0);
				break;
			case sf::Keyboard::Down:
				attemptMove(currentShape, 0, 1);
				break;
			case sf::Keyboard::Space:
				drop(currentShape);
				lock(currentShape);
				break;
		}
	}
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
	if (gameLoopState == GameLoopState::Playing) {
		secondsSinceLastTick += secondsSinceLastLoop;
		if (secondsSinceLastTick > secondsPerTick) {
			tick();
			secondsSinceLastTick -= secondsPerTick;
		}

		if (shapePlacedSinceLastGameLoop) {
			shapePlacedSinceLastGameLoop = false;
			if (spawnNextShape()) {
				pickNextShape();
				if (board.getCompletedRowIndices().size() > 0) {
					score += getScoresFromRows(board.removeCompletedRows());
				}
				determineSecondsPerTick();
				updateScoreDisplay();
			}
			else {
				tetrisMusic.stop();
				gameOver.play();
				gameLoopState = GameLoopState::GameOver;
				gameOverClock.restart();
			}
		}
	}
	else if (gameLoopState == GameLoopState::GameOver) {
		if (gameOverClock.getElapsedTime().asMilliseconds() >= 4000) {
			gameLoopState = GameLoopState::Resetting;
			reset();
			gameLoopState = GameLoopState::Playing;
		}
	}
}


int TetrisGame::getScoresFromRows(int rows) const {
	switch (rows) {
		case 0: return 0;
		case 1: return 100;
		case 2: return 300;
		case 3: return 500;
		case 4: return 800;
	}
}

void TetrisGame::tick() {
	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
	}
}

// PRIVATE METHODS ---------------------------------------

void TetrisGame::reset() {
	gameIsOver = false;
	gameLoopState = GameLoopState::Playing;
	score = 0;
	updateScoreDisplay();
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();
	tetrisMusic.play();
}

void TetrisGame::pickNextShape() {
	nextShape.setShape(Tetromino::getRandomShape());
	nextShape.setColor(Tetromino::getRandomColor());
}

bool TetrisGame::spawnNextShape() {
	currentShape = nextShape;
	currentShape.setGridLoc(board.getSpawnLoc());
	return isPositionLegal(currentShape);
}

bool TetrisGame::attemptRotate(GridTetromino& shape) {
	GridTetromino copy = shape;
	copy.rotateClockwise();

	if (isPositionLegal(copy)) {
		shape.rotateClockwise();
		return true;
	}

	return false;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {
	GridTetromino copy = shape;
	copy.move(x, y);

	if (isPositionLegal(copy)) {
		shape.move(x, y);
		return true;
	}
	return false;
}

void TetrisGame::drop(GridTetromino& shape) {
	while (attemptMove(shape, 0, 1));
}

void TetrisGame::lock(GridTetromino& shape) {
	std::vector<Point> shapeLocs = shape.getBlockLocsMappedToGrid();

	board.setContent(shapeLocs, static_cast<int>(shape.getColor()));
	shapePlacedSinceLastGameLoop = true;

}

void TetrisGame::updateGhostShape() {
	ghostShape = currentShape;
	drop(ghostShape);
}

// GRAPHICS METHODS ---------------------------------------

void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color, float alpha) {
	int colorOffset = static_cast<int>(color) * BLOCK_WIDTH;
	int xPos = topLeft.getX() + (xOffset * BLOCK_WIDTH);
	int yPos = topLeft.getY() + (yOffset * BLOCK_HEIGHT);
	blockSprite.setTextureRect({ colorOffset, 0, BLOCK_WIDTH, BLOCK_HEIGHT });  

	if (alpha == 0.5f) {  // Adjust alpha value if needed
		blockSprite.setColor(sf::Color(255, 255, 255, 100));
	}
	else {
		blockSprite.setColor(sf::Color::White); 
	}

	blockSprite.setPosition(xPos, yPos);  
	window.draw(blockSprite);  
}

void TetrisGame::drawGameboard() {
	for (int y = 0; y < board.MAX_Y; y++) {
		for (int x = 0; x < board.MAX_X; x++) {
			if (board.getContent(x, y) != board.EMPTY_BLOCK) {
				drawBlock(gameboardOffset, x, y, static_cast<TetColor>(board.getContent(x, y)), 1.0);
			}
		}
	}
}

void TetrisGame::drawTetromino(GridTetromino& shape, const Point& p, float alpha) {
	for (const Point& blockLoc : shape.getBlockLocsMappedToGrid()) {
		drawBlock(p, blockLoc.getX(), blockLoc.getY(), shape.getColor(), alpha);
	}
}

void TetrisGame::updateScoreDisplay() {
	std::string scoreStr = "score: " + std::to_string(score);
	scoreText.setString(scoreStr);
}

// STATE & GAMEPLAY/LOGIC METHODS ----------------------------

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {
	return isWithinBorders(shape) && 
		   board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid());
}

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
	for (const Point& p : shape.getBlockLocsMappedToGrid()) {
		if (p.getX() < 0 || p.getX() > board.MAX_X - 1 || p.getY() > board.MAX_Y - 1) {
			return false;
		}
	}
	return true;
}

void TetrisGame::determineSecondsPerTick() {
	if (score <= 100) {
		secondsPerTick = MAX_SECONDS_PER_TICK;
	}
	else if (score < 500) {
		secondsPerTick = MAX_SECONDS_PER_TICK * 0.9;
	}
	else if (score < 1000) {
		secondsPerTick = MAX_SECONDS_PER_TICK * 0.8;
	}
	else if (score < 1500) {
		secondsPerTick = MAX_SECONDS_PER_TICK * 0.7;
	}
	else if (score < 2000) {
		secondsPerTick = MAX_SECONDS_PER_TICK * 0.6;
	}
	else {
		secondsPerTick = MIN_SECONDS_PER_TICK;
	}
}

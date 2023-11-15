#pragma once

#include "Gameboard.h"
#include "GridTetromino.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class GameLoopState {
	Playing,
	GameOver,
	Resetting
};

class TetrisGame {
public:
	// Static Constants ============================================================================
	static const int BLOCK_WIDTH;			  // Pixel width of a tetris block
	static const int BLOCK_HEIGHT;			  // Pixel height of a tetris block
	static const double MAX_SECONDS_PER_TICK; // The slowest "tick" rate (in seconds)
	static const double MIN_SECONDS_PER_TICK; // The fastest "tick" rate (in seconds)

private:	
	// State members ===============================================================================
	int score;					// The current game score.
    Gameboard board;			// The gameboard (grid) to represent where all the blocks are.
	GridTetromino currentShape;	// The tetromino that is currently falling.
    GridTetromino nextShape;	// The tetromino that is "on deck".
	GridTetromino ghostShape;	// The tetromino that displays where the currentShape will fall.
	GameLoopState gameLoopState;
	sf::Clock gameOverClock;	// Forces game to reset after the gameOver Sound
	
	// Graphics members ============================================================================
	sf::Sprite& blockSprite;		// The sprite used for all the blocks.
	sf::RenderWindow& window;		// The window the game is drawn on.
	const Point gameboardOffset;	// Pixel XY offset of the gameboard on the screen
	const Point nextShapeOffset;	// Pixel XY offset of the nextShape
	sf::Font scoreFont;				// SFML font for displaying the score.
	sf::Text scoreText;				// SFML text object for displaying the score

	// Music members ===============================================================================
	sf::Music tetrisMusic;		     // The Music for the Tetris Game
	sf::Sound gameOver;			     // Sound for game over
	sf::SoundBuffer gameOverBuffer;  

	
	// Time members ================================================================================
	double secondsPerTick = MAX_SECONDS_PER_TICK;   // The seconds per tick (Time for block to fall one line)	
	double secondsSinceLastTick{ 0.0 };				// To determine if its time to tick
	bool shapePlacedSinceLastGameLoop{ false };		// Tracks whether a shape has been placed in the current gameloop

public:
	// Constructor
	// Resets the game to its initial State
	// @param window: Where the Tetris Game will be held
	// @param blockSprite: The Sprite used for all Tetrominos
	// @param gameboardOffset: The offset of the Gameboard on the Window
	// @param nextShapeOffset: The offset of the nextShape on the Gameboard
	TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset);

	// Event and game loop processing ==============================================================

	// Draws everything to do with the game (board, curentShape, nextShape, score)
	// Called every gameloop 
	void draw();								

	// Handles keypress events for the game (up, left, right, down, space) 
	// and updates the state of the game accordingly.
	// @param event: The keyboard event that maps to a command.
	void onKeyPressed(const sf::Event& event);

	// Called every game loop to handle ticks & tetromino placement/ locking.
	// @param secondsSinceLastLoop: Float - Time elapsed since last tick.
	void processGameLoop(float secondsSinceLastLoop);

	// Returns the corresponding score for the amount of rows completed at once.
	// @param rows: The amount of completed rows on the board.
	// @return: The score attained from the amount of rows comppleted.
	int getScoresFromRows(int rows) const;

	// A tick forces the currentShape to move down by one square. If not successfull, 
	// it is locked into the gameboard.
	void tick();

private:
	// Reset everything for a new game 
	//  - Clear the gameboard and set the score to 0.
	//  - Determine the tick rate.
	//  - Pick and spawn the next shape and pick the shape on deck.
	void reset();

	// Selects a random tetShape and tetColor for the next Shape to be used in the game.
	void pickNextShape();

	// copy the nextShape into the currentShape (through assignment)
	//   position the currentShape to its spawn location.
	//	 @return: True/false based on if currentShape is in a legal position.
	bool spawnNextShape();																	

	// Test to see if a rotation is legal on the tetromino and if so, rotates it.
	// @param shape: The tetromino shape that is attempting to rotate.
	// @return: True/false based on if tetromino rotated or not.
	bool attemptRotate(GridTetromino& shape);
   
	// Test to see if a movement is legal on the tetromino and if so, moves it.
	// @param shape: The tetromino shape that is attempting to move.
	// @param x: The horizontal direction the tetromino shape is attempting to move.
	// @param y: The vertical direction the tetromino shape is attempting to move.
	// @return: True/false based on if tetromino moved or not.
	bool attemptMove(GridTetromino& shape, int x, int y);												

	// Drops the tetromino shape vertically as far as it can legally go.
	// @param shape: The tetromino shape that will drop. 
	void drop(GridTetromino& shape);

	// Copy the Tetrmono shape contents (color) onto the grid. 
	// @param shape: The tetromino shape whose contents will be added to the grid. 
	void lock(GridTetromino& shape);

	// Drops the Ghost Shape as far as it will go to represent where the current
	// shape will fall.
	void updateGhostShape();
	
	// Graphics methods =================================================================================
	
	// Draws a tetris block sprite on the canvas in the window. 
	// The block position is specified in terms of 2 offsets (top left of gameboard and x, y offset into the gameboard.
	// @param topLeft: Top left of the gameboard in pixels.
	// @param xOffset: The x-Offset of new shape on the board in blocks.
	// @param yOffset: The y-offset of new shape on the board in blocks.
	// @param color: The color of the new shape
	void drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color, float alpha);
										
	// Draws the gameboard blocks on the window by iterating through each row and col and drawing each block. 
	// Only draws the blocks that are not empty.
	void drawGameboard();
	
	// Draws a tetromino on the window. 
	// @param shape: The tetromino shape to be drawn onto the canvas.
	// @param p: The 'base pont' from which to calculate block offsets.
	void drawTetromino(GridTetromino& shape, const Point& p, float alpha);
	
	// Updates the score display by forming the string "score: ####"
	void updateScoreDisplay();

	// State & gameplay/logic methods ======================================================================

	// Determines if a Tetromino can legally be placed at its current position on the gameboard.
	// A Tetrmino can be legally placed if it is within the gameboard and all the locations it inhabits are empty. 
	// @param shape: The tetromino shape being tested if its in a legal position. 
	bool isPositionLegal(const GridTetromino& shape) const;

	// Determines if a Tetromino is within the left, right, & bottom gameboard borders (ignore the upper for spawning purposes)
	// @param shape: The tetromino shape being tested if its within borders of gameboard.
	// @return: bool, true if the shape is within the left, right, and lower border of the grid. 
	bool isWithinBorders(const GridTetromino& shape) const;


	// set secsPerTick 
	//   - basic: use MAX_SECS_PER_TICK
	//   - advanced: base it on score (higher score results in lower secsPerTick)
	// params: none
	// return: nothing
	void determineSecondsPerTick();
};

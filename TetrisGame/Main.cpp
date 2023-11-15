#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrisGame.h"
#include "TestSuite.h"


int main() {	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Seed the Randomizer
	TestSuite::runTestSuite();									// Run some Test Suites

	/*--------- Load & Set Sprites/ Textures used in Game ---------*/

	sf::Sprite blockSprite;			// The tetromino block sprite
	sf::Texture blockTexture;		// The tetromino block texture
	sf::Sprite backgroundSprite;	// The background sprite
	sf::Texture backgroundTexture;	// The background texture
	backgroundTexture.loadFromFile("images/background.png");  // Load the Background Sprite
	backgroundSprite.setTexture(backgroundTexture);			  // Set texture of Background Sprite
	blockTexture.loadFromFile("images/tiles.png");	// Load the Tetris Block Sprite
	blockSprite.setTexture(blockTexture);			// Set texture of Tetris Block Sprite

	/*------------------ Create the Game Window ------------------*/

	sf::RenderWindow window(sf::VideoMode(640, 800), "Tetris Game Window");	
	window.setFramerateLimit(30);				// set a max framerate of 30 FPS
	const Point gameboardOffset{ 54, 125 };		// the pixel offset of the top left of the gameboard 
	const Point nextShapeOffset{ 490, 210 };	// the pixel offset of the next shape Tetromino

	/*--------------------- Set up the Game ----------------------*/

	TetrisGame game(window, blockSprite, gameboardOffset, nextShapeOffset);
	sf::Clock clock;		// Clock used to determine seconds per game loop
	sf::Event guiEvent;		// Event for handling userInput from the GUI

	/*---------------------- Main Game Loop ----------------------*/

	while (window.isOpen()) {	
		float elapsedTime = clock.getElapsedTime().asSeconds(); // Get time since the last loop
		clock.restart();		

		sf::Event event;  // Window or keyboard event that has occured since the last game loop
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {	// Handle Close Button Clicked
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {  // Handle Key Press
				game.onKeyPressed(event);
			}
		}

		game.processGameLoop(elapsedTime);	// handle tetris game logic in here.

		window.clear(sf::Color::White);	// clear the entire window
		window.draw(backgroundSprite);	// draw the background (onto the window) 				
		game.draw();					// draw the game (onto the window)
		window.display();				// re-display the entire window
	}

	return 0;
}

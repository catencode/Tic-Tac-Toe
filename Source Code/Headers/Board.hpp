#pragma once
#include "Constants.hpp"
#include "ResourceManager.hpp"

class Board
{

public:

	// The enum for a square in the board
	enum Square { Cross, None, Circle };

	// Initialize the board
	void init();
	// Add an object on the board
	void add(int x, int y);
	// Draw the board to the screen
	void draw();
	// Update the board
	void update();
	// No of valid clicks
	int clicks;
	// Is this board evaluated?
	bool evaluated;
	// The array holding the board
	Square board[3][3];

};


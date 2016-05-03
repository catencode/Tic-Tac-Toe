#include "..\Headers\Board.hpp"

// Initialize the board
void Board::init()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = None;
		}
	}
}

// Draw the board to the screen
void Board::draw()
{
	// Get the resource manager
	ResourceManager* resourceManager = ResourceManager::get();

	// Draw the board in the center of the screen
	resourceManager->draw("board", (SCREEN_WIDTH - BOARD_WIDTH) / 2, (SCREEN_HEIGHT - BOARD_HEIGHT) / 2, BOARD_WIDTH, BOARD_HEIGHT);

	// Draw each piece on the board
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Draw a cross if its a cross and circle if its a circle
			if (board[i][j] == Cross)
				resourceManager->draw("cross", 60 + i * 240, 60 + j * 240, 200, 200);
			if (board[i][j] == Circle)
				resourceManager->draw("circle", 60 + i * 240, 60 + j * 240, 200, 200);
		}
	}
}

// Update the board
void Board::update()
{
	// The x and y positions of the mouse
	int mouseX, mouseY;

	// Get the position of the mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseX >= 54 && mouseY >= 54 && mouseX <= 745 && mouseY <= 745)
		add((mouseX - 54) / 232, (mouseY - 54) / 232);
}

// Add an object on the board
void Board::add(int x, int y)
{
	// If the position is not occupied by any object
	if (board[x][y] == None)
	{
		// Place a cross and circle alternatively
		if (clicks++ % 2 == 0)
			board[x][y] = Cross;
		else
			board[x][y] = Circle;

		// If clicks are more than or equal to 3 then the game needs to be evaluated
		if (clicks >= 3)
			evaluated = false;
	}
}

#include "../Headers/Game.hpp"

int main(int argc, char* argv[])
{
	// Create the game object
	Game* game = new Game();

	// Initialize the game
	if (!game->init("Tic Tac Toe"))
	{
		// Error initializing the game, show error message
		cout << "Error initializing, quitting..." << endl;
		return 1;
	}

	// The Game Loop
	while (game->isRunning())
	{
		game->handleEvents();
		game->update();
		game->render();
		game->postUpdate();
	}

	// Clean the game
	game->clean();

	return 0;
}
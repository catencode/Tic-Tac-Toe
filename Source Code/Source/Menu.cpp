#include "..\Headers\Menu.hpp"

// Initialize the game room
bool Menu::init()
{
	load();

	playPlayer = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 6, "moonhouse", "Play vs Player");
	playComputer = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 6, "moonhouse", "Play vs Computer");

	return true;
}

// Update the game room
void Menu::update()
{
	playComputer->update();
	playPlayer->update();

	if (playComputer->isActive())
	{
		SDL_Delay(100);

		TicTacToe* game = new TicTacToe(renderer);
		game->gameMode = TicTacToe::Computer;

		Game::playRoom(game);
		return;
	}
	
	if (playPlayer->isActive())
	{
		SDL_Delay(100);

		TicTacToe* game = new TicTacToe(renderer);
		game->gameMode = TicTacToe::Player;

		Game::playRoom(game);
		return;
	}
}

// Render, draw the game room to the screen
void Menu::render()
{
	playComputer->draw();
	playPlayer->draw();
}

// Clean the resource used by the game room
void Menu::clean()
{
	delete playComputer;
	delete playPlayer;
}

// Load the required resources
void Menu::load()
{
	// Get the resource manager
	ResourceManager* resourceManager = ResourceManager::get();

	// Load the font
	resourceManager->loadFont("Assets/moonhouse.ttf", "moonhouse", 64);
}

// Handle events
void Menu::handleEvent(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		playComputer->click();
		playPlayer->click();
	}
}

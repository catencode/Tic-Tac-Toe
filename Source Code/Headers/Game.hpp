#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Constants.hpp"
#include "ResourceManager.hpp"
#include "Board.hpp"
#include "Evaluator.hpp"
#include "GameRoom.hpp"
#include "Menu.hpp"
#include "TicTacToe.hpp"

using namespace std;

class Game
{
public:

	// Initialize the game
	bool init(string title);
	// Handle events (mouse, keyboard, etc.)
	void handleEvents();
	// Update, Process, Do physics, etc.
	void update();
	// Render, draw to the screen
	void render();
	// Clean the game and its resources
	void clean();
	// Is the game running? (return running)
	bool isRunning() { return running; }
	// Post update ( update after draw )
	void postUpdate();
	// Play a specific game room
	static void playRoom(GameRoom* room);

private:

	// Load game resources
	bool load();

	// The state of the game, running or not
	bool running;
	// The main window
	SDL_Window* window;
	// The main renderer
	SDL_Renderer* renderer;

	// The pointer to the current game room
	static GameRoom* currentRoom;
};
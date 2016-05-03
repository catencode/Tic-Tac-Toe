#pragma once
#include "ResourceManager.hpp"
#include "Constants.hpp"
#include "GameRoom.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "TicTacToe.hpp"

class Menu:
	public GameRoom
{

private:
	// Load the required resources
	void load();
	// The button for playing with computer
	Button* playComputer;
	// The button for playing with computer
	Button* playPlayer;

public:
	Menu(SDL_Renderer* argRenderer) : GameRoom(argRenderer) {};

	bool init();
	void update();
	void render();
	void clean();
	void handleEvent(SDL_Event e);
};


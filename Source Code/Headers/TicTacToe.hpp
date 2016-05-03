#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameRoom.hpp"
#include "ResourceManager.hpp"
#include "Evaluator.hpp"

class TicTacToe:
	public GameRoom
{

private:
	// Load the required resources
	bool load();
	// Play the move of the computer
	void playMove(vector<int> move);

	// The board
	Board* board;
	// The evaluator
	Evaluator* evaluator;
	// Is the result of the game declared?
	bool result;

public:
	TicTacToe(SDL_Renderer* argRenderer) : GameRoom(argRenderer) {};

	bool init();
	void update();
	void render();
	void clean();
	void handleEvent(SDL_Event e);
	void postUpdate();

	// The enum for the game mode of the game
	enum GameMode{ Player, Computer };

	// The gamemode of the game. ( vs Player or vs Computer )
	GameMode gameMode;

};


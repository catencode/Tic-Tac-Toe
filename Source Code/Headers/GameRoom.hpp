#pragma once
#include <SDL.h>

class GameRoom
{

public:
	// Constructor
	GameRoom(SDL_Renderer* argRenderer){ renderer = argRenderer; }

	// Initialize the game room
	virtual bool init(){ return true; }
	// Update the game room
	virtual void update(){}
	// Render, draw the game room to the screen
	virtual void render(){}
	// Clean the resource used by the game room
	virtual void clean(){}
	// Handle an event
	virtual void handleEvent(SDL_Event e){}
	// Post update the game room
	virtual void postUpdate(){}

	// The renderer
	SDL_Renderer* renderer;

};


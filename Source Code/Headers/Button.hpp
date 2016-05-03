#pragma once
#include <iostream>
#include <string>
#include <SDL_mouse.h>
#include "ResourceManager.hpp"
#include <sstream>

using namespace std;

class Button
{

private:
	// The width of the button
	int width;
	// The height of the button
	int height;
	// The current background color of the button
	SDL_Color bgColor;
	// The current text color of the button
	SDL_Color textColor;
	// Is the button activated?
	bool active;
	// The object counter
	static int counter;
	// The id of the button
	int id;
	// The font of the button
	string font;
	// The texture id of the button
	string textureId;

public:
	// The x position of the button
	int x;
	// The y position of the button
	int y;
	// The background colors of the button
	SDL_Color bgColorNormal, bgColorActivated;
	// The colors of the text of the button
	SDL_Color textColorNormal, textColorActivated;
	// The text shown in the button
	string text;
	// The padding of the button
	int padding;

	// Draw the button to the screen
	void draw();
	// Update the state of the button
	void update();
	// The button was clicked
	void click();
	// The constructor should initialize the button
	Button(int x, int y, string font, string text);

	// Is the button activated? return active
	bool isActive(){ return active; }

};


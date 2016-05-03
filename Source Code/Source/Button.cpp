#include "..\Headers\Button.hpp"

int Button::counter = 0;

// The constructor should initialize the button
Button::Button(int argX, int argY, string argFont, string argText)
{
	// Give an id to the button
	id = counter++;

	// Initialize all the properties
	x = argX;
	y = argY;
	text = argText;
	font = argFont;

	// The default background color is white
	bgColor = bgColorNormal = { 0xFF, 0xFF, 0xFF };

	// The default text color is black
	textColor = textColorNormal = { 0x00, 0x00, 0x00 };

	// By default, when the button is activated the colors are swapped
	textColorActivated = { 0xFF, 0xFf, 0xFF };
	bgColorActivated = { 0x00, 0x00, 0x00 };

	// The default padding
	padding = 10;

	// Generate the texture id for the button
	stringstream intToString;

	intToString << "buttonTexture" << id;
	textureId = intToString.str();

	// Initially the button is not active
	active = false;
}

// Update the state of the button
void Button::click()
{
	// The co-ordinates of the mouse
	int mouseX, mouseY;

	// Get the co-ordinates of the mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// Is the mouse inside the button?
	if (mouseX >= x - width / 2 &&
		mouseX <= x + width / 2 &&
		mouseY >= y - height / 2 &&
		mouseY <= y + height / 2)
	{
		active = !active;
	}
}

// Update the state of the button
void Button::update()
{
	// The co-ordinates of the mouse
	int mouseX, mouseY;

	// Get the co-ordinates of the mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// Is the mouse inside the button?
	if (mouseX >= x - width / 2 &&
		mouseX <= x + width / 2 &&
		mouseY >= y - height / 2 &&
		mouseY <= y + height / 2)
	{
		bgColor = bgColorActivated;
		textColor = textColorActivated;
	}
	else
	{
		bgColor = bgColorNormal;
		textColor = textColorNormal;
	}
}


// Draw the button to the screen
void Button::draw()
{	
	// Get the resource manager
	ResourceManager* resourceManager = ResourceManager::get();

	// Delete the texture if it already exists
	if (resourceManager->exists(textureId))
	{
		resourceManager->clean(textureId);
	}

	// Load the text texture
	resourceManager->loadFromText(textureId, font, text, textColor);

	// The variables holding the size of the text
	int rectWidth, rectHeight;

	// Query the text texture to get its size
	resourceManager->queryTexture(textureId, &rectWidth, &rectHeight);

	width = rectWidth + padding;
	height = rectHeight + padding;

	// Draw the background rectangle
	resourceManager->drawRectFilled(x - width / 2, y - height / 2, width, height, bgColor);

	// Draw the text on top
	resourceManager->drawOriginal(textureId, x - rectWidth / 2, y - rectHeight / 2);

}


#pragma once
#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class ResourceManager
{
public:
	// Load a texture
	bool load(string name, string fileName);
	// Draw a texture to the screen
	bool draw(string textureId, float xpos, float ypos, float width, float height);
	// Clean a texture and its resources
	bool clean(string textureId);
	// Set the renderer for loading and drawing
	void setRenderer(SDL_Renderer* renderer) { textureRenderer = renderer; }
	// Get the resource manager object
	static ResourceManager* get();
	// Load a texture from text, font and color
	bool loadFromText(string textureId, string font, string text, SDL_Color color);
	// Load a ttf font
	bool loadFont(string fileName, string fontId, int pointSize);
	// Delete a font
	bool deleteFont(string fontId);
	// Draw a texture with its original size
	void drawOriginal(string textureId, float xpos, float ypos);
	// Query the texture for width and height
	void queryTexture(string textureId, int* width, int* height); 
	// Does the given texture exist?
	bool exists(string textureId) { return (textureMap[textureId] != NULL); }

	// Draw a rectangle to the screen
	void drawRect(int x, int y, int width, int height, SDL_Color color);
	// Draw a rectangle to the screen
	void drawRectFilled(int x, int y, int width, int height, SDL_Color color);

private:
	// Private constructor
	ResourceManager(){}
	
	// The texture map
	map<string, SDL_Texture*> textureMap;
	// The font map
	map<string, TTF_Font*> fontMap;
	// The pointer to the renderer
	SDL_Renderer* textureRenderer;
	// The static resource manager instance
	static ResourceManager* instance;
};


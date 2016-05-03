#include "..\Headers\ResourceManager.hpp"

// Load a texture
bool ResourceManager::load(string textureId, string fileName)
{
	// Does the texture with this id already exist?
	if (textureMap[textureId] != NULL)
	{
		// It exists! Report error and quit
		cout << "Error while loading texture." << endl;
		cout << "A texture with the id '" << textureId.c_str() << "' already exists." << endl;
		return false;
	}

	SDL_Texture* texture; // The texture to be loaded
	SDL_Surface* tempSurface; // The temporary surface required

	// Load the file in the temp surface
	tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface == NULL)
	{
		// There was an error loading the surface, show error message and quit
		cout << "Error loading surface from file '" << fileName.c_str() << "'" << endl;
		cout << "SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}

	// Create texture from the temporary surface
	texture = SDL_CreateTextureFromSurface(textureRenderer, tempSurface);

	if (texture == NULL)
	{
		// There was an error converting the surface, show error message and quit
		cout << "Error converting the surface '" << textureId.c_str() << "' to texture" << endl;
		cout << "SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}

	// Map the texture to its id
	textureMap[textureId] = texture;

	// Loading successful, return true
	return true;
}

// Draw a texture to the screen
bool ResourceManager::draw(string textureId, float xpos, float ypos, float width, float height)
{
	// Does a texture with this id exist?
	if (textureMap[textureId] == NULL)
	{
		// It doesn't! Report error and quit
		cout << "Error while drawing texture." << endl;
		cout << "A texture with the id '" << textureId.c_str() << "' doesn't exist!" << endl;
		return false;
	}

	SDL_Rect srcRect; // The rectangle for the source texture
	SDL_Rect destRect; // The rectangle for the destination texture

	// Get information about the texture for the source rectangle
	SDL_QueryTexture(textureMap[textureId], NULL, NULL, &srcRect.w, &srcRect.h);

	// Set the rectangles!
	srcRect.x = srcRect.y = 0;

	destRect.x = (int)xpos;
	destRect.y = (int)ypos;

	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	if (width != NULL)
		destRect.w = (int)width;
	if (height != NULL)
		destRect.h = (int)height;

	// Let's draw(copy) the texture to the screen
	SDL_RenderCopy(textureRenderer, textureMap[textureId], &srcRect, &destRect);

	// Drawing successful, return true
	return true;
}

bool ResourceManager::clean(string textureId)
{
	// Does a texture with this id exist?
	if (textureMap[textureId] == NULL)
	{
		// It doesn't! Report error and quit
		cout << "Error while cleaning!" << endl;
		cout << "A texture with the id '" << textureId.c_str() << "' doesn't exist." << endl;
		return false;
	}

	// Destroy the texture
	SDL_DestroyTexture(textureMap[textureId]);

	// Set the pointer to null
	textureMap[textureId] = NULL;

	return true;
}


// --- The singleton implementation --- //

// Set the object reference to null, first
ResourceManager* ResourceManager::instance = NULL;

// Get the resource manager object
ResourceManager* ResourceManager::get()
{
	// Has the instance been created?
	if (instance == NULL)
	{
		// No, Create the instance!
		instance = new ResourceManager();
	}

	// Return the singleton object
	return instance;
}

// --- --- //

bool ResourceManager::loadFont(string fileName, string fontId, int pointSize)
{
	// Does a font with this id exist?
	if (fontMap[fontId] != NULL)
	{
		// Yes, report error and quit
		cout << "error loading font '" << fontId << "'!" << endl;
		cout << "font with id '" << fontId << "' already exists." << endl;
		return false;
	}

	TTF_Font *tempFont; // The font to be loaded

	// Load the font from the given file name and with the given point size
	tempFont = TTF_OpenFont(fileName.c_str(), pointSize);

	// Map the font with its id
	fontMap[fontId] = tempFont;

	// Font loaded successfully
	return true;
}

bool ResourceManager::loadFromText(string textureId, string fontId, string text, SDL_Color color)
{
	// Does a texture with this id exist?
	if (textureMap[textureId] != NULL)
	{
		// Yes, report error and quit
		cout << "error loading texture '" << textureId << "'!" << endl;
		cout << "texture with id '" << textureId << "' already exists." << endl;
		return false;
	}

	// Does a font with this id exist?
	if (fontMap[fontId] == NULL)
	{
		// No, report error and quit
		cout << "error loading texture '" << textureId << "'!" << endl;
		cout << "font with id '" << fontId << "' doesn't exist." << endl;
		return false;
	}

	SDL_Surface* tempSurface; // The temporary surface
	SDL_Texture* texture; // The texture to be loaded

	// Load the text on the surface
	tempSurface = TTF_RenderText_Solid(fontMap[fontId], text.c_str(), color);

	// Load texture from the text surface
	texture = SDL_CreateTextureFromSurface(textureRenderer, tempSurface);

	// Map the texture with its id
	textureMap[textureId] = texture;

	// Texture loaded successful
	return true;
}

bool ResourceManager::deleteFont(string fontId)
{
	// Does a font with this id exist?
	if (fontMap[fontId] == NULL)
	{
		// No, report error and quit
		cout << "error deleting font '" << fontId << "'!" << endl;
		cout << "font with id '" << fontId << "' doesn't exist." << endl;
		return false;
	}

	// Close the font!
	TTF_CloseFont(fontMap[fontId]);
	fontMap[fontId] = NULL;

	// Font deleted successfully
	return true;
}

void ResourceManager::drawOriginal(string textureId, float xpos, float ypos)
{
	// The size variables
	int width;
	int height;

	// Get the size of the texture
	SDL_QueryTexture(textureMap[textureId], NULL, NULL, &width, &height);

	// Use the normal draw function to draw the texture with its original size
	draw(textureId, xpos, ypos, width, height);
}

void ResourceManager::queryTexture(string textureId, int* width, int* height)
{
	SDL_QueryTexture(textureMap[textureId], NULL, NULL, width, height);
}

void ResourceManager::drawRect(int x, int y, int width, int height, SDL_Color color)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	SDL_SetRenderDrawColor(textureRenderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawRect(textureRenderer, &rect);
}

void ResourceManager::drawRectFilled(int x, int y, int width, int height, SDL_Color color)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	SDL_SetRenderDrawColor(textureRenderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderFillRect(textureRenderer, &rect);
}

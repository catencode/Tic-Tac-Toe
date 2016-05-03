#include "..\Headers\Game.hpp"

GameRoom* Game::currentRoom = NULL;

// Initialize the game
bool Game::init(string title)
{
	// Initialize SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Error initializing SDL, show error message and quit
		cout << "Unable to initialize SDL Video!" << endl;
		cout << "SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	// Create the window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (window == NULL)
	{
		// Error creating window, show error message and quit
		cout << "Unable to create the main window!" << endl;
		cout << "SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	// Create the renderer for the window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		// Error creating renderer, show error message and quit
		cout << "Unable to create renderer for the main window!" << endl;
		cout << "SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	// Initialize SDL_image
	IMG_InitFlags imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		// The flags given were not the ones which which were returned
		// Error initializing SDL_image, show error message and quit
		cout << "Unable to initialize SDL_image!" << endl;
		cout << "SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() < 0)
	{
		// SDL_ttf could not be initialized, show error message
		cout << "failed to initialize SDL_ttf" << endl;
		cout << "SDL_ttf Error: " << TTF_GetError() << endl;
	}

	// Play the first room
	playRoom(new Menu(renderer));

	// Get the resource manager
	ResourceManager* resourceManager = ResourceManager::get();
	resourceManager->setRenderer(renderer); // set renderer

	// Initialization successful, change the state of the game to running
	running = true;

	return true;
}


// Load game resources
bool Game::load()
{
	// Get the resource manager
	ResourceManager* resourceManager = ResourceManager::get();

	// Load textures
	resourceManager->load("board", "Assets/Board.png"); // load the board texture
	resourceManager->load("cross", "Assets/Cross.png"); // load the cross texture
	resourceManager->load("circle", "Assets/Circle.png"); // load the circle texture

	return true;
}

// Handle events (mouse, keyboard, etc.)
void Game::handleEvents()
{
	// Event holder
	SDL_Event e;

	// Poll the event queue
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			// User closes the window, stop the game, set running to false
			running = false;
			break;
		default:
			// Let the current room handle the event
			currentRoom->handleEvent(e);
			break;
		}
	}
}

// Update, Process, Do physics, etc.
void Game::update()
{
	// Update the current game room
	currentRoom->update();
}

// Render, draw to the screen
void Game::render()
{
	// Set the draw color of the renderer to opaque white
	SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0xFf);

	// First, clear the renderer
	SDL_RenderClear(renderer);

	// Render the current game room
	currentRoom->render();

	// Update the renderer
	SDL_RenderPresent(renderer);
}

// Clean the game and its resources
void Game::clean()
{
	// Delete the current room
	currentRoom->clean();

	delete currentRoom;

	// Destroy the renderer and the window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Nullify pointers
	renderer = NULL;
	window = NULL;

	// Quit SDL, SDL_image
	IMG_Quit();
	SDL_Quit();
}


// Post update ( update after draw )
void Game::postUpdate()
{
	// Post Update the current room
	currentRoom->postUpdate();
}

void Game::playRoom(GameRoom* room)
{
	// Was the room already created?
	if (currentRoom != NULL)
	{
		// Yes, clean the room
		currentRoom->clean();
		delete currentRoom;
	}

	// Set the current room to the new room
	currentRoom = room;
	currentRoom->init();
}

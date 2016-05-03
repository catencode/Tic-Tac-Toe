#include "..\Headers\TicTacToe.hpp"

// Initialize the game room
bool TicTacToe::init()
{
	// Get the resource manager
	ResourceManager* resourceManager = ResourceManager::get();
	resourceManager->setRenderer(renderer); // Set the renderer

	// Load game resources
	if (!load())
	{
		// Error while loading, show error message
		cout << "Error while loading, quiting." << endl;
	}

	// Create game objects
	board = new Board();
	board->init(); // Initialize the board
	board->evaluated = true; // the new board is already evaluated

	// Initially the result is not declared
	result = false;

	// The evaluator object
	evaluator = new Evaluator();

	return true;
}

// Update the game room
void TicTacToe::update()
{
	Evaluator::Result evaluation;

	// If the board is not evaluated, evaluate the board
	if (board->evaluated == false)
	{
		cout << "evaluating..." << endl;

		evaluation = evaluator->evaluatePosition(board);

		switch (evaluation)
		{
		case Evaluator::None:
			// No result
			cout << "no result yet!" << endl;
			break;
		case Evaluator::Cross:
			// Cross wins
			cout << "Cross Wins! Congratulations!!!" << endl;
			result = true;
			break;
		case Evaluator::Circle:
			// Circle wins
			cout << "Circle Wins! Congratulations!!!" << endl;
			result = true;
			break;
		case Evaluator::Draw:
			// Game Drawn
			cout << "Game Drawn!" << endl;
			result = true;
			break;
		}

		// The board has been evaluated
		board->evaluated = true;
	}
}

// Render, draw the game room to the screen
void TicTacToe::render()
{
	// Draw the board
	board->draw();
}

// Clean the resource used by the game room
void TicTacToe::clean()
{
	// Clean and delete the game objects
	delete board;
}

bool TicTacToe::load()
{
	// Get the resource manager
	ResourceManager* resourceManager = ResourceManager::get();

	// Load textures
	resourceManager->load("board", "Assets/Board.png"); // load the board texture
	resourceManager->load("cross", "Assets/Cross.png"); // load the cross texture
	resourceManager->load("circle", "Assets/Circle.png"); // load the circle texture

	return true;
}

// Handle an event
void TicTacToe::handleEvent(SDL_Event e)
{
	// The mouse button down event
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (result == false)
			board->update();
	}
}

// Play the move of the computer
void TicTacToe::playMove(vector<int> move)
{
	board->add(move[0], move[1]);
}

// Post update the game room
void TicTacToe::postUpdate()
{
	// If its the computers turn and the result has not been declared
	if (!result && board->clicks % 2 == 1 && gameMode == Computer)
	{
		// Play the computed move!
		playMove(evaluator->computeMove(board));
	}
}

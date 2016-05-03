#include "..\Headers\Evaluator.hpp"

// Evaluate a position based on the input
Evaluator::Result Evaluator::evaluatePosition(Board* board)
{
	for (int i = 0; i < 8; i++)
	{
		if (i < 3)
		{
			// Evaluate row
			if (board->board[0][i] == board->board[1][i] && board->board[1][i] == board->board[2][i] && board->board[0][i] != Board::None)
				return (Result)board->board[0][i];
		}
		else if (i >= 3 && i < 6)
		{
			int j = i - 3;

			// Evaluate column
			if (board->board[j][0] == board->board[j][1] && board->board[j][1] == board->board[j][2] && board->board[j][0] != Board::None)
				return (Result)board->board[j][0];
		}
		else if (i == 6)
		{
			// Evaluate Diagonal
			if (board->board[0][0] == board->board[1][1] && board->board[1][1] == board->board[2][2] && board->board[0][0] != Board::None)
				return (Result)board->board[0][0];
		}
		else if (i == 7)
		{
			// Evaluate Diagonal
			if (board->board[2][0] == board->board[1][1] && board->board[1][1] == board->board[0][2] && board->board[2][0] != Board::None)
				return (Result)board->board[2][0];
		}
	}

	if (board->clicks >= 9)
		return Draw;

	// No result
	return None;
}

// Get all the valid moves on a board
vector<vector<int>> Evaluator::getMoves(Board* board)
{
	vector<vector<int>> moves;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// If the place is empty, the move is valid
			if (board->board[i][j] == Board::None)
			{
				vector<int> move;
				move.push_back(i);
				move.push_back(j);
				moves.push_back(move);
			}
		}
	}

	// Return the vector holding the moves
	return moves;
}

// Give a value for the board in value map
int Evaluator::valueBoard(Board board, vector<int> move)
{
	// Play the move
	board.add(move[0], move[1]);

	// Get the result of the position
	Result positionResult = evaluatePosition(&board);

	// Is the result of the board declared?
	if (positionResult != None)
	{
		// Yes, assign the board its value and quit
		return (int)positionResult;
	}

	// No result yet, Get all the possible moves for the board
	vector<vector<int>> moves = getMoves(&board);

	vector<int> moveValues;

	// Get into a loop for getting the values of all required board
	for (int i = 0; i < moves.size(); i++)
	{
		moveValues.push_back(valueBoard(board, moves[i]));
	}

	vector<int>::iterator it; // the iterator

	// Get the value of the best move
	Turn turn = getTurn(&board);

	if (turn == Player)
		it = min_element(moveValues.begin(), moveValues.end());
	else
		it = max_element(moveValues.begin(), moveValues.end());

	return *it;
}

// Whoose turn is it?
Evaluator::Turn Evaluator::getTurn(Board* board)
{
	if (board->clicks % 2 == 0)
		return Player;
	else
		return Computer;
}

// Compute move for a position
vector<int> Evaluator::computeMove(Board* board)
{
	// Get all the valid moves
	vector<vector<int>> moves = getMoves(board);
	// A map to store values of all the moves
	vector<int> moveValues;
	// The iterator
	vector<int>::iterator it;

	// Value all the moves
	for (int i = 0; i < moves.size(); i++)
	{
		moveValues.push_back(valueBoard(*board, moves[i]));
	}

	// Select the best move
	it = max_element(moveValues.begin(), moveValues.end());

	// Return the best move
	return moves[distance(moveValues.begin(), it)];
}


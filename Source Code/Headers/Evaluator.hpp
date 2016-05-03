#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include "Board.hpp"

class Evaluator
{

public:
	// The enum for result
	enum Result { Cross, Draw, Circle, None };

	// Evaluate a position based on the input
	Result evaluatePosition(Board* board);
	// Compute move for a position
	vector<int> computeMove(Board* board);

private:
	// The enum for turns
	enum Turn { Computer, Player };

	// Give a value for the board in value map
	int valueBoard(Board board, vector<int> move);
	// Get all the valid moves on a board
	vector<vector<int>> getMoves(Board* board);
	// Whoose turn is it?
	Turn getTurn(Board* board);

	int counter;
};

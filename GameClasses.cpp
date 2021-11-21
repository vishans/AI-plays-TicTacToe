

#include "Header.h"



//Board definition

void Board::initEncoding()
{
	ENCODING[0] = '-';
	ENCODING[1] = 'O';
	ENCODING[2] = 'X';



}

char Board::encode(int symbol) {
	return ENCODING[symbol];
}

void Board::initGrid() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			grid[i][j] = 0;
		}

	}
}

std::vector<int> Board::getAvailableMove()
{
	std::vector<int> av_moves;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (grid[i][j] == 0) {
				av_moves.push_back((i * 3) + j + 1);
			}
		}
	}
	return av_moves;
}


bool Board::Modify(int move, int symbol)
{

	std::vector<int> av_move = getAvailableMove();
	if (std::find(av_move.begin(), av_move.end(), move) == av_move.end()) {
		return false;
	}

	move --;
	//number_of_available_moves--;
	int row = move == 0 ? 0: floor(move / 3);
	int col = move % 3;
	//std::cout << row << "," << col << std::endl;
	this->grid[row][col] = symbol;
	return true;

	
}

void Board::showBoard() {
	char symbol;
	const char* strcol;
	const char* endcol;

	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			
			strcol = "";
			endcol = "";

			if (grid[i][j] == 0) {
				symbol =  (i*3)+j +1 + '0';
			}
			else 
			{
				symbol = ENCODING[grid[i][j]];

				if (ANSIcolorOutput) {
					endcol = "\033[0m";
					if (symbol == 'X') {
						strcol = "\033[31;1m"; //red and increased intensity

					}
					else { //symbol is O
						strcol = "\033[32;1m";//green and increased intensity
					}
				}
			}




			std::cout<< strcol  << symbol << endcol;
			if (j < 2) {
				std::cout << " | ";
			}

		}
		std::cout << std::endl;
	}
	}

Board::Board()
{
	initGrid();
	initEncoding();
	//grid[0][0] = 2;
	//grid[1][1] = 1;
	ANSIcolorOutput = true;

}

int Board::check() {

	/*for (int i = 0; i < 3; i++) {
		
		for (int j = 0; j < 3; j++) {
			std::cout << grid[i][j] << " | ";
			

		}
		std::cout << std::endl;
	}*/

	for (int symbol = 1; symbol < 3; symbol++) {
		//bool win = false;
		int cum_count = 0;
		int i,j;
		i = 0;
		j = 0;
		//int lim = 0;

		
		while (i < 3 && cum_count < 3) {
			cum_count = 0;
			j = 0;
			while (j < 3) {
				if (grid[i][j] == symbol) 
				{
					cum_count++;
				}
				else 
				{
					break;
				}

				j++;
			}
			i++;
		}
		
		i = 0;
		while (i < 3 && cum_count < 3) {
			cum_count = 0;
			j = 0;
			while (j < 3) {
				if (grid[j][i] == symbol)
				{
					cum_count++;
				}
				else
				{
					break;
				}

				j++;
			}
			i++;
		}
		


		if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol && cum_count < 3) {
			cum_count = 3;

		}
		else if (grid[2][0] == symbol && grid[1][1] == symbol && grid[0][2] == symbol && cum_count < 3) {
			cum_count = 3;
		}


		if (cum_count == 3){
			return symbol;
		}

	}

	return 0;

}

bool Board::isGameFull(void) {
	return helper_count() == 0;
}

int Board::helper_count() const { //counts how many empty slots there are in the grid
	                              // an empty slot has value 0
	int count = 0;
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) if (grid[i][j] == 0) ++count;

	return count;
}

void Board::swap_player_characters() {
	char temp = ENCODING[1];
	ENCODING[1] = ENCODING[2];
	ENCODING[2] = temp;
}

void Board::switchANSIcolorOutput(void) {

	ANSIcolorOutput = !ANSIcolorOutput;
}

bool  Board::getANSIcolorOutput() {
	return ANSIcolorOutput;
}


//Player 

Player::Player(int symbol) {
	this->symbol = symbol;
}

int Player::getSymbol() {
	return symbol;
}


//Human

Human::Human(int symbol): Player(symbol) {
	
}

void Human::promptMove(Board& game) {

	int move_entered;
	while (true) {
		std::cout << "Enter move: ";
		std::cin >> move_entered;
		//std::cout << getSymbol();
		if (game.Modify(move_entered,this->getSymbol()))
		{
			//std::cout << "SUCESS" << std::endl;
			break;
		}
		else 
		{
			std::cout << "Illegal move. Please enter again." << std::endl;
		}

	}

}


//Machine



Machine::Machine(int symbol) : Player(symbol) {

}

void Machine::randomMove(Board& game) {

	std::random_device rd;
	std::uniform_int_distribution<int> RandInt(1, 9);

	std::vector<int>availble_moves = game.getAvailableMove();
	int Ranmove = RandInt(rd);


	while (true) {

		if (std::find(availble_moves.begin(), availble_moves.end(),Ranmove ) != availble_moves.end()) {
			/* contains move */
			break;
		}
		else {
			/* contain move / occupied */
			Ranmove = RandInt(rd);
		}

	}

	game.Modify(Ranmove, this->getSymbol());



}

tuple Machine::smartMove(Board game, bool maxmizingPlayer,
	int alpha, int beta, int move) 
{
	//std::cout << "here" << std::endl;

	int score = -1;
	int verdict = game.check();
	int h_count = game.helper_count();

	if (h_count == 0) {
		score = 0;
		return tuple{ move,score };
	}



	if (verdict == 1) {
		score = h_count + 1;
		return tuple{ move, score };


	}
	else if (verdict == 2) 
	{
		score = (h_count * -1) + 1;
		return tuple{ move, score };

	}
	
	
	if (maxmizingPlayer) {

		int bestMove = -1;
		int maxEval = -10;
		std::vector<int> possible_move = game.getAvailableMove();

		for (int m : possible_move) {

			Board game_copy = game;
			game_copy.Modify(m, 1);

			tuple result = smartMove(game_copy, false, alpha, beta, m);

			if (result.score > maxEval) {
				maxEval = result.score;
				bestMove = m;
			}

			if (result.score > alpha) {
				alpha = result.score;
			}

			if (beta <= alpha) {
				break;
			}
		}

		return tuple{ bestMove, maxEval };

	}
	else {

		int bestMove = -1;
		int minEval = 10;
		std::vector<int> possible_move = game.getAvailableMove();

		for (int m : possible_move) {

			Board game_copy = game;
			game_copy.Modify(m, 2);

			tuple result = smartMove(game_copy, true, alpha, beta, m);

			if (result.score < minEval) {
				minEval = result.score;
				bestMove = m;
			}

			if (result.score < beta) {
				beta = result.score;
			}

			if (beta <= alpha) {
				break;
			}
		}

		return tuple{ bestMove, minEval };

	}
}


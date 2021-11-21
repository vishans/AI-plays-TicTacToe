#pragma once
#include <iostream>
#include <unordered_map>
#include <math.h> // floor
#include <vector>
#include <algorithm>  // std::find 
#include <random>

struct tuple {  // data stucture used to return minimax's result
	int move;
	int score;

	tuple(int m, int s):move(m), score(s){}
};

class Board {

private:
	
	std::unordered_map <int, char> ENCODING; //specifies the encoding of characters
	                                         //for example int value 2 will be rendered as "X"
											// when printing the game on the terminal

	void initEncoding(); // initializes the ENCODING hash map
						// by default the encoding is as follows
						// 1 -> "O"
						// 2 -> "X"
						// 0 -> "-"


	void initGrid(); //populate the grid with 0, zero represents empty slots

	bool ANSIcolorOutput; //flag stating if ANSI color code can be used. If the terminal/console 
						 // does not support the ANSI color code, the flag should be false
	                     //the method getANSIcolorOutput returns a bool stating the state of the variable
						//the method switchANSIcolorOutput switches the state of the flag i.e ANSIcolorOutput = !ANSIcolorOutput

						//By default ANSIcolorOutput is set to true



public:
	int grid[3][3]; // grid to store game
	bool Modify(int move, int symbol); //plays a symbol in the grid at a specific move
	/*
								1 | 2 | 3
								4 | 5 | 6
								7 | 8 | 9

						Board.Modify(9,2) results in:

						(By default the symbol for X is 2, see ENCODING)

								1 | 2 | 3
								4 | 5 | 6
								7 | 8 | X
	
	
	
	
	*/
										
	Board();
	void showBoard(); // prints the board to the terminal

	std::vector<int> getAvailableMove(); //returns a vector of all available moves

	int check(); //check if someone won, if it is the case returns the player's symbol else returns 0
				//for example if X win, returns 2


	char encode(int symbol); //returns the character of the corresponding encoding
	
	bool isGameFull(void); //check if grid is full
	

	int helper_count() const ; // returns a count of available moves in the grid
							//in other words count empty slots
	                        // used in the move evaluating function in minimax

	void swap_player_characters(); // make O's symbol becomes X's and vice-versa

	void switchANSIcolorOutput(void); //see ENCODING section

	bool getANSIcolorOutput();
	

};


class Player {

protected:
	int symbol;  // player's symbol




public:
	


	Player(int symbol);

	int getSymbol();


};



class Human : public Player {

public:
	Human(int symbol);

	void promptMove(Board& game); //prompts player to make a move
								//only int range validation is implemented
};


class Machine : public Player {

public:

	Machine(int symbol);

	void randomMove(Board &game);


	tuple smartMove(Board game, bool maxmizingPlayer,
		int alpha, int beta, int move); //minimax algorithm


	
};


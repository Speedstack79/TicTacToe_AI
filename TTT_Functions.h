#ifndef TTT_FUNCTIONS_H_INCLUDED
#define TTT_FUNCTIONS_H_INCLUDED
#include <iostream>
#include <climits>
#define SIZE 3
class TicTacToe
{
public:
	/**
	*	The constructor of the class. Initialized the variables.
	*	@params: 
	*	@return:
	*/
    TicTacToe ();
	
	/**
	*	Destructor of the class.
	*	@params: 
	*	@return:
	*/
	~TicTacToe ();
	
	/**
	*	Says if there is any valid turns left on tbe board.
	*	@params: 
	*	@return:
	*/
    bool any_turns ();
	
	/**
	*	The functions that starts a game.
	*	@params: 
	*	@return:
	*/
	void begin_game();
	
	/**
	*	An evaluation function that gives the board a numerical score.
	*	@params: 
	*	@return: 10 if the computer has won a game, -10 if the computer has lost a game, 0 if it is a tie.
	*/
	int board_score();
	
	/**
	*	The minimax algorithm that decides the best move the computer can do.
	*	@params: How deep into the recursoin the algorithm is (used to decide which move is better
	*	if 2 moves have the same board score. Also a boolean value that says if it is the computers turn.
	*	@return: An integer returning the board score that is used to recursively decide the best move.
	*/
	int minimax (int level, bool max);
	
	/**
	*	Uses the minimax algorithm to find the best move and put that move on the board.
	*	@params: 
	*	@return:
	*/
	void opti_move ();
	
	/**
	*	Asks the user if s/he would like to play again and does appropriate actions.
	*	@params: 
	*	@return:
	*/
	void prompt_replay();
	
	/**
    *	Will print the board.
    *	@params:
    *	@return:
    */
    void print_board ();
	
	/**
	*	Reset the moves on the baord to the empty state.
	*	@params: 
	*	@return:
	*/
    void reset_board ();	
	
	/**
	*	Set the current col and row variables to the move to be set. Coordinates are 0-indxed.
	*	@params: Two unsigned integers representing the col and row (coordinates).
	*	@return: True if the coordinates to be set is valid, false if not.
	*/
	bool set_pos (unsigned int col, unsigned int row); 
	
	/**
	*	Uses the current values of col and row to put a character on the board.
	*	@params: 
	*	@return:
	*/
	void set_tic (bool computer);
	
	/**
	*	Uses the board_score() function to check if the computer has won or tied against the human.
	*	@params: 
	*	@return:
	*/
	void winner ();
private:
    char board[SIZE][SIZE];
	char computer;
	char human;
    unsigned int col;
    unsigned int row;
};

#endif // TTT_FUNCTIONS_H_INCLUDED

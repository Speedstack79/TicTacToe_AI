#include "TTT_Functions.h"
//position functions such that the order is the same as the order in the header file
TicTacToe::TicTacToe ()
{
	//'~' is the empty state of a slot
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        for (unsigned int j = 0; j < SIZE; ++j)
        {
            board[i][j] = '~';
        }
    }
	computer = 'O';
	human = 'X';
	row = col = 4;
    std::cout << "Board initialized. You are 'X'. Computer is 'O'." << std::endl;
}

TicTacToe::~TicTacToe ()
{
	std::cout << "Exiting game.\n";
}

bool TicTacToe::any_turns ()
{
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		for (unsigned int j = 0; j < SIZE; ++j)
			if (board[i][j] == '~')
			{
				return true;
			}
	}
	return false;
}

void TicTacToe::begin_game()
{
	bool computer_turn = false;
	char c;
	//if user enters invalid input, just default to false...
	std::cout << "Do you want to go first? ('n' for no)\n";
	std::cin >> c;
	if (c == 'n')
	{
		computer_turn = true;
	}
	else computer_turn = false;
	std::cout << "Enter a valid 0-based index coordinate in the form of \"col row\"" << std::endl;
	while (any_turns() && board_score() == 0)
	{	
		std::cout << "\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n" << std::endl;
		std::cout << (computer_turn ? "You did: \n" : "Computer did: \n");
		print_board();
		if (!computer_turn)
		{
			int col, row;
			std::cout << "Coordinates: ";
			std::cin >> col >> row;
			//error checking if user enters non-integer
			while (std::cin.fail())
			{
				std::cout << "Coordinates entered are not integers!\n";
				std::cout << "Coordinates: ";
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> col >> row;
			}
			if (!set_pos(col, row))
			{
				std::cout << "Position in board already in use, or invalid coordinates. Try again!\n";
				computer_turn = false;
				continue;
			}
			set_tic(false);
			computer_turn = true;
		}
		else
		{
			opti_move();
			computer_turn = false;
		}
	}
	std::cout << "------------\n";
	print_board();
	winner();
	prompt_replay();
}

//board evaluation function
int TicTacToe::board_score()
{
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		if (board[i][0] == board[i][1] 
		&&  board[i][1] == board[i][2])
		{
			if (board[i][0] == computer)
			{
				return 10;
			}
			else if (board[i][0] == human)
			{
				return -10;
			}
		}
		else if (board[0][i] == board[1][i]
			&&   board[1][i] == board[2][i])
			{
				if (board[0][i] == computer)
				{
					return 10;
				}
				else if (board[0][i] == human)
				{
					return -10;
				}
				
			}
		else if (board[0][0] == board[1][1] 
			&&   board[1][1] == board[2][2])
			{
				if (board[0][0] == computer)
				{
					return 10;
				}
				else if (board[0][0] == human)
				{
					return -10;
				}
			}
		else if (board[0][2] == board[1][1]
			&&   board[1][1] == board[2][0])
			{
				if (board[0][2] == computer)
				{
					return 10;
				}
				else if (board[0][2] == human)
				{
					return -10;
				}
			}
	}
	return 0;
}

//the minimax algorithm
int TicTacToe::minimax (int level, bool max)
{
	//check for win/lost first because not having any turns left doesn't mean a win/lose
	if (board_score() == 10)
	{
		return 10;
	}
	if (board_score() == -10)
	{
		return -10;
	}
	if (!any_turns())
	{
		return 0;
	}
	if (max)
	{		
		int max_score = INT_MIN;
		for (unsigned int i = 0; i < SIZE; ++i)
		{
			for (unsigned int j = 0; j < SIZE; ++j)
			{
				if (board[i][j] == '~')
				{
					board[i][j] = computer;
					int mm_result = minimax(level + 1, !max);
					max_score = (max_score > mm_result) ? max_score : mm_result;
					board[i][j] = '~';
				}
			}
		}
		return max_score;
	}
	else
	{
		int min_score = INT_MAX;
		for (unsigned int i = 0; i < SIZE; ++i)
		{
			for (unsigned int j = 0; j < SIZE; ++j)
			{
				if (board[i][j] == '~')
				{
					board[i][j] = human;
					int mm_result = minimax(level - 1, !max);
					min_score = (min_score < mm_result) ? min_score : mm_result;
					board[i][j] = '~';
				}
			}
		}
		return min_score;
	}
}

void TicTacToe::opti_move()
{
	int max_score = INT_MIN;
	set_pos(4, 4); //4 is sentinel value
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		for (unsigned int j = 0; j < SIZE; ++j)
		{
			if (board[i][j] == '~')
			{
				board[i][j] = computer;
				int temp_val = minimax(0, false); //
				board[i][j] = '~';
				if (temp_val > max_score)
				{
					set_pos(i, j);
					max_score = temp_val;
				}
			}
		}
	}
	set_tic(true); //true means it is the computer's turn
}

void TicTacToe::prompt_replay ()
{
	char c;
	std::cout << "Would you like to play again?('y' for yes)\n";
	std::cin >> c;
	if (c == 'y')
	{
		reset_board();
		begin_game();
	}
}

void TicTacToe::print_board ()
{
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        for (unsigned int j = 0; j < SIZE; ++j)
        {
            std::cout << board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void TicTacToe::reset_board()
{
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		for (unsigned int j = 0; j < SIZE; ++j)
		{
			board[i][j] = '~';
		}
	}
}

bool TicTacToe::set_pos(unsigned int col, unsigned int row)
{
	if (col >= 0 && col <= 2 && row >= 0 && row <=2 && board[col][row] == '~')
	{
		this->col = col;
		this->row = row;
		return true;
	}
	return false;
}

void TicTacToe::set_tic (bool computer)
{
	if (col >= 0 && col <= 2 && row >= 0 && row <= 2)
	{
		board[col][row] = computer ? this->computer : human;
	}
}

void TicTacToe::winner()
{
	switch (board_score())
	{
		case (10):
			std::cout << "Computer won!\n";
			break;
		case (0):
			std::cout << "Tie!\n";
			break;
		default: //default won't happen because this is perfect code
			std::cout << "How?\n";
			break;
	}
}
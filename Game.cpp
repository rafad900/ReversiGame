/*****************************************************************************/
/*								             */
/*                                                      		     */
/* Date: 10/16/18                                                            */        
/* Description:                                                              */
/*                                                                           */
/*****************************************************************************/

#include "Game.h"
#include <iomanip>
#include <stdlib.h>
#include <ctime>

/*****************************************************************************/
/*                                                                           */
/* Function: Cell()				                             */ 
/* Input parameters: NONE                                                    */ 
/* Return value: NONE                                                        */ 
/* Description:  Default constructor for the Cell type.                      */
/*                                                                           */
/*****************************************************************************/

Game::Cell::Cell ()
{
	owner = NONE;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Display () 						     */ 
/* Input parameters: Output Stream                                           */ 
/* Return value: NONE                                                        */ 
/* Description: Prints out the player character for the game.                */
/*                                                                           */
/*****************************************************************************/

void Game::Cell::Display (ostream & outs)
{
	char symbols []  {' ', 'X', 'O'};
	outs << symbols[owner];
}

/*****************************************************************************/
/*                                                                           */
/* Function: Game()                                                          */ 
/* Input parameters:NONE                                                     */ 
/* Return value:NONE                                                         */ 
/* Description: Default constructor for the Game object.                     */
/*                                                                           */
/*****************************************************************************/

Game::Game ()
{
        score[0] = 0;
	score[HUMAN] = 0;
	score[COMPUTER] = 0;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Instructions()                                                  */ 
/* Input parameters: Output Stream                                           */ 
/* Return value:NONE                                                         */ 
/* Description: Prints out the instructions for the game.                    */
/*                                                                           */
/*****************************************************************************/

void Game::Instructions (ostream & outs)
{
	outs << "Welcome to My Game of Reversi/Othello" << endl << endl;
	outs << "This game is played on a square (usually 8x8) grid of cells. Each player takes turns placing" << endl;
	outs << "their symbols (in this case 'X' and 'O') on the board and in a manner that claims a cell" << endl;
	outs << "The cell that they choose must flank an opponanats piece and be able to take it over when making the move. \nThe pieces can move vertically, horizontaly, and diagonally." << endl;
	outs << "The game starts with 4 pieces, 2 for one player and 2 for the other. They are in a diagonal pattern \nand the X is the first to make a move." << endl;
	outs << "Once the board is failled or there are no more valid moves left, or there are only one kind of piece \nleft then the game is over and the winner is declared." << endl << endl << endl;
	
}

/*****************************************************************************/
/*                                                                           */
/* Function: Init()                                                          */ 
/* Input parameters:NONE                                                     */ 
/* Return value:NONE                                                         */ 
/* Description: Sets the initial pieces on the board.                        */
/*                                                                           */
/*****************************************************************************/

void Game::Init ()
{
	Cell cell;
	for (int r = 1; r <= ROWS; r++)
		for (int c = 1; c <= COLS; c++)
			board[r][c] = cell;
	board[ROWS/2][COLS/2].owner = COMPUTER;
	board[ROWS/2][COLS/2+1].owner = HUMAN;
	board[ROWS/2+1][COLS/2].owner = HUMAN;
	board[ROWS/2+1][COLS/2+1].owner = COMPUTER;
	score[HUMAN] = 2;
	score[COMPUTER] = 2;
}

/*****************************************************************************/
/*                                                                           */
/* Function:Display()                                                        */ 
/* Input parameters: output stream                                           */ 
/* Return value: NONE                                                        */ 
/* Description: Displays the board to the screen with the currect values.    */
/*                                                                           */
/*****************************************************************************/

void Game::Display (ostream & outs)
{
	outs << "My Game!" << endl;
	outs << "Scores\tHUMAN: " << score[HUMAN] << ";\tCOMPUTER: " << score[COMPUTER] << endl;

	cout << "    A   B   C   D   E   F   G   H  " << endl;

	for (int r = 1; r <= ROWS; r++)
	{
		cout << "  +---+---+---+---+---+---+---+---+" << endl;	
		cout << r << " ";
		for (int c = 1; c <= COLS; c++)
		{
			cout << "| ";
			board[r][c].Display(outs);
			cout << " ";
		}
		cout << "| " << r;
		outs << endl;
	}
		cout << "  +---+---+---+---+---+---+---+---+" << endl;
	cout << "    A   B   C   D   E   F   G   H  " << endl;
}

/*****************************************************************************/
/*                                                                           */
/* Function: CheckBoard()                                                    */ 
/* Input parameters: playerType                                              */ 
/* Return value: Boolean value                                               */ 
/* Description: Checks the boerd for any valid moves left for either player  */
/*                                                                           */
/*****************************************************************************/

bool Game::CheckBoard (playerType Who)
{
	for (int r = 1; r <= 9; r++) 
	{
		for (int c = 1; c <= 9; c++)
		{
			if (ValidMove(Who, r, c, false))
				return true;
			continue;
		}
	}
	return false;
}


/*****************************************************************************/
/*                                                                           */
/* Function: ValidMove()                                                     */ 
/* Input parameters: PlayerType, Row, Col                                    */ 
/* Return value: Boolean value                                               */ 
/* Description: Checks if the coordinateds passed are valid in the board     */
/*                                                                           */
/*****************************************************************************/

bool Game::ValidMove (playerType Who, int Row, int Col, bool setBool)
{
	bool whatisit;
	playerType Other = Who == HUMAN ? COMPUTER : HUMAN;

	if (board[Row][Col].owner != NONE) 
	{
		whatisit = false;
	} else {
		for (int i = 0; i < 9; i++) 
		{
			enemies = 0;
			r = pos[i][0];
			c = pos[i][1];
			while (board[Row+r][Col+c].owner == Other) 
			{
				enemies++;
				r += pos[i][0];
				c += pos[i][1];
			}
			if (board[Row+r][Col+c].owner == Who && enemies > 0)
			{
				while (true)
				{
					if (r != 0)
					{
						if (r < 0)
							r-=1;
						else 
							r+=1;
					}
					if (c != 0)
					{
						if (c < 0)
							c-=1;
						else 
							c+=1;
					}
					if (setBool) 
						board[Row+r][Col+c].isValid = true;
					if (r == 0 && c == 0) 
					{
						if (setBool)
							board[Row][Col].isValid = true; 
						enemies = 0;
						break;
					}
				}
				whatisit = true;
			}
		}
	}
	return whatisit;				
}

/*****************************************************************************/
/*                                                                           */
/* Function: MakeMove()                                                      */ 
/* Input parameters: PlayerType, Row, Col                                    */ 
/* Return value: NONE                                                        */ 
/* Description:						                     */
/*                                                                           */
/*****************************************************************************/

void Game::MakeMove (playerType Who, int Row, int Col)
{
	playerType Other = Who == HUMAN ? COMPUTER : HUMAN;

	for (int i = 1; i < 9; i++) 
	{
		for (int j = 1; j < 9; j++) 
		{
			if (board[i][j].isValid == true) 
			{
				board[i][j].owner = Who;
				score[Who]++;
				score[Other]--; 
			}
				
		}
	}
	score[Other]++;
}

/*****************************************************************************/
/*                                                                           */
/* Function:ChooseMove()                                                     */ 
/* Input parameters: PlayerType, row, col, input stream, output stream       */ 
/* Return value: Boolean Value						     */ 
/* Description:  Prompt user for location of move                            */
/*                                                                           */
/*****************************************************************************/

bool Game::ChooseMove (playerType Who, int & Row, int & Col, istream & In, ostream & Out)
{
  if (!(CheckBoard(Who)))
	return false;
  string player = "";
  string pla = "";
  if (Who == HUMAN) {
    	player = "X";
    	pla = "HUMAN";
  } else {
    	player = "O";
    	pla = "COMPUTER";
  }
  char C = ' ';
  Out << "Current player is: " << pla << " " << player << endl;
	Out << "Please enter your move:" << endl;
	Out << "Row: ";
	In >> Row;
	Out << "Col: ";
	In >> C;
	while (!(isalpha(C)))
	{
  		Out << "Please enter a letter for the column: ";
	    	In >> C;
	}
	Col = toupper(C) - 64;
	while (!(ValidMove(Who, Row, Col, false))) {
		  Row = 0;
		  C = ' ';
		  Col = 0;
	  	  Out << "Invalid move, try again." << endl;
	  	  Out << "Please enter your move:" << endl;
		  Out << "Row: ";
		  In >> Row;
		  Out << "Col: ";
		  In >> C;
		  while (!(isalpha(C)))
	    	  {
	    	  	Out << "Please enter a letter for the column2: ";
	          	In >> C;
	    	  }
	 	 Col = toupper(C) - 64;
	}
	ValidMove(Who, Row, Col, true);
	return true;
}

/*****************************************************************************/
/*                                                                           */
/* Function: ChooseMove()                                                    */ 
/* Input parameters: PlayerType, row, col                                    */ 
/* Return value: Boolean Value                                               */ 
/* Description: AI determines desired location of move                       */
/*                                                                           */
/*****************************************************************************/

bool Game::ChooseMove (playerType Who, int & Row, int & Col)
{	
	if (!(CheckBoard(Who)))
		return false;
	srand(time(0));
	int r = rand() % 7 + 1;
	int c = rand() % 7 + 1;
	while (!(ValidMove(Who, r, c, false)))
	{
		r = rand() % 7 + 1;
		c = rand() % 7 + 1;
	}
	ValidMove(Who, r, c, true);
	return true;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Done()                                                          */ 
/* Input parameters:NONE                                                     */ 
/* Return value: Boolean Value                                               */ 
/* Description: Checks to see if there are no more moves for either player   */
/*                                                                           */
/*****************************************************************************/

bool Game::Done ()
{
	if (score[HUMAN] == 0 || score[COMPUTER] == 0)
		return true;
	if (CheckBoard(HUMAN) == false || CheckBoard(COMPUTER) == false) 
		return true;
	return false;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Winner()                                                        */ 
/* Input parameters: Output strea					     */ 
/* Return value: playerType                                                  */ 
/* Description: Prints out the winner of the game with their score.          */
/*                                                                           */
/*****************************************************************************/

playerType Game::Winner (ostream & outs)
{
	playerType winner = NONE;
		if (score[HUMAN] > score[COMPUTER])
		{
			playerType winner = HUMAN;
			outs << "\nPlayer HUMAN won! Score: " << score[HUMAN] << endl;
		} else if (score[HUMAN] < score[COMPUTER])
		{
			playerType winner = COMPUTER;
			outs << "\nPlayer COMPUTER won! Score: " << score[COMPUTER] << endl;
		}
	return winner;
}

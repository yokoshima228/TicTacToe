#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define BOARDSIZE 9
using namespace std;

class Board
{
public:
	Board();
	char whoWin() const;
	char whoWin(const char board[]);
	void PrintBoard() const;
	void PrintBoard(bool rules) const;
public:
	char board[BOARDSIZE];
	void setBoard(const int index, const char Piece);
private:
	void LoadBoard();
};

Board::Board()
{
	LoadBoard();
}

inline char Board::whoWin(const char board[])
{
	char winner;
	bool haveSpaces = false;

	for (int i = 0; i < BOARDSIZE; i += 3)
	{
		if (board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != ' ')
		{
			return board[i];
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ')
		{
			return board[i];
		}
	}

	if (board[0] == board[4] && board[0] == board[8] && board[0] != ' ')
	{
		return board[0];
	}

	if (board[2] == board[4] && board[2] == board[6] && board[2] != ' ')
	{
		return board[2];
	}

	for (int i = 0; i < BOARDSIZE; ++i)
	{
		haveSpaces = true;
	}

	if (!haveSpaces)
	{
		return 'D';
	}
	return 'C';
}

inline void Board::setBoard(const int index, const char Piece)
{
	this->board[index] = Piece;
}

inline void Board::PrintBoard() const
{
	for (int i = 0; i < BOARDSIZE; i += 3)
	{
		cout << board[i] << " | ";
		cout << board[i + 1] << " | ";
		cout << board[i + 2] << endl;
		cout << "---------\n";
	}
	cout << "\n\n";
}

inline void Board::PrintBoard(bool rules) const
{
	for (int i = 0; i < BOARDSIZE; i += 3)
	{
		cout << i << " | ";
		cout << i + 1 << " | ";
		cout << i + 2 << endl;
		cout << "---------\n";
	}
	cout << "\n\n";
}

inline void Board::LoadBoard()
{
	for (int i = 0; i < BOARDSIZE; ++i)
	{
		board[i] = ' ';
	}
}

inline char Board::whoWin() const
{
	char winner;
	bool haveSpaces = false;

	for (int i = 0; i < BOARDSIZE; i += 3)
	{
		if (board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != ' ')
		{
			return board[i];
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ')
		{
			return board[i];
		}
	}

	if (board[0] == board[4] && board[0] == board[8] && board[0] != ' ')
	{
		return board[0];
	}

	if (board[2] == board[4] && board[2] == board[6] && board[2] != ' ')
	{
		return board[2];
	}

	for (int i = 0; i < BOARDSIZE; ++i)
	{
		haveSpaces = true;
	}

	if (!haveSpaces)
	{
		return 'D';
	}
	return 'C';
}

class Player
{
public:
	Player();
	void MakeMove(Board& gameBoard);
	void SetName(const string& newName);
	void DefinePiece();
	char getPiece() const;
public:
	char Piece;
	string name;
};

Player::Player()
{
	cout << "Enter your name: ";
	string name;
	cin >> name;

	SetName(name);
}

inline char Player::getPiece() const
{
	return this->Piece;
}

inline void Player::SetName(const string& newName)
{
	name = newName;
}

inline void Player::DefinePiece()
{
	char choice;
	do
	{
		cout << name << " вы хотите играть крестиками? (y/n): ";
		cin >> choice;
	} while (tolower(choice) != 'y' && tolower(choice) != 'n');

	if (tolower(choice) == 'y')
	{
		Piece = 'X';
	}
	else
	{
		Piece = 'O';
	}
}

inline bool canMove(const int index)
{
	if (index >= 0 && index < BOARDSIZE)
	{
		return true;
	}
	return false;
}

inline void Player::MakeMove(Board& gameBoard)
{
	int index;
	do
	{
		cout << "Введите клетку куда вы хотите сделать ход: ";
		cin >> index;
	} while (!canMove(index) || gameBoard.board[index] != ' ');

	gameBoard.setBoard(index, this->Piece);
}

class Computer
{
public:
	Computer(Board& board, const char opponentPiece);
	void MakeMove(char opponentPiece, Board& board);
	char getPiece() const;
private:
	char cpyBoard[BOARDSIZE];
	void FillCpy(Board& board);
	bool isLegal(int index, Board& board);
	char Piece;
	//void DefinePiece(char opponentPiece);
};

Computer::Computer(Board& board, const char opponentPiece)
{
	FillCpy(board);
	Piece = 'O';
}

inline char Computer::getPiece() const
{
	return this->Piece;
}

inline bool Computer::isLegal(int index, Board& board)
{
	if (index >= 0 && index < BOARDSIZE)
	{
		if (board.board[index] == ' ')
		{
			return true;
		}
	}
	return true;
}

inline void Computer::FillCpy(Board& board)
{
	for (int i = 0; i < BOARDSIZE; ++i)
	{
		cpyBoard[i] = board.board[i];
	}
}

inline void Computer::MakeMove(const char opponentPiece, Board& board)
{
	int move = 0;
	while (move < BOARDSIZE)
	{
		if (isLegal(move, board))
		{
			cpyBoard[move] = this->Piece;

			if (board.whoWin(cpyBoard) == this->Piece && board.board[move] == ' ')
			{
				board.board[move] = this->Piece;
				return;
			}
			FillCpy(board);
			move++;
		}
	}

	move = 0;
	while (move < BOARDSIZE)
	{
		if (isLegal(move, board))
		{
			cpyBoard[move] = opponentPiece;

			if (board.whoWin() == opponentPiece && board.board[move] == ' ')
			{
				board.board[move] = this->Piece;
				return;
			}
			FillCpy(board);
			move++;
		}
	}

	move = 0;
	int prioritetes[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
	for (int i = 0; i < BOARDSIZE; ++i)
	{
		if (isLegal(prioritetes[i], board) && board.board[prioritetes[i]] == ' ')
		{
			board.board[prioritetes[i]] = this->Piece;
			return;
		}
	}
}

int main()
{
	Board board = Board();
	Player player = Player();
	Computer computer = Computer(board, player.getPiece());
	player.DefinePiece();
	do
	{
		player.MakeMove(board);
		computer.MakeMove(player.getPiece(), board);
		board.PrintBoard();
	} while (board.whoWin() == 'C');

	if (board.whoWin() == 'X')
	{
		cout << "You won! Congragulations!\n";
	}
	else
	{
		cout << "You lose. Nice try.\n";
	}
	return 0;
}
// Программа Крестики-нолики
// Компьютер играет в "Крестики-нолики" против пользователя
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// глобальные константы
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
//Прототипы функций
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

// Функция main
int main()
{
	setlocale(0, "");
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	displayBoard(board);
	while (winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}
	announceWinner(winner(board), computer, human);
	return 0;
}

// Функция announceWinner
void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << "'s won!\n";
		cout << "As I predicted. human. I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (winner == human)
	{
		cout << winner << "'s won!\n";
		cout << "No. nо! It cannot bе! Somehow you tricked me. human. \n";
		cout << "But never again! I. the computer. so swear it!\n";
	}
	else
	{
		cout << "It's а tie.\n";
		cout << "You were most lucky. human. and somehow managed to tie me.\n";
		cout << "Celebrate ... for this is the best you will ever achieve.\n";
	}
}

// Функция computerMove()
int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	// если компьютер может выиграть следующим ходом.то он делает этот ход
	while (move < board.size() && !found)
	{
		if (isLegal(board, move))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
	}
	// иначе, если человек может победить следующим ходом, блокировать этот ход if (!found)
	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size())
		{
			if (isLegal(board, move))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found)
			{
				++move;
			}
		}
	}
	// иначе занять следующим ходом оптимальную свободную клетку
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4,0,2,6,8,1,3,5,7 };
		while (i < board.size() && !found)
		{
			move = BEST_MOVES[i];
			if (isLegal(board, move))
			{
				found = true;
			}
			++i;
		}
	}
	cout << "I shall take square number " << move << endl;
	return move;
}

// Функция humanMove(const vector<char>& board, int human)
int humanMove(const vector<char>& board, char human)
{
	int EasterEgg = 0;
	int move = askNumber("Where will you move?",(board.size() - 1),0);
	while (!isLegal(board, move))
	{
		cout << "\That square is already occupied. foolish human.\n";
		EasterEgg++;
		if (EasterEgg >= 10)
		{
			cout << "\n\n\n";
			cout << "                  Screamer                 ";
			cout << "\n\n\n";
		}
		move = askNumber("Where will you move?", (board.size() - 1), 0);
	}
	cout << "Fine...\n";
	return move;
}

// Функия isLegal(const vector<char>& board, int move)
bool isLegal(const vector<char>& board, int move)
{
	return (board[move] == EMPTY);
}

//winer()
char winner(const vector<char>& board)
{
	// все возможные выигрышние ряды
	const int WINNING_ROWS[8][3] =
	{
		{0,1,2},
		{3,4,5},
		{6,7,8},
		{0,3,6},
		{1,4,7},
		{2,5,8},
		{0,4,8},
		{2,4,6},
	};
	const int TOTAL_ROWS = 8;
	// если в одном из выигрышных рядов уже присутствуют три одинаковых значения
	// (причем они не равны ЕМРТУ).то победитель определился
	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) && 
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}
	// поскольку победитель не определился.проверяем.не наступила ли ничья
	// (остались ли на поле пустые клетки)
	if (count(board.begin(), board.end(), EMPTY) == 0)
	{
		return TIE;
	}
	else
	{
		// Поскольку победитель не определился.но и ничья еще не наступила.
		// игра продолжается
		return NO_ONE;
	}
}

//Функция displayBoard(const vector<char>& board)
void displayBoard(const vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

//функция opponent(char piece);
char opponent(char piece)
{
	if (piece == X) 
	{
		return O;
	}
	else
	{
		return X;
	}
}

// Функция humanPiece
char humanPiece()
{
	char go_first = askYesNo("Do you require the first move?\n");
	if (go_first == 'y')
	{
		cout << "\nThen take the first move.You will need it.\n";
		return X;
	}
	else
	{
		cout << "\nYour bravery will bе your undoing ... I will go first.\n";
		return O;
	}
}

// Функция askNumber
int askNumber(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number <low);
	return number;
}

// Функция askYesNo
char askYesNo(string question)
{
	char responce;
	do
	{
		cout << question << " (y/n): ";
		cin >> responce;
	} while (responce != 'y' && responce != 'n');
	return responce;
}

// Функция instructions()
void instructions() {
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n"; //Добро пожаловать на финальную битву между человеком и машиной: Крестики-нолики
	cout << "--where human brain is pit against silicon processor\n\n"; //Где человеческий мозг находится под воздействием кремниевого процессора
	cout << "Make your move known bу entering а number. 0 - 8. The number\n"; //Соверши свой ход введя число от 0 до 8
	cout << "corresponds to the desired board position. as illustrated:\n\n"; //Соответствующий желаемой позиции на доске, как иллюстрировано
	cout << " 0 | 1 | 2\n";
	cout << " 3 | 4 | 5\n";
	cout << " 6 | 7 | 8\n\n";
	cout << "Prepare yourself, human. The battle is about to begin.\n\n"; //Готовься, человек. Битва начинается.
}

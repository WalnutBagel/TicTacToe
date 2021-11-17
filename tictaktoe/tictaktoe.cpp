#include <iostream>
#include <clocale>
#include <windows.h>
#include <time.h>
using namespace std;

char field[] = { '-', '-', '-', '-', '-', '-', '-', '-', '-' };

void SetColor(int text, int background)
{
    /* процедура для смены цвета шрифта */
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void printspace(int s) {
    /* для вывода пробелов (для центрирования текста) */
    for (int i = 0; i < s; i++)
        cout << ' ';
}

void printfield() {
    /* выводим игровое поле */
    SetColor(14, 0);
    printspace(60); cout << '-' << field[0] << "-|-" << field[1] << "-|-" << field[2] << "-\n";
    printspace(60); cout << '-' << field[3] << "-|-" << field[4] << "-|-" << field[5] << "-\n";
    printspace(60); cout << '-' << field[6] << "-|-" << field[7] << "-|-" << field[8] << "-\n";
}

void clearfield() {
    /* очищаем поле после каждой игры */
    for (int i = 0; i < 9; i++)
        field[i] = char(i + 49);
}

void clearscreen(int s) {
    for (int i = 0; i < s; i++)
        cout << endl;
}


bool isWinner(char who) {
    if (field[0] == who && field[1] == who && field[2] == who) return true;
    if (field[3] == who && field[4] == who && field[5] == who) return true;
    if (field[6] == who && field[7] == who && field[8] == who) return true;
    if (field[0] == who && field[3] == who && field[6] == who) return true;
    if (field[1] == who && field[4] == who && field[7] == who) return true;
    if (field[2] == who && field[5] == who && field[8] == who) return true;
    if (field[0] == who && field[4] == who && field[8] == who) return true;
    if (field[2] == who && field[4] == who && field[6] == who) return true;
    return false;
}

int botMove() {
    if (field[4] == '5') return 5;
    for (int i = 0; i < 9; i++)
        if (field[i] == char(i + 49)) {
            field[i] = 'O';
            if (isWinner('O'))
                return i + 1;
            else
                field[i] = char(i + 49);

            field[i] = 'X';
            if (isWinner('X'))
                return i + 1;
            else
                field[i] = char(i + 49);
        }
    for (int i = 0; i < 9; i++)
        if (field[i] == char(i + 49))
            return i + 1;
}

void print() {
    system("cls");
    clearscreen(2);
    clearscreen(2);
    printfield();
    clearscreen(1);
}

char play(int h) {
    int turn = 1; // 0 - bot, 1 - player
    int move;
    char a = 'X', b = 'O';
    if (h == 0) swap(a, b);
    while (1) {
        if (turn % 2 == h) {
            print();
            SetColor(12, 0);
            if (turn > 1) {
                printspace(30);
                cout << "Бот поставил " << b << " на " << move << endl;
            }
            printspace(34);
            cout << "Ваш ход:  ";
            cin >> move;
            while (move > 9 || field[move - 1] == 'X' || field[move - 1] == 'O') {
                print();
                SetColor(12, 0);
                printspace(15);
                cout << "** Пожалуйста, введите коректное значение (1-9) **\n";
                printspace(34);
                cout << "Ваш ход:  ";
                cin >> move;
            }
            field[move - 1] = a;
            if (isWinner(a)) {
                print();
                printspace(35);
                for (int i = 0; i < 400000000; i++)
                    if (i % 100000000 == 0) cout << '.';
                SetColor(2, 0);
                cout << "X победил!\n";
                return a;
            }
        }
        else {
            print();
            SetColor(12, 0);
            if (turn > 1) {
                printspace(30);
                cout << "Вы поставили " << a << " на " << move << endl;
            }
            printspace(35); cout << "Бот думает";
            for (int i = 0; i < 600000000; i++)
                if (i % 100000000 == 0) cout << '.';
            cout << endl;
            move = botMove();
            field[move - 1] = b;
            if (isWinner(b)) {
                print();
                printspace(33);
                for (int i = 0; i < 400000000; i++)
                    if (i % 100000000 == 0) cout << '.';
                SetColor(2, 0);
                cout << "О победил!\n";
                return b;
            }
        }
        turn++;
        if (turn == 10) {
            print();
            printspace(33);
            for (int i = 0; i < 400000000; i++)
                if (i % 100000000 == 0) cout << '.';
            SetColor(2, 0);
            cout << "Ничья!\n";
            return 'D';
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int p_wins, b_wins, draws;
    p_wins = b_wins = draws = 0; // статистика
    char choice = 'y';
    int h = 0;
    while (choice == 'y') {
        clearfield();
        char winner;
        h = abs(h - 1);
        winner = play(h);
        if (winner == 'D') draws++;
        if (winner == 'X') {
            if (h == 1) p_wins++;
            else b_wins++;
        }
        if (winner == 'O') {
            if (h == 0) p_wins++;
            else b_wins++;
        }
        SetColor(3, 0);
        printspace(32);
        cout << "Вы выиграли " << p_wins << " раз\n";
        printspace(32);
        cout << "Компьютер выиграл " << b_wins << " раз\n";
        printspace(32);
        cout << "Ничья была " << draws << " раз\n\n";
        SetColor(7, 0);
        printspace(32);
        cout << "Еще? y/n :";
        cin >> choice;
    }
    return 0;
}
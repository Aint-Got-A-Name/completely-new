#include <iostream>
using namespace std;

#include "main.h"
#include "Console.h"
#include "function.h"

short STrang, SViTriChon, STongMuc;

int main()
{
	resizeConsole(ConsoleWidth, ConsoleHeigth);
	SetConsoleTitle(TEXT("MINESWEEPER"));
	Title();
	Cursor(false); // Ẩn con trỏ
	MainMenu(0);
	STrang = 1;
	xuLySuKien();

	cout << endl;
	return 0;
}
#include <stdio.h>
#include <Windows.h>

enum Color
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White,
};

void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);

struct Obj
{
	int x; 
	int y;
	Color color;
	const char* shape;

};


int main()
{
	Obj a;
	a.x = 10;
	a.y = 10;
	a.color = Blue;
	a.shape = "бс";
	
	Obj b;
	b.x = rand() % 35;
	b.y = rand() % 35;
	b.color = Red;
	b.shape = "бс";

	HideCursor();

	while (true)
	{
		system("cls");

		SetTextColor(a.color);
		SetPosition(a.x, a.y);
		printf(a.shape);

		SetTextColor(b.color);
		SetPosition(b.x, b.y);
		printf(b.shape);

		Sleep(50);
	}

	return 0;
}

void SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetTextColor(Color color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
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
	const char* shape1;
	const char* shape2;
	const char* shape3;
};



int main()
{
	Obj obj;
	obj.x = 10;
	obj.y = 10;
	obj.color = White;
	obj.shape1 = "¡á¡á¡á¡á";
	obj.shape2 = "¡á¡á¡á¡á";
	obj.shape3 = "¡á¡á¡á¡á";

	HideCursor();

	while (true)
	{
		system("cls");

		SetTextColor(obj.color);
		SetPosition(obj.x, obj.y);
		printf(obj.shape1);
		SetPosition(obj.x, obj.y + 1);
		printf(obj.shape2);
		SetPosition(obj.x, obj.y +2);
		printf(obj.shape3);

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
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
	const char* shape[3];

};


int main()
{
	Obj a;
	a.x = 10;
	a.y = 10;
	a.color = Blue;
	a.shape[0] = "¡á¡á¡á¡á";
	a.shape[1] = "¡á¡á¡á¡á";
	a.shape[2] = "¡á¡á¡á¡á";
	
	Obj b;
	b.x = rand() % 35;
	b.y = rand() % 35;
	b.color = Red;
	b.shape[0] = "¡á";

	HideCursor();

	while (true)
	{
		system("cls");

		if (GetAsyncKeyState(VK_LEFT))
		{
			a.x--;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			a.x++;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			a.y--;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			a.y++;
		}

		if (a.x == b.x && a.y == b.y)
		{
			b.x = rand() % 35;
			b.y = rand() % 35;
		}

		for (int i = 0; i < 3; i++)
		{

			SetTextColor(a.color);
			SetPosition(a.x, a.y + i);
			printf(a.shape[i]);
		}

		SetTextColor(b.color);
		SetPosition(b.x, b.y);
		printf(b.shape[0]);

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
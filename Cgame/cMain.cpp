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
	Obj obj;
	obj.x = 10;
	obj.y = 10;
	obj.color = White;
	obj.shape[0] = "   -----|-----";
	obj.shape[1] = "*>=====[_]L)";
	obj.shape[2] = "      -'-`-";

	HideCursor();

	while (true)
	{
		system("cls");

		if (GetAsyncKeyState(VK_LEFT))
		{
			obj.x--;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			obj.x++;
		}

		if (GetAsyncKeyState(VK_UP))
		{
			obj.y--;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			obj.y++;
		}

		SetTextColor(obj.color);
		for (int i = 0; i < 3; i++)
		{
			SetPosition(obj.x, obj.y + i);
			printf(obj.shape[i]);
		}

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
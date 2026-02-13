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
	const char* shape[8][3];

};



int main()
{
	Obj obj;
	obj.x = 10;
	obj.y = 10;
	obj.color = White;
	obj.shape[0][0] = "   -----|-----";
	obj.shape[0][1] = "*>=====[_]L)";
	obj.shape[0][2] = "      -'-`-";

	obj.shape[1][0] = "    ----|----";
	obj.shape[1][1] = "*>=====[_]L)";
	obj.shape[1][2] = "      -'-`-";

	obj.shape[2][0] = "     ---|---";
	obj.shape[2][1] = "*>=====[_]L)";
	obj.shape[2][2] = "      -'-`-";

	obj.shape[3][0] = "      --|--";
	obj.shape[3][1] = "*>=====[_]L)";
	obj.shape[3][2] = "      -'-`-";

	obj.shape[4][0] = "       -|-";
	obj.shape[4][1] = "*>=====[_]L)";
	obj.shape[4][2] = "      -'-`-";

	obj.shape[5][0] = "      --|--";
	obj.shape[5][1] = "*>=====[_]L)";
	obj.shape[5][2] = "      -'-`-";

	obj.shape[6][0] = "     ---|---";
	obj.shape[6][1] = "*>=====[_]L)";
	obj.shape[6][2] = "      -'-`-";

	obj.shape[7][0] = "    ----|----";
	obj.shape[7][1] = "*>=====[_]L)";
	obj.shape[7][2] = "      -'-`-";


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
			printf(obj.shape[1][i]);
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
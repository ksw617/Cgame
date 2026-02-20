#include <stdio.h>
#include <Windows.h>

#pragma region Enum
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
#pragma endregion
#pragma region WIN_API
void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);
#pragma endregion

#pragma region Define

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

#pragma endregion


#pragma region MAP
int map[MAP_HEIGHT][MAP_WIDTH] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,1},
	{1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
	{1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1},
	{1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,1,0,0,0,1},
	{1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

};

#pragma endregion


int main()
{

	HideCursor();

	while (true)
	{
		system("cls");

		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				switch (map[y][x])
				{
				case 0:
					break;
				case 1:
					SetTextColor(White);
					SetPosition(x, y);
					printf("бс");
					break;
				default:
					break;
				}
			}
		}
	
		Sleep(50);
	}

	return 0;
}

#pragma region WIN_API

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
#pragma endregion

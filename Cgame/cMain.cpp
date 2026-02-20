#include <stdio.h>
#include <Windows.h>

#pragma region Define

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

#pragma endregion
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
#pragma region Struct
struct Obj
{
	int x;
	int y;
	Color color;
	const char* shape;
};
#pragma endregion

#pragma region WIN_API
void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);
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
	{1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,2,0,1},
	{1,0,1,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
	{1,1,1,1,0,0,2,0,1,0,0,0,1,0,0,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1},
	{1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,1,0,0,0,1},
	{1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,0,0,0,0,2,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

};

#pragma endregion

int main()
{
	Obj* player = (Obj*)malloc(sizeof(Obj));
	player->x = 10;
	player->y = 10;
	player->color = Yellow;
	player->shape = "¿Ê";

	Obj* enemy = (Obj*)malloc(sizeof(Obj));

	//1¹ø
	do
	{
		enemy->x = rand() % 18 + 1;
		enemy->y = rand() % 18 + 1;

	} while ((map[enemy->y][enemy->x] == 1);

	//2¹ø
	enemy->x = rand() % 18 + 1;
	enemy->y = rand() % 18 + 1;
	while (map[enemy->y][enemy->x] == 1)
	{
		enemy->x = rand() % 18 + 1;
		enemy->y = rand() % 18 + 1;
	}

	//3¹ø
	enemy->x = rand() % 18 + 1;
	enemy->y = rand() % 18 + 1;
	while (true)
	{
		enemy->x = rand() % 18 + 1;
		enemy->y = rand() % 18 + 1;
		if (map[enemy->y][enemy->x] != 1)
		{
			break;
		}
	}


	enemy->color = Red;
	enemy->shape = "º¿";
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
					printf("¡á");
					break;
				case 2:
					SetTextColor(Red);
					SetPosition(x, y);
					printf("¢¾");
					break;
				default:
					break;
				}
			}
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			player->x--;
			if (map[player->y][player->x] == 1)
			{
				player->x++;
			}
		}


		if (GetAsyncKeyState(VK_RIGHT))
		{
			player->x++;
			if (map[player->y][player->x] == 1)
			{
				player->x--;
			}
		}


		if (GetAsyncKeyState(VK_UP))
		{
			player->y--;
			if (map[player->y][player->x] == 1)
			{
				player->y++;
			}
		}


		if (GetAsyncKeyState(VK_DOWN))
		{
			player->y++;
			if (map[player->y][player->x] == 1)
			{
				player->y--;
			}
		}

		if (map[player->y][player->x] == 2)
		{
			map[player->y][player->x] = 0;
		}

		SetTextColor(player->color);
		SetPosition(player->x, player->y);
		printf(player->shape);

		SetTextColor(enemy->color);
		SetPosition(enemy->x, enemy->y);
		printf(enemy->shape);
	
		Sleep(50);
	}

	free(player);
	player = nullptr;

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

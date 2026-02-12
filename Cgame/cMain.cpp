#pragma region Header
#include <stdio.h>
#include <Windows.h>
#include <time.h>
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

enum Dir
{
	Left,
	Right,
	Up,
	Down
};

#pragma endregion

#pragma region ±¸Á¶Ã¼

struct Obj
{
	int x;
	int y;
	Color color;
	const char* shape;

};
#pragma endregion

#pragma region WIN_API
void SetPosition(int x, int y);
void SetTextColor(Color color);
void HideCursor();
#pragma endregion

#pragma region GAME

Obj* player;
Obj* enemy;
int heart;

void Init();
void Progress();
void Render();

#pragma endregion


int main()
{

	HideCursor();
	Init();

	while (true)
	{
		system("cls");

		Progress();
		Render();

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

#pragma region GAME
void Init()
{
	heart = 3;
	srand((unsigned)time(NULL));

	player = (Obj*)malloc(sizeof(Obj));
	player->x = 10;
	player->y = 10;
	player->color = Blue;
	player->shape = "¡á";

	enemy = (Obj*)malloc(sizeof(Obj));
	enemy->x = rand() % 30;
	enemy->y = rand() % 30 + 1;
	enemy->color = Red;
	enemy->shape = "¢¾";
}
void Progress()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		player->x--;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		player->x++;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		player->y--;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		player->y++;
	}

	if (player->x == enemy->x && player->y == enemy->y)
	{
		enemy->x = rand() % 30;
		enemy->y = rand() % 30 + 1;
		heart++;
	}

	Dir randDir = (Dir)(rand() % 4);

	switch (randDir)
	{
	case Left:
		enemy->x--;
		break;
	case Right:
		enemy->x++;
		break;
	case Up:
		enemy->y--;
		break;
	case Down:
		enemy->y++;
		break;
	default:
		break;
	}

}
void Render()
{
	SetPosition(player->x, player->y);
	SetTextColor(player->color);
	printf(player->shape);

	SetPosition(enemy->x, enemy->y);
	SetTextColor(enemy->color);
	printf(enemy->shape);

	for (int i = 0; i < heart; i++)
	{
		SetPosition(i, 0);
		SetTextColor(Red);
		printf("¢¾");
	}
}
#pragma endregion


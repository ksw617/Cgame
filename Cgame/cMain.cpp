#include <stdio.h>
#include <Windows.h>

#pragma region ENUM
enum Color
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKCYAN,
	DARKRED,
	DARKMAGENTA,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
};

#pragma endregion
#pragma region WIN_API
void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);
#pragma endregion

#pragma region GAME
void Logo();
void Menu();
void Stage();
#pragma endregion



int main()
{
	
	HideCursor();


	while (true)
	{
		system("cls");

		Logo();
	
		Sleep(50);
	}


	return 0;
}

#pragma region GAME

void Logo()
{
	SetTextColor(WHITE);
	SetPosition(10, 10);
	printf("LOGO");
}

void Menu()
{
	SetTextColor(WHITE);
	SetPosition(10, 10);
	printf("MENU");
}

void Stage()
{
	SetTextColor(WHITE);
	SetPosition(10, 10);
	printf("STAGE");
}
#pragma endregion


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

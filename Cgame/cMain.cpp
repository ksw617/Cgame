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

enum SCENE_ID
{
	LOGO,
	MENU, 
	STAGE,
};

#pragma endregion
#pragma region WIN_API
void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);
#pragma endregion

#pragma region GAME
void LogoInit();
void LogoUpdate();
void MenuInit();
void MenuUpate();
void StageInit();
void StageUpate();
#pragma endregion

SCENE_ID id;

int main()
{	
	HideCursor();

	id = LOGO;
	LogoInit();

	while (true)
	{
		system("cls");

		switch (id)
		{
		case LOGO:
			LogoUpdate();
			break;
		case MENU:
			MenuUpate();
			break;
		case STAGE:
			StageUpate();
			break;
		default:
			break;
		}
		Sleep(50);
	}


	return 0;
}

#pragma region GAME

#pragma region LOGO

void LogoInit()
{
}

void LogoUpdate()
{
	SetTextColor(WHITE);
	SetPosition(10, 10);
	printf("LOGO");

	if (GetAsyncKeyState(VK_RETURN))
	{
		SetTextColor(RED);
		SetPosition(10, 20);
		printf("PRESSED");
		MenuInit();
		id = MENU;
	}
}
#pragma endregion

#pragma region MENU
void MenuInit()
{
}

void MenuUpate()
{
	SetTextColor(WHITE);
	SetPosition(10, 10);
	printf("MENU");

	if (GetAsyncKeyState(VK_RETURN))
	{
		SetTextColor(YELLOW);
		SetPosition(10, 20);
		printf("PRESSED");
		StageInit();
		id = STAGE;
	}
}
#pragma endregion

#pragma region STAGE
void StageInit()
{
}

void StageUpate()
{
	SetTextColor(WHITE);
	SetPosition(10, 10);
	printf("STAGE");
}
#pragma endregion

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
